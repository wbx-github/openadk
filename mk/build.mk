# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

CONFIG_CONFIG_IN = Config.in
CONFIG = adk/config
DEFCONFIG=		ADK_DEBUG=n \
			ADK_PRELINK=n \
			ADK_BUILD_WITH_DEBUG=n \
			ADK_DISABLE_CHECKSUM=n \
			ADK_APPLIANCE_MPD=n \
			ADK_APPLIANCE_TOOLCHAIN=n \
			ADK_APPLIANCE_KODI=n \
			ADK_APPLIANCE_BRUTEFIR=n \
			ADK_APPLIANCE_TEST=n \
			ADK_APPLIANCE_FIREFOX=n \
			ADK_APPLIANCE_DEVELOPMENT=n \
			ADK_PACKAGE_BUSYBOX_HIDE=n \
			ADK_DISABLE_KERNEL_PATCHES=n \
			ADK_DISABLE_TARGET_KERNEL_PATCHES=n \
			ADK_MAKE_PARALLEL=y \
			ADK_MAKE_JOBS=4 \
			ADK_LEAVE_ETC_ALONE=n \
			ADK_SIMPLE_NETWORK_CONFIG=n \
			ADK_USE_CCACHE=n \
			ADK_RUNTIME_START_SERVICES=n \
			ADK_PACKAGE_BASE_FILES=y \
			ADK_PACKAGE_DBUS_WITH_SYSTEMD=n \
			ADK_PACKAGE_KEXECINIT=n \
			ADK_PACKAGE_CLASSPATH=n \
			ADK_PACKAGE_LM_SENSORS_DETECT=n \
			ADK_PACKAGE_CRYPTINIT=n \
			ADK_STATIC_TOOLCHAIN=n \
			ADK_TOOLCHAIN_WITH_SSP=n \
			ADK_TARGET_USE_SSP=n \
			ADK_TOOLCHAIN_WITH_LTO=n \
			ADK_TARGET_USE_LTO=n \
			ADK_TOOLCHAIN_WITH_GOLD=n \
			ADK_TARGET_USE_GOLD=n \
			ADK_TARGET_USE_GNU_HASHSTYLE=n \
			ADK_TARGET_USE_PIE=n \
			ADK_TARGET_USE_STATIC_LIBS_ONLY=n \
			ADK_TARGET_USE_LD_RELRO=n \
			ADK_TARGET_USE_LD_BIND_NOW=n \
			ADK_TARGET_USE_LD_GC=n \
			BUSYBOX_IFPLUGD=n \
			BUSYBOX_EXTRA_COMPAT=n \
			BUSYBOX_FEATURE_IFCONFIG_SLIP=n \
			BUSYBOX_BBCONFIG=n \
			BUSYBOX_SELINUX=n \
			BUSYBOX_INSTALL_NO_USR=n \
			BUSYBOX_MODPROBE_SMALL=n \
			BUSYBOX_EJECT=n \
			BUSYBOX_UBIDETACH=n \
			BUSYBOX_UBIATTACH=n \
			BUSYBOX_BUILD_LIBBUSYBOX=n \
			BUSYBOX_FEATURE_2_4_MODULES=n \
			BUSYBOX_LOCALE_SUPPORT=n \
			BUSYBOX_FEATURE_PREFER_APPLETS=n \
			BUSYBOX_FEATURE_SUID=n \
			BUSYBOX_SELINUXENABLED=n \
			BUSYBOX_FEATURE_INSTALLER=n \
			BUSYBOX_PAM=n \
			BUSYBOX_FLASH_LOCK=n \
			BUSYBOX_FLASH_UNLOCK=n \
			BUSYBOX_FLASH_ERASEALL=n \
			BUSYBOX_PIE=n \
			BUSYBOX_TASKSET=n \
			BUSYBOX_DEBUG=n \
			BUSYBOX_DEBUG_SANITIZE=n \
			BUSYBOX_NOMMU=n \
			BUSYBOX_WERROR=n \
			BUSYBOX_STATIC=n \
			BUSYBOX_FEATURE_AIX_LABEL=n \
			BUSYBOX_FEATURE_SUN_LABEL=n \
			BUSYBOX_FEATURE_OSF_LABEL=n \
			BUSYBOX_FEATURE_SGI_LABEL=n \
			BUSYBOX_FEATURE_INETD_RPC=n \
			BUSYBOX_FEATURE_MOUNT_NFS=n \
			BUSYBOX_FEATURE_VI_REGEX_SEARCH=n \
			ADK_LINUX_KERNEL_FB_CON_DECOR=n \
			ADK_LINUX_KERNEL_RT2X00_DEBUG=n \
			ADK_LINUX_KERNEL_ATH5K_DEBUG=n \
			ADK_LINUX_KERNEL_BUG=n \
			ADK_LINUX_KERNEL_DEBUG_WITH_KGDB=n

