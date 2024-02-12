# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		liburcu
PKG_VERSION:=		0.14.0
PKG_RELEASE:=		1
PKG_HASH:=		ca43bf261d4d392cff20dfae440836603bf009fce24fdc9b2697d837a2239d4f
PKG_DESCR:=		userspace rcu (read-copy-update) libraries
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://lttng.org/files/urcu/
PKG_OPTS:=		dev

DISTFILES:=             userspace-rcu-$(PKG_VERSION).tar.bz2
WRKDIST=		${WRKDIR}/userspace-rcu-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBURCU,liburcu,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

liburcu-install:
	$(INSTALL_DIR) $(IDIR_LIBURCU)/usr/lib
	$(CP) $(WRKINST)/usr/lib/liburcu*.so* \
		$(IDIR_LIBURCU)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
