#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"
#include "elfldr.h"
#include "elf.h"
#include "ingenic.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define ALIGN(a) ((a + 4095) & ~4095)

#define TRAMP_ARGC	0 // command line argument count
#define TRAMP_ARGV	1 // command line argument array
#define TRAMP_ARG2	2
#define TRAMP_ARG3	3
#define TRAMP_ENTRY	4	// Kernel entry point

static const uint32_t trampoline_template[] = {
	0x3c04ffff,	// lui     a0,   0xffff
	0x3484ffff,	// ori     a0,a0,0xffff

	0x3c05ffff,	// lui     a1,   0xffff
	0x34a5ffff,	// ori     a1,a1,0xffff

	0x3c06ffff,	// lui     a2,   0xffff
	0x34c6ffff,	// ori     a2,a2,0xffff

	0x3c07ffff, // lui     a3,   0xffff
	0x34e7ffff,	// ori     a3,a3,0xffff

	0x3c08ffff,	// lui     t0,   0xffff
	0x3508ffff, // ori     t0,t0,0xffff
	0x01000008, // jr      t0
	0x00000000, // nop
};

static const unsigned char valid_ident[EI_PAD] = {
        [EI_MAG0]    = ELFMAG0,
        [EI_MAG1]    = ELFMAG1,
        [EI_MAG2]    = ELFMAG2,
        [EI_MAG3]    = ELFMAG3,
        [EI_CLASS]   = ELFCLASS32,
        [EI_DATA]    = ELFDATA2LSB,
        [EI_VERSION] = EV_CURRENT
};

static int load_segment(void *ingenic, void *data, uint32_t base, uint32_t filesz, uint32_t memsz) {
	uint32_t end = base + memsz, tail = memsz - filesz;
	int ret = 0;

	printf("Loading segment: base 0x%08X, file 0x%08X, mem 0x%08X\n", base, filesz, memsz);

	if(end > ingenic_sdram_size(ingenic) + SDRAM_BASE - STAGE2_CODESIZE) {
		fputs("  Segment doesn't fit into SDRAM\n", stderr);

		return -1;
	}

	if(filesz && ingenic_load_sdram(ingenic, data, base, filesz) == -1)
		return -1;

	if(tail) {
		char *dummy_data = malloc(tail);

		if(dummy_data == NULL)
			return -1;

		memset(dummy_data, 0, tail);

		ret = ingenic_load_sdram(ingenic, dummy_data, base + filesz, tail);

		free(dummy_data);
	}

	return ret;
}

static int load_elf_image(FILE *elf, void *ingenic, uint32_t *entry, uint32_t *end) {
	Elf32_Ehdr ehdr;
	Elf32_Phdr phdr;
	int i, ret;
	char *data;

	if(fread(&ehdr, 1, sizeof(Elf32_Ehdr), elf) != sizeof(Elf32_Ehdr)) {
		if(feof(elf))
			errno = EINVAL;

		return -1;
 	}

	*entry = ehdr.e_entry;

	if(memcmp(ehdr.e_ident, valid_ident, EI_PAD) != 0 || ehdr.e_type != ET_EXEC || ehdr.e_machine != EM_MIPS || ehdr.e_version != EV_CURRENT 
		|| ehdr.e_phoff == 0 || ehdr.e_phentsize != sizeof(Elf32_Phdr)) {

		fputs("Bad ELF identification\n", stderr);

		errno = EINVAL;

		return -1;
        }

	fseek(elf, ehdr.e_phoff, SEEK_SET);

	*end = 0;

 	for(i = 0; i < ehdr.e_phnum; i++) {
		if(fread(&phdr, 1, sizeof(Elf32_Phdr), elf) != sizeof(Elf32_Phdr)) {
			if(feof(elf))
 				errno = EINVAL;

			return -1;
		}

		if(phdr.p_type == PT_LOAD) {
			data = malloc(phdr.p_filesz);

			if(data == NULL)
				return -1;

			long save = ftell(elf);
			fseek(elf, phdr.p_offset, SEEK_SET);
			ret = fread(data, 1, phdr.p_filesz, elf);
			fseek(elf, save, SEEK_SET);

			if(ret != phdr.p_filesz) {
				free(data);
			
				if(feof(elf))
	 				errno = EINVAL;

				return -1;
			}

			ret = load_segment(ingenic, data, phdr.p_paddr, phdr.p_filesz, phdr.p_memsz);

			free(data);

			if(ret == -1)
				return -1;

			*end = max(phdr.p_paddr + phdr.p_memsz, *end);
		}
	}

	return 0;
}


