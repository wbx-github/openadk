# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		hush
PKG_VERSION:=		1.38.0
PKG_RELEASE:=		1
PKG_HASH:=		34f9ea6ff8636f2c9241153b9114eefa9e65674a45318ae1ef95bb5f31c53bb2
PKG_DESCR:=		hush standalone shell
PKG_SECTION:=		base/shells
PKG_URL:=		http://www.busybox.net/
PKG_SITES:=		https://www.busybox.net/downloads/

WRKDIST=		$(WRKDIR)/busybox-$(PKG_VERSION)
DISTFILES:=		busybox-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,HUSH,hush,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

BB_MAKE_FLAGS:=		V=1 \
			ARCH="${ADK_TARGET_ARCH}" \
			IPKG_ARCH="${ADK_TARGET_CPU_ARCH}" \
			HOSTCC="${CC_FOR_BUILD}" \
			HOSTCFLAGS="$(CFLAGS_FOR_BUILD)" \
			CROSS_COMPILE="$(TARGET_CROSS)" \
			SKIP_STRIP=y

do-configure:
	$(CP) ./files/config $(WRKBUILD)/.config

do-build:
	PATH='$(HOST_PATH)' $(MAKE) $(BB_MAKE_FLAGS) -C $(WRKBUILD) busybox

do-install:
	$(INSTALL_DIR) $(IDIR_HUSH)/bin
	$(CP) $(WRKBUILD)/busybox $(IDIR_HUSH)/bin/hush

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
