# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		bcm28xx-utils
PKG_VERSION:=		e65f5ec102e74218cda7da9fdc8b1caa0fd1127d
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_DESCR:=		videocore tools and utils
PKG_SECTION:=		sys/hw
PKG_BUILDDEP:=		cmake-host
PKG_NEEDS:=		c++ threads
PKG_URL:=		https://github.com/raspberrypi/utils
PKG_SITES:=		https://github.com/raspberrypi/utils.git

PKG_SYSTEM_DEPENDS:=	raspberry-pi raspberry-pi0 raspberry-pi2 raspberry-pi3 raspberry-pi3-64 raspberry-pi4 raspberry-pi4-64 raspberry-pi5

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BCM28XX_UTILS,bcm28xx-utils,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=          cmake

bcm28xx-utils-install:
	$(INSTALL_DIR) $(IDIR_BCM28XX_UTILS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/vcgencmd \
		$(IDIR_BCM28XX_UTILS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/vclog \
		$(IDIR_BCM28XX_UTILS)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
