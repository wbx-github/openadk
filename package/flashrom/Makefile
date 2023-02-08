# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		flashrom
PKG_VERSION:=		v1.2
PKG_RELEASE:=		1
PKG_HASH:=		e1f8d95881f5a4365dfe58776ce821dfcee0f138f75d0f44f8a3cd032d9ea42b
PKG_DESCR:=		utility for identifying, reading, writing, verifying and erasing flash chips.
PKG_SECTION:=		sys/hw
PKG_DEPENDS:=		pciutils libusb zlib
PKG_BUILDDEP:=		pciutils libusb zlib
PKG_URL:=		https://www.flashrom.org/Flashrom
PKG_SITES:=		https://download.flashrom.org/releases/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FLASHROM,flashrom,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
TARGET_CFLAGS+=		-I$(STAGING_TARGET_DIR)/usr/include/libusb-1.0

flashrom-install:
	${INSTALL_DIR} ${IDIR_FLASHROM}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/local/sbin/flashrom ${IDIR_FLASHROM}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
