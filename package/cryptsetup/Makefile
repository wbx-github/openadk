# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		cryptsetup
PKG_VERSION:=		2.4.1
PKG_RELEASE:=		1
PKG_HASH:=		a356a727a83a464ade566e95239622a22dbe4e0f482b198fdb04ab0d3a5a9c5f
PKG_DESCR:=		utility used to conveniently setup disk encryption
PKG_SECTION:=		app/crypto
PKG_DEPENDS:=		libgcrypt device-mapper libuuid libpopt json-c libncurses
PKG_BUILDDEP:=		libgcrypt popt e2fsprogs lvm json-c ncurses
PKG_NEEDS:=		iconv
PKG_KDEPENDS:=		crypto-user-api-hash crypto-user-api-skcipher
PKG_KDEPENDS+=		crypto-user-api-rng crypto-user-api-aead
# these are the default algorithms used by older and newer cryptsetup versions
PKG_KDEPENDS+=		dm-crypt crypto-essiv crypto-cbc crypto-xts
PKG_KDEPENDS+=		crypto-aes crypto-sha1 crypto-sha256
PKG_URL:=		https://gitlab.com/cryptsetup/cryptsetup
PKG_SITES:=		https://www.kernel.org/pub/linux/utils/cryptsetup/v2.4/
PKG_OPTS:=		dev

PKG_FLAVOURS_CRYPTSETUP:=	WITH_LIBARGON2
PKGFD_WITH_LIBARGON2:=		use libargon2 instead of the slow internal one
PKGFS_WITH_LIBARGON2:=		libargon2
PKGFB_WITH_LIBARGON2:=		libargon2
PKGFX_WITH_LIBARGON2:=		y

PKG_CHOICES_CRYPTSETUP:=	WITH_GCRYPT WITH_KERNEL WITH_NETTLE WITH_OPENSSL
PKGCD_WITH_GCRYPT:=		use libgcrypt crypto backend
PKGCS_WITH_GCRYPT:=		libgcrypt libgpg-error
PKGCB_WITH_GCRYPT:=		libgcrypt libgpg-error
PKGCD_WITH_KERNEL:=		use kernel user API crypto backend (slow)
PKGCD_WITH_NETTLE:=		use libnettle crypto backend
PKGCS_WITH_NETTLE:=		libnettle
PKGCB_WITH_NETTLE:=		libnettle
PKGCD_WITH_OPENSSL:=		use OpenSSL crypto backend
PKGCS_WITH_OPENSSL:=		libressl
PKGCB_WITH_OPENSSL:=		libressl

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,CRYPTSETUP,${PKG_NAME},${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-selinux \
			--disable-ssh-token \
			--disable-udev \
			--disable-nls \
			--enable-libargon2

ifeq (${ADK_PACKAGE_CRYPTSETUP_WITH_GCRYPT},y)
CONFIGURE_ARGS+=	--with-crypto_backend=gcrypt
endif
ifeq (${ADK_PACKAGE_CRYPTSETUP_WITH_KERNEL},y)
CONFIGURE_ARGS+=	--with-crypto_backend=kernel
endif
ifeq (${ADK_PACKAGE_CRYPTSETUP_WITH_NETTLE},y)
CONFIGURE_ARGS+=	--with-crypto_backend=nettle
endif
ifeq (${ADK_PACKAGE_CRYPTSETUP_WITH_OPENSSL},y)
CONFIGURE_ARGS+=	--with-crypto_backend=openssl
endif

cryptsetup-install:
	${INSTALL_DIR} ${IDIR_CRYPTSETUP}/usr/sbin ${IDIR_CRYPTSETUP}/usr/lib
	${CP} ${WRKINST}/usr/lib/libcryptsetup.so* \
		${IDIR_CRYPTSETUP}/usr/lib
	${INSTALL_BIN} ${WRKINST}/usr/sbin/cryptsetup \
		${IDIR_CRYPTSETUP}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
