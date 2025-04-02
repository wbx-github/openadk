# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		yaml
PKG_VERSION:=		0.2.5
PKG_RELEASE:=		1
PKG_HASH:=		c642ae9b75fee120b2d96c712538bd2cf283228d2337df2cf2988e3c02678ef4
PKG_DESCR:=		yaml library
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/yaml/libyaml/releases/download/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,YAML,yaml,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,YAML,yaml,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

yaml-install:
	$(INSTALL_DIR) $(IDIR_YAML)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libyaml*.so* \
		$(IDIR_YAML)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
