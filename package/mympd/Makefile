# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mympd
PKG_VERSION:=		14.0.2
PKG_RELEASE:=		1
PKG_HASH:=		309476bcc352f5b9ddc365412cb636e41b3a9e675c0ef94c17b982af2dfc3aa8
PKG_DESCR:=		standalone music player daemon web gui
PKG_SECTION:=		net/http
PKG_DEPENDS:=		mpd libopenssl pcre2
PKG_BUILDDEP:=		cmake-host libmpdclient openssl pcre2
PKG_URL:=		https://github.com/jcorporation/myMPD
PKG_SITES:=		https://github.com/jcorporation/myMPD/archive/refs/tags/

DISTFILES:=             v$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/myMPD-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MYMPD,mympd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj
CONFIG_STYLE:=		cmake
CMAKE_FLAGS:=		-DMYMPD_EMBEDDED_ASSETS=ON

mympd-install:
	$(INSTALL_DIR) $(IDIR_MYMPD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mympd \
		$(IDIR_MYMPD)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
