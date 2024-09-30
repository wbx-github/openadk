# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		rpcbind
PKG_VERSION:=		1.2.7
PKG_RELEASE:=		1
PKG_HASH:=		f6edf8cdf562aedd5d53b8bf93962d61623292bfc4d47eedd3f427d84d06f37e
PKG_DESCR:=		converts rpc program numbers into universal addresses
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		libtirpc
PKG_BUILDDEP:=		libtirpc
PKG_URL:=		http://sourceforge.net/projects/rpcbind/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=rpcbind/}

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,RPCBIND,rpcbind,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CPPFLAGS+=	-I${STAGING_TARGET_DIR}/usr/include/tirpc
CONFIGURE_ARGS+=	--disable-libwrap \
			--without-systemdsystemunitdir \
			--with-rpcuser=root

rpcbind-install:
	$(INSTALL_DIR) $(IDIR_RPCBIND)/usr/bin
	$(INSTALL_DIR) $(IDIR_RPCBIND)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/rpcbind \
		$(IDIR_RPCBIND)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/rpcinfo \
		$(IDIR_RPCBIND)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
