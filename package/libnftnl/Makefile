# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libnftnl
PKG_VERSION:=		1.3.1
PKG_RELEASE:=		1
PKG_HASH:=		607da28dba66fbdeccf8ef1395dded9077e8d19f2995f9a4d45a9c2f0bcffba8
PKG_DESCR:=		low-level netlink programming interface to the in-kernel nf_tables subsystem
PKG_SECTION:=		libs/misc
PKG_URL:=		https://www.netfilter.org/projects/libnftnl/index.html
PKG_SITES:=		https://www.netfilter.org/projects/libnftnl/files/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBNFTNL,libnftnl,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libnftnl-install:
	$(INSTALL_DIR) $(IDIR_LIBNFTNL)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libnftnl*.so* \
		$(IDIR_LIBNFTNL)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
