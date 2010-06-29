
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
#include "readprefs.h"
#include "swapfuncs.h"
#include "showfuncs.h"
#include "scancd.h"
#include "scanct.h"
#include "createcat.h"
#include "globals.h"
#include "utils.h"
#include "openlibs.h"

const char VString[] = VERS " [" SYSTEMSHORT "/" CPU "] (" EXE_DATE ")\n" EXE_COPYRIGHT;
const char EString[] = "Contact: http://sourceforge.net/projects/flexcat/";

/// FUNC: MyExit

void MyExit ( int Code )
{
#ifdef __amigados
    if ( ( ( NumberOfWarnings > 0 ) || ( Code != 0 ) ) && ( !NoBeep ) )
        DisplayBeep ( NULL );

#endif
    CloseFlexCatCatalog (  );
    CloseLibs();
    exit ( Code );
}

///

#ifndef __amigados

/*
 * This array is designed for mapping upper and lower case letters
 * together for a case independent comparison.  The mappings are
 * based upon ascii character sequences.
 */

typedef unsigned char uc;
static const unsigned char charmap[] = {
    ( uc ) '\000', ( uc ) '\001', ( uc ) '\002', ( uc ) '\003', ( uc ) '\004',
        ( uc ) '\005', ( uc ) '\006', ( uc ) '\007',
    ( uc ) '\010', ( uc ) '\011', ( uc ) '\012', ( uc ) '\013', ( uc ) '\014',
        ( uc ) '\015', ( uc ) '\016', ( uc ) '\017',
    ( uc ) '\020', ( uc ) '\021', ( uc ) '\022', ( uc ) '\023', ( uc ) '\024',
        ( uc ) '\025', ( uc ) '\026', ( uc ) '\027',
    ( uc ) '\030', ( uc ) '\031', ( uc ) '\032', ( uc ) '\033', ( uc ) '\034',
        ( uc ) '\035', ( uc ) '\036', ( uc ) '\037',
    ( uc ) '\040', ( uc ) '\041', ( uc ) '\042', ( uc ) '\043', ( uc ) '\044',
        ( uc ) '\045', ( uc ) '\046', ( uc ) '\047',
    ( uc ) '\050', ( uc ) '\051', ( uc ) '\052', ( uc ) '\053', ( uc ) '\054',
        ( uc ) '\055', ( uc ) '\056', ( uc ) '\057',
    ( uc ) '\060', ( uc ) '\061', ( uc ) '\062', ( uc ) '\063', ( uc ) '\064',
        ( uc ) '\065', ( uc ) '\066', ( uc ) '\067',
    ( uc ) '\070', ( uc ) '\071', ( uc ) '\072', ( uc ) '\073', ( uc ) '\074',
        ( uc ) '\075', ( uc ) '\076', ( uc ) '\077',
    ( uc ) '\100', ( uc ) '\141', ( uc ) '\142', ( uc ) '\143', ( uc ) '\144',
        ( uc ) '\145', ( uc ) '\146', ( uc ) '\147',
    ( uc ) '\150', ( uc ) '\151', ( uc ) '\152', ( uc ) '\153', ( uc ) '\154',
        ( uc ) '\155', ( uc ) '\156', ( uc ) '\157',
    ( uc ) '\160', ( uc ) '\161', ( uc ) '\162', ( uc ) '\163', ( uc ) '\164',
        ( uc ) '\165', ( uc ) '\166', ( uc ) '\167',
    ( uc ) '\170', ( uc ) '\171', ( uc ) '\172', ( uc ) '\133', ( uc ) '\134',
        ( uc ) '\135', ( uc ) '\136', ( uc ) '\137',
    ( uc ) '\140', ( uc ) '\141', ( uc ) '\142', ( uc ) '\143', ( uc ) '\144',
        ( uc ) '\145', ( uc ) '\146', ( uc ) '\147',
    ( uc ) '\150', ( uc ) '\151', ( uc ) '\152', ( uc ) '\153', ( uc ) '\154',
        ( uc ) '\155', ( uc ) '\156', ( uc ) '\157',
    ( uc ) '\160', ( uc ) '\161', ( uc ) '\162', ( uc ) '\163', ( uc ) '\164',
        ( uc ) '\165', ( uc ) '\166', ( uc ) '\167',
    ( uc ) '\170', ( uc ) '\171', ( uc ) '\172', ( uc ) '\173', ( uc ) '\174',
        ( uc ) '\175', ( uc ) '\176', ( uc ) '\177',
    ( uc ) '\200', ( uc ) '\201', ( uc ) '\202', ( uc ) '\203', ( uc ) '\204',
        ( uc ) '\205', ( uc ) '\206', ( uc ) '\207',
    ( uc ) '\210', ( uc ) '\211', ( uc ) '\212', ( uc ) '\213', ( uc ) '\214',
        ( uc ) '\215', ( uc ) '\216', ( uc ) '\217',
    ( uc ) '\220', ( uc ) '\221', ( uc ) '\222', ( uc ) '\223', ( uc ) '\224',
        ( uc ) '\225', ( uc ) '\226', ( uc ) '\227',
    ( uc ) '\230', ( uc ) '\231', ( uc ) '\232', ( uc ) '\233', ( uc ) '\234',
        ( uc ) '\235', ( uc ) '\236', ( uc ) '\237',
    ( uc ) '\240', ( uc ) '\241', ( uc ) '\242', ( uc ) '\243', ( uc ) '\244',
        ( uc ) '\245', ( uc ) '\246', ( uc ) '\247',
    ( uc ) '\250', ( uc ) '\251', ( uc ) '\252', ( uc ) '\253', ( uc ) '\254',
        ( uc ) '\255', ( uc ) '\256', ( uc ) '\257',
    ( uc ) '\260', ( uc ) '\261', ( uc ) '\262', ( uc ) '\263', ( uc ) '\264',
        ( uc ) '\265', ( uc ) '\266', ( uc ) '\267',
    ( uc ) '\270', ( uc ) '\271', ( uc ) '\272', ( uc ) '\273', ( uc ) '\274',
        ( uc ) '\275', ( uc ) '\276', ( uc ) '\277',
    ( uc ) '\300', ( uc ) '\341', ( uc ) '\342', ( uc ) '\343', ( uc ) '\344',
        ( uc ) '\345', ( uc ) '\346', ( uc ) '\347',
    ( uc ) '\350', ( uc ) '\351', ( uc ) '\352', ( uc ) '\353', ( uc ) '\354',
        ( uc ) '\355', ( uc ) '\356', ( uc ) '\357',
    ( uc ) '\360', ( uc ) '\361', ( uc ) '\362', ( uc ) '\363', ( uc ) '\364',
        ( uc ) '\365', ( uc ) '\366', ( uc ) '\367',
    ( uc ) '\370', ( uc ) '\371', ( uc ) '\372', ( uc ) '\333', ( uc ) '\334',
        ( uc ) '\335', ( uc ) '\336', ( uc ) '\337',
    ( uc ) '\340', ( uc ) '\341', ( uc ) '\342', ( uc ) '\343', ( uc ) '\344',
        ( uc ) '\345', ( uc ) '\346', ( uc ) '\347',
    ( uc ) '\350', ( uc ) '\351', ( uc ) '\352', ( uc ) '\353', ( uc ) '\354',
        ( uc ) '\355', ( uc ) '\356', ( uc ) '\357',
    ( uc ) '\360', ( uc ) '\361', ( uc ) '\362', ( uc ) '\363', ( uc ) '\364',
        ( uc ) '\365', ( uc ) '\366', ( uc ) '\367',
    ( uc ) '\370', ( uc ) '\371', ( uc ) '\372', ( uc ) '\373', ( uc ) '\374',
        ( uc ) '\375', ( uc ) '\376', ( uc ) '\377',
};

