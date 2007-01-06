#
# $Id$
#

CC          = gcc
MAKEINFO    = makeinfo
CFLAGS      = -ggdb -funsigned-char -O2 -Wall -Wwrite-strings
CATFILES    = FlexCat_cat.h FlexCat_cat_other.h locale.c locale_other.c

# Might be replaced by 'delete'
REMOVE      = rm -f

# Overriding the OS definition is possible, for example "make OS=ABCDEF". Handy for cross-compiling.
ifndef (OS)
OS          =   $(shell uname)

# We separate AmigaOS 4.x from Classic AmigaOS and call it AmigaOS4.
ifeq ($(OS), AmigaOS)
ifeq ($(shell uname -m), ppc)
OS          =   AmigaOS4
endif
endif

endif

ifeq ($(OS), MorphOS)

# Building on MorphOS

# -lauto here is a workaround for libabox's bug. Without it locale.library will not
# be opened automatically. Don't remove it.
CC          =   ppc-morphos-gcc
LDFLAGS     =   -lauto -noixemul
CATOBJS     =   locale.o

else
ifeq ($(OS), AmigaOS)

# Building on AmigaOS

CC          =   m68k-amigaos-gcc
LDFLAGS     =   -lamiga -noixemul
CFLAGS      +=  -DNO_INLINE_STDARG
CATOBJS     =   locale.o getft.o

else
ifeq ($(OS), AmigaOS4)

# Building on AmigaOS 4

CC          =   ppc-amigaos-gcc
LDFLAGS     =   -mcrt=newlib -lauto -lunix
CFLAGS      +=  -mcrt=newlib -D__USE_INLINE__
CATOBJS     =   locale.o getft.o

else

# Building on UNIX

LDFLAGS     =
CATOBJS     =   locale_other.o

endif
endif
endif

OBJS= createcat.o createcatsrc.o createct.o globals.o main.o readprefs.o \
      scancd.o scanct.o showfuncs.o swapfuncs.o utils.o $(CATOBJS)

all: $(CATFILES) FlexCat

FlexCat: $(OBJS) $(CATFILES)
	$(CC) -o FlexCat $(OBJS) $(LDFLAGS)

locale.c: catalogs/FlexCat.cd lib/NoAutoC_c.sd
	FlexCat catalogs/FlexCat.cd locale.c=lib/NoAutoC_c.sd
FlexCat_cat.h: catalogs/FlexCat.cd lib/NoAutoC_h.sd
	FlexCat catalogs/FlexCat.cd FlexCat_cat.h=lib/NoAutoC_h.sd
locale_other.c: catalogs/FlexCat.cd lib/Hardcode_c.sd
	FlexCat catalogs/FlexCat.cd locale_other.c=lib/Hardcode_c.sd
FlexCat_cat_other.h: catalogs/FlexCat.cd lib/Hardcode_h.sd
	FlexCat catalogs/FlexCat.cd FlexCat_cat_other.h=lib/Hardcode_h.sd

clean:
	$(REMOVE) *.o
	$(REMOVE) FlexCat
	$(REMOVE) ../doc/*.guide

realclean:
	$(REMOVE) *.o
	$(REMOVE) FlexCat
	$(REMOVE) ../doc/*.guide
	$(REMOVE) FlexCat_cat.h
	$(REMOVE) FlexCat_cat_other.h
	$(REMOVE) locale.c
	$(REMOVE) locale_other.c

doc:
	$(MAKEINFO) ../doc/FlexCat_german.texinfo --amiga-39 --fill-column 76 --output ../doc/FlexCat_deutsch.guide
	$(MAKEINFO) ../doc/FlexCat_english.texinfo --amiga-39 --fill-column 76 --output ../doc/FlexCat_english.guide
	$(MAKEINFO) ../doc/FlexCat_spanish.texinfo --amiga-39 --fill-column 76 --output ../doc/FlexCat_español.guide
	$(MAKEINFO) ../doc/FlexCat_swedish.texinfo --amiga-39 --fill-column 76 --output ../doc/FlexCat_svenska.guide
