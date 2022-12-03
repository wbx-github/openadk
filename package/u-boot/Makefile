# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		u-boot
PKG_VERSION:=		2022.10
PKG_RELEASE:=		1
PKG_HASH:=		50b4482a505bc281ba8470c399a3c26e145e29b23500bc35c50debd7fa46bdf8
PKG_DESCR:=		portable bootloader
PKG_SECTION:=		base/boot
HOST_BUILDDEP:=		libressl-host dtc-host
PKG_BUILDDEP:=		python3-host swig-host u-boot-host
PKG_URL:=		http://www.denx.de/wiki/U-Boot	
PKG_SITES:=		ftp://ftp.denx.de/pub/u-boot/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.bz2

PKG_SYSTEM_DEPENDS:=	beaglebone-black orange-pi0 raspberry-pi raspberry-pi2 raspberry-pi3 banana-pro solidrun-imx6 solidrun-clearfog raspberry-pi3-64 raspberry-pi3p raspberry-pi3p-64 phytec-imx6 pcduino-3b imgtec-ci20 st-stm32f746g

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,U_BOOT,u-boot,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,U_BOOT,u-boot,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

UBOOT:=			u-boot.bin
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_CLEARFOG),y)
CONFIG:=		clearfog_defconfig
UBOOT:=			u-boot-spl.kwb
endif
ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_IMX6),y)
CONFIG:=		pcm058_defconfig
UBOOT:=			u-boot.img
endif
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_IMX6),y)
CONFIG:=		mx6cuboxi_defconfig
UBOOT:=			u-boot.img
endif
ifeq ($(ADK_TARGET_SYSTEM_PCDUINO_3B),y)
CONFIG:=		Linksprite_pcDuino3_defconfig
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI),y)
CONFIG:=		rpi_defconfig
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI2),y)
CONFIG:=		rpi_defconfig
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI3),y)
CONFIG:=		rpi_3_32b_defconfig
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI3P),y)
CONFIG:=		rpi_3_32b_defconfig
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI3_64),y)
CONFIG:=		rpi_3_defconfig
endif
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI3P_64),y)
CONFIG:=		rpi_3_defconfig
endif
ifeq ($(ADK_TARGET_SYSTEM_BANANA_PRO),y)
CONFIG:=		Bananapro_defconfig
UBOOT:=			u-boot-sunxi-with-spl.bin
endif
ifeq ($(ADK_TARGET_SYSTEM_ORANGE_PI0),y)
CONFIG:=		orangepi_zero_defconfig
UBOOT:=			u-boot-sunxi-with-spl.bin
endif
ifeq ($(ADK_TARGET_SYSTEM_BEAGLEBONE_BLACK),y)
CONFIG:=		am335x_evm_defconfig
UBOOT:=			u-boot.img
endif
ifeq ($(ADK_TARGET_SYSTEM_IMGTEC_CI20),y)
CONFIG:=		ci20_mmc_defconfig
UBOOT:=			u-boot-dtb.img
endif
ifeq ($(ADK_TARGET_SYSTEM_ST_STM32F746G),y)
CONFIG:=		stm32f746-disco_defconfig
UBOOT:=			u-boot-dtb.bin
endif

HOST_MAKE_FLAGS+=	HOSTCFLAGS="$(HOST_CPPFLAGS) $(HOST_CFLAGS)" \
			HOSTLDFLAGS="$(HOST_LDFLAGS) -ldl"
HOST_STYLE:=		manual
CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

host-build:
	(cd $(WRKBUILD) && env $(HOST_MAKE_ENV) $(MAKE) -f $(MAKE_FILE) \
		$(HOST_MAKE_FLAGS) sandbox_defconfig )
	(cd $(WRKBUILD) && env $(HOST_MAKE_ENV) $(MAKE) -f $(MAKE_FILE) \
		$(HOST_MAKE_FLAGS) tools $(MAKE_TRACE) )

u-boot-hostinstall:
	$(INSTALL_BIN) $(WRKBUILD)/tools/mk{,env}image \
		$(STAGING_HOST_DIR)/usr/bin

do-configure:
	(cd $(WRKBUILD) && $(MAKE) $(CONFIG))

do-build:
	(cd $(WRKBUILD) && env \
		V=1 \
		PATH='$(HOST_PATH)' \
		CROSS_COMPILE='$(TARGET_CROSS)' \
		KCFLAGS='-mno-fdpic' \
		$(MAKE))
ifneq ($(OS_FOR_BUILD),Darwin)
	(cd $(WRKBUILD) && env \
		PATH='$(HOST_PATH)' \
		CROSS_COMPILE='$(TARGET_CROSS)' \
		$(MAKE) env)
endif

u-boot-install:
	$(CP) $(WRKBUILD)/$(UBOOT) $(FW_DIR)
ifeq ($(ADK_TARGET_SYSTEM_IMGTEC_CI20),y)
	$(CP) $(WRKBUILD)/spl/u-boot-spl.bin $(FW_DIR)
endif
	$(INSTALL_DIR) $(IDIR_U_BOOT)/etc
	$(CP) ./files/fw_env.config $(IDIR_U_BOOT)/etc
ifneq ($(OS_FOR_BUILD),Darwin)
	$(INSTALL_DIR) $(IDIR_U_BOOT)/usr/bin
	$(INSTALL_BIN) ./files/uboot_print_env $(IDIR_U_BOOT)/usr/bin
	$(INSTALL_BIN) ./files/uboot_set_env $(IDIR_U_BOOT)/usr/bin
endif
ifeq ($(ADK_TARGET_SYSTEM_BANANA_PRO),y)
	$(INSTALL_BIN) ./files/boot.script.bpi $(FW_DIR)
endif
ifeq ($(ADK_TARGET_SYSTEM_ORANGE_PI0),y)
	$(INSTALL_BIN) ./files/boot.script.opi $(FW_DIR)
endif
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_CLEARFOG),y)
	$(INSTALL_BIN) ./files/boot.script.clearfog $(FW_DIR)
endif
ifeq ($(ADK_TARGET_SYSTEM_SOLIDRUN_IMX6),y)
	$(INSTALL_BIN) $(WRKBUILD)/SPL $(FW_DIR)
	$(INSTALL_BIN) ./files/boot.script.imx6 $(FW_DIR)
endif
ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_IMX6),y)
	$(INSTALL_BIN) $(WRKBUILD)/SPL $(FW_DIR)
	$(INSTALL_BIN) ./files/boot.script.phytec $(FW_DIR)
endif
ifeq ($(ADK_TARGET_SYSTEM_BEAGLEBONE_BLACK),y)
	$(CP) ./files/uEnv.txt.bbb $(FW_DIR)/uEnv.txt
	$(INSTALL_BIN) $(WRKBUILD)/MLO $(FW_DIR)
endif

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
