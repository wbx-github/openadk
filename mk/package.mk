# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

all: build-all-pkgs

# does not change CONFIGURE_ARGS in minimal mode
ifeq ($(filter minimal,${CONFIG_STYLE}),)
ifneq ($(ADK_DEBUG),)
CONFIGURE_ARGS+=	--enable-debug
endif
endif

AUTOTOOL_ENV+=		PATH='${HOST_PATH}' \
			PKG_CONFIG_LIBDIR='${STAGING_TARGET_DIR}/usr/lib/pkgconfig:${STAGING_TARGET_DIR}/usr/share/pkgconfig' \
			PKG_CONFIG_SYSROOT_DIR='${STAGING_TARGET_DIR}' \
			${COMMON_ENV}

MESON_ENV+=		PATH='${HOST_PATH}' \
			PKG_CONFIG_LIBDIR='${STAGING_TARGET_DIR}/usr/lib/pkgconfig:${STAGING_TARGET_DIR}/usr/share/pkgconfig' \
			PKG_CONFIG_SYSROOT_DIR='${STAGING_TARGET_DIR}'

CONFIGURE_ENV+=		PATH='${TARGET_PATH}' \
			${COMMON_ENV} \
			${TARGET_ENV} \
			PKG_CONFIG_LIBDIR='${STAGING_TARGET_DIR}/usr/lib/pkgconfig:${STAGING_TARGET_DIR}/usr/share/pkgconfig' \
			PKG_CONFIG_SYSROOT_DIR='${STAGING_TARGET_DIR}' \
			cross_compiling=yes

CONFIGURE_PROG?=	configure
MAKE_FILE?=		Makefile
# this is environment for 'make all' and 'make install'
MAKE_ENV?=
# this is arguments for 'make all' and 'make install'
XAKE_FLAGS?=
# this is arguments for 'make all' ONLY
MAKE_FLAGS?=
# this is arguments for 'make install' ONLY
FAKE_FLAGS?=
ALL_TARGET?=		all
INSTALL_TARGET?=	install

MAKE_ENV+=		PATH='${TARGET_PATH}' \
			${COMMON_ENV} \
			${TARGET_ENV} \
			PKG_CONFIG_LIBDIR='${STAGING_TARGET_DIR}/usr/lib/pkgconfig:${STAGING_TARGET_DIR}/usr/share/pkgconfig' \
			PKG_CONFIG_SYSROOT_DIR='${STAGING_TARGET_DIR}' \
			WRKDIR='${WRKDIR}' WRKDIST='${WRKDIST}' \
			WRKSRC='${WRKSRC}' WRKBUILD='${WRKBUILD}'

MAKE_FLAGS+=		${XAKE_FLAGS}
FAKE_FLAGS+=		${XAKE_FLAGS}

ifeq ($(strip ${WRKDIR_BSD}),)
WRKDIR_BASE:=		${BUILD_DIR}
else
WRKDIR_BASE:=		$(shell pwd)
endif

_EXTRACT_COOKIE=	${WRKDIST}/.extract_done
_PATCH_COOKIE=		${WRKDIST}/.prepared
_CONFIGURE_COOKIE=	${WRKBUILD}/.configure_done
_BUILD_COOKIE=		${WRKBUILD}/.build_done
_FAKE_COOKIE=		${WRKINST}/.fake_done
_IPKGS_COOKIE=		${STAGING_PKG_DIR}/stamps/${PKG_NAME}${PKG_VERSION}-${PKG_RELEASE}

_IN_PACKAGE:=		1
include ${ADK_TOPDIR}/mk/buildhlp.mk

# defined in buildhlp.mk ('extract' can fail, use 'patch' then)
extract: ${_EXTRACT_COOKIE}
patch: ${_PATCH_COOKIE}

# defined below (will be moved to pkg-bottom.mk!)
configure: ${_CONFIGURE_COOKIE}
build: ${_BUILD_COOKIE}
fake: ${_FAKE_COOKIE}

# our recursive build entry point
build-all-pkgs: ${_IPKGS_COOKIE}

