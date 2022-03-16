# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		screen
PKG_VERSION:=		4.9.0
PKG_RELEASE:=		1
PKG_HASH:=		f9335281bb4d1538ed078df78a20c2f39d3af9a4e91c57d084271e0289c730f4
PKG_DESCR:=		window manager for the terminal session
PKG_SECTION:=		sys/utils
PKG_DEPENDS:=		libncurses libelf
PKG_BUILDDEP:=		ncurses libelf
PKG_NEEDS:=		mmu
PKG_URL:=		http://www.gnu.org/software/screen/
PKG_SITES:=		${MASTER_SITE_GNU:=screen/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SCREEN,screen,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
TARGET_LDFLAGS+=	-ltinfo
CONFIGURE_ENV+=		$(foreach flag,rename fchmod fchown strerror lstat _exit utimes vsnprintf getcwd setlocale strftime,ac_cv_func_${flag}=yes)
CONFIGURE_ARGS+=	--with-sys-screenrc=/etc/screenrc

pre-build:
	echo '#undef UTMPOK' >> ${WRKBUILD}/config.h
	echo '#undef LOGINDEFAULT' >> ${WRKBUILD}/config.h
	echo '#define LOGINDEFAULT 0' >> ${WRKBUILD}/config.h
	echo '#undef GETUTENT' >> ${WRKBUILD}/config.h
	echo '#undef UTHOST' >> ${WRKBUILD}/config.h
	echo '#undef BUGGYGETLOGIN' >> ${WRKBUILD}/config.h
	mv ${WRKBUILD}/sched.h ${WRKBUILD}/my_sched.h

screen-install:
	${INSTALL_DIR} ${IDIR_SCREEN}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/screen ${IDIR_SCREEN}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
