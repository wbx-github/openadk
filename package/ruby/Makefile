# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ruby
PKG_VERSION:=		3.1.2
PKG_RELEASE:=		1
PKG_HASH:=		ca10d017f8a1b6d247556622c841fc56b90c03b1803f87198da1e4fd3ec3bf2a
PKG_DESCR:=		scripting language
PKG_SECTION:=		dev/lang
PKG_DEPENDS:=		libressl zlib
PKG_BUILDDEP:=		ruby-host libressl zlib
HOST_BUILDDEP:=		libressl-host
PKG_NEEDS:=		threads
PKG_URL:=		http://www.ruby-lang.org/
PKG_SITES:=		http://ftp.ruby-lang.org/pub/ruby/3.1/

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,RUBY,ruby,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,RUBY,ruby,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

# uClibc setpgrp does not take arguments
CONFIGURE_ENV+=         ac_cv_func_setpgrp_void=yes \
			stack_protector=no \
			rb_cv_binary_elf=yes
CONFIGURE_ARGS+=	--disable-install-doc \
			--with-out-ext=fiddle \
			--with-baseruby=${STAGING_HOST_DIR}/usr/bin/ruby

MAKE_FILE:=		GNUmakefile
XAKE_FLAGS+=		optflags='' debugflags='' dldflags="$(TARGET_LDFLAGS)" 
ALL_TARGET:=		main
INSTALL_TARGET:=	install-nodoc

HOST_CONFIGURE_ARGS+=	--disable-install-doc \
			--disable-shared \
			--with-out-ext=curses,readline,openssl \
			--disable-rubygems
HOST_ALL_TARGET:=	main
HOST_INSTALL_TARGET:=	install-nodoc
HOST_XAKE_FLAGS:=	DESTDIR=""

ruby-install:
	${INSTALL_DIR} ${IDIR_RUBY}/usr/lib/ruby
	${INSTALL_DIR} ${IDIR_RUBY}/usr/bin
	${CP} ${WRKINST}/usr/lib/libruby.so* ${IDIR_RUBY}/usr/lib
	${CP} ${WRKINST}/usr/lib/ruby/* ${IDIR_RUBY}/usr/lib/ruby
	${INSTALL_BIN} ${WRKINST}/usr/bin/* ${IDIR_RUBY}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
