# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libcap
PKG_VERSION:=		2.59
PKG_RELEASE:=		1
PKG_HASH:=		49f64ae40b113e53cbc161e22af7094e3bb4a0611fa33ef5a4257b011779f034
PKG_DESCR:=		capabilities library
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.friedhoff.org/posixfilecaps.html
PKG_SITES:=		https://www.kernel.org/pub/linux/libs/security/linux-privs/libcap2/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBCAP,libcap,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,LIBCAP,libcap,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

ifeq ($(OS_FOR_BUILD),Darwin)
HOST_CFLAGS+=		-I$(STAGING_TARGET_DIR)/usr/include
endif

HOST_STYLE:=		manual
CONFIG_STYLE:=		manual
MAKE_ENV+=		BUILD_CC="${HOST_CC}"
ifeq ($(ADK_PACKAGE_PAM),)
MAKE_ENV+=		PAM_CAP=no
endif

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_ALL_TARGET}) $(MAKE_TRACE)

libcap-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} DESTDIR='${STAGING_HOST_DIR}' ${HOST_INSTALL_TARGET} $(MAKE_TRACE)

libcap-install:
	$(INSTALL_DIR) $(IDIR_LIBCAP)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcap*.so* \
		$(IDIR_LIBCAP)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
