# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		uClibc-ng-test
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_DESCR:=		embedded c library testsuite
PKG_SECTION:=		base/tests
PKG_KDEPENDS:=		inotify-user
PKG_URL:=		http://www.uclibc-ng.org
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng-test.git

PKG_NOPARALLEL:=	1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,UCLIBC_NG_TEST,uclibc-ng-test,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual

ifeq ($(ADK_TARGET_LIB_GLIBC),y)
XAKE_FLAGS+=		NO_CRYPT=1
endif
ifeq ($(ADK_TARGET_LIB_MUSL),y)
XAKE_FLAGS+=		NO_MATH=1
endif
ifeq ($(ADK_TARGET_WITH_LT),y)
XAKE_FLAGS+=		NO_TLS=1 NO_NPTL=1
endif
ifeq ($(ADK_TARGET_WITHOUT_THREADS),y)
XAKE_FLAGS+=		NO_TLS=1 NO_THREADS=1
endif
ifeq ($(ADK_TARGET_BINFMT_FLAT),y)
XAKE_FLAGS+=		NO_DL=1
endif
ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
XAKE_FLAGS+=		NO_DL=1 NO_TLS=1 NO_NPTL=1
endif
ifeq ($(ADK_TARGET_LIBC_WITH_LOCALE),)
XAKE_FLAGS+=		NO_LOCALE=1
endif
ifeq ($(ADK_TARGET_ARCH_KVX),y)
XAKE_FLAGS+=		NO_TLS=1
endif

uclibc-ng-test-install:
	${INSTALL_DIR} ${IDIR_UCLIBC_NG_TEST}/etc
	echo '00:11:22:33:44:55 teeth' > ${IDIR_UCLIBC_NG_TEST}/etc/ethers
	${INSTALL_DIR} ${IDIR_UCLIBC_NG_TEST}/usr/lib
	${CP} $(WRKINST)/usr/lib/* ${IDIR_UCLIBC_NG_TEST}/usr/lib/
	-find $(IDIR_UCLIBC_NG_TEST) -name \*.gdb -delete

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
