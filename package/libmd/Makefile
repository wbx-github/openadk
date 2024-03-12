# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libmd
PKG_VERSION:=		1.1.0
PKG_RELEASE:=		1
PKG_HASH:=		1bd6aa42275313af3141c7cf2e5b964e8b1fd488025caf2f971f43b00776b332
PKG_DESCR:=		message digest implementations
PKG_SECTION:=		libs/misc
PKG_URL:=		https://www.hadrons.org/software/libmd/
PKG_SITES:=		https://archive.hadrons.org/software/libmd/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBMD,libmd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libmd-install:
	$(INSTALL_DIR) $(IDIR_LIBMD)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmd*.so* \
		$(IDIR_LIBMD)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