noconfig_targets:=	menuconfig \
			_config \
			_mconfig \
			distclean \
			defconfig

POSTCONFIG=		-@\
	if [ ! -f .firstrun ]; then \
		$(ADK_TOPDIR)/adk/tools/pkgrebuild;\
		rebuild=0; \
		cleandir=0; \
		if [ "$$(grep ^BUSYBOX .config|md5sum)" != "$$(grep ^BUSYBOX .config.old|md5sum)" ];then \
			touch .rebuild.busybox;\
			rebuild=1;\
		fi; \
		for i in ADK_SIMPLE_NETWORK_CONFIG ADK_RUNTIME_ ADK_TARGET_ROOTFS;do \
			if [ "$$(grep ^$$i .config|md5sum)" != "$$(grep ^$$i .config.old|md5sum)" ];then \
				touch .rebuild.base-files;\
				rebuild=1;\
			fi; \
		done; \
		for i in ADK_TARGET_GPU_MEM ADK_LINUX_KERNEL_SND_BCM2708;do \
			if [ "$$(grep ^$$i .config|md5sum)" != "$$(grep ^$$i .config.old|md5sum)" ];then \
				touch .rebuild.bcm28xx-bootloader;\
				rebuild=1;\
			fi; \
		done; \
		if [ "$$(grep ^ADK_RUNTIME_TIMEZONE .config|md5sum)" != "$$(grep ^ADK_RUNTIME_TIMEZONE .config.old|md5sum)" ];then \
			touch .rebuild.musl .rebuild.uclibc-ng .rebuild.glibc;\
			rebuild=1;\
		fi; \
		if [ "$$(grep ^ADK_RUNTIME_SSH_PUBKEY .config|md5sum)" != "$$(grep ^ADK_RUNTIME_SSH_PUBKEY .config.old|md5sum)" ];then \
			touch .rebuild.dropbear .rebuild.openssh;\
			rebuild=1;\
		fi; \
		if [ "$$(grep ^ADK_TOOLCHAIN_WITH .config|md5sum)" != "$$(grep ^ADK_TOOLCHAIN_WITH .config.old|md5sum)" ];then \
			cleandir=1;\
			rebuild=1;\
		fi; \
		if [ "$$(grep ^ADK_TARGET_KERNEL_VERSION .config|md5sum)" != "$$(grep ^ADK_TARGET_KERNEL_VERSION .config.old|md5sum)" ];then \
			cleandir=1;\
			rebuild=1;\
		fi; \
		if [ "$$(grep ^ADK_RUNTIME_INIT_ .config|md5sum)" != "$$(grep ^ADK_RUNTIME_BASE_ .config.old|md5sum)" ];then \
			cleandir=1;\
			rebuild=1;\
		fi; \
		if [ "$$(grep ^ADK_RUNTIME_BASE_ .config|md5sum)" != "$$(grep ^ADK_RUNTIME_BASE_ .config.old|md5sum)" ];then \
			cleandir=1;\
			rebuild=1;\
		fi; \
		if [ "$$(grep ^ADK_TARGET_USE .config|md5sum)" != "$$(grep ^ADK_TARGET_USE .config.old|md5sum)" ];then \
			cleandir=1;\
			rebuild=1;\
		fi; \
		if [ $$cleandir -eq 1 ];then \
			echo "You should rebuild with 'make cleansystem'";\
		fi; \
		if [ "$$(grep ^ADK_TARGET_KERNEL_USE_DEFCONFIG .config)" ];then \
			if [ "$$(grep ^ADK_TARGET_KERNEL_DEFCONFIG .config|awk -F= '{print $$2}')" == '""' ];then \
			echo "custom Linux defconfig name missing";\
			fi; \
		fi; \
		if [ $$rebuild -eq 1 ];then \
			cp .config .config.old;\
		fi; \
	fi; \
	if [ -f .firstrun ]; then rm .firstrun; fi

# Pull in the user's configuration file
ifeq ($(filter $(noconfig_targets),$(MAKECMDGOALS)),)
-include $(ADK_TOPDIR)/.config
endif

ifeq ($(strip $(ADK_HAVE_DOT_CONFIG)),y)
include $(ADK_TOPDIR)/rules.mk

all: world

