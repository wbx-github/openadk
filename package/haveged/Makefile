# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		haveged
PKG_VERSION:=		1.9.18
PKG_RELEASE:=		1
PKG_HASH:=		b835fa02b52ee7d06276e028571cadcb14d08f5e5a4b5767adf81451f70561c7
PKG_DESCR:=		entropy gathering daemon
PKG_SECTION:=		sys/misc
PKG_SITES:=	 	https://github.com/jirka-h/haveged/archive/refs/tags/

PKG_ARCH_DEPENDS:=	!arm !mips

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,HAVEGED,haveged,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--enable-clock_gettime=yes

haveged-install:
	$(INSTALL_DIR) $(IDIR_HAVEGED)/usr/lib
	-$(CP) $(WRKINST)/usr/lib/libhaveg*.so* \
		$(IDIR_HAVEGED)/usr/lib
	$(INSTALL_DIR) $(IDIR_HAVEGED)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/haveged \
		$(IDIR_HAVEGED)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
