# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ORBit2
PKG_VERSION:=		2.14.19
PKG_EXTRAVER:=		2.14
PKG_RELEASE:=		5
PKG_HASH:=		5724ed85c626ce406156d2f7c4d104d670eb82cf78e582c325e713a31632c9bd
PKG_DESCR:=		corba 2.4-compliant object request broker
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		glib libIDL-host libIDL 
HOST_BULDDEP:=		glib-host libIDL-host
PKG_NEEDS:=		intl
PKG_URL:=		http://projects.gnome.org/ORBit2/
PKG_SITES:=		ftp://ftp.gnome.org//pub/gnome/sources/ORBit2/${PKG_EXTRAVER}/
PKG_LIBNAME:=		orbit2
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ORBIT2,orbit2,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_CFLAGS+=		$(shell env $(HOST_CONFIGURE_ENV) libIDL-config-2 --cflags 2>/dev/null)
HOST_LIBS:=		$(shell env $(HOST_CONFIGURE_ENV) libIDL-config-2 --libs 2>/dev/null)
HOST_LDFLAGS+=		-static
HOST_LIBS+=		-lrt
HOST_LIBS+=		-lgmodule-2.0 -ldl -lpthread -lglib-2.0
CONFIGURE_ENV+=		ac_cv_alignof_CORBA_octet=1 \
			ac_cv_alignof_CORBA_boolean=1 \
			ac_cv_alignof_CORBA_char=1 \
			ac_cv_alignof_CORBA_wchar=2 \
			ac_cv_alignof_CORBA_short=2 \
			ac_cv_alignof_CORBA_long=4 \
			ac_cv_alignof_CORBA_long_long=4 \
			ac_cv_alignof_CORBA_float=4 \
			ac_cv_alignof_CORBA_double=4 \
			ac_cv_alignof_CORBA_long_double=4 \
			ac_cv_alignof_CORBA_struct=1 \
			ac_cv_alignof_CORBA_pointer=4 \
			ac_cv_cflags_gcc_option__Werror_implicit_function_declaration=no

orbit2-install:
	$(INSTALL_DIR) $(IDIR_ORBIT2)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/lib/libORBit*.so* \
		$(IDIR_ORBIT2)/usr/lib
	$(INSTALL_DIR) $(STAGING_TARGET_DIR)/usr/bin
	$(CP) $(WRKINST)/usr/bin/orbit-idl-2 \
		$(STAGING_TARGET_DIR)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
