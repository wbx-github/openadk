# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

OSTRIP:=-R .reginfo -R .notes -R .note -R .comment -R .mdebug 
OSTRIP+=-R .note.gnu.build-id -K sun4u_init -K _end -K _start

KERNEL:=$(LINUX_DIR)/vmlinux
ifeq ($(ADK_TARGET_KERNEL_ZIMAGE),y)
KERNEL:=$(LINUX_DIR)/arch/sparc/boot/zImage
endif
ifeq ($(ADK_TARGET_KERNEL_VMLINUX_AOUT),y)
KERNEL:=$(LINUX_DIR)/arch/sparc/boot/image
endif

ifeq ($(ADK_TARGET_SYSTEM_QEMU_SPARC_LEON3),y)
QEMU_ARGS:=-M leon3_generic
QEMU_ARGS+=-nographic
endif

ifeq ($(ADK_TARGET_SYSTEM_QEMU_SPARC),y)
QEMU_ARGS:=-M SS-10
QEMU_ARGS+=${ADK_QEMU_ARGS}
ifeq ($(ADK_TARGET_FS),archive)
QEMU_ARGS+=-append "root=/dev/sda1"
endif
endif

# target helper text
ifeq ($(ADK_TARGET_FS),archive)
targethelp:
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSTARBALL)"
ifeq ($(ADK_TARGET_QEMU),y)
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "Use following command to create a QEMU Image:"
	@echo "./scripts/create.sh qemu-${ADK_TARGET_CPU_ARCH}.img $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Start qemu with following options:"
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) qemu-${ADK_TARGET_CPU_ARCH}.img'
endif
endif
ifeq ($(ADK_TARGET_FS),initramfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The initramfs image is: ${FW_DIR}/${INITRAMFS}'
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) -initrd ${FW_DIR}/${INITRAMFS}'
endif
endif
ifeq ($(ADK_TARGET_FS),initramfsarchive)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSUSERTARBALL)"
endif
ifeq ($(ADK_TARGET_FS),initramfspiggyback)
targethelp:
	@echo 'The kernel+initramfs file is: $(FW_DIR)/${TARGET_KERNEL}'
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
endif
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The nfs root tarball is: ${FW_DIR}/${ROOTFSUSERTARBALL}'
endif

# image creation and kernel install
kernel-strip:
	cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
	$(TARGET_CROSS)objcopy $(OSTRIP) -S $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)

kernel-install: kernel-strip
ifeq ($(ADK_TARGET_KERNEL_VMLINUX_AOUT),y)
	PATH='$(HOST_PATH)' elftoaout -o $(FW_DIR)/$(TARGET_KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
else
	cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(TARGET_KERNEL)
endif

mklinuximg:
ifeq ($(ADK_TARGET_SYSTEM_QEMU_SPARC_LEON3),y)
	PATH='$(HOST_PATH)' CROSS_COMPILE=sparc-leon3-linux-uclibc- \
	     mklinuximg $(KERNEL) $(FW_DIR)/$(TARGET_KERNEL) \
	     -cmdline "console=ttyS0,38400" -cflags "--sysroot=$(STAGING_TARGET_DIR)" \
	     -strip
endif

# filesystem specific targets
ifeq ($(ADK_TARGET_FS),archive)
imageinstall: $(FW_DIR)/$(ROOTFSTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfs)
imageinstall: kernel-install $(FW_DIR)/$(INITRAMFS) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfsarchive)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfspiggyback)
imageinstall: createinitramfs mklinuximg targethelp
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
