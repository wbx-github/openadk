# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tinyx
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_HASH:=		db206aeef89104e1bd4cab40508eb1160f8a6bc69848eaf16cbc35eda1c62864
PKG_DESCR:=		tiny x server
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		libxcvt libfontenc xkeyboard-config xkbcomp libxau libxaw
PKG_DEPENDS+=		libxmu libxpm libxrender libxt libxxf86dga libxext
PKG_DEPENDS+=		libxdmcp libxv libsm libice libx11 libxcb libdrm libxtst
PKG_DEPENDS+=		libxshmfence libfreetype libfontenc libxfont
PKG_BUILDDEP:=		libX11 randrproto renderproto fixesproto damageproto
PKG_BUILDDEP+=		scrnsaverproto resourceproto fontsproto videoproto
PKG_BUILDDEP+=		compositeproto evieext xf86dgaproto recordproto dri3proto
PKG_BUILDDEP+=		xineramaproto presentproto xf86driproto glproto libXtst
PKG_BUILDDEP+=		xorgproto libxcvt font-util-host libXfont
PKG_NEEDS:=		threads c++
PKG_SITES:=		https://github.com/tinycorelinux/tinyx.git

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_CFLINE_TINYX:=depends on ADK_TARGET_WITH_VGA || ADK_TARGET_QEMU_WITH_GRAPHIC

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TINYX,tinyx,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--with-fontdir=/usr/share/fonts/X11

tinyx-install:
	$(INSTALL_DIR) $(IDIR_TINYX)/usr/bin
	${CP} ${WRKINST}/usr/bin/Xfbdev $(IDIR_TINYX)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
