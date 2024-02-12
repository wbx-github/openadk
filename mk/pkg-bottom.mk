# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.
# Comments:
# * pre/do/post-foo are always defined here, but empty. This is so
#   that we can call it (BSD make has .if target(foo) but GNU not)
#   and it won't error out.
# * ${_foo_COOKIE} are the actual targets
# * default is "auto" 
# * define "manual" if you need your own method
#   -> define a do-foo: target in the Makefile
# * if you have a style -> define a pre-foo: and post-foo: if they
#   are required, but the do-foo: magic is done here

PKG_LIBNAME?=	$(PKG_NAME)

ifeq ($(ADK_TARGET_USE_SHARED_LIBS_ONLY),y)
CONFIGURE_LIB:=--disable-static --enable-shared
endif
ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
CONFIGURE_LIB:=--enable-static --disable-shared
endif
ifeq ($(ADK_TARGET_USE_SHARED_AND_STATIC_LIBS)$(ADK_TARGET_USE_STATIC_AND_SHARED_LIBS),y)
CONFIGURE_LIB:=--enable-static --enable-shared
endif

pre-configure:
do-configure:
post-configure:
${_CONFIGURE_COOKIE}: ${_PATCH_COOKIE}
ifneq (,$(filter bootstrap,${AUTOTOOL_STYLE}))
	@$(CMD_TRACE) "autotooling.. "
	@cd ${WRKSRC}; env ${AUTOTOOL_ENV} $(BASH) bootstrap* $(MAKE_TRACE)
endif
ifneq (,$(filter autogen,${AUTOTOOL_STYLE}))
	@$(CMD_TRACE) "autotooling.. "
	@cd ${WRKSRC}; env ${AUTOTOOL_ENV} $(BASH) autogen.sh $(MAKE_TRACE)
endif
ifneq (,$(filter autoconf,${AUTOTOOL_STYLE}))
	@$(CMD_TRACE) "autotooling.. "
	@cd ${WRKSRC}; env ${AUTOTOOL_ENV} autoconf $(MAKE_TRACE)
endif
ifneq (,$(filter autoreconf,${AUTOTOOL_STYLE}))
	@$(CMD_TRACE) "autotooling.. "
	@cd ${WRKSRC}; env ${AUTOTOOL_ENV} autoreconf -vif $(MAKE_TRACE)
	@rm -rf ${WRKSRC}/autom4te.cache
	@touch ${WRKDIR}/.autoreconf_done
endif
	mkdir -p ${WRKBUILD}
	@${MAKE} pre-configure $(MAKE_TRACE)

ifneq ($(filter manual,${CONFIG_STYLE}),)
	env ${CONFIGURE_ENV} ${MAKE} do-configure $(MAKE_TRACE)
else ifneq ($(filter meson,${CONFIG_STYLE}),)
	@$(CMD_TRACE) "configuring meson.. "
	(cd ${WRKSRC} && $(MESON_ENV) \
		meson setup --prefix /usr --libdir lib \
		 --cross-file $(STAGING_HOST_DIR)/etc/meson/cross-compilation.conf \
		 --build.pkg-config-path $(STAGING_HOST_DIR)/usr/lib/pkgconfig \
		 --buildtype release $(MESON_FLAGS) \
		$(WRKSRC) $(WRKBUILD)) $(MAKE_TRACE)
else ifneq ($(filter cmake,${CONFIG_STYLE}),)
	@$(CMD_TRACE) "configuring cmake.. "
	sed -e "s#@@TARGET_CC@@#$(TARGET_CC_NO_CCACHE)#" \
	 	-e "s#@@TARGET_CXX@@#$(TARGET_CXX_NO_CCACHE)#" \
		-e "s#@@TARGET_CFLAGS@@#$(TARGET_CFLAGS)#" \
		-e "s#@@TARGET_CXXFLAGS@@#$(TARGET_CXXFLAGS)#" \
		-e "s#@@TARGET_ARCH@@#$(ADK_TARGET_ARCH)#" \
		-e "s#@@STAGING_TARGET_DIR@@#$(STAGING_TARGET_DIR)#g" \
		-e "s#@@STAGING_HOST_DIR@@#$(STAGING_HOST_DIR)#g" \
		$(SCRIPT_DIR)/toolchain.cmake.in > $(SCRIPT_DIR)/toolchain.cmake
	(cd ${WRKBUILD} && PATH='${HOST_PATH}' \
		cmake -Wno-dev -DCMAKE_INSTALL_PREFIX:PATH=/usr \
			-DCMAKE_TOOLCHAIN_FILE="$(SCRIPT_DIR)/toolchain.cmake" \
			${CMAKE_FLAGS} ${WRKSRC}) $(MAKE_TRACE)
