# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		afboot-stm32
PKG_VERSION:=		3566acd582e5536fb60864281788a30f5527df2d
PKG_RELEASE:=		1
PKG_DESCR:=		bootloader for stm32 devices
PKG_SECTION:=		base/boot
PKG_SITES:=		https://github.com/mcoquelin-stm32/afboot-stm32.git

PKG_SYSTEM_DEPENDS:=	st-stm32f429 st-stm32f769

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AFBOOT_STM32,afboot-stm32,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

afboot-stm32-install:
ifeq ($(ADK_TARGET_SYSTEM_ST_STM32F429),y)
	$(CP) $(WRKBUILD)/stm32f429i-disco.bin $(FW_DIR)
endif
ifeq ($(ADK_TARGET_SYSTEM_ST_STM32F769),y)
	$(CP) $(WRKBUILD)/stm32746g-eval.bin $(FW_DIR)
endif

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
