# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mailutils
PKG_VERSION:=		3.21
PKG_RELEASE:=		1
PKG_HASH:=		e47c1edc699b8d6675fdbc77db3a84ae837f18e1f2094fe29d48bb58a97ef5e9
PKG_DESCR:=		mail program
PKG_SECTION:=		net/mail
PKG_BUILDDEP:=		readline
PKG_DEPENDS:=		libreadline
PKG_URL:=		http://mailutils.org/
PKG_SITES:=		https://ftp.gnu.org/gnu/mailutils/

PKG_LIBC_DEPENDS:=	glibc musl

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MAILUTILS,mailutils,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--without-fribidi

mailutils-install:
	$(INSTALL_DIR) $(IDIR_MAILUTILS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mail \
		$(IDIR_MAILUTILS)/usr/bin
	$(INSTALL_DIR) $(IDIR_MAILUTILS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmailutils*so* \
		$(IDIR_MAILUTILS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmu*so* \
		$(IDIR_MAILUTILS)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
