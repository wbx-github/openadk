# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		iptraf-ng
PKG_GIT:=		tag
PKG_HASH:=		cf385d3a0d2344f0159be0ab859651de2f750b661d88d1f22f96b82a7cd4ae13
PKG_VERSION:=		v1.2.1
PKG_RELEASE:=		1
PKG_DESCR:=		a console-based network monitoring program
PKG_SECTION:=		net/perf
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		https://github.com/iptraf-ng/iptraf-ng
PKG_SITES:=		https://github.com/iptraf-ng/iptraf-ng.git

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,IPTRAF_NG,iptraf-ng,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
TARGET_LDFLAGS+=	-ltinfo -lncurses -lpanel
XAKE_FLAGS+=		PLATFORM="-DPLATFORM=\\\"Linux/${ARCH}\\\"" \
			TARGET="/usr/bin" \
			WORKDIR="/var/lib/iptraf-ng" V=1

iptraf-ng-install:
	${INSTALL_DIR} ${IDIR_IPTRAF_NG}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/iptraf-ng ${IDIR_IPTRAF_NG}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
