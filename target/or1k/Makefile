# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=$(LINUX_DIR)/vmlinux
OSTRIP:=-R .reginfo -R .notes -R .note -R .comment -R .mdebug -R .note.gnu.build-id
QEMU_ARGS:=-m 256 -nographic

# target helper text
ifeq ($(ADK_TARGET_FS),initramfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The initramfs image is: ${FW_DIR}/${INITRAMFS}'
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-or1k ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) -initrd ${FW_DIR}/${INITRAMFS}'
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
	@echo 'qemu-system-or1k ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
endif
endif

kernel-strip:
	$(TARGET_CROSS)objcopy $(OSTRIP) -S $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)

kernel-install: kernel-strip
	@cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(TARGET_KERNEL)

# filesystem specific targets
ifeq ($(ADK_TARGET_FS),initramfs)
imageinstall: kernel-install $(FW_DIR)/$(INITRAMFS) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfsarchive)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfspiggyback)
imageinstall: createinitramfs targethelp
endif
