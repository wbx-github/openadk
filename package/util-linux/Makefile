# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		util-linux
PKG_VERSION:=		2.40.2
PKG_RELEASE:=		1
PKG_HASH:=		d78b37a66f5922d70edf3bdfb01a6b33d34ed3c3cafd6628203b2a2b67c8e8b3
PKG_DESCR:=		basic utilities
PKG_SECTION:=		base/apps
PKG_BUILDDEP:=		ncurses
PKG_NEEDS:=		threads
PKG_SITES:=		http://www.kernel.org/pub/linux/utils/util-linux/v2.40/
PKG_OPTS:=		dev

PKG_SUBPKGS:=		FDISK AGETTY SFDISK SWAP_UTILS LOSETUP LSFD MCOOKIE MOUNT
PKG_SUBPKGS+=		LIBFDISK LIBUUID LIBBLKID LIBMOUNT LIBSMARTCOLS CFDISK MKFS
PKGSD_LIBUUID:=		uuid library
PKGSC_LIBUUID:=		libs/misc
PKGSD_LIBBLKID:=	blkid library
PKGSC_LIBBLKID:=	libs/misc
PKGSD_LIBFDISK:=	fdisk library
PKGSC_LIBFDISK:=	libs/misc
PKGSD_LIBMOUNT:=	mount library
PKGSC_LIBMOUNT:=	libs/misc
PKGSD_LIBSMARTCOLS:=	smartcols library
PKGSC_LIBSMARTCOLS:=	libs/misc
PKGSD_FDISK:=		partition table manipulation utility
PKGSC_FDISK:=		sys/fs
PKGSS_FDISK:=		libfdisk libblkid libuuid libncurses libscmartcols
PKGSD_AGETTY:=		getty utility
PKGSC_AGETTY:=		sys/utils
PKGSS_AGETTY:=		libncurses
PKGSD_SFDISK:=		scriptable partition table manipulation utility
PKGSC_SFDISK:=		sys/fs
PKGSS_SFDISK:=		libfdisk libreadline
PKGSD_CFDISK:=		partition table manipulation utility
PKGSC_CFDISK:=		sys/fs
PKGSS_CFDISK:=		libfdisk
PKGSD_SWAP_UTILS:=	swap space management utilities
PKGSS_SWAP_UTILS:=	libblkid
PKGSC_SWAP_UTILS:=	sys/fs
PKGSD_LOSETUP:=		loop devices management utilities
PKGSC_LOSETUP:=		sys/fs
PKGSD_LSFD:=		modern lsof alternative program
PKGSC_LSFD:=		sys/utils
PKGSS_LSFD:=		libsmartcols libncurses
PKGSD_MKFS:=		filesystem creation frontend
PKGSC_MKFS:=		sys/fs
PKGSD_MOUNT:=		mount/umount utilities
PKGSS_MOUNT:=		libblkid libmount libuuid libncurses
PKGSC_MOUNT:=		sys/fs
PKGSD_MCOOKIE:=		generate magic cookies for xauth
PKGSC_MCOOKIE:=		x11/utils

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,UTIL_LINUX,util-linux,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,AGETTY,agetty,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_AGETTY),$(PKGSC_AGETTY)))
$(eval $(call PKG_template,FDISK,fdisk,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_FDISK),$(PKGSC_FDISK)))
$(eval $(call PKG_template,CFDISK,cfdisk,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_CFDISK),$(PKGSC_CFDISK)))
$(eval $(call PKG_template,SFDISK,sfdisk,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_SFDISK),$(PKGSC_SFDISK)))
$(eval $(call PKG_template,SWAP_UTILS,swap-utils,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_SWAP_UTILS),$(PKGSD_SWAP_UTILS),$(PKGSC_SWAP_UTILS)))
$(eval $(call PKG_template,LOSETUP,losetup,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_LOSETUP),$(PKGSD_LOSETUP),$(PKGSC_LOSETUP)))
$(eval $(call PKG_template,LSFD,lsfd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_LSFD),$(PKGSD_LSFD),$(PKGSC_LSFD)))
$(eval $(call PKG_template,MKFS,mkfs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_MKFS),$(PKGSD_MKFS),$(PKGSC_MKFS)))
$(eval $(call PKG_template,MOUNT,mount,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_MOUNT),$(PKGSD_MOUNT),$(PKGSC_MOUNT)))
$(eval $(call PKG_template,MCOOKIE,mcookie,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_MCOOKIE),$(PKGSC_MCOOKIE)))
$(eval $(call PKG_template,LIBUUID,libuuid,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_LIBUUID),$(PKGSC_LIBUUID),$(PKG_OPTS)))
$(eval $(call PKG_template,LIBBLKID,libblkid,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_LIBBLKID),$(PKGSC_LIBBLKID),$(PKG_OPTS)))
$(eval $(call PKG_template,LIBFDISK,libfdisk,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_LIBFDISK),$(PKGSC_LIBFDISK),$(PKG_OPTS)))
$(eval $(call PKG_template,LIBMOUNT,libmount,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_LIBMOUNT),$(PKGSC_LIBMOUNT),$(PKG_OPTS)))
$(eval $(call PKG_template,LIBSMARTCOLS,libsmartcols,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_LIBSMARTCOLS),$(PKGSC_LIBSMARTCOLS),$(PKG_OPTS)))

