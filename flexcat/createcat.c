
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

#include "flexcat.h"
#include "scanct.h"
#include "showfuncs.h"
#include "readprefs.h"
#include "swapfuncs.h"
#include "globals.h"
#include "utils.h"

struct CatString *FirstCatString = NULL;       /* First catalog string */
struct CatalogChunk *FirstChunk = NULL;        /* List of catalog chunks */

/// FUNC: CatPuts

/* CatPuts prints a string to a catalog. (The string is preceded by a
   long integer containing its length and probably padded up to word
   boundary or longword boundary, depending on the argument padbytes.)
   The arguments countnul should be TRUE if the NUL byte at the end of
   the string should be counted. */

int CatPuts ( FILE * fp, char *str, int padbytes, int countnul, int lenbytes )
{
    unsigned long   reallen, virtuallen, chunklen, swapped_long;
    int             bytesread;
    char           *oldstr;
    char            bytes[10];

/* Get length of string */

    oldstr = str;
    reallen = 0;

    while ( *oldstr )
    {
        bytesread = ReadChar ( &oldstr, bytes );
        if ( bytesread == 2 )
        {
            bytesread--;
        }
        reallen += bytesread;
    }

    virtuallen = chunklen = reallen + lenbytes;
    if ( countnul || chunklen % padbytes == 0 )
    {
        virtuallen++;
    }

    swapped_long = SwapLong ( virtuallen );

    fwrite ( &swapped_long, sizeof ( virtuallen ), 1, fp );
    if ( lenbytes )
    {
        fwrite ( ( ( char * )&reallen ) + sizeof ( reallen ) - lenbytes,
                 lenbytes, 1, fp );
    }

    while ( *str )
    {
        bytesread = ReadChar ( &str, bytes );
        if ( bytesread )
        {
            fwrite ( bytes + bytesread - 1, 1, 1, fp );
        }
    }

    do
    {
        putc ( '\0', fp );
    }
    while ( ++chunklen % padbytes );

    return ( ( int )chunklen + 4 );
}

//|

/// FUNC: PutCatalogChunk

/* This puts a string chunk into the catalog */

int PutCatalogChunk ( FILE * fp, struct CatalogChunk *cc )
{
    fwrite ( &cc->ID, sizeof ( cc->ID ), 1, fp );
    return ( 4 + CatPuts ( fp, cc->ChunkStr, 2, TRUE, 0 ) );
}

//|

/// FUNC: CreateCatalog

/* This creates a catalog */

