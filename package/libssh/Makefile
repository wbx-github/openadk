# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libssh
PKG_VERSION:=		0.9.5
PKG_RELEASE:=		1
PKG_HASH:=		acffef2da98e761fc1fd9c4fddde0f3af60ab44c4f5af05cd1b2d60a3fa08718
PKG_DESCR:=		secure shell library
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		zlib libressl
PKG_BUILDDEP:=		cmake-host zlib libressl
PKG_URL:=		http://www.libssh.org/
PKG_SITES:=		https://www.libssh.org/files/0.9/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSSH,libssh,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj
CONFIG_STYLE:=          cmake
CMAKE_FLAGS:=		-DOPENSSL_INCLUDE_DIRS='$(STAGING_TARGET_DIR)/usr/include' \
			-DOPENSSL_LIBRARIES='-lcrypto -lssl -lz' \
			-DZLIB_INCLUDE_DIR='$(STAGING_TARGET_DIR)/usr/include' \
			-DZLIB_LIBRARY='$(STAGING_TARGET_DIR)/usr/lib' \
			-DWITH_GSSAPI=off \
			-DWITH_STACK_PROTECTOR=off \
			-DWITH_EXAMPLES=off

libssh-install:
	$(INSTALL_DIR) $(IDIR_LIBSSH)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libssh*.so* \
		$(IDIR_LIBSSH)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
