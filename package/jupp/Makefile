# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		jupp
PKG_VERSION:=		41
PKG_RELEASE:=		1
PKG_HASH:=		7bb8ea8af519befefff93ec3c9e32108d7f2b83216c9bc7b01aef5098861c82f
PKG_DESCR:=		wordstar-inspired text editor
PKG_SECTION:=		app/editor
PKG_URL:=		https://www.mirbsd.org/jupp.htm
PKG_SITES:=		${MASTER_SITE_MIRBSD:distfiles/=dist/jupp/}
DISTFILES:=		joe-3.1jupp${PKG_VERSION}.tgz

PKG_CFLINE_JUPP:=	depends on ADK_BROKEN

WRKDIST=		${WRKDIR}/jupp

PKG_FLAVOURS_JUPP:=	CURSES EXTRAS JOE
PKGFD_CURSES:=		use ncurses for terminal control
PKGFS_CURSES:=		libncurses
PKGFB_CURSES:=		ncurses
PKGFD_EXTRAS:=		add syntax highlighting, charmaps
PKGFD_JOE:=		add jmacs, joe, jpico, jstar, rjoe

include ${ADK_TOPDIR}/mk/package.mk
$(eval $(call PKG_template,JUPP,jupp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

XAKE_FLAGS+=		sysconfjoesubdir=/jupp

# not available
CONFIGURE_ARGS+=	--disable-selinux

ifneq (${ADK_PACKAGE_JUPP_CURSES},y)
# disable curses/termcap support
CONFIGURE_ARGS+=	--disable-curses --disable-termcap --disable-terminfo
endif

# necessary workaround for GNU libc
ifeq (${ADK_TARGET_LIB_GLIBC},y)
CONFIGURE_ARGS+=	--disable-getpwnam
endif

# unneeded
CONFIGURE_ARGS+=	--disable-termidx

jupp-install:
	${INSTALL_DIR} ${IDIR_JUPP}/usr/bin
	${CP} ${WRKINST}/usr/bin/joe ${IDIR_JUPP}/usr/bin/jupp
ifneq (${ADK_PACKAGE_JUPP_EXTRAS}${ADK_PACKAGE_JUPP_JOE},)
	${INSTALL_DIR} ${IDIR_JUPP}/etc/jupp
endif
ifeq (${ADK_PACKAGE_JUPP_EXTRAS},y)
	${CP} ${WRKINST}/etc/jupp/jupprc ${IDIR_JUPP}/etc/jupp/
	${INSTALL_DIR} ${IDIR_JUPP}/etc/jupp/charmaps
	${INSTALL_DIR} ${IDIR_JUPP}/etc/jupp/syntax
	${CP} ${WRKINST}/etc/jupp/charmaps/* ${IDIR_JUPP}/etc/jupp/charmaps/
	${CP} ${WRKINST}/etc/jupp/syntax/* ${IDIR_JUPP}/etc/jupp/syntax/
endif
ifeq (${ADK_PACKAGE_JUPP_JOE},y)
	for x in jmacs joe jpico jstar rjoe; do \
		ln -s jupp ${IDIR_JUPP}/usr/bin/$$x; \
		${CP} ${WRKINST}/etc/jupp/$${x}rc ${IDIR_JUPP}/etc/jupp/; \
	done
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
