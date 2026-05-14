# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		busybox-small
PKG_VERSION:=		1.38.0
PKG_RELEASE:=		1
PKG_HASH:=		34f9ea6ff8636f2c9241153b9114eefa9e65674a45318ae1ef95bb5f31c53bb2
PKG_DESCR:=		core utilities for embedded systems (extra small for noMMU)
PKG_SECTION:=		base/apps
PKG_URL:=		http://www.busybox.net/
PKG_SITES:=		https://www.busybox.net/downloads/

DISTFILES:=		busybox-${PKG_VERSION}.tar.bz2
WRKDIST=		${WRKDIR}/busybox-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BUSYBOX_SMALL,busybox-small,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

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
	cp ./files/busybox.config $(WRKBUILD)/.config
	$(SED) 's;@IDIR@;${WRKINST};' ${WRKBUILD}/.config

do-build:
	PATH='$(HOST_PATH)' $(MAKE) ${BB_MAKE_FLAGS} -C ${WRKBUILD} busybox

do-install:
	PATH='$(HOST_PATH)' $(MAKE) ${BB_MAKE_FLAGS} -C ${WRKBUILD} install $(MAKE_TRACE)
	$(CP) $(WRKINST)/* $(IDIR_BUSYBOX_SMALL)/
	mkdir -p $(IDIR_BUSYBOX_SMALL)/etc
	$(CP) ./files/inittab $(IDIR_BUSYBOX_SMALL)/etc
	$(SED) 's#@DEVICE@#$(ADK_RUNTIME_CONSOLE_SERIAL_DEVICE)#g' $(IDIR_BUSYBOX_SMALL)/etc/inittab
	$(SED) 's#@SPEED@#$(ADK_RUNTIME_CONSOLE_SERIAL_SPEED)#' $(IDIR_BUSYBOX_SMALL)/etc/inittab

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
