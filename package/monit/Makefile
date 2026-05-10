# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		monit
PKG_VERSION:=		5.35.2
PKG_RELEASE:=		1
PKG_HASH:=		4dfef54329e63d9772a9e1c36ac99bc41173b79963dc0d8235f2c32f4b9e078f
PKG_DESCR:=		utility for system services monitoring
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libopenssl zlib
PKG_BUILDDEP:=		openssl zlib
PKG_NEEDS:=		threads
PKG_URL:=		http://mmonit.com/monit/
PKG_SITES:=		https://mmonit.com/monit/dist/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MONIT,monit,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		libmonit_cv_setjmp_available=yes \
			libmonit_cv_vsnprintf_c99_conformant=yes
CONFIGURE_ARGS+=	--with-ssl \
			--with-ssl-dir="${STAGING_TARGET_DIR}/usr" \
			--without-pam

monit-install:
	${INSTALL_DIR} ${IDIR_MONIT}/etc
	install -m0600 ${WRKBUILD}/monitrc ${IDIR_MONIT}/etc
	${INSTALL_DIR} ${IDIR_MONIT}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/monit ${IDIR_MONIT}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