${ADK_TOPDIR}/package/Depends.mk: ${ADK_TOPDIR}/.config $(wildcard ${ADK_TOPDIR}/package/*/Makefile) $(ADK_TOPDIR)/adk/tools/depmaker
	@printf " --->  generating dependencies.. "
	$(ADK_TOPDIR)/adk/tools/depmaker > ${ADK_TOPDIR}/package/Depends.mk
	@printf "done\n"

.NOTPARALLEL:
.PHONY: all world clean cleandir cleansystem distclean image_clean

world:
	@mkdir -p $(DL_DIR) $(HOST_BUILD_DIR) $(BUILD_DIR) $(TARGET_DIR) $(FW_DIR) \
		$(STAGING_HOST_DIR) $(TOOLCHAIN_BUILD_DIR) $(STAGING_PKG_DIR)/stamps
ifeq ($(ADK_APPLIANCE_TOOLCHAIN),y)
	$(MAKE) -f mk/build.mk package/hostcompile toolchain/final
else
ifeq ($(ADK_TARGET_OS_BAREMETAL),y)
	$(MAKE) -f mk/build.mk package/hostcompile toolchain/final
endif
ifeq ($(ADK_TARGET_OS_LINUX),y)
	$(MAKE) -f mk/build.mk package/hostcompile toolchain/final target/config-prepare target/compile package_clean package/compile root_clean package/install target/install package_index
endif
endif

package_index:
ifeq ($(ADK_TARGET_PACKAGE_IPKG),y)
	-cd ${PACKAGE_DIR} && \
	    ${BASH} ${ADK_TOPDIR}/scripts/ipkg-make-index.sh . >Packages
endif
ifeq ($(ADK_TARGET_PACKAGE_OPKG),y)
	-cd ${PACKAGE_DIR} && \
	    ${BASH} ${ADK_TOPDIR}/scripts/ipkg-make-index.sh . >Packages
endif

${STAGING_TARGET_DIR} ${STAGING_TARGET_DIR}/etc ${STAGING_HOST_DIR}:
	@mkdir -p ${STAGING_TARGET_DIR}/lib
	@mkdir -p ${STAGING_TARGET_DIR}/bin
	@mkdir -p ${STAGING_TARGET_DIR}/etc
	@mkdir -p ${STAGING_TARGET_DIR}/usr/bin
	@mkdir -p ${STAGING_TARGET_DIR}/usr/include
	@mkdir -p ${STAGING_TARGET_DIR}/usr/lib/pkgconfig
	@mkdir -p ${STAGING_HOST_DIR}/lib
	@mkdir -p ${STAGING_HOST_DIR}/usr/bin
	@mkdir -p ${STAGING_HOST_DIR}/usr/lib
	@mkdir -p ${STAGING_HOST_DIR}/usr/include
	@for i in lib64 lib32 libx32; do \
		cd ${STAGING_TARGET_DIR}; ln -sf lib $$i; \
		cd ${STAGING_TARGET_DIR}/usr; ln -sf lib $$i; \
		cd ${STAGING_HOST_DIR}; ln -sf lib $$i; \
		cd ${STAGING_HOST_DIR}/usr; ln -sf lib $$i; \
	done

${STAGING_TARGET_DIR}/etc/ipkg.conf: ${STAGING_TARGET_DIR}/etc
	echo "dest root /" >${STAGING_TARGET_DIR}/etc/ipkg.conf
	echo "option offline_root ${TARGET_DIR}" >>$(STAGING_TARGET_DIR)/etc/ipkg.conf

package/%: ${STAGING_TARGET_DIR}/etc/ipkg.conf ${ADK_TOPDIR}/package/Depends.mk
	$(MAKE) -C package $(patsubst package/%,%,$@)

target/%:
	$(MAKE) -C target $(patsubst target/%,%,$@)

toolchain/%: ${STAGING_TARGET_DIR}
	$(MAKE) -C toolchain $(patsubst toolchain/%,%,$@)

image:
	$(MAKE) -C target image

targethelp:
	$(MAKE) -C target targethelp 

kernelconfig:
	${KERNEL_MAKE_ENV} ${MAKE} -C "${LINUX_DIR}" \
		ARCH=$(ADK_TARGET_KARCH) \
		${KERNEL_MAKE_OPTS} \
		menuconfig

ifeq ($(ADK_TARGET_LINUX_KERNEL_USE_CUSTOMCONFIG),y)
savekconfig:
	@echo "Saving kernel configuration to $(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH)"
	$(CP) $(LINUX_DIR)/.config $(ADK_TOPDIR)/$(ADK_TARGET_LINUX_KERNEL_CUSTOMCONFIG_PATH)
else
savekconfig:
	@echo "You have to enable ADK_TARGET_LINUX_KERNEL_USE_CUSTOMCONFIG to be able to save the current kernel configuration."
endif


# create a new package from package/.template
newpackage:
	@echo "Creating new package $(PKG)"
	$(CP) $(ADK_TOPDIR)/package/.template$(TYPE) $(ADK_TOPDIR)/package/$(PKG)
	pkg=$$(echo $(PKG)|tr '[:lower:]-' '[:upper:]_'); \
		$(SED) "s#@UPKG@#$$pkg#" $(ADK_TOPDIR)/package/$(PKG)/Makefile
	$(SED) 's#@PKG@#$(PKG)#' $(ADK_TOPDIR)/package/$(PKG)/Makefile
	$(SED) 's#@VER@#$(VER)#' $(ADK_TOPDIR)/package/$(PKG)/Makefile
	@echo "Edit package/$(PKG)/Makefile to complete"

package_clean:
	rm -rf $(PACKAGE_DIR)
	mkdir -p $(PACKAGE_DIR)

root_clean:
	rm -rf $(TARGET_DIR)
	mkdir -p $(TARGET_DIR)
	touch $(TARGET_DIR)/.adk

# Do a per-package clean here, too. This way stale headers and
# libraries from target_*/ get wiped away, which keeps
# future package build's configure scripts from returning false
# dependencies information.

clean:
	@printf " --->  cleaning target build directories and files.. "
	$(MAKE) -C $(CONFIG) clean
	for f in $$(ls ${STAGING_PKG_DIR}/ 2>/dev/null |grep -v [A-Z]|grep -v stamps 2>/dev/null); do  \
		while read file ; do \
			rm ${STAGING_TARGET_DIR}/$$file 2>/dev/null;\
		done < ${STAGING_PKG_DIR}/$$f ; \
		rm ${STAGING_PKG_DIR}/$$f ; \
	done
	rm -rf $(BUILD_DIR) $(FW_DIR) $(TARGET_DIR) \
	    	${ADK_TOPDIR}/package/pkglist.d
	rm -f ${ADK_TOPDIR}/package/Depends.mk
	@printf "done\n"

cleankernel:
	@printf " --->  cleaning kernel build directories.. "
	@rm -rf $(TOOLCHAIN_BUILD_DIR)/w-$(ADK_TARGET_OS)* $(BUILD_DIR)/$(ADK_TARGET_OS)
	@printf "done\n"

cleandir:
	@printf " --->  cleaning all build directories and files.. "
	@$(MAKE) -C $(CONFIG) clean $(MAKE_TRACE) 
	@rm -rf $(BUILD_DIR_PFX) $(FW_DIR_PFX) $(TARGET_DIR_PFX) \
	    ${ADK_TOPDIR}/package/pkglist.d ${ADK_TOPDIR}/package/pkgconfigs.d
	@rm -rf $(TOOLCHAIN_DIR_PFX) $(STAGING_HOST_DIR_PFX)
	@rm -rf $(STAGING_TARGET_DIR_PFX) $(STAGING_PKG_DIR_PFX)
	@rm -f .menu .tmpconfig.h .rebuild* make.log
	@rm -f ${ADK_TOPDIR}/package/Depends.mk ${ADK_TOPDIR}/prereq.mk
	@printf "done\n"

cleansystem:
	@printf " --->  cleaning system build directories and files .. "
	@$(MAKE) -C $(CONFIG) clean $(MAKE_TRACE) 
	@rm -rf $(BUILD_DIR) $(FW_DIR) $(TARGET_DIR) \
	    ${ADK_TOPDIR}/package/pkglist.d ${ADK_TOPDIR}/package/pkgconfigs.d
	@rm -rf $(TOOLCHAIN_DIR) $(STAGING_TARGET_DIR) $(STAGING_PKG_DIR) $(TOOLCHAIN_BUILD_DIR)
	@rm -f .menu .tmpconfig.h .rebuild* ${ADK_TOPDIR}/package/Depends.mk ${ADK_TOPDIR}/prereq.mk
	@printf "done\n"

distclean:
	@printf " --->  cleaning build directories, files and downloads.. "
	@$(MAKE) -C $(CONFIG) clean $(MAKE_TRACE)
	@rm -rf $(TOOLCHAIN_DIR_PFX) $(STAGING_HOST_DIR_PFX)
	@rm -rf $(STAGING_TARGET_DIR_PFX) $(STAGING_PKG_DIR_PFX)
	@rm -rf $(BUILD_DIR_PFX) $(FW_DIR_PFX) $(TARGET_DIR_PFX) $(DL_DIR)
	@rm -rf package/pkglist.d package/pkgconfigs.d
	@rm -f .config* .defconfig .tmpconfig.h all.config prereq.mk make.log
	@rm -f .firstrun .menu package/Depends.mk .ADK_HAVE_DOT_CONFIG .rebuild.*
	@rm -f target/*/Config.in.arch target/*/Config.in.systems target/config/Config.in.tasks
	@rm -f target/config/Config.in.arch.choice target/config/Config.in.arch.default
	@rm -f target/config/Config.in.system.choice target/config/Config.in.system.default
	@rm -f package/Config.in.auto* target/config/Config.in.system
	@rm -f target/config/Config.in.prereq target/config/Config.in.scripts
	@rm -f adk/tools/pkgmaker adk/tools/depmaker adk/tools/pkgrebuild
	@printf "done\n"

else # ! ifeq ($(strip $(ADK_HAVE_DOT_CONFIG)),y)

ifeq ($(filter-out distclean,${MAKECMDGOALS}),)
include ${ADK_TOPDIR}/mk/vars.mk
else
include $(ADK_TOPDIR)/prereq.mk
endif

all: menuconfig
	@echo "Start the build with \"make\" or with \"make v\" to be verbose"

# configuration
# ---------------------------------------------------------------------------

# force entering the subdir, as dependency checking is done there
.PHONY: $(CONFIG)/conf $(CONFIG)/mconf

$(CONFIG)/conf:
	@$(MAKE) -C $(CONFIG) conf

$(CONFIG)/mconf:
	@$(MAKE) -C $(CONFIG)

defconfig: .menu $(CONFIG)/conf
	@if [ -f $(ADK_TOPDIR)/.defconfig ]; then rm $(ADK_TOPDIR)/.defconfig;fi
	@if [ ! -z "$(ADK_NO_CHECKSUM)" ];then \
		echo "ADK_DISABLE_CHECKSUM=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_BASE)" ];then \
		echo "ADK_PACKAGE_ADKTEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_HELLOWORLD=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_TOOLCHAIN)" ];then \
		echo "ADK_PACKAGE_HELLOWORLD=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_LTP)" ];then \
		echo "ADK_PACKAGE_ADKTEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_FILE=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_LTP=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_MKSH)" ];then \
		echo "ADK_PACKAGE_ADKTEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_PERL=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_MKSH_TEST=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_UCLIBC_NG_TEST)" ];then \
		echo "ADK_PACKAGE_ADKTEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_UCLIBC_NG_TEST=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_LIBC_TEST)" ];then \
		echo "ADK_PACKAGE_ADKTEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_LIBC_TEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_MAKE=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_UCLIBC_NG_NATIVE)" ];then \
		echo "ADK_PACKAGE_ADKTEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_GCC=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_BINUTILS=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_MAKE=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_UCLIBC_NG_DEV=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_MUSL_NATIVE)" ];then \
		echo "ADK_PACKAGE_ADKTEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_GCC=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_BINUTILS=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_MAKE=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_MUSL_DEV=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TEST_GLIBC_NATIVE)" ];then \
		echo "ADK_PACKAGE_ADKTEST=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_GCC=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_BINUTILS=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_MAKE=y" >> $(ADK_TOPDIR)/.defconfig; \
		echo "ADK_PACKAGE_GLIBC_DEV=y" >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_APPLIANCE)" ];then \
		grep "^config" target/config/Config.in.tasks \
			|grep -i "_$(ADK_APPLIANCE)$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			 >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_OS)" ];then \
		grep "^config" target/config/Config.in.os \
			|grep -i "_$(ADK_TARGET_OS)$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			 >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_ARCH)" ];then \
		grep "^config" target/config/Config.in.arch.choice \
			|grep -i "$(ADK_TARGET_OS)_ARCH_$(ADK_TARGET_ARCH)$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			 >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_FS)" ];then \
		grep "^config" target/config/Config.in.rootfs \
			|grep -i "$(ADK_TARGET_FS)" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_ABI)" ];then \
		grep "^config" target/config/Config.in.abi \
			|grep -i "$(ADK_TARGET_ABI)$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_FLOAT)" ];then \
		grep "^config" target/config/Config.in.float \
			|grep -i "$(ADK_TARGET_FLOAT)_" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_BINFMT)" ];then \
		grep "^config" target/config/Config.in.binfmt \
			|grep -i "$(ADK_TARGET_BINFMT)$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_INSTRUCTION_SET)" ];then \
		grep "^config" target/config/Config.in.instructions \
			|grep -i "$(ADK_TARGET_INSTRUCTION_SET)$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_ENDIAN)" ];then \
		grep "^config" target/config/Config.in.endian \
			|grep -i "$(ADK_TARGET_ENDIAN)" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_MMU)" ];then \
		printf "# ADK_TARGET_WITH_MMU is not set\n" \
			>> $(ADK_TOPDIR)/.defconfig; \
		printf "BUSYBOX_NOMMU=y\n" \
                        >> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_THREADS)" ];then \
		if [ "$(ADK_TARGET_THREADS)" = "nptl" ];then \
			printf "ADK_TARGET_WITH_NPTL=y\n" >> $(ADK_TOPDIR)/.defconfig; \
		fi; \
		if [ "$(ADK_TARGET_THREADS)" = "lt" ];then \
			printf "ADK_TARGET_WITH_LT=y\n" >> $(ADK_TOPDIR)/.defconfig; \
		fi; \
		if [ "$(ADK_TARGET_THREADS)" = "none" ];then \
			printf "ADK_TARGET_WITHOUT_THREADS=y\n" >> $(ADK_TOPDIR)/.defconfig; \
		fi; \
	fi
	@if [ ! -z "$(ADK_TARGET_LIBC)" ];then \
		libc=$$(echo "$(ADK_TARGET_LIBC)"|sed -e "s/-/_/"); \
		grep "^config" target/config/Config.in.libc \
			|grep -i "$$libc$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_CPU)" ];then \
		cpu=$$(echo "$(ADK_TARGET_CPU)" |sed -e "s/-/_/g"); \
		grep -h "^config" target/config/Config.in.cpu \
			|grep -i "$$cpu$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_SYSTEM)" ];then \
		system=$$(echo "$(ADK_TARGET_SYSTEM)" |sed -e "s/-/_/g"); \
		grep -h "^config" target/*/Config.in.systems \
			|grep -i "$$system$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_KERNEL_VERSION)" ];then \
		kernelversion=$$(echo "$(ADK_TARGET_KERNEL_VERSION)"|sed -e "s/\./_/g"); \
		grep "^config" target/config/Config.in.kernelversion \
			|grep -i "$$kernelversion$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/.defconfig; \
	fi
	@if [ ! -z "$(ADK_TARGET_LIBC_VERSION)" ];then \
		libcversion=$$(echo "$(ADK_TARGET_LIBC_VERSION)"|sed -e "s/\./_/g"); \
		if [ "$$libcversion" = "git" ];then \
			if [ "$(ADK_TARGET_LIBC)" = "glibc" ];then \
				echo "ADK_TARGET_LIB_GLIBC_GIT=y" >> $(ADK_TOPDIR)/.defconfig; \
			fi; \
			if [ "$(ADK_TARGET_LIBC)" = "uclibc-ng" ];then \
				echo "ADK_TARGET_LIB_UCLIBC_NG_GIT=y" >> $(ADK_TOPDIR)/.defconfig; \
			fi; \
			if [ "$(ADK_TARGET_LIBC)" = "musl" ];then \
				echo "ADK_TARGET_LIB_MUSL_GIT=y" >> $(ADK_TOPDIR)/.defconfig; \
			fi; \
		else \
			grep "^config" target/config/Config.in.libc \
				|grep -i "$$libcversion$$" \
				|sed -e "s#^config \(.*\)#\1=y#" \
				>> $(ADK_TOPDIR)/.defconfig; \
		fi; \
	fi
	@if [ ! -z "$(ADK_TOOLCHAIN_BINUTILS_VERSION)" ];then \
		binutilsversion=$$(echo "$(ADK_TOOLCHAIN_BINUTILS_VERSION)"|sed -e "s/\./_/g"); \
		if [ "$$binutilsversion" = "git" ];then \
			echo "ADK_TOOLCHAIN_BINUTILS_GIT=y" >> $(ADK_TOPDIR)/.defconfig; \
		else \
			grep "^config" target/config/Config.in.binutils \
				|grep -i "$$binutilsversion$$" \
				|sed -e "s#^config \(.*\)#\1=y#" \
				>> $(ADK_TOPDIR)/.defconfig; \
		fi; \
	fi
	@if [ ! -z "$(ADK_TOOLCHAIN_GCC_VERSION)" ];then \
		echo "ADK_BUILD_COMPILER_GCC=y" >> $(ADK_TOPDIR)/.defconfig; \
		gccversion=$$(echo "$(ADK_TOOLCHAIN_GCC_VERSION)"|sed -e "s/\./_/g"); \
		if [ "$$gccversion" = "git" ];then \
			echo "ADK_TOOLCHAIN_GCC_GIT=y" >> $(ADK_TOPDIR)/.defconfig; \
		else \
			grep "^config" target/config/Config.in.compiler \
				|grep -i "$$gccversion$$" \
				|sed -e "s#^config \(.*\)#\1=y#" \
				>> $(ADK_TOPDIR)/.defconfig; \
		fi; \
	fi
	@if [ ! -z "$(ADK_TOOLCHAIN_GDB_VERSION)" ];then \
		gdbversion=$$(echo "$(ADK_TOOLCHAIN_GDB_VERSION)"|sed -e "s/\./_/g"); \
		if [ "$$gdbversion" = "git" ];then \
			echo "ADK_TOOLCHAIN_GDB_GIT=y" >> $(ADK_TOPDIR)/.defconfig; \
		else \
			grep "^config" target/config/Config.in.gdb \
				|grep -i "$$gdbversion$$" \
				|sed -e "s#^config \(.*\)#\1=y#" \
				>> $(ADK_TOPDIR)/.defconfig; \
		fi; \
	fi
	@if [ ! -z "$(ADK_APPLIANCE)" ];then \
		$(CONFIG)/conf --defconfig=.defconfig $(CONFIG_CONFIG_IN); \
	fi

allconfig:
	@if [ ! -z "$(ADK_APPLIANCE)" ];then \
		grep "^config" target/config/Config.in.tasks \
			|grep -i "_$(ADK_APPLIANCE)"\$$ \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/all.config; \
	fi
	@if [ ! -z "$(ADK_TARGET_OS)" ];then \
		grep "^config" target/config/Config.in.os \
			|grep -i "_$(ADK_TARGET_OS)$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			 >> $(ADK_TOPDIR)/all.config; \
	fi
	@if [ ! -z "$(ADK_TARGET_ARCH)" ];then \
		grep "^config" target/config/Config.in.arch.choice \
			|grep -i "$(ADK_TARGET_OS)_ARCH_$(ADK_TARGET_ARCH)$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			 >> $(ADK_TOPDIR)/all.config; \
	fi
	@for symbol in ${DEFCONFIG}; do \
		echo $$symbol >> $(ADK_TOPDIR)/all.config; \
	done
	@if [ ! -z "$(ADK_TARGET_FS)" ];then \
		grep "^config" target/config/Config.in.rootfs \
			|grep -i "$(ADK_TARGET_FS)" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/all.config; \
	fi
	@if [ ! -z "$(ADK_TARGET_LIBC)" ];then \
		grep "^config" target/config/Config.in.libc \
			|grep -i "$(ADK_TARGET_LIBC)" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/all.config; \
	fi
	@if [ ! -z "$(ADK_TARGET_SYSTEM)" ];then \
		system=$$(echo "$(ADK_TARGET_SYSTEM)" |sed -e "s/-/_/g"); \
		grep -h "^config" target/*/Config.in.systems \
			|grep -i "$$system$$" \
			|sed -e "s#^config \(.*\)#\1=y#" \
			>> $(ADK_TOPDIR)/all.config; \
	fi

