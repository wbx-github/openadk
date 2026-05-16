# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		iptraf-ng
PKG_VERSION:=		1.2.2
PKG_RELEASE:=		1
PKG_HASH:=		75fd653745ea0705995c25e6c07b34252ecc2563c6a91b007a3a8c26f29cc252
PKG_DESCR:=		a console-based network monitoring program
PKG_SECTION:=		net/perf
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		https://github.com/iptraf-ng/iptraf-ng
PKG_SITES:=		https://github.com/iptraf-ng/iptraf-ng/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,IPTRAF_NG,iptraf-ng,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
XAKE_FLAGS+=		PLATFORM="-DPLATFORM=\\\"Linux/${ARCH}\\\"" \
			TARGET="/usr/bin" \
			WORKDIR="/var/lib/iptraf-ng" V=1

iptraf-ng-install:
	${INSTALL_DIR} ${IDIR_IPTRAF_NG}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/iptraf-ng ${IDIR_IPTRAF_NG}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
