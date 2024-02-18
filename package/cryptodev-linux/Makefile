# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		cryptodev-linux
PKG_VERSION:=		5e7121e45ff283d30097da381fd7e97c4bb61364
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_DESCR:=		device that allows access to kernel cryptographic drivers
PKG_SECTION:=		app/crypto
PKG_DEPENDS:=		libressl
PKG_BUILDDEP:=		libressl
PKG_KDEPENDS:=		crypto-aead crypto-algapi crypto-manager
PKG_URL:=		http://home.gna.org/cryptodev-linux/
PKG_SITES:=		https://github.com/cryptodev-linux/cryptodev-linux.git

include $(ADK_TOPDIR)/mk/package.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS)-ver.mk
include ${ADK_TOPDIR}/mk/kernel-vars.mk

$(eval $(call PKG_template,CRYPTODEV_LINUX,cryptodev-linux,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

XAKE_FLAGS+=		CRYPTODEV_CFLAGS='-DENABLE_ASYNC'

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-build:
	${MAKE} -C "${WRKBUILD}"/tests check
	${MAKE} -C "${WRKBUILD}" version.h
	LDFLAGS="" ${MAKE} -C ${LINUX_DIR} ${KERNEL_MAKE_OPTS} M="${WRKBUILD}" modules
	${INSTALL_DIR} ${WRKINST}/usr/include/crypto
	${INSTALL_DATA} ${WRKBUILD}/crypto/cryptodev.h \
		${WRKINST}/usr/include/crypto/

do-install:
	${INSTALL_DIR} ${IDIR_CRYPTODEV_LINUX}/usr/bin
	for i in cipher cipher-aead hmac speed async_cipher async_hmac \
		async_speed sha_speed hashcrypt_speed fullspeed cipher-gcm \
		cipher-aead-srtp cipher_comp hash_comp hmac_comp; do \
		$(INSTALL_BIN) ${WRKBUILD}/tests/$$i ${IDIR_CRYPTODEV_LINUX}/usr/bin; \
	done
	${INSTALL_DIR} ${IDIR_CRYPTODEV_LINUX}/usr/include/crypto
	${INSTALL_DATA} ${WRKBUILD}/crypto/cryptodev.h \
		${IDIR_CRYPTODEV_LINUX}/usr/include/crypto/
	${INSTALL_DIR} ${IDIR_CRYPTODEV_LINUX}/etc/modules.d/
	echo "cryptodev" > ${IDIR_CRYPTODEV_LINUX}/etc/modules.d/90-cryptodev
	${INSTALL_DIR} ${IDIR_CRYPTODEV_LINUX}/lib/modules/${KERNEL_VERSION}/
	$(INSTALL_DATA)	$(WRKBUILD)/cryptodev.ko \
		$(IDIR_CRYPTODEV_LINUX)/lib/modules/${KERNEL_VERSION}/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
