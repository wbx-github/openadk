# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		afpfs-ng
PKG_VERSION:=		0.8.1
PKG_RELEASE:=		1
PKG_HASH:=		688560de1cde57ab8d9e0ef7dc6436dbf0267fe8884f9014e50ff92b297b01a8
PKG_DESCR:=		client for apple filing protocol
PKG_SECTION:=		net/fs
PKG_DEPENDS:=		libgcrypt
PKG_BUILDDEP:=		fuse libgcrypt readline
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=afpfs-ng/}
PKG_LIBNAME:=		libafpclient
PKG_OPTS:=		dev

PKG_SUBPKGS:=		AFPFS_NG LIBAFPCLIENT
PKGSD_LIBAFPCLIENT:=	afp client library
PKGSC_LIBAFPCLIENT:=	libs/net

PKG_ARCH_DEPENDS:=	!mips !mipsel

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AFPFS_NG,afpfs-ng,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBAFPCLIENT,libafpclient,$(PKG_VERSION)-${PKG_RELEASE},${PKGSS_LIBAFPCLIENT},${PKGSD_LIBAFPCLIENT},${PKGSC_LIBAFPCLIENT},$(PKG_OPTS)))

TARGET_CFLAGS+=		-fcommon
AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--enable-gcrypt
CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes

post-build:
	$(INSTALL_DIR) ${WRKINST}/usr/include/afpfs-ng
	$(CP) ${WRKBUILD}/include/*.h \
		${WRKINST}/usr/include/afpfs-ng

afpfs-ng-install:
	$(INSTALL_DIR) $(IDIR_AFPFS_NG)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_AFPFS_NG)/usr/bin

libafpclient-install:
	$(INSTALL_DIR) $(IDIR_LIBAFPCLIENT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libafpclient.so* \
		$(IDIR_LIBAFPCLIENT)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
