
/*
 * FlexCat.h
 */

#ifndef  FLEXCAT_H
#define  FLEXCAT_H

// undef if not on Amiga
#define __amigados

#define VERSION 2
#define REVISION 6
#define VERS       "FlexCat 2.6.3"

#ifdef __amigados

#if (defined(_M68060) || defined(__mc68060))
#define _CPU "[68060]"
#else
#if (defined(_M68040) || defined(__mc68040))
#define _CPU "[68040]"
#else
#if (defined(_M68030) || defined(__mc68030))
#define _CPU "[68030]"
#else
#if (defined(_M68020) || defined(__mc68020))
#define _CPU "[68020]"
#else
#if (defined(_M68010) || defined(__mc68010))
#define _CPU "[68010]"
#else
#define _CPU "[680x0]"
#endif
#endif
#endif
#endif
#endif

#define VSTRING  VERS " " _CPU " " __DATE__
#else
#define VSTRING  VERS
#endif

#define VERSTAG  "$VER: " VSTRING

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef __amigados
#include <dos.h>
#endif

#if ((defined(_DCC) && defined(AMIGA))       ||     \
	 (defined(__SASC) && defined(_AMIGA)))      &&  \
	!defined(__amigados)
#define __amigados
#endif

#if defined(__amigados)
#include <exec/types.h>
#if defined(_DCC) || defined(__SASC) || defined(__GNUC__)
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <proto/utility.h>
#else
#include <clib/exec_protos.h>
#include <clib/dos_protos.h>
#include <clib/utility_protos.h>
#endif

#ifdef tolower
#undef tolower
#endif
#define tolower         ToLower
#define stricmp(s,t)    Stricmp((char *) (s), (char *) (t))
#define strnicmp(s,t,l) Strnicmp((char *) (s), (char *) (t), l)

#endif


#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif


#define MAXPATHLEN 512
#define FLEXCAT_SDDIR "FLEXCAT_SDDIR"
#if defined(__amigados)
#define DEFAULT_FLEXCAT_SDDIR "PROGDIR:lib"
#else
#define DEFAULT_FLEXCAT_SDDIR "lib"
#endif

#ifndef MAKE_ID
#define MAKE_ID(a,b,c,d)        \
		((ULONG) (a)<<24 | (ULONG) (b)<<16 | (ULONG) (c)<<8 | (ULONG) (d))
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#define MAX_NEW_STR_LEN 25
#define BUFSIZE 4096

struct CDLine
{
    struct CDLine  *Next;
    char           *Line;
};

struct CatString
{
    struct CatString *Next;
    char           *CD_Str;
    char           *CT_Str;
    char           *ID_Str;
    int             MinLen, MaxLen, ID, Nr;
    int             NotInCT;    /* If string is not present we write NEW
                                   while updating CT file, for easier work. */

};

struct CatalogChunk
{
    struct CatalogChunk *Next;  /* struct CatalogChunk *Next */
    ULONG           ID;
    char           *ChunkStr;
};

#endif
