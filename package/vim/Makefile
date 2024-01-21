# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		vim
PKG_VERSION:=		9.1
PKG_EXTRAVER:=		0041
PKG_RELEASE:=		1
PKG_HASH:=		1531eb2f9a42e3e5a0c5579e26d9a376bd85f7062701c727af482d8597c59592
PKG_DESCR:=		very popular text editor
PKG_SECTION:=		app/editor
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://www.vim.org/
PKG_SITES:=		https://github.com/vim/vim/archive/refs/tags/

DISTFILES:=		v${PKG_VERSION}.${PKG_EXTRAVER}.tar.gz
WRKDIST=		${WRKDIR}/$(PKG_NAME)-$(PKG_VERSION).$(PKG_EXTRAVER)
WRKSRC=			${WRKDIST}/src

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,VIM,vim,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-ltinfo
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
			--without-x \
			--with-tlib=ncurses
XAKE_FLAGS+=		prefix=/usr \
			DESTDIR=${WRKINST} \
			STRIP=:

vim-install:
	${INSTALL_DIR} ${IDIR_VIM}/usr/bin
	${INSTALL_DIR} ${IDIR_VIM}/usr/share/vim
	${CP} ${WRKINST}/usr/bin/{ex,vim,view} ${IDIR_VIM}/usr/bin
	${CP} ${WRKINST}/usr/share/vim/vim91/defaults.vim \
		${IDIR_VIM}/usr/share/vim/
	${CP} ${WRKINST}/usr/share/vim/vim91/vimrc_example.vim \
		${IDIR_VIM}/usr/share/vim/vimrc

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
