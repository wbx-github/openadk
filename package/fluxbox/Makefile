# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fluxbox
PKG_VERSION:=		1.3.7
PKG_RELEASE:=		2
PKG_HASH:=		fc8c75fe94c54ed5a5dd3fd4a752109f8949d6df67a48e5b11a261403c382ec0
PKG_DESCR:=		window manager featuring tabs and an iconbar
PKG_SECTION:=		x11/apps
PKG_BUILDDEP:=		libXpm libXft
PKG_NEEDS:=		c++
PKG_URL:=		http://www.fluxbox.org/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=fluxbox/}

PKG_FLAVOURS_FLUXBOX:=	WITH_IMLIB2
PKGFD_WITH_IMLIB2:=	enable imlib2 support
PKGFS_WITH_IMLIB2:=	imlib2
PKGFB_WITH_IMLIB2:=	imlib2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FLUXBOX,fluxbox,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=         ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes

ifeq (${ADK_PACKAGE_FLUXBOX_WITH_IMLIB2},y)
CONFIGURE_ARGS+=	--enable-imlib2
else
CONFIGURE_ARGS+=	--disable-imlib2
endif

fluxbox-install:
	$(INSTALL_DIR) $(IDIR_FLUXBOX)/usr/{bin,share}
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_FLUXBOX)/usr/bin
	${CP} ${WRKINST}/usr/share/fluxbox ${IDIR_FLUXBOX}/usr/share/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