menuconfig: $(CONFIG)/mconf defconfig .menu
	@if [ ! -f .config ];then \
		$(CONFIG)/conf --olddefconfig $(CONFIG_CONFIG_IN); \
	fi
	@$(CONFIG)/mconf $(CONFIG_CONFIG_IN)
	${POSTCONFIG}

_config: $(CONFIG)/conf allconfig .menu
	-@touch .config
	@$(CONFIG)/conf ${W} $(CONFIG_CONFIG_IN)
	${POSTCONFIG}

distclean cleandir:
	@printf " --->  cleaning build directories, files and downloads.. "
	@$(MAKE) -C $(CONFIG) clean
	@rm -rf $(BUILD_DIR_PFX) $(FW_DIR_PFX) $(TARGET_DIR_PFX) $(DL_DIR)
	@rm -rf $(TOOLCHAIN_DIR_PFX) $(STAGING_TARGET_DIR_PFX)
	@rm -rf $(STAGING_HOST_DIR_PFX) $(STAGING_TARGET_DIR_PFX) $(STAGING_PKG_DIR_PFX)
	@rm -rf package/pkglist.d package/pkgconfigs.d
	@rm -f .config* .defconfig .tmpconfig.h all.config make.log
	@rm -f .menu .rebuild.* package/Depends.mk .ADK_HAVE_DOT_CONFIG prereq.mk
	@rm -f target/*/Config.in.arch target/*/Config.in.systems
	@rm -f target/config/Config.in.arch.choice target/config/Config.in.arch.default
	@rm -f target/config/Config.in.system.choice target/config/Config.in.system.default
	@rm -f package/Config.in.auto* target/config/Config.in.system target/config/Config.in.tasks
	@rm -f target/config/Config.in.prereq target/config/Config.in.scripts
	@rm -f adk/tools/pkgmaker adk/tools/depmaker adk/tools/pkgrebuild
	@printf "done\n"

