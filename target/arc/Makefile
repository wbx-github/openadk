# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=$(LINUX_DIR)/$(ADK_TARGET_KERNEL)
ifeq ($(ADK_TARGET_KERNEL_UIMAGE),y)
KERNEL:=$(LINUX_DIR)/arch/arc/boot/uImage
endif
ifeq ($(ADK_TARGET_KERNEL_LOADER),y)
KERNEL:=$(LINUX_DIR)/arch/arc/boot/loader
endif

QEMU_ARGS:=-monitor none -serial stdio
QEMU_ARGS+=-netdev user,id=eth0 -device virtio-net-device,netdev=eth0
QEMU_ARGS+=${ADK_QEMU_ARGS}

ifeq ($(ADK_TARGET_CPU_ARC_ARC700),y)
QEMU:=qemu-system-arc
QEMU_ARGS+=-cpu arc700
endif

ifeq ($(ADK_TARGET_CPU_ARC_ARCHS),y)
QEMU:=qemu-system-arc
QEMU_ARGS+=-cpu archs
endif

ifeq ($(ADK_TARGET_CPU_ARC_ARC32),y)
QEMU:=qemu-system-arc
QEMU_ARGS+=-cpu hs5x -M virt,ram_start=0
endif

ifeq ($(ADK_TARGET_CPU_ARC_ARC64),y)
QEMU:=qemu-system-arc64
QEMU_ARGS+=-cpu hs6x -M virt,ram_start=0
endif

# target helper text
ifeq ($(ADK_TARGET_FS),archive)
targethelp:
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSTARBALL)"
endif
ifeq ($(ADK_TARGET_FS),initramfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The initramfs image is: ${FW_DIR}/${INITRAMFS}'
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
	@echo '${QEMU} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
endif
ifeq ($(ADK_TARGET_SYSTEM_SYNOPSYS_NSIM),y)
ifeq ($(ADK_TARGET_LITTLE_ENDIAN),y)
ifeq ($(ADK_TARGET_CPU_ARC_ARC700),y)
	@echo './scripts/nsim.sh arcv1 $(FW_DIR)/${TARGET_KERNEL}'
endif
ifeq ($(ADK_TARGET_CPU_ARC_ARCHS),y)
	@echo './scripts/nsim.sh arcv2 $(FW_DIR)/${TARGET_KERNEL}'
endif
endif
ifeq ($(ADK_TARGET_BIG_ENDIAN),y)
ifeq ($(ADK_TARGET_CPU_ARC_ARC700),y)
	@echo './scripts/nsim.sh arcv1-be $(FW_DIR)/${TARGET_KERNEL}'
endif
ifeq ($(ADK_TARGET_CPU_ARC_ARCHS),y)
	@echo './scripts/nsim.sh arcv2-be $(FW_DIR)/${TARGET_KERNEL}'
endif
endif
endif
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSUSERTARBALL)"
endif

kernel-strip:
	@cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)

kernel-install: kernel-strip
	@cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(TARGET_KERNEL)

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
imageinstall: createinitramfs targethelp
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
