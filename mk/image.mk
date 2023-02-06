# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

ifeq ($(ADK_RUNTIME_FIX_PERMISSION),y)
FAKEROOT:=$(STAGING_HOST_DIR)/usr/bin/fakeroot --
else
FAKEROOT:=
endif

ifeq ($(ADK_TARGET_OS_LINUX),y)
# relative paths, like 'mksh' or '../usr/bin/foosh'
ifeq (${ADK_BINSH_ASH},y)
BINSH:=ash
else ifeq (${ADK_BINSH_BASH},y)
BINSH:=bash
else ifeq (${ADK_BINSH_SASH},y)
BINSH:=sash
else ifeq (${ADK_BINSH_HUSH},y)
BINSH:=hush
else ifeq (${ADK_BINSH_MKSH},y)
BINSH:=mksh
else ifeq (${ADK_BINSH_ZSH},y)
BINSH:=zsh
else
$(error No /bin/sh configured!)
endif

# absolute paths
ifeq (${ADK_ROOTSH_ASH},y)
ROOTSH:=/bin/ash
else ifeq (${ADK_ROOTSH_BASH},y)
ROOTSH:=/bin/bash
else ifeq (${ADK_ROOTSH_SASH},y)
ROOTSH:=/bin/sash
else ifeq (${ADK_ROOTSH_HUSH},y)
ROOTSH:=/bin/hush
else ifeq (${ADK_ROOTSH_MKSH},y)
ROOTSH:=/bin/mksh
else ifeq (${ADK_ROOTSH_TCSH},y)
ROOTSH:=/usr/bin/tcsh
else ifeq (${ADK_ROOTSH_ZSH},y)
ROOTSH:=/bin/zsh
else
$(error No login shell configured!)
endif
endif

imageprepare: image-prepare-post extra-install prelink

# if an extra directory exist in ADK_TOPDIR, copy all content over the 
# root directory, do the same if make extra=/dir/to/extra is used
extra-install:
	@-if [ -h ${TARGET_DIR}/etc/resolv.conf -a -f $(ADK_TOPDIR)/extra/etc/resolv.conf ];then \
		rm ${TARGET_DIR}/etc/resolv.conf;\
	fi
	@if test -d '${ADK_TOPDIR}/extra'; then \
		(cd '${ADK_TOPDIR}/extra' && tar -cf - .) | \
		    (cd ${TARGET_DIR}; tar -xf -); \
	fi
ifneq (,$(strip ${extra}))
	@(cd '${extra}' && tar -cf - .) | (cd ${TARGET_DIR}; tar -xf -)
endif

image-prepare-post:
	$(BASH) $(ADK_TOPDIR)/scripts/update-rcconf
	rng=/dev/arandom; test -e $$rng || rng=/dev/urandom; \
	    dd if=$$rng bs=512 count=1 >>${TARGET_DIR}/etc/.rnd 2>/dev/null; \
	    chmod 600 ${TARGET_DIR}/etc/.rnd
	-for dir in X11 truetype; do \
		if [ -d ${TARGET_DIR}/usr/share/fonts/$${dir} ];then \
			for i in $$(ls ${TARGET_DIR}/usr/share/fonts/$${dir}/);do \
				mkfontdir ${TARGET_DIR}/usr/share/fonts/$${dir}/$${i}; \
				mkfontscale ${TARGET_DIR}/usr/share/fonts/$${dir}/$${i}; \
			done; \
		fi; \
	done
	$(SED) '/^root:/s!:/bin/sh$$!:${ROOTSH}!' ${TARGET_DIR}/etc/passwd
	-rm -f ${TARGET_DIR}/bin/sh
	ln -sf ${BINSH} ${TARGET_DIR}/bin/sh

	test -z $(GIT) || \
	     $(GIT) log -1|head -1|sed -e 's#commit ##' \
		> $(TARGET_DIR)/etc/.adkgithash
	echo $(ADK_APPLIANCE_VERSION) > $(TARGET_DIR)/etc/.adkversion
	echo $(ADK_TARGET_SYSTEM) > $(TARGET_DIR)/etc/.adktarget
	$(TARGET_CC) -v 2> $(TARGET_DIR)/etc/.adkcompiler
	$(TARGET_LD) -v > $(TARGET_DIR)/etc/.adklinker
