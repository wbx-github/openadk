# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gptfdisk
PKG_VERSION:=		1.0.10
PKG_RELEASE:=		1
PKG_HASH:=		2abed61bc6d2b9ec498973c0440b8b804b7a72d7144069b5a9209b2ad693a282
PKG_DESCR:=		utilities to create gpt partition tables
PKG_SECTION:=		sys/fs
PKG_DEPENDS:=		libncurses libuuid
PKG_BUILDDEP:=		util-linux popt ncurses
HOST_BUILDDEP:=		util-linux-host popt-host
PKG_NEEDS:=		c++
PKG_URL:=		http://www.rodsbooks.com/gdisk/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=gptfdisk/}

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GPTFDISK,gptfdisk,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,GPTFDISK,gptfdisk,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS+=	-ltinfo
HOST_STYLE:=		manual
CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${ALL_TARGET})

gptfdisk-hostinstall:
	$(CP) $(WRKBUILD)/{g,sg,cg}disk \
		$(STAGING_HOST_DIR)/usr/bin

gptfdisk-install:
	$(INSTALL_DIR) $(IDIR_GPTFDISK)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/{g,sg,cg}disk $(IDIR_GPTFDISK)/usr/sbin

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
