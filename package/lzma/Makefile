# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lzma
PKG_VERSION:=		4.65
PKG_RELEASE:=		1
PKG_HASH:=		dcbdb5f4843eff638e4a5e8be0e2486a3c5483df73c70823618db8e66f609ec2
PKG_DESCR:=		compression utility
PKG_SECTION:=		app/archive
PKG_NEEDS:=		c++
PKG_URL:=		http://tukaani.org/lzma/
PKG_SITES:=		http://tukaani.org/lzma/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LZMA,lzma,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,LZMA,lzma,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_STYLE:=		manual

host-build:
	(cd $(WRKBUILD) && $(MAKE) -C C/LzmaUtil -f makefile.gcc)
	(cd $(WRKBUILD) && $(MAKE) -C CPP/7zip/Compress/LZMA_Alone -f makefile.gcc)

lzma-hostinstall:
	$(INSTALL_BIN) $(WRKBUILD)/CPP/7zip/Compress/LZMA_Alone/lzma \
		$(STAGING_HOST_DIR)/usr/bin

lzma-install:
	$(INSTALL_DIR) $(IDIR_LZMA)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/lzma $(IDIR_LZMA)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
