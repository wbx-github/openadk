# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		monit
PKG_VERSION:=		5.33.0
PKG_RELEASE:=		1
PKG_HASH:=		1ace889c0183473a9d70160df6533bb6e1338dc1354f5928507803e1e2a863b5
PKG_DESCR:=		utility for system services monitoring
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libressl zlib
PKG_BUILDDEP:=		libressl zlib
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
