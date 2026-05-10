# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		openjpeg
PKG_VERSION:=		2.5.4
PKG_RELEASE:=		1
PKG_HASH:=		a695fbe19c0165f295a8531b1e4e855cd94d0875d2f88ec4b61080677e27188a
PKG_DESCR:=		jpeg library
PKG_SECTION:=		libs/image
PKG_URL:=		https://www.openjpeg.org/
PKG_SITES:=		https://github.com/uclouvain/openjpeg/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,OPENJPEG,openjpeg,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake

openjpeg-install:
	$(INSTALL_DIR) $(IDIR_OPENJPEG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libopenjp2.so* \
		$(IDIR_OPENJPEG)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
