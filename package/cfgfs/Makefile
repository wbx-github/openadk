# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		cfgfs
PKG_VERSION:=		1.0.12
PKG_RELEASE:=		1
PKG_DESCR:=		compressed config filesystem
PKG_SECTION:=		base/adk
PKG_URL:=		http://www.openadk.org/

PKG_CFLINE_CFGFS:=	select BUSYBOX_COMM@
PKG_CFLINE_CFGFS+=	select BUSYBOX_DIFF@
PKG_CFLINE_CFGFS+=	select BUSYBOX_MD5SUM@
PKG_CFLINE_CFGFS+=	select BUSYBOX_XARGS@
PKG_CFLINE_CFGFS+=	select BUSYBOX_RDEV@
PKG_CFLINE_CFGFS+=	select BUSYBOX_SORT@
PKG_CFLINE_CFGFS+=	select BUSYBOX_FEATURE_SORT_BIG@
PKG_CFLINE_CFGFS+=	depends on !ADK_TARGET_ROOTFS_NFSROOT && !ADK_TARGET_ROOTFS_INITRAMFSPIGGYBACK && !ADK_TARGET_ROOTFS_INITRAMFS && !ADK_TARGET_ROOTFS_INITRAMFSARCHIVE && !ADK_TARGET_ROOTFS_JFFS2 && !ADK_TARGET_ROOTFS_SQUASHFS && !ADK_TARGET_ROOTFS_ISO
PKG_DFLT_CFGFS:=	y if !(ADK_APPLIANCE_TOOLCHAIN || ADK_TOOLCHAIN_ARCHIVE || ADK_PKG_TEST)

WRKDIST=		${WRKDIR}/${PKG_NAME}-${PKG_VERSION}
NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,CFGFS,cfgfs,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

# runtime problems on x86_64 with O3
TARGET_CFLAGS:=         $(subst O3,Os,$(TARGET_CFLAGS))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

do-install:
	${INSTALL_DIR} ${IDIR_CFGFS}/sbin
	${INSTALL_BIN} ${WRKBUILD}/fwcf.sh ${IDIR_CFGFS}/sbin/cfgfs
	${INSTALL_BIN} ${WRKBUILD}/fwcf.helper.out \
		${IDIR_CFGFS}/sbin/cfgfs.helper
	cd ${IDIR_CFGFS}/sbin; for tgt in halt reboot poweroff; do \
		ln cfgfs $$tgt; \
	done

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
