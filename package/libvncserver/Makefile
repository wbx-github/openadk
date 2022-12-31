# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libvncserver
PKG_VERSION:=		0.9.14
PKG_RELEASE:=		1
PKG_HASH:=		83104e4f7e28b02f8bf6b010d69b626fae591f887e949816305daebae527c9a5
PKG_DESCR:=		VNC library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		cmake-host
PKG_SITES:=		https://github.com/LibVNC/libvncserver/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             LibVNCServer-$(PKG_VERSION).tar.gz

WRKDIST=		${WRKDIR}/${PKG_NAME}-LibVNCServer-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBVNCSERVER,libvncserver,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake

libvncserver-install:
	$(INSTALL_DIR) $(IDIR_LIBVNCSERVER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libvncserver*.so* \
		$(IDIR_LIBVNCSERVER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libvncclient*.so* \
		$(IDIR_LIBVNCSERVER)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
