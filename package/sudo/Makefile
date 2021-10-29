# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sudo
PKG_VERSION:=		1.9.8p2
PKG_RELEASE:=		1
PKG_HASH:=		9e3b8b8da7def43b6e60c257abe80467205670fd0f7c081de1423c414b680f2d
PKG_DESCR:=		su do
PKG_SECTION:=		sys/misc
PKG_NEEDS:=		mmu
PKG_URL:=		http://www.sudo.ws/sudo/
PKG_SITES:=		http://www.sudo.ws/sudo/dist/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SUDO,sudo,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_CPPFLAGS+=		-I../ -I../include

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
MAKE_FLAGS+=		LDFLAGS="$(TARGET_LDFLAGS) -all-static"
else
TARGET_LDFLAGS+=	-ldl
endif

CONFIGURE_ARGS+=	--without-pam \
			--without-sendmail \
			--disable-shared \
			--enable-static-sudoers \
			--disable-shared-libutil \
			--with-env-editor

ifeq ($(ADK_TARGET_USE_SSP),y)
CONFIGURE_ARGS+=	--enable-hardening
else
CONFIGURE_ARGS+=	--disable-hardening
endif

XAKE_FLAGS+=		INSTALL_OWNER=""

sudo-install:
	$(INSTALL_DIR) $(IDIR_SUDO)/usr/bin
	$(INSTALL_DIR) $(IDIR_SUDO)/usr/sbin
	$(INSTALL_DIR) $(IDIR_SUDO)/etc
	$(INSTALL_DATA) ./files/sudoers $(IDIR_SUDO)/etc
	chmod 440 $(IDIR_SUDO)/etc/sudoers
	$(INSTALL_BIN) $(WRKINST)/usr/bin/sudo \
		$(IDIR_SUDO)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/visudo \
		$(IDIR_SUDO)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
