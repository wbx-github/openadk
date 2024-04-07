# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		dropbear
PKG_VERSION:=		2024.84
PKG_RELEASE:=		1
PKG_HASH:=		16e22b66b333d6b7e504c43679d04ed6ca30f2838db40a21f935c850dfc01009
PKG_DESCR:=		ssh server/client designed for embedded systems
PKG_SECTION:=		net/security
PKG_URL:=		http://matt.ucc.asn.au/dropbear/
PKG_SITES:=		http://matt.ucc.asn.au/dropbear/releases/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

PKG_SUBPKGS:=		DROPBEAR DBCONVERT
PKGSD_DBCONVERT:=	utility for converting ssh private keys

PKG_FLAVOURS_DROPBEAR:=	WITH_UTMP
PKGFD_WITH_UTMP:=	support writing /var/run/utmp

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DROPBEAR,dropbear,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,DBCONVERT,dropbearconvert,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_DBCONVERT},${PKG_SECTION}))

TARGET_CFLAGS+=		-fPIC

BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual
CONFIGURE_ARGS+=	--disable-pam \
			--enable-openpty \
			--enable-syslog \
			--enable-shadow \
			--disable-lastlog \
			--disable-utmpx \
			--disable-wtmp \
			--disable-wtmpx \
			--disable-loginfunc \
			--disable-pututxline \
			--disable-harden \
			--disable-zlib
ifeq (${ADK_PACKAGE_DROPBEAR_WITH_UTMP},)
CONFIGURE_ARGS+=	--disable-utmp --disable-pututline
else
CONFIGURE_ENV+=		conf_utmp_location=/var/run/utmp
endif


pre-configure:
	echo "#define DO_HOST_LOOKUP 0" >>$(WRKBUILD)/localoptions.h
	echo "#define DROPBEAR_X11FWD 1" >>$(WRKBUILD)/localoptions.h

do-build:
	cd ${WRKBUILD} && env ${MAKE_ENV} ${MAKE} \
	    PROGRAMS="dropbear dbclient dropbearkey scp" MULTI=1 SCPPROGRESS=1
	cd ${WRKBUILD} && env ${MAKE_ENV} ${MAKE} \
	    PROGRAMS=dropbearconvert

do-install:
	# main package
	$(INSTALL_DIR) $(IDIR_DROPBEAR)/etc/dropbear
	$(INSTALL_DIR) $(IDIR_DROPBEAR)/bin
	$(INSTALL_DIR) $(IDIR_DROPBEAR)/usr/bin
	$(INSTALL_DIR) $(IDIR_DROPBEAR)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/dropbearmulti \
		$(IDIR_DROPBEAR)/usr/sbin/dropbear
	ln -sf ../usr/sbin/dropbear $(IDIR_DROPBEAR)/bin/scp
	ln -sf ../usr/sbin/dropbear $(IDIR_DROPBEAR)/bin/ssh
	ln -sf ../sbin/dropbear $(IDIR_DROPBEAR)/usr/bin/dbclient
	ln -sf ../sbin/dropbear $(IDIR_DROPBEAR)/usr/bin/dropbearkey
	# subpackage dropbearconvert
	$(INSTALL_DIR) $(IDIR_DBCONVERT)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/dropbearconvert \
		$(IDIR_DBCONVERT)/usr/bin/dropbearconvert
	# ssh pubkey
	test -z $(ADK_RUNTIME_SSH_PUBKEY) || ( \
		$(INSTALL_DIR) $(IDIR_DROPBEAR)/root/.ssh; \
		echo $(ADK_RUNTIME_SSH_PUBKEY) \
		>$(IDIR_DROPBEAR)/root/.ssh/authorized_keys; \
        )

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
