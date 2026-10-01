# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gumbo-parser
PKG_VERSION:=		0.14.1
PKG_RELEASE:=		1
PKG_HASH:=		ba5d13b9b508ec693613b3b61518163aced38f8e885f7e28dc047348a4e61365
PKG_DESCR:=		html5 parser
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		meson-host
PKG_URL:=		https://codeberg.org/gumbo-parser
PKG_SITES:=		https://codeberg.org/gumbo-parser/gumbo-parser/archive/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GUMBO_PARSER,gumbo-parser,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Dtests=false

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

gumbo-parser-install:
	$(INSTALL_DIR) $(IDIR_GUMBO_PARSER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgumbo.so* \
		$(IDIR_GUMBO_PARSER)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
