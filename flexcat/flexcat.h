
/* $Id$
 * 
 * Copyright (C) 1993-1999 by Jochen Wiedmann and Marcin Orlowski
 * Copyright (C) 2002-2006 by the FlexCat Open Source Team
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

// Amiga enviroment?
#ifdef AMIGA
 #define __amigados
 #include "flexcat_cat.h"
#else
 #undef __amigados
 #include "flexcat_cat_other.h"
#endif

#define VERSION                2
#define REVISION               7
#define DATE                   "1.11.2006"
#define VERS                   "FlexCat 2.7-dev"
#define VSTRING                VERS " (" DATE ") (C) 2002-2006 FlexCat Open Source Team"
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
 #define TRUE (!FALSE)
#endif


#define MAXPATHLEN             512
#define FLEXCAT_SDDIR          "FLEXCAT_SDDIR"

#if defined(__amigados)
 #define FILE_MASK             FIBF_EXECUTE
 #define DEFAULT_FLEXCAT_SDDIR "PROGDIR:lib"
#else
 #define DEFAULT_FLEXCAT_SDDIR "lib"
#endif

#ifndef MAKE_ID
 #define MAKE_ID(a,b,c,d)      ((ULONG) (a)<<24 | (ULONG) (b)<<16 | (ULONG) (c)<<8 | (ULONG) (d))
#endif

#ifndef ULONG
 #define ULONG                 unsigned long
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

long getft ( char *filename );

#endif  /* FLEXCAT_H */
