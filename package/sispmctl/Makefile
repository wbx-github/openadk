# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		sispmctl
PKG_VERSION:=		4.12
PKG_RELEASE:=		1
PKG_HASH:=		e757863a4838da6e1ca72a57adc5aca6fc47ffbddc72a69052d8abd743d57082
PKG_DESCR:=		control application for power sockets
PKG_SECTION:=		sys/hw
PKG_DEPENDS:=		libusb libusb-compat
PKG_BUILDDEP:=		libusb libusb-compat
PKG_URL:=		http://sispmctl.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/sispmctl/files/sispmctl/sispmctl-$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SISPMCTL,sispmctl,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=         ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes

sispmctl-install:
	${INSTALL_DIR} ${IDIR_SISPMCTL}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/sispmctl ${IDIR_SISPMCTL}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
