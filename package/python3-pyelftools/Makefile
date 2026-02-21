# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python3-pyelftools
PKG_VERSION:=		0.32
PKG_RELEASE:=		1
PKG_HASH:=		6de90ee7b8263e740c8715a925382d4099b354f29ac48ea40d840cf7aa14ace5
PKG_DESCR:=		fast, expressive, extensible templating engine
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		python3-host
PKG_SITES:=		https://files.pythonhosted.org/packages/b9/ab/33968940b2deb3d92f5b146bc6d4009a5f95d1d06c148ea2f9ee965071af/

DISTFILES:=             pyelftools-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/pyelftools-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PYTHON3_YAML,python3-pyelftools,${PKG_VERSION}-${PKG_RELEASE}))

include $(ADK_TOPDIR)/mk/python3.mk

HOST_STYLE:=		manual

python3-pyelftools-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python3 ./setup.py install \
		--prefix=$(STAGING_HOST_DIR)/usr)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
