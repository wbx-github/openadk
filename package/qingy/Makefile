# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		qingy
PKG_VERSION:=		1.0.0
PKG_RELEASE:=		3
PKG_HASH:=		de4b4b398d5ba81ab2544729864676a04ddc6ae818b357ee09a8770293740cd3
PKG_DESCR:=		directfb getty replacement
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		directfb libncurses
PKG_BUILDDEP:=		DirectFB ncurses
PKG_NEEDS:=		threads c++
PKG_URL:=		http://qingy.sourceforge.net/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=qingy/}

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,QINGY,qingy,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-fcommon
TARGET_LDFLAGS+=	-ltinfo
CONFIGURE_ARGS+=	--disable-screen-savers \
			--disable-optimizations \
			--disable-pam \
			--disable-x-support \
			--disable-crypto

qingy-install:
	$(INSTALL_DIR) $(IDIR_QINGY)/etc/qingy/sessions
	${INSTALL_BIN} ./files/{pre,post}_GUI.sh ${IDIR_QINGY}/etc/qingy/
	${INSTALL_DATA} ./files/{settings,welcomes} ${IDIR_QINGY}/etc/qingy/
	touch ${IDIR_QINGY}/etc/qingy/sessions/.keep_me
	$(INSTALL_DIR) $(IDIR_QINGY)/usr/lib/qingy
	${CP} $(WRKINST)/usr/lib/qingy/libqingy*.so ${IDIR_QINGY}/usr/lib/qingy/
	$(INSTALL_DIR) $(IDIR_QINGY)/usr/sbin
	${INSTALL_BIN} $(WRKINST)/usr/sbin/qingy* ${IDIR_QINGY}/usr/sbin/
	$(INSTALL_DIR) $(IDIR_QINGY)/usr/share/qingy
	${CP} $(WRKINST)/usr/share/qingy/themes ${IDIR_QINGY}/usr/share/qingy

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
