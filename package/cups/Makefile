# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		cups
PKG_VERSION:=		2.3.6
PKG_RELEASE:=		1
PKG_HASH:=		3a96912fc88f62c5d8ac9b251bf0652f1cbe7e69cde16919103aea39f31a1a84
PKG_DESCR:=		common unix printing system
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_NEEDS:=		threads c++ iconv
PKG_URL:=		http://www.cups.org/
PKG_SITES:=		https://github.com/apple/cups/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=		v${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,CUPS,cups,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,CUPS,cups,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

ifneq ($(ADK_HOST_LINUX),y)
HOST_LINUX_ONLY:=	1
endif

HOST_CONFIGURE_ARGS+=	--disable-tcp-wrappers \
			--disable-webif \
			--disable-gssapi \
			--disable-avahi \
			--disable-pam \
			--disable-dbus \
			--disable-gnutls \
			--disable-cdsassl \
			--disable-dbus \
			--disable-ssl \
			--disable-systemd \
			--with-components=core \
			--with-rcdir=$(STAGING_HOST_DIR)/etc
CONFIGURE_ENV+=		ac_cv_func_sigset=no \
			OPTIM='-fPIC -std=c89' LSB_BUILD=y
CONFIGURE_ARGS+=	--with-cups-user=cups \
			--with-cups-group=cups \
			--libdir=/usr/lib \
			--disable-static \
			--disable-avahi \
			--disable-webif \
			--disable-tcp-wrappers \
			--disable-gssapi \
			--disable-pam \
			--disable-dbus \
			--without-java \
			--without-perl \
			--without-python \
			--without-php \
			--disable-gnutls \
			--disable-openssl \
			--disable-cdsassl \
			--disable-dbus \
			--disable-ssl \
			--with-components=core \
			--with-rcdir=$(STAGING_TARGET_DIR)/etc

cups-install:
	${INSTALL_DIR} ${IDIR_CUPS}/usr/lib
	${CP} ${WRKINST}/usr/lib/libcups*.so* ${IDIR_CUPS}/usr/lib/

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
