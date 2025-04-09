# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		poco
PKG_VERSION:=		1.14.1
PKG_RELEASE:=		1
PKG_HASH:=		58e386e48bf82ca84005eb7f5fbf543e1d55ebf2e86c5914185c643cd3951632
PKG_DESCR:=		c++ network libraries
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		zlib pcre2
PKG_DEPENDS:=		zlib libpcre2
PKG_URL:=		http://pocoproject.org
PKG_SITES:=		http://pocoproject.org/releases/poco-1.14.1/
PKG_OPTS:=		dev

#PKG_LIBC_DEPENDS:=	glibc

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,POCO,poco,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

TARGET_LDFLAGS+=	-latomic
XAKE_FLAGS+=		POCO_TARGET_OSARCH=$(ADK_TARGET_CPU_ARCH)
CONFIG_STYLE:=		minimal
CONFIGURE_ARGS+=	--prefix=/usr \
			--ldflags='$(TARGET_LDFLAGS)' \
			--no-tests \
			--no-samples

poco-install:
	$(INSTALL_DIR) $(IDIR_POCO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libPoco*.so* \
		$(IDIR_POCO)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
