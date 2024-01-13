# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python-setuptools
PKG_VERSION:=		69.0.3
PKG_RELEASE:=		1
PKG_HASH:=		be1af57fc409f93647f2e8e4573a142ed38724b8cdd389706a867bb4efcf1e78
PKG_DESCR:=		python setuptools
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		python3-host
PKG_SITES:=		https://files.pythonhosted.org/packages/fc/c9/b146ca195403e0182a374e0ea4dbc69136bad3cd55bc293df496d625d0f7/

DISTFILES:=             setuptools-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/setuptools-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PYTHON_SETUPTOOLS,python-setuptools,${PKG_VERSION}-${PKG_RELEASE}))

include $(ADK_TOPDIR)/mk/python3.mk

HOST_STYLE:=		manual

python-setuptools-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python3 ./setup.py install \
		--prefix=$(STAGING_HOST_DIR)/usr)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
