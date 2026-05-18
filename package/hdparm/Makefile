# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		hdparm
PKG_VERSION:=		9.65
PKG_RELEASE:=		1
PKG_HASH:=		d14929f910d060932e717e9382425d47c2e7144235a53713d55a94f7de535a4b
PKG_DESCR:=		get/set ata/sata drive parameters
PKG_SECTION:=		sys/hw
PKG_URL:=		http://sourceforge.net/projects/hdparm
PKG_SITES:=		https://sourceforge.net/projects/hdparm/files/hdparm/
PKG_BB:=		1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,HDPARM,hdparm,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual

hdparm-install:
	${INSTALL_DIR} ${IDIR_HDPARM}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/sbin/hdparm ${IDIR_HDPARM}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
