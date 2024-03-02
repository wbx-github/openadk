# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libcap-ng
PKG_VERSION:=		0.8.4
PKG_RELEASE:=		1
PKG_HASH:=		5615c76a61039e283a6bd107c4faf345ae5ad4dcd45907defe5e474d8fdb6fd2
PKG_DESCR:=		capability library
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/stevegrubb/libcap-ng/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBCAP_NG,libcap-ng,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	autogen

libcap-ng-install:
	$(INSTALL_DIR) $(IDIR_LIBCAP_NG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcap-ng*.so* \
		$(IDIR_LIBCAP_NG)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
