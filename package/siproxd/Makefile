# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		siproxd
PKG_VERSION:=		0.8.4
PKG_RELEASE:=		1
PKG_HASH:=		ad5b9bf24713aed02906507a503ed0c85e26921c9bea63c72adac4a5ee39e416
PKG_DESCR:=		session initiation protocol proxy
PKG_SECTION:=		net/voip
PKG_DEPENDS:=		libosip2
PKG_BUILDDEP:=		libosip2
PKG_NEEDS:=		threads
PKG_URL:=		http://siproxd.sourceforge.net
PKG_SITES:=		https://sourceforge.net/projects/siproxd/files/siproxd/$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SIPROXD,siproxd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

siproxd-install:
	${INSTALL_DIR} ${IDIR_SIPROXD}/usr/sbin ${IDIR_SIPROXD}/etc
	${INSTALL_DATA} ${WRKINST}/etc/siproxd.conf.example \
		${IDIR_SIPROXD}/etc/siproxd.conf
	${INSTALL_DATA} ${WRKINST}/etc/siproxd_passwd.cfg ${IDIR_SIPROXD}/etc/
	${INSTALL_BIN} ${WRKINST}/usr/sbin/siproxd ${IDIR_SIPROXD}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
