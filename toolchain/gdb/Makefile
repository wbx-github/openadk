# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc
include ${ADK_TOPDIR}/mk/buildhlp.mk

GDB_BUILD_DIR:=		$(WRKBUILD)-obj

ifeq (${ADK_MAKE_PARALLEL},y)
GDB_MAKEOPTS+=		-j${ADK_MAKE_JOBS}
endif

ifeq ($(ADK_TARGET_SIM),y)
CONFIGURE_ARGS:=	--enable-sim --enable-sim-stdio
else
CONFIGURE_ARGS:= 	--disable-sim
endif

$(WRKBUILD)/.configured:
	$(SED) 's/install_to_$(INSTALL_DEST) //' ${WRKBUILD}/libiberty/Makefile.in
	mkdir -p $(GDB_BUILD_DIR)
	(cd $(GDB_BUILD_DIR); PATH='$(HOST_PATH)' \
		gdb_cv_func_sigsetjmp=yes \
		M4='${STAGING_HOST_DIR}/usr/bin/m4' \
		$(WRKBUILD)/configure \
		--prefix=$(STAGING_HOST_DIR) \
		--build=$(GNU_HOST_NAME) \
		--host=$(GNU_HOST_NAME) \
		--target=$(GNU_TARGET_NAME) \
		--with-libgmp-prefix='${STAGING_HOST_DIR}/usr' \
		--disable-dependency-tracking \
		--without-uiout \
		--enable-gdbmi \
		--disable-gdbtk \
		--without-included-gettext \
		--disable-libtool-lock \
		--disable-nls \
		--with-curses \
		--enable-threads \
		--disable-tui \
		--disable-werror \
		--disable-install-libiberty \
		--without-python \
		--without-x \
		$(CONFIGURE_ARGS) \
	);
	touch $@

$(WRKBUILD)/.compiled:
	PATH='$(HOST_PATH)' $(MAKE) ${GDB_MAKEOPTS} -C $(GDB_BUILD_DIR) CFLAGS="-fPIC ${CFLAGS_FOR_BUILD}"
	touch $@

$(WRKBUILD)/.installed:
	$(INSTALL_BIN) $(GDB_BUILD_DIR)/gdb/gdb $(TARGET_CROSS)gdb
ifeq ($(ADK_TARGET_SIM),y)
ifeq ($(ADK_TARGET_ARCH_BFIN),y)
	$(INSTALL_BIN) $(GDB_BUILD_DIR)/sim/bfin/run $(TARGET_CROSS)run
endif
ifeq ($(ADK_TARGET_ARCH_FRV),y)
	$(INSTALL_BIN) $(GDB_BUILD_DIR)/sim/frv/run $(TARGET_CROSS)run
endif
ifeq ($(ADK_TARGET_ARCH_H8300),y)
	$(INSTALL_BIN) $(GDB_BUILD_DIR)/sim/h8300/run $(TARGET_CROSS)run
endif
endif
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
