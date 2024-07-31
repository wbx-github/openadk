# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/kernel-build.mk
include $(ADK_TOPDIR)/mk/image.mk

KERNEL:=$(LINUX_DIR)/$(ADK_TARGET_KERNEL)
ifeq ($(ADK_TARGET_KERNEL_ZIMAGE),y)
KERNEL:=$(LINUX_DIR)/arch/arm/boot/zImage
endif
ifeq ($(ADK_TARGET_KERNEL_UIMAGE),y)
KERNEL:=$(LINUX_DIR)/arch/arm/boot/uImage
endif
ifeq ($(ADK_TARGET_KERNEL_XIPIMAGE),y)
KERNEL:=$(LINUX_DIR)/arch/arm/boot/xipImage
endif
ifeq ($(ADK_TARGET_KERNEL_IMAGE),y)
KERNEL:=$(LINUX_DIR)/arch/arm/boot/Image
endif

QEMU_ARGS:=${ADK_QEMU_ARGS}
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_XILINX_ZYNQ),y)
QEMU_ARGS+=-M xilinx-zynq-a9 -dtb $(FW_DIR)/zynq-zc702.dtb -serial null -serial mon:stdio
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_SPITZ),y)
QEMU_ARGS+=-M spitz
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_TERRIER),y)
QEMU_ARGS+=-M terrier
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_REALVIEW_EB_MPCORE),y)
QEMU_ARGS+=-M realview-eb-mpcore -net user -net nic -dtb $(FW_DIR)/arm-realview-eb-11mp-ctrevb.dtb
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VERSATILEPB),y)
QEMU_ARGS+=-M versatilepb -m 256 -net user -net nic,model=smc91c111 -dtb $(FW_DIR)/versatile-pb.dtb
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VEXPRESS_A9),y)
QEMU_ARGS+=-M vexpress-a9 -cpu cortex-a9 -m 256 -net user -net nic,model=lan9118 -dtb $(FW_DIR)/vexpress-v2p-ca9.dtb
ifeq ($(ADK_TARGET_ROOTFS_ARCHIVE),y)
QEMU_ARGS+=-drive file=qemu-arm.img,if=sd,format=raw
endif
endif
ifeq ($(ADK_TARGET_QEMU_WITH_VIRTIO),y)
QEMU_ARGS+=-drive file=qemu-${ADK_TARGET_CPU_ARCH}.img,if=virtio,index=0 -net nic,model=virtio -net user
endif

# target helper text
ifeq ($(ADK_TARGET_FS),archive)
targethelp:
	@echo "#################################################"
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSTARBALL)"
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VEXPRESS_A9)$(ADK_TARGET_SYSTEM_QEMU_ARM_VERSATILEPB)$(ADK_TARGET_SYSTEM_QEMU_ARM_TERRIER)$(ADK_TARGET_SYSTEM_QEMU_ARM_SPITZ),y)
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "Use following command to create a QEMU Image:"
	@echo "./scripts/create.sh qemu-${ADK_TARGET_CPU_ARCH}.img $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Start qemu with following options:"
	@echo 'qemu-system-${ADK_TARGET_CPU_ARCH} ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) qemu-${ADK_TARGET_CPU_ARCH}.img'
endif
ifeq ($(ADK_TARGET_BOARD_BCM28XX)$(ADK_TARGET_SYSTEM_SOLIDRUN_IMX6)$(ADK_TARGET_SYSTEM_SOLIDRUN_CLEARFOG),y)
ifeq ($(ADK_RUNTIME_DATA_PARTITION),y)
	@echo "Use following command to install with a writable data partition"
	@echo "sudo ./scripts/install.sh -d 256 $(ADK_TARGET_SYSTEM) /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "If you want to update a card without loosing existing data on the writable partition use:"
	@echo "sudo ./scripts/install.sh -k -d 256 $(ADK_TARGET_SYSTEM) /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "In both cases the cfgfs partition is _not_ removed!"
else
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh $(ADK_TARGET_SYSTEM) /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
endif
endif
ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_WEGA),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh phytec-wega /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Use following command to install with a writable data partition"
	@echo "sudo ./scripts/install.sh -d 256 phytec-wega /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo
	@echo "To boot from SD card do following in barebox bootloader:"
	@echo "mount /dev/mmc0.0 /mnt"
	@echo "bootm -o /mnt/am335x-wega-rdk.dtb /mnt/kernel"
	@echo
