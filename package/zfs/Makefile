# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		zfs
PKG_VERSION:=		2.2.6
PKG_RELEASE:=		1
PKG_HASH:=		c92e02103ac5dd77bf01d7209eabdca55c7b3356aa747bb2357ec4222652a2a7
PKG_DESCR:=		Advanced file system and volume manager
PKG_SECTION:=		sys/fs
PKG_DEPENDS:=		libcurl
PKG_URL:=		https://openzfs.org
PKG_SITES:=		https://github.com/openzfs/zfs/releases/download/${PKG_NAME}-${PKG_VERSION}/

# needs a older kernel then 6.10
PKG_CFLINE_ZFS:=	depends on ADK_BROKEN

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		ZFS ZFS_TESTS
PKGSS_ZFS_TESTS:=	bash
PKGSC_ZFS_TESTS:=	base/tests
PKGSD_ZFS_TESTS:=	OpenZFS testsuite

include $(ADK_TOPDIR)/mk/package.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS)-ver.mk
include ${ADK_TOPDIR}/mk/kernel-vars.mk

$(eval $(call PKG_template,ZFS,zfs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,ZFS_TESTS,zfs-tests,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_ZFS_TESTS),$(PKGSD_ZFS_TESTS),$(PKGSC_ZFS_TESTS)))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--with-linux=${LINUX_DIR} --without-python
CONFIGURE_ENV+=		KERNEL_CC="${TARGET_CC}" \
			KERNEL_CROSS_COMPILE="${TARGET_CROSS}" \
			KERNEL_ARCH="${ADK_TARGET_KARCH}"

zfs-install:
	$(INSTALL_DIR) $(IDIR_ZFS)/sbin
	$(INSTALL_BIN) $(WRKINST)/sbin/mount.zfs $(IDIR_ZFS)/sbin
	$(INSTALL_DIR) $(IDIR_ZFS)/etc/zfs/zed.d
	$(CP) $(WRKINST)/etc/zfs/zed.d/* $(IDIR_ZFS)/etc/zfs/zed.d
	$(CP) $(WRKINST)/etc/zfs/zfs-functions $(IDIR_ZFS)/etc/zfs
	$(INSTALL_DIR) $(IDIR_ZFS)/etc/zfs/zpool.d
	$(CP) $(WRKINST)/etc/zfs/zpool.d/* $(IDIR_ZFS)/etc/zfs/zpool.d
	$(INSTALL_DIR) $(IDIR_ZFS)/lib/modules/${KERNEL_VERSION}/
	$(CP) $(WRKINST)/lib/modules/${KERNEL_VERSION}/extra/{zfs,spl}.ko \
		$(IDIR_ZFS)/lib/modules/${KERNEL_VERSION}/
	$(INSTALL_DIR) $(IDIR_ZFS)/etc/modules.d/
	printf "spl\nzfs\n" >$(IDIR_ZFS)/etc/modules.d/2-zfs
	$(INSTALL_DIR) $(IDIR_ZFS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* $(IDIR_ZFS)/usr/bin
	$(INSTALL_DIR) $(IDIR_ZFS)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/* $(IDIR_ZFS)/usr/sbin
	$(INSTALL_DIR) $(IDIR_ZFS)/usr/libexec/zfs/zed.d
	$(INSTALL_BIN) $(WRKINST)/usr/libexec/zfs/zed.d/* \
		$(IDIR_ZFS)/usr/libexec/zfs/zed.d/
	$(INSTALL_DIR) $(IDIR_ZFS)/usr/libexec/zfs/zpool.d
	$(INSTALL_BIN) $(WRKINST)/usr/libexec/zfs/zpool.d/* \
		$(IDIR_ZFS)/usr/libexec/zfs/zpool.d/
	$(INSTALL_BIN) $(WRKINST)/usr/libexec/zfs/zpool_influxdb \
		$(IDIR_ZFS)/usr/libexec/zfs/
	$(INSTALL_DIR) $(IDIR_ZFS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/*.so* $(IDIR_ZFS)/usr/lib/

zfs-tests-install:
	$(INSTALL_DIR) $(IDIR_ZFS_TESTS)/usr/share
	$(CP) $(WRKINST)/usr/share/zfs $(IDIR_ZFS_TESTS)/usr/share/

# XXX: use /usr/share/initramfs-tools for custom init scripts
#      or just the files in root/etc/{conf,init}.d

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
