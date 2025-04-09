# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ethtool
PKG_VERSION:=		6.14
PKG_RELEASE:=		1
PKG_HASH:=		9338bb00e492878d3bbe3cd2894e60db35813634c208db0b20f5c7ee84da69b1
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