# there are some parameters to the PKG_template function
# 1.) Config.in identifier ADK_PACKAGE_$(1)
# 2.) name of the package, for single package mostly $(PKG_NAME)
# 3.) package version (upstream version) and package release (adk version),
#     always $(PKG_VERSION)-$(PKG_RELEASE)
# 4.) dependencies to other packages, $(PKG_DEPENDS)
# 5.) description for the package, $(PKG_DESCR)
# 6.) section of the package, $(PKG_SECTION)  
# 7.) special package options $(PKG_OPTS)
#     noscripts -> do not install scripts to $(STAGING_TARGET_DIR)/scripts
#		  (needed for example for autoconf/automake)
#     noremove -> do not remove files from $(STAGING_TARGET_DIR) while
#                 cleaning (needed for toolchain packages like glibc)
#     nostaging -> do not install files to $(STAGING_TARGET_DIR)
#     nostrip -> do not strip files
#     dev -> create a development subpackage with headers and pkg-config files
#     devonly -> create a development package only
# should be package format independent and modular in the future
define PKG_template
ALL_PKGOPTS+=	$(1)
PKGNAME_$(1)=	$(2)
PKGDEPS_$(1)=	$(4)
PKGDESC_$(1)=	$(5)
PKGSECT_$(1)=	$(6)
IPKG_$(1)=	$(PACKAGE_DIR)/$(2)_$(3)_${ADK_TARGET_CPU_ARCH}.${PKG_SUFFIX}
IPKG_$(1)_DEV=	$(PACKAGE_DIR)/$(2)-dev_$(3)_${ADK_TARGET_CPU_ARCH}.${PKG_SUFFIX}
IPKG_$(1)_DBG=	$(PACKAGE_DIR)/$(2)-dbg_$(3)_${ADK_TARGET_CPU_ARCH}.${PKG_SUFFIX}
IDIR_$(1)=	$(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(2)
IDIR_$(1)_DEV=	$(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(2)-dev
IDIR_$(1)_DBG=	$(WRKDIR)/fake-${ADK_TARGET_CPU_ARCH}/pkg-$(2)-dbg
ifneq (${ADK_PACKAGE_$(1)}${DEVELOPER},)
ifneq (,$(filter dev,$(7)))
ifneq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
ifneq ($(ADK_TARGET_BINFMT_FLAT),y)
ALL_IPKGS+=	$$(IPKG_$(1))
ALL_IDIRS+=	$${IDIR_$(1)}
ALL_POSTINST+=	$(2)-install
$(2)-install:
endif
endif
else
ALL_IPKGS+=	$$(IPKG_$(1))
ALL_IDIRS+=	$${IDIR_$(1)}
ALL_POSTINST+=	$(2)-install
$(2)-install:
endif
endif
INFO_$(1)=	$(PKG_STATE_DIR)/info/$(2).list
INFO_$(1)_DEV=	$(PKG_STATE_DIR)/info/$(2)-dev.list
INFO_$(1)_DBG=	$(PKG_STATE_DIR)/info/$(2)-dbg.list

ifeq ($(ADK_PACKAGE_$(1)),y)

ifeq (,$(filter devonly,$(7)))
ifeq ($(ADK_PACKAGE_$(1)_DBG),y)
install-targets: $$(INFO_$(1)) $$(INFO_$(1)_DBG)
ifeq ($(ADK_PACKAGE_$(1)_DEV),y)
install-targets: $$(INFO_$(1)) $$(INFO_$(1)_DBG) $$(INFO_$(1)_DEV)
else
install-targets: $$(INFO_$(1)) $$(INFO_$(1)_DBG)
endif
else
ifeq ($(ADK_PACKAGE_$(1)_DEV),y)
install-targets: $$(INFO_$(1)) $$(INFO_$(1)_DEV)
else
install-targets: $$(INFO_$(1))
endif
endif
else
install-targets: $$(INFO_$(1))
endif

endif

IDEPEND_$(1):=	$$(strip $(4))

_ALL_CONTROLS+=	$$(IDIR_$(1))/CONTROL/control
ICONTROL_$(1)?=	$(WRKDIR)/.$(2).control
ICONTROL_$(1)_DEV?= $(WRKDIR)/.$(2)-dev.control
ICONTROL_$(1)_DBG?= $(WRKDIR)/.$(2)-dbg.control
$$(IDIR_$(1))/CONTROL/control: ${_PATCH_COOKIE}
	@echo "Package: $$(shell echo $(2) | tr '_' '-')" > $(WRKDIR)/.$(2).control
	@echo "Section: $(6)" >> $(WRKDIR)/.$(2).control
	@echo "Description: $(5)" >> $(WRKDIR)/.$(2).control
	@${BASH} ${SCRIPT_DIR}/make-ipkg-dir.sh $${IDIR_$(1)} $${ICONTROL_$(1)} $(3) ${ADK_TARGET_CPU_ARCH}
	@adeps='$$(strip $${IDEPEND_$(1)})'; if [[ -n $$$$adeps ]]; then \
		comma=; \
		deps=; \
		last=; \
		for dep in $$$$adeps; do \
			if [[ $$$$last = kernel && $$$$dep = \(* ]]; then \
				deps="$$$$deps $$$$dep"; \
			else \
				deps="$$$$deps$$$$comma$$$$dep"; \
			fi; \
			comma=", "; \
			last=$$$$dep; \
		done; \
		echo "Depends: $$$$deps" | tr '_' '-' >>$${IDIR_$(1)}/CONTROL/control; \
	fi
	@for file in conffiles preinst postinst prerm postrm; do \
		[ ! -f ./files/$(2).$$$$file ] || cp ./files/$(2).$$$$file $$(IDIR_$(1))/CONTROL/$$$$file; \
	done
ifeq ($(ADK_BUILD_WITH_DEBUG),y)
	@echo "Package: $$(shell echo $(2) | tr '_' '-')-dbg" > $(WRKDIR)/.$(2)-dbg.control
	@echo "Section: debug" >> $(WRKDIR)/.$(2)-dbg.control
	@echo "Description: debugging symbols for $(2)" >> $(WRKDIR)/.$(2)-dbg.control
	@${BASH} ${SCRIPT_DIR}/make-ipkg-dir.sh $${IDIR_$(1)_DBG} $${ICONTROL_$(1)_DBG} $(3) ${ADK_TARGET_CPU_ARCH}
	@echo "Depends: $$(shell echo $(2) | tr '_' '-')" >> $${IDIR_$(1)_DBG}/CONTROL/control
endif
ifneq (,$(filter dev,$(7)))
	@echo "Package: $$(shell echo $(2) | tr '_' '-')-dev" > $(WRKDIR)/.$(2)-dev.control
	@echo "Section: devel" >> $(WRKDIR)/.$(2)-dev.control
	@echo "Description: development files for $(2)" >> $(WRKDIR)/.$(2)-dev.control
	@${BASH} ${SCRIPT_DIR}/make-ipkg-dir.sh $${IDIR_$(1)_DEV} $${ICONTROL_$(1)_DEV} $(3) ${ADK_TARGET_CPU_ARCH}
	@echo "Depends: $$(shell echo $(2) | tr '_' '-')" >> $${IDIR_$(1)_DEV}/CONTROL/control
endif

$$(IPKG_$(1)): $$(IDIR_$(1))/CONTROL/control $${_FAKE_COOKIE}
ifeq (,$(filter nostrip,$(7)))
ifeq ($(ADK_DEBUG),)
	@$${RSTRIP} $${IDIR_$(1)} $(MAKE_TRACE)
endif
ifeq ($(ADK_DEBUG_STRIP),y)
	@$${RSTRIP} $${IDIR_$(1)} $(MAKE_TRACE)
endif
endif
ifeq (${ADK_LEAVE_ETC_ALONE}$(filter force_etc,$(7)),y)
	-rm -rf $${IDIR_$(1)}/etc
else
ifeq (${ADK_INSTALL_PACKAGE_INIT_SCRIPTS},y)
	@for file in $$$$(ls ./files/*.init 2>/dev/null); do \
		fname=$$$$(echo $$$$file| sed -e "s#.*/##" -e "s#.init##"); \
		check=$$$$(grep PKG $$$$file|cut -d ' '  -f 2); \
		if [ "$$$$check" == $(2) ];then \
			mkdir -p $$(IDIR_$(1))/etc/init.d && cp $$$$file $$(IDIR_$(1))/etc/init.d/$$$$fname; \
		fi; \
	done
	@cd $${IDIR_$(1)}; for script in etc/init.d/*; do \
		[[ -e $$$$script ]] || continue; \
		chmod 0755 "$$$$script"; \
	done
endif
ifneq (${ADK_INSTALL_PACKAGE_NETWORK_SCRIPTS},y)
	-@rm -rf $${IDIR_$(1)}/etc/network
endif
endif
	@mkdir -p $${PACKAGE_DIR} '$${STAGING_PKG_DIR}/stamps' \
	    '$${STAGING_TARGET_DIR}/scripts'
	@for file in $$$$(ls ./files/*.perm 2>/dev/null); do \
		cat $$$$file >> $${STAGING_TARGET_DIR}/scripts/permissions.sh; \
	done
ifeq (,$(filter noremove,$(7)))
	@if test -s '$${STAGING_PKG_DIR}/$(1)'; then \
		cd '$${STAGING_TARGET_DIR}'; \
		while read fn; do \
			rm -f "$$$$fn"; \
		done <'$${STAGING_PKG_DIR}/$(1)'; \
	fi
endif
	@rm -f '$${STAGING_PKG_DIR}/$(1)'
ifeq (,$(filter nostaging,$(7)))
	@-cd $${IDIR_$(1)}; \
	    x=$$$$(find tmp run -mindepth 1 2>/dev/null); if [[ -n $$$$x ]]; then \
		echo 'WARNING: $${IPKG_$(1)} installs files into a' \
		    'ramdisk location:' >&2; \
		echo "$$$$x" | sed 's/^/- /' >&2; \
	    fi; \
	    find usr ! -type d 2>/dev/null | \
	    grep -E -v -e '^usr/lib/pkgconfig' -e '^usr/share' -e '^usr/doc' -e '^usr/src' -e '^usr/man' \
		       -e '^usr/info' -e '^usr/lib/libc.so' -e '^usr/bin/[a-z0-9-]+-config' -e '^usr/lib/.*\.la$$$$' | \
	    tee '$${STAGING_PKG_DIR}/$(1)' | \
	    $(CPIO) -padlmu --quiet '$${STAGING_TARGET_DIR}'
endif
ifeq (,$(filter noscripts,$(7)))
	@cd '$${STAGING_TARGET_DIR}'; grep 'usr/s*bin/' \
	    '$${STAGING_PKG_DIR}/$(1)' | \
	    while read fn; do \
		b="$$$$(dd if="$$$$fn" bs=2 count=1 2>/dev/null)"; \
		[[ $$$$b = '#!' ]] || continue; \
		cp "$$$$fn" scripts/; \
		echo "scripts/$$$$(basename "$$$$fn")" \
		    >>'$${STAGING_PKG_DIR}/$(1)'; \
	done
endif

ifeq (,$(filter devonly,$(7)))
	PATH='$(HOST_PATH)' $${PKG_BUILD} $${IDIR_$(1)} $${PACKAGE_DIR} $(MAKE_TRACE)
ifneq ($(ADK_BUILD_WITH_DEBUG),)
	PATH='$(HOST_PATH)' $${PKG_BUILD} $${IDIR_$(1)_DBG} $${PACKAGE_DIR} $(MAKE_TRACE)
endif
endif
ifneq (,$(filter dev,$(7)))
	PATH='$(HOST_PATH)' $${PKG_BUILD} $${IDIR_$(1)_DEV} $${PACKAGE_DIR} $(MAKE_TRACE)
endif

clean-targets: clean-dev-$(1)

clean-dev-$(1):
ifeq (,$(filter noremove,$(7)))
	@if test -s '$${STAGING_PKG_DIR}/$(1)'; then \
		cd '$${STAGING_TARGET_DIR}'; \
		while read fn; do \
			rm -f "$$$$fn"; \
		done <'$${STAGING_PKG_DIR}/$(1)'; \
	fi
endif
	@rm -f '$${STAGING_PKG_DIR}/$(1)'

$$(INFO_$(1)): $$(IPKG_$(1))
	$(PKG_INSTALL) $$(IPKG_$(1))

$$(INFO_$(1)_DBG): $$(IPKG_$(1)_DBG)
	$(PKG_INSTALL) $$(IPKG_$(1)_DBG)

ifneq ($(1),UCLIBC_NG)
ifneq ($(1),GLIBC)
ifneq ($(1),MUSL)
$$(INFO_$(1)_DEV): $$(IPKG_$(1)_DEV)
	$(PKG_INSTALL) $$(IPKG_$(1)_DEV)
endif
endif
endif

endef

install-targets:
install:
	@$(CMD_TRACE) "installing.. "
	@$(MAKE) install-targets $(MAKE_TRACE)

clean-targets:
clean:
	@printf " --->  cleaning package build directories and files.. "
	@$(MAKE) clean-targets $(MAKE_TRACE)
	rm -rf ${WRKDIR} ${ALL_IPKGS} ${_IPKGS_COOKIE}
	@printf " done\n"

distclean: clean
	rm -f ${FULLDISTFILES}

.PHONY:	all refetch extract patch configure \
	build fake package install clean build-all-pkgs
