# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		dbus-python
PKG_VERSION:=		1.3.2
PKG_RELEASE:=		1
PKG_HASH:=		ad67819308618b5069537be237f8e68ca1c7fcc95ee4a121fe6845b1418248f8
PKG_DESCR:=		python bindings for dbus
PKG_SECTION:=		dev/python
PKG_DEPENDS:=		dbus dbus-glib
PKG_BUILDDEP:=		dbus dbus-glib
PKG_URL:=		http://dbus.freedesktop.org/doc/dbus-python/
PKG_SITES:=		http://dbus.freedesktop.org/releases/dbus-python/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DBUS_PYTHON,dbus-python,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

include $(ADK_TOPDIR)/mk/python3.mk

dbus-python-install:
	$(INSTALL_DIR) $(IDIR_DBUS_PYTHON)/usr/lib/python$(PYTHON_VERSION)/site-packages/
	$(CP) $(WRKINST)/usr/lib/python$(PYTHON_VERSION)/site-packages/*.so \
		$(IDIR_DBUS_PYTHON)/usr/lib/python$(PYTHON_VERSION)/site-packages/
	$(INSTALL_DIR) $(IDIR_DBUS_PYTHON)/usr/lib/python$(PYTHON_VERSION)/site-packages/dbus
	$(CP) $(WRKINST)/usr/lib/python$(PYTHON_VERSION)/site-packages/dbus/*.py \
		$(IDIR_DBUS_PYTHON)/usr/lib/python$(PYTHON_VERSION)/site-packages/dbus/
	$(INSTALL_DIR) $(IDIR_DBUS_PYTHON)/usr/lib/python$(PYTHON_VERSION)/site-packages/dbus/mainloop
	$(CP) $(WRKINST)/usr/lib/python$(PYTHON_VERSION)/site-packages/dbus/mainloop/*.py \
		$(IDIR_DBUS_PYTHON)/usr/lib/python$(PYTHON_VERSION)/site-packages/dbus/mainloop

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
