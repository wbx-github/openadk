# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		cherrypy
PKG_VERSION:=		5.1.0
PKG_RELEASE:=		1
PKG_HASH:=		5fccc9ad3bf9a1df83bbb934772f34f42571421bdd75f90f74c170b6c0ef13b1
PKG_DESCR:=		python web framework
PKG_SECTION:=		dev/python	
PKG_DEPENDS:=		python3
PKG_BUILDDEP:=		python3
PKG_URL:=		http://www.cherrypy.org/
PKG_SITES:=		https://pypi.python.org/packages/source/C/CherryPy/

DISTFILES:=		CherryPy-${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/CherryPy-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CHERRYPY,cherrypy,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

include $(ADK_TOPDIR)/mk/python3.mk

do-build:
	cd $(WRKBUILD); env PYTHONPATH=$(PYTHON_LIBDIR) $(PYTHON) ./setup.py build
	cd $(WRKBUILD); env PYTHONPATH=$(PYTHON_LIBDIR) $(PYTHON) ./setup.py install --prefix="$(WRKINST)/usr"

do-install:
	$(INSTALL_DIR) $(IDIR_CHERRYPY)/usr/bin
	$(INSTALL_DIR) $(IDIR_CHERRYPY)/usr/lib/python$(PYTHON_VERSION)
	$(CP) $(WRKINST)/usr/lib/python$(PYTHON_VERSION)/* $(IDIR_CHERRYPY)/usr/lib/python$(PYTHON_VERSION)
	$(CP) $(WRKINST)/usr/lib/python$(PYTHON_VERSION)/site-packages/CherryPy-$(PKG_VERSION)-py3.9.egg/cherrypy/cherryd $(IDIR_CHERRYPY)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
