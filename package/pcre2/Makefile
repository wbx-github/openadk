# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pcre2
PKG_VERSION:=		10.45
PKG_RELEASE:=		1
PKG_HASH:=		35ce7d21f511c4a81d7079164077d25fbc41af00f19e1b547801df905c5f0fab
PKG_DESCR:=		perl compatible regular expression library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		cmake-host
HOST_BUILDDEP:=		cmake-host
PKG_SITES:=		https://github.com/PCRE2Project/pcre2/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/$(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PCRE2,pcre2,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,PCRE2,pcre2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_CONFIG_STYLE:=	cmake
HOST_CMAKE_FLAGS+=	-DBUILD_SHARED_LIBS=ON
CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DBUILD_SHARED_LIBS=ON \
			-DPCRE2_BUILD_TESTS=OFF

pcre2-install:
	$(INSTALL_DIR) $(IDIR_PCRE2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpcre2*.so* \
		$(IDIR_PCRE2)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
