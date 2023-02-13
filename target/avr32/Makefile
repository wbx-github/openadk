# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=$(LINUX_DIR)/arch/avr32/boot/images/uImage

# target helper text
ifeq ($(ADK_TARGET_FS),archive)
targethelp:
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh $(ADK_TARGET_SYSTEM) /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "U-Boot commands:"
	@echo "set bootargs 'console=ttyS0 root=/dev/mmcblk0p1 ro rootwait'"
	@echo "ext2load mmc 0:1 0x10300000 /boot/kernel; bootm 0x10300000"
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The nfs root tarball is: ${FW_DIR}/${ROOTFSUSERTARBALL}'
endif

kernel-strip:
	cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)

kernel-install: kernel-strip
	cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(TARGET_KERNEL)

# filesystem specific targets
ifeq ($(ADK_TARGET_FS),archive)
imageinstall: $(FW_DIR)/$(ROOTFSTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
