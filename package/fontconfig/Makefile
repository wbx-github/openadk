# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		fontconfig
PKG_VERSION:=		2.18.0
PKG_RELEASE:=		1
PKG_HASH:=		e7064a4725431ddba06ff8b971ec5a4b422e23b0169ce215747beedcb30e9073
PKG_DESCR:=		library for configuring and customizing font access
PKG_SECTION:=		libs/fonts
PKG_DEPENDS:=		libfreetype libxml2
PKG_BUILDDEP:=		freetype libxml2 gperf-host util-linux
HOST_BUILDDEP:=		expat-host
PKG_NEEDS:=		locale
PKG_URL:=		http://fontconfig.org/
PKG_SITES:=		https://gitlab.freedesktop.org/api/v4/projects/890/packages/generic/$(PKG_NAME)/$(PKG_VERSION)/
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,FONTCONFIG,fontconfig,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,FONTCONFIG,fontconfig,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_STYLE:=		auto
CONFIGURE_ENV+=		ac_cv_va_copy=yes
CONFIGURE_ARGS+=	--enable-libxml2 \
			--disable-docs

fontconfig-install:
	${INSTALL_DIR} ${IDIR_FONTCONFIG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/fc-* \
		${IDIR_FONTCONFIG}/usr/bin
	${INSTALL_DIR} ${IDIR_FONTCONFIG}/usr/lib ${IDIR_FONTCONFIG}/etc/fonts
	${CP} ${WRKINST}/usr/lib/libfontconfig.so* ${IDIR_FONTCONFIG}/usr/lib
	$(CP) ${WRKINST}/etc/fonts/* ${IDIR_FONTCONFIG}/etc/fonts

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
