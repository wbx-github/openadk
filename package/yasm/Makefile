# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		yasm
PKG_VERSION:=		1.3.0
PKG_RELEASE:=		1
PKG_HASH:=		3dce6601b495f5b3d45b59f7d2492a340ee7e84b5beca17e48f862502bd5603f
PKG_DESCR:=		modular assembler
PKG_SECTION:=		dev/lang
PKG_BUILDDEP:=		yasm-host
PKG_SITES:=		https://github.com/yasm/yasm/releases/download/v$(PKG_VERSION)/

PKG_CFLINE_YASM:=	depends on ADK_HOST_ONLY

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,YASM,yasm,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,YASM,yasm,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

yasm-install:
	$(INSTALL_DIR) $(IDIR_YASM)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/yasm $(IDIR_YASM)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
