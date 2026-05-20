# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		elfutils
PKG_VERSION:=		0.195
PKG_RELEASE:=		1
PKG_HASH:=		37629fdf7f1f3dc2818e138fca2b8094177d6c2d0f701d3bb650a561218dc026
PKG_DESCR:=		libraries/utilities to handle elf objects (drop in replacement for libelf)
PKG_SECTION:=		base/libs
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_BUILDDEP_UCLIBC_NG:=musl-obstack
PKG_NEEDS:=		intl
PKG_SITES:=		https://sourceware.org/elfutils/ftp/$(PKG_VERSION)/

# require argp()
PKG_LIBC_DEPENDS:=	glibc uclibc-ng

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ELFUTILS,elfutils,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

# not only because we pass -DNDEBUG, this package won't build with -Werror
TARGET_CFLAGS+=		-Wno-error

CONFIGURE_ARGS+=	--disable-symbol-versioning \
			--disable-debuginfod \
			--disable-libdebuginfod \
			--disable-demangler

elfutils-install:
	$(INSTALL_DIR) $(IDIR_ELFUTILS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib{asm,dw,elf}*.so* \
		$(IDIR_ELFUTILS)/usr/lib
	$(INSTALL_DIR) $(IDIR_ELFUTILS)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_ELFUTILS)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