ifneq (${ADK_PACKAGE_CONFIG_IN_ETC},)
	gzip -9c ${ADK_TOPDIR}/.config > $(TARGET_DIR)/etc/adkconfig.gz
	chmod 600 $(TARGET_DIR)/etc/adkconfig.gz
endif
ifneq ($(ADK_TARGET_ARCH_AARCH64)$(ADK_TARGET_ARCH_X86_64)$(ADK_TARGET_ARCH_PPC64)$(ADK_TARGET_ARCH_SPARC64)$(ADK_TARGET_ABI_N32)$(ADK_TARGET_ABI_N64),)
	test ! -d ${TARGET_DIR}/lib || mv ${TARGET_DIR}/lib/* ${TARGET_DIR}/${ADK_TARGET_LIBC_PATH}
	test ! -d ${TARGET_DIR}/lib || rm -rf ${TARGET_DIR}/lib
	ln -sf /${ADK_TARGET_LIBC_PATH} ${TARGET_DIR}/lib
	mkdir -p ${TARGET_DIR}/usr/${ADK_TARGET_LIBC_PATH} 2>/dev/null
	-test ! -d ${TARGET_DIR}/usr/lib || mv ${TARGET_DIR}/usr/lib/* ${TARGET_DIR}/usr/${ADK_TARGET_LIBC_PATH} 2>/dev/null
	test ! -d ${TARGET_DIR}/usr/lib || rm -rf ${TARGET_DIR}/usr/lib/
	(cd ${TARGET_DIR}/usr ; ln -sf ${ADK_TARGET_LIBC_PATH} lib)
endif
ifeq ($(ADK_TARGET_ARCH_LOONGARCH)$(ADK_TARGET_ARCH_S390),y)
	(cd ${TARGET_DIR}/; ln -sf lib lib64)
endif

ifeq (${ADK_PRELINK},)
prelink:
else
${TARGET_DIR}/etc/prelink.conf:
	echo '/' > $@

prelink: ${TARGET_DIR}/etc/prelink.conf
	$(TRACE) target/prelink
	${TARGET_CROSS}prelink ${ADK_PRELINK_OPTS} \
		--ld-library-path=${STAGING_TARGET_DIR}/usr/lib:${STAGING_TARGET_DIR}/lib \
		--root=${TARGET_DIR} -a $(MAKE_TRACE)
endif

KERNEL_PKGDIR:=$(LINUX_BUILD_DIR)/kernel-pkg
KERNEL_PKG:=$(PACKAGE_DIR)/kernel_$(KERNEL_VERSION)_$(ADK_TARGET_CPU_ARCH).$(PKG_SUFFIX)
TARGET_KERNEL=		${ADK_TARGET_SYSTEM}-${ADK_TARGET_FS}-kernel
INITRAMFS=		${ADK_TARGET_SYSTEM}-${ADK_TARGET_LIBC}-${ADK_TARGET_FS}
ROOTFSSQUASHFS=		${ADK_TARGET_SYSTEM}-${ADK_TARGET_LIBC}-${ADK_TARGET_FS}.img
ROOTFSJFFS2=		${ADK_TARGET_SYSTEM}-${ADK_TARGET_LIBC}-jffs2.img
ROOTFSUBIFS=		${ADK_TARGET_SYSTEM}-${ADK_TARGET_LIBC}-ubifs.img
ROOTFSTARBALL=		${ADK_TARGET_SYSTEM}-${ADK_TARGET_LIBC}-${ADK_TARGET_FS}+kernel.tar.xz
ROOTFSUSERTARBALL=	${ADK_TARGET_SYSTEM}-${ADK_TARGET_LIBC}-${ADK_TARGET_FS}.tar.xz
ROOTFSISO=		${ADK_TARGET_SYSTEM}-${ADK_TARGET_LIBC}.iso

kernel-package: kernel-strip
	$(START_TRACE) "target/$(ADK_TARGET_ARCH)-create-kernel-package.. "
	rm -rf $(KERNEL_PKGDIR)
ifeq ($(ADK_TARGET_DUAL_BOOT),y)
	@mkdir -p $(KERNEL_PKGDIR)
	cp $(BUILD_DIR)/$(TARGET_KERNEL) $(KERNEL_PKGDIR)/kernel
else
	@mkdir -p $(KERNEL_PKGDIR)/boot
	cp $(BUILD_DIR)/$(TARGET_KERNEL) $(KERNEL_PKGDIR)/boot/kernel
endif
	@${BASH} ${SCRIPT_DIR}/make-ipkg-dir.sh ${KERNEL_PKGDIR} \
	    ../$(ADK_TARGET_OS)/kernel.control ${KERNEL_VERSION} ${ADK_TARGET_CPU_ARCH}
	PATH='$(HOST_PATH)' $(PKG_BUILD) $(KERNEL_PKGDIR) $(PACKAGE_DIR) $(MAKE_TRACE)
	$(PKG_INSTALL) $(KERNEL_PKG) $(MAKE_TRACE)
	$(CMD_TRACE) " done"
	$(END_TRACE)

${FW_DIR}/${ROOTFSTARBALL}: ${TARGET_DIR}/.adk kernel-package
	cd ${TARGET_DIR}; find . | sed -n '/^\.\//s///p' | sort | \
		$(CPIO) --quiet -o -Hustar --owner=0:0 | $(XZ) -c >$@
ifeq ($(ADK_TARGET_QEMU),y)
	@cp $(KERNEL) $(FW_DIR)/$(TARGET_KERNEL)
endif

${FW_DIR}/${ROOTFSUSERTARBALL}: ${TARGET_DIR}/.adk
	cd ${TARGET_DIR}; find . | grep -v ./boot/ | sed -n '/^\.\//s///p' | sort | \
		$(CPIO) --quiet -o -Hustar --owner=0:0 | $(XZ) -c >$@

${STAGING_TARGET_DIR}/${INITRAMFS}_list: ${TARGET_DIR}/.adk
	PATH='${HOST_PATH}' $(BASH) ${SCRIPT_DIR}/gen_initramfs_list.sh -u squash -g squash \
		${TARGET_DIR}/ >$@
	( \
		echo "nod /dev/console 0644 0 0 c 5 1"; \
		echo "nod /dev/tty 0644 0 0 c 5 0"; \
		for i in 0 1 2 3 4; do \
			echo "nod /dev/tty$$i 0644 0 0 c 4 $$$$i"; \
		done; \
		echo "nod /dev/null 0644 0 0 c 1 3"; \
		echo "nod /dev/ram 0655 0 0 b 1 1"; \
		echo "nod /dev/ttyS0 0660 0 0 c 4 64"; \
		echo "nod /dev/ttyS1 0660 0 0 c 4 65"; \
		echo "nod /dev/ttyB0 0660 0 0 c 11 0"; \
		echo "nod /dev/ttyB1 0660 0 0 c 11 1"; \
		echo "nod /dev/ttyAMA0 0660 0 0 c 204 64"; \
		echo "nod /dev/ttyAMA1 0660 0 0 c 204 65"; \
		echo "nod /dev/ttySC0 0660 0 0 c 204 8"; \
		echo "nod /dev/ttySC1 0660 0 0 c 204 9"; \
		echo "nod /dev/ttySC2 0660 0 0 c 204 10"; \
		echo "nod /dev/ttyBF0 0660 0 0 c 204 64"; \
		echo "nod /dev/ttyBF1 0660 0 0 c 204 65"; \
		echo "nod /dev/ttyUL0 0660 0 0 c 204 187"; \
		echo "nod /dev/ttyUL1 0660 0 0 c 204 188"; \
		echo "slink /init /sbin/init 755 0 0"; \
	) >>$@

${FW_DIR}/${INITRAMFS}: ${STAGING_TARGET_DIR}/${INITRAMFS}_list
	${LINUX_DIR}/usr/gen_init_cpio ${STAGING_TARGET_DIR}/${INITRAMFS}_list | \
		${ADK_COMPRESSION_TOOL} -c >$@

${BUILD_DIR}/root.squashfs: ${TARGET_DIR}/.adk
	${STAGING_HOST_DIR}/usr/bin/mksquashfs ${TARGET_DIR} \
		${BUILD_DIR}/root.squashfs -comp xz \
		-nopad -noappend -root-owned $(MAKE_TRACE)

${FW_DIR}/${ROOTFSJFFS2}: ${TARGET_DIR}
	PATH='${HOST_PATH}' mkfs.jffs2 $(ADK_JFFS2_OPTS) -q -r ${TARGET_DIR} \
		--pad=$(ADK_TARGET_MTD_SIZE) -o ${FW_DIR}/${ROOTFSJFFS2} $(MAKE_TRACE)

${FW_DIR}/${ROOTFSUBIFS}: ${TARGET_DIR}
	( \
		PATH='${HOST_PATH}'; \
		SP_SIZE='${ADK_TARGET_FLASH_SUBPAGE_SIZE}'; \
		PG_SIZE='${ADK_TARGET_FLASH_PAGE_SIZE}'; \
		LEB_SIZE=$$(((($$SP_SIZE + $$PG_SIZE) / $$PG_SIZE) * $$PG_SIZE)); \
		mkfs.ubifs -r ${TARGET_DIR} \
			-m $$PG_SIZE \
			-e $$((${ADK_TARGET_FLASH_PEB_SIZE} - $$LEB_SIZE)) \
			-c $$(((${ADK_TARGET_MTD_SIZE} / $$LEB_SIZE))) \
			-o ${FW_DIR}/rootfs.ubifs; \
		cd ${FW_DIR} && ubinize -o $@ \
			-p ${ADK_TARGET_FLASH_PEB_SIZE} \
			-m ${ADK_TARGET_FLASH_PAGE_SIZE} \
			-s ${ADK_TARGET_FLASH_SUBPAGE_SIZE} \
			"${ADK_TOPDIR}/target/${ADK_TARGET_ARCH}/${ADK_TARGET_SYSTEM}/ubinize.cfg"; \
	) $(MAKE_TRACE)

createinitramfs: ${STAGING_TARGET_DIR}/${INITRAMFS}_list
	${SED} 's/.*CONFIG_\(RD_\|BLK_DEV_INITRD\|INITRAMFS_\).*//' \
		${LINUX_DIR}/.config
	( \
		echo "CONFIG_BLK_DEV_INITRD=y"; \
		echo "CONFIG_ACPI_INITRD_TABLE_OVERRIDE=n"; \
		echo 'CONFIG_INITRAMFS_SOURCE="${STAGING_TARGET_DIR}/${INITRAMFS}_list"'; \
		echo '# CONFIG_INITRAMFS_COMPRESSION_NONE is not set'; \
		echo 'CONFIG_CRC32_BIT=y'; \
		echo '# CONFIG_CRC32_SELFTEST is not set'; \
		echo '# CONFIG_CRC32_SLICEBY8 is not set'; \
		echo '# CONFIG_CRC32_SLICEBY4 is not set'; \
		echo '# CONFIG_CRC32_SARWATE is not set'; \
		echo 'CONFIG_INITRAMFS_FORCE=n'; \
		echo 'CONFIG_INITRAMFS_ROOT_UID=0'; \
		echo 'CONFIG_INITRAMFS_ROOT_GID=0'; \
		echo 'CONFIG_INITRAMFS_IS_LARGE=n'; \
		echo 'CONFIG_INITRAMFS_PRESERVE_MTIME=n'; \
	) >> ${LINUX_DIR}/.config
