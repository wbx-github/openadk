# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libgssglue
PKG_VERSION:=		0.9
PKG_RELEASE:=		1
PKG_HASH:=		67ed16283dc45fe6acdd71adac76acf4a8af41eb75d0bb27cbb10c6110c72601
PKG_DESCR:=		gss glue library for nfsv4
PKG_SECTION:=		libs/net
PKG_SITES:=		https://gitlab.com/-/project/37744631/uploads/7310f7060cdf240a4b8eaaf80a435986/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBGSSGLUE,libgssglue,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libgssglue-install:
	$(INSTALL_DIR) $(IDIR_LIBGSSGLUE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgssglue.so* $(IDIR_LIBGSSGLUE)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
