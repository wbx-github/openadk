# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		arm-trusted-firmware
PKG_VERSION:=		6952ce49c29be021eb07159c2f472e9e23633135
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_DESCR:=		ARM Trusted Firmware
PKG_SECTION:=		base/boot
PKG_SITES:=		https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ARM_TRUSTED_FIRMWARE,arm-trusted-firmware,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS:=
XAKE_FLAGS+=		V=1
ALL_TARGET:=		bl31
CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

arm-trusted-firmware-install:

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