ifeq ($(ADK_LINUX_KERNEL_COMP_XZ),y)
		echo "CONFIG_RD_BZIP2=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_GZIP=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZMA=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZ4=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZO=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_XZ=y" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_ZSTD=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_INITRAMFS_COMPRESSION_XZ=y" >> ${LINUX_DIR}/.config
		echo "CONFIG_XZ_DEC_X86=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_XZ_DEC_POWERPC=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_XZ_DEC_IA64=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_XZ_DEC_ARM=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_XZ_DEC_ARMTHUMB=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_XZ_DEC_SPARC=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_XZ_DEC_TEST=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_XZ_DEC_MICROLZMA=n" >> ${LINUX_DIR}/.config
endif
ifeq ($(ADK_LINUX_KERNEL_COMP_LZ4),y)
		echo "CONFIG_RD_XZ=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_BZIP2=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_GZIP=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZO=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZ4=y" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZMA=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_ZSTD=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_INITRAMFS_COMPRESSION_LZ4=y" >> ${LINUX_DIR}/.config
endif
ifeq ($(ADK_LINUX_KERNEL_COMP_LZMA),y)
		echo "CONFIG_RD_XZ=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_BZIP2=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_GZIP=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZO=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZ4=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZMA=y" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_ZSTD=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_INITRAMFS_COMPRESSION_LZMA=y" >> ${LINUX_DIR}/.config
