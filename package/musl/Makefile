# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS)-ver.mk
include $(ADK_TOPDIR)/mk/kernel-vars.mk
include $(ADK_TOPDIR)/toolchain/musl/Makefile.inc

PKG_NAME:=		musl
PKG_DESCR:=		embedded C library
PKG_SECTION:=		base/libs
PKG_OPTS:=		noremove nostaging noscripts

PKG_SUBPKGS:=		MUSL MUSL_DEV
PKGSD_MUSL_DEV:=	development files for musl
PKGSC_MUSL_DEV:=	dev/header

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MUSL,musl,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,MUSL_DEV,musl-dev,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_MUSL_DEV},${PKGSC_MUSL_DEV},${PKG_OPTS}))

CONFIG_STYLE:=          manual
BUILD_STYLE:=           manual
INSTALL_STYLE:=         manual

MUSL_LD_SO:=		"`echo 'void main(void) {}' |${TARGET_CC} ${TARGET_CFLAGS} -x c -o \
			$(BUILD_DIR)/.musl.tmp - >/dev/null 2>&1 ;\
			${TARGET_COMPILER_PREFIX}readelf -l $(BUILD_DIR)/.musl.tmp 2>/dev/null \
			| grep 'program interpreter: /lib/ld-musl' | sed -e 's|.*lib/||'|sed -e 's|]||' ;\
			rm $(BUILD_DIR)/.musl.tmp`"

# do nothing, musl is already build in toolchain directory
do-install:
ifneq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
	${INSTALL_DIR} $(IDIR_MUSL)/bin
	${INSTALL_DIR} $(IDIR_MUSL)/$(ADK_TARGET_LIBC_PATH)
	$(CP) $(STAGING_TARGET_DIR)/usr/lib/libc.so $(IDIR_MUSL)/$(ADK_TARGET_LIBC_PATH)
	(cd $(IDIR_MUSL)/$(ADK_TARGET_LIBC_PATH) && \
		ln -sf libc.so $(MUSL_LD_SO))
	(cd $(IDIR_MUSL)/bin && \
		ln -sf ../lib/$(MUSL_LD_SO) ldd)
endif
	

musl-dev-install:
	${INSTALL_DIR} ${IDIR_MUSL_DEV}/usr/lib 
	${CP} ${STAGING_TARGET_DIR}/usr/lib/crt*.o ${IDIR_MUSL_DEV}/usr/lib
	${KERNEL_MAKE} INSTALL_HDR_PATH=$(IDIR_MUSL_DEV)/usr headers_install
	$(MAKE) -C $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/${PKG_NAME}-${PKG_VERSION} \
		DESTDIR=$(IDIR_MUSL_DEV) \
		install-headers
	@find $(IDIR_MUSL_DEV) -name .install -exec rm {} \;
	@find $(IDIR_MUSL_DEV) -name ..install.cmd -exec rm {} \;

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
