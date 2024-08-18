# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libssh
PKG_VERSION:=		0.11.0
PKG_RELEASE:=		1
PKG_HASH:=		860e814579e7606f3fc3db98c5807bef2ab60f793ec871d81bcd23acdcdd3e91
PKG_DESCR:=		secure shell library
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		zlib libopenssl
PKG_BUILDDEP:=		cmake-host zlib openssl
PKG_URL:=		http://www.libssh.org/
PKG_SITES:=		https://www.libssh.org/files/0.11/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSSH,libssh,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj
CONFIG_STYLE:=          cmake
CMAKE_FLAGS:=		-DOPENSSL_INCLUDE_DIR='$(STAGING_TARGET_DIR)/usr/include' \
			-DOPENSSL_LIBRARIES='-lcrypto -lssl -lz' \
			-DWITH_GSSAPI=on \
			-DWITH_SYMBOL_VERSIONING=off \
			-DWITH_EXAMPLES=off

XAKE_FLAGS+=		VERBOSE=1

libssh-install:
	$(INSTALL_DIR) $(IDIR_LIBSSH)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libssh*.so* \
		$(IDIR_LIBSSH)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
