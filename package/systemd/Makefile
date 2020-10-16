# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		systemd
PKG_VERSION:=		246
PKG_RELEASE:=		2
PKG_HASH:=		4268bd88037806c61c5cd1c78d869f7f20bf7e7368c63916d47b5d1c3411bd6f
PKG_DESCR:=		system and service manager
PKG_SECTION:=		base/init
PKG_DEPENDS:=		libcap libmount libuuid libblkid libncurses libkmod
PKG_BUILDDEP:=		intltool-host gperf-host libcap util-linux
PKG_BUILDDEP+=		gettext-host kmod meson-host ninja-host
PKG_KDEPENDS:=		inotify-user cgroups namespaces fhandle tmpfs-posix-acl tmpfs-xattr
PKG_KDEPENDS+=		uts-ns
PKG_NEEDS:=		locale intl
PKG_URL:=		https://wiki.freedesktop.org/www/Software/systemd/
PKG_SITES:=		https://github.com/systemd/systemd/archive/

PKG_CFLINE_SYSTEMD:=	select BUSYBOX_SULOGIN if ADK_RUNTIME_BASE_BUSYBOX
PKG_LIBC_DEPENDS:=	!musl

PKG_FLAVOURS_SYSTEMD:=	WITH_PAM WITH_XZ WITH_ZLIB
PKGFD_WITH_PAM:=	enable pam support
PKGFS_WITH_PAM:=	pam
PKGFB_WITH_PAM:=	pam
PKGFD_WITH_XZ:=		enable xz support
PKGFS_WITH_XZ:=		xz
PKGFB_WITH_XZ:=		xz
PKGFD_WITH_ZLIB:=	enable zlib support
PKGFS_WITH_ZLIB:=	zlib
PKGFB_WITH_ZLIB:=	zlib

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SYSTEMD,systemd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Drootlibdir='/usr/lib' \
			-Dman=false \
			-Dima=false \
			-Dlibcryptsetup=false \
			-Defi=false \
			-Dgnu-efi=false \
			-Dldconfig=false \
			-Ddefault-dnssec=no \
			-Dtests=false \
			-Dkill-path=/usr/bin/kill \
			-Dkmod-path=/usr/bin/kmod \
			-Dkexec-path=/usr/sbin/kexec \
			-Dsulogin-path=/usr/sbin/sulogin \
			-Dmount-path=/usr/bin/mount \
			-Dumount-path=/usr/bin/umount \
			-Dacl=false \
			-Daudit=false \
			-Didn=false \
			-Dnss-systemd=false \
			-Dmyhostname=false \
			-Dresolve=false \
			-Dseccomp=false \
			-Dxkbcommon=false \
			-Dbzip2=false \
			-Dlz4=false \
			-Dlibcurl=false \
			-Dgcrypt=false \
			-Dqrencode=false \
			-Dmicrohttpd=false \
			-Dselinux=false \
			-Dhwdb=false \
			-Dportabled=false \
			-Dbinfmt=false \
			-Dvconsole=false \
			-Dquotacheck=false \
			-Dbacklight=false \
			-Drfkill=false \
			-Dmachined=false \
			-Dimportd=false \
			-Dhostnamed=false \
			-Dlocaled=false \
			-Dcoredump=false \
			-Dsmack=false \
			-Dsysusers=false \
			-Dhibernate=false \
			-Dpolkit=false \
			-Dnetworkd=true \
			-Dtimesyncd=true \
			-Dtmpfiles=true \
			-Dnss-systemd=true \
			-Dfirstboot=true \
			-Drandomseed=true \
			-Dlogind=true \
			-Dtimedated=true


ifeq ($(ADK_PACKAGE_SYSTEMD_WITH_PAM),y)
MESON_FLAGS+=		-Dpam=true
else
MESON_FLAGS+=		-Dpam=false
endif

ifeq ($(ADK_PACKAGE_SYSTEMD_WITH_XZ),y)
MESON_FLAGS+=		-Dxz=true
else
MESON_FLAGS+=		-Dxz=false
endif

ifeq ($(ADK_PACKAGE_SYSTEMD_WITH_ZLIB),y)
MESON_FLAGS+=		-Dzlib=true
else
MESON_FLAGS+=		-Dzlib=false
endif

systemd-install:
	$(INSTALL_DIR) $(IDIR_SYSTEMD)/etc
	touch $(IDIR_SYSTEMD)/etc/machine-id
	$(CP) $(WRKINST)/etc/* \
		$(IDIR_SYSTEMD)/etc
	$(INSTALL_DIR) $(IDIR_SYSTEMD)/lib/systemd
	$(CP) $(WRKINST)/lib/systemd/* \
		$(IDIR_SYSTEMD)/lib/systemd
	$(INSTALL_DIR) $(IDIR_SYSTEMD)/usr/lib
	$(CP) $(WRKINST)/usr/lib/*.so* \
		$(IDIR_SYSTEMD)/usr/lib
	$(CP) $(WRKINST)/usr/lib/{systemd,kernel,sysctl.d,tmpfiles.d} \
		$(IDIR_SYSTEMD)/usr/lib
	$(INSTALL_DIR) $(IDIR_SYSTEMD)/sbin
	$(CP) $(WRKINST)/sbin/* \
		$(IDIR_SYSTEMD)/sbin
	$(INSTALL_DIR) $(IDIR_SYSTEMD)/bin
	$(CP) $(WRKINST)/bin/* \
		$(IDIR_SYSTEMD)/bin
	$(INSTALL_DIR) $(IDIR_SYSTEMD)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_SYSTEMD)/usr/bin
	$(INSTALL_DIR) $(IDIR_SYSTEMD)/usr/share
	$(CP) $(WRKINST)/usr/share/* \
		$(IDIR_SYSTEMD)/usr/share
	$(CP) ./files/*.network \
		$(IDIR_SYSTEMD)/etc/systemd/network
	(cd $(IDIR_SYSTEMD)/lib/systemd/system && ln -sf multi-user.target default.target)
	$(CP) $(WRKBUILD)/systemd $(IDIR_SYSTEMD)/usr/lib/systemd/
	mv $(IDIR_SYSTEMD)/lib/systemd/libsystemd-shared-246.so $(IDIR_SYSTEMD)/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
