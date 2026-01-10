# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libiconv
PKG_VERSION:=		1.18
PKG_RELEASE:=		1
PKG_HASH:=		3b08f5f4f9b4eb82f151a7040bfd6fe6c6fb922efe4b1659c66ea933276965e8
PKG_DESCR:=		character set conversion library
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.gnu.org/software/libiconv/
PKG_SITES:=		$(MASTER_SITE_GNU:=libiconv/)
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBICONV,libiconv,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,LIBICONV,libiconv,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libiconv-install:
	$(INSTALL_DIR) $(IDIR_LIBICONV)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libiconv.so* $(IDIR_LIBICONV)/usr/lib/
	$(CP) $(WRKINST)/usr/lib/libcharset.so* $(IDIR_LIBICONV)/usr/lib/

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
