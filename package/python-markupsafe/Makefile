# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python-markupsafe
PKG_VERSION:=		3.0.2
PKG_RELEASE:=		1
PKG_HASH:=		ee55d3edf80167e48ea11a923c7386f4669df67d7994554387f84e7d8b0a2bf0
PKG_DESCR:=		implements a XML/HTML/XHTML markup safe string
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		python3-host
PKG_SITES:=		https://files.pythonhosted.org/packages/b2/97/5d42485e71dfc078108a86d6de8fa46db44a1a9295e89c5d6d4a06e23a62/

DISTFILES:=             markupsafe-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/markupsafe-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PYTHON_MAKO,python-markupsafe,${PKG_VERSION}-${PKG_RELEASE}))

include $(ADK_TOPDIR)/mk/python3.mk

HOST_STYLE:=		manual

python-markupsafe-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python3 ./setup.py install \
		--prefix=$(STAGING_HOST_DIR)/usr)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
