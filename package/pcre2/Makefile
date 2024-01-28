# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pcre2
PKG_VERSION:=		10.42
PKG_RELEASE:=		1
PKG_HASH:=		a8e52a9bd1bca8f51c5c24823adc2a99acb12288e289a6507090c1a4a4815010
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

HOST_STYLE:=		cmake
CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DBUILD_SHARED_LIBS=ON

pcre2-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -j${ADK_MAKE_JOBS} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} ${HOST_INSTALL_TARGET}

pcre2-install:
	$(INSTALL_DIR) $(IDIR_PCRE2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpcre2*.so* \
		$(IDIR_PCRE2)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
