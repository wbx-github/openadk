# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		openssl
PKG_VERSION:=		3.0.13
PKG_RELEASE:=		1
PKG_HASH:=		88525753f79d3bec27d2fa7c66aa0b92b3aa9498dafd93d7cfa4b3780cdae313
PKG_DESCR:=		ssl/tls library
PKG_SECTION:=		libs/crypto
PKG_URL:=		https://www.openssl.org
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_SITES:=		https://www.openssl.org/source/
PKG_LIBNAME:=		libopenssl
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		LIBOPENSSL OPENSSL_UTIL
PKGSD_OPENSSL_UTIL:=	openssl command line tool
PKGSC_OPENSSL_UTIL:=	app/crypto
PKGSS_OPENSSL_UTIL:=	libopenssl


include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,OPENSSL,openssl,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBOPENSSL,libopenssl,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},$(PKG_OPTS)))
$(eval $(call PKG_template,OPENSSL_UTIL,openssl-util,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_OPENSSL_UTIL},${PKGSD_OPENSSL_UTIL},${PKGSC_OPENSSL_UTIL}))

ifeq ($(ADK_TARGET_USE_STATIC_LIBS),y)
OPENSSL_OPTIONS:=	no-shared zlib no-dso
else
OPENSSL_OPTIONS:=	shared zlib-dynamic
endif

OPENSSL_OPTIONS+=	threads no-err no-tests no-fuzz-libfuzzer no-fuzz-afl 
OPENSSL_OPTIONS+=	no-rc5 no-rc2 no-rc4 no-md2 no-idea

HOST_STYLE:=		manual
CONFIG_STYLE:=		manual

INSTALL_TARGET:=	install_sw
FAKE_FLAGS+=		INSTALL_PREFIX=${WRKINST}

ifeq ($(ADK_TARGET_ARCH_MICROBLAZE),y)
TARGET_CFLAGS:=		$(subst g3,g,$(TARGET_CFLAGS))
endif
ifeq ($(ADK_TARGET_ARCH_XTENSA),y)
TARGET_CFLAGS:=		$(subst g3,g,$(TARGET_CFLAGS))
endif
ifeq ($(ADK_TARGET_ARCH_PPC),y)
TARGET_CFLAGS:=		$(subst g3,g,$(TARGET_CFLAGS))
endif

CONFIG:=		linux-generic32
ifeq ($(ADK_TARGET_ARCH_X86_64),y)
CONFIG:=		linux-x86_64
endif
ifeq ($(ADK_TARGET_ARCH_AARCH64),y)
CONFIG:=		linux-aarch64
endif

ifneq (,$(filter CYGWIN%,${OS_FOR_BUILD}))
HOSTCONFIG:=		Cygwin-x86_64
endif
ifeq ($(OS_FOR_BUILD),Darwin)
HOSTCONFIG:=		darwin64-x86_64-cc
endif

host-configure:
ifeq ($(HOSTCONFIG),)
	(cd $(WRKBUILD); ./config --prefix='$(STAGING_HOST_DIR)/usr' -fPIC -ldl)
else
	(cd $(WRKBUILD); ./Configure $(HOSTCONFIG) --prefix='$(STAGING_HOST_DIR)/usr')
endif

host-build:
	(cd $(WRKBUILD); make)

openssl-hostinstall:
	(cd $(WRKBUILD); make install)

do-configure:
	(cd $(WRKBUILD); \
		PATH='$(TARGET_PATH)' \
		CROSS_COMPILE='' \
		CFLAGS="$(TARGET_CFLAGS)" \
		./Configure $(CONFIG) \
			--prefix=/usr \
			--openssldir=/etc/ssl \
			-I$(STAGING_TARGET_DIR)/usr/include \
			-L$(STAGING_TARGET_DIR)/usr/lib \
			-DOPENSSL_SMALL_FOOTPRINT \
			-DOPENSSL_NO_ASYNC \
			$(OPENSSL_OPTIONS) \
		);
	#$(SED) "s:-O[0-9]:$(TARGET_CFLAGS) -fPIC:" $(WRKBUILD)/Makefile

libopenssl-install:
	${INSTALL_DIR} ${IDIR_LIBOPENSSL}/usr/lib
	${CP} ${WRKINST}/usr/lib*/lib*.so* ${IDIR_LIBOPENSSL}/usr/lib
	chmod 644 ${IDIR_LIBOPENSSL}/usr/lib/lib*.so*

openssl-util-install:
	${INSTALL_DIR} ${IDIR_OPENSSL_UTIL}/usr/bin
	${CP} ${WRKINST}/usr/bin/openssl ${IDIR_OPENSSL_UTIL}/usr/bin
	${INSTALL_DIR} ${IDIR_OPENSSL_UTIL}/etc/ssl/{,certs,private}
	${CP} ${WRKSRC}/apps/openssl.cnf ${IDIR_OPENSSL_UTIL}/etc/ssl/
	chmod 0700 ${IDIR_OPENSSL_UTIL}/etc/ssl/private

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
