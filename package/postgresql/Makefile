# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		postgresql
PKG_VERSION:=		18.7
PKG_RELEASE:=		1
PKG_HASH:=		19c2dc7d8520e10532d082b43c36c4d2dcc6cd9e40506c6f598e7338f84bbde7
PKG_DESCR:=		postgresql database library
PKG_SECTION:=		libs/db
PKG_DEPENDS:=		icu4c
PKG_BUILDDEP:=		icu4c
PKG_NEEDS:=		locale
PKG_URL:=		http://www.postgresql.org/
PKG_SITES:=		http://ftp.postgresql.org/pub/source/v$(PKG_VERSION)/
PKG_LIBNAME:=		libpq
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBPQ,libpq,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

TARGET_CFLAGS:=		$(filter-out -ffast-math,$(TARGET_CFLAGS))

CONFIGURE_ARGS+=	--without-openssl \
			--without-pam \
			--without-perl \
			--without-python \
			--without-readline \
			--without-zlib \
			--without-bonjour \
			--without-tcl \
			--with-system-tzdata=$(STAGING_TARGET_DIR)

libpq-install:
	$(INSTALL_DIR) $(IDIR_LIBPQ)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpq.so* $(IDIR_LIBPQ)/usr/lib

post-install:
	PATH='$(HOST_PATH)' sed -e "s#@@STAGING_TARGET_DIR@@#$(STAGING_TARGET_DIR)#" \
		./files/pg_config > $(STAGING_HOST_DIR)/usr/bin/pg_config
	-rm $(STAGING_TARGET_DIR)/usr/bin/pg_config

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
