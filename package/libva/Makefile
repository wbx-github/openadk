# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libva
PKG_VERSION:=		1.8.2
PKG_RELEASE:=		1
PKG_HASH:=		9ed3e3ddc8f47a715d4c6ec366beb21c83fc4e8a3d4d39a811baff76f0a0cede
PKG_DESCR:=		video acceleration api library
PKG_SECTION:=		libs/video
PKG_BUILDDEP:=		libdrm
PKG_URL:=		https://www.freedesktop.org/wiki/Software/vaapi/
PKG_SITES:=		https://www.freedesktop.org/software/vaapi/releases/libva/
PKG_OPTS:=		dev

# package moved to github, find there a newer version
PKG_CFLINE_LIBVA:=	depends on ADK_BROKEN

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBVA,libva,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--disable-wayland \
			--disable-docs \
			--enable-glx \
			--enable-drm \
			--enable-x11 \
			--with-drivers-path=/usr/lib/va/drivers

libva-install:
	$(INSTALL_DIR) $(IDIR_LIBVA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libva*.so* \
		$(IDIR_LIBVA)/usr/lib
	$(INSTALL_DIR) $(IDIR_LIBVA)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_LIBVA)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
