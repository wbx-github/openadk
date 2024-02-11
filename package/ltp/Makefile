# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ltp
PKG_VERSION:=		20240129
PKG_RELEASE:=		1
PKG_DESCR:=		linux test project
PKG_HASH:=		c302f6b2ca09cbb7835f549777bdb9233fe31f7086d7ad8e65472a0804e3e025
PKG_DEPENDS:=		bash mke2fs mkfs shadow libtirpc libaio
PKG_DEPENDS+=		kmod dosfstools
PKG_BUILDDEP+=		libtirpc libaio
PKG_KDEPENDS:=		coredump bsd-process-acct ikconfig-proc cgroups
PKG_KDEPENDS+=		user-ns net-ns time-ns bpf-syscall blk-dev-loop watch-queue
PKG_NEEDS:=		threads
PKG_SECTION:=		base/tests
PKG_URL:=		http://linux-test-project.github.io
PKG_SITES:=		https://github.com/linux-test-project/ltp/releases/download/$(PKG_VERSION)/
PKG_NOPARALLEL:=	1

DISTFILES:=		$(PKG_NAME)-full-$(PKG_VERSION).tar.xz

WRKDIST=		$(WRKDIR)/$(PKG_NAME)-full-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LTP,ltp,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--with-open-posix-testsuite \
			--with-realtime-testsuite \
			--without-power-management-testsuite \
			--without-python \
			--without-perl \
			--without-expect \
			--disable-metadata

pre-configure:
	PATH="$(HOST_PATH)" $(MAKE) -C $(WRKBUILD) autotools

ltp-install:
	$(INSTALL_DIR) $(IDIR_LTP)/opt/ltp/tmp
	$(CP) $(WRKINST)/usr/* $(IDIR_LTP)/opt/ltp

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
