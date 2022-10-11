# toolbox for OpenADK on memory-constrained NOMMU binfmt_flat systems
# Copyright © 2017
#	mirabilos <m@mirbsd.org>
# Derived from Android Toolbox
# platform/system/core, as of commit efbf36f2dad8f083de6f48dbb682461d7cfa9781
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.
#
# Individual files are covered by their own licence notices, which are
# also reproduced below (at the end of the top-level Makefile, this file).
# Changes to those files done within the OpenADK toolbox and the build
# system of the toolbox are published under Ⓕ The MirOS Licence as above.
#
# Summarising the licences used:
# • 3-clause BSD
# • ISC (OpenBSD)
# • MirOS
# • Public Domain

  SUBDIR+= lib

  SUBDIR+= cat
  SUBDIR+= chmod
  SUBDIR+= chown
  SUBDIR+= clear
  SUBDIR+= cmp
  SUBDIR+= cp
  SUBDIR+= date
  SUBDIR+= dd
  SUBDIR+= df
  SUBDIR+= dmesg
  SUBDIR+= du
  SUBDIR+= exists
  SUBDIR+= grep
  SUBDIR+= hd
  SUBDIR+= id
  SUBDIR+= ifconfig
  SUBDIR+= iftop
  SUBDIR+= insmod
#  SUBDIR+= ioctl needs pthread.h
  SUBDIR+= kill
  SUBDIR+= ln
  SUBDIR+= ls
  SUBDIR+= lsof
  SUBDIR+= md5
  SUBDIR+= mkdir
#  SUBDIR+= mknod # does not compile with glibc
  SUBDIR+= mount
  SUBDIR+= mv
  SUBDIR+= netstat
  SUBDIR+= notify
  SUBDIR+= printenv
  SUBDIR+= ps
  SUBDIR+= readlink
  SUBDIR+= renice
  SUBDIR+= rm
  SUBDIR+= rmdir
  SUBDIR+= rmmod
  SUBDIR+= route
  SUBDIR+= schedtop
  SUBDIR+= sed
  SUBDIR+= setkey
  SUBDIR+= sleep
  SUBDIR+= sync
  SUBDIR+= top
  SUBDIR+= touch
  SUBDIR+= umount
  SUBDIR+= vmstat

%:
	@for subdir in ${SUBDIR}; do \
		echo "==> $$subdir"; \
		${MAKE} --no-print-directory -I.. \
		    -C "$$subdir" $@ || exit $?; \
		echo "<== $$subdir"; \
	done

all:

#======================================
# Now follows the original NOTICE file:
#======================================

