# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		freeswitch
PKG_VERSION:=		1.10.11
PKG_RELEASE:=		1
PKG_HASH:=		4437edfa08558aa407c9fad5e4eed58f757357c53ca735aed9977e48aa1c53e3
PKG_DESCR:=		cross-platform telephony platform
PKG_SECTION:=		net/voip
PKG_DEPENDS:=		libpcre libcurl zlib libjpeg-turbo libsqlite
PKG_DEPENDS+=		libressl libopus spandsp sofia-sip
PKG_BUILDDEP:=		util-linux zlib libjpeg-turbo sqlite curl pcre
PKG_BUILDDEP+=		speex libressl opus spandsp sofia-sip
PKG_URL:=		http://www.freeswitch.org/
PKG_SITES:=		https://github.com/signalwire/freeswitch/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FREESWITCH,freeswitch,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	bootstrap
CONFIGURE_ARGS+=	--disable-core-libedit-support \
			--disable-libvpx
CONFIGURE_ENV+=		ac_cv_file__dev_ptmx=yes \
			ac_cv_file__dev_zero=yes \
			ac_cv_file__dev_urandom=yes \
			ac_cv_sizeof_ssize_t=4 \
		 	ac_cv_func_realloc_0_nonnull=yes \
		       	ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_gcc_supports_w_no_unused_result=no \
			apr_cv_tcp_nodelay_with_cork=yes \
			apr_cv_process_shared_works=no \
			ac_cv_file_dbd_apr_dbd_mysql_c=no \
			ac_cv_func_setpgrp_void=yes

pre-configure:
	$(SED) "/applications\/mod_av/d" $(WRKBUILD)/modules.conf
	$(SED) "/applications\/mod_enum/d" $(WRKBUILD)/modules.conf
	$(SED) "/applications\/mod_fsv/d" $(WRKBUILD)/modules.conf
	$(SED) "/applications\/mod_signalwire/d" $(WRKBUILD)/modules.conf
	$(SED) "/applications\/mod_spandsp/d" $(WRKBUILD)/modules.conf
	$(SED) "/databases\/mod_pgsql/d" $(WRKBUILD)/modules.conf
	$(SED) "/languages\/mod_lua/d" $(WRKBUILD)/modules.conf
	$(SED) "/endpoints\/mod_sofia/d" $(WRKBUILD)/modules.conf
	$(SED) "/endpoints\/mod_verto/d" $(WRKBUILD)/modules.conf
	$(SED) "/codecs\/mod_vpx/d" $(WRKBUILD)/modules.conf
	$(SED) "/formats\/mod_sndfile/d" $(WRKBUILD)/modules.conf

freeswitch-install:
	$(INSTALL_DIR) $(IDIR_FREESWITCH)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/freeswitch \
		$(IDIR_FREESWITCH)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
