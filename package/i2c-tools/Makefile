# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		i2c-tools
PKG_VERSION:=		4.4
PKG_RELEASE:=		1
PKG_HASH:=		8b15f0a880ab87280c40cfd7235cfff28134bf14d5646c07518b1ff6642a2473
PKG_DESCR:=		i2c tools
PKG_SECTION:=		sys/hw
PKG_SITES:=		https://www.kernel.org/pub/software/utils/i2c-tools/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,I2C_TOOLS,i2c-tools,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual

XAKE_FLAGS:=		PREFIX=/usr

i2c-tools-install:
	$(INSTALL_DIR) $(IDIR_I2C_TOOLS)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/i2c* \
		$(IDIR_I2C_TOOLS)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
