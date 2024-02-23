# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		cherokee
PKG_VERSION:=		1.2.103
PKG_RELEASE:=		1
PKG_HASH:=		7ec379bf7e9d6fdf952d91fadc43eb6ee5295119aea7d8dabbf89f2799a53ae6
PKG_DESCR:=		small and fast webserver
PKG_SECTION:=		net/http
PKG_URL:=		http://www.cherokee-project.com
PKG_SITES:=		https://github.com/cherokee/webserver/archive/

PKG_CFLINE_CHEROKEE:=	depends on ADK_BROKEN

DISTFILES:=		v${PKG_VERSION}.zip
WRKDIST=		${WRKDIR}/webserver-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CHEROKEE,cherokee,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autogen
CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes
CONFIGURE_ARGS+=	--enable-static-module=all \
			--without-mysql \
			--without-ldap \
			--disable-pam \
			--without-ffmpeg

cherokee-install:
	$(INSTALL_DIR) $(IDIR_CHEROKEE)/etc/cherokee
	$(INSTALL_DATA) ./files/cherokee.conf \
		$(IDIR_CHEROKEE)/etc/cherokee
	$(INSTALL_DIR) $(IDIR_CHEROKEE)/usr/lib/cherokee
	$(CP) $(WRKINST)/usr/lib/libcherokee*so* \
		$(IDIR_CHEROKEE)/usr/lib
	$(INSTALL_DIR) $(IDIR_CHEROKEE)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/cherokee{,-worker} \
		$(IDIR_CHEROKEE)/usr/sbin
	$(INSTALL_DIR) $(IDIR_CHEROKEE)/usr/share/cherokee/themes/default
	$(CP) $(WRKINST)/usr/share/cherokee/themes/default/* \
		$(IDIR_CHEROKEE)/usr/share/cherokee/themes/default

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
