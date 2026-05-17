# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		vala
PKG_VERSION:=		0.56.18
PKG_RELEASE:=		1
PKG_HASH:=		f2affe7d40ab63db8e7b9ecc3f6bdc9c2fc7e3134c84ff2d795f482fe926a382
PKG_DESCR:=		compiler for the gobject type system
PKG_SECTION:=		dev/lang
PKG_BUILDDEP:=		glib
HOST_BUILDDEP:=		glib-host libffi-host
PKG_URL:=		https://wiki.gnome.org/Vala
PKG_SITES:=		http://download.gnome.org/sources/vala/0.56/

PKG_CFLINE_VALA:=	depends on ADK_HOST

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,VALA,vala,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,VALA,vala,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_LDFLAGS+=		-ldl -lffi
HOST_CONFIGURE_ENV+=	GI_GIRDIR="$(STAGING_HOST_DIR)/usr/share/gir-1.0"
HOST_CONFIGURE_ARGS+=	--disable-valadoc

vala-install:
	$(INSTALL_DIR) $(IDIR_VALA)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_VALA)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
