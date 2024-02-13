# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		scons
PKG_VERSION:=		3.1.2
PKG_RELEASE:=		1
PKG_HASH:=		7801f3f62f654528e272df780be10c0e9337e897650b62ddcee9f39fde13f8fb
PKG_DESCR:=		software construction tool
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		python3-host
PKG_URL:=		http://www.scons.org
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=scons/}

DISTFILES:=		$(PKG_NAME)-${PKG_VERSION}.tar.gz

PKG_CFLINE_SCONS:=	depends on ADK_HOST_ONLY

#WRKDIST=		${WRKDIR}/SCons-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,SCONS,scons,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		manual

scons-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python setup.py install \
		--prefix=$(STAGING_HOST_DIR)/usr --install-lib=$(STAGING_HOST_DIR)/usr/lib/scons-$(PKG_VERSION))

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