# Copyright (c) 2010, The Android Open Source Project.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
#  * Neither the name of The Android Open Source Project nor the names
#    of its contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
# OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#
# Copyright (c) 2009, The Android Open Source Project.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
#  * Neither the name of The Android Open Source Project nor the names
#    of its contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
# OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#
# Copyright (c) 2008, The Android Open Source Project.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
#  * Neither the name of The Android Open Source Project nor the names
#    of its contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
# OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#
# Copyright (c) 1998 Robert Nordier
# Copyright (c) 1989, 1993
#      The Regents of the University of California.  All rights reserved.
#
# This code is derived from software contributed to Berkeley by
# Kevin Fall.
# This code is derived from software contributed to Berkeley by
# Keith Muller of the University of California, San Diego and Lance
# Visser of Convex Computer Corporation.
# This code is derived from software contributed to Berkeley by
# Mike Muuss.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#
#
#  Copyright (c) 1989, 1993
# 	The Regents of the University of California.  All rights reserved.
#
#  This code is derived from software contributed to Berkeley by
#  Kevin Fall.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. Neither the name of the University nor the names of its contributors
#     may be used to endorse or promote products derived from this software
#     without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
#  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
#  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#  SUCH DAMAGE.
#
#
#  Copyright (c) 1991, 1993, 1994
# 	The Regents of the University of California.  All rights reserved.
#
#  This code is derived from software contributed to Berkeley by
#  Keith Muller of the University of California, San Diego and Lance
#  Visser of Convex Computer Corporation.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. Neither the name of the University nor the names of its contributors
#     may be used to endorse or promote products derived from this software
#     without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
#  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
#  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#  SUCH DAMAGE.
#
#
# /*
#  * Copyright (c) 1985, 1987, 1988, 1993
#  *	The Regents of the University of California.  All rights reserved.
#  *
#  * Redistribution and use in source and binary forms, with or without
#  * modification, are permitted provided that the following conditions
#  * are met:
#  * 1. Redistributions of source code must retain the above copyright
#  *    notice, this list of conditions and the following disclaimer.
#  * 2. Redistributions in binary form must reproduce the above copyright
#  *    notice, this list of conditions and the following disclaimer in the
#  *    documentation and/or other materials provided with the distribution.
#  * 3. Neither the name of the University nor the names of its contributors
#  *    may be used to endorse or promote products derived from this software
#  *    without specific prior written permission.
#  *
#  * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
#  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
#  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
#  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#  * SUCH DAMAGE.
#  */
#
# /*-
#  * Copyright (c) 2007, 2009
#  *	Thorsten Glaser <tg@mirbsd.org>
#  *
#  * Provided that these terms and disclaimer and all copyright notices
#  * are retained or reproduced in an accompanying document, permission
#  * is granted to deal in this work without restriction, including un-
#  * limited rights to use, publicly perform, distribute, sell, modify,
#  * merge, give away, or sublicence.
#  *
#  * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
#  * the utmost extent permitted by applicable law, neither express nor
#  * implied; without malicious intent or gross negligence. In no event
#  * may a licensor, author or contributor be held liable for indirect,
#  * direct, other damage, loss, or other issues arising in any way out
#  * of dealing in the work, even if advised of the possibility of such
#  * damage or existence of a defect, except proven that it results out
#  * of said person's immediate fault when using the work as intended.
#  */
#
# /*
#  * This code implements the MD5 message-digest algorithm.
#  * The algorithm is due to Ron Rivest.	This code was
#  * written by Colin Plumb in 1993, no copyright is claimed.
#  * This code is in the public domain; do with it what you wish.
#  */
#
# /*-
#  * Copyright (c) 2006, 2008, 2011
#  *	mirabilos <m@mirbsd.org>
#  *
#  * Provided that these terms and disclaimer and all copyright notices
#  * are retained or reproduced in an accompanying document, permission
#  * is granted to deal in this work without restriction, including un-
#  * limited rights to use, publicly perform, distribute, sell, modify,
#  * merge, give away, or sublicence.
#  *
#  * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
#  * the utmost extent permitted by applicable law, neither express nor
#  * implied; without malicious intent or gross negligence. In no event
#  * may a licensor, author or contributor be held liable for indirect,
#  * direct, other damage, loss, or other issues arising in any way out
#  * of dealing in the work, even if advised of the possibility of such
#  * damage or existence of a defect, except proven that it results out
#  * of said person's immediate fault when using the work as intended.
#  */
#
# /*-
#  * Copyright (c) 1998 Todd C. Miller <Todd.Miller@courtesan.com>
#  *
#  * Permission to use, copy, modify, and distribute this software for any
#  * purpose with or without fee is hereby granted, provided that the above
#  * copyright notice and this permission notice appear in all copies.
#  *
#  * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#  * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#  * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#  * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#  * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#  * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#  * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#  */
#
# /*
#  * Copyright (c) 1989, 1990, 1993
#  *	The Regents of the University of California.  All rights reserved.
#  *
#  * This code is derived from software contributed to Berkeley by
#  * Kevin Fall.
#  *
#  * Redistribution and use in source and binary forms, with or without
#  * modification, are permitted provided that the following conditions
#  * are met:
#  * 1. Redistributions of source code must retain the above copyright
#  *    notice, this list of conditions and the following disclaimer.
#  * 2. Redistributions in binary form must reproduce the above copyright
#  *    notice, this list of conditions and the following disclaimer in the
#  *    documentation and/or other materials provided with the distribution.
#  * 3. Neither the name of the University nor the names of its contributors
#  *    may be used to endorse or promote products derived from this software
#  *    without specific prior written permission.
#  *
#  * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
#  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
#  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
#  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#  * SUCH DAMAGE.
#  */
#
# /*
#  * Copyright (c) 1989, 1993, 1994
#  *	The Regents of the University of California.  All rights reserved.
#  *
#  * This code is derived from software contributed to Berkeley by
#  * Dave Borman at Cray Research, Inc.
#  *
#  * Redistribution and use in source and binary forms, with or without
#  * modification, are permitted provided that the following conditions
#  * are met:
#  * 1. Redistributions of source code must retain the above copyright
#  *    notice, this list of conditions and the following disclaimer.
#  * 2. Redistributions in binary form must reproduce the above copyright
#  *    notice, this list of conditions and the following disclaimer in the
#  *    documentation and/or other materials provided with the distribution.
#  * 3. Neither the name of the University nor the names of its contributors
#  *    may be used to endorse or promote products derived from this software
#  *    without specific prior written permission.
#  *
#  * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
#  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
#  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
#  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#  * SUCH DAMAGE.
#  */
#
# /*-
#  * Copyright (c) 2015, 2016, 2017
#  *	mirabilos <m@mirbsd.org>
#  * Copyright (c) 1992 Diomidis Spinellis.
#  * Copyright (c) 1992, 1993
#  *	The Regents of the University of California.  All rights reserved.
#  *
#  * This code is derived from software contributed to Berkeley by
#  * Diomidis Spinellis of Imperial College, University of London.
#  *
#  * Redistribution and use in source and binary forms, with or without
#  * modification, are permitted provided that the following conditions
#  * are met:
#  * 1. Redistributions of source code must retain the above copyright
#  *    notice, this list of conditions and the following disclaimer.
#  * 2. Redistributions in binary form must reproduce the above copyright
#  *    notice, this list of conditions and the following disclaimer in the
#  *    documentation and/or other materials provided with the distribution.
#  * 3. Neither the name of the University nor the names of its contributors
#  *    may be used to endorse or promote products derived from this software
#  *    without specific prior written permission.
#  *
#  * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
#  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#  * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
#  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
#  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
#  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
#  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
#  * SUCH DAMAGE.
#  */
#
# /*
#  * Copyright (c) 2008 Otto Moerbeek <otto@drijf.net>
#  *
#  * Permission to use, copy, modify, and distribute this software for any
#  * purpose with or without fee is hereby granted, provided that the above
#  * copyright notice and this permission notice appear in all copies.
#  *
#  * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#  * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
#  * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
#  * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
#  * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
#  * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
#  * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#  */
#
# /*-
#  * Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
#  *		 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017
#  *	mirabilos <m@mirbsd.org>
#  *
#  * Provided that these terms and disclaimer and all copyright notices
#  * are retained or reproduced in an accompanying document, permission
#  * is granted to deal in this work without restriction, including un-
#  * limited rights to use, publicly perform, distribute, sell, modify,
#  * merge, give away, or sublicence.
#  *
#  * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
#  * the utmost extent permitted by applicable law, neither express nor
#  * implied; without malicious intent or gross negligence. In no event
#  * may a licensor, author or contributor be held liable for indirect,
#  * direct, other damage, loss, or other issues arising in any way out
#  * of dealing in the work, even if advised of the possibility of such
#  * damage or existence of a defect, except proven that it results out
#  * of said person's immediate fault when using the work as intended.
#  */
