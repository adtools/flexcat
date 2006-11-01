
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
#include "readprefs.h"
#include "showfuncs.h"
#include "scancd.h"
#include "scanct.h"
#include "createcat.h"
#include "globals.h"

#ifdef __amigados
 #include <proto/locale.h>
#endif

/// FUNC: CreateCTFile

/* This creates a new catalog translation file. */

void CreateCTFile ( char *NewCTFile )
{
    FILE           *fp;
    struct CDLine  *cd;
    struct CatString *cs;
    struct CatalogChunk *cc;
    char           *line;
    char           *ctlanguage = NULL;

    if ( !CatVersionString && !CatRcsId )
    {
        ScanLine = 1;
    // ##version,##rcsid,##name are not valid for *.cd-files
    // ShowWarn(MSG_ERR_NoCTVersion);
    }

    if ( CatLanguage == NULL )
    {
#ifdef __amigados
        char            lang[80];

        if ( GetVar ( "language", lang, 80, 0 ) != 0 )
        {
            ctlanguage = lang;
        }
#else
        char           *lang = NULL;

        if ( ( lang = getenv ( "language" ) ) != NULL )
        {
            register int    i;

            for ( i = 0; i < strlen ( lang ); i++ )
            {
                if ( lang[i] == '\n' )
                {
                    lang[i] = 0;
                    break;
                }
            }
            ctlanguage = lang;
        }
#endif
    }
    else
        ctlanguage = CatLanguage;
        
    if ( ctlanguage == NULL )
        ctlanguage = (char *)"nolanguage";

    if ( NewCTFile == NULL )
    {
        if ( BaseName == NULL )
            ShowError ( MSG_NoCTFileName );
        else
        {
            NewCTFile =
                malloc ( strlen ( BaseName ) + strlen ( ctlanguage ) + 5 );
            sprintf ( NewCTFile, "%s_%s.catalog", BaseName, ctlanguage );
        }
    }
    if ( !( fp = fopen ( NewCTFile, "w" ) ) )
    {
        ShowError ( MSG_ERR_NoNewCTFile );
    }

    if ( !NoBufferedIO )
        setvbuf ( fp, NULL, _IOFBF, buffer_size );

    {
        if ( CatRcsId )
        {
            fprintf ( fp, "## rcsid %s\n", CatRcsId ? CatRcsId : "" );
            if ( CatName )
                fprintf ( fp, "## name %s\n", CatName );
        }
        else
        {
            if ( CatVersionString )
                fprintf ( fp, "## version %s\n", CatVersionString );
            else
            {
                char           *dateStr;
                long            tim;
                struct tm      *t;

                dateStr = calloc ( 15, 1 );
                time ( &tim );
                t = localtime ( &tim );
                strftime ( dateStr, 12, "%d.%m.%Y", t );
                fprintf ( fp, "## version $V" );
                fprintf ( fp, "%c", 50 + 19 );  // E
                if ( CatVersion )
                {
                    if ( BaseName )
                    {
                        fprintf ( fp, "R: %s.catalog %d.<rev> (%s)\n", BaseName,
                                  CatVersion, dateStr );
                    }
                    else
                    {
                        fprintf ( fp, "R: <name>.catalog %d.<rev> (%s)\n", CatVersion,
                                  dateStr );
                    }
                }
                else
                {
                    if ( BaseName )
                    {
                        fprintf ( fp, "R: %s.catalog <ver>.0 (%s)\n", BaseName,
                                  dateStr );
                    }
                    else
                    {
                        fprintf ( fp, "R: <name>.catalog <ver>.0 (%s)\n",
                                  dateStr );
                    }
                }
                free ( dateStr );
            }
        }
    }

#ifdef __amigados
    if ( CodeSet == 0 )
    {
        struct LocaleBase *LocaleBase;
        struct Locale  *my_locale;

        if ( ( LocaleBase =
               ( struct LocaleBase * )OpenLibrary ( "locale.library",
                                                    47L ) ) != NULL )
        {
            if ( ( my_locale = OpenLocale ( NULL ) ) != NULL )
            {
                CodeSet = my_locale->loc_CodeSet;
                CloseLocale ( my_locale );
            }
            CloseLibrary ( ( struct Library * )LocaleBase );
        }
    }
#endif
    fprintf ( fp, "## language %s\n## codeset %d\n;\n",
              ctlanguage ? ctlanguage : "X", CodeSet );
    for ( cc = FirstChunk; cc != NULL; cc = cc->Next )
    {
        if ( cc->ChunkStr != CatLanguage )
        {
            fprintf ( fp, "## chunk " );
            fwrite ( ( char * )&cc->ID, sizeof ( cc->ID ), 1, fp );
            fprintf ( fp, " %s\n", cc->ChunkStr );
        }
    }

    for ( cd = FirstCDLine, cs = FirstCatString; cd != NULL; cd = cd->Next )
    {
        switch ( *cd->Line )
        {
            case '#':
                fprintf ( fp, ";%s\n", cd->Line );
                break;
            case ';':
                fprintf ( fp, "%s\n", cd->Line );
                break;
            default:
                if ( cs )
                {

                /*
                   fprintf(fp, "%s\n", cs->ID_Str);
                   fprintf(fp, "%s\n", cs->CT_Str ? cs->CT_Str : "");
                   putc(';', fp);
                   putc(' ', fp);
                 */
                    fprintf ( fp, "%s\n%s\n;", cs->ID_Str,
                              cs->CT_Str ? cs->CT_Str : "" );
                    if ( !NoSpace )
                        putc ( ' ', fp );
                    for ( line = cs->CD_Str; *line; ++line )
                    {
                        putc ( ( int )*line, fp );
                        if ( *line == '\n' )
                        {
                            putc ( ';', fp );
                            if ( !NoSpace )
                                putc ( ' ', fp );
                        }
                    }
                    putc ( '\n', fp );
                    if ( cs->NotInCT && CT_Scanned )
                        fprintf ( fp, ";\n; %s\n", Msg_New );
                    cs = cs->Next;
                }
        }
    }
    fclose ( fp );
#ifdef __amigados
    SetProtection ( NewCTFile, FILE_MASK );
#endif
}

//|
