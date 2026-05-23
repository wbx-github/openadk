# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sysfsutils
PKG_VERSION:=		2.1.1
PKG_RELEASE:=		1
PKG_HASH:=		f7f669d27c997d3eb3f3e014b4c0aa1aa4d07ce4d6f9e41fa835240f2bf38810
PKG_DESCR:=		utilites built upon sysfs
PKG_SECTION:=		sys/utils
PKG_URL:=		https://github.com/linux-ras/sysfsutils
PKG_SITES:=		https://github.com/linux-ras/sysfsutils/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=		v${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SYSFSUTILS,sysfsutils,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf

sysfsutils-install:
	$(INSTALL_DIR) $(IDIR_SYSFSUTILS)/usr/bin
	$(INSTALL_DIR) $(IDIR_SYSFSUTILS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libsysfs.so* \
		$(IDIR_SYSFSUTILS)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/bin/systool \
		$(IDIR_SYSFSUTILS)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
