# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		poppler
PKG_VERSION:=		26.05.0
PKG_RELEASE:=		1
PKG_HASH:=		6fef27ff04f37db43054c86bcdff6128c9fb1f6af4ef3c8b369a7e9abd68d0bb
PKG_DESCR:=		pdf rendering library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		cmake-host fontconfig libpng cairo
PKG_DEPENDS:=		fontconfig libpng cairo
PKG_NEEDS:=		c++
PKG_URL:=		http://poppler.freedesktop.org/
PKG_SITES:=		http://poppler.freedesktop.org/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,POPPLER,poppler,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		cmake

CMAKE_FLAGS+=		-DENABLE_NSS3=OFF \
			-DENABLE_QT5=OFF \
			-DENABLE_QT6=OFF \
			-DENABLE_GPGME=OFF \
			-DENABLE_LCMS=OFF

poppler-install:
	$(INSTALL_DIR) $(IDIR_POPPLER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpoppler*.so* \
		$(IDIR_POPPLER)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
