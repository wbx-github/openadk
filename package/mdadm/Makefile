# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mdadm
PKG_VERSION:=		4.2
PKG_RELEASE:=		1
PKG_HASH:=		461c215670864bb74a4d1a3620684aa2b2f8296dffa06743f26dda5557acf01d
PKG_DESCR:=		tool for managing software raid arrays
PKG_DEPENDS:=		libudev
PKG_BUILDDEP:=		eudev
PKG_KDEPENDS:=		blk-dev-md md md-raid0 md-raid1 md-raid456
PKG_SECTION:=		sys/fs
PKG_URL:=		http://neil.brown.name/blog/mdadm
PKG_SITES:=		${MASTER_SITE_KERNEL:=utils/raid/mdadm/}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MDADM,mdadm,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
XAKE_FLAGS+=		CROSS_COMPILE="${TARGET_CROSS}" CHECK_RUN_DIR=0

mdadm-install:
	${INSTALL_DIR} ${IDIR_MDADM}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/sbin/mdadm ${IDIR_MDADM}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
