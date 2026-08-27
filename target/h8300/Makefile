# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=$(LINUX_DIR)/vmlinux
OSTRIP:=-R .reginfo -R .notes -R .note -R .comment -R .mdebug -R .note.gnu.build-id
ifeq ($(ADK_TARGET_KERNEL_UIMAGEBIN),y)
KERNEL:=$(LINUX_DIR)/arch/h8300/boot/uImage.bin
OSTRIP:=
endif
ifeq ($(ADK_TARGET_KERNEL_ZIMAGE),y)
KERNEL:=$(LINUX_DIR)/arch/h8300/boot/zImage
OSTRIP:=
endif
ifeq ($(ADK_TARGET_KERNEL_VMLINUX_SREC),y)
KERNEL:=$(LINUX_DIR)/arch/h8300/boot/vmlinux.srec
endif
ifeq ($(ADK_TARGET_KERNEL_VMLINUX_BIN),y)
KERNEL:=$(LINUX_DIR)/arch/h8300/boot/vmlinux.bin
OSTRIP:=
endif

QEMU_ARGS:=${ADK_QEMU_ARGS}
ifeq ($(ADK_TARGET_SYSTEM_QEMU_H8300),y)
QEMU_ARGS+=-M edosk2674 -append "console=ttySC2,38400"
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
ifeq ($(ADK_TARGET_SIM),y)
	@echo "Run the simulator via:"
	@echo '$(TARGET_CROSS)gdb $(FW_DIR)/$(TARGET_KERNEL)'
	@echo 'gdb> target sim'
	@echo 'gdb> sim intmode 1'
	@echo 'gdb> sim sci net 12345'
	@echo 'gdb> load'
	@echo 'start telnet localhost 12345 in a second shell'
	@echo 'gdb> run earlyprintk=h8300-sim console=ttySC0'
endif
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSUSERTARBALL)"
endif
ifeq ($(ADK_TARGET_FS),squashfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS image is: $(FW_DIR)/$(ROOTFSSQUASHFS)"
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following options:"
	@echo 'qemu-system-h8300 $(QEMU_ARGS) -nographic -kernel $(FW_DIR)/$(TARGET_KERNEL) -pflash $(FW_DIR)/$(ROOTFSSQUASHFS)'
endif
endif

kernel-strip:
ifneq ($(OSTRIP),)
	$(TARGET_CROSS)objcopy $(OSTRIP) -S $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
else
	@cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
endif

kernel-install: kernel-strip
	@cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(TARGET_KERNEL)
ifeq ($(ADK_TARGET_FS),squashfs)
	env PATH=$(HOST_PATH) qemu-img create -f raw $(FW_DIR)/$(ROOTFSSQUASHFS) 4M
	dd conv=notrunc if=$(BUILD_DIR)/root.squashfs of=$(FW_DIR)/$(ROOTFSSQUASHFS)
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
