# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		py-spidev
PKG_VERSION:=		1c713aaaad1f611d675d9188d2d5a6401fbb8843
PKG_RELEASE:=		1
PKG_GIT:=		hash
PKG_DESCR:=		module for interfacing with spi devices from user space via the spidev linux kernel driver
PKG_SECTION:=		dev/python
PKG_DEPENDS:=		python3
PKG_BUILDDEP:=		python3
PKG_URL:=		https://github.com/doceme/py-spidev
PKG_SITES:=		https://github.com/doceme/py-spidev.git

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PY_SPIDEV,py-spidev,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

include $(ADK_TOPDIR)/mk/python3.mk

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

MAKE_ENV+=		LDSHARED="$(TARGET_CC) -shared"

do-build:
	cd $(WRKBUILD); env PYTHONPATH=$(PYTHON_LIBDIR) $(PYTHON) ./setup.py install --prefix="$(WRKINST)/usr"

do-install:
	$(INSTALL_DIR) $(IDIR_PY_SPIDEV)/usr/lib/python$(PYTHON_VERSION)/site-packages
	$(CP) $(WRKINST)/usr/lib/python$(PYTHON_VERSION)/site-packages/* \
		$(IDIR_PY_SPIDEV)/usr/lib/python$(PYTHON_VERSION)/site-packages

include $(ADK_TOPDIR)/mk/pkg-bottom.mk

