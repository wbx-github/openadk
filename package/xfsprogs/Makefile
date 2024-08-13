# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		xfsprogs
PKG_VERSION:=		6.9.0
PKG_RELEASE:=		1
PKG_HASH:=		975284783fb3fbc4e1ae640bd804d788e4237a86b07582acee86b6e48f6521b7
PKG_DESCR:=		utilities for xfs filesystems
PKG_SECTION:=		sys/fs
PKG_DEPENDS:=		libuuid libblkid libncurses libinih liburcu
PKG_BUILDDEP:=		e2fsprogs ncurses libinih liburcu
PKG_NEEDS:=		threads
PKG_URL:=		http://oss.sgi.com/projects/xfs
PKG_SITES:=		https://www.kernel.org/pub/linux/utils/fs/xfs/xfsprogs/

PKG_NOPARALLEL:=	1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,XFSPROGS,xfsprogs,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-lblkid -luuid
INSTALL_STYLE:=		manual
CONFIGURE_ARGS+=	--enable-gettext=no \
			--enable-blkid=yes \
			--with-gnu-ld
CONFIGURE_ENV+=		DEBUG=" " OPTIMIZER=" " PLATFORM=linux \
			ac_cv_header_aio_h=yes ac_cv_lib_rt_lio_listio=yes
ALL_TARGET=

do-install:
	${INSTALL_DIR} ${IDIR_XFSPROGS}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/mkfs/mkfs.xfs ${IDIR_XFSPROGS}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/repair/xfs_repair ${IDIR_XFSPROGS}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/growfs/xfs_growfs ${IDIR_XFSPROGS}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
