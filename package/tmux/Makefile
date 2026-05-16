# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tmux
PKG_VERSION:=		3.6a
PKG_RELEASE:=		1
PKG_HASH:=		b6d8d9c76585db8ef5fa00d4931902fa4b8cbe8166f528f44fc403961a3f3759
PKG_DESCR:=		terminal multiplexer
PKG_SECTION:=		sys/utils
PKG_BUILDDEP:=		libevent ncurses
PKG_DEPENDS:=		libevent libncurses
PKG_NEEDS:=		threads locale
PKG_URL:=		http://tmux.github.io
PKG_SITES:=		https://github.com/tmux/tmux/releases/download/$(PKG_VERSION)/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TMUX,tmux,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

#AUTOTOOL_STYLE:=	autoreconf

tmux-install:
	$(INSTALL_DIR) $(IDIR_TMUX)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/tmux \
		$(IDIR_TMUX)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
