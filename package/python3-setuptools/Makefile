# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python3-setuptools
PKG_VERSION:=		78.1.0
PKG_RELEASE:=		1
PKG_HASH:=		18fd474d4a82a5f83dac888df697af65afa82dec7323d09c3e37d1f14288da54
PKG_DESCR:=		python installer
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		python3-host
PKG_SITES:=		https://files.pythonhosted.org/packages/a9/5a/0db4da3bc908df06e5efae42b44e75c81dd52716e10192ff36d0c1c8e379/

DISTFILES:=             setuptools-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/setuptools-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PYTHON3_SETUPTOOLS,python3-setuptools,${PKG_VERSION}-${PKG_RELEASE}))

include $(ADK_TOPDIR)/mk/python3.mk

HOST_STYLE:=		manual

python3-setuptools-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python3 ./setup.py install \
		--prefix=$(STAGING_HOST_DIR)/usr)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
