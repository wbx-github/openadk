# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

MASTER_SITE_BACKUP?=	http://distfiles.${ADK_HOST}/

MASTER_SITE_OPENADK?=	\
	http://distfiles.openadk.org/ \

MASTER_SITE_MIRBSD?=	\
	http://www.mirbsd.org/MirOS/distfiles/ \
	http://pub.allbsd.org/MirOS/distfiles/ \

ifeq ($(ADK_TARGET_KERNEL_NO_MIRROR),)
MASTER_SITE_KERNEL?=	\
	http://www.kernel.org/pub/linux/ \
	ftp://www.kernel.org/pub/linux/ \

else
MASTER_SITE_KERNEL?=	\
	http://distfiles.openadk.org/ \

endif

MASTER_SITE_GNU?=	\
	http://ftp.gnu.org/gnu/ \
	ftp://ftp.gnu.org/gnu/ \
	ftp://ftp.funet.fi/pub/gnu/prep/ \
	ftp://mirrors.usc.edu/pub/gnu/ \
	ftp://ftp.cs.tu-berlin.de/pub/gnu/ \
	ftp://aeneas.mit.edu/pub/gnu/ \
	ftp://mirrors.dotsrc.org/gnu/ \
	ftp://ftp.wustl.edu/pub/gnu/ \
	ftp://ftp.kddilabs.jp/GNU/ \
	ftp://ftp.mirror.ac.uk/sites/ftp.gnu.org/gnu/ \
	ftp://sunsite.org.uk/package/gnu/ \
	ftp://ftp.informatik.hu-berlin.de/pub/gnu/ \
	ftp://ftp.rediris.es/mirror/gnu/gnu/ \
	ftp://ftp.cs.univ-paris8.fr/mirrors/ftp.gnu.org/ \
	ftp://ftp.chg.ru/pub/gnu/ \
	ftp://ftp.uvsq.fr/pub/gnu/ \
  	ftp://ftp.sunet.se/pub/gnu/ \

MASTER_SITE_SOURCEFORGE?=	\
	http://jaist.dl.sourceforge.net/sourceforge/ \
	http://heanet.dl.sourceforge.net/sourceforge/ \
	http://netcologne.dl.sourceforge.net/sourceforge/ \
	http://nchc.dl.sourceforge.net/sourceforge/ \
	http://kent.dl.sourceforge.net/sourceforge/ \
	http://ufpr.dl.sourceforge.net/sourceforge/ \
	http://easynews.dl.sourceforge.net/sourceforge/ \

MASTER_SITE_MYSQL?=		\
	ftp://ftp.fu-berlin.de/unix/databases/mysql/ \
	http://sunsite.informatik.rwth-aachen.de/mysql/ \
	http://mysql.easynet.be/ \

MASTER_SITE_GNOME?=	\
	https://download.gnome.org/sources/ \
	ftp://ftp.gnome.org/pub/GNOME/sources/ \
	ftp://ftp.linux.org.uk/mirrors/ftp.gnome.org/sources/ \
	ftp://ftp.acc.umu.se/pub/GNOME/sources/	\
	ftp://ftp.rpmfind.net/linux/gnome.org/sources/ \
	ftp://ftp.unina.it/pub/linux/GNOME/sources/ \
	ftp://ftp.belnet.be/mirror/ftp.gnome.org/sources/ \
	ftp://ftp.dit.upm.es/linux/gnome/sources/ \
	ftp://ftp.dataplus.se/pub/linux/gnome/sources/ \
	ftp://ftp.cse.buffalo.edu/pub/Gnome/sources/ \

