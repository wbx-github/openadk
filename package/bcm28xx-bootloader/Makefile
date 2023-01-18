# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		bcm28xx-bootloader
# not cloned, local src directory used
PKG_VERSION:=		827fdd073638fa7b7292d1148fe0af7465111eae
PKG_RELEASE:=		1
PKG_DESCR:=		bootloader for bcm28xx
PKG_SECTION:=		base/boot
PKG_URL:=		https://github.com/raspberrypi/firmware
PKG_SITES:=		https://github.com/raspberrypi/firmware.git

PKG_SYSTEM_DEPENDS:=	raspberry-pi raspberry-pi0 raspberry-pi2 raspberry-pi3 raspberry-pi3-64 raspberry-pi4 raspberry-pi4-64

PKG_CHOICES_BCM28XX_BOOTLOADER:=	DEFAULT EXTRA CUTDOWN
PKGCD_DEFAULT:=		default bootloader
PKGCD_EXTRA:=		bootloader with extra features and codecs
PKGCD_CUTDOWN:=		cut down bootloader

PKG_SUBPKGS:=		BCM28XX_BOOTLOADER BCM28XX_DEBUGTOOL
PKGSD_BCM28XX_DEBUGTOOL:=	bcm28xx debugtool (vcdbg)
PKGSC_BCM28XX_DEBUGTOOL:=	sys/hw
PKGSS_BCM28XX_DEBUGTOOL:=	bcm28xx-vc-debug bcm28xx-vc-libs

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BCM28XX_BOOTLOADER,bcm28xx-bootloader,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,BCM28XX_DEBUGTOOL,bcm28xx-debugtool,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKGSC_BCM28XX_DEBUGTOOL)))

CONFIG_STYLE:=          manual
BUILD_STYLE:=           manual
INSTALL_STYLE:=         manual

do-install:
	$(INSTALL_DIR) $(IDIR_BCM28XX_BOOTLOADER)/boot
	$(CP) $(WRKBUILD)/boot/bootcode.bin $(IDIR_BCM28XX_BOOTLOADER)/boot/
ifeq ($(ADK_RUNTIME_VERBOSE_KERNEL_SERIAL_ONLY),y)
	printf "console=serial0,115200 root=/dev/mmcblk0p2 rootfstype=ext4 rootwait" > \
			$(IDIR_BCM28XX_BOOTLOADER)/boot/cmdline.txt
endif
ifeq ($(ADK_RUNTIME_VERBOSE_KERNEL_VGA_ONLY),y)
	printf "console=tty0 root=/dev/mmcblk0p2 rootfstype=ext4 rootwait" > \
			$(IDIR_BCM28XX_BOOTLOADER)/boot/cmdline.txt
endif
	printf "kernel=kernel\n" > $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
	printf "dtparam=audio,i2s,spi,i2c\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
ifeq ($(ADK_PACKAGE_BCM28XX_BOOTLOADER_DEFAULT),y)
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI4)$(ADK_TARGET_SYSTEM_RASPBERRY_PI4_64),y)
	$(CP) $(WRKBUILD)/boot/{start4.elf,fixup4.dat} $(IDIR_BCM28XX_BOOTLOADER)/boot/
	printf "start_file=start4.elf\n" >> $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
	printf "fixup_file=fixup4.dat\n" >> $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
else
	$(CP) $(WRKBUILD)/boot/{start.elf,fixup.dat} $(IDIR_BCM28XX_BOOTLOADER)/boot/
	printf "start_file=start.elf\n" >> $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
	printf "fixup_file=fixup.dat\n" >> $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
endif
ifeq ($(ADK_PACKAGE_BCM28XX_BOOTLOADER_EXTRA),y)
	$(CP) $(WRKBUILD)/boot/{start_x.elf,fixup_x.dat} $(IDIR_BCM28XX_BOOTLOADER)/boot/
	printf "start_file=start_x.elf\n" >> $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
	printf "fixup_file=fixup_x.dat\n" >> $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifeq ($(ADK_PACKAGE_BCM28XX_BOOTLOADER_CUTDOWN),y)
	$(CP) $(WRKBUILD)/boot/{start_cd.elf,fixup_cd.dat} $(IDIR_BCM28XX_BOOTLOADER)/boot/
	printf "start_file=start_cd.elf\n" >> $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
	printf "fixup_file=fixup_cd.dat\n" >> $(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
	printf "gpu_mem=$(ADK_TARGET_GPU_MEM)\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
ifneq ($(ADK_TARGET_HARDWARE_HIFIBERRY_AMP),)
	printf "dtoverlay=hifiberry-amp\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifneq ($(ADK_TARGET_HARDWARE_HIFIBERRY_DAC),)
	printf "dtoverlay=hifiberry-dac\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifneq ($(ADK_TARGET_HARDWARE_HIFIBERRY_DACPLUS),)
	printf "dtoverlay=hifiberry-dacplus\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifneq ($(ADK_TARGET_HARDWARE_HIFIBERRY_DIGI),)
	printf "dtoverlay=hifiberry-digi\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifneq ($(ADK_TARGET_HARDWARE_RPI_DAC),)
	printf "dtoverlay=rpi-dac\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifneq ($(ADK_TARGET_HARDWARE_IQAUDIO_DAC),)
	printf "dtoverlay=iqaudio-dac\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifneq ($(ADK_TARGET_HARDWARE_RPI_PROTO),)
	printf "dtoverlay=rpi-proto\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifeq ($(ADK_TARGET_HARDWARE_RPI3_NO_WIFI),y)
	printf "dtoverlay=pi3-disable-wifi\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifeq ($(ADK_TARGET_HARDWARE_RPI3_NO_BT),y)
	printf "dtoverlay=pi3-disable-bt\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifeq ($(ADK_TARGET_HARDWARE_RPI3_SERIAL),y)
	printf "enable_uart=1\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI4),y)
	printf "enable_uart=1\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI3_64)$(ADK_TARGET_SYSTEM_RASPBERRY_PI4_64),y)
	printf "arm_control=0x200\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
	printf "enable_uart=1\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifneq ($(ADK_RUNTIME_MPEG2_KEY),)
	printf "decode_MPG2=$(ADK_RUNTIME_MPEG2_KEY)\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifneq ($(ADK_RUNTIME_VC1_KEY),)
	printf "decode_WVC1=$(ADK_RUNTIME_VC1_KEY)\n" >> \
		$(IDIR_BCM28XX_BOOTLOADER)/boot/config.txt
endif
ifeq ($(ADK_PACKAGE_BCM28XX_DEBUGTOOL),y)
	$(INSTALL_DIR) $(IDIR_BCM28XX_DEBUGTOOL)/usr/bin
	$(INSTALL_BIN) ./files/vcdbg \
		$(IDIR_BCM28XX_DEBUGTOOL)/usr/bin
endif

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
