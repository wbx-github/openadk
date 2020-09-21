#	$OpenBSD: Makefile,v 1.7 2015/09/11 21:07:01 beck Exp $

PROG=	nc
SRCS=	netcat.c atomicio.c socks.c

PKG_CONFIG ?= pkg-config
LIBS=  `$(PKG_CONFIG) --libs libbsd` -lresolv
OBJS=  $(SRCS:.c=.o)
CFLAGS=  -g -O2
LDFLAGS=  -Wl,--no-add-needed

all: nc
nc: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o nc

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) nc
