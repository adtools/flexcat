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
#include "flexcat_cat.h"
#include "readprefs.h"
#include "swapfuncs.h"
#include "showfuncs.h"
#include "scancd.h"
#include "scanct.h"
#include "createcat.h"
#include "globals.h"

char            VString[] = VSTRING " by Jochen Wiedmann and Marcin Orlowski";
char            EString[] =
    "E-mail: carlos@amiga.com.pl or marcin@orlowski.com WWW: http://amiga.com.pl/flexcat/";


/// FUNC: MyExit
void MyExit ( int Code )
{
#if defined(__amigados)

    if ( ( ( NumberOfWarnings > 0 ) || ( Code != 0 ) ) && ( !NoBeep ) )
        DisplayBeep ( NULL );

#endif

    CloseFlexCatCatalog (  );
    exit ( Code );
}

//|

/// FUNC: stricmp

/* Amiga implementation of quick stricmp */

#ifndef __amigados
int stricmp ( char *str1, char *str2 )
{
    register int    i;

    for ( i = 0;; i++ )
    {
        int             a = tolower ( ( int )*str1 );
        int             b = tolower ( ( int )*str2 );

        if ( !a || !b )
            break;

        if ( a != b )
            return ( 1 );

        str1++;
        str2++;
    }

    return ( 0 );
}
#endif

//|

/// FUNC: strnicmp

/* Amiga implementation of quick strnicmp */
#ifndef __amigados
int strnicmp ( char *str1, char *str2, int len )
{
    register int    i;

    for ( i = 0; i < len; i++ )
    {
        int             a = tolower ( ( int )*str1 );
        int             b = tolower ( ( int )*str2 );

        if ( !a || !b )
            break;

        if ( a != b )
            return ( 1 );

        str1++;
        str2++;
    }

    return ( 0 );
}
#endif

//|

/// FUNC: AllocString

/* This allocates a string */
char           *AllocString ( const char *str )
{
    char           *ptr;

    if ( !( ptr = malloc ( strlen ( str ) + 1 ) ) )
    {
        MemError (  );
    }
    strcpy ( ptr, str );
    return ( ptr );
}

//|

/// FUNC: Add catalog chunk

/* This adds a new catalog chunk to the list of catalog
   chunks. */
char           *AddCatalogChunk ( char *ID, const char *string )
{
    struct CatalogChunk *cc, **ccptr;

    if ( !( cc = malloc ( sizeof ( *cc ) ) ) )
    {
        MemError (  );
    }
    cc->Next = NULL;
    cc->ID = *( ( ULONG * ) ID );
    cc->ChunkStr = AllocString ( string );

/*
   Put the new chunk to the end of the chunk list. 
 */
    for ( ccptr = &FirstChunk; *ccptr != NULL; ccptr = &( *ccptr )->Next )
    {
    }
    *ccptr = cc;
    return ( cc->ChunkStr );
}

//|

/// FUNC: gethex

/* This translates a hex character. */
int gethex ( int c )
{
    if ( c >= '0' && c <= '9' )
    {
        return ( c - '0' );
    }
    else if ( c >= 'a' && c <= 'f' )
    {
        return ( c - 'a' + 10 );
    }
    else if ( c >= 'A' && c <= 'F' )
    {
        return ( c - 'A' + 10 );
    }
    ShowWarn ( msgExpectedHex );
    return ( 0 );
}

//|

/// FUNC: getoctal

/* This translates an octal digit. */
int getoctal ( int c )
{

    if ( c >= '0' && c <= '7' )
    {
        return ( c - '0' );
    }

    ShowWarn ( msgExpectedOctal );
    return ( 0 );

}

//|

/// FUNC: ReadLine

/* Reading a line is somewhat complicated in order to allow lines of any
   length.
   Inputs: fp           - the file, where the input comes from
		   AllowComment - TRUE, if a leading semicolon should force to
		   			      interpret the line as a comment line */
