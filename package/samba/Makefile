# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		samba
PKG_VERSION:=		4.13.2
PKG_RELEASE:=		1
PKG_HASH:=		276464396a05d88b775bda01ac2eb1e5a636ccf7010b0fd28efc3d85583af2b4
PKG_DESCR:=		file and print server
PKG_SECTION:=		net/fs
PKG_DEPENDS:=		libuuid libpopt libgnutls libtirpc
PKG_DEPENDS+=		libtalloc libkrb5
PKG_BUILDDEP:=		util-linux talloc p5-parse-yapp-host
PKG_NEEDS:=		threads intl
PKG_URL:=		http://www.samba.org/
PKG_SITES:=		http://samba.org/samba/ftp/stable/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SAMBA,samba,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

XAKE_ENV+=		V=1
CONFIG_STYLE:=		minimal
CONFIGURE_ARGS+=	--enable-fhs \
			--prefix=/usr \
			--sysconfdir=/etc \
			--localstatedir=/var \
			--with-privatedir=/etc/samba \
			--cross-compile \
			--cross-answers=$(WRKSRC)/cache.txt \
			--hostcc=gcc \
			--with-system-mitkrb5 \
			--without-pie \
			--without-gettext \
			--without-relro \
			--without-systemd \
			--without-automount \
			--without-pam \
			--without-fam \
			--without-dmapi \
			--without-ads \
			--without-ldap \
			--without-acl-support \
			--without-ad-dc \
			--without-json \
			--without-libarchive \
			--without-iconv \
			--disable-glusterfs \
			--disable-iprint \
			--disable-cups \
			--disable-avahi \
			--disable-rpath \
			--disable-python \
			--bundled-libraries='com_err,!asn1_compile,!compile_et' \
			--with-shared-modules=!vfs_snapper \
			--disable-rpath-install
CONFIGURE_ENV+=		PYTHON_CONFIG="$(STAGING_TARGET_DIR)/usr/bin/python-config" \
			python_LDFLAGS="" \
			python_LIBDIR="" \
			PERL="$(STAGING_HOST_DIR)/usr/bin/perl-host"

pre-configure:
	$(CP) ./files/cache.txt $(WRKSRC)
	echo 'Checking uname machine type: "$(ADK_TARGET_ARCH)"' >>$(WRKSRC)/cache.txt
ifneq ($(ADK_LINUX_64),)
	echo 'Checking for a 64-bit host to support lmdb: OK' >>$(WRKSRC)/cache.txt
else
	echo 'Checking for a 64-bit host to support lmdb: NO' >>$(WRKSRC)/cache.txt
endif

samba-install:
	$(INSTALL_DIR) $(IDIR_SAMBA)/etc/samba
	$(INSTALL_DIR) $(IDIR_SAMBA)/usr/{sbin,bin,lib}
	$(INSTALL_DATA) ./files/smb.conf $(IDIR_SAMBA)/etc/samba
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/{nmbd,smbd} \
		$(IDIR_SAMBA)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/{smbpasswd,smbclient} \
		$(IDIR_SAMBA)/usr/bin
	$(CP) $(WRKINST)/usr/lib/lib*.so* \
		$(IDIR_SAMBA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/samba \
		$(IDIR_SAMBA)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
