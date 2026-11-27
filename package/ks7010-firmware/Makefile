# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ks7010-firmware
PKG_VERSION:=		1.0
PKG_RELEASE:=		1
PKG_DESCR:=		firmware for keystream ks7010 sdio wireless cards
PKG_SECTION:=		sys/firmware

NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,KS7010_FIRMWARE,ks7010-firmware,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-install:
	${INSTALL_DIR} ${IDIR_KS7010_FIRMWARE}/lib/firmware
	${INSTALL_DATA} ./files/ks7010sd.rom \
		${IDIR_KS7010_FIRMWARE}/lib/firmware

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
