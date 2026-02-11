# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		opensbi
PKG_VERSION:=		1.8.1
PKG_RELEASE:=		1
PKG_HASH:=		fb1ae61a85e966322101acb1c982f84d9eaafc4de7dd474a7d7546d9bb321c6f
PKG_DESCR:=		bootloader for riscv hardware
PKG_SECTION:=		base/boot
PKG_URL:=		https://github.com/riscv-software-src/opensbi
PKG_SITES:=		https://github.com/riscv-software-src/opensbi/archive/refs/tags/
PKG_ARCH_DEPENDS:=	riscv32 riscv64

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,OPENSBI,opensbi,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

MAKE_ENV+=		PLATFORM=generic FW_TEXT_START=0x40000000 FW_OPTIONS=0
CONFIG_STYLE:=		manual

opensbi-install:
		$(CP) $(WRKBUILD)/build/platform/generic/firmware/*.bin \
			$(FW_DIR)

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
