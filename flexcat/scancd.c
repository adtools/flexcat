
/* $Id$
 * 
 * Copyright (C) 2002 Ondrej Zima <amiandrew@volny.cz>
 * Copyright (C) 2002 Stefan Kost <ensonic@sonicpulse.de>
 * Copyright (C) 1993 Jochen Wiedmann and Marcin Orlowski <carlos@wfmh.org.pl>
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
#include FLEXCAT_CATALOG_H
#include "showfuncs.h"
#include "readprefs.h"
#include "globals.h"
#include "utils.h"
#include "createcat.h"

struct CDLine  *FirstCDLine = NULL;     /* First catalog description line  */

/// FUNC: ScanCDFile

/* This scans the catalog description file.
   Inputs: cdfile  - name of the catalog description file
   Result: TRUE, if successful, FALSE otherwise */
int ScanCDFile ( char *cdfile )
{
    FILE           *fp;
    struct CDLine  *cdline, **cdptr = &FirstCDLine;
    struct CatString *cs, **csptr = &FirstCatString;
    char           *line, *newline;
    int             NextID = 0;
    int             Result = TRUE;
    int             lenbytes = 0;

    ScanFile = cdfile;
    ScanLine = 0;

    if ( !( fp = fopen ( cdfile, "r" ) ) )
    {
        ShowError ( msgNoCatalogDescription, cdfile );
    }

    if ( !NoBufferedIO )
        setvbuf ( fp, NULL, _IOFBF, buffer_size );

    while ( !feof ( fp ) && ( line = newline = ReadLine ( fp, TRUE ) ) )
    {
        if ( !( cdline = malloc ( sizeof ( *cdline ) ) ) )
        {
            MemError (  );
        }

        *cdptr = cdline;
        cdptr = &cdline->Next;
        cdline->Next = NULL;
        cdline->Line = line = AllocString ( newline );
        free ( newline );

        if ( *line == ';' )
        {
            continue;
        }

        if ( *line == '#' )
        {
            int             CheckExtra = TRUE;

            if ( strnicmp ( line + 1, "language", 8 ) == 0 ||
                 strnicmp ( line + 1, "#language", 9 ) == 0 )
            {
                char           *ptr;

                if ( strnicmp ( line + 1, "language", 8 ) == 0 )
                    line += 9;
                else
                    line += 10;
                OverSpace ( &line );
                Language = AllocString ( line );
                if ( LANGToLower )
                {
                    for ( ptr = Language; *ptr; ptr++ )
                    {
                        *ptr = tolower ( ( int )*ptr );
                    }
                    CheckExtra = FALSE;
                }

            }
            else if ( strnicmp ( line + 1, "version", 7 ) == 0 ||
                      strnicmp ( line + 1, "#version", 8 ) == 0 )
            {
                if ( strnicmp ( line + 1, "#version", 8 ) == 0 )
                    line += 9;
                else
                    line += 8;
                OverSpace ( &line );
                CatVersion = strtol ( line, &line, 0 );
                CheckExtra = TRUE;
            }
            else if ( strnicmp ( line + 1, "basename", 8 ) == 0 ||
                      strnicmp ( line + 1, "#basename", 9 ) == 0 )
            {
                if ( strnicmp ( line + 1, "#basename", 9 ) == 0 )
                    line += 10;
                else
                    line += 9;
                OverSpace ( &line );
                free ( BaseName );
                BaseName = AllocString ( line );
                CheckExtra = FALSE;
            }
            else if ( strnicmp ( line + 1, "ifdef", 5 ) == 0 )
            {
                continue;
            }
            else if ( strnicmp ( line + 1, "endif", 5 ) == 0 )
            {
                continue;
            }
            else if ( strnicmp ( line + 1, "header", 6 ) == 0 )
            {
                continue;
            }
            else if ( strnicmp ( line + 1, "lengthbytes", 11 ) == 0 ||
                      strnicmp ( line + 1, "#lengthbytes", 12 ) == 0 )
            {
                if ( strnicmp ( line + 1, "#lengthbytes", 12 ) == 0 )
                    line += 13;
                else
                    line += 12;
                OverSpace ( &line );
                lenbytes = atoi ( line );
                CheckExtra = FALSE;
            }
            else if ( strnicmp ( line + 1, "#", 1 ) == 0 )
            {
                continue;
            }
            else
            {
                ShowWarn ( msgUnknownCDCommand );
                Result = FALSE;
                CheckExtra = FALSE;
            }

            if ( CheckExtra )
            {
                OverSpace ( &line );
                if ( *line )
                {
                    ShowWarn ( msgExtraCharacters );
                    Result = FALSE;
                }
            }
        }
        else
        {
            char           *idstr;

        // Some blanks on start of line
            if ( *line == ' ' || *line == '\t' )
            {
                ShowWarn ( msgUnexpectedBlanks );
                Result = FALSE;
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
                ShowWarn ( msgNoIdentifier );
                Result = FALSE;
            }
            else
            {
                int             found;

                if ( !( cs = malloc ( sizeof ( *cs ) ) ) )
                {
                    MemError (  );
                }

                do
                {
                    struct CatString *scs;

                    found = TRUE;
                    for ( scs = FirstCatString; scs != NULL; scs = scs->Next )
                    {
                        if ( scs->ID == NextID )
                        {
                            found = FALSE;
                            ++NextID;
                            break;
                        }
                    }
                }
                while ( !found );
                cs->Next = NULL;
                cs->ID = NextID;
                cs->MinLen = 0;
                cs->MaxLen = -1;
                cs->CD_Str = "";
                cs->CT_Str = NULL;
                cs->NotInCT = TRUE;
                if ( !( cs->ID_Str = malloc ( ( line - idstr ) + 1 ) ) )
                {
                    MemError (  );
                }
                strncpy ( cs->ID_Str, idstr, line - idstr );
                cs->ID_Str[line - idstr] = '\0';
                OverSpace ( &line );
            // Next char in line is '('? (//)
                if ( *line != '(' )
                {
                    ShowWarn ( msgNoLeadingBracket );
                    Result = FALSE;
                }
                else
                {
                    char           *oldstr;
                    struct CatString *scs;
                    char            bytes[10];
                    int             bytesread, reallen;

                    ++line;
                    OverSpace ( &line );
                // Check for default config of line (//)
                    if ( *line != '/' )
                    {
                        if ( *line == '+' )
                        {
                            NextID = cs->ID =
                                NextID + strtol ( line, &line, 0 );
                        }
                        else if ( *line == '$' )
                        {
                            line++;
                            cs->ID = NextID = strtol ( line, &line, 16 );
                        }
                        else
                        {
                            cs->ID = NextID = strtol ( line, &line, 0 );
                        }
                        OverSpace ( &line );
                    }

                // Check for already used identifier
                    for ( scs = FirstCatString; scs != NULL; scs = scs->Next )
                    {
                        if ( scs->ID == cs->ID )
                        {
                            ShowWarn ( msgDoubleID );
                            Result = FALSE;
                        }
                        if ( strcmp ( cs->ID_Str, scs->ID_Str ) == 0 )
                        {
                            ShowWarn ( msgDoubleIdentifier );
                            Result = FALSE;
                        }
                    }

                // If line not have a minlen config (//)
                    if ( *line != '/' )
                    {
                        ShowWarn ( msgNoMinLen );
                        Result = FALSE;
                    }
                    else
                    {
                        ++line;
                        OverSpace ( &line );
                        if ( *line != '/' )
                        {
                            cs->MinLen = strtol ( line, &line, 0 );
                            OverSpace ( &line );
                        }
                        if ( *line != '/' )
                        {
                            ShowWarn ( msgNoMaxLen );
                            Result = FALSE;
                        }
                        else
                        {
                            ++line;
                            OverSpace ( &line );
                            if ( *line != ')' )
                            {
                                cs->MaxLen = strtol ( line, &line, 0 );
                                OverSpace ( &line );
                            }
                            if ( *line != ')' )
                            {
                                ShowWarn ( msgNoTrailingBracket );
                                Result = FALSE;
                            }
                            else
                            {
                                ++line;
                                OverSpace ( &line );
                                if ( *line )
                                {
                                    ShowWarn ( msgExtraCharacters );
                                }
                            }
                        }
                    }

                // Huh? There is no string for this definition?
                    if ( !( newline = ReadLine ( fp, FALSE ) ) )
                    {
                        ShowWarn ( msgNoString );
                        Result = FALSE;
                        cs->CD_Str = "";
                    }
                    else
                    {
                        cs->CD_Str = AllocString ( newline );
                        free ( newline );
                    }

                // Get stringlen
                    oldstr = cs->CD_Str;
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

                // Too short string
                    if ( cs->MinLen > 0 && reallen < cs->MinLen )
                    {
                        ShowWarn ( msgShortString );
                    }
                // Too long string
                    if ( cs->MaxLen > 0 && reallen > cs->MaxLen )
                    {
                        ShowWarn ( msgLongString );
                    }

                    cs->Nr = NumStrings;
                    cs->LenBytes = lenbytes;
                    *csptr = cs;
                    csptr = &cs->Next;
                    ++NumStrings;
                }
            }
        }
    }
    fclose ( fp );
    return ( Result );
}

//|
