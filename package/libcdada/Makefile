# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libcdada
PKG_VERSION:=		0.5.2
PKG_RELEASE:=		1
PKG_HASH:=		507f0b7bf8cb7533c22731c64d92737e7536866be7c7dd317b89709cd6529867
PKG_DESCR:=		basic data structures in C
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/msune/libcdada/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBCDADA,libcdada,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	autogen
CONFIGURE_ARGS+=	--disable-silent-rules \
			--without-tests \
			--without-examples

libcdada-install:
	$(INSTALL_DIR) $(IDIR_LIBCDADA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcdada*.so* \
		$(IDIR_LIBCDADA)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