/// FUNC: Stricmp

int Stricmp ( const char *str1, const char *str2 )
{
    register unsigned char u1, u2;

    for ( ;; )
    {
        u1 = ( unsigned char )*str1++;
        u2 = ( unsigned char )*str2++;

        if ( charmap[u1] != charmap[u2] )
        {
            return charmap[u1] - charmap[u2];
        }
        if ( u1 == '\0' )
        {
            return 0;
        }
    }
}

///
/// FUNC: Strnicmp

int Strnicmp ( const char *str1, const char *str2, register int len )
{
    register unsigned char u1, u2;

    for ( ; len != 0; --len )
    {
        u1 = ( unsigned char )*str1++;
        u2 = ( unsigned char )*str2++;
        if ( charmap[u1] != charmap[u2] )
        {
            return charmap[u1] - charmap[u2];
        }
        if ( u1 == '\0' )
        {
            return 0;
        }
    }
    return 0;
}
#endif
///
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

///
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

    /* Put the new chunk at the end of the chunk list. */

    for ( ccptr = &FirstChunk; *ccptr != NULL; ccptr = &( *ccptr )->Next )
    {
    }
    *ccptr = cc;
    return ( cc->ChunkStr );
}

///
/// FUNC: gethex

/* This translates an hex character. */

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
    ShowError ( MSG_ERR_EXPECTEDHEX );
    return ( 0 );
}

