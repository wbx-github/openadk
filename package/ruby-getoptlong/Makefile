# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ruby-getoptlong
PKG_VERSION:=		0.2.1
PKG_RELEASE:=		1
PKG_HASH:=		d67eba6bcf2348928e3c594a24b15cdd69fc2442054305f120bd90db49629764
PKG_DESCR:=		ruby getoptlong
PKG_SECTION:=		libs/misc
HOST_BUILDDEP:=		ruby-host
PKG_SITES:=		https://github.com/ruby/getoptlong/archive/refs/tags/

DISTFILES:=             v$(PKG_VERSION).tar.gz

WRKDIST=		$(WRKDIR)/getoptlong-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,RUBY_GETOPTLONG,ruby-getoptlong,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,RUBY_GETOPTLONG,ruby-getoptlong,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_STYLE:=		manual

host-configure:

ruby-getoptlong-hostinstall:
	cd ${WRKBUILD} && PATH="$(HOST_PATH)" rake install
	$(CP) lib/getoptlong.rb $(STAGING_HOST_DIR)/usr/lib/ruby/site_ruby/4.0.0/

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
