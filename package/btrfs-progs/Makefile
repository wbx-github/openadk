# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		btrfs-progs
PKG_VERSION:=		7.0
PKG_RELEASE:=		1
PKG_HASH:=		c286d6876cbcd72327a0b417e4cfd280353ec23e37b549fdbcd7800a832d9a99
PKG_DESCR:=		btrfs progs
PKG_DEPENDS:=		zstd
PKG_BUILDDEP:=		zstd
PKG_KDEPENDS:=		btrfs-fs
PKG_SECTION:=		sys/fs
PKG_SITES:=		https://mirrors.edge.kernel.org/pub/linux/kernel/people/kdave/btrfs-progs/

DISTFILES:=             $(PKG_NAME)-v$(PKG_VERSION).tar.xz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-v$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BTRFS_PROGS,btrfs-progs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes
CONFIGURE_ARGS+=	--disable-backtrace \
			--disable-documentation \
			--disable-python \
			--disable-libudev

btrfs-progs-install:
	$(INSTALL_DIR) $(IDIR_BTRFS_PROGS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libbtrfs*.so* \
		$(IDIR_BTRFS_PROGS)/usr/lib
	$(INSTALL_DIR) $(IDIR_BTRFS_PROGS)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_BTRFS_PROGS)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
