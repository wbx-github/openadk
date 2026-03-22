# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		realtek-firmware
PKG_VERSION:=		1.2
PKG_RELEASE:=		1
PKG_HASH:=		a06e7834f15ee4c6cd0c205f61c9667023c0a195ec182a7700877ea90bbaa142
PKG_DESCR:=		firmware for realtek wired and wireless cards
PKG_SECTION:=		sys/firmware
PKG_SITES:=		http://distfiles.openadk.org/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		REALTEK_FIRMWARE_WIRELESS REALTEK_FIRMWARE_WIRED

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,REALTEK_FIRMWARE_WIRED,realtek-firmware-wired,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,REALTEK_FIRMWARE_WIRELESS,realtek-firmware-wireless,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual
BUILD_STYLE:=           manual
INSTALL_STYLE:=         manual

do-install:
	${INSTALL_DIR} ${IDIR_REALTEK_FIRMWARE_WIRELESS}/lib/firmware
	${CP} ${WRKBUILD}/rtlwifi \
		${IDIR_REALTEK_FIRMWARE_WIRELESS}/lib/firmware
	${INSTALL_DIR} ${IDIR_REALTEK_FIRMWARE_WIRED}/lib/firmware
	${CP} ${WRKBUILD}/rtl_nic \
		${IDIR_REALTEK_FIRMWARE_WIRED}/lib/firmware

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
