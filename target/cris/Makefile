# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

ifeq ($(ADK_TARGET_SYSTEM_FOXBOARD_LX832),y)
KERNEL:=$(LINUX_DIR)/arch/cris/boot/zImage
else
KERNEL:=$(LINUX_DIR)/arch/cris/boot/Image
QEMU_ARGS:=-M axis-dev88 -nographic -monitor none
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
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-${ADK_TARGET_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) -initrd ${FW_DIR}/${INITRAMFS}'
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
	@echo 'qemu-system-${ADK_TARGET_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
endif
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSUSERTARBALL)"
	@echo "Use following command to flash the kernel:"
	@echo "cd $(STAGING_HOST_DIR)/usr/bin && sudo ./boot_linux -F -i $(FW_DIR)/${TARGET_KERNEL}"
	@echo Do not forget to set network boot jumper, before you start the foxboard
endif
ifeq ($(ADK_TARGET_FS),squashfs)
targethelp:
	@echo "The image is: $(FW_DIR)/$(ROOTFSSQUASHFS)"
	@echo "Use following command to flash the image:"
	@echo "cd $(STAGING_HOST_DIR)/usr/bin && sudo ./boot_linux -F -i $(FW_DIR)/${ROOTFSSQUASHFS}"
	@echo Do not forget to set network boot jumper, before you start the foxboard
endif
ifeq ($(ADK_TARGET_FS),jffs2)
targethelp:
	@echo "The image is: $(FW_DIR)/$(ROOTFSJFFS2)"
endif

kernel-strip:
	@cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)

kernel-install: kernel-strip
ifeq ($(ADK_TARGET_FS),squashfs)
	$(STAGING_HOST_DIR)/usr/bin/mkfimage $(KERNEL) $(KERNEL).fimage
	cat $(KERNEL).fimage $(BUILD_DIR)/root.squashfs > \
		$(BUILD_DIR)/$(ROOTFSSQUASHFS)
	dd if=$(BUILD_DIR)/$(ROOTFSSQUASHFS) of=$(FW_DIR)/$(ROOTFSSQUASHFS) bs=4194304 conv=sync
else
	$(STAGING_HOST_DIR)/usr/bin/mkfimage $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(TARGET_KERNEL)
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
imageinstall: createinitramfs targethelp
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),squashfs)
imageinstall: $(BUILD_DIR)/root.squashfs kernel-install targethelp
endif
ifeq ($(ADK_TARGET_FS),jffs2)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSJFFS2) targethelp
endif
