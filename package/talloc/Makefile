# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		talloc
PKG_VERSION:=		2.3.4
PKG_RELEASE:=		1
PKG_HASH:=		179f9ebe265e67e4ab2c26cad2b7de4b6a77c6c212f966903382869f06be6505
PKG_DESCR:=		memory allocation library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		python3-host python3
PKG_URL:=		https://talloc.samba.org/talloc/doc/html/index.html
PKG_SITES:=		https://www.samba.org/ftp/talloc/
PKG_LIBNAME:=		libtalloc
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBTALLOC,libtalloc,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		minimal
CONFIGURE_ARGS+=	--prefix=/usr \
			--cross-compile \
			--cross-answers=$(WRKSRC)/cache.txt \
			--hostcc=gcc

CONFIGURE_ENV+=		PYTHON_CONFIG="$(STAGING_TARGET_DIR)/usr/bin/python-config" \
			python_LDFLAGS="" \
			python_LIBDIR=""

pre-configure:
	$(CP) ./files/cache.txt $(WRKSRC)
	echo 'Checking uname machine type: "$(ADK_TARGET_ARCH)"' >>$(WRKSRC)/cache.txt

libtalloc-install:
	$(INSTALL_DIR) $(IDIR_LIBTALLOC)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libtalloc.so* \
		$(IDIR_LIBTALLOC)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
