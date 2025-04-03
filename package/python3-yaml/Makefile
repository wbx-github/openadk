# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		python3-yaml
PKG_VERSION:=		6.0.2
PKG_RELEASE:=		1
PKG_HASH:=		d584d9ec91ad65861cc08d42e834324ef890a082e591037abe114850ff7bbc3e
PKG_DESCR:=		fast, expressive, extensible templating engine
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		python3-host
PKG_SITES:=		https://files.pythonhosted.org/packages/54/ed/79a089b6be93607fa5cdaedf301d7dfb23af5f25c398d5ead2525b063e17/

DISTFILES:=             pyyaml-$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/pyyaml-$(PKG_VERSION)

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
