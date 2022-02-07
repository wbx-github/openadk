# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include $(ADK_TOPDIR)/mk/rootfs.mk

PKG_NAME:=		base-files
PKG_VERSION:=		1.1
PKG_RELEASE:=		27
PKG_SECTION:=		base/apps
PKG_DESCR:=		basic files and scripts

WRKDIST=		${WRKDIR}/base-files
NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BASE_FILES,${PKG_NAME},${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},force_etc))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

ifeq ($(ADK_RUNTIME_DEV_MDEV_LOGGING),y)
ADK_RUNTIME_DEV_MDEV_LOGGING_LINE:='echo >/dev/mdev.log'
else
ADK_RUNTIME_DEV_MDEV_LOGGING_LINE:=''
endif

ifeq ($(ADK_RUNTIME_GETTY_SERIAL_AUTOLOGIN),y)
ADK_RUNTIME_GETTY_SERIAL_AUTOLOGIN_STANZA:= -n -l autologin
else
ADK_RUNTIME_GETTY_SERIAL_AUTOLOGIN_STANZA:=
endif

do-install:
	$(CP) ./src/* $(IDIR_BASE_FILES)
	mkdir -p $(IDIR_BASE_FILES)/{etc,dev,boot,root,sys,proc,tmp,run,var,mnt,media}
	mkdir -p $(IDIR_BASE_FILES)/usr/{lib,bin,sbin}
	ln -sf ../run $(IDIR_BASE_FILES)/var/run
	chmod 600 $(IDIR_BASE_FILES)/etc/shadow
	chmod 1777 ${IDIR_BASE_FILES}/tmp
	echo $(ADK_RUNTIME_TMPFS_SIZE) > $(IDIR_BASE_FILES)/etc/tmpfs
	mkdir -p $(IDIR_BASE_FILES)/etc/init.d
	cp ./files/init.d/* $(IDIR_BASE_FILES)/etc/init.d
	mkdir -p $(IDIR_BASE_FILES)/etc/network/{if-pre-up.d,if-up.d,if-down.d,if-post-down.d}
	cp ./files/fstab $(IDIR_BASE_FILES)/etc
	cp ./files/modules $(IDIR_BASE_FILES)/etc
	ln -sf ../proc/mounts $(IDIR_BASE_FILES)/etc/mtab
ifeq ($(ADK_RUNTIME_LOAD_KERNEL_MODULES),)
	-rm $(IDIR_BASE_FILES)/etc/init.d/kmod
endif
ifeq ($(ADK_TARGET_WITH_NETDEVICE),y)
	cp ./files/interfaces-dhcp $(IDIR_BASE_FILES)/etc/network/interfaces
	cp ./files/rc.netinfo $(IDIR_BASE_FILES)/etc/
else
	cp ./files/interfaces-lo $(IDIR_BASE_FILES)/etc/network/interfaces
endif
	chmod 600 $(IDIR_BASE_FILES)/etc/network/interfaces
ifeq (${ADK_TARGET_ROOTFS_NFSROOT},y)
	echo '#' > $(IDIR_BASE_FILES)/etc/network/interfaces
	(cd $(IDIR_BASE_FILES)/etc; ln -sf ../proc/net/pnp resolv.conf)
else
	(cd $(IDIR_BASE_FILES)/etc; ln -sf ../tmp/resolv.conf .)
endif
ifeq ($(ADK_RUNTIME_DEV_MDEV),y)
	$(CP) ./files/rcdev.mdev $(IDIR_BASE_FILES)/etc/init.d/rcdev
	$(SED) "s#@ADK_RUNTIME_DEV_MDEV_LOGGING@#"$(ADK_RUNTIME_DEV_MDEV_LOGGING_LINE)"#g" $(IDIR_BASE_FILES)/etc/init.d/rcdev
	$(CP) ./files/mdev.conf $(IDIR_BASE_FILES)/etc
	$(CP) ./files/mdev $(IDIR_BASE_FILES)/etc
endif

ifeq ($(ADK_RUNTIME_DEV_UDEV),y)
	$(CP) ./files/rcdev.udev $(IDIR_BASE_FILES)/etc/init.d/rcdev
endif
ifeq ($(ADK_RUNTIME_INIT_SYSV),y)
	cp ./files/inittab.sysv $(IDIR_BASE_FILES)/etc/inittab
	test -z $(ADK_RUNTIME_SHELL) || \
	    cat ./files/inittab.shell >> $(IDIR_BASE_FILES)/etc/inittab
ifeq ($(ADK_TARGET_WITH_VGA)$(ADK_TARGET_GENERIC),y)
	test -z $(ADK_RUNTIME_SHELL) || \
		cat ./files/inittab.shellvga >> $(IDIR_BASE_FILES)/etc/inittab
endif
	test -z $(ADK_RUNTIME_GETTY_VGA) || \
	    cat ./files/inittab.vga >> $(IDIR_BASE_FILES)/etc/inittab
	test -z $(ADK_RUNTIME_GETTY_SERIAL) || \
	    cat ./files/inittab.serial >> $(IDIR_BASE_FILES)/etc/inittab
	$(SED) 's#@DEVICE@#$(ADK_RUNTIME_CONSOLE_SERIAL_DEVICE)#g' $(IDIR_BASE_FILES)/etc/inittab
	$(SED) 's#@SPEED@#$(ADK_RUNTIME_CONSOLE_SERIAL_SPEED)#' $(IDIR_BASE_FILES)/etc/inittab
	$(SED) 's#@AUTOLOGIN@#$(ADK_RUNTIME_GETTY_SERIAL_AUTOLOGIN_STANZA)#' $(IDIR_BASE_FILES)/etc/inittab
endif
ifeq ($(ADK_RUNTIME_MOUNT_DEBUGFS),y)
	echo debugfs    /sys/kernel/debug      debugfs  defaults  0 0 >> $(IDIR_BASE_FILES)/etc/fstab
	echo null::sysinit:/bin/mount -a -t debugfs >> $(IDIR_BASE_FILES)/etc/inittab
endif
	test -z $(ADK_RUNTIME_HOSTNAME) || \
	    echo $(ADK_RUNTIME_HOSTNAME) > $(IDIR_BASE_FILES)/etc/hostname; \
	    echo "127.0.0.1	localhost" > $(IDIR_BASE_FILES)/etc/hosts
	    echo "127.0.1.1	$(ADK_RUNTIME_HOSTNAME)" >> $(IDIR_BASE_FILES)/etc/hosts
	    echo "::1     ip6-localhost ip6-loopback" >> $(IDIR_BASE_FILES)/etc/hosts
	    echo "fe00::0 ip6-localnet" >> $(IDIR_BASE_FILES)/etc/hosts
	    echo "ff00::0 ip6-mcastprefix" >> $(IDIR_BASE_FILES)/etc/hosts
	    echo "ff02::1 ip6-allnodes" >> $(IDIR_BASE_FILES)/etc/hosts
	    echo "ff02::2 ip6-allrouters" >> $(IDIR_BASE_FILES)/etc/hosts
	    echo "ff02::3 ip6-allhosts" >> $(IDIR_BASE_FILES)/etc/hosts
	test -z '$(ADK_RUNTIME_PASSWORD)' || \
	    $(SED) 's,\*NP\*,'"$$(awk -F\= '/^ADK_RUNTIME_PASSWORD/ { print $$2 }' $(ADK_TOPDIR)/.config|sed -e 's^\"^^g'),g" \
		 $(IDIR_BASE_FILES)/etc/shadow
	echo /bin/sh >${IDIR_BASE_FILES}/etc/shells
	echo /bin/mksh >>${IDIR_BASE_FILES}/etc/shells
ifneq (${ADK_PACKAGE_ASH},)
	echo /bin/ash >>${IDIR_BASE_FILES}/etc/shells
endif
ifneq (${ADK_PACKAGE_HUSH},)
	echo /bin/hush >>${IDIR_BASE_FILES}/etc/shells
endif
ifneq (${ADK_PACKAGE_BASH},)
	echo /bin/bash >>${IDIR_BASE_FILES}/etc/shells
endif
ifneq (${ADK_PACKAGE_ZSH},)
	echo /bin/zsh >>${IDIR_BASE_FILES}/etc/shells
endif
ifeq ($(ADK_PACKAGE_MKSH),y)
	$(CP) ./files/profile $(IDIR_BASE_FILES)/etc/profile
ifeq ($(ADK_TARGET_WITH_ROOT_RW),y)
	echo 'export IPKGTMPDIR=/root/.ipkg' >> $(IDIR_BASE_FILES)/etc/profile
else
	echo 'export IPKGTMPDIR=/tmp' >> $(IDIR_BASE_FILES)/etc/profile
endif
ifeq ($(ADK_TARGET_BOARD_BCM28XX),y)
	echo 'export LD_LIBRARY_PATH=/opt/vc/lib' >> $(IDIR_BASE_FILES)/etc/profile
endif
endif
ifeq (${ADK_TARGET_PACKAGE_IPKG},y)
	$(CP) ./files/ipkg.conf $(IDIR_BASE_FILES)/etc/
	$(SED) 's,@ARCH@,$(ADK_TARGET_CPU_ARCH),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	$(SED) 's,@SYSTEM@,$(ADK_TARGET_SYSTEM),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	$(SED) 's,@LIBC@,$(ADK_TARGET_LIBC),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	$(SED) 's,@HOST@,$(ADK_HOST),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	$(SED) 's,@VENDOR@,$(ADK_VENDOR),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	mkdir -p $(IDIR_BASE_FILES)/usr/lib/ipkg/lists
endif
ifeq (${ADK_TARGET_PACKAGE_OPKG},y)
	$(CP) ./files/ipkg.conf $(IDIR_BASE_FILES)/etc/
	$(SED) 's,@ARCH@,$(ADK_TARGET_CPU_ARCH),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	$(SED) 's,@SYSTEM@,$(ADK_TARGET_SYSTEM),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	$(SED) 's,@LIBC@,$(ADK_TARGET_LIBC),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	$(SED) 's,@HOST@,$(ADK_HOST),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	$(SED) 's,@VENDOR@,$(ADK_VENDOR),g' $(IDIR_BASE_FILES)/etc/ipkg.conf
	mkdir -p $(IDIR_BASE_FILES)/usr/lib/opkg/lists
endif

# simple network configuration
ifneq (${ADK_SIMPLE_NETWORK_CONFIG},)
	${INSTALL_DIR} ${IDIR_BASE_FILES}/etc/network
	printf "auto lo\niface lo inet loopback\n" > ${IDIR_BASE_FILES}/etc/network/interfaces

ifeq (${ADK_SIMPLE_NETWORK_CONFIG_ETH0_DHCP},y)
	printf "\nauto eth0\niface eth0 inet dhcp\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
endif
ifeq (${ADK_SIMPLE_NETWORK_CONFIG_ETH0_STATIC},y)
	printf "\nauto eth0\niface eth0 inet static\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  address ${ADK_SIMPLE_NETWORK_CONFIG_ETH0_IP}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  netmask ${ADK_SIMPLE_NETWORK_CONFIG_ETH0_NM}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  broadcast +\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
ifneq (${ADK_SIMPLE_NETWORK_CONFIG_ETH0_GW},)
	printf "  gateway ${ADK_SIMPLE_NETWORK_CONFIG_ETH0_GW}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
endif
endif

ifeq (${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_DHCP},y)
	printf "\nauto wlan0\niface wlan0 inet dhcp\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
ifeq (${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_WPA2},y)
	printf "  wireless-mode sta\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  wireless-ssid ${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_WPA2_SSID}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  wireless-security wpa2\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  wireless-passphrase ${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_WPA2_PW}\n\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
endif
endif
ifeq (${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_STATIC},y)
	printf "\nauto wlan0\niface wlan0 inet static\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
ifeq (${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_WPA2},y)
	printf "  wireless-mode sta\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  wireless-ssid ${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_WPA2_SSID}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  wireless-security wpa2\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  wireless-passphrase ${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_WPA2_PW}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
endif
	printf "  address ${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_IP}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  netmask ${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_NM}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  broadcast +\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
ifneq (${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_GW},)
	printf "  gateway ${ADK_SIMPLE_NETWORK_CONFIG_WLAN0_GW}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
endif
endif

ifeq (${ADK_SIMPLE_NETWORK_CONFIG_ETH1_DHCP},y)
	printf "\nauto eth1\niface eth1 inet dhcp\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
endif
ifeq (${ADK_SIMPLE_NETWORK_CONFIG_ETH1_STATIC},y)
	printf "\nauto eth1\niface eth1 inet static\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  address ${ADK_SIMPLE_NETWORK_CONFIG_ETH1_IP}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  netmask ${ADK_SIMPLE_NETWORK_CONFIG_ETH1_NM}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
	printf "  broadcast +\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
ifneq (${ADK_SIMPLE_NETWORK_CONFIG_ETH1_GW},)
	printf "  gateway ${ADK_SIMPLE_NETWORK_CONFIG_ETH1_GW}\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces
endif
endif
	printf "\n" >> ${IDIR_BASE_FILES}/etc/network/interfaces

ifneq (${ADK_SIMPLE_NETWORK_CONFIG_NS},)
	rm ${IDIR_BASE_FILES}/etc/resolv.conf
	printf "nameserver ${ADK_SIMPLE_NETWORK_CONFIG_NS}\n" > ${IDIR_BASE_FILES}/etc/resolv.conf
endif
ifneq (${ADK_SIMPLE_NETWORK_CONFIG_PROXY},)
	printf "http_proxy=${ADK_SIMPLE_NETWORK_CONFIG_PROXY}\n" >> ${IDIR_BASE_FILES}/etc/profile
	printf "https_proxy=${ADK_SIMPLE_NETWORK_CONFIG_PROXY}\n" >> ${IDIR_BASE_FILES}/etc/profile
	printf "ftp_proxy=${ADK_SIMPLE_NETWORK_CONFIG_PROXY}\n" >> ${IDIR_BASE_FILES}/etc/profile
endif
endif

ifeq ($(ADK_RUNTIME_ADDUSER),y)
	mkdir -p ${IDIR_BASE_FILES}/$(ADK_RUNTIME_USER_HOME)
	printf "$(ADK_RUNTIME_USER_NAME):x:100:100:$(ADK_RUNTIME_USER_NAME):$(ADK_RUNTIME_USER_HOME):$(ADK_RUNTIME_USER_SHELL)" >> ${IDIR_BASE_FILES}/etc/passwd
	printf "$(ADK_RUNTIME_USER_NAME):$(ADK_RUNTIME_USER_PASSWORD):16514:0:::::" >> ${IDIR_BASE_FILES}/etc/shadow
	printf "$(ADK_RUNTIME_USER_NAME):x:100:" >> ${IDIR_BASE_FILES}/etc/group
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
