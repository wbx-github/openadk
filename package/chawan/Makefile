# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		chawan
PKG_VERSION:=		0.4.4
PKG_RELEASE:=		1
PKG_HASH:=		e0a06e1504e10a51c6009751d79b798c98d8274e559fe195d4b4b7ddadf91bb8
PKG_DESCR:=		console www browser
PKG_SECTION:=		app/browser
PKG_DEPENDS:=		libopenssl brotli libssh2 ca-certificates
PKG_BUILDDEP:=		openssl brotli libssh2 nim-host
PKG_KDEPENDS:=		seccomp seccomp-filter
PKG_URL:=		https://chawan.net/index.html
PKG_SITES:=		https://git.sr.ht/~bptato/chawan/archive/

DISTFILES:=             v$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-v$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CHAWAN,chawan,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

ifeq ($(ADK_TARGET_LIBC),glibc)
LIBC=			gnu
else
LIBC=			uclibc
endif
ifeq ($(ADK_TARGET_ARCH),aarch64)
ARCH=			arm64
else
ARCH=			$(ADK_TARGET_ARCH)
endif

XAKE_FLAGS:=		FLAGS="--os:linux --cpu:$(ARCH) --gcc.exe:$(ADK_TARGET_CPU_ARCH)-$(ADK_VENDOR)-linux-$(LIBC)-gcc --gcc.linkerexe:$(ADK_TARGET_CPU_ARCH)-$(ADK_VENDOR)-linux-$(LIBC)-gcc"
XAKE_FLAGS+=		PREFIX="/usr" FORCE_POLL_MODE=2
CONFIG_STYLE:=		manual

chawan-install:
	$(INSTALL_DIR) $(IDIR_CHAWAN)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/cha \
		$(IDIR_CHAWAN)/usr/bin
	$(INSTALL_DIR) $(IDIR_CHAWAN)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/chawan \
		$(IDIR_CHAWAN)/usr/libexec

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
