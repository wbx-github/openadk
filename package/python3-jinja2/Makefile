# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python3-jinja2
PKG_VERSION:=		3.0.2
PKG_RELEASE:=		1
PKG_HASH:=		827a0e32839ab1600d4eb1c4c33ec5a8edfbc5cb42dafa13b81f182f97784b45
PKG_DESCR:=		fast, expressive, extensible templating engine
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		python3-host
PKG_URL:=		https://pypi.org/project/Jinja2/
PKG_SITES:=		https://files.pythonhosted.org/packages/f8/86/7c0eb6e8b05385d1ce682abc0f994abd1668e148fb52603fa86e15d4c110/

DISTFILES:=             Jinja2-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/Jinja2-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PYTHON3_JINJA2,python3-jinja2,${PKG_VERSION}-${PKG_RELEASE}))

include $(ADK_TOPDIR)/mk/python.mk

HOST_STYLE:=		manual

python3-jinja2-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python3 ./setup.py install \
		--prefix=$(STAGING_HOST_DIR)/usr)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
