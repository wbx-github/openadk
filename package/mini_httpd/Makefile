# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mini-httpd
PKG_VERSION:=		1.19
PKG_RELEASE:=		10
PKG_HASH:=		f7f36533b1338ea16d916ea525ea7006ab38fdd3544ac7df93a4688a8e270241
PKG_DESCR:=		small webserver with ssl support
PKG_DEPENDS:=		libopenssl
PKG_BUILDDEP:=		openssl
PKG_SECTION:=		net/http
PKG_URL:=		http://www.acme.com/software/mini_httpd/
PKG_SITES:=		http://www.acme.com/software/mini_httpd/

DISTFILES:=		mini_httpd-${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/mini_httpd-${PKG_VERSION}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MINI_HTTPD,mini-httpd,${PKG_VERSION}-${PKG_RELEASE},,${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-build:
	${MAKE} -C ${WRKBUILD} \
		CC="${TARGET_CC}" \
		SSL_DEFS="-DUSE_SSL -DHAVE_OPENSSL" \
		SSL_INC="-I${STAGING_TARGET_DIR}/usr/include" \
		SSL_LIBS="-L${STAGING_TARGET_DIR}/usr/lib -lssl -lcrypto" \
		all

do-install:
	${INSTALL_DIR} ${IDIR_MINI_HTTPD}/etc
	${INSTALL_DATA} ./files/mini_httpd-ssl.conf \
		${IDIR_MINI_HTTPD}/etc/mini_httpd.conf
	install -m0600 ./files/mini_httpd.pem ${IDIR_MINI_HTTPD}/etc/
	${INSTALL_DIR} ${IDIR_MINI_HTTPD}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/mini_httpd \
		${IDIR_MINI_HTTPD}/usr/sbin/mini_httpd

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
