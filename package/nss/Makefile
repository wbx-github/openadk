# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		nss
PKG_VERSION:=		3.123.1
PKG_RELEASE:=		1
PKG_MAJ_VERSION:=	3
PKG_MIN_VERSION:=	123_1
PKG_HASH:=		42065a3ff780a9710a3dddcd1cee9b9be2aa40628883cea851d562eb58b178b0
PKG_DESCR:=		network security services library
PKG_SECTION:=		libs/crypto
PKG_BUILDDEP:=		nspr zlib sqlite
PKG_DEPENDS:=		nspr zlib libsqlite
PKG_URL:=		http://www.mozilla.org/projects/security/pki/nss/
PKG_SITES:=		https://ftp.mozilla.org/pub/security/nss/releases/NSS_${PKG_MAJ_VERSION}_${PKG_MIN_VERSION}_RTM/src/
PKG_NOPARALLEL:=	1

PKG_CFLINE_NSS:=	depends on ADK_BROKEN

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
WRKSRC=			${WRKDIST}/nss

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,NSS,nss,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

ifeq ($(ADK_LINUX_64),y)
ifeq ($(ADK_TARGET_ABI_N32),y)
TARGET_CFLAGS+=		-DNS_PTR_LE_32
endif
XAKE_FLAGS+=		USE_64=1
endif

MAKE_FLAGS+=		NATIVE_CC="${HOST_CC}" NATIVE_FLAGS="${HOST_CFLAGS}"
TARGET_CPPFLAGS+=	-I${STAGING_TARGET_DIR}/usr/include/nspr
TARGET_CFLAGS+=		-I${STAGING_TARGET_DIR}/usr/include/nspr -Wno-implicit-function-declaration

XAKE_FLAGS+=		SOURCE_MD_DIR=${WRKDIST}/dist DIST=${WRKDIST}/dist
XAKE_FLAGS+=		ARCHFLAG="${TARGET_CFLAGS} ${TARGET_CPPFLAGS} ${TARGET_LDFLAGS}"
XAKE_FLAGS+=		OS_TEST=${ADK_TARGET_CPU_ARCH} OS_TARGET=Linux OS_RELEASE=2.6 OS_ARCH=Linux
XAKE_FLAGS+=		ARTOOL="${TARGET_CROSS}ar" RANLIB="${TARGET_CROSS}ranlib"
XAKE_FLAGS+=		NSS_USE_SYSTEM_ZLIB=1 NSS_ENABLE_WERROR=0 NSS_DISABLE_DBM=1 NSS_USE_SYSTEM_SQLITE=1
ALL_TARGET:=		all

do-install:
	$(INSTALL_DIR) $(IDIR_NSS)/usr/lib
	${INSTALL_DATA} ${WRKDIST}/dist/lib/lib{nsssysinit,nssckbi,freebl3,freeblpriv3,ssl3,smime3,nss3,nssutil3,softokn3}.so \
		$(IDIR_NSS)/usr/lib
	${INSTALL_DIR} ${STAGING_TARGET_DIR}/usr/include/nss
	${INSTALL_DATA} ${WRKDIST}/dist/public/nss/* \
		${STAGING_TARGET_DIR}/usr/include/nss
	# needed for firefox
	${INSTALL_DIR} ${WRKINST}/usr/bin
	${INSTALL_BIN} ${WRKDIST}/dist/bin/nss-config \
		${WRKINST}/usr/bin
	${INSTALL_DIR} ${WRKINST}/usr/lib/pkgconfig
	${INSTALL_BIN} ${WRKDIST}/dist/lib/pkgconfig/nss.pc \
		${WRKINST}/usr/lib/pkgconfig
	${INSTALL_DIR} ${STAGING_TARGET_DIR}/usr/lib
	$(INSTALL_DATA) ${WRKDIST}/dist/lib/libcrmf.a \
		${STAGING_TARGET_DIR}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