TARGET_CFLAGS+=		-DSWAPON_HAS_TWO_ARGS -DHAVE_LLSEEK
TARGET_LDFLAGS+=	-ltinfo

CONFIGURE_ARGS+=	--exec-prefix=/usr \
			--libdir=/usr/lib \
			--with-pic \
			--with-ncurses \
			--without-ncursesw \
			--disable-makeinstall-chown \
			--disable-makeinstall-setuid \
			--disable-widechar \
			--disable-use-tty-group \
			--disable-chfn-chsh \
			--disable-more \
			--disable-su \
			--disable-runuser \
			--disable-schedutils \
			--disable-setpriv \
			--disable-setterm \
			--disable-cramfs \
			--disable-login \
			--disable-eject \
			--disable-switch_root \
			--disable-nsenter \
			--disable-unshare \
			--disable-wall \
			--disable-liblastlog2 \
			--disable-symvers \
			--without-python \
			--without-systemd \
			--without-user \
			--enable-libfdisk \
			--enable-libuuid \
			--enable-libblkid \
			--enable-libmount

TARGET_CFLAGS+=		-fPIC
FAKE_FLAGS+=		INSTALLSUID="install -m 4755"
HOST_CONFIGURE_ARGS+=	--enable-libblkid \
			--enable-libuuid \
			--enable-libmount \
			--disable-all-programs \
			--disable-use-tty-group
ifneq ($(OS_FOR_BUILD),Darwin)
HOST_CONFIGURE_ARGS+=   --enable-libuuid
endif

fdisk-install:
	$(INSTALL_DIR) $(IDIR_FDISK)/usr/sbin
	$(CP) $(WRKINST)/sbin/fdisk $(IDIR_FDISK)/usr/sbin

agetty-install:
	$(INSTALL_DIR) $(IDIR_AGETTY)/sbin
	$(CP) $(WRKINST)/sbin/agetty $(IDIR_AGETTY)/sbin

cfdisk-install:
	$(INSTALL_DIR) $(IDIR_CFDISK)/usr/sbin
	$(CP) $(WRKINST)/sbin/cfdisk $(IDIR_CFDISK)/usr/sbin

sfdisk-install:
	$(INSTALL_DIR) $(IDIR_SFDISK)/usr/sbin
	$(CP) $(WRKINST)/sbin/sfdisk $(IDIR_SFDISK)/usr/sbin

losetup-install:
	$(INSTALL_DIR) $(IDIR_LOSETUP)/usr/sbin
	$(CP) $(WRKINST)/sbin/losetup $(IDIR_LOSETUP)/usr/sbin

lsfd-install:
	$(INSTALL_DIR) $(IDIR_LSFD)/usr/bin
	$(CP) $(WRKINST)/usr/bin/lsfd $(IDIR_LSFD)/usr/bin

swap-utils-install:
	$(INSTALL_DIR) $(IDIR_SWAP_UTILS)/usr/sbin
	$(CP) $(WRKINST)/sbin/mkswap $(IDIR_SWAP_UTILS)/usr/sbin
	$(CP) $(WRKINST)/sbin/swap{on,off} $(IDIR_SWAP_UTILS)/usr/sbin

mkfs-install:
	$(INSTALL_DIR) $(IDIR_MKFS)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/mkfs $(IDIR_MKFS)/usr/sbin

mount-install:
	$(INSTALL_DIR) $(IDIR_MOUNT)/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/{u,}mount $(IDIR_MOUNT)/bin

mcookie-install:
	$(INSTALL_DIR) $(IDIR_MCOOKIE)/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mcookie $(IDIR_MCOOKIE)/bin

libuuid-install:
	$(INSTALL_DIR) $(IDIR_LIBUUID)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libuuid.so* $(IDIR_LIBUUID)/usr/lib

libblkid-install:
	$(INSTALL_DIR) $(IDIR_LIBBLKID)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libblkid.so* $(IDIR_LIBBLKID)/usr/lib

libfdisk-install:
	$(INSTALL_DIR) $(IDIR_LIBFDISK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libfdisk.so* $(IDIR_LIBFDISK)/usr/lib

libmount-install:
	$(INSTALL_DIR) $(IDIR_LIBMOUNT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmount.so* $(IDIR_LIBMOUNT)/usr/lib

libsmartcols-install:
	$(INSTALL_DIR) $(IDIR_LIBSMARTCOLS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libsmartcols.so* $(IDIR_LIBSMARTCOLS)/usr/lib


include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
