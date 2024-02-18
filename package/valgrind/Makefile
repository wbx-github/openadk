# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		valgrind
PKG_VERSION:=		3.22.0
PKG_RELEASE:=		1
PKG_HASH:=		c811db5add2c5f729944caf47c4e7a65dcaabb9461e472b578765dd7bf6d2d4c
PKG_DESCR:=		memory management debugging tool
PKG_SECTION:=		app/debug
PKG_URL:=		http://valgrind.org/
PKG_SITES:=		ftp://sourceware.org/pub/valgrind/

PKG_ARCH_DEPENDS:=	aarch64 arm ppc ppc64 mips mipsel mips64 mips64el tile s390 x86 x86_64

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,VALGRIND,valgrind,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ifeq ($(ADK_TARGET_LIB_MUSL),y)
TARGET_CPPFLAGS+=	-D__MUSL__
endif
CONFIGURE_ENV+=		ac_cv_file__proc_self_fd=yes \
			ac_cv_file__proc_self_exe=yes \
			ac_cv_file__proc_self_maps=yes

ifeq ($(ADK_TARGET_ARCH_ARM),y)
CONFIGURE_ARGS+=	--host=$(patsubst arm-%,armv7-%,$(GNU_TARGET_NAME))
endif

valgrind-install:
	$(INSTALL_DIR) $(IDIR_VALGRIND)/usr/bin
	$(INSTALL_DIR) $(IDIR_VALGRIND)/usr/lib/valgrind
	$(INSTALL_DIR) $(IDIR_VALGRIND)/usr/libexec/valgrind
	$(INSTALL_BIN) $(WRKINST)/usr/bin/valgrind $(IDIR_VALGRIND)/usr/bin/
	$(INSTALL_BIN) $(WRKBUILD)/memcheck/memcheck-*-linux \
		$(IDIR_VALGRIND)/usr/libexec/valgrind
	$(CP) $(WRKINST)/usr/libexec/valgrind/default.supp \
		$(IDIR_VALGRIND)/usr/libexec/valgrind
	$(CP) $(WRKINST)/usr/libexec/valgrind/*.so \
		$(IDIR_VALGRIND)/usr/libexec/valgrind
	$(CP) $(WRKINST)/usr/lib/valgrind/* \
		$(IDIR_VALGRIND)/usr/lib/valgrind

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