endif
ifeq ($(ADK_LINUX_KERNEL_COMP_LZO),y)
		echo "CONFIG_RD_XZ=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_BZIP2=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_GZIP=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZMA=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZ4=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZO=y" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_ZSTD=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_INITRAMFS_COMPRESSION_LZO=y" >> ${LINUX_DIR}/.config
endif
ifeq ($(ADK_LINUX_KERNEL_COMP_GZIP),y)
		echo "CONFIG_RD_XZ=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_BZIP2=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZO=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZMA=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZ4=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_GZIP=y" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_ZSTD=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_INITRAMFS_COMPRESSION_GZIP=y" >> ${LINUX_DIR}/.config
endif
ifeq ($(ADK_LINUX_KERNEL_COMP_BZIP2),y)
		echo "CONFIG_RD_XZ=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_GZIP=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZMA=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZO=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZ4=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_BZIP2=y" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_ZSTD=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_INITRAMFS_COMPRESSION_BZIP2=y" >> ${LINUX_DIR}/.config
endif
ifeq ($(ADK_LINUX_KERNEL_COMPRESS_NONE),y)
		echo "CONFIG_RD_XZ=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_BZIP2=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZO=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZMA=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_LZ4=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_GZIP=n" >> ${LINUX_DIR}/.config
		echo "CONFIG_RD_ZSTD=n" >> ${LINUX_DIR}/.config
