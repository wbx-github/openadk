# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		wifidog
PKG_VERSION:=		1.1.5
PKG_RELEASE:=		2
PKG_HASH:=		a58c5fe2e54f6b3decb27c83f3154820ed1429580a9c5f4c67bec0c40a31701a
PKG_DESCR:=		complete and embeddable captive portal
PKG_SECTION:=		net/wifi
PKG_DEPENDS:=		iptables
PKG_URL:=		http://dev.wifidog.org/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=${PKG_NAME}/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,WIFIDOG,wifidog,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-fcommon
CONFIGURE_ENV+=		ac_cv_func_memcmp_working=yes \
			ac_cv_lib_nsl_main=no \
			ac_cv_func_setvbuf_reversed=no

wifidog-install:
	${INSTALL_DIR} ${IDIR_WIFIDOG}/usr/{bin,lib} ${IDIR_WIFIDOG}/etc
	${INSTALL_DATA} ./files/wifidog.conf ${IDIR_WIFIDOG}/etc/
	${INSTALL_BIN} ${WRKBUILD}/scripts/init.d/wifidog \
		${IDIR_WIFIDOG}/usr/bin/wifidog-init
	${INSTALL_BIN} ${WRKINST}/usr/bin/wifidog \
		       ${WRKINST}/usr/bin/wdctl ${IDIR_WIFIDOG}/usr/bin/
	${CP} ${WRKINST}/usr/lib/libhttpd.so* ${IDIR_WIFIDOG}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