endif
ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_IMX6),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh phytec-imx6 /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo
endif
ifeq ($(ADK_TARGET_SYSTEM_BEAGEBONE_BLACK),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh beaglebone-black /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo
endif
ifeq ($(ADK_TARGET_SYSTEM_BANANA_PRO),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh banana-pro /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Use following command to install with a writable data partition"
	@echo "sudo ./scripts/install.sh -d 256 banana-pro /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
endif
ifeq ($(ADK_TARGET_SYSTEM_BANANA_P2_ZERO),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh banana-pro-zero /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Use following command to install with a writable data partition"
	@echo "sudo ./scripts/install.sh -d 256 banana-pro-zero /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
endif
ifeq ($(ADK_TARGET_SYSTEM_ORANGE_PI0),y)
	@echo "Use following command to install it on SD card:"
	@echo "sudo ./scripts/install.sh orange-pi0 /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
	@echo "Use following command to install with a writable data partition"
	@echo "sudo ./scripts/install.sh -d 256 orange-pi0 /dev/sdX $(FW_DIR)/$(ROOTFSTARBALL)"
endif
endif
ifeq ($(ADK_TARGET_FS),initramfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo 'The initramfs image is: ${FW_DIR}/${INITRAMFS}'
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following command line:"
	@echo 'qemu-system-arm ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL) -initrd ${FW_DIR}/${INITRAMFS}'
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
	@echo 'qemu-system-arm ${QEMU_ARGS} -kernel $(FW_DIR)/$(TARGET_KERNEL)'
endif
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS tarball is: $(FW_DIR)/$(ROOTFSUSERTARBALL)"
ifeq ($(ADK_TARGET_SYSTEM_LINKSYS_NSLU2),y)
	@echo "Use following in RedBoot bootloader:"
	@echo "RedBoot> ip_address -l <localip> -h <serverip>; load -r -v -b 0x01d00000 ${TARGET_KERNEL}; exec 0x01d00000"
endif
endif
ifeq ($(ADK_TARGET_FS),squashfs)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS image is: $(FW_DIR)/$(ROOTFSSQUASHFS)"
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following options:"
	@echo 'qemu-system-arm $(QEMU_ARGS) -nographic -kernel $(FW_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(ROOTFSSQUASHFS)'
endif
endif
ifeq ($(ADK_TARGET_FS),jffs2)
targethelp:
	@echo 'The kernel file is: $(FW_DIR)/${TARGET_KERNEL}'
	@echo "The RootFS image is: $(FW_DIR)/$(ROOTFSJFFS2)"
ifeq ($(ADK_TARGET_QEMU),y)
	@echo "Start qemu with following options:"
	@echo 'qemu-system-arm $(QEMU_ARGS) -nographic -kernel $(FW_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(ROOTFSJFFS2)'
endif
endif
ifeq ($(ADK_TARGET_FS),genimage)
targethelp:
	@echo "The disk image is: $(FW_DIR)/sdcard.img"
	@echo "Use following command to install it on SD card:"
	@echo 'sudo dd if=$(FW_DIR)/sdcard.img of=/dev/sdX bs=32M'
endif

kernel-strip:
ifeq ($(ADK_TARGET_KERNEL_GIT_REPO_NAME),rpi)
	@echo adding DT trailer to kernel $(MAKE_TRACE)
	PATH='$(HOST_PATH)' perl $(LINUX_DIR)/scripts/mkknlimg $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL) $(MAKE_TRACE)
else
	@cp $(KERNEL) $(BUILD_DIR)/$(TARGET_KERNEL)
endif

kernel-install: kernel-strip
	@cp $(BUILD_DIR)/$(TARGET_KERNEL) $(FW_DIR)/$(TARGET_KERNEL)
ifeq ($(ADK_TARGET_FS),squashfs)
	env PATH=$(HOST_PATH) qemu-img create -f raw $(FW_DIR)/$(ROOTFSSQUASHFS) $(ADK_TARGET_MTD_SIZE)
	dd conv=notrunc if=$(BUILD_DIR)/root.squashfs of=$(FW_DIR)/$(ROOTFSSQUASHFS)
endif

ifeq ($(ADK_TARGET_LINUX_KERNEL_VERSION_6_6)$(ADK_TARGET_LINUX_KERNEL_VERSION_6_9)$(ADK_TARGET_LINUX_KERNEL_VERSION_GIT),y)
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VERSATILEPB),y)
VENDOR:=arm/
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_REALVIEW_EB_MPCORE),y)
VENDOR:=arm/
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VEXPRESS_A9),y)
VENDOR:=arm/
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_XILINX_ZYNQ),y)
VENDOR:=xilinx/
endif
ifeq ($(ADK_TARGET_SYSTEM_ST_STM32F746G),y)
VENDOR:=st/
endif
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_IMX6),y)
VENDOR:=nxp/imx/
endif
ifeq ($(ADK_TARGET_SYSTEM_BEAGLEBONE_BLACK),y)
VENDOR:=ti/omap/
endif
endif

