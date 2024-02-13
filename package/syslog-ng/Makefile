# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		syslog-ng
PKG_VERSION:=		4.6.0
PKG_RELEASE:=		1
PKG_HASH:=		a5f8b089887767b5e87f523562fc3c6d5ef4dd320fc9b1f44953cb2d6bd50026
PKG_DESCR:=		powerful syslog daemon
PKG_SECTION:=		sys/misc
PKG_BUILDDEP:=		cmake-host glib ivykis libressl json-c libnet 
PKG_BUILDDEP+=		pcre flex
PKG_DEPENDS:=		glib ivykis libressl json-c libnet
PKG_URL:=		http://www.balabit.com/
PKG_SITES:=		https://github.com/balabit/syslog-ng/archive/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/$(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SYSLOG_NG,syslog-ng,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DSYSLOG_NG_ENABLE_SYSTEMD=OFF \
			-DSYSLOG_NG_ENABLE_TCP_WRAPPER=OFF \
			-DENABLE_CURL=OFF \
			-DENABLE_JAVA=OFF \
			-DENABLE_PYTHON=OFF \
			-DENABLE_JAVA_MODULES=OFF \
			-DBUILD_TESTING=OFF \
			-DENABLE_AFSNMP=OFF \
			-DENABLE_EXAMPLE_MODULES=OFF

syslog-ng-install:
	${INSTALL_DIR} ${IDIR_SYSLOG_NG}/usr/sbin \
		${IDIR_SYSLOG_NG}/etc/syslog-ng
	${INSTALL_BIN} ${WRKINST}/usr/sbin/syslog-ng \
		${IDIR_SYSLOG_NG}/usr/sbin/
	${INSTALL_DATA} ./files/syslog-ng.conf \
		${IDIR_SYSLOG_NG}/etc/syslog-ng/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
