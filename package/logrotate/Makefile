# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		logrotate
PKG_VERSION:=		3.21.0
PKG_RELEASE:=		1
PKG_HASH:=		8fa12015e3b8415c121fc9c0ca53aa872f7b0702f543afda7e32b6c4900f6516
PKG_DESCR:=		logfile rotation utility
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libpopt
PKG_BUILDDEP:=		popt
PKG_SITES:=		https://github.com/logrotate/logrotate/releases/download/$(PKG_VERSION)/

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LOGROTATE,logrotate,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

logrotate-install:
	${INSTALL_DIR} ${IDIR_LOGROTATE}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/logrotate ${IDIR_LOGROTATE}/usr/sbin
	${INSTALL_DIR} ${IDIR_LOGROTATE}/etc/logrotate.d
	${INSTALL_DATA} ./files/logrotate.conf ${IDIR_LOGROTATE}/etc

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
