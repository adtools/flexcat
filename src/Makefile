#/***************************************************************************
#
# $Id$
#
# Copyright (C) 1993-1999 by Jochen Wiedmann and Marcin Orlowski
# Copyright (C) 2002-2007 by the FlexCat Open Source Team
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

CC          =   gcc
STRIP       =   strip
MAKEINFO    =   makeinfo
DEBUG       =   -ggdb -O0
CFLAGS      =   -O3 -fomit-frame-pointer -W -Wall -Wwrite-strings $(DEBUG)
CATFILES    =   FlexCat_cat.h FlexCat_cat_other.h locale.c locale_other.c
MKDIR       =   mkdir -p

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
  LDFLAGS     =   -noixemul
  LDLIBS      =   -lauto
  CATOBJS     =   locale.o

  ###########################################################################
else
  ifeq ($(OS), os3)

    # Building on AmigaOS3 ##################################################

    CC          =   m68k-amigaos-gcc
    STRIP       =   m68k-amigaos-strip
    CFLAGS      +=  -DNO_INLINE_STDARG
    LDFLAGS     =   -noixemul
    LDLIBS      =   -lamiga
    CATOBJS     =   locale.o getft.o

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
        LDLIBS      =   -lamiga
        CATOBJS     =   locale.o

        ###############################################################

      else

        # Building on UNIX ##############################################

        CFLAGS      +=  -m32
        LDFLAGS     =   -m32
        CATOBJS     =   locale_other.o
        OS          =   unix

        #################################################################
      endif
    endif
  endif
endif

OBJDIR = .obj_$(OS)
BINDIR = bin_$(OS)
TARGET = $(BINDIR)/FlexCat

OBJS= createcat.o createcatsrc.o createct.o globals.o main.o readprefs.o \
      scancd.o scanct.o showfuncs.o swapfuncs.o utils.o $(CATOBJS)

all: $(OBJDIR) $(BINDIR) $(CATFILES) $(TARGET)

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

$(TARGET): $(addprefix $(OBJDIR)/,$(OBJS)) $(CATFILES)
	@echo "  LD $@.debug"
	@$(CC) $(LDFLAGS) -o $@.debug $(addprefix $(OBJDIR)/,$(OBJS)) $(LDLIBS) -Wl,--cref,-M,-Map=$@.map
	@echo "  LD $@"
	@$(STRIP) --preserve-dates -R.comment -R.sdata2 -S -o $@ $@.debug

createcatsrc.o: createcatsrc.c flexcat.h readprefs.h swapfuncs.h showfuncs.h scancd.h scanct.h createcat.h globals.h utils.h

locale.c: catalogs/FlexCat.cd lib/NoAutoC_c.sd
    FlexCat catalogs/FlexCat.cd locale.c=lib/NoAutoC_c.sd
FlexCat_cat.h: catalogs/FlexCat.cd lib/NoAutoC_h.sd
    FlexCat catalogs/FlexCat.cd FlexCat_cat.h=lib/NoAutoC_h.sd
locale_other.c: catalogs/FlexCat.cd lib/Hardcode_c.sd
    FlexCat catalogs/FlexCat.cd locale_other.c=lib/Hardcode_c.sd
FlexCat_cat_other.h: catalogs/FlexCat.cd lib/Hardcode_h.sd
    FlexCat catalogs/FlexCat.cd FlexCat_cat_other.h=lib/Hardcode_h.sd

clean:
	-$(RM) $(addprefix $(OBJDIR)/,$(OBJS))
	-$(RM) $(BINDIR)/FlexCat
	-$(RM) ../doc/*.guide

realclean: clean
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
