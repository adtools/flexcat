#/***************************************************************************
#
# $Id$
#
# Copyright (C) 1993-1999 by Jochen Wiedmann and Marcin Orlowski
# Copyright (C) 2002-2010 by the FlexCat Open Source Team
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or (at
# your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
#***************************************************************************/

CC          = gcc
SED         = sed
STRIP       = strip
MAKEINFO    = makeinfo
WARN        = -W -Wall -Wwrite-strings
OPTFLAGS    = -O3 -fomit-frame-pointer
DEBUG       = -DDEBUG -fno-omit-frame-pointer #-O0
DEBUGSYM    = -g -gstabs
CFLAGS      = $(WARN) $(OPTFLAGS) $(DEBUG) $(DEBUGSYM)
CATFILES    = FlexCat_cat.h FlexCat_cat_other.h locale.c locale_other.c
MKDIR       = mkdir -p
FLEXCAT     = flexcat

# Might be replaced by 'delete'
RM          =   rm -f
RMDIR       =   rm -rf

# Overriding the OS definition is possible, for example "make OS=ABCDEF".
# Handy for cross-compiling.
ifndef (OS)
  OS          =   $(shell uname)

  # We separate AmigaOS 4.x from Classic AmigaOS and call it AmigaOS4.
  # We support both "ppc" and "powerpc" as result from "uname -m" for
  # compatibility with old coreutils releases.

  ifeq ($(OS), AmigaOS)
    ifeq ($(shell uname -m), powerpc)
      OS          =   os4
    endif
    ifeq ($(shell uname -m), ppc)
      OS          =   os4
    endif
  endif

endif

OBJS= createcat.o createcatsrc.o createct.o globals.o main.o readprefs.o \
      scancd.o scanct.o showfuncs.o swapfuncs.o utils.o $(CATOBJS)

CATALOGS = catalogs/croatian.catalog \
           catalogs/czech.catalog \
           catalogs/danish.catalog \
           catalogs/dutch.catalog \
           catalogs/finnish.catalog \
           catalogs/french.catalog \
           catalogs/german.catalog \
           catalogs/greek.catalog \
           catalogs/hungarian.catalog \
           catalogs/italian.catalog \
           catalogs/norwegian.catalog \
           catalogs/polish.catalog \
           catalogs/portuguese.catalog \
           catalogs/serbian.catalog \
           catalogs/slovenian.catalog \
           catalogs/spanish.catalog \
           catalogs/swedish.catalog
           # catalogs/swabian.catalog
           # catalogs/turkish.catalog

# Default CPU for AROS
ifndef (CPU)
  CPU = i386
endif

ifeq ($(OS), mos)

  # Building on MorphOS #####################################################

  # -lauto here is a workaround for libabox's bug. Without it locale.library
  # will not be opened automatically. Don't remove it.
  CC          =   ppc-morphos-gcc
  STRIP       =   ppc-morphos-strip
  CFLAGS      +=  -noixemul -mcpu=powerpc
  LDFLAGS     =   -noixemul
  OBJS        +=  asprintf.o vasprintf.o
  LDLIBS      =   -lauto
  CATOBJS     =   locale.o

  ###########################################################################
else
  ifeq ($(OS), os3)

    # Building on AmigaOS3 ##################################################

    CC          =   m68k-amigaos-gcc
    STRIP       =   m68k-amigaos-strip
    CFLAGS      +=  -noixemul -DNO_INLINE_STDARG -m68020-60 -msoft-float
    LDFLAGS     =   -noixemul
    LDLIBS      =   -lamiga
    CATOBJS     =   locale.o getft.o openlibs.o vastubs.o

    #########################################################################

  else
    ifeq ($(OS), os4)

      # Building on AmigaOS 4 ###############################################

      CC          =   ppc-amigaos-gcc
      STRIP       =   ppc-amigaos-strip
      CFLAGS      +=  -mcrt=newlib -D__USE_INLINE__
      LDFLAGS     =   -mcrt=newlib
      LDLIBS      =   -lauto -lunix
      CATOBJS     =   locale.o getft.o

      #######################################################################

    else
      ifeq ($(OS), aros-i386)

        # Building on AROS ############################################

        CC          =   $(CPU)-aros-gcc
        LDFLAGS     =
        OBJS        +=  asprintf.o vasprintf.o
        LDLIBS      =   -lamiga
        CATOBJS     =   locale.o

        ###############################################################

      else
        ifeq ($(OS), mingw32)

          # Building on Windows/mingw32 #################################

          CC          =   i586-mingw32msvc-gcc
          LDFLAGS     =
          OBJS        +=  asprintf.o vasprintf.o
          CATOBJS     =   locale_other.o
          EXE         =   .exe

          ###############################################################

        else

          # Building on UNIX ##############################################

          CFLAGS      +=  -m32 -D_GNU_SOURCE
          LDFLAGS     =   -m32
          CATOBJS     =   locale_other.o
          OS          =   unix

          #################################################################
        endif
      endif
    endif
  endif
endif

OBJDIR = .obj_$(OS)
BINDIR = bin_$(OS)
TARGET = $(BINDIR)/flexcat$(EXE)

all: $(OBJDIR) $(BINDIR) $(TARGET)

# for making a release we compile ALL target with no debug
release:
	@echo "  CC $<"
	make OS=os4 clean
	make OS=os4 DEBUG=
	@echo "  CC $<"
	make OS=os3 clean
	make OS=os3 DEBUG=
	@echo "  CC $<"
	make OS=mos clean
	make OS=mos DEBUG=
	@echo "  CC $<"
	make OS=aros-i386 clean
	make OS=aros-i386 DEBUG=
	@echo "  CC $<"
	make OS=aros-ppc clean
	make OS=aros-ppc DEBUG=
	@echo "  CC $<"
	make OS=aros-x86_64 clean
	make OS=aros-x86_64 DEBUG=
	@echo "  CC $<"
	make OS=unix clean
	make OS=unix DEBUG=
	@echo "  CC $<"
	make OS=mingw32 clean
	make OS=mingw32 DEBUG=

# make the object directories
$(OBJDIR):
	@echo "  MK $@"
	@$(MKDIR) $(OBJDIR)

$(BINDIR):
	@echo "  MK $@"
	@$(MKDIR) $(BINDIR)

# for compiling single .c files
$(OBJDIR)/%.o: %.c
	@echo "  CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(CATFILES) $(addprefix $(OBJDIR)/,$(OBJS))
	@echo "  LD $@.debug"
	@$(CC) $(LDFLAGS) -o $@.debug $(addprefix $(OBJDIR)/,$(OBJS)) $(LDLIBS) -Wl,--cref,-M,-Map=$@.map
	@echo "  LD $@"
	@$(STRIP) --preserve-dates -R.comment -R.sdata2 -S -o $@ $@.debug

locale.c: catalogs/FlexCat.cd lib/NoAutoC_c.sd
	@echo "  FC $@"
	@$(FLEXCAT) catalogs/FlexCat.cd locale.c=lib/NoAutoC_c.sd

FlexCat_cat.h: catalogs/FlexCat.cd lib/NoAutoC_h.sd
	@echo "  FC $@"
	@$(FLEXCAT) catalogs/FlexCat.cd FlexCat_cat.h=lib/NoAutoC_h.sd

locale_other.c: catalogs/FlexCat.cd lib/Hardcode_c.sd
	@echo "  FC $@"
	@$(FLEXCAT) catalogs/FlexCat.cd locale_other.c=lib/Hardcode_c.sd

FlexCat_cat_other.h: catalogs/FlexCat.cd lib/Hardcode_h.sd
	@echo "  FC $@"
	@$(FLEXCAT) catalogs/FlexCat.cd FlexCat_cat_other.h=lib/Hardcode_h.sd

catalogs/%.catalog: catalogs/%.ct catalogs/FlexCat.cd
	@echo "  MK $@"
	@$(FLEXCAT) catalogs/FlexCat.cd $< CATALOG $@

.IGNORE: $(CATALOGS)

catalogs: $(CATALOGS)

clean:
	-$(RM) $(addprefix $(OBJDIR)/,$(OBJS))
	-$(RM) $(BINDIR)/$(FLEXCAT)
	-$(RM) ../doc/*.guide

cleanall: clean
	-$(RM) FlexCat_cat.h
	-$(RM) FlexCat_cat_other.h
	-$(RM) locale.c
	-$(RM) locale_other.c
	-$(RMDIR) $(OBJDIR)

doc:
	$(MAKEINFO) ../doc/FlexCat_german.texinfo --amiga-39 --fill-column 76 --output ../doc/FlexCat_deutsch.guide
	$(MAKEINFO) ../doc/FlexCat_english.texinfo --amiga-39 --fill-column 76 --output ../doc/FlexCat_english.guide
	$(MAKEINFO) ../doc/FlexCat_spanish.texinfo --amiga-39 --fill-column 76 --output ../doc/FlexCat_español.guide
	$(MAKEINFO) ../doc/FlexCat_swedish.texinfo --amiga-39 --fill-column 76 --output ../doc/FlexCat_svenska.guide

## DEPENDENCY GENERATION ##############

Makefile.dep: ;
	@echo "WARNING: Makefile.dep missing. Please run 'make depend'"

.PHONY: depend
depend: locale.c locale_other.c
	@echo "  MK Makefile.dep"
	@$(CC) -MM -MG $(CFLAGS) $(wildcard *.c) >/tmp/Makefile.dep1
	@$(SED) -i 's,^\(.*\)\.o:,$$\(OBJDIR\)/\1.o:,g' /tmp/Makefile.dep1
	@echo "# AUTOGENERATED! DO NOT EDIT!!!" >Makefile.dep
	@cat /tmp/Makefile.dep? >>Makefile.dep
	@echo "# AUTOGENERATED! DO NOT EDIT!!!" >>Makefile.dep
	@$(RM) /tmp/Makefile.dep?

## DEPENDENCY INCLUDE #################

-include Makefile.dep
