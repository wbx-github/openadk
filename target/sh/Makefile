# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

ifeq ($(ADK_TARGET_SYSTEM_NUMATO_MIMASV2)$(ADK_TARGET_SYSTEM_QEMU_J2),y)
KERNEL:=$(LINUX_DIR)/vmlinux
else
KERNEL:=$(LINUX_DIR)/arch/sh/boot/zImage
endif
OSTRIP:=-R .reginfo -R .notes -R .note -R .comment -R .mdebug -R .note.gnu.build-id

ifeq ($(ADK_TARGET_SYSTEM_QEMU_J2),y)
QEMU:=qemu-system-sh4eb
QEMU_ARGS:=-M j2
QEMU_ARGS+=-nographic
endif

ifeq ($(ADK_TARGET_SYSTEM_QEMU_SH),y)
ifeq ($(ADK_TARGET_BIG_ENDIAN),y)
QEMU:=qemu-system-sh4eb
else
QEMU:=qemu-system-sh4
endif
QEMU_ARGS:=-M r2d
QEMU_ARGS+=${ADK_QEMU_ARGS}
QEMU_ARGS+=-monitor null
QEMU_ARGS+=-net user -net nic,model=rtl8139
ifeq ($(ADK_TARGET_QEMU_WITH_GRAPHIC),)
QEMU_ARGS+=-serial null -serial stdio
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
	@echo '${QEMU} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) qemu-${ADK_TARGET_CPU_ARCH}.img'
endif
endif
ifeq ($(ADK_TARGET_FS),initramfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The initramfs image is: ${FW_DIR}/${INITRAMFS}'
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo '${QEMU} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) -initrd ${FW_DIR}/${INITRAMFS}'
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
	@echo '${QEMU} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
endif
endif

# image creation and kernel install
kernel-strip:
ifeq ($(ADK_TARGET_SYSTEM_NUMATO_MIMASV2)$(ADK_TARGET_SYSTEM_QEMU_J2),y)
	$(TARGET_CROSS)objcopy $(OSTRIP) -S $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
else
	@cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
endif

kernel-install: kernel-strip
	@cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/${TARGET_KERNEL}

dtb-install:
ifeq ($(ADK_TARGET_SYSTEM_NUMATO_MIMASV2),y)
	PATH='$(HOST_PATH)' dtc -O dtb -o $(FW_DIR)/dt.dtb \
		$(LINUX_DIR)/arch/sh/boot/dts/j2_mimas_v2.dts
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
imageinstall: dtb-install createinitramfs targethelp
endif
