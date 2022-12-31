# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xorg-server
PKG_VERSION:=		21.1.5
PKG_RELEASE:=		1
PKG_HASH:=		05b0c8301cee7c5a78083df421ba3a071891553541a417b3d85adf5cf20f8720
PKG_DESCR:=		xorg server
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		libxfont2 pixman libpciaccess libxkbfile libxcvt
PKG_DEPENDS+=		libfontenc xkeyboard-config xkbcomp libxau libxaw
PKG_DEPENDS+=		libxmu libxpm libxrender libxt libxxf86dga libxext
PKG_DEPENDS+=		libxdmcp libxv libsm libice libx11 libxcb libdrm
PKG_DEPENDS+=		libxshmfence libfreetype libfontenc libpciaccess
PKG_DEPENDS+=		libepoxy
PKG_BUILDDEP:=		libX11 randrproto renderproto fixesproto damageproto
PKG_BUILDDEP+=		scrnsaverproto resourceproto fontsproto videoproto
PKG_BUILDDEP+=		compositeproto evieext libxkbfile libXfont2 pixman
PKG_BUILDDEP+=		libpciaccess xf86dgaproto recordproto dri3proto
PKG_BUILDDEP+=		xineramaproto presentproto xf86driproto glproto mesa
PKG_BUILDDEP+=		xorgproto libxcvt libdrm libepoxy
PKG_NEEDS:=		threads c++
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/xserver/
PKG_OPTS:=		dev

PKG_CFLINE_XORG_SERVER:=depends on ADK_TARGET_WITH_VGA || ADK_TARGET_QEMU_WITH_GRAPHIC

PKG_FLAVOURS_XORG_SERVER:=	WITH_KDRIVE
PKGFD_WITH_KDRIVE:=		build kdrive xfbdev server

PKG_CHOICES_XORG_SERVER:=	WITH_LIBRESSL WITH_GCRYPT
PKGCD_WITH_LIBRESSL:=		use libressl crypto for sha1
PKGCS_WITH_LIBRESSL:=		libressl
PKGCB_WITH_LIBRESSL:=		libressl
PKGCD_WITH_GCRYPT:=		use libgcrypt for sha1
PKGCS_WITH_GCRYPT:=		libgcrypt
PKGCB_WITH_GCRYPT:=		libgcrypt

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XORG_SERVER,xorg-server,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_CPPFLAGS+=	-D_GNU_SOURCE -D__gid_t=gid_t -D__uid_t=uid_t

ifeq (${ADK_PACKAGE_XORG_SERVER_WITH_GCRYPT},y)
CONFIGURE_ARGS+=	 --with-sha1=libgcrypt
endif

ifeq (${ADK_PACKAGE_XORG_SERVER_WITH_LIBRESSL},y)
CONFIGURE_ARGS+=	 --with-sha1=libcrypto
endif

CONFIGURE_ENV+=		V=1
CONFIGURE_ARGS+=	--enable-dga \
			--enable-xorg \
			--enable-xv \
			--enable-vgahw \
			--enable-dpms \
			--enable-xinerama \
			--disable-docs \
			--disable-glamor \
			--disable-config-hal \
			--disable-config-udev \
			--disable-xace \
			--disable-xephyr \
			--disable-xf86bigfont \
			--disable-xf86vidmode \
			--disable-xnest \
			--disable-xselinux \
			--disable-xcsecurity \
			--disable-xvfb \
			--disable-xvmc \
			--disable-selective-werror \
			--disable-strict-compilation \
			--enable-dri \
			--enable-dri2 \
			--enable-dri3 \
			--enable-glx \
			--enable-glamor \
			--with-xkb-output=/tmp \
			--with-vendor-web="$(ADK_VENDOR_URL)"

ifeq (${ADK_PACKAGE_XORG_SERVER_WITH_KDRIVE},y)
CONFIGURE_ARGS+=	--enable-kdrive --enable-kdrive-kbd --enable-kdrive-mouse --enable-kdrive-evdev
else
CONFIGURE_ARGS+=	--disable-kdrive
endif

ifeq (${ADK_TARGET_SYSTEM_LEMOTE_YEELONG},y)
CONFIGURE_ARGS+=	--with-int10=stub
endif

xorg-server-install:
	$(INSTALL_DIR) $(IDIR_XORG_SERVER)/etc/X11
	$(INSTALL_DIR) $(IDIR_XORG_SERVER)/usr/bin
	$(INSTALL_DIR) $(IDIR_XORG_SERVER)/usr/lib/xorg/modules/extensions
	$(INSTALL_DIR) $(IDIR_XORG_SERVER)/usr/lib/xorg/modules/drivers
	$(INSTALL_DIR) $(IDIR_XORG_SERVER)/usr/lib/xorg/modules/fonts
	$(INSTALL_DIR) $(IDIR_XORG_SERVER)/usr/lib/xorg/modules/multimedia
	${CP} ${WRKINST}/usr/lib/xorg/protocol.txt \
		$(IDIR_XORG_SERVER)/usr/lib/xorg/
	${CP} ${WRKINST}/usr/bin/* $(IDIR_XORG_SERVER)/usr/bin
	${CP} ${WRKINST}/usr/lib/xorg/modules/*.so \
		$(IDIR_XORG_SERVER)/usr/lib/xorg/modules
	${CP} ${WRKINST}/usr/lib/xorg/modules/drivers/*.so \
		$(IDIR_XORG_SERVER)/usr/lib/xorg/modules/drivers
	${CP} ${WRKINST}/usr/lib/xorg/modules/extensions/*.so \
		$(IDIR_XORG_SERVER)/usr/lib/xorg/modules/extensions
ifeq (${ADK_TARGET_SYSTEM_LEMOTE_YEELONG},y)
	${CP} ./files/xorg.conf.lemote-yeelong \
		$(IDIR_XORG_SERVER)/etc/X11/xorg.conf
endif
ifeq (${ADK_TARGET_SYSTEM_SHARP_ZAURUS},y)
	${CP} ./files/xorg.conf.sharp-zaurus \
		$(IDIR_XORG_SERVER)/etc/X11/xorg.conf
endif
	# add m4 file to host directory
	$(INSTALL_DIR) $(STAGING_HOST_DIR)/usr/share/aclocal
	$(CP) ${WRKINST}/usr/share/aclocal/xorg-server.m4 \
		$(STAGING_HOST_DIR)/usr/share/aclocal

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
