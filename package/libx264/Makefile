# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libx264
PKG_VERSION:=		0480cb05fa188d37ae87e8f4fd8f1aea3711f7ee
PKG_RELEASE:=		1
PKG_GIT:=		hash
PKG_DESCR:=		h264 encoding library
PKG_SECTION:=		libs/video
PKG_URL:=		http://www.videolan.org/developers/x264.html
PKG_SITES:=		http://git.videolan.org/git/x264.git
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBX264,libx264,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		minimal

CONFIGURE_ARGS+=	--disable-asm \
			--disable-cli \
			--disable-opencl \
			--enable-shared \
			--prefix=/usr \
			--host=${GNU_TARGET_NAME} \
			--sysroot=${STAGING_TARGET_DIR} \
			--cross-prefix=$(TARGET_CROSS)

libx264-install:
	$(INSTALL_DIR) $(IDIR_LIBX264)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libx264*.so* \
		$(IDIR_LIBX264)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
