# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		meson
PKG_VERSION:=		1.3.1
PKG_RELEASE:=		1
PKG_HASH:=		274c121edb859602eb4589d31d8791e980748bb19950fc6f611a21d76dc22cc6
PKG_DESCR:=		build utility
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		python3-host ninja-host
PKG_URL:=		http://www.mesonbuild.com/
PKG_SITES:=		https://github.com/mesonbuild/meson/archive/

DISTFILES:=		${PKG_VERSION}.tar.gz

PKG_CFLINE_MESON:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,MESON,meson,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		manual

host-configure:

host-build:

meson-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python3 ./setup.py install)
	$(INSTALL_DIR) $(STAGING_HOST_DIR)/etc/meson
	sed -e "s%@TARGET_CROSS@%$(TARGET_CROSS)%g" \
	    -e "s%@TARGET_ARCH@%$(ADK_TARGET_ARCH)%g" \
	    -e "s%@TARGET_CPU@%$(ADK_TARGET_CPU_ARCH)%g" \
	    -e "s%@TARGET_ENDIAN@%$(ADK_TARGET_ENDIAN)%g" \
            -e "s%@TARGET_CFLAGS@%`printf '"%s", ' $(TARGET_CFLAGS)`%g" \
	    -e "s%@TARGET_LDFLAGS@%`printf '"%s", ' $(TARGET_LDFLAGS)`%g" \
	    -e "s%@TARGET_CXXFLAGS@%`printf '"%s", ' $(TARGET_CXXFLAGS)`%g" \
	    -e "s%@STAGING_HOST_DIR@%$(STAGING_HOST_DIR)%g" \
		$(WRKBUILD)/cross-compilation.conf.in \
		> $(STAGING_HOST_DIR)/etc/meson/cross-compilation.conf
	sed -i "s/\"/'/g" $(STAGING_HOST_DIR)/etc/meson/cross-compilation.conf
	sed -e "s%@HOST_CFLAGS@%`printf '"%s", ' $(HOST_CFLAGS)`%g" \
	    -e "s%@HOST_LDFLAGS@%`printf '"%s", ' $(HOST_LDFLAGS)`%g" \
	    -e "s%@HOST_CXXFLAGS@%`printf '"%s", ' $(HOST_CXXFLAGS)`%g" \
	    -e "s%@STAGING_HOST_DIR@%$(STAGING_HOST_DIR)%g" \
		$(WRKBUILD)/host-compilation.conf.in \
		> $(STAGING_HOST_DIR)/etc/meson/host-compilation.conf
	sed -i "s/\"/'/g" $(STAGING_HOST_DIR)/etc/meson/host-compilation.conf

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
