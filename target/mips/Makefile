# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=$(LINUX_DIR)/$(ADK_TARGET_KERNEL)
ifeq ($(ADK_TARGET_KERNEL_UIMAGE),y)
KERNEL:=$(LINUX_DIR)/arch/mips/boot/uImage
endif

OSTRIP:=-R .reginfo -R .notes -R .note -R .comment -R .mdebug -R .note.gnu.build-id

QEMU_ARGS:=-M malta
QEMU_ARGS+=${ADK_QEMU_ARGS}
QEMU_ARGS+=-device e1000,netdev=adk0 -netdev user,id=adk0

ifeq ($(ADK_TARGET_CPU_MIPS_MIPS32R6),y)
QEMU_ARGS+=-cpu mips32r6-generic
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
ifeq ($(ADK_TARGET_SYSTEM_MIKROTIK_RB532),y)
	@echo "Use following command to install it on CF card:"
	@echo "sudo ./scripts/install-rb532.sh /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo 'Or boot your Routerboard via NFS and'
	@echo 'then install kernel and filesystem via:'
	@echo 'adkinstall -c -a ${ROOTFSTARBALL}'
endif
ifeq ($(ADK_TARGET_SYSTEM_IMGTEC_CI20),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh $(ADK_TARGET_SYSTEM) /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
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
ifeq ($(ADK_TARGET_FS),usb)
targethelp:
	@echo 'The root tarball is: ${FW_DIR}/${ROOTFSTARBALL}'
endif
ifeq ($(ADK_TARGET_FS),genimage)
targethelp:
	@echo "The disk image is: $(FW_DIR)/disk.img"
ifeq ($(ADK_TARGET_QEMU),y)
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} $(FW_DIR)/disk.img'
else
	@echo "Use following command to install it on SD card:"
	@echo 'sudo dd if=$(FW_DIR)/disk.img of=/dev/sdX bs=2048k'
endif
endif
ifeq ($(ADK_TARGET_FS),ubifs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The UBI image is: ${FW_DIR}/${ROOTFSUBIFS}'
endif

# image creation and kernel install
kernel-strip:
ifeq ($(ADK_TARGET_KERNEL_UIMAGE),)
	$(TARGET_CROSS)objcopy $(OSTRIP) -S $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
else
	@cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
endif

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
ifeq ($(ADK_TARGET_FS),nfsroot)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),ubifs)
imageinstall: $(FW_DIR)/$(ROOTFSUBIFS) targethelp
endif
