
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

#include "flexcat.h"
#include "showfuncs.h"
#include "readprefs.h"
#include "globals.h"
#include "utils.h"
#include "createcat.h"

char           *CatVersionString = NULL;   /* Version string of catalog
                                              translation (## version) */
char           *CatLanguage = NULL;        /* Language of catalog translation */
char           *CatRcsId = NULL;           /* RCS ID of catalog translation
                                              (## rcsid) */
char           *CatName = NULL;            /* Name of catalog translation */
int             CodeSet = 0;               /* Codeset of catalog translation */
int             CT_Scanned = FALSE;        /* If TRUE and we are going to
                                              write a new #?.ct file, then the
                                              user is surely updating his own
                                              #?.ct file, so we should write
                                              ***NEW*** wherever necessary. */

/// FUNC: ScanCTFile

/* This scans a catalog translation file.
   Inputs: ctfile  - name of the translation file to scan.
   Result: TRUE if successful, FALSE otherwise. */

int ScanCTFile ( char *ctfile )
{
    FILE           *fp;
    char           *newline, *line, *idstr, *newidstr, *newstr;
    struct CatString *cs = NULL;
    int             Result = TRUE;

    ScanFile = ctfile;
    ScanLine = 0;

    if ( !( fp = fopen ( ctfile, "r" ) ) )
    {
        ShowError ( MSG_ERR_NOCATALOGTRANSLATION, ctfile );
    }

    if ( !NoBufferedIO )
        setvbuf ( fp, NULL, _IOFBF, buffer_size );


    while ( !feof ( fp ) && ( line = newline = ReadLine ( fp, TRUE ) ) )
    {
        switch ( *line )
        {
            case ';':
                if ( CopyNEWs == TRUE )
                {
                    if ( Strnicmp
                         ( line, Old_Msg_New, strlen ( Old_Msg_New ) ) == 0 )
                    {
                        cs->NotInCT = TRUE;
                    }
                }
                break;

            case '#':

                /* '#' in the first  column of a line is the command introducer --
                any number of # symbols, blank spaces and tabs afterwards are
                skipped for compatibility with CatComp */

                while ( ( ( *line ) == '#' ) || ( ( *line ) == ' ' ) || ( ( *line ) == '\t' ) )
                {
                    ++line;
                }

                OverSpace ( &line );
                if ( Strnicmp ( line, "version", 7 ) == 0 )
                {
                    if ( CatVersionString || CatRcsId || CatName )
                    {
                        ShowWarn ( MSG_ERR_DOUBLECTVERSION );
                    }
                    line += 7;
                    OverSpace ( &line );
                    CatVersionString = AllocString ( line );
                }
                else if ( Strnicmp ( line, "codeset", 7 ) == 0 )
                {
                    line += 7;
                    CodeSet = strtol ( line, &line, 0 );
                    OverSpace ( &line );
                    if ( *line )
                    {
                        ShowWarn ( MSG_ERR_EXTRACHARACTERS );
                    }
                }
                else if ( Strnicmp ( line, "language", 8 ) == 0 )
                {
                    char           *ptr;

                    if ( CatLanguage )
                    {
                        ShowWarn ( MSG_ERR_DOUBLECTLANGUAGE );
                    }
                    line += 8;
                    OverSpace ( &line );
                    CatLanguage = AddCatalogChunk ( strdup("LANG"), line );

                    if ( LANGToLower )
                        for ( ptr = CatLanguage; *ptr; ptr++ )
                            *ptr = tolower ( ( int )*ptr );
                }
                else if ( Strnicmp ( line, "chunk", 5 ) == 0 )
                {
                    char           *ID;

                    line += 5;
                    OverSpace ( &line );
                    ID = line;
                    line += sizeof ( ULONG );
                    OverSpace ( &line );

                    AddCatalogChunk ( ID, AllocString ( line ) );
                }
                else if ( Strnicmp ( line, "rcsid", 5 ) == 0 )
                {
                    if ( CatVersionString || CatRcsId )
                    {
                        ShowWarn ( MSG_ERR_DOUBLECTVERSION );
                    }
                    line += 5;
                    OverSpace ( &line );
                    CatRcsId = AllocString ( line );
                }
                else if ( Strnicmp ( line, "name", 5 ) == 0 )
                {
                    if ( CatVersionString || CatName )
                    {
                        ShowWarn ( MSG_ERR_DOUBLECTVERSION );
                    }
                    line += 4;
                    OverSpace ( &line );
                    CatName = AllocString ( line );
                }
                else
                {
                    ShowWarn ( MSG_ERR_UNKNOWNCTCOMMAND );
                }

                /* Stop looking for commands */

                break;

            default:
                if ( *line == ' ' || *line == '\t' )
                {
                    ShowWarn ( MSG_ERR_UNEXPECTEDBLANKS );
                    OverSpace ( &line );
                }
                idstr = line;

                while ( ( *line >= 'a' && *line <= 'z' ) ||
                        ( *line >= 'A' && *line <= 'Z' ) ||
                        ( *line >= '0' && *line <= '9' ) || *line == '_' )
                {
                    ++line;
                }
                if ( idstr == line )
                {
                    ShowWarn ( MSG_ERR_NOIDENTIFIER );
                    break;
                }

                if ( !( newidstr = malloc ( line - idstr + 1 ) ) )
                {
                    MemError (  );
                }

                strncpy ( newidstr, idstr, line - idstr );
                newidstr[line - idstr] = '\0';
                OverSpace ( &line );

                if ( *line )
                {
                    ShowWarn ( MSG_ERR_EXTRACHARACTERS );
                }

                if ( ( newstr = ReadLine ( fp, FALSE ) ) )
                {
                    for ( cs = FirstCatString; cs != NULL; cs = cs->Next )
                    {
                        if ( strcmp ( cs->ID_Str, newidstr ) == 0 )
                        {
                            break;
                        }
                    }
                    if ( cs == NULL )
                    {
                        ShowWarn ( MSG_ERR_UNKNOWNIDENTIFIER, newidstr );
                    }
                    else
                    {
                        char           *oldstr;
                        char            bytes[10];
                        int             bytesread, reallen;

                        if ( cs->CT_Str )
                        {
                            ShowWarn ( MSG_ERR_DOUBLEIDENTIFIER );
                            Result = FALSE;
                            free ( cs->CT_Str );
                        }
                        cs->CT_Str = AllocString ( newstr );
                        cs->NotInCT = FALSE;

                        /* Get string length */

                        oldstr = cs->CT_Str;
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

                        if ( cs->MinLen > 0 && reallen < cs->MinLen )
                        {
                            ShowWarn ( MSG_ERR_STRINGTOOSHORT );
                        }
                        if ( cs->MaxLen > 0 && reallen > cs->MaxLen )
                        {
                            ShowWarn ( MSG_ERR_STRINGTOOLONG );
                        }


                        /* Check for trailing ellipsis. */

                        if ( reallen >= 3 )
                        {
                            long            cd_len = strlen ( cs->CD_Str );

                            if ( cd_len >= 3 )
                            {
                                if ( strcmp ( &cs->CD_Str[cd_len - 2], "..." )
                                     == 0 )
                                    if ( strcmp
                                         ( &cs->CT_Str[reallen - 2],
                                           "..." ) != 0 )
                                    {
                                    /* printf("ORG: '%s'\nNEW: '%s'\n", cs->CD_Str, cs->CT_Str); */
                                        ShowWarn ( MSG_ERR_TRAILINGELLIPSIS );
                                    }
                            }
                        }


                        /* Check for trailing spaces. */

                        if ( reallen >= 1 )
                        {
                            long            cd_len = strlen ( cs->CD_Str );

                            if ( cd_len >= 1 )
                            {
                                if ( strcmp ( &cs->CD_Str[cd_len - 1], " " )
                                     == 0 )
                                    if ( strcmp
                                         ( &cs->CT_Str[reallen - 1],
                                           " " ) != 0 )
                                        ShowWarn ( MSG_ERR_TRAILINGBLANKS );
                            }
                        }


                    }
                    free ( newstr );
                }
                else
                {
                    ShowWarn ( MSG_ERR_MISSINGSTRING );
                    if ( cs )
                        cs->CT_Str = (char *)"";
                }
                free ( newidstr );
        }
        free ( newline );
    }

    fclose ( fp );

    if ( WarnCTGaps )
    {
        for ( cs = FirstCatString; cs != NULL; cs = cs->Next )
        {
            if ( cs->CT_Str == NULL )
            {
                ShowWarn ( MSG_ERR_CTGAP, cs->ID_Str );
            }
        }
    }

    if ( Result )
        CT_Scanned = TRUE;

    return ( Result );
}

//|
