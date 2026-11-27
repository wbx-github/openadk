#ifndef __ELFLDR__H__
#define __ELFLDR__H__

int load_elf(void *ingenic,
             const char *filename,
             const char *args,
             const char *initrd);

#endif

