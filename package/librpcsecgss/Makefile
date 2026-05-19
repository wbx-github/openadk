# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		librpcsecgss
PKG_VERSION:=		0.19
PKG_RELEASE:=		3
PKG_HASH:=		0cafb86b67e5eb4c89e8abaaad9165298946bc164d258e8925fc6dc1fa913abd
PKG_DESCR:=		secure rpc library for nfsv4
PKG_SECTION:=		libs/net
PKG_DEPENDS:=		libgssglue libtirpc
PKG_BUILDDEP:=		libgssglue libtirpc
PKG_SITES:=		http://www.citi.umich.edu/projects/nfsv4/linux/librpcsecgss/
PKG_OPTS:=		dev

PKG_CFLINE_LIBRPCSECGSS:=	depends on ADK_BROKEN

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_LIBC_DEPENDS:=	uclibc-ng glibc

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBRPCSECGSS,librpcsecgss,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
TARGET_CPPFLAGS+=	-I$(STAGING_TARGET_DIR)/usr/include/tirpc
TARGET_LDFLAGS+=	-ltirpc

librpcsecgss-install:
	$(INSTALL_DIR) $(IDIR_LIBRPCSECGSS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/librpcsecgss.so* $(IDIR_LIBRPCSECGSS)/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
