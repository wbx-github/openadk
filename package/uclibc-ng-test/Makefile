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

PKG_SUBPKGS:=		UCLIBC_NG_TEST UCLIBC_NG_TEST_ALL UCLIBC_NG_TEST_NPTL UCLIBC_NG_TEST_WCHAR UCLIBC_NG_TEST_MATH
PKG_SUBPKGS+=		UCLIBC_NG_TEST_OTHER
PKGSD_UCLIBC_NG_TEST_ALL:=		all uClibc-ng tests
PKGSN_UCLIBC_NG_TEST_ALL:=		uclibc-ng-test
PKGSD_UCLIBC_NG_TEST_NPTL:=		only NPTL tests
PKGSN_UCLIBC_NG_TEST_NPTL:=		uclibc-ng-test
PKGSD_UCLIBC_NG_TEST_WCHAR:=		only WCHAR tests
PKGSN_UCLIBC_NG_TEST_WCHAR:=		uclibc-ng-test
PKGSD_UCLIBC_NG_TEST_MATH:=		only MATH tests
PKGSN_UCLIBC_NG_TEST_MATH:=		uclibc-ng-test
PKGSD_UCLIBC_NG_TEST_OTHER:=		only all other tests, except NPTL, WCHAR and MATH
PKGSN_UCLIBC_NG_TEST_OTHER:=		uclibc-ng-test

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,UCLIBC_NG_TEST,uclibc-ng-test,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UCLIBC_NG_TEST_NPTL,uclibc-ng-test-nptl,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_UCLIBC_NG_TEST_NPTL},${PKG_SECTION}))
$(eval $(call PKG_template,UCLIBC_NG_TEST_WCHAR,uclibc-ng-test-wchar,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_UCLIBC_NG_TEST_WCHAR},${PKG_SECTION}))
$(eval $(call PKG_template,UCLIBC_NG_TEST_MATH,uclibc-ng-test-math,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_UCLIBC_NG_TEST_MATH},${PKG_SECTION}))
$(eval $(call PKG_template,UCLIBC_NG_TEST_OTHER,uclibc-ng-test-other,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_UCLIBC_NG_TEST_OTHER},${PKG_SECTION}))

CONFIG_STYLE:=          manual

XAKE_FLAGS+=		V=1
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
ifeq ($(ADK_TARGET_ARCH_NDS32),y)
XAKE_FLAGS+=		NO_TLS=1
endif

uclibc-ng-test-install:
	${INSTALL_DIR} ${IDIR_UCLIBC_NG_TEST}/etc
	echo '00:11:22:33:44:55 teeth' > ${IDIR_UCLIBC_NG_TEST}/etc/ethers
	${INSTALL_DIR} ${IDIR_UCLIBC_NG_TEST}/usr/lib
ifeq ($(ADK_PACKAGE_UCLIBC_NG_TEST_ALL),y)
	${CP} $(WRKINST)/usr/lib/* ${IDIR_UCLIBC_NG_TEST}/usr/lib/
endif
ifeq ($(ADK_PACKAGE_UCLIBC_NG_TEST_NPTL),y)
	mkdir -p ${IDIR_UCLIBC_NG_TEST_NPTL}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/nptl \
		${IDIR_UCLIBC_NG_TEST_NPTL}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.sh \
		${IDIR_UCLIBC_NG_TEST_NPTL}/usr/lib/uclibc-ng-test/test
	cat $(WRKINST)/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.in \
		| gawk '$$4 == "nptl"' > \
		${IDIR_UCLIBC_NG_TEST_NPTL}/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.in
endif
ifeq ($(ADK_PACKAGE_UCLIBC_NG_TEST_WCHAR),y)
	mkdir -p ${IDIR_UCLIBC_NG_TEST_WCHAR}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/nptl \
		${IDIR_UCLIBC_NG_TEST_WCHAR}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.sh \
		${IDIR_UCLIBC_NG_TEST_WCHAR}/usr/lib/uclibc-ng-test/test
	cat $(WRKINST)/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.in \
		| gawk '$$4 == "locale-mbwc"' > \
		${IDIR_UCLIBC_NG_TEST_WCHAR}/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.in
endif
ifeq ($(ADK_PACKAGE_UCLIBC_NG_TEST_MATH),y)
	mkdir -p ${IDIR_UCLIBC_NG_TEST_MATH}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/math \
		${IDIR_UCLIBC_NG_TEST_MATH}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.sh \
		${IDIR_UCLIBC_NG_TEST_NPTL}/usr/lib/uclibc-ng-test/test
	cat $(WRKINST)/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.in \
		| gawk '$$4 == "math"' > \
		${IDIR_UCLIBC_NG_TEST_NPTL}/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.in
endif
ifeq ($(ADK_PACKAGE_UCLIBC_NG_TEST_OTHER),y)
	mkdir -p ${IDIR_UCLIBC_NG_TEST_OTHER}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/{argp,args,assert,crypt,ctype,dlopen,inet,malloc,misc,mmap} \
		${IDIR_UCLIBC_NG_TEST_OTHER}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/{plt,pthread,pwd_grp,regex,rpc,rt,setjmp,signal,silly,stat} \
		${IDIR_UCLIBC_NG_TEST_OTHER}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/{stdio,stdlib,string,termios,time,tls,unistd,iconv} \
		${IDIR_UCLIBC_NG_TEST_OTHER}/usr/lib/uclibc-ng-test/test
	${CP} $(WRKINST)/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.sh \
		${IDIR_UCLIBC_NG_TEST_OTHER}/usr/lib/uclibc-ng-test/test
	cat $(WRKINST)/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.in \
		| gawk '$$4 !~ /^(nptl|math|locale-mbwc)$$/' > \
		${IDIR_UCLIBC_NG_TEST_OTHER}/usr/lib/uclibc-ng-test/test/uclibcng-testrunner.in
endif
	-find $(IDIR_UCLIBC_NG_TEST) -name \*.gdb -delete
	-find $(IDIR_UCLIBC_NG_TEST) -name \*.c -delete
	-find $(IDIR_UCLIBC_NG_TEST) -name \*.o -delete

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
