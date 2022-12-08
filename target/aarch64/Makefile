# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=${LINUX_DIR}/arch/arm64/boot/Image

QEMU_ARGS:=${ADK_QEMU_ARGS}
QEMU_ARGS+=-M virt -cpu cortex-a57 -smp 1
ifeq ($(ADK_TARGET_QEMU_WITH_VIRTIO),y)
QEMU_ARGS+=-netdev user,id=eth0 -device virtio-net-device,netdev=eth0
endif
ifeq ($(ADK_TARGET_FS),archive)
QEMU_ARGS+=-device virtio-blk-device,drive=vda -drive file=qemu-${ADK_TARGET_CPU_ARCH}.img,if=none,id=vda,format=raw
endif

# target helper text
ifeq ($(ADK_TARGET_FS),archive)
targethelp:
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSTARBALL)"
ifeq ($(ADK_TARGET_BOARD_BCM28XX),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh $(ADK_TARGET_SYSTEM) /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
endif
ifeq ($(ADK_TARGET_SYSTEM_ROCKPI4_PLUS),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh $(ADK_TARGET_SYSTEM) /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
endif
ifeq ($(ADK_TARGET_QEMU),y)
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "Use following command to create a QEMU Image:"
	@echo "./scripts/create.sh qemu-${ADK_TARGET_CPU_ARCH}.img $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Start qemu with following options:"
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
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
ifeq ($(ADK_TARGET_FS),genimage)
targethelp:
	@echo "The disk image is: $(FW_DIR)/sdcard.img"
	@echo "Use following command to install it on SD card:"
	@echo 'sudo dd if=$(FW_DIR)/sdcard.img of=/dev/sdX bs=2048k'
endif

kernel-strip:
	@cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)

kernel-install: kernel-strip
	@cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(TARGET_KERNEL)

dtb-install:
ifeq ($(ADK_TARGET_BOARD_BCM28XX),y)
	${KERNEL_MAKE} dtbs $(MAKE_TRACE)
	mkdir -p $(FW_DIR)/overlays
	for x in $(LINUX_DIR)/arch/arm64/boot/dts/overlays/*.dtbo; do \
		[[ -e "$$x" ]] && cp $(LINUX_DIR)/arch/arm64/boot/dts/overlays/*.dtbo $(FW_DIR)/overlays; \
		break; \
	done
	for x in $(LINUX_DIR)/arch/arm64/boot/dts/broadcom/*.dtb; do \
		[[ -e "$$x" ]] && cp $(LINUX_DIR)/arch/arm64/boot/dts/broadcom/*.dtb $(FW_DIR); \
		break; \
	done
endif
ifeq ($(ADK_TARGET_SYSTEM_ROCKPI4_PLUS),y)
	${KERNEL_MAKE} rockchip/rk3399-rock-pi-4c-plus.dtb $(MAKE_TRACE)
endif
	for x in $(LINUX_DIR)/arch/arm64/boot/dts/*/*.dtb; do \
		[[ -e "$$x" ]] && cp $(LINUX_DIR)/arch/arm64/boot/dts/*/*.dtb $(FW_DIR); \
		break; \
	done

# filesystem specific targets
ifeq ($(ADK_TARGET_FS),archive)
imageinstall: dtb-install $(FW_DIR)/$(ROOTFSTARBALL) targethelp
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
ifeq ($(ADK_TARGET_FS),genimage)
imageinstall: dtb-install $(FW_DIR)/$(GENIMAGE) targethelp
endif