dtb-install:
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_XILINX_ZYNQ),y)
	${KERNEL_MAKE} dtbs $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VEXPRESS_A9),y)
	${KERNEL_MAKE} $(VENDOR)vexpress-v2p-ca9.dtb $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_REALVIEW_EB_MPCORE),y)
	${KERNEL_MAKE} $(VENDOR)arm-realview-eb-11mp-ctrevb.dtb $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VERSATILEPB),y)
	${KERNEL_MAKE} $(VENDOR)versatile-pb.dtb $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_WEGA),y)
	${KERNEL_MAKE} am335x-wega-rdk.dtb $(MAKE_TRACE)
	cp $(LINUX_DIR)/arch/arm/boot/dts/am335x-wega-rdk.dtb ${TARGET_DIR}/boot
endif
ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_IMX6),y)
	${KERNEL_MAKE} imx6q-phytec-pbab01.dtb $(MAKE_TRACE)
	cp $(LINUX_DIR)/arch/arm/boot/dts/imx6q-phytec-pbab01.dtb ${TARGET_DIR}/boot
endif
ifeq ($(ADK_TARGET_SYSTEM_BEAGLEBONE_BLACK),y)
	${KERNEL_MAKE} $(VENDOR)am335x-boneblack.dtb $(MAKE_TRACE)
	cp $(LINUX_DIR)/arch/arm/boot/dts/$(VENDOR)am335x-boneblack.dtb ${TARGET_DIR}/boot
endif
ifeq ($(ADK_TARGET_BOARD_BCM28XX),y)
	${KERNEL_MAKE} dtbs $(MAKE_TRACE)
	mkdir -p $(FW_DIR)/overlays
	for x in $(LINUX_DIR)/arch/arm/boot/dts/overlays/*.dtbo; do \
		[[ -e "$$x" ]] && cp $(LINUX_DIR)/arch/arm/boot/dts/overlays/*.dtbo $(FW_DIR)/overlays; \
		break; \
	done
	for x in $(LINUX_DIR)/arch/arm/boot/dts/overlays/*.dtb; do \
		[[ -e "$$x" ]] && cp $(LINUX_DIR)/arch/arm/boot/dts/overlays/*.dtb $(FW_DIR)/overlays; \
		break; \
	done
endif
ifeq ($(ADK_TARGET_SYSTEM_BANANA_PRO),y)
	${KERNEL_MAKE} sun7i-a20-bananapro.dtb $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_ORANGE_PI0),y)
	${KERNEL_MAKE} sun8i-h2-plus-orangepi-zero.dtb $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_BANANA_P2_ZERO),y)
	${KERNEL_MAKE} sun8i-h2-plus-bananapi-m2-zero.dtb $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_IMX6),y)
	${KERNEL_MAKE} $(VENDOR)imx6q-cubox-i.dtb $(VENDOR)imx6dl-cubox-i.dtb \
		$(VENDOR)imx6dl-hummingboard.dtb $(VENDOR)imx6q-hummingboard.dtb $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_CLEARFOG),y)
	${KERNEL_MAKE} armada-388-clearfog.dtb $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_ST_STM32F429),y)
	${KERNEL_MAKE} dtbs $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_ST_STM32F769),y)
	${KERNEL_MAKE} dtbs $(MAKE_TRACE)
endif
ifeq ($(ADK_TARGET_SYSTEM_ST_STM32F746G),y)
	${KERNEL_MAKE} $(VENDOR)stm32f746-disco.dtb $(MAKE_TRACE)
endif
	for x in $(LINUX_DIR)/arch/arm/boot/dts/$(VENDOR)*.dtb; do \
		[[ -e "$$x" ]] && cp $(LINUX_DIR)/arch/arm/boot/dts/$(VENDOR)*.dtb $(FW_DIR); \
		break; \
	done

# filesystem specific targets
ifeq ($(ADK_TARGET_FS),archive)
imageinstall: dtb-install $(FW_DIR)/$(ROOTFSTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfs)
imageinstall: kernel-install dtb-install $(FW_DIR)/$(INITRAMFS) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfsarchive)
imageinstall: kernel-install dtb-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),initramfspiggyback)
imageinstall: dtb-install createinitramfs targethelp
endif
ifeq (${ADK_TARGET_FS},genimage)
imageinstall: dtb-install $(FW_DIR)/$(GENIMAGE) targethelp
endif
ifeq ($(ADK_TARGET_FS),nfsroot)
imageinstall: kernel-install $(FW_DIR)/$(ROOTFSUSERTARBALL) targethelp
endif
ifeq ($(ADK_TARGET_FS),squashfs)
imageinstall: $(BUILD_DIR)/root.squashfs kernel-install dtb-install targethelp
endif
ifeq ($(ADK_TARGET_FS),jffs2)
imageinstall: kernel-install dtb-install $(FW_DIR)/$(ROOTFSJFFS2) targethelp
endif
ifeq ($(ADK_TARGET_FS),usb)
imageinstall: $(FW_DIR)/$(ROOTFSTARBALL) targethelp
endif
