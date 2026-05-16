# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		nodejs
PKG_VERSION:=		24.15.0
PKG_RELEASE:=		1
PKG_HASH:=		729de494dd2872e5a3a6c32a1cd156a5413d4aca2772b2d873ee86bb5531bcd9
PKG_DESCR:=		asynchronous event driven framework
PKG_SECTION:=		net/http
PKG_DEPENDS:=		zlib libopenssl
PKG_BUILDDEP:=		python3-host nodejs-host zlib openssl
PKG_NEEDS:=		threads c++
PKG_URL:=		https://nodejs.org/
PKG_SITES:=		https://nodejs.org/dist/v$(PKG_VERSION)/

PKG_CFLINE_NODEJS:=	depends on ADK_BROKEN

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
			--without-intl \
			--shared-zlib \
		)

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${ALL_TARGET})

nodejs-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} DESTDIR='${STAGING_HOST_DIR}' ${HOST_INSTALL_TARGET} $(MAKE_TRACE)
	$(INSTALL_BIN) ${WRKBUILD}/out/Release/node_js2c ${STAGING_HOST_DIR}/usr/bin
	$(INSTALL_BIN) ${WRKBUILD}/out/Release/bytecode_builtins_list_generator ${STAGING_HOST_DIR}/usr/bin
	$(INSTALL_BIN) ${WRKBUILD}/out/Release/torque ${STAGING_HOST_DIR}/usr/bin

do-configure:
		(cd $(WRKSRC); \
                PYTHON=$(STAGING_HOST_DIR)/usr/bin/python3 \
                $(STAGING_HOST_DIR)/usr/bin/python3 ./configure \
			--prefix=/usr \
			--cross-compiling \
			--without-intl \
			--shared-openssl \
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
