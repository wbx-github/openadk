# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		uClibc-ng-test
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_DESCR:=		embedded c library testsuite
PKG_SECTION:=		base/tests
PKG_URL:=		http://www.uclibc-ng.org
PKG_SITES:=		git://uclibc-ng.org/git/uclibc-ng-test

PKG_NOPARALLEL:=	1
PKG_LIBC_DEPENDS:=	uclibc-ng

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,UCLIBC_NG_TEST,uclibc-ng-test,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual
INSTALL_STYLE:=         manual

ifeq ($(ADK_TARGET_WITHOUT_THREADS),y)
XAKE_FLAGS+=		NO_THREADS=1
endif
ifeq ($(ADK_TARGET_USE_STATIC_LIBS),y)
XAKE_FLAGS+=		NO_DL=1
endif
ifeq ($(ADK_RUNTIME_ENABLE_LOCALE),)
XAKE_FLAGS+=		NO_LOCALE=1
endif

uclibc-ng-test-install:
	${INSTALL_DIR} ${IDIR_UCLIBC_NG_TEST}/etc
	echo '00:11:22:33:44:55 teeth' > ${IDIR_UCLIBC_NG_TEST}/etc/ethers
	${INSTALL_DIR} ${IDIR_UCLIBC_NG_TEST}/opt/uclibc-ng
	${CP} $(WRKBUILD)/test \
		${IDIR_UCLIBC_NG_TEST}/opt/uclibc-ng
	@find ${IDIR_UCLIBC_NG_TEST}/opt/uclibc-ng -name \*.o -exec rm {} \;

include ${ADK_TOPDIR}/mk/pkg-bottom.mk