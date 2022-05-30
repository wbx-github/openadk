# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		dtc
PKG_VERSION:=		1.6.1
PKG_RELEASE:=		1
PKG_HASH:=		6401c9a0f577a270df4632bf0f3e5454ccc7a5ca3caefa67a3e1c29c9c6b8c60
PKG_DESCR:=		compiler for dts files
PKG_SECTION:=		sys/misc
HOST_BUILDDEP:=		m4-host flex-host bison-host python3-host swig-host
PKG_URL:=		http://www.devicetree.org/Device_Tree_Compiler
PKG_SITES:=		https://github.com/dgibson/dtc/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

PKG_CFLINE_DTC:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,DTC,dtc,$(PKG_VERSION)-$(PKG_RELEASE)))

HOST_STYLE:=		manual

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} all)

dtc-hostinstall:
	$(INSTALL_DIR) $(STAGING_HOST_DIR)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/dtc $(STAGING_HOST_DIR)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/fdtget $(STAGING_HOST_DIR)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/fdtput $(STAGING_HOST_DIR)/usr/bin

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
