# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		procps-ng
PKG_VERSION:=		4.0.6
PKG_RELEASE:=		1
PKG_HASH:=		8476bc173508b4b9755e86e221ebee00b0f1d9d91c60432f12077f8a8b38e428
PKG_DESCR:=		/proc file system utilities
PKG_SECTION:=		base/tools
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://procps-ng.sourceforge.net/
PKG_SITES:=		https://gitlab.com/procps-ng/procps/-/archive/v$(PKG_VERSION)/
PKG_BB:=		1

DISTFILES:=		${PKG_NAME}-v${PKG_VERSION}.tar.gz

WRKDIST=		$(WRKDIR)/procps-v$(PKG_VERSION)-4dafddf4c3f4646caa517f039a2307e92657ec93

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,PROCPS_NG,procps-ng,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes

procps-ng-install:
	${INSTALL_DIR} ${IDIR_PROCPS_NG}/{bin,sbin,usr/bin}
	${INSTALL_BIN} ${WRKINST}/usr/bin/uptime ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/tload ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/free ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/w ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/top ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/vmstat ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/watch ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/pmap ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/pgrep ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/slabtop ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/pwdx ${IDIR_PROCPS_NG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/kill ${IDIR_PROCPS_NG}/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/ps ${IDIR_PROCPS_NG}/bin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/sysctl ${IDIR_PROCPS_NG}/sbin
	cd ${IDIR_PROCPS_NG}/usr/bin; \
	    ln -sf ../../bin/kill skill; \
	    ln -sf ../../bin/kill snice; \
	    ln -sf pgrep pkill

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
