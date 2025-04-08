# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libIDL
PKG_VERSION:=		0.8.14
PKG_RELEASE:=		2
PKG_HASH:=		bca99570f1ab453e11ae627b209561019cde5aaa98f71f43cc6da048d3bc7e72
PKG_DESCR:=		libraries for interface definition language files
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib
PKG_BUILDDEP:=		glib
HOST_BUILDDEP:=		glib-host
PKG_URL:=		http://www.gnome.org/
PKG_SITES:=		http://ftp.gnome.org/pub/GNOME/sources/libIDL/0.8/
PKG_LIBNAME:=		libidl
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBIDL,libidl,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBIDL,libidl,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ENV+=		libIDL_cv_long_long_format=ll

libidl-install:
	$(INSTALL_DIR) $(IDIR_LIBIDL)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libIDL*.so* \
		$(IDIR_LIBIDL)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
