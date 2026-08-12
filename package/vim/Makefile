# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		vim
PKG_VERSION:=		9.2
PKG_EXTRAVER:=		0943
PKG_RELEASE:=		1
PKG_HASH:=		9b90b23241007b20ba89b7b00e6202008f4ff5b5278974d42aa199867c2eada5
PKG_DESCR:=		very popular text editor
PKG_SECTION:=		app/editor
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://www.vim.org/
PKG_SITES:=		https://github.com/vim/vim/archive/refs/tags/

PKG_FLAVOURS_VIM:=	WITH_X
PKGFD_WITH_X:=		enable Xorg support
PKGFS_WITH_X:=		libx11 libgtk3
PKGFB_WITH_X:=		libX11 libgtk3

DISTFILES:=		v${PKG_VERSION}.${PKG_EXTRAVER}.tar.gz
WRKDIST=		${WRKDIR}/$(PKG_NAME)-$(PKG_VERSION).$(PKG_EXTRAVER)
WRKSRC=			${WRKDIST}/src

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,VIM,vim,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		vim_cv_toupper_broken=no \
			vim_cv_getcwd_broken=no \
			vim_cv_stat_ignores_slash=yes \
			ac_cv_sizeof_int=4 \
			vim_cv_terminfo=yes \
			vim_cv_tgetent=zero \
			vim_cv_tty_group=tty \
			vim_cv_memmove_handles_overlap=yes \
			vim_cv_tty_mode=666
CONFIGURE_ARGS+=	--disable-darwin \
			--disable-xsmp \
			--disable-mzschemeinterp \
			--disable-perlinterp \
			--disable-pythoninterp \
			--disable-tclinterp \
			--disable-rubyinterp \
			--disable-cscope \
			--disable-netbeans \
			--disable-xim \
			--disable-fontset \
			--disable-gui \
			--disable-acl \
			--disable-gpm \
			--with-features=small \
			--with-compiledby=OpenADK \
			--with-tlib=ncursesw
XAKE_FLAGS+=		prefix=/usr \
			DESTDIR=${WRKINST} \
			STRIP=:

ifeq ($(ADK_PACKAGE_VIM_WITH_X),y)
CONFIGURE_ARGS+=	--with-x --enable-gui=gtk3
else
CONFIGURE_ARGS+=	--without-x
endif

vim-install:
	${INSTALL_DIR} ${IDIR_VIM}/usr/bin
	${INSTALL_DIR} ${IDIR_VIM}/usr/share/vim
	${CP} ${WRKINST}/usr/bin/{ex,vim,view} ${IDIR_VIM}/usr/bin
	${CP} ${WRKINST}/usr/share/vim/vim92/defaults.vim \
		${IDIR_VIM}/usr/share/vim/
	${CP} ${WRKINST}/usr/share/vim/vim92/vimrc_example.vim \
		${IDIR_VIM}/usr/share/vim/vimrc
ifeq ($(ADK_PACKAGE_VIM_WITH_X),y)
	${CP} ${WRKINST}/usr/bin/gvim ${IDIR_VIM}/usr/bin
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
