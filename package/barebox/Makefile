# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		barebox
PKG_VERSION:=		2025.03.0
PKG_RELEASE:=		1
PKG_HASH:=		0bf7118004e445bdd57feeef89ee9064982acc221e8a046c4a7994d3da6da2ec
PKG_DESCR:=		portable bootloader
PKG_SECTION:=		base/boot
PKG_BUILDDEP:=		lzop-host
PKG_URL:=		http://www.barebox.org
PKG_SITES:=		http://www.barebox.org/download/

PKG_ARCH_DEPENDS:=	aarch64 arm mips or1k ppc riscv32 riscv64 x86_64

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BAREBOX,barebox,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS:=
CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

BAREBOX_ARCH:=		$(ADK_TARGET_ARCH)
ifeq ($(ADK_TARGET_ARCH_X86_64),y)
CONFIG:=		efi_defconfig
BAREBOX_ARCH:=		x86
BAREBOX:=		barebox.efi
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_MIPS),y)
ifeq ($(ADK_TARGET_LITTLE_ENDIAN),y)
CONFIG:=		qemu-maltael_defconfig
BAREBOX:=		images/barebox-qemu-malta.img.swapped
else
CONFIG:=		qemu-malta_defconfig
BAREBOX:=		images/barebox-qemu-malta.img
endif
endif
ifeq ($(ADK_TARGET_SYSTEM_QEMU_ARM_VEXPRESS_A9),y)
CONFIG:=		vexpress_ca9_defconfig
endif
ifeq ($(ADK_TARGET_SYSTEM_PHYTEC_IMX6),y)
CONFIG:=		imx_v7_defconfig
endif

do-configure:
	(cd $(WRKBUILD) && $(MAKE) ARCH=$(BAREBOX_ARCH) $(CONFIG))

do-build:
	(cd $(WRKBUILD) && env \
		PATH='$(HOST_PATH)' \
		ARCH=$(BAREBOX_ARCH) \
		CROSS_COMPILE='$(TARGET_CROSS)' \
		$(MAKE))

barebox-install:
	$(CP) $(WRKBUILD)/$(BAREBOX) $(FW_DIR)

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
