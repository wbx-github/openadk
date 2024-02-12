# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		kmod
PKG_VERSION:=		31
PKG_RELEASE:=		1
PKG_HASH:=		f5a6949043cc72c001b728d8c218609c5a15f3c33d75614b78c79418fcf00d80
PKG_DESCR:=		kernel module utils
PKG_SECTION:=		sys/utils
PKG_DEPENDS:=		libkmod
PKG_SITES:=		https://www.kernel.org/pub/linux/utils/kernel/kmod/
PKG_LIBNAME:=		libkmod
PKG_OPTS:=		dev

PKG_SUBPKGS:=		KMOD LIBKMOD
PKGSD_LIBKMOD:=		kernel module library
PKGSC_LIBKMOD:=		libs/misc

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,KMOD,kmod,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,KMOD,kmod,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBKMOD,libkmod,$(PKG_VERSION)-${PKG_RELEASE},${PKGSS_LIBKMOD},${PKGSD_LIBKMOD},${PKGSC_LIBKMOD},${PKG_OPTS}))

CONFIG_STYLE:=		minimal
CONFIGURE_ARGS+=	--host=${GNU_TARGET_NAME} \
			--disable-manpages

HOST_CONFIGURE_ARGS+=	--disable-manpages \
			--disable-logging

hostpost-install:
	ln -sf kmod $(STAGING_HOST_DIR)/usr/bin/depmod
	ln -sf kmod $(STAGING_HOST_DIR)/usr/bin/modinfo

kmod-install:
	$(INSTALL_DIR) $(IDIR_KMOD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/kmod \
		$(IDIR_KMOD)/usr/bin
	cd $(IDIR_KMOD)/usr/bin && ln -sf kmod modinfo
	cd $(IDIR_KMOD)/usr/bin && ln -sf kmod modprobe
	cd $(IDIR_KMOD)/usr/bin && ln -sf kmod lsmod
	cd $(IDIR_KMOD)/usr/bin && ln -sf kmod insmod
	cd $(IDIR_KMOD)/usr/bin && ln -sf kmod depmod
	cd $(IDIR_KMOD)/usr/bin && ln -sf kmod rmmod

libkmod-install:
	$(INSTALL_DIR) $(IDIR_LIBKMOD)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libkmod*.so* \
		$(IDIR_LIBKMOD)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
