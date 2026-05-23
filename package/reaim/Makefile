# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		reaim
PKG_VERSION:=		0.8
PKG_RELEASE:=		9
PKG_HASH:=		8a530d8b2ee40c63dd71f20657f324252732632778928ecccaea2a237be19eb5
PKG_DESCR:=		transparent aim / msn proxy
PKG_SECTION:=		app/chat
PKG_DEPENDS:=		iptables
PKG_URL:=		http://reaim.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/reaim/files/reaim/$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,REAIM,reaim,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual

reaim-install:
	${INSTALL_DIR} ${IDIR_REAIM}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/reaim ${IDIR_REAIM}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
