# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tigervnc
PKG_VERSION:=		1.16.2
PKG_RELEASE:=		1
PKG_HASH:=		b107c0c8b8a962594281690366c24186e95c2ea4a169acbc0076aa62ed01f467
PKG_DESCR:=		x11 vnc server
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		libfltk libjpeg-turbo libsm libice libxtst libx11 zlib
PKG_DEPENDS+=		libxext libxdamage
PKG_BUILDDEP:=		fltk libjpeg-turbo libSM libICE libXtst libX11 zlib
PKG_BUILDDEP+=		libXext libXdamage cmake-host
PKG_NEEDS:=		c++
PKG_URL:=		http://tigervnc.org
PKG_SITES:=		https://github.com/TigerVNC/tigervnc/archive/

# not comaptible with fltk 1.4.x
PKG_CFLINE_TIGERVNC:=	depends on ADK_BROKEN

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TIGERVNC,tigervnc,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		cmake

tigervnc-install:
	$(INSTALL_DIR) $(IDIR_TIGERVNC)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_TIGERVNC)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
