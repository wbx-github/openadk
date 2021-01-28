# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		clamav
PKG_VERSION:=		0.103.0
PKG_RELEASE:=		1
PKG_HASH:=		32a9745277bfdda80e77ac9ca2f5990897418e9416880f3c31553ca673e80546
PKG_DESCR:=		anti-virus software
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libressl zlib libpcre libncurses libcurl libmspack
PKG_BUILDDEP:=		libressl zlib pcre ncurses curl libmspack
PKG_NEEDS:=		c++ threads
PKG_URL:=		http://www.clamav.net/
PKG_SITES:=		http://www.clamav.net/downloads/production/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CLAMAV,clamav,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

TARGET_LDFLAGS+=	-ltinfo
CONFIGURE_ENV+=		ac_cv_c_mmap_private=yes
CONFIGURE_ARGS+=	--enable-mempool \
			--with-system-libmspack \
			--disable-xml \
			--disable-check \
			--with-openssl="$(STAGING_TARGET_DIR)/usr" \
			--with-pcre="$(STAGING_TARGET_DIR)/usr"

clamav-install:
	$(INSTALL_DIR) $(IDIR_CLAMAV)/etc
	$(CP) $(WRKINST)/etc/* \
		$(IDIR_CLAMAV)/etc
	$(INSTALL_DIR) $(IDIR_CLAMAV)/usr/lib
	$(CP) $(WRKINST)/usr/lib*/lib*.so* \
		$(IDIR_CLAMAV)/usr/lib
	$(INSTALL_DIR) $(IDIR_CLAMAV)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_CLAMAV)/usr/bin
	$(INSTALL_DIR) $(IDIR_CLAMAV)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/clamd \
		$(IDIR_CLAMAV)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
