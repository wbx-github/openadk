# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		opkg
PKG_VERSION:=		0.6.3
PKG_RELEASE:=		1
PKG_HASH:=		f3938e359646b406c40d5d442a1467c7e72357f91ab822e442697529641e06de
PKG_DESCR:=		embedded package manager
PKG_DEPENDS:=		libcurl libarchive gpgme libressl bzip2
PKG_BUILDDEP:=		curl libarchive gpgme bzip2 libressl
HOST_BUILDDEP:=		libarchive-host curl-host cpio-host
PKG_NEEDS:=		threads
PKG_SECTION:=		sys/misc
PKG_URL:=		http://git.yoctoproject.org/cgit/cgit.cgi/opkg/
PKG_SITES:=		http://downloads.yoctoproject.org/releases/opkg/

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,OPKG,opkg,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,OPKG,opkg,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_CONFIGURE_ARGS+=	--disable-openssl \
			--disable-gpg \
			--disable-xz \
			--disable-ssl-curl
CONFIGURE_ARGS+=	--enable-bzip2 \
			--enable-ssl-curl \
			--enable-openssl \
			--disable-xz \
			--enable-gpg

opkg-install:
	$(INSTALL_DIR) $(IDIR_OPKG)/usr/bin
	$(INSTALL_DIR) $(IDIR_OPKG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libopkg.so* \
		$(IDIR_OPKG)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/bin/opkg* \
		$(IDIR_OPKG)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
