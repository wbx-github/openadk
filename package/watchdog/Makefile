# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		watchdog
PKG_VERSION:=		5.16
PKG_RELEASE:=		1
PKG_HASH:=		b8e7c070e1b72aee2663bdc13b5cc39f76c9232669cfbb1ac0adc7275a3b019d
PKG_DESCR:=		watchdog daemon
PKG_SECTION:=		sys/hw
PKG_DEPENDS:=		libtirpc
PKG_BUILDDEP:=		libtirpc
PKG_SITES:=		https://sourceforge.net/projects/watchdog/files/watchdog/$(PKG_VERSION)/
PKG_BB:=		1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,WATCHDOG,watchdog,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CPPFLAGS+=	-D_GNU_SOURCE
TARGET_CFLAGS+=		-I$(STAGING_TARGET_DIR)/usr/include/tirpc
TARGET_LDFLAGS+=	-ltirpc

watchdog-install:
	${INSTALL_DIR} ${IDIR_WATCHDOG}/sbin ${IDIR_WATCHDOG}/etc/
	${INSTALL_DATA} ./files/watchdog.conf ${IDIR_WATCHDOG}/etc/
	${INSTALL_BIN} ${WRKINST}/usr/sbin/watchdog \
		       ${IDIR_WATCHDOG}/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
