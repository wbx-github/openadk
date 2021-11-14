# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/$(ADK_TARGET_OS)-ver.mk
include $(ADK_TOPDIR)/mk/kernel-vars.mk
include $(ADK_TOPDIR)/toolchain/glibc/Makefile.inc

PKG_NAME:=		glibc
PKG_DESCR:=		gnu c library
PKG_SECTION:=		base/libs
PKG_OPTS:=		noremove nostaging noscripts
PKG_SUBPKGS:=		GLIBC GLIBC_DEV GLIBC_GCONV

PKGSD_GLIBC_GCONV:=	gconv libraries used at runtime
PKGSS_GLIBC_GCONV:=	glibc

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GLIBC,glibc,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,GLIBC_DEV,glibc-dev,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,GLIBC_GCONV,glibc-gconv,$(PKG_VERSION)-${PKG_RELEASE},${PKGSS_GLIBC_GCONV},${PKGSD_GLIBC_GCONV},${PKG_SECTION},${PKG_OPTS}))

GLIBC_ENV:=             PATH='${TARGET_PATH}' \
                        BUILD_CC='${CC_FOR_BUILD}' \
                        CFLAGS="$(TARGET_CFLAGS)" \
                        CXXFLAGS="$(TARGET_CXXFLAGS)" \
                        CC="${TARGET_CC}" \
                        CXX="${TARGET_CXX}" \
                        AR="${TARGET_AR}" \
                        RANLIB="${TARGET_RANLIB}" \
                        libc_cv_forced_unwind=yes \
			libc_cv_cc_with_libunwind=yes \
                        libc_cv_c_cleanup=yes \
                        libc_cv_gnu99_inline=yes \
			libc_cv_initfini_array=yes

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

# compile nothing, glibc is already build in toolchain directory
do-install:
ifneq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
	${INSTALL_DIR} ${IDIR_GLIBC}/$(ADK_TARGET_LIBC_PATH)
	$(CP) $(STAGING_TARGET_DIR)/lib/ld*.so* $(IDIR_GLIBC)/$(ADK_TARGET_LIBC_PATH)
	for file in libc libpthread librt libcrypt libdl libm libanl libnsl libresolv libutil libnss_dns libnss_files; do \
		$(CP) $(STAGING_TARGET_DIR)/$(ADK_TARGET_LIBC_ABI_PATH)/$$file.so* $(IDIR_GLIBC)/$(ADK_TARGET_LIBC_PATH); \
		#$(CP) $(STAGING_TARGET_DIR)/$(ADK_TARGET_LIBC_ABI_PATH)/$$file-$(PKG_GLIBCVER).so $(IDIR_GLIBC)/$(ADK_TARGET_LIBC_PATH); \
	done
else
	${INSTALL_DIR} ${IDIR_GLIBC}/$(ADK_TARGET_LIBC_PATH)
	for file in libnss_dns libnss_files; do \
		$(CP) $(STAGING_TARGET_DIR)/$(ADK_TARGET_LIBC_ABI_PATH)/$$file.so* $(IDIR_GLIBC)/$(ADK_TARGET_LIBC_PATH); \
		$(CP) $(STAGING_TARGET_DIR)/$(ADK_TARGET_LIBC_ABI_PATH)/$$file-$(PKG_GLIBCVER).so $(IDIR_GLIBC)/$(ADK_TARGET_LIBC_PATH); \
	done
endif
	${INSTALL_DIR} $(IDIR_GLIBC)/usr/bin
	$(CP) $(STAGING_TARGET_DIR)/usr/bin/getconf $(IDIR_GLIBC)/usr/bin
	${INSTALL_DIR} ${IDIR_GLIBC}/etc
	${INSTALL_DATA} ${STAGING_TARGET_DIR}/etc/gai.conf ${IDIR_GLIBC}/etc
	${INSTALL_DATA} ./files/nsswitch.conf ${IDIR_GLIBC}/etc

