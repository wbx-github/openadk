# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		links
PKG_VERSION:=		2.30
PKG_RELEASE:=		1
PKG_HASH:=		7f0d54f4f7d1f094c25c9cbd657f98bc998311122563b1d757c9aeb1d3423b9e
PKG_DESCR:=		web browser for console
PKG_SECTION:=		app/browser
PKG_DEPENDS:=		libpng libjpeg-turbo libtiff gpm
PKG_BUILDDEP:=		libpng libjpeg-turbo gpm
PKG_URL:=		http://links.twibright.com/
PKG_SITES:=		http://links.twibright.com/download/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CHOICES_LINKS:=	WITH_OPENSSL WITHOUT_SSL
PKGCD_WITH_OPENSSL:=	use libopenssl for crypto
PKGCB_WITH_OPENSSL:=	openssl
PKGCS_WITH_OPENSSL:=	libopenssl
PKGCD_WITHOUT_SSL:=	use no ssl

PKG_FLAVOURS_LINKS:=	WITH_FB WITH_DIRECTFB WITH_X
PKGFD_WITH_DIRECTFB:=	enable DirectFB video output support
PKGFS_WITH_DIRECTFB:=	directfb
PKGFB_WITH_DIRECTFB:=	DirectFB
PKGFD_WITH_FB:=		enable framebuffer video output support
PKGFD_WITH_X:=		enable xorg video output support
PKGFS_WITH_X:=		libx11
PKGFB_WITH_X:=		libX11

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LINKS,links,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--without-libevent \
			--without-svgalib \
			--without-libtiff \
			--without-pmshell \
			--without-atheos

ifeq (${ADK_PACKAGE_LINKS_WITHOUT_SSL},y)
CONFIGURE_ARGS+=	--without-ssl
else
CONFIGURE_ARGS+=	--with-ssl
endif

ifeq (${ADK_PACKAGE_LINKS_WITH_FB},y)
CONFIGURE_ARGS+=	--with-fb --enable-graphics
else
CONFIGURE_ARGS+=	--without-fb --disable-graphics
endif

ifeq (${ADK_PACKAGE_LINKS_WITH_DIRECTFB},y)
CONFIGURE_ARGS+=	--with-directfb --enable-graphics
else
CONFIGURE_ARGS+=	--without-directfb --disable-graphics
endif

ifeq (${ADK_PACKAGE_LINKS_WITH_X},y)
CONFIGURE_ARGS+=	--with-x --enable-graphics
else
CONFIGURE_ARGS+=	--without-x --disable-graphics
endif

links-install:
	${INSTALL_DIR} ${IDIR_LINKS}/usr/bin
	${CP} ${WRKINST}/usr/bin/* ${IDIR_LINKS}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
