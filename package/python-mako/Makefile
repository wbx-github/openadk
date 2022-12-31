# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python-mako
PKG_VERSION:=		1.2.4
PKG_RELEASE:=		1
PKG_HASH:=		d60a3903dc3bb01a18ad6a89cdbe2e4eadc69c0bc8ef1e3773ba53d44c3f7a34
PKG_DESCR:=		fast, expressive, extensible templating engine
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		python3-host
PKG_SITES:=		https://files.pythonhosted.org/packages/05/5f/2ba6e026d33a0e6ddc1dddf9958677f76f5f80c236bd65309d280b166d3e/

DISTFILES:=             Mako-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/Mako-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PYTHON_MAKO,python-mako,${PKG_VERSION}-${PKG_RELEASE}))

include $(ADK_TOPDIR)/mk/python.mk

HOST_STYLE:=		manual

python-mako-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python3 ./setup.py install \
		--prefix=$(STAGING_HOST_DIR)/usr)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