glibc-gconv-install:
	${INSTALL_DIR} $(IDIR_GLIBC_GCONV)/usr/lib/gconv
	${INSTALL_DATA} ${STAGING_TARGET_DIR}/usr/lib/gconv/gconv-modules \
		$(IDIR_GLIBC_GCONV)/usr/lib/gconv
	$(CP) ${STAGING_TARGET_DIR}/usr/lib/gconv/*.so \
		$(IDIR_GLIBC_GCONV)/usr/lib/gconv

glibc-dev-install:
	${INSTALL_DIR} $(IDIR_GLIBC_DEV)/$(ADK_TARGET_LIBC_PATH) $(IDIR_GLIBC_DEV)/usr/lib
ifeq ($(ADK_TARGET_ARCH_RISCV64),y)
	${CP} ${STAGING_TARGET_DIR}/usr/lib/*/libc.so ${IDIR_GLIBC_DEV}/usr/lib
else
	${CP} ${STAGING_TARGET_DIR}/usr/lib/*/libc.so ${IDIR_GLIBC_DEV}/usr/lib
endif
ifeq ($(ADK_TARGET_ABI_O32),y)
ifeq ($(ADK_TARGET_BIG_ENDIAN),y)
	$(SED) "s#@@ELFTARGET@@#elf32-tradbigmips#" $(IDIR_GLIBC_DEV)/usr/lib/libc.so
else
	$(SED) "s#@@ELFTARGET@@#elf32-tradlittlemips#" $(IDIR_GLIBC_DEV)/usr/lib/libc.so
endif
endif
ifeq ($(ADK_TARGET_ABI_N32),y)
ifeq ($(ADK_TARGET_BIG_ENDIAN),y)
	$(SED) "s#@@ELFTARGET@@#elf32-ntradbigmips#" $(IDIR_GLIBC_DEV)/usr/lib/libc.so
else
	$(SED) "s#@@ELFTARGET@@#elf32-ntradlittlemips#" $(IDIR_GLIBC_DEV)/usr/lib/libc.so
endif
endif
ifeq ($(ADK_TARGET_ABI_N64),y)
ifeq ($(ADK_TARGET_BIG_ENDIAN),y)
	$(SED) "s#@@ELFTARGET@@#elf64-tradbigmips#" $(IDIR_GLIBC_DEV)/usr/lib/libc.so
else
	$(SED) "s#@@ELFTARGET@@#elf64-tradlittlemips#" $(IDIR_GLIBC_DEV)/usr/lib/libc.so
endif
endif
ifeq ($(ADK_TARGET_ARCH_RISCV64),y)
	${CP} ${STAGING_TARGET_DIR}/usr/lib/*/libc_nonshared.a ${IDIR_GLIBC_DEV}/usr/lib
	${CP} ${STAGING_TARGET_DIR}/usr/lib/*/crt* ${IDIR_GLIBC_DEV}/usr/lib
else
	${CP} ${STAGING_TARGET_DIR}/usr/lib/libc_nonshared.a ${IDIR_GLIBC_DEV}/usr/lib
	${CP} ${STAGING_TARGET_DIR}/usr/lib/crt* ${IDIR_GLIBC_DEV}/usr/lib
endif
	-for file in libpthread librt libcrypt libdl libm libresolv libutil; do \
		cd $(IDIR_GLIBC_DEV)/$(ADK_TARGET_LIBC_PATH); ln -sf $$file-$(PKG_GLIBCVER).so $$file.so; \
	done
	# header package
	${KERNEL_MAKE} INSTALL_HDR_PATH=$(IDIR_GLIBC_DEV)/usr headers_install
	(cd $(WRKBUILD); \
		$(GLIBC_ENV) \
		$(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/$(PKG_NAME)-$(PKG_VERSION)/configure \
			--prefix=$(IDIR_GLIBC_DEV)/usr \
			--with-sysroot=$(IDIR_GLIBC_DEV) \
			${GLIBC_CONFOPTS} \
	);
	$(GLIBC_ENV) $(MAKE) -C $(WRKBUILD) cross-compiling=yes install-headers
	touch $(IDIR_GLIBC_DEV)/usr/include/gnu/stubs.h
	touch $(IDIR_GLIBC_DEV)/usr/include/gnu/stubs-{32,x32,64}.h
	touch $(IDIR_GLIBC_DEV)/usr/include/bits/stdio_lim.h
	# WORKAROUND: bits/syscall.h is only installed via install-others target
	$(CP) $(STAGING_TARGET_DIR)/usr/include/bits/syscall.h \
		$(IDIR_GLIBC_DEV)/usr/include/bits
	@find $(IDIR_GLIBC_DEV) -name .install -exec rm {} \;

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
