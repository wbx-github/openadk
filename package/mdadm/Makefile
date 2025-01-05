# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mdadm
PKG_VERSION:=		4.4
PKG_RELEASE:=		1
PKG_HASH:=		556266fb8322de465eff2aa7e0f7d2b1056153770c70971834833f571dbc02a2
PKG_DESCR:=		tool for managing software raid arrays
PKG_DEPENDS:=		libudev
PKG_BUILDDEP:=		eudev
PKG_KDEPENDS:=		blk-dev-md md md-raid0 md-raid1 md-raid456
PKG_SECTION:=		sys/fs
PKG_URL:=		http://neil.brown.name/blog/mdadm
PKG_SITES:=		https://github.com/md-raid-utilities/mdadm/archive/refs/tags/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/${PKG_NAME}-${PKG_NAME}-${PKG_VERSION}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MDADM,mdadm,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
# gcc-12.4.0 at least seems to get some things wrong
TARGET_CFLAGS+=		-Wno-error=uninitialized
# Without this, I get "undefined reference to `__stack_chk_fail'" while linking
TARGET_CFLAGS+=		-fno-stack-protector
XAKE_FLAGS+=		CROSS_COMPILE="${TARGET_CROSS}" \
			CHECK_RUN_DIR=0 \
			CXFLAGS="${TARGET_CFLAGS}"

mdadm-install:
	${INSTALL_DIR} ${IDIR_MDADM}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/sbin/mdadm ${IDIR_MDADM}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