char           *ReadLine ( FILE * fp, int AllowComment )
{

    char           *OldLine, *NewLine = NULL;
    int             c = '\0';
    int             Len = 0, LineLen = 0;
    int             FirstChar = TRUE;
    int             BackslashSeen = FALSE;
    int             BackslashSeenOn = 0;        /* position the last backslash was seen on */
    int             CommentLine = FALSE;        /* if TRUE we should ignore normally treat trailing \'s */

    while ( c != EOF )
    {
        if ( Len + 10 > LineLen )
        {
            OldLine = NewLine;
            if ( !( NewLine = malloc ( LineLen + BUFSIZE ) ) )
                MemError (  );

            strncpy ( NewLine, OldLine, LineLen );
            if ( OldLine )
                free ( OldLine );

            LineLen += BUFSIZE;
        }

        c = getc ( fp );

        if ( FirstChar )
        {
            if ( c == EOF )
            {
                free ( NewLine );
                return ( NULL );
            }

            if ( c == ';' )
            {
                CommentLine = TRUE;
            }

            FirstChar = FALSE;
        }

        switch ( c )
        {
            case '\r':
                break;

            case '\n':
                ++ScanLine;
                if ( BackslashSeen )
                {
                    NewLine[Len++] = c;
                    BackslashSeen = FALSE;
                    break;
                }
                c = EOF;

            case EOF:
                break;

            /*
               Let's check for trailing \\ 
             */
            case '\\':
                {
                    if ( !CommentLine )
                    {
                        if ( BackslashSeen )
                        {
                            if ( BackslashSeenOn == ( Len - 1 ) )
                            {
                                BackslashSeen = FALSE;
                                NewLine[Len++] = c;
                                break;
                            }
                        }

                        BackslashSeen = TRUE;
                        BackslashSeenOn = Len;
                    }

                    NewLine[Len++] = c;
                    break;
                }


            default:
                BackslashSeen = FALSE;
                NewLine[Len++] = c;
        }
    }

    NewLine[Len] = '\0';

    return ( NewLine );

}

//|

/// FUNC: OverSpace

/* This removes trailing blanks. */
void OverSpace ( char **strptr )
{
    int             c;

    while ( ( c = **strptr ) == ' ' || c == '\t' )
    {
        ( *strptr )++;
    }
}

//|

/// FUNC: Expunge

void Expunge ( void )
{
#if defined(__amigados)


    if ( DoExpunge )
    {
#ifdef __EXPUNGE_ALL__
        APTR            Memory;

        if ( Memory = AllocMem ( -1, NULL ) )
            FreeMem ( Memory, -1 );     // just in case ;-)
#else

#ifdef __GNUC__
#define localeExpunge() \
	((BPTR (*)(struct Library * __asm("a6"))) \
  (((char *) LocaleBase) - 18))((struct Library *) LocaleBase)
#else
#pragma libcall LocaleBase localeExpunge 12 00
        VOID            localeExpunge ( VOID );
#endif
        struct Library *LocaleBase;

        if ( ( LocaleBase = OpenLibrary ( "locale.library", 0 ) ) != NULL )
        {
            localeExpunge (  );
            CloseLibrary ( LocaleBase );
        }

#endif
    }
#endif

}

//|

/// FUNC: ReadChar

/* ReadChar scans an input line translating the backslash characters.
   Inputs: char *  - a pointer to a stringpointer; the latter points to the
					 next character to be read and points behind the read
					 bytes after executing ReadChar
		   dest    - a pointer to a buffer, where the read bytes should be
					 stored
   Result: number of bytes that are written to dest (between 0 and 2) */
int ReadChar ( char **strptr, char *dest )
{
    char            c;
    register int    i;

    switch ( c = *( ( *strptr )++ ) )
    {
        case '\\':

            switch ( c = tolower ( ( int )*( ( *strptr )++ ) ) )
            {
                case '\n':
                    return ( 0 );
                case 'b':
                    *dest = '\b';
                    break;
                case 'c':
                    *dest = '\233';
                    break;
                case 'e':
                    *dest = '\033';
                    break;
                case 'f':
                    *dest = '\f';
                    break;
                case 'g':
                    *dest = '\007';
                    break;
                case 'n':
                    *dest = '\n';
                    break;
                case 'r':
                    *dest = '\r';
                    break;
                case 't':
                    *dest = '\t';
                    break;
                case 'v':
                    *dest = '\013';
                    break;
                case 'x':
                    *dest = gethex ( ( int )**strptr );
                    ( *strptr )++;
                    if ( ( ( c = **strptr ) >= '0' && c <= '9' ) ||
                         ( c >= 'a' && c <= 'f' ) || ( c >= 'A' &&
                                                       c <= 'F' ) )
                    {
                        *dest = ( *dest << 4 ) + gethex ( ( int )c );
                        ( *strptr )++;
                    }
                    break;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':

                    *dest = getoctal ( ( int )c );

                    for ( i = 0; i < 2; i++ )
                    {
                        if ( ( c = **strptr ) >= '0' && c <= '7' )
                        {
                            *dest = ( *dest << 3 ) + getoctal ( ( int )c );
                            ( *strptr )++;
                        }
                    }
                    break;
                case ')':
                case '\\':
                    *( dest++ ) = '\\';
                    *dest = c;
                    return ( 2 );
                default:
                    *dest = c;
            }
            break;

        default:
            *dest = c;
    }
    return ( 1 );
}

