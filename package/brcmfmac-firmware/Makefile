# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		brcmfmac-firmware
PKG_VERSION:=		1.0
PKG_RELEASE:=		5
PKG_DESCR:=		firmware for broadcom wireless cards
PKG_SECTION:=		sys/firmware

NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,BRCMFMAC_FIRMWARE,brcmfmac-firmware,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual
BUILD_STYLE:=           manual
INSTALL_STYLE:=         manual

do-install:
	${INSTALL_DIR} ${IDIR_BRCMFMAC_FIRMWARE}/lib/firmware/brcm
	${CP} ${WRKBUILD}/* ${IDIR_BRCMFMAC_FIRMWARE}/lib/firmware/brcm

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
