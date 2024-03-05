# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		icecast
PKG_VERSION:=		2.4.4
PKG_RELEASE:=		1
PKG_HASH:=		49b5979f9f614140b6a38046154203ee28218d8fc549888596a683ad604e4d44
PKG_DESCR:=		streaming media server
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		libcurl libvorbis libxml2 libxslt
PKG_BUILDDEP:=		curl libvorbis libxml2 libxslt
PKG_NEEDS:=		threads
PKG_URL:=		http://www.icecast.org/
PKG_SITES:=		http://downloads.us.xiph.org/releases/icecast/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,ICECAST,icecast,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
TARGET_CPPFLAGS+=	-I${STAGING_TARGET_DIR}/usr/include/libxml2
TARGET_LDFLAGS+=	-lxml2
CONFIGURE_ARGS+=	--disable-yp \
			--with-curl="yes" \
			--with-curl-config="${STAGING_TARGET_DIR}/usr/bin/curl-config" \
			--with-ogg="${STAGING_TARGET_DIR}/usr" \
			--with-vorbis="${STAGING_TARGET_DIR}/usr" \
			--with-speex="no" \
			--with-theora="no" \
			--with-xslt-config="${STAGING_TARGET_DIR}/usr/bin/xslt-config"

icecast-install:
	${INSTALL_DIR} ${IDIR_ICECAST}/etc
	${CP} ${WRKINST}/etc/icecast.xml ${IDIR_ICECAST}/etc/
	${INSTALL_DIR} ${IDIR_ICECAST}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/icecast ${IDIR_ICECAST}/usr/bin/
	${INSTALL_DIR} ${IDIR_ICECAST}/usr/share/icecast
	${CP} ${WRKINST}/usr/share/icecast/admin \
		${IDIR_ICECAST}/usr/share/icecast/
	${CP} ${WRKINST}/usr/share/icecast/web \
		${IDIR_ICECAST}/usr/share/icecast/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
