# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=$(LINUX_DIR)/arch/x86/boot/bzImage

QEMU_ARCH:=i386
QEMU_ARGS:=-M pc
QEMU_ARGS+=${ADK_QEMU_ARGS}
QEMU_ARGS+=-net user -net nic,model=e1000

ifeq ($(ADK_PACKAGE_GRUB_EFI_X86),y)
QEMU_ARGS+=-L . -bios bios-x86.bin
endif

ifeq ($(ADK_TARGET_QEMU_WITH_AUDIO),y)
QEMU_ARGS+=-soundhw ac97
endif

ifeq ($(ADK_TARGET_QEMU_WITH_BOOTLOADER),y)
ifeq ($(ADK_TARGET_QEMU_WITHOUT_GRAPHIC),y)
CREATE:=./scripts/create.sh -g -t
else
CREATE:=./scripts/create.sh -g
endif
else
CREATE:=./scripts/create.sh
endif

# target helper text
ifeq ($(ADK_TARGET_FS),archive)
targethelp:
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSTARBALL)"
ifeq ($(ADK_TARGET_QEMU),y)
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "Use following command to create a QEMU Image:"
	@echo "$(CREATE) qemu-${ADK_TARGET_CPU_ARCH}.img $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Start qemu with following options:"
ifeq ($(ADK_TARGET_QEMU_WITH_BOOTLOADER),y)
	@echo 'qemu-system-${QEMU_ARCH} ${QEMU_ARGS} qemu-${ADK_TARGET_CPU_ARCH}.img'
else
	@echo 'qemu-system-${QEMU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) qemu-${ADK_TARGET_CPU_ARCH}.img'
endif
endif
endif
ifeq ($(ADK_TARGET_FS),initramfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The initramfs image is: ${FW_DIR}/${INITRAMFS}'
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-${QEMU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) -initrd ${FW_DIR}/${INITRAMFS}'
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
	@echo 'qemu-system-${QEMU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
endif
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The nfs root tarball is: ${FW_DIR}/${ROOTFSUSERTARBALL}'
endif
ifeq ($(ADK_TARGET_FS),usb)
targethelp:
	@echo 'The root tarball is: ${FW_DIR}/${ROOTFSTARBALL}'
	@echo "To install everything to USB use scripts/install.sh"
endif
ifeq ($(ADK_TARGET_FS),iso)
targethelp:
	@echo 'ISO image is at $<'
endif
ifeq ($(ADK_TARGET_FS),genimage)
targethelp:
	@echo "The disk image is: $(FW_DIR)/disk.img"
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-${QEMU_ARCH} ${QEMU_ARGS} $(FW_DIR)/disk.img'
else
	@echo "Use following command to install it on SD card:"
	@echo 'sudo dd if=$(FW_DIR)/disk.img of=/dev/sdX bs=2048k'
endif
endif

# image creation and kernel install
kernel-strip:
	@cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)

kernel-install: kernel-strip
	@cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/${TARGET_KERNEL}

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
ifeq (${ADK_TARGET_FS},genimage)
imageinstall: ${FW_DIR}/${GENIMAGE} targethelp
endif
ifeq (${ADK_TARGET_FS},iso)
imageinstall: ${FW_DIR}/${ROOTFSISO} targethelp
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),usb)
imageinstall: $(FW_DIR)/$(ROOTFSTARBALL) targethelp
endif
