# Makefile for `Wget' utility
# Copyright (C) 1995, 1996, 1997, 2006, 2007,
# 2008 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Additional permission under GNU GPL version 3 section 7

# If you modify this program, or any covered work, by linking or
# combining it with the OpenSSL project's OpenSSL library (or a
# modified version of that library), containing parts covered by the
# terms of the OpenSSL or SSLeay licenses, the Free Software Foundation
# grants you additional permission to convey the resulting work.
# Corresponding Source for a non-source form of such a combination
# shall include the source code for the parts of OpenSSL used as well
# as that of the covered work.

#
# Version: 1.11.2
#

SHELL = /bin/sh


top_builddir = .

srcdir = .


#
# User configuration section
#

#
# Install variables
#
prefix      = /usr/local
exec_prefix = ${prefix}
bindir      = ${exec_prefix}/bin
infodir     = ${prefix}/info
sysconfdir  = ${prefix}/etc
mandir      = ${prefix}/man
manext      = 1
localedir   = $(prefix)/share/locale

#CC = mips-linux-uclibc-gcc -mips32r2 -msoft-float
CFLAGS =  -O2 -Wall
CPPFLAGS = 
DEFS = -DHAVE_CONFIG_H -DSYSTEM_WGETRC=\"$(sysconfdir)/wgetrc\" -DLOCALEDIR=\"$(localedir)\"
LIBS = -ldl     
LDFLAGS = 

#
# End of user configuration section.  There should be no need to change
# anything below this line.
#

DISTNAME = wget-1.11.2
RM = rm -f

# These are used for maintenance only, so they are safe without
# special autoconf cruft.
FIND = find
GZIP = gzip
TAR = tar

# flags passed to recursive makes in subdirectories
MAKEDEFS = CC='$(CC)' CPPFLAGS='$(CPPFLAGS)' DEFS='$(DEFS)' \
CFLAGS='$(CFLAGS)' LDFLAGS='$(LDFLAGS)' LIBS='$(LIBS)' \
DESTDIR='$(DESTDIR)' prefix='$(prefix)' exec_prefix='$(exec_prefix)' \
bindir='$(bindir)' infodir='$(infodir)' mandir='$(mandir)' \
manext='$(manext)'

# subdirectories in the distribution
SUBDIRS = src doc po tests util windows

# default target
all: src/config.h Makefile $(SUBDIRS)

test: src/config.h Makefile src
	cd tests && $(MAKE) $(MAKEDEFS) $@
	
check: all

$(SUBDIRS): FORCE
	cd $@ && $(MAKE) $(MAKEDEFS)

# install everything
install: install.bin install.info install.wgetrc \
	 install.mo install.man

# install/uninstall the binary
install.bin uninstall.bin:
	cd src && $(MAKE) $(MAKEDEFS) $@

# Rules for info, man page (needed for make dist)
doc/wget.1 doc/wget.info:
	cd doc && $(MAKE) $(MAKEDEFS)

# install/uninstall the info/man pages
install.info uninstall.info install.man uninstall.man install.wgetrc:
	cd doc && $(MAKE) $(MAKEDEFS) $@

# Install `.mo' files
install.mo:
	cd po && $(MAKE) $(MAKEDEFS) $@

# create tag files for Emacs
TAGS:
	cd src && $(MAKE) $@

dist: $(srcdir)/configure doc/wget.1 doc/wget.info DISTFILES
	mkdir $(DISTNAME)
	for d in `$(FIND) . -type d ! -regex '.*/\.\(svn\|hg\)\(/.*\)?' -print`; do \
		if [ "$$d" != "." -a "$$d" != "./$(DISTNAME)" ]; then \
			mkdir $(DISTNAME)/$$d; \
		fi; \
	done
	for f in `cat DISTFILES`; do \
		ln $(srcdir)/$$f $(DISTNAME)/$$f || \
		{ echo copying $$f; cp -p $(srcdir)/$$f $(DISTNAME)/$$f ; } \
	done
	$(TAR) chvf - $(DISTNAME) | $(GZIP) -c --best >$(DISTNAME).tar.gz
	$(RM) -r $(DISTNAME)

#
# Cleanup dependencies
#

clean:		clean-recursive		clean-top
distclean:	distclean-recursive	distclean-top
realclean:	realclean-recursive	realclean-top

clean-top:
	$(RM) *~ *.bak $(DISTNAME).tar.gz

distclean-top: clean-top
	$(RM) Makefile config.status config.log config.cache libtool stamp-h
	$(RM) -r autom4te.cache

realclean-top: distclean-top
	$(RM) configure

clean-recursive distclean-recursive realclean-recursive:
	for subdir in $(SUBDIRS); do \
	   target=`echo $@ | sed s/-recursive//`; \
	   (cd $$subdir && $(MAKE) $(MAKEDEFS) $$target) || exit 1; \
	done

#
# Dependencies for maintenance
#

$(srcdir)/configure: configure.in
	cd $(srcdir) && autoconf

# autoheader might not change config.h.in, so touch a stamp file.
$(srcdir)/src/config.h.in: stamp-h.in
$(srcdir)/stamp-h.in: configure.in
	@true; # running autoheader here breaks: cd $(srcdir) && autoheader
	echo timestamp > $(srcdir)/stamp-h.in

src/config.h: stamp-h
stamp-h: src/config.h.in config.status
	./config.status

Makefile: Makefile.in config.status
	./config.status

config.status: configure
	./config.status --recheck

FORCE:
