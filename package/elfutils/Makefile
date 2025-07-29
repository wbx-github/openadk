# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		elfutils
PKG_VERSION:=		0.189
PKG_RELEASE:=		1
PKG_HASH:=		39bd8f1a338e2b7cd4abc3ff11a0eddc6e690f69578a57478d8179b4148708c8
PKG_DESCR:=		libraries/utilities to handle elf objects (drop in replacement for libelf)
PKG_SECTION:=		base/libs
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_NEEDS:=		intl
PKG_SITES:=		https://sourceware.org/elfutils/ftp/$(PKG_VERSION)/

# require argp()
PKG_LIBC_DEPENDS:=	glibc uclibc-ng

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ELFUTILS,elfutils,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

# not only because we pass -DNDEBUG, this package won't build with -Werror
TARGET_CFLAGS+=		-Wno-error

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--disable-symbol-versioning \
			--disable-debuginfod \
			--disable-libdebuginfod \
			--disable-demangler \
			--disable-progs

elfutils-install:
	$(INSTALL_DIR) $(IDIR_ELFUTILS)/usr/lib/elfutils
	$(CP) $(WRKINST)/usr/lib/lib{asm,dw,elf}*.so* \
		$(IDIR_ELFUTILS)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
