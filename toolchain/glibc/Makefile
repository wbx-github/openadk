# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc
include ${ADK_TOPDIR}/mk/buildhlp.mk

# glibc does not boot with Os and CPU specific FLAGS for nios2
ifeq ($(ADK_TARGET_ARCH_NIOS2),y)
TARGET_CFLAGS:=		-O2
TARGET_CXXFLAGS:=	-O2
endif

# glibc does not compile with NEON suggested CFLAGS/CXXFLAGS
TARGET_CFLAGS:=		$(filter-out -ffast-math,$(TARGET_CFLAGS))
TARGET_CXXFLAGS:=	$(filter-out -ffast-math,$(TARGET_CXXFLAGS))

GLIBC_CONFOPTS:=	--build=$(GNU_HOST_NAME) \
			--host=$(GNU_TARGET_NAME) \
			--with-headers=$(STAGING_TARGET_DIR)/usr/include \
			--disable-sanity-checks \
			--disable-werror \
			--disable-nscd \
			--disable-default-pie \
			--enable-shared

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
GLIBC_CONFOPTS+=	--enable-static-nss
endif

GLIBC_ENV:=             PATH='${HOST_PATH}:${TARGET_PATH}' \
                        BUILD_CC='${CC_FOR_BUILD}' \
                        CFLAGS="$(TARGET_CFLAGS)" \
                        CXXFLAGS="$(TARGET_CXXFLAGS)" \
                        CC="${TARGET_CC}" \
                        CXX="${TARGET_CXX}" \
                        AR="${TARGET_AR}" \
                        RANLIB="${TARGET_RANLIB}" \
                        libc_cv_gnu99_inline=yes \
			libc_cv_initfini_array=yes

ifeq ($(ADK_TARGET_ARCH_RISCV64),y)
GLIBC_ENV+=		libc_cv_slibdir=/lib libc_cv_rtlddir=/lib
endif
ifeq ($(ADK_TARGET_ARCH_RISCV32),y)
GLIBC_ENV+=		libc_cv_slibdir=/lib libc_cv_rtlddir=/lib
endif

GLIBC_MAKEOPTS+=	cross-compiling=yes
ifeq (${ADK_MAKE_PARALLEL},y)
GLIBC_MAKEOPTS+=	PARALLELMFLAGS="-j$(ADK_MAKE_JOBS)"
endif


GLIBC_BUILD_DIR_FINAL:=		${WRKDIR}/$(PKG_NAME)-$(PKG_VERSION)-final

$(WRKBUILD)/.configured:
	mkdir -p $(GLIBC_BUILD_DIR_FINAL)
	(cd $(GLIBC_BUILD_DIR_FINAL); \
		${GLIBC_ENV} \
		$(WRKBUILD)/configure \
			--prefix=/usr \
			${GLIBC_CONFOPTS} \
	);
	touch $@

$(WRKBUILD)/.compiled:
	${GLIBC_ENV} $(MAKE) ${GLIBC_MAKEOPTS} -C $(GLIBC_BUILD_DIR_FINAL) all
	touch $@

$(WRKBUILD)/.installed:
	${GLIBC_ENV} $(MAKE) -C $(GLIBC_BUILD_DIR_FINAL) install_root=$(STAGING_TARGET_DIR) install
	touch $(STAGING_TARGET_DIR)/usr/include/gnu/stubs.h
	touch $(STAGING_TARGET_DIR)/usr/include/gnu/stubs-{32,x32,64,lp64,soft,hard}.h
	mkdir -p ${STAGING_TARGET_DIR}/etc
	${INSTALL_DATA} ${WRKBUILD}/posix/gai.conf ${STAGING_TARGET_DIR}/etc
	${INSTALL_DATA} ${WRKBUILD}/nss/nsswitch.conf ${STAGING_TARGET_DIR}/etc
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
