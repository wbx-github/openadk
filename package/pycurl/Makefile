# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pycurl
PKG_VERSION:=		7.45.2
PKG_RELEASE:=		1
PKG_HASH:=		5730590be0271364a5bddd9e245c9cc0fb710c4cbacbdd95264a3122d23224ca
PKG_DESCR:=		python module for fetching of files
PKG_SECTION:=		dev/python
PKG_BUILDDEP:=		python3 curl
PKG_DEPENDS:=		python3 libcurl
PKG_URL:=		http://pycurl.io/
PKG_SITES:=		https://files.pythonhosted.org/packages/a8/af/24d3acfa76b867dbd8f1166853c18eefc890fc5da03a48672b38ea77ddae/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PYCURL,pycurl,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

TARGET_CFLAGS+=		-fPIC
MAKE_ENV+=		LDSHARED="$(TARGET_CC) -shared"
CURL_CONFIG:=		$(STAGING_TARGET_DIR)/usr/bin/curl-config

include $(ADK_TOPDIR)/mk/python3.mk

do-build:
	(cd $(WRKBUILD); env PYTHONPATH=$(PYTHON_LIBDIR) $(PYTHON) ./setup.py --curl-config=$(CURL_CONFIG) build)
	(cd $(WRKBUILD); env PYTHONPATH=$(PYTHON_LIBDIR) $(PYTHON) ./setup.py --curl-config=$(CURL_CONFIG) install --prefix="$(WRKINST)/usr")

do-install:
	$(INSTALL_DIR) $(IDIR_PYCURL)/usr/lib/python$(PYTHON_VERSION)/site-packages
	$(CP) $(WRKINST)/usr/lib/python$(PYTHON_VERSION)/site-packages/* \
		$(IDIR_PYCURL)/usr/lib/python$(PYTHON_VERSION)/site-packages

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
