# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python-markupsafe
PKG_VERSION:=		2.1.5
PKG_RELEASE:=		1
PKG_HASH:=		d283d37a890ba4c1ae73ffadf8046435c76e7bc2247bbb63c00bd1a709c6544b
PKG_DESCR:=		implements a XML/HTML/XHTML markup safe string
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		python3-host
PKG_SITES:=		https://files.pythonhosted.org/packages/87/5b/aae44c6655f3801e81aa3eef09dbbf012431987ba564d7231722f68df02d/

DISTFILES:=             MarkupSafe-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/MarkupSafe-$(PKG_VERSION)

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
