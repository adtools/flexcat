
/* $Id$
 * 
 * Copyright (C) 1993-1999 by Jochen Wiedmann and Marcin Orlowski
 * Copyright (C) 2002-2007 by the FlexCat Open Source Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef  FLEXCAT_H
#define  FLEXCAT_H

/* Amiga enviroment? */
#ifdef AMIGA
 #define __amigados
 #include "FlexCat_cat.h"
#else
 #undef __amigados
 #include "FlexCat_cat_other.h"
#endif

#define VERSION                2
#define REVISION               7
#define DATE                   "21.01.2007"
#define VERS                   "FlexCat 2.7-dev"
#define VSTRING                VERS " (" DATE ") (C) 2002-2007 FlexCat Open Source Team"
#define VERSTAG                "\0$VER: " VSTRING

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#ifdef __amigados
 #include <dos/dos.h>
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
 #define tolower ToLower
#endif


#ifndef FALSE
 #define FALSE 0
#endif
#ifndef TRUE
 #define TRUE  1
#endif


#define MAXPATHLEN             512
#define FLEXCAT_SDDIR          "FLEXCAT_SDDIR"

#if defined(__amigados)
 #define FILE_MASK             FIBF_EXECUTE
 #define DEFAULT_FLEXCAT_SDDIR "PROGDIR:lib"
#else
 #define DEFAULT_FLEXCAT_SDDIR "lib"
#endif


// we have to care about own basic datatype
// definitions as flexcat may also be compiled
// on 64bit environments (e.g. linux)
//
// in fact, these definitions are borrowed from
// the OS4 SDK and we bring them onto all the
// other OSs as well....
#if !defined(__amigaos4__)
typedef unsigned char uint8;
typedef   signed char  int8;

typedef unsigned short uint16;
typedef   signed short  int16;

typedef unsigned long uint32;
typedef   signed long  int32;

#if !defined(__SASC) && ((__GNUC__ >= 3 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)) || defined(__VBCC__))
typedef unsigned long long uint64;
typedef   signed long long  int64;
#else
typedef struct { unsigned long hi,lo; } uint64; /* Not exactly scalar data
                                                 * types, but the right size.
                                                 */
typedef struct { long hi,lo; }           int64;
#endif

typedef uint8  UBYTE;
typedef  int8   BYTE;
typedef uint8   BYTEBITS;
typedef uint16 UWORD;
typedef  int16  WORD;
typedef uint16  WORDBITS;
typedef uint32 ULONG;
typedef  int32  LONG;
typedef uint32  LONGBITS;
typedef uint16  RPTR;

#endif /* !__amigaos4__ */

#ifndef MAKE_ID
 #define MAKE_ID(a,b,c,d)      ((ULONG) (a)<<24 | (ULONG) (b)<<16 | (ULONG) (c)<<8 | (ULONG) (d))
#endif

#define MAX_NEW_STR_LEN        25
#define BUFSIZE                4096

struct CDLine
{
    struct CDLine  *Next;
    char           *Line;
};

struct CatString
{
    struct CatString *Next;
    char             *CD_Str;
    char             *CT_Str;
    char             *ID_Str;
    int               MinLen, MaxLen, ID, Nr, LenBytes;
    int               NotInCT;    /* If a string is not present, we write NEW
                                     while updating the CT file for easier work. */

};

struct CatalogChunk
{
    struct CatalogChunk *Next;  /* struct CatalogChunk *Next */
    ULONG                ID;
    char                *ChunkStr;
};

int32 getft ( char *filename );

#endif  /* FLEXCAT_H */
