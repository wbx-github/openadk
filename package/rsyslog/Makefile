# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		rsyslog
PKG_VERSION:=		8.2604.0
PKG_RELEASE:=		1
PKG_HASH:=		2a04b1cd6f0a5e2b60eec231acce3cf9927c4ed02bc5fbbe5dc4c35fcf887b64
PKG_DESCR:=		syslog daemon
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libestr liblogging libfastjson libuuid zlib libncurses libgcrypt
PKG_DEPENDS+=		libcurl
PKG_BUILDDEP:=		libestr liblogging libfastjson util-linux zlib ncurses libgcrypt
PKG_BUILDDEP+=		curl
PKG_NEEDS:=		threads
PKG_URL:=		http://www.rsyslog.com/
PKG_SITES:=		https://www.rsyslog.com/files/download/rsyslog/

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,RSYSLOG,rsyslog,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes
CONFIGURE_ARGS+=	--disable-impstats-push

rsyslog-install:
	$(INSTALL_DIR) $(IDIR_RSYSLOG)/etc
	$(CP) ./files/rsyslog.conf $(IDIR_RSYSLOG)/etc
	$(INSTALL_DIR) $(IDIR_RSYSLOG)/usr/lib/rsyslog
	$(CP) $(WRKINST)/usr/lib/rsyslog/*.so \
		$(IDIR_RSYSLOG)/usr/lib/rsyslog
	$(INSTALL_DIR) $(IDIR_RSYSLOG)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/rsyslogd \
		$(IDIR_RSYSLOG)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
