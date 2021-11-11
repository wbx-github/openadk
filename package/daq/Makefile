# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		daq
PKG_VERSION:=		2.0.7
PKG_RELEASE:=		1
PKG_HASH:=		d1f6709bc5dbddee3fdf170cdc1e49fb926e2031d4869ecf367a8c47efc87279
PKG_DESCR:=		data acquisition library
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libpcap libdnet
PKG_BUILDDEP:=		libpcap libdnet
PKG_URL:=		http://www.snort.org
PKG_SITES:=		https://www.snort.org/downloads/snort/
PKG_OPTS:=		dev
PKG_NOPARALLEL:=	1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DAQ,daq,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--disable-ipfw-module

daq-install:
	$(INSTALL_DIR) $(IDIR_DAQ)/usr/lib/daq
	$(CP) $(WRKINST)/usr/lib/daq/*.so \
		$(IDIR_DAQ)/usr/lib/daq
	$(CP) $(WRKINST)/usr/lib/*.so* \
		$(IDIR_DAQ)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