endif
	@-rm $(LINUX_DIR)/usr/initramfs_data.cpio* 2>/dev/null
ifneq ($(ADK_TARGET_KERNEL_APPEND_DTB),)
	${KERNEL_MAKE} zImage dtbs $(MAKE_TRACE)
	(cd $(LINUX_DIR)/arch/$(ADK_TARGET_ARCH)/boot && \
	 cat dts/${ADK_TARGET_KERNEL_APPEND_DTB}.dtb >> zImage)
endif
	${KERNEL_MAKE} $(ADK_TARGET_KERNEL) $(MAKE_TRACE)
	@cp $(KERNEL) $(FW_DIR)/$(TARGET_KERNEL)

${FW_DIR}/${ROOTFSISO}: ${TARGET_DIR} kernel-package
	mkdir -p ${TARGET_DIR}/boot/syslinux
	cp ${STAGING_HOST_DIR}/usr/share/syslinux/{isolinux.bin,ldlinux.c32} \
		${TARGET_DIR}/boot/syslinux
	echo 'DEFAULT /boot/kernel root=/dev/sr0' > \
		${TARGET_DIR}/boot/syslinux/isolinux.cfg
	PATH='${HOST_PATH}' mkisofs -R -uid 0 -gid 0 -o $@ \
		-b boot/syslinux/isolinux.bin \
		-c boot/syslinux/boot.cat -no-emul-boot \
		-boot-load-size 4 -boot-info-table ${TARGET_DIR}

ifeq (,$(wildcard $(ADK_TOPDIR)/target/$(ADK_TARGET_ARCH)/$(ADK_TARGET_SYSTEM)/$(ADK_TARGET_GENIMAGE_FILENAME)))
GENCFG:=$(ADK_TOPDIR)/adk/genimage/$(ADK_TARGET_GENIMAGE_FILENAME)
else
GENCFG:=$(ADK_TOPDIR)/target/$(ADK_TARGET_ARCH)/$(ADK_TARGET_SYSTEM)/$(ADK_TARGET_GENIMAGE_FILENAME)
endif
ifeq (,$(wildcard $(ADK_TOPDIR)/target/$(ADK_TARGET_ARCH)/$(ADK_TARGET_SYSTEM)/$(ADK_TARGET_EXTLINUX_FILENAME)))
EXTLINUX:=$(ADK_TOPDIR)/adk/extlinux/$(ADK_TARGET_EXTLINUX_FILENAME)
else
EXTLINUX:=$(ADK_TOPDIR)/target/$(ADK_TARGET_ARCH)/$(ADK_TARGET_SYSTEM)/$(ADK_TARGET_EXTLINUX_FILENAME)
endif

${FW_DIR}/${GENIMAGE}: ${TARGET_DIR} kernel-package
	@rm -rf ${FW_DIR}/temp
	@mkdir -p ${FW_DIR}/temp
	@$(CP) $(KERNEL) $(FW_DIR)/kernel
	@dd if=/dev/zero of=${FW_DIR}/cfgfs.img bs=16384 count=1024 $(MAKE_TRACE)
	@mkdir -p ${FW_DIR}/extlinux
	@$(CP) $(EXTLINUX) $(FW_DIR)/extlinux
