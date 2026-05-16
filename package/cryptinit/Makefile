# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		cryptinit
PKG_VERSION:=		2.0
PKG_RELEASE:=		1
PKG_DESCR:=		init for encrypted rootfilesystem
PKG_SECTION:=		base/adk
PKG_DEPENDS:=		cryptsetup

PKG_CFLINE_CRYPTINIT:=	select BUSYBOX_STTY@
PKG_CFLINE_CRYPTINIT+=	select BUSYBOX_SWITCH_ROOT@

PKG_FLAVOURS_CRYPTINIT:=SC NO_GRUB
PKGFD_NO_GRUB:=		predefine root/swap partition (without grub)
PKGFD_SC:=		with smartcard support
PKGFS_SC:=		ccid opensc pcsc-lite
PKGFB_SC:=		ccid opensc pcsc-lite

PKG_FLAVOURS_STRING_CRYPTINIT:=	ROOT SWAP
PKGFD_ROOT:=		root partition
PKGFX_ROOT:=		/dev/sda2
PKGFC_ROOT:=		depends on ADK_PACKAGE_CRYPTINIT_NO_GRUB
PKGFD_SWAP:=		swap partition
PKGFX_SWAP:=		/dev/sda3
PKGFC_SWAP:=		depends on ADK_PACKAGE_CRYPTINIT_NO_GRUB

WRKDIST=		${WRKDIR}/${PKG_NAME}-${PKG_VERSION}
NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,CRYPTINIT,cryptinit,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-install:
	$(INSTALL_DIR) $(IDIR_CRYPTINIT)/sbin
	$(TARGET_CC) $(TARGET_CFLAGS) -Wall -o $(IDIR_CRYPTINIT)/sbin/p \
		./src/p.c
ifeq ($(ADK_PACKAGE_CRYPTINIT_SC),y)
	$(INSTALL_BIN) ./src/cryptinitsc $(IDIR_CRYPTINIT)/cryptinit
else
	$(INSTALL_BIN) ./src/cryptinit $(IDIR_CRYPTINIT)/
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
