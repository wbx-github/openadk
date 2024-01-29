# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gnupg2
PKG_VERSION:=		2.4.4
PKG_RELEASE:=		1
PKG_HASH:=		67ebe016ca90fa7688ce67a387ebd82c6261e95897db7b23df24ff335be85bc6
PKG_DESCR:=		gnu privacy guard (modern)
PKG_SECTION:=		app/crypto
PKG_DEPENDS:=		libreadline libncurses libgcrypt libgpg-error libassuan
PKG_DEPENDS+=		libksba npth pinentry
PKG_BUILDDEP:=		readline ncurses libgcrypt libgpg-error libassuan
PKG_BUILDDEP+=		libksba npth
PKG_NEEDS:=		iconv
PKG_URL:=		http://www.gnupg.org/
PKG_SITES:=		ftp://ftp.gnupg.org/gcrypt/gnupg/

DISTFILES:=		gnupg-$(PKG_VERSION).tar.bz2
WRKDIST=		${WRKDIR}/gnupg-${PKG_VERSION}

PKG_SUBPKGS:=		GNUPG2 GPGV2
 
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GNUPG2,gnupg2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,GPGV2,gpgv2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--disable-dirmngr \
			--disable-gpgsm \
			--disable-scdaemon \
			--disable-card-support \
			--disable-bzip2 \
			--disable-exec \
			--disable-ldap \
			--disable-rpath \
			--disable-regex \
			--disable-tests \
			--disable-doc

gpgv2-install:
	$(INSTALL_DIR) $(IDIR_GPGV2)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/g10/gpgv \
		$(IDIR_GPGV2)/usr/bin

gnupg2-install:
	$(INSTALL_DIR) $(IDIR_GNUPG2)/usr/bin/
	$(INSTALL_BIN) $(WRKBUILD)/g10/gpg $(IDIR_GNUPG2)/usr/bin/
	$(INSTALL_BIN) $(WRKBUILD)/agent/gpg-agent $(IDIR_GNUPG2)/usr/bin/
	# we need root privileges for secure memory (locked pages)
	chmod u+s $(IDIR_GNUPG2)/usr/bin/gpg

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
