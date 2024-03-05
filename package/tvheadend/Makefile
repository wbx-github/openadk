# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tvheadend
PKG_VERSION:=		a9c6db8acbd85297238771b8b4430435b7994928
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_DESCR:=		tv streaming server
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		libressl
PKG_BUILDDEP:=		libressl yasm-host ffmpeg
PKG_URL:=		https://tvheadend.org/projects/tvheadend
PKG_SITES:=		https://github.com/tvheadend/tvheadend.git

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TVHEADEND,tvheadend,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

ifeq ($(ADK_TARGET_LIB_UCLIBC_NG),y)
XAKE_FLAGS+=		LDLIBS=-liconv
endif

CONFIGURE_ARGS+=	--disable-bundle \
			--disable-ffmpeg_static \
			--disable-execinfo \
			--disable-libvpx \
			--disable-libx264 \
			--disable-libx265 \
			--nowerror

tvheadend-install:
	$(INSTALL_DIR) $(IDIR_TVHEADEND)/usr/bin
	$(INSTALL_DIR) $(IDIR_TVHEADEND)/usr/share
	$(INSTALL_BIN) $(WRKINST)/usr/bin/tvheadend \
		$(IDIR_TVHEADEND)/usr/bin
	$(CP) $(WRKINST)/usr/share/tvheadend \
		$(IDIR_TVHEADEND)/usr/share

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
