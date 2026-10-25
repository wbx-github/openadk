# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ethtool
PKG_VERSION:=		7.2
PKG_RELEASE:=		1
PKG_HASH:=		44256ddf4631ed08d816b7b8725f4b2e0f05e96b8c7ca64ee5c81449da2b6507
PKG_DESCR:=		display or change ethernet card settings
PKG_DEPENDS:=		libmnl
PKG_BUILDDEP:=		libmnl
PKG_SECTION:=		net/misc
PKG_SITES:=		https://www.kernel.org/pub/software/network/ethtool/

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,ETHTOOL,ethtool,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ethtool-install:
	${INSTALL_DIR} ${IDIR_ETHTOOL}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/ethtool \
		${IDIR_ETHTOOL}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
