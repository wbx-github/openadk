# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		squirrel
PKG_VERSION:=		3.1
PKG_RELEASE:=		1
PKG_HASH:=		4845a7fb82e4740bde01b0854112e3bb92a0816ad959c5758236e73f4409d0cb
PKG_DESCR:=		the squirrel language	
PKG_SECTION:=		dev/lang
PKG_BUILDDEP:=		cmake-host
PKG_NEEDS:=		c++
PKG_URL:=		squirrel-lang.org
PKG_SITES:=		https://sourceforge.net/projects/squirrel/files/squirrel3/squirrel%203.1%20stable/
DISTFILES:=             $(PKG_NAME)_3_1_stable.tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)3

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SQUIRREL,squirrel,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		cmake	

squirrel-install:
	$(INSTALL_DIR) $(IDIR_SQUIRREL)/usr/bin
	$(INSTALL_DIR) $(IDIR_SQUIRREL)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/bin/sq \
		$(IDIR_SQUIRREL)/usr/bin
	$(CP) $(WRKINST)/usr/lib/libsq*.so* \
		$(IDIR_SQUIRREL)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
