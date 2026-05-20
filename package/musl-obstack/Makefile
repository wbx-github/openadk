# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		musl-obstack
PKG_VERSION:=		1.2.3
PKG_RELEASE:=		1
PKG_HASH:=		9ffb3479b15df0170eba4480e51723c3961dbe0b461ec289744622db03a69395
PKG_DESCR:=		obstack library
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/void-linux/musl-obstack/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MUSL_OBSTACK,musl-obstack,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	autoreconf

musl-obstack-install:
	$(INSTALL_DIR) $(IDIR_MUSL_OBSTACK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libobstack*.so* \
		$(IDIR_MUSL_OBSTACK)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
