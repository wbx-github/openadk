# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		nodejs
PKG_VERSION:=		18.12.1
PKG_RELEASE:=		1
PKG_HASH:=		ba8174dda00d5b90943f37c6a180a1d37c861d91e04a4cb38dc1c0c74981c186
PKG_DESCR:=		asynchronous event driven framework
PKG_SECTION:=		net/http
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		python3-host nodejs-host zlib
PKG_NEEDS:=		threads c++
PKG_URL:=		https://nodejs.org/
PKG_SITES:=		https://nodejs.org/dist/v$(PKG_VERSION)/

DISTFILES:=             node-v$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/node-v$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,NODEJS,nodejs,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,NODEJS,nodejs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

HOST_CFLAGS:=
HOST_CXXFLAGS:=
HOST_STYLE:=		manual
CONFIG_STYLE:=		manual

host-configure:
		(cd $(WRKSRC); \
                PYTHON=$(STAGING_HOST_DIR)/usr/bin/python3 \
                $(STAGING_HOST_DIR)/usr/bin/python3 ./configure \
			--prefix=/usr \
			--without-snapshot \
			--without-dtrace \
			--without-etw \
			--without-intl \
			--shared-zlib \
		)

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${ALL_TARGET})

nodejs-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} DESTDIR='${STAGING_HOST_DIR}' ${HOST_INSTALL_TARGET} $(MAKE_TRACE)
#	$(INSTALL_BIN) ${WRKBUILD}/out/Release/mkpeephole ${STAGING_HOST_DIR}/usr/bin

do-configure:
		(cd $(WRKSRC); \
                PYTHON=$(STAGING_HOST_DIR)/usr/bin/python3 \
                $(STAGING_HOST_DIR)/usr/bin/python3 ./configure \
			--prefix=/usr \
			--cross-compiling \
                	--without-snapshot \
                	--without-dtrace \
                	--without-etw \
			--without-intl \
                	--shared-zlib \
		)
#		$(SED) "s#<(mkpeephole_exec)#$(STAGING_HOST_DIR)/usr/bin/mkpeephole#g" $(WRKSRC)/deps/v8/src/v8.gyp

nodejs-install:
	$(INSTALL_DIR) $(IDIR_NODEJS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/node_modules \
		$(IDIR_NODEJS)/usr/lib
	$(INSTALL_DIR) $(IDIR_NODEJS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/node \
		$(IDIR_NODEJS)/usr/bin

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
