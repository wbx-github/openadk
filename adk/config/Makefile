# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/prereq.mk

ifneq ($(filter-out clean,${MAKECMDGOALS}),)
include ${ADK_TOPDIR}/rules.mk
endif

CP=cp -fpR
HOST_CFLAGS+=	-DKBUILD_NO_NLS -w ${CURSES_CFLAGS}
LIBS=		${CURSES_LIBS}

all: ncurses conf mconf

CONF_SRC  =conf.c
MCONF_SRC =mconf.c $(wildcard lxdialog/*.c)
SHARED_SRC=zconf.tab.c
SHARED_DEPS:=lkc.h lkc_proto.h lkc_defs.h expr.h zconf.tab.h
CONF_OBJS =$(patsubst %.c,%.o, $(CONF_SRC))
MCONF_OBJS=$(patsubst %.c,%.o, $(MCONF_SRC))
SHARED_OBJS=$(patsubst %.c,%.o, $(SHARED_SRC))

conf: $(CONF_OBJS) $(SHARED_OBJS)
	@$(HOST_CC) $(HOST_CFLAGS) $^ -o $@ 2>/dev/null

mconf: $(MCONF_OBJS) $(SHARED_OBJS)
	@$(HOST_CC) $(HOST_CFLAGS) $^ -o $@ $(LIBS) 2>/dev/null

$(CONF_OBJS): %.o : %.c $(SHARED_DEPS)
	@$(HOST_CC) $(HOST_CFLAGS) -I. -c $< -o $@ 2>/dev/null

$(MCONF_OBJS): %.o : %.c $(SHARED_DEPS)
	@$(HOST_CC) $(HOST_CFLAGS) -I. -c $< -o $@ 2>/dev/null

glob.o: glob.c $(SHARED_DEPS)
	@$(HOST_CC) $(HOST_CFLAGS) -I. -c glob.c -o $@ 2>/dev/null

lkc_defs.h: lkc_proto.h
	@sed < $< > $@ 's/P(\([^,]*\),.*/#define \1 (\*\1_p)/'

###
# The following requires flex/bison
# By default we use the _shipped versions, uncomment the
# following line if you are modifying the flex/bison src.
# LKC_GENPARSER:=	1

ifdef LKC_GENPARSER

%.tab.c %.tab.h: %.y
	bison -t -d -v -b $* -p $(notdir $*) $<

%.hash.c: %.gperf
	gperf -t --output-file zconf.hash.c -a -C -E -g -k '1,3,$$' -p -t zconf.gperf

lex.%.c: %.l
	flex -P$(notdir $*) -o$@ $<

lex.zconf.o: lex.zconf.c $(SHARED_DEPS)
	@$(HOST_CC) $(HOST_CFLAGS) -I. -c $< -o $@

zconf.tab.o: zconf.tab.c zconf.hash.c lex.zconf.c confdata.c expr.c symbol.c menu.c $(SHARED_DEPS)
	@$(HOST_CC) $(HOST_CFLAGS) -I. -c $< -o $@

else

lex.zconf.o: lex.zconf.c $(SHARED_DEPS)
	@$(HOST_CC) $(HOST_CFLAGS) -I. -c $< -o $@

lex.zconf.c: lex.zconf.c_shipped
	@$(CP) lex.zconf.c_shipped lex.zconf.c

zconf.hash.c: zconf.hash.c_shipped
	@$(CP) zconf.hash.c_shipped zconf.hash.c

zconf.tab.o: zconf.tab.c zconf.hash.c lex.zconf.c confdata.c expr.c symbol.c menu.c $(SHARED_DEPS)
	@$(HOST_CC) $(HOST_CFLAGS) -I. -c $< -o $@

zconf.tab.c: zconf.tab.c_shipped
	@$(CP) zconf.tab.c_shipped zconf.tab.c

zconf.tab.h: zconf.tab.h_shipped
	@$(CP) zconf.tab.h_shipped zconf.tab.h
endif

.PHONY: ncurses

ncurses:
	@echo "int main(void) { return -1; }" > lxtemp.c
	@if $(HOST_CC) $(HOST_CFLAGS) lxtemp.c $(LIBS) ; then \
		rm -f lxtemp.c a.out; \
	else \
		rm -f lxtemp.c; \
		printf '\007'; \
		echo ">> Unable to find the Ncurses libraries." ;\
		echo ">>" ;\
		echo ">> You must have Ncurses installed in order" ;\
		echo ">> to use 'make menuconfig'" ;\
		echo ;\
		exit 1 ;\
	fi

clean:
	@rm -f *.o *~ core $(TARGETS) $(MCONF_OBJS) $(CONF_OBJS) zconf.hash.c \
		conf mconf zconf.tab.c zconf.tab.h lex.zconf.c lkc_defs.h
