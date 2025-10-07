# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		exiv2
PKG_VERSION:=		0.28.7
PKG_RELEASE:=		1
PKG_HASH:=		5e292b02614dbc0cee40fe1116db2f42f63ef6b2ba430c77b614e17b8d61a638
PKG_DESCR:=		fast read and write access to the Exif, IPTC and XMP metadata of an image
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libinih
PKG_BUILDDEP:=		libinih
PKG_URL:=		https://www.exiv2.org
PKG_SITES:=		https://github.com/Exiv2/exiv2/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,EXIV2,exiv2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DEXIV2_ENABLE_BROTLI=OFF \
			-DBUILD_WITH_STACK_PROTECTOR=OFF

exiv2-install:
	$(INSTALL_DIR) $(IDIR_EXIV2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libexiv2*.so* \
		$(IDIR_EXIV2)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