//|

/// FUNC: AllocFileName

/* This function creates a copy of a filename, removes an
   optional ending and pathname components, if desired.
   Inputs: filename - the filename to copy
		   howto - a set of bits
				   bit 0: 1 = remove ending, 0 = leave it
				   bit 1: 1 = remove pathname, 0 = leave it
   Result: The copy of the filename
*/
char           *AllocFileName ( char *filename, int howto )
{
    char           *tempstr, *ptr;

    if ( !( tempstr = strdup ( filename ) ) )
    {
        MemError (  );
        MyExit ( 10 );
    }

/*
   Remove pathname components, if desired 
 */
    if ( howto & 2 )
    {
        if ( ( ptr = strchr ( tempstr, ':' ) ) )
        {
            tempstr = ptr + 1;
        }
        if ( ( ptr = strrchr ( tempstr, '/' ) ) )
        {
            tempstr = ptr + 1;
        }
    }

/* Remove ending, if desired. */
    if ( howto & 1 )
    {
        if ( ( ptr = strrchr ( tempstr, '.' ) ) )
        {
            *ptr = '\0';
        }
    }

    return ( tempstr );
}

//|

/// FUNC: AddFileName

/* This function adds a pathname and a filename to a full
   filename.
   Inputs: pathname - the leading pathname
		   filename - the filename
   Result: The new filename */
char           *AddFileName ( char *pathname, char *filename )
{
    char           *buffer;
    int             size = strlen ( pathname ) + strlen ( filename ) + 2;

    if ( !( buffer = malloc ( size ) ) )
    {
        MemError (  );
        MyExit ( 10 );
    }

#if defined(__amigados)
    strcpy ( buffer, pathname );
    AddPart ( ( char * )buffer, ( char * )filename, size );
#else
    sprintf ( buffer, "%s/%s", pathname, filename );
#endif

    return ( buffer );
}

//|


/// FUNC: Usage

/* The Usage function describes the programs calling syntax. */
void Usage ( void )
{
    fprintf ( stderr,
              "%s\n        FlexCat CDFILE/A,CTFILE,CATALOG/K,NEWCTFILE/K,SOURCES/M,\n                WARNCTGAPS/S,NOOPTIM/S,FILL/S,FLUSH/S,NOBEEP/S,\n                QUIET/S,NOLANGTOLOWER/S,NOBUFFEREDIO/S,\n                MODIFIED/S,COPYMSGNEW/S,OLDMSGNEW/K,NOSPACE/S,NOAUTODATE/S\n\n",
              ( char * )msgUsageHead );
    fprintf ( stderr, "%s\n%s\n%s\n", msgUsage_1, msgUsage_2, msgUsage_3 );
    fprintf ( stderr, "%s\n%s\n%s\n", msgUsage_4, msgUsage_5, msgUsage_6 );
    fprintf ( stderr, "%s\n%s\n%s\n", msgUsage_7, msgUsage_8, msgUsage_9 );
    fprintf ( stderr, "%s\n%s\n%s\n", msgUsage_10, msgUsage_11, msgUsage_12 );
    fprintf ( stderr, "%s\n%s\n%s\n", msgUsage_13, msgUsage_14, msgUsage_15 );
    fprintf ( stderr, "%s\n%s\n%s\n", msgUsage_16, msgUsage_17, msgUsage_18 );
    fprintf ( stderr, "\n\n%s\n", VString );
    fprintf ( stderr, "%s\n", EString );
    MyExit ( 5 );
}

//|

/// FUNC: wbmain

/* Dice's entry point for workbench programs */
#if defined(__amigados)  &&  defined(_DCC)
void wbmain ( struct WBStartup *wbmsg )
{
    fprintf ( stderr, "FlexCat can't be run from Workbench!\n\n" );
    fprintf ( stderr, "Open a Shell session and type FlexCat\n" );
    fprintf ( stderr, "for syntax and more information\n" );

    exit ( 5 );
}
#endif
//|
