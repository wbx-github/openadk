# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mini-init-v850
PKG_VERSION:=		1.0
PKG_RELEASE:=		1
PKG_DESCR:=		minimal /init without a C library
PKG_SECTION:=		base/tests

PKG_ARCH_DEPENDS:=	v850

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MINI_INIT_V850,mini-init-v850,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-build:
	$(TARGET_CC) -nostdlib $(TARGET_LDFLAGS) -o $(WRKBUILD)/init $(WRKBUILD)/init.S

# the initramfs gets /init -> /sbin/init and the /dev nodes from
# mk/image.mk; /dev itself normally comes from base-files
mini-init-v850-install:
	$(INSTALL_DIR) $(IDIR_MINI_INIT_V850)/dev
	$(INSTALL_DIR) $(IDIR_MINI_INIT_V850)/sbin
	$(INSTALL_BIN) $(WRKBUILD)/init $(IDIR_MINI_INIT_V850)/sbin/init

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