ifeq ($(ADK_RUNTIME_FIX_PERMISSION),y)
	echo '#!/bin/sh' > $(ADK_TOPDIR)/scripts/fakeroot.sh
	echo "chown -R 0:0 $(TARGET_DIR)" >> $(ADK_TOPDIR)/scripts/fakeroot.sh
	echo 'cd $(TARGET_DIR)' >> $(ADK_TOPDIR)/scripts/fakeroot.sh
	-@cat $(STAGING_TARGET_DIR)/scripts/permissions.sh >> $(ADK_TOPDIR)/scripts/fakeroot.sh 2>/dev/null
	chmod 755 $(ADK_TOPDIR)/scripts/fakeroot.sh
	PATH='$(HOST_PATH)' $(FAKEROOT) $(ADK_TOPDIR)/scripts/fakeroot.sh
	rm $(ADK_TOPDIR)/scripts/fakeroot.sh $(STAGING_TARGET_DIR)/scripts/permissions.sh
endif
ifeq ($(ADK_TARGET_DUAL_BOOT),y)
	$(CP) $(FW_DIR)/kernel $(TARGET_DIR)
	$(CP) $(FW_DIR)/*.dtb $(TARGET_DIR)
	mkdir $(TARGET_DIR)/extlinux
	$(CP) $(EXTLINUX) $(TARGET_DIR)/extlinux
	$(SED) "s#root=.*#root=/dev/$(ADK_TARGET_ROOTDEV)p1#" $(TARGET_DIR)/extlinux/extlinux.conf
	PATH='${HOST_PATH}' $(FAKEROOT) mkfs.ext2 \
		-d "$(TARGET_DIR)" \
		-r 1 -N 0 -m 5 -L "rootfs1" \
		$(FW_DIR)/rootfs1.ext "64M" $(MAKE_TRACE)
	$(SED) "s#root=.*#root=/dev/$(ADK_TARGET_ROOTDEV)p2#" $(TARGET_DIR)/extlinux/extlinux.conf
	PATH='${HOST_PATH}' $(FAKEROOT) mkfs.ext2 \
		-d "$(TARGET_DIR)" \
		-r 1 -N 0 -m 5 -L "rootfs2" \
		$(FW_DIR)/rootfs2.ext "64M" $(MAKE_TRACE)
	PATH='${HOST_PATH}' genimage \
		--config "$(GENCFG)" \
		--tmppath "${FW_DIR}/temp" \
		--rootpath "$(TARGET_DIR)" \
		--inputpath "$(FW_DIR)" \
		--outputpath "$(FW_DIR)" $(MAKE_TRACE)
else
	PATH='${HOST_PATH}' $(FAKEROOT) mkfs.ext2 \
		-d "$(TARGET_DIR)" \
		-r 1 -N 0 -m 5 -L "rootfs" \
		$(FW_DIR)/rootfs.ext "64M" $(MAKE_TRACE)
	PATH='${HOST_PATH}' genimage \
		--config "$(GENCFG)" \
		--tmppath "${FW_DIR}/temp" \
		--rootpath "$(TARGET_DIR)" \
		--inputpath "$(FW_DIR)" \
		--outputpath "$(FW_DIR)" $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_DUAL_BOOT),y)
	(cd ${TARGET_DIR}; find . | sed -n '/^\.\//s///p' | sort | \
		PATH='${HOST_PATH}' $(CPIO) -o --quiet -Hustar --owner=0:0 | \
		${XZ} -c > ${FW_DIR}/openadk.tar.xz)
	(cd ${FW_DIR}; PATH='${HOST_PATH}' sha256sum openadk.tar.xz \
		| cut -d\  -f1 > sha256.txt)
	(cd ${FW_DIR}; PATH='${HOST_PATH}' tar -cf ${ADK_TARGET_SYSTEM}-update.tar openadk.tar.xz sha256.txt)
	@rm -rf ${FW_DIR}/temp
endif
ifeq ($(ADK_PACKAGE_GRUB_EFI_X86)$(ADK_PACKAGE_GRUB_EFI_X86_64),y)
	@if [ ! -f $(ADK_TOPDIR)/bios-$(ADK_TARGET_ARCH).bin ]; then \
		cd $(ADK_TOPDIR); wget http://distfiles.openadk.org/bios-$(ADK_TARGET_ARCH).bin ;\
	fi
endif

imageclean:
	rm -f $(FW_DIR)/$(ADK_TARGET_SYSTEM)-* ${BUILD_DIR}/$(ADK_TARGET_SYSTEM)-*
