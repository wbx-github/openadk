# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		faad2
PKG_VERSION:=		2.8.8
PKG_RELEASE:=		1
PKG_HASH:=		985c3fadb9789d2815e50f4ff714511c79c2710ac27a4aaaf5c0c2662141426d
PKG_DESCR:=		mp4 decoding library
PKG_SECTION:=		libs/video
PKG_URL:=		http://sourceforge.net/projects/faac/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=faac/}
PKG_LIBNAME:=		libfaad2
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBFAAD2,libfaad2,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--without-mpeg4ip \
			--without-xmms
TARGET_LDFLAGS+=	-lm

libfaad2-install:
	${INSTALL_DIR} ${IDIR_LIBFAAD2}/usr/lib
	${CP} ${WRKINST}/usr/lib/libfaad.so* ${IDIR_LIBFAAD2}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