void CreateCat ( char *CatFile )
{
    FILE           *fp;
    int             CatLen, HeadLen;
    struct CatString *cs;
    struct CatalogChunk *cc;
    int             i;

    if ( !CatVersionString && !CatRcsId )
    {
        ShowError ( MSG_ERR_NoCTVersion );
    }

    if ( !CatLanguage )
    {
        ShowError ( MSG_ERR_NoCTLanguage );
    }

    if ( strlen ( CatLanguage ) == 0 )
    {
        ShowError ( MSG_ERR_NoCTLanguage );
    }

    if ( CatFile == NULL )
    {
        if ( BaseName == NULL )
            ShowError ( MSG_NoCatFileName );
        else
        {
            CatFile = malloc ( strlen ( BaseName ) + 10 );
            sprintf ( CatFile, "%s.catalog", BaseName );
        }
    }

    if ( !( fp = fopen ( CatFile, "w" ) ) )
    {
        ShowError ( MSG_ERR_NoCatalog, CatFile );
    }

    if ( !NoBufferedIO )
        setvbuf ( fp, NULL, _IOFBF, buffer_size );

    fputs ( "FORM0000CTLG", fp );
    CatLen = 4;

    if ( CatVersionString )
    {
        struct CatalogChunk cc;
        char           *verStr;
        char           *found, *found1, *found2;

        cc.ID = MAKE_ID ( 'F', 'V', 'E', 'R' );

        cc.ChunkStr = strdup ( CatVersionString );

    // Replace $TODAY placeholder

        found = strstr ( cc.ChunkStr, "$TODAY" );
        if ( found )
        {
            if ( ( verStr =
                   malloc ( strlen ( cc.ChunkStr ) + 128 ) ) != NULL )
            {
                char            dateStr[10];

                long            tim;
                struct tm      *t;

                time ( &tim );
                t = localtime ( &tim );

                *found = 0;
                strftime ( dateStr, sizeof ( dateStr ), "%d.%m.%y", t );

                sprintf ( verStr, "%s%s%s", cc.ChunkStr, dateStr,
                          found + strlen ( "$TODAY" ) );
                free ( cc.ChunkStr );
                cc.ChunkStr = verStr;
            }
            else
                MemError (  );
        }
        else
        {

        // If a date exists in the string, then update it?

            found1 = strstr ( cc.ChunkStr, " (" );
            if ( found1 && found1[1] == '(' && isdigit ( found1[2] ) )
            {
                found2 = strstr ( found1, ")" );
                if ( found2 )
                {
                    if ( !NoAutoDate )
                    {
                        if ( ( verStr =
                               malloc ( strlen ( cc.ChunkStr ) + 128 ) ) !=
                             NULL )
                        {
                            char            dateStr[10];

                            long            tim;
                            struct tm      *t;

                            time ( &tim );
                            t = localtime ( &tim );

                            found1[2] = 0;
                            strftime ( dateStr, sizeof ( dateStr ),
                                       "%d.%m.%y", t );

                            sprintf ( verStr, "%s%s%s", cc.ChunkStr, dateStr,
                                      found2 );
                            free ( cc.ChunkStr );
                            cc.ChunkStr = verStr;
                        }
                        else
                            MemError (  );
                    }
                }
            }
        }

    // Replace ".ct" with ".catalog"

        found = strstr ( cc.ChunkStr, ".ct " );
        if ( found )
        {
            if ( ( verStr =
                   malloc ( strlen ( cc.ChunkStr ) + 128 ) ) != NULL )
            {
                *found = 0;
                sprintf ( verStr, "%s.catalog%s", cc.ChunkStr, found + 3 );
                free ( cc.ChunkStr );
                cc.ChunkStr = verStr;
            }
        }

        cc.ID = SwapLong ( cc.ID );
        CatLen += PutCatalogChunk ( fp, &cc );
        free ( cc.ChunkStr );
    }
    else
    {
        struct CatalogChunk cc;
        char           *verStr;
        int             year = 0, month = 0, day = 0;
        int             version = 0, revision = 0;
        char           *name = NULL;
        char           *ptr;

        if ( !CatRcsId )
        {
            ShowError ( MSG_ERR_NoCTVersion );
        }
        else
        {
            if ( !( ptr = strstr ( CatRcsId, "$Date:" ) )
                 || sscanf ( ptr + 6, " %d/%d/%d", &year, &month, &day ) != 3
                 || !( ptr = strstr ( CatRcsId, "$Revision:" ) )
                 || sscanf ( ptr + 10, " %d.%d", &version, &revision ) != 2 )
            {
                ShowError ( MSG_WARN_WrongRcsId );
            }
            if ( ( ptr = strstr ( CatRcsId, "$Id:" ) ) )
            {
                int             len = 0;
                char           *found;

                ptr += 4;
                OverSpace ( &ptr );
                found = ptr;

                while ( *ptr && *ptr != '$' && *ptr != ' ' && *ptr != '\t' )
                {
                    ++len;
                    ++ptr;
                }
                if ( !( name = malloc ( len + 1 ) ) )
                {
                    MemError (  );
                }
                strncpy ( name, found, len );
                name[len] = '\0';
            }
        }

        if ( CatName )
        {
            name = CatName;
        }
        else if ( !name )
        {
            ShowError ( MSG_ERR_NoCTVersion );
            name = "";
        }
        if ( !( verStr = malloc ( strlen ( name ) + 256 ) ) )
        {
            MemError (  );
        }

        sprintf ( verStr, "$V" );
        sprintf ( verStr, "ER: %s %d.%d (%d.%d.%d)", name,
                  version, revision, day, month, year );

        cc.ID = MAKE_ID ( 'F', 'V', 'E', 'R' );
        cc.ID = SwapLong ( cc.ID );
        cc.ChunkStr = verStr;
        CatLen += PutCatalogChunk ( fp, &cc );
    }

    for ( cc = FirstChunk; cc != NULL; cc = cc->Next )
    {
        CatLen += PutCatalogChunk ( fp, cc );
    }

    i = 32;
    fputs ( "CSET", fp );

    {
        int             i_tmp = SwapLong ( i );

        fwrite ( &i_tmp, sizeof ( i_tmp ), 1, fp );
        i_tmp = SwapLong ( CodeSet );
        fwrite ( &i_tmp, sizeof ( i_tmp ), 1, fp );
        i -= sizeof ( i_tmp );
    }

    while ( i-- > 0 )
    {
        putc ( '\0', fp );
    }

    CatLen += 48;
    fprintf ( fp, "STRS0000" );
    HeadLen = CatLen;

    for ( cs = FirstCatString; cs != NULL; cs = cs->Next )
    {
        int             FillUsed = FALSE;
        int             tmp_ID = SwapLong ( cs->ID );

        if ( Fill )
        {

            if ( cs->CT_Str )
            {
                if ( strlen ( cs->CT_Str ) == 0 )
                {
                    fwrite ( &tmp_ID, sizeof ( tmp_ID ), 1, fp );
                    CatLen +=
                        4 + CatPuts ( fp, cs->CD_Str, 4, FALSE,
                                      cs->LenBytes );
                    FillUsed = TRUE;
                }
            }
            else
            {
                fwrite ( &tmp_ID, sizeof ( cs->ID ), 1, fp );
                CatLen +=
                    4 + CatPuts ( fp, cs->CD_Str, 4, FALSE, cs->LenBytes );
                FillUsed = TRUE;
            }
        }

        if ( ( !FillUsed ) && cs->CT_Str &&
             ( NoOptim ? TRUE : strcmp ( cs->CT_Str, cs->CD_Str ) ) )
        {
            fwrite ( &tmp_ID, sizeof ( tmp_ID ), 1, fp );
            CatLen += 4 + CatPuts ( fp, cs->CT_Str, 4, FALSE, cs->LenBytes );
        }

    //printf("LB=%d\n", cs->LenBytes);

    }
    {
        int             tmp_Len;

        fseek ( fp, 4, SEEK_SET );

        tmp_Len = SwapLong ( CatLen );
        fwrite ( &tmp_Len, sizeof ( tmp_Len ), 1, fp );
        fseek ( fp, HeadLen - 4, SEEK_CUR );

        CatLen -= HeadLen;
        tmp_Len = SwapLong ( CatLen );
        fwrite ( &tmp_Len, sizeof ( CatLen ), 1, fp );
    }

    fclose ( fp );
#ifdef __amigados
    SetProtection ( CatFile, FILE_MASK );
#endif
    Expunge (  );
}

//|
