# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libhugetlbfs
PKG_VERSION:=		2.24
PKG_RELEASE:=		1
PKG_HASH:=		d501dfa91c8ead1106967a3d3829f2ba738c3fac0a65cb358ed2ab3870ddc5ef
PKG_DESCR:=		easy hugepage access
PKG_SECTION:=		libs/misc
PKG_URL:=		http://libhugetlbfs.ozlabs.org/
PKG_SITES:=		https://github.com/libhugetlbfs/libhugetlbfs/releases/download/$(PKG_VERSION)/
PKG_OPTS:=		dev

PKG_ARCH_DEPENDS:=	x86 x86_64
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBHUGETLBFS,libhugetlbfs,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf

XAKE_FLAGS+=		V=1 PREFIX=/usr DESTDIR=${WRKINST} ARCH=${ADK_TARGET_CPU_ARCH} BUILDTYPE=NATIVEONLY
ALL_TARGET:=		libs tools

libhugetlbfs-install:
	$(INSTALL_DIR) $(IDIR_LIBHUGETLBFS)/usr/{bin,lib,share/libhugetlbfs/ldscripts}
	$(INSTALL_BIN) $(WRKINST)/usr/bin/{huge{adm,ctl,edit},pagesize} \
		$(IDIR_LIBHUGETLBFS)/usr/bin
	${INSTALL_DATA} ${WRKINST}/usr/lib*/libhugetlbfs* \
		${IDIR_LIBHUGETLBFS}/usr/lib
	${INSTALL_BIN} ${WRKINST}/usr/share/libhugetlbfs/ld.hugetlbfs \
		${IDIR_LIBHUGETLBFS}/usr/share/libhugetlbfs
	${INSTALL_DATA} ${WRKINST}/usr/share/libhugetlbfs/ldscripts/* \
		${IDIR_LIBHUGETLBFS}/usr/share/libhugetlbfs/ldscripts
	${CP} ${WRKINST}/usr/share/libhugetlbfs/ld \
		${IDIR_LIBHUGETLBFS}/usr/share/libhugetlbfs

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