else ifneq ($(filter minimal,${CONFIG_STYLE}),)
	@$(CMD_TRACE) "configuring.. "
	cd ${WRKBUILD}; rm -f config.{cache,status}; \
	    env ${CONFIGURE_ENV} \
	    ${BASH} ${WRKSRC}/${CONFIGURE_PROG} \
	    ${CONFIGURE_ARGS} $(MAKE_TRACE)
else ifneq ($(filter basic,${CONFIG_STYLE}),)
	@$(CMD_TRACE) "configuring.. "
	cd ${WRKBUILD}; rm -f config.{cache,status}; \
	    env ${CONFIGURE_ENV} \
	    ${BASH} ${WRKSRC}/${CONFIGURE_PROG} ${CONFIGURE_TRIPLE} \
	    ${CONFIGURE_ARGS} $(MAKE_TRACE)
else ifneq ($(filter perl,${CONFIG_STYLE}),)
	@$(CMD_TRACE) "configuring perl module.. "
	if [ -f ${WRKBUILD}/Makefile.PL ]; then \
		cd ${WRKBUILD}; \
			PATH='${HOST_PATH}' \
			PERL_MM_USE_DEFAULT=1 \
			PERL_AUTOINSTALL=--skipdeps \
			$(PERL_ENV) \
			perl-host Makefile.PL ${CONFIGURE_ARGS}; \
	else \
		cd ${WRKBUILD}; \
			PATH='${HOST_PATH}' \
			$(PERL_ENV) \
			perl-host Build.PL; \
	fi
else ifeq ($(strip ${CONFIG_STYLE}),)
	@$(CMD_TRACE) "configuring.. "
	cd ${WRKBUILD}; rm -f config.{cache,status}; \
	    env ${CONFIGURE_ENV} \
	    ${BASH} ${WRKSRC}/${CONFIGURE_PROG} ${CONFIGURE_TRIPLE} \
	    --program-prefix= \
	    --program-suffix= \
	    --prefix=/usr \
	    --bindir=/usr/bin \
	    --datadir=/usr/share \
	    --mandir=/usr/share/man \
	    --libexecdir=/usr/libexec \
	    --localstatedir=/var \
	    --sysconfdir=/etc \
	    --disable-dependency-tracking \
	    --disable-libtool-lock \
	    --disable-nls \
	    ${CONFIGURE_LIB} \
	    ${CONFIGURE_ARGS} $(MAKE_TRACE)
else
	@echo "Invalid CONFIG_STYLE '${CONFIG_STYLE}'" >&2
	@exit 1
endif
	@${MAKE} post-configure $(MAKE_TRACE)
	@touch $@

# do a parallel build if requested && package doesn't force disable it
ifeq (${ADK_MAKE_PARALLEL},y)
ifeq ($(strip ${PKG_NOPARALLEL}),)
MAKE_FLAGS+=		-j${ADK_MAKE_JOBS}
endif
endif

pre-build:
do-build:
post-build:
${_BUILD_COOKIE}: ${_CONFIGURE_COOKIE}
	@env ${MAKE_ENV} ${MAKE} pre-build $(MAKE_TRACE)
	@$(CMD_TRACE) "compiling.. "
ifneq ($(filter meson,${BUILD_STYLE}),)
	PATH='$(HOST_PATH)' ninja -v -C $(WRKBUILD) $(MAKE_TRACE)
else ifneq ($(filter manual,${BUILD_STYLE}),)
	env ${MAKE_ENV} ${MAKE} ${MAKE_FLAGS} do-build $(MAKE_TRACE)
