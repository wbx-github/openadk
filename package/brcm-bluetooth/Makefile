# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		brcm-bluetooth
PKG_VERSION:=		1.0
PKG_RELEASE:=		3
PKG_DESCR:=		firmware for broadcom bluetooth chips
PKG_SECTION:=		sys/firmware
PKG_DEPENDS:=		bluez

PKG_CFLINE_BRCM_BLUETOOTH:=	depends on ADK_BROKEN

NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,BRCM_BLUETOOTH,brcm-bluetooth,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual
BUILD_STYLE:=           manual
INSTALL_STYLE:=         manual

do-build:
	${TARGET_CC} ${TARGET_CPPFLAGS} ${TARGET_CFLAGS} ${TARGET_LDFLAGS} \
		-o ${WRKBUILD}/brcm_patchram ${WRKBUILD}/brcm_patchram.c

do-install:
	${INSTALL_DIR} ${IDIR_BRCM_BLUETOOTH}/etc/init.d
	$(INSTALL_BIN) ./files/hci $(IDIR_BRCM_BLUETOOTH)/etc/init.d/
	${INSTALL_DIR} ${IDIR_BRCM_BLUETOOTH}/lib/firmware/brcm
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI3)$(ADK_TARGET_SYSTEM_RASPBERRY_PI3P),y)
	${CP} ${WRKBUILD}/BCM43430A1.hcd ${IDIR_BRCM_BLUETOOTH}/lib/firmware
else
	${CP} ${WRKBUILD}/*.hcd ${IDIR_BRCM_BLUETOOTH}/lib/firmware/brcm
	${INSTALL_DIR} ${IDIR_BRCM_BLUETOOTH}/sbin
	${INSTALL_BIN} ${WRKBUILD}/brcm_patchram \
		${IDIR_BRCM_BLUETOOTH}/sbin/brcm_patchram
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
