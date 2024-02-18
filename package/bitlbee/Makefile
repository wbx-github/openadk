# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		bitlbee
PKG_VERSION:=		3.6
PKG_RELEASE:=		1
PKG_HASH:=		9f15de46f29b46bf1e39fc50bdf4515e71b17f551f3955094c5da792d962107e
PKG_DESCR:=		irc gateway to im chat networks
PKG_SECTION:=		app/chat
PKG_DEPENDS:=		glib libressl
PKG_BUILDDEP:=		glib libressl
PKG_URL:=		http://www.bitlbee.org/
PKG_SITES:=		http://get.bitlbee.org/src/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,BITLBEE,bitlbee,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		minimal
TARGET_CFLAGS+=		-fPIC
CONFIGURE_ARGS:=	--target=${GNU_TARGET_NAME} \
			--prefix=/usr \
			--bindir=/usr/sbin \
			--etcdir=/etc/bitlbee \
			--datadir=/usr/share/bitlbee \
			--config=/var/lib/bitlbee \
			--arch=Linux \
			--cpu="${ADK_TARGET_ARCH}" \
			--debug=0 \
			--strip=0 \
			--ipv6=1 \
			--ssl=openssl
INSTALL_TARGET=		install-etc install-bin
XAKE_ENV+=		VERBOSE=1

post-configure:
	@echo 'CFLAGS+="-I${STAGING_TARGET_DIR}/usr/include/iconv"' >> \
		${WRKBUILD}/Makefile.settings
	@echo 'LFLAGS+=${TARGET_LDFLAGS}' >> \
		${WRKBUILD}/Makefile.settings

bitlbee-install:
	${INSTALL_DIR} ${IDIR_BITLBEE}/etc/bitlbee ${IDIR_BITLBEE}/usr/sbin
	${INSTALL_DATA} ${WRKINST}/etc/bitlbee/* ${IDIR_BITLBEE}/etc/bitlbee
	${INSTALL_BIN} ${WRKINST}/usr/sbin/bitlbee ${IDIR_BITLBEE}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