else ifeq ($(strip ${BUILD_STYLE}),)
	cd ${WRKBUILD} && env ${MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
	    ${MAKE_FLAGS} ${ALL_TARGET} $(MAKE_TRACE)
else
	@echo "Invalid BUILD_STYLE '${BUILD_STYLE}'" >&2
	@exit 1
endif
	@env ${MAKE_ENV} ${MAKE} post-build $(MAKE_TRACE)
	touch $@

pre-install:
do-install:
post-install:
spkg-install: ${ALL_POSTINST}
${_FAKE_COOKIE}: ${_BUILD_COOKIE}
	@-rm -f ${_ALL_CONTROLS}
	@mkdir -p '${STAGING_PKG_DIR}/stamps' ${WRKINST} '${STAGING_TARGET_DIR}/scripts'
	@${MAKE} -j${ADK_MAKE_JOBS} ${_ALL_CONTROLS} $(MAKE_TRACE)
	@env ${MAKE_ENV} ${MAKE} pre-install $(MAKE_TRACE)
ifneq ($(filter meson,${INSTALL_STYLE}),)
	DESTDIR='$(WRKINST)' PATH='$(HOST_PATH)' \
		ninja -C $(WRKBUILD) install $(MAKE_TRACE)
else ifneq ($(filter manual,${INSTALL_STYLE}),)
	env ${MAKE_ENV} ${MAKE} do-install $(MAKE_TRACE)
else ifeq ($(strip ${INSTALL_STYLE}),)
	cd ${WRKBUILD} && env ${MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
	    DESTDIR='${WRKINST}' ${FAKE_FLAGS} ${INSTALL_TARGET} $(MAKE_TRACE)
	env ${MAKE_ENV} ${MAKE} post-install $(MAKE_TRACE)
else
	@echo "Invalid INSTALL_STYLE '${INSTALL_STYLE}'" >&2
	@exit 1
endif
	env ${MAKE_ENV} ${MAKE} spkg-install $(MAKE_TRACE)
	@rm -f '${STAGING_PKG_DIR}/${PKG_NAME}.scripts'
	@for a in ${WRKINST}/usr/bin/*-config*; do \
		[[ -e $$a ]] || continue; \
		sed -e "s,^prefix=.*,prefix=${STAGING_TARGET_DIR}/usr," $$a > \
		${STAGING_TARGET_DIR}/usr/bin/$$(basename $$a); \
		chmod u+x ${STAGING_TARGET_DIR}/usr/bin/$$(basename $$a); \
		[[ "$$(basename $$a)" != "pkg-config" ]] && cp ${STAGING_TARGET_DIR}/usr/bin/$$(basename $$a) ${STAGING_TARGET_DIR}/scripts; \
		echo "scripts/$$(basename $$a)" \
		    >>'${STAGING_PKG_DIR}/${PKG_NAME}.scripts'; \
	done
ifeq (,$(filter noremove,${PKG_OPTS}))
	@if test -s '${STAGING_PKG_DIR}/${PKG_NAME}'; then \
		cd '${STAGING_TARGET_DIR}'; \
		while read fn; do \
			rm -f "$$fn"; \
		done <'${STAGING_PKG_DIR}/${PKG_NAME}'; \
	fi
endif
	@rm -f '${STAGING_PKG_DIR}/${PKG_NAME}'
ifneq (,$(filter dev,${PKG_OPTS}))
	@mkdir -p  $(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(PKG_LIBNAME)-dev/usr/include
	@test -d ${WRKINST}/usr/include && cd ${WRKINST}/usr/include; \
	    find . -name \*.h | \
	    $(CPIO) -padlmu --quiet $(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(PKG_LIBNAME)-dev/usr/include
	@mkdir -p  $(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(PKG_LIBNAME)-dev/usr/lib/pkgconfig
	@test -d ${WRKINST}/usr/lib/pkgconfig && cd ${WRKINST}/usr/lib/pkgconfig; \
	    find . -name \*.pc | \
	    $(CPIO) -padlmu --quiet $(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(PKG_LIBNAME)-dev/usr/lib/pkgconfig
	@for a in ${WRKINST}/usr/bin/*-config*; do \
		[[ -e $$a ]] || continue; \
		mkdir -p $(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(PKG_LIBNAME)-dev/usr/bin; \
		cp $$a $(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(PKG_LIBNAME)-dev/usr/bin; \
		chmod 755 $(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(PKG_LIBNAME)-dev/usr/bin/$$(basename $$a); \
	done
endif
ifeq (,$(filter nostaging,${PKG_OPTS}))
	@-cd ${WRKINST}; \
	    find usr ! -type d 2>/dev/null | \
	    grep -E -v -e '^usr/src' -e '^usr/doc' -e '^usr/local' -e '^usr/man' -e '^usr/info' \
			-e '^usr/lib/libc.so' -e '^usr/bin/[a-z0-9-]+-config*' -e '^usr/lib/.*\.la$$' \
			-e '^/usr/lib/libpthread_nonshared.a' | \
	    tee '${STAGING_PKG_DIR}/${PKG_NAME}' | \
	    $(CPIO) -padlmu --quiet '${STAGING_TARGET_DIR}'
endif
ifeq (,$(filter noscripts,${PKG_OPTS}))
	@cd '${STAGING_TARGET_DIR}'; grep 'usr/s*bin/' \
	    '${STAGING_PKG_DIR}/${PKG_NAME}' | \
	    while read fn; do \
		b="$$(dd if="$$fn" bs=2 count=1 2>/dev/null)"; \
		[[ $$b = '#!' ]] || continue; \
		cp "$$fn" scripts/; \
		echo "scripts/$$(basename "$$fn")" \
		    >>'${STAGING_PKG_DIR}/${PKG_NAME}'; \
	done
endif
	-@test -e '${STAGING_PKG_DIR}/${PKG_NAME}.scripts' && \
	cat '${STAGING_PKG_DIR}/${PKG_NAME}.scripts' >> '${STAGING_PKG_DIR}/${PKG_NAME}' || :
	touch $@

${_IPKGS_COOKIE}:
	exec ${MAKE} package

package: ${ALL_IPKGS}
ifneq ($(DEVELOPER),)
	@cd ${WRKDIR}/fake-${ADK_TARGET_CPU_ARCH} || exit 1; \
	y=; sp=; for x in ${ALL_IDIRS}; do \
		y="$$y$$sp$${x#$(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/}"; \
		sp=' '; \
	done; ls=; ln=; x=1; [[ -z $$y ]] || \
	    md5sum $$(find $$y -type f) | sed -e "s/*//" | \
	    while read sum name; do \
		inode=$$(ls -i "$$name"); \
		echo "$$sum $${inode%% *} $$name"; \
	    done | sort | while read sum inode name; do \
		if [[ $$sum = $$ls ]]; then \
			[[ $$li = $$inode ]] && continue; \
			case $$x in \
			1)	echo 'WARNING: duplicate files found in' \
				    'package "${PKG_NAME}"! Fix them.' >&2; \
				echo -n "> $$ln "; \
				;; \
			2)	echo -n "> $$ln "; \
				;; \
			3)	echo -n ' '; \
				;; \
			esac; \
			echo -n "$$name"; \
			x=3; \
		else \
			case $$x in \
			3)	echo; \
				x=2; \
				;; \
			esac; \
		fi; \
		ls=$$sum; \
		ln=$$name; \
		li=$$inode; \
	done
endif
	touch ${_IPKGS_COOKIE}

clean-targets: clean-dev-generic

clean-dev-generic:
ifeq (,$(filter noremove,${PKG_OPTS}))
	@if test -s '${STAGING_PKG_DIR}/${PKG_NAME}'; then \
		cd '${STAGING_TARGET_DIR}'; \
		while read fn; do \
			rm -f "$$fn"; \
		done <'${STAGING_PKG_DIR}/${PKG_NAME}'; \
	fi
endif
	@rm -f '${STAGING_PKG_DIR}/${PKG_NAME}'

ifneq (,$(filter autoreconf,${AUTOTOOL_STYLE}))
DIFF_IGNOREFILES?=	configure missing depcomp install-sh INSTALL \
			aclocal.m4 config.h.in Makefile.in */Makefile.in \
			config.sub config.guess */config.sub */config.guess
else
DIFF_IGNOREFILES?=	config.sub config.guess */config.sub */config.guess
endif
