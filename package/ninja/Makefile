# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ninja
PKG_VERSION:=		1.13.1
PKG_RELEASE:=		1
PKG_HASH:=		f0055ad0369bf2e372955ba55128d000cfcc21777057806015b45e4accbebf23
PKG_DESCR:=		build utility
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		python3-host
PKG_URL:=		http://www.ninja-build.org/
PKG_SITES:=		https://github.com/ninja-build/ninja/archive/

DISTFILES:=		v${PKG_VERSION}.tar.gz

PKG_CFLINE_NINJA:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,NINJA,ninja,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		manual

host-configure:
	(cd $(WRKBUILD); ./configure.py --bootstrap)

host-build:

ninja-hostinstall:
	$(INSTALL_BIN) $(WRKBUILD)/ninja \
	       $(STAGING_HOST_DIR)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
