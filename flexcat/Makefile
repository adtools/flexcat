#
# $Id$
#

CC       = gcc
MAKEINFO = makeinfo
CFLAGS   = -g -funsigned-char -O2

# Might be replaced by 'delete'
REMOVE   = rm -f

# Overriding the OS definition is possible, for example "make OS=ABCDEF". Handy for cross-compiling.
ifndef (OS)
OS=$(shell uname)
endif

ifeq ($(OS), MorphOS)

# Building on MorphOS

# -lauto here is a workaround for libabox's bug. Without it locale.library will not
# be opened automatically. Don't remove it.
LDFLAGS     =	-lauto -noixemul
CATFILES    =   flexcat_cat.h
CATOBJS     =   locale.o

else
ifeq ($(OS), AmigaOS)

# Building on AmigaOS

LDFLAGS     =   -lamiga -noixemul
CATFILES    =   flexcat_cat.h
CATOBJS     =   locale.o

else
ifeq ($(OS), AmigaOS4)

# Building on AmigaOS 4

LDFLAGS     =   -newlib -lauto
CFLAGS      =   -newlib -D__USE_INLINE__
CATFILES    =   flexcat_cat.h
CATOBJS     =   locale.o getft.o

else

# Building on UNIX

LDFLAGS     =
CATFILES    =   flexcat_cat_other.h
CATOBJS     =   locale_other.o

endif
endif
endif

OBJS= createcat.o createcatsrc.o createct.o globals.o main.o readprefs.o \
      scancd.o scanct.o showfuncs.o swapfuncs.o utils.o $(CATOBJS)

all: $(CATFILES) flexcat

flexcat: $(OBJS) $(CATFILES)
	$(CC) -o flexcat $(OBJS) $(LDFLAGS)

locale.c: catalogs/FlexCat.cd lib/NoAutoC_c.sd
	flexcat catalogs/FlexCat.cd locale.c=lib/NoAutoC_c.sd
flexcat_cat.h: catalogs/FlexCat.cd lib/NoAutoC_h.sd
	flexcat catalogs/FlexCat.cd flexcat_cat.h=lib/NoAutoC_h.sd

locale_other.c: catalogs/FlexCat.cd lib/Hardcode_c.sd
	flexcat catalogs/FlexCat.cd locale_other.c=lib/Hardcode_c.sd
flexcat_cat_other.h: catalogs/FlexCat.cd lib/Hardcode_h.sd
	flexcat catalogs/FlexCat.cd flexcat_cat_other.h=lib/Hardcode_h.sd

clean:
	$(REMOVE) *.o
	$(REMOVE) flexcat

doc:
	$(MAKEINFO) docs/FlexCat_german.texinfo --amiga-39 --fill-column 76 --output docs/FlexCat_deutsch.guide
	$(MAKEINFO) docs/FlexCat_english.texinfo --amiga-39 --fill-column 76 --output docs/FlexCat_english.guide
	$(MAKEINFO) docs/FlexCat_spanish.texinfo --amiga-39 --fill-column 76 --output docs/FlexCat_español.guide
	$(MAKEINFO) docs/FlexCat_swedish.texinfo --amiga-39 --fill-column 76 --output docs/FlexCat_svenska.guide

