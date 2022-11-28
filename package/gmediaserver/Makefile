# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gmediaserver
PKG_VERSION:=		0.13.0
PKG_RELEASE:=		4
PKG_HASH:=		357030911bcce4ac9e47c2c9219b72e88705a8465899d4e0553bce540fb0fd12
PKG_DESCR:=		media server
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		id3lib libupnp libmagic magic
PKG_BUILDDEP:=		id3lib libupnp file
PKG_NEEDS:=		c++
PKG_URL:=		http://www.gnu.org/software/gmediaserver
PKG_SITES:=		http://savannah.nongnu.org/download/gmediaserver/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_LIBC_DEPENDS:=	uclibc-ng glibc

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,GMEDIASERVER,gmediaserver,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CPPFLAGS+=	-D_GNU_SOURCE -I$(STAGING_TARGET_DIR)/usr/include/taglib
CONFIGURE_ENV+=		LIBS=" -lixml -lthreadutil -lupnp -lz"
CONFIGURE_ARGS+=	--with-id3lib="${STAGING_TARGET_DIR}/usr" \
			--with-libupnp="${STAGING_TARGET_DIR}/usr"

gmediaserver-install:
	${INSTALL_DIR} ${IDIR_GMEDIASERVER}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/bin/gmediaserver \
		${IDIR_GMEDIASERVER}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
