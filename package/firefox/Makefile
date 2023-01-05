# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		firefox
PKG_VERSION:=		108.0.1
PKG_RELEASE:=		1
PKG_HASH:=		9821ac130dad01383e03276bf6cc92d41329d351da1fa7fa238168f8890611ea
PKG_DESCR:=		www browser
PKG_SECTION:=		app/browser
PKG_DEPENDS:=		pango libfreetype fontconfig libxcomposite libxcursor
PKG_DEPENDS+=		libgtk3 dbus-glib alsa-lib libatk harfbuzz
PKG_BUILDDEP:=		python3-host nodejs-host pango freetype fontconfig libXcomposite
PKG_BUILDDEP+=		libXcursor libgtk3 dbus-glib alsa-lib atk harfbuzz
PKG_SITES:=		https://ftp.mozilla.org/pub/firefox/releases/$(PKG_VERSION)/source/

PKG_ARCH_DEPENDS:=	aarch64

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).source.tar.xz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FIREFOX,firefox,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=		$(WRKDIR)/$(PKG_NAME)-obj

ifeq ($(ADK_TARGET_ARCH),aarch64)
TARGET_NAME:=		aarch64-linux-gnu
endif

CONFIG_STYLE:=		minimal
CONFIGURE_ENV+=		CROSS_COMPILE=1 \
			BINDGEN_CFLAGS="--sysroot /usr/$(TARGET_NAME)" \
			AS="$(GNU_TARGET_NAME)-gcc"
CONFIGURE_ARGS+=	--prefix=/usr \
			--target=$(TARGET_NAME) \
			--with-toolchain-prefix=$(GNU_TARGET_NAME)- \
			--enable-application=browser \
			--enable-official-branding \
			--disable-audio-backends \
			--without-wasm-sandboxed-libraries \
			--disable-profiling \
			--with-clang-path=/usr/bin/clang-13

firefox-install:
	$(INSTALL_DIR) $(IDIR_FIREFOX)/usr/bin
	$(INSTALL_DIR) $(IDIR_FIREFOX)/usr/lib/firefox
	$(CP) $(WRKINST)/usr/bin/firefox \
		$(IDIR_FIREFOX)/usr/bin
	$(CP) $(WRKINST)/usr/lib/firefox/* \
		$(IDIR_FIREFOX)/usr/lib/firefox

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