static void trampoline_set(uint32_t *trampoline, int index,
                           uint32_t value) {
	index *= 2;

	trampoline[index] =     (trampoline[index]     & 0xFFFF0000) | ((value & 0xFFFF0000) >> 16);
	trampoline[index + 1] = (trampoline[index + 1] & 0xFFFF0000) | (value  & 0x0000FFFF);
}

static int load_args(void *ingenic, uint32_t base, const char *filename,
                     const char *const *args, int *pargc, uint32_t *end) {
						
	size_t total_len = 0;
	int argc = 0;
	
	for(int i = 0; args[i]; i++) {
		size_t len = strlen(args[i]);
		total_len += len + 1;
		
		for(int j = 0; j < len; j++)
			if(args[i][j] == ' ')
				argc++;
				
		argc++;
	}
	
	*pargc = argc;
	*end = base + total_len + sizeof(uint32_t) * argc;
	
	uint32_t *buf = malloc(sizeof(uint32_t) * argc + total_len);
	if(buf == NULL)
		return -1;
		
	char *cmdline = (char *)(buf + argc);
	size_t off = 0;
	
	for(int i = 0; args[i]; i++) {
		size_t len = strlen(args[i]);
		memcpy(cmdline + off, args[i], len + 1);
		
		if(args[i + 1])
			cmdline[off + len] = ' ';
			
		off += len + 1;
	}
	
	printf("Compiled cmdline: '%s'\n", cmdline);
	
	uint32_t offset = 0;
	char *ptr = cmdline;

	for(int i = 0; i < argc; i++) {
		buf[i] = base + argc * sizeof(uint32_t) + offset;

		ptr = strchr(ptr, ' ');

		if(ptr == NULL)
			break;

		*ptr++ = 0;
		offset = ptr - cmdline;		
	}
			
	int ret = load_segment(ingenic,
	                       buf,
	                       base,
	                       sizeof(uint32_t) * argc + total_len,
	                       sizeof(uint32_t) * argc + total_len);
	free(buf);
	
	return ret;	
}

int load_elf(void *ingenic,
             const char *filename,
             const char *args,
             const char *initrd) {
				 
	uint32_t entry, end, trampoline_base, args_base;
	uint32_t initrd_base, initrd_size;
	
	int argc;
	const char *all_args[4] = { filename, args, NULL, NULL };
	char initrd_args[64];
	
	printf(
		"Loading kernel %s:\n"
		"  Command line: '%s'\n",
		filename,
		args
	);

	FILE *elf = fopen(filename, "rb");

	if(elf == NULL)
		return -1;

	int ret = load_elf_image(elf, ingenic, &entry, &end);

	fclose(elf);

	if(ret == -1)
		return -1;
	
	if(initrd) {
		struct stat statbuf;
		
		initrd_base = ALIGN(end);
		
		if(stat(initrd, &statbuf) == -1)
			return -1;
			
		initrd_size = statbuf.st_size;
		
		printf("Loading initrd to 0x%08X, size 0x%08X\n",
		       initrd_base, initrd_size);

				
		end = initrd_base + initrd_size;
		
		if(end > ingenic_sdram_size(ingenic) + SDRAM_BASE - STAGE2_CODESIZE) {
			fputs("  Initrd doesn't fit into SDRAM\n", stderr);

			return -1;
		}		
					
		if(ingenic_load_sdram_file(ingenic, initrd_base, initrd) == -1)
			return -1;
				
		snprintf(initrd_args, sizeof(initrd_args),
		         "rd_start=0x%08X rd_size=0x%08X",
		         initrd_base, initrd_size);
		         
		all_args[2] = initrd_args;
	}
	
	args_base = ALIGN(end);
	
	if(load_args(ingenic, args_base, filename, all_args, &argc, &end) == -1)
		return -1;

	trampoline_base = ALIGN(end);
	end = trampoline_base + sizeof(trampoline_template);

	uint32_t *trampoline = malloc(sizeof(trampoline_template));
	if(trampoline == NULL)
		return -1;

	memcpy(trampoline, trampoline_template, sizeof(trampoline_template));
	trampoline_set(trampoline, TRAMP_ARGC, argc);
	trampoline_set(trampoline, TRAMP_ARGV, args_base);
	trampoline_set(trampoline, TRAMP_ARG2, 0);
	trampoline_set(trampoline, TRAMP_ARG3, 0);
	trampoline_set(trampoline, TRAMP_ENTRY, entry);

	ret = load_segment(ingenic, trampoline, trampoline_base, sizeof(trampoline_template), sizeof(trampoline_template));

	free(trampoline);

	if(ret == -1)
		return -1;

	printf("Image end: 0x%08X, entry: 0x%08X\n", end, entry);

	//return 0;
	return ingenic_go(ingenic, trampoline_base);
}