endif # ! ifeq ($(strip $(ADK_HAVE_DOT_CONFIG)),y)

$(ADK_TOPDIR)/adk/tools/pkgmaker: $(ADK_TOPDIR)/adk/tools/pkgmaker.c $(ADK_TOPDIR)/adk/tools/sortfile.c $(ADK_TOPDIR)/adk/tools/strmap.c
	@$(HOST_CC) $(HOST_CFLAGS) -o $@ adk/tools/pkgmaker.c adk/tools/sortfile.c adk/tools/strmap.c

$(ADK_TOPDIR)/adk/tools/pkgrebuild: $(ADK_TOPDIR)/adk/tools/pkgrebuild.c $(ADK_TOPDIR)/adk/tools/strmap.c
	@$(HOST_CC) $(HOST_CFLAGS) -o $@ adk/tools/pkgrebuild.c adk/tools/strmap.c

$(ADK_TOPDIR)/adk/tools/depmaker: $(ADK_TOPDIR)/adk/tools/depmaker.c
	@$(HOST_CC) $(HOST_CFLAGS) -o $@ $(ADK_TOPDIR)/adk/tools/depmaker.c

menu .menu: $(wildcard package/*/Makefile) $(wildcard target/*/systems) $(wildcard target/*/systems/*) $(ADK_TOPDIR)/adk/tools/pkgmaker $(ADK_TOPDIR)/adk/tools/pkgrebuild $(wildcard tasks/*)
	@printf " --->  generating menu structure.. "
	@$(SHELL) $(ADK_TOPDIR)/scripts/create-menu
	@$(ADK_TOPDIR)/adk/tools/pkgmaker
	@:>.menu
	@printf "done\n"

dep: $(ADK_TOPDIR)/adk/tools/depmaker
	@printf " --->  generating dependencies.. "
	@$(ADK_TOPDIR)/adk/tools/depmaker > ${ADK_TOPDIR}/package/Depends.mk
	@printf "done\n"

.PHONY: menu dep

include $(ADK_TOPDIR)/toolchain/gcc/Makefile.inc

check-dejagnu:
	@-rm adk/tests/adk.exp adk/tests/master.exp >/dev/null 2>&1
	@sed -e "s#@ADK_TARGET_IP@#$(ADK_TARGET_IP)#" \
		-e "s#@ADK_TARGET_PORT@#$(ADK_TARGET_PORT)#" \
		adk/tests/adk.exp.in > adk/tests/adk.exp
	@sed -e "s#@ADK_TOPDIR@#$(ADK_TOPDIR)#" adk/tests/master.exp.in > \
		adk/tests/master.exp

check-gcc: check-dejagnu
	env DEJAGNU=$(ADK_TOPDIR)/adk/tests/master.exp \
	$(MAKE) -C $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/$(PKG_NAME)-$(PKG_VERSION)-final/gcc -k check-c

check-g++: check-dejagnu
	env DEJAGNU=$(ADK_TOPDIR)/adk/tests/master.exp \
	$(MAKE) -C $(TOOLCHAIN_BUILD_DIR)/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)/$(PKG_NAME)-$(PKG_VERSION)-final/gcc -k check-c++

check: check-gcc check-g++

info:
	@printf -- "---OPENADK-INFO---\n"
	@printf "ADK_TOPDIR=$(ADK_TOPDIR)\n"
	@printf "TARGET_COMPILER_PREFIX=${TARGET_COMPILER_PREFIX}\n"
	@printf "TOOLCHAIN_DIR=$(TOOLCHAIN_DIR)\n"
	@printf "TARGET_PATH=$(TARGET_PATH)\n"
	@printf "LINUX_DIR=$(LINUX_DIR)\n"
	@printf "TARGET_DIR=$(TARGET_DIR)\n"
	@printf -- "---OPENADK-INFO---\n"