///
/// FUNC: getoctal

/* This translates an octal digit. */

int getoctal ( int c )
{

    if ( c >= '0' && c <= '7' )
    {
        return ( c - '0' );
    }

    ShowError ( MSG_ERR_EXPECTEDOCTAL );
    return ( 0 );

}

///
/// FUNC: ReadLine

/* Reading a line is somewhat complicated in order to allow lines of any
   length.

   Inputs: fp - the file, where the input comes from
           AllowComment - TRUE if a leading semicolon should force the
                          line to be interpreted as a comment */

char *ReadLine ( FILE * fp, __attribute__((unused)) int AllowComment )
{

    char           *NewLine = NULL;
    int             c = '\0';
    int             Len = 0, LineLen = 0;
    int             FirstChar = TRUE;
    int             BackslashSeen = FALSE;
    int             BackslashSeenOn = 0;        /* Position where the last backslash was seen. */
    int             CommentLine = FALSE;        /* If TRUE, we should ignore any trailing \'s */

    while ( c != EOF )
    {
        if ( Len + 10 > LineLen )
        {
            NewLine = realloc(NewLine, LineLen + BUFSIZE);
            LineLen += BUFSIZE;
        }

        c = getc ( fp );

        if ( FirstChar )
        {
            if ( c == EOF )
            {
            	if ( NewLine != NULL)
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

            /* Check for trailing \\ */

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

///
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

///
/// FUNC: Expunge

void Expunge(void)
{
#ifdef __amigados
  if(DoExpunge)
  {
    struct Library *localeBase;

    // this may look utterly wrong since we are trying to RemLibrary() a library
    // which we just opened. But this is the most convenient way to invoke the
    // Expunge() function of locale.library, which will just remove any still
    // opened but unused catalog file from memory without removing locale.library
    // itself.
    if((localeBase = OpenLibrary( "locale.library", 0)) != NULL)
    {
      RemLibrary(localeBase);
      CloseLibrary(localeBase);
    }
  }
#endif // __amigados
}

///
/// FUNC: ReadChar

/* ReadChar scans an input line and translates the backslash characters.
   Inputs: char *  - a pointer to a string pointer; the latter points
                     to the next character to be read and points behind
                     the read bytes after executing ReadChar
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

///
/// FUNC: AllocFileName

/* This function creates a copy of a filename, and optionally
   removes an ending and pathname components, if desired.
   Inputs: filename  - the filename to copy
           howto     - a set of bits
                         bit 0: 1 = remove ending, 0 = leave it
                         bit 1: 1 = remove pathname, 0 = leave it
   Result: the copy of the filename
*/

char           *AllocFileName ( char *filename, int howto )
{
    char           *tempstr, *ptr;

    if ( !( tempstr = strdup ( filename ) ) )
    {
        MemError (  );
        MyExit ( 10 );
    }

    /* Remove pathname components, if desired. */

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

///
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

#ifdef __amigados
    strcpy ( buffer, pathname );
    AddPart ( ( char * )buffer, ( char * )filename, size );
#else
    sprintf ( buffer, "%s/%s", pathname, filename );
#endif

    return ( buffer );
}

///
/// FUNC: Usage

/* The Usage function describes the program's calling syntax. */

void Usage ( void )
{
    fprintf ( stderr, "%s\n", VString );
    fprintf ( stderr, "%s\n", EString );
    fprintf ( stderr,
            "\n%s\n         FlexCat CDFILE/A,CTFILE,CATALOG/K,NEWCTFILE/K,SOURCES/M,\n                 WARNCTGAPS/S,NOOPTIM/S,FILL/S,FLUSH/S,NOBEEP/S,\n                 QUIET/S,NOLANGTOLOWER/S,NOBUFFEREDIO/S,MODIFIED/S,\n                 COPYMSGNEW/S,OLDMSGNEW/K\n\n",
            ( char * )MSG_USAGE_HEAD );
    fprintf ( stderr, "%s\n", MSG_USAGE );
    MyExit ( 5 );
}

///
/// FUNC: wbmain

/* Dice's entry point for workbench programs */

#if defined(__amigados)  &&  defined(_DCC)
void wbmain ( struct WBStartup *wbmsg )
{
    fprintf ( stderr, "FlexCat can't be run from Workbench!\n\n" );
    fprintf ( stderr, "Open a shell session and type FlexCat\n" );
    fprintf ( stderr, "for syntax and more information.\n" );

    exit ( 5 );
}
#endif
///

