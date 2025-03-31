# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python3-yaml
PKG_VERSION:=		5.3.1
PKG_RELEASE:=		1
PKG_HASH:=		b8eac752c5e14d3eca0e6dd9199cd627518cb5ec06add0de9d32baeee6fe645d
PKG_DESCR:=		fast, expressive, extensible templating engine
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		python3-host
PKG_SITES:=		http://pyyaml.org/download/pyyaml/

DISTFILES:=             PyYAML-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/PyYAML-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PYTHON3_YAML,python3-yaml,${PKG_VERSION}-${PKG_RELEASE}))

include $(ADK_TOPDIR)/mk/python3.mk

HOST_STYLE:=		manual

python3-yaml-hostinstall:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' python3 ./setup.py install \
		--prefix=$(STAGING_HOST_DIR)/usr)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
