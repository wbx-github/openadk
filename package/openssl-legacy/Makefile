# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		openssl-legacy
PKG_VERSION:=		1.0.2u
PKG_RELEASE:=		1
PKG_HASH:=		ecd0c6ffb493dd06707d38b14bb4d8c2288bb7033735606569d8f90f89669d16
PKG_DESCR:=		ssl/tls library (legacy)
PKG_SECTION:=		libs/crypto
PKG_URL:=		https://openssl-library.org/
PKG_SITES:=		https://github.com/openssl/openssl/releases/download/OpenSSL_1_0_2u/

DISTFILES:=             openssl-$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/openssl-$(PKG_VERSION)

PKG_CFLINE_OPENSSL_LEGACY:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,OPENSSL_LEGACY,openssl-legacy,${PKG_VERSION}-${PKG_RELEASE}))

HOST_STYLE:=		manual
INSTALL_TARGET:=	install_sw
FAKE_FLAGS+=		INSTALL_PREFIX=${WRKINST}

host-configure:
	(cd $(WRKBUILD); ./config --prefix='$(STAGING_HOST_DIR)/usr' -fPIC -ldl no-tests)

host-build:
	(cd $(WRKBUILD); $(MAKE))

openssl-legacy-hostinstall:
	(cd $(WRKBUILD); $(MAKE) install)

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
