
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
#include "swapfuncs.h"
#include "showfuncs.h"
#include "scancd.h"
#include "scanct.h"
#include "createcat.h"
#include "globals.h"
#include "utils.h"

enum StringTypes
{
    TYPE_C,                     /* Produce C strings */
    TYPE_ASSEMBLER,             /* Produce Assembler strings */
    TYPE_OBERON,                /* Produce Oberon strings */
    TYPE_E,                     /* Produce E strings. (Oops, thought
                                   it allows only 32 bit integers? ;-) */
    TYPE_NONE                   /* Simple strings */
};

enum OutputModes
{
    OutputMode_None,            /* Nothing written yet */
    OutputMode_Bin,             /* Last character written was binary */
    OutputMode_Ascii            /* Last character written was Ascii */
};

int             OutputMode = OutputMode_None;
int             OutputType = TYPE_C;

FILE           *OutputFile;
int             OutputLen;
int             LongStrings = TRUE;     /* Generate long or short strings */


/// FUNC: CalcRealLength

/* This function measures the real (binary) length of source
   string. It correctly process 'slash chars' (\n, \000 etc),
   and gives the real length such source string have.

   Inputs: source - pointer to NULL terminated source string
   Result: real length */

int CalcRealLength ( char *source )
{
    int             count = 0;
    char           *src = source;
    char            bytes[10];

    while ( *src )

    {
        count += ReadChar ( &src, bytes );

    }

// printf("%ld: '%s'\n", count, source);
    return ( count );

}


//|

/// FUNC: InitCatStringOutput

/* InitCatStringOutput gets called before writing a catalog string as source.
   Inputs: fp   = file pointer to the output file
   type = one of TYPE_C          create C strings
                 TYPE_ASSEMBLER  create Assembler strings
                 TYPE_OBERON     create Oberon strings
                 TYPE_E          create E strings
                 TYPE_NONE       create simple strings */

void InitCatStringOutput ( FILE * fp )
{
    OutputLen = 0;
    OutputFile = fp;
    OutputMode = OutputMode_None;
    switch ( OutputType )

    {
        case TYPE_C:
        case TYPE_OBERON:
            putc ( '\"', fp );
            OutputMode = OutputMode_Ascii;
            break;
        case TYPE_E:
            putc ( '\'', fp );
        case TYPE_ASSEMBLER:
        case TYPE_NONE:
            break;

    }

}


//|

/// FUNC: SeparateCatStringOutput

/* SeparateCatStringOutput gets called to split a catalog into
   separate lines. */

void SeparateCatStringOutput ( void )
{
    switch ( OutputType )

    {
        case TYPE_C:
            if ( !LongStrings )

            {
                fputs ( "\"\\\n\t\"", OutputFile );

            }
            break;
        case TYPE_E:
            if ( !LongStrings )

            {
                fputs ( "\' +\n\t\'", OutputFile );

            }
            break;
        case TYPE_OBERON:
            if ( !LongStrings )

            {
                fputs ( "\"\n\t\"", OutputFile );

            }
            break;
        case TYPE_ASSEMBLER:
            if ( !LongStrings )

            {
                if ( OutputMode == OutputMode_Ascii )

                {
                    putc ( '\'', OutputFile );

                }
                putc ( '\n', OutputFile );
                OutputMode = OutputMode_None;

            }
            break;
        case TYPE_NONE:
            break;

    }

}


//|

/// FUNC: WriteBinChar

/* WriteBinChar writes one binary character into the source file. */

void WriteBinChar ( int c )
{
    switch ( OutputType )

    {
        case TYPE_C:
        case TYPE_E:
        case TYPE_OBERON:
            switch ( c )

            {
                case '\b':
                    fputs ( "\\b", OutputFile );
                    break;
                case '\n':
                    fputs ( "\\n", OutputFile );
                    break;
                case '\r':
                    fputs ( "\\r", OutputFile );
                    break;
                case '\t':
                    fputs ( "\\t", OutputFile );
                    break;
                case '\f':
                    fputs ( "\\f", OutputFile );
                    break;
                case '\0':
                    fputs ( "\\000", OutputFile );
                    break;
                default:
                    if ( OutputType == TYPE_E && c == '\033' )

                    {
                        fputs ( "\\e", OutputFile );

                    }

                    else
                    {
                        fprintf ( OutputFile, "\\%c%c%c",
                                  ( ( c >> 6 ) & 3 ) + '0',
                                  ( ( c >> 3 ) & 7 ) + '0', ( c & 7 ) + '0' );

                    }
                    break;

            }
            ++OutputLen;
            OutputMode = OutputMode_Bin;
            break;
        case TYPE_ASSEMBLER:
            switch ( OutputMode )

            {
                case OutputMode_None:
                    fprintf ( OutputFile, "\tdc.b\t$%02x", c & 0xff );
                    break;
                case OutputMode_Ascii:
                    putc ( '\'', OutputFile );
                case OutputMode_Bin:
                    fprintf ( OutputFile, ",$%02x", c & 0xff );
                    break;

            }
            ++OutputLen;
            OutputMode = OutputMode_Bin;
            break;
        case TYPE_NONE:
            ShowWarn ( MSG_WARN_NoBinChars );
            break;

    }

}


//|

/// FUNC: WriteAsciiChar

/* WriteAsciiChar writes one ascii character into the source file. */

void WriteAsciiChar ( int c )
{
    switch ( OutputType )

    {
        case TYPE_C:
        case TYPE_OBERON:
            switch ( c )

            {
                case '\"':
                    fputs ( "\\\"", OutputFile );
                    break;
                default:
                    putc ( c, OutputFile );
                    break;

            }
            ++OutputLen;
            OutputMode = OutputMode_Ascii;
            break;
        case TYPE_E:
            switch ( c )

            {
                case '\'':
                    fputs ( "''", OutputFile );
                    break;
                default:
                    putc ( c, OutputFile );
                    break;

            }
            ++OutputLen;
            OutputMode = OutputMode_Ascii;
            break;
        case TYPE_ASSEMBLER:
            if ( c == '\'' )

            {
                WriteBinChar ( c );

            }

            else
            {
                switch ( OutputMode )

                {
                    case OutputMode_None:
                        fprintf ( OutputFile, "\tdc.b\t\'%c", c );
                        break;
                    case OutputMode_Ascii:
                        putc ( c, OutputFile );
                        break;
                    case OutputMode_Bin:
                        fprintf ( OutputFile, ",\'%c", c );
                        break;

                }
                ++OutputLen;
                OutputMode = OutputMode_Ascii;

            }
            break;
        case TYPE_NONE:
            putc ( c, OutputFile );
            break;

    }

}


//|

/// FUNC: TerminateCatStringOutput

/* TerminateCatStringOutput finishes the output of a catalog string. */

void TerminateCatStringOutput ( void )
{
    switch ( OutputType )

    {
        case TYPE_C:
        case TYPE_OBERON:
            putc ( '\"', OutputFile );
            break;
        case TYPE_E:
            putc ( '\'', OutputFile );
            break;
        case TYPE_ASSEMBLER:
            switch ( OutputMode )

            {
                case OutputMode_Ascii:
                    putc ( '\'', OutputFile );
                case OutputMode_Bin:
                    break;
                case OutputMode_None:
                    break;

            }
        case TYPE_NONE:
            break;

    }

}


//|

/// FUNC: WriteString

/* This writes a source string. */

void WriteString ( FILE * fpout, char *str, long Len, int lenbytes )
{
    char            bytes[10];
    int             bytesread;
    int             needseparate = FALSE;

    InitCatStringOutput ( fpout );
    if ( Len >= 0 )

    {
        register int    i;

        for ( i = lenbytes; i >= 1; i-- )

        {
            WriteBinChar ( ( int )( ( char * )&Len )[sizeof ( Len ) - i] );

        }

    }
    while ( *str )

    {
        bytesread = ReadChar ( &str, bytes );
        if ( bytesread )

        {
            unsigned char   c;

            if ( needseparate )

            {
                SeparateCatStringOutput (  );
                needseparate = FALSE;

            }
            c = bytes[bytesread - 1];
            if ( ( c >= 0x20 && c < 0x7f ) || c >= 0xa0 )

            {
                WriteAsciiChar ( ( int )c );

            }

            else
            {
                WriteBinChar ( ( int )c );

            }

        }

        else
        {
            needseparate = TRUE;

        }

    }
    TerminateCatStringOutput (  );

}


//|

/// FUNC: CreateSourceFile

/* Finally, the source creation. */

void CreateSourceFile ( char *SourceFile, char *TemplateFile, char *CDFile )
{
    FILE           *fpin, *fpout;
    char           *line;
    char           *OrigTemplateFile = TemplateFile;

    ScanFile = SourceFile;
    ScanLine = 0;

    // Open the source file. This may be found in various places.

    if ( !( fpin = fopen ( TemplateFile, "r" ) ) )

    {

#ifdef __amigados
        if ( *prefs_sddir != 0 )

        {
            TemplateFile = AddFileName ( prefs_sddir, OrigTemplateFile );
            fpin = fopen ( TemplateFile, "r" );

        }

#endif
    }
    if ( !fpin )
    {
#ifdef __amigados
        char            sddir[80];

        if ( GetVar ( FLEXCAT_SDDIR, sddir, 80, NULL ) != 0 )
#else
        char           *sddir;

        if ( ( sddir = getenv ( FLEXCAT_SDDIR ) ) != NULL )
#endif
        {
            TemplateFile = AddFileName ( sddir, OrigTemplateFile );
            fpin = fopen ( TemplateFile, "r" );

        }

    }
    if ( !fpin )

    {
        TemplateFile =
            AddFileName ( DEFAULT_FLEXCAT_SDDIR, OrigTemplateFile );
        fpin = fopen ( TemplateFile, "r" );

    }
    if ( !fpin )

    {
        ShowError ( MSG_ERR_NoSourceDescription, OrigTemplateFile );
        return;

    }
    if ( !( fpout = fopen ( SourceFile, "w" ) ) )

    {
        ShowError ( MSG_ERR_NoSource, SourceFile );
        return;

    }
    if ( !NoBufferedIO )
        setvbuf ( fpin, NULL, _IOFBF, buffer_size );
    if ( !NoBufferedIO )
        setvbuf ( fpout, NULL, _IOFBF, buffer_size );
    while ( !feof ( fpin ) && ( line = ReadLine ( fpin, FALSE ) ) )

    {
        struct CatString *cs;
        int             NeedRepeat;
        char            bytes[10];
        int             bytesread;

        cs = FirstCatString;

        do

        {
            char           *currentline = line;

            NeedRepeat = FALSE;
            if ( *currentline == '#' && *( ++currentline ) == '#' )

            {
                ++currentline;
                OverSpace ( &currentline );
                if ( Strnicmp ( currentline, "rem", 3 ) == 0 )

                {

                // We just skip this line.
                    continue;

                }
                if ( Strnicmp ( currentline, "stringtype", 10 ) == 0 )

                {
                    currentline += 10;
                    OverSpace ( &currentline );
                    if ( Strnicmp ( currentline, "c", 1 ) == 0 )

                    {
                        OutputType = TYPE_C;
                        ++currentline;

                    }

                    else if ( Strnicmp ( currentline, "assembler", 9 ) == 0 )

                    {
                        OutputType = TYPE_ASSEMBLER;
                        currentline += 9;

                    }

                    else if ( Strnicmp ( currentline, "oberon", 6 ) == 0 )

                    {
                        OutputType = TYPE_OBERON;
                        currentline += 6;

                    }

                    else if ( Strnicmp ( currentline, "e", 1 ) == 0 )

                    {
                        OutputType = TYPE_E;
                        ++currentline;

                    }

                    else if ( Strnicmp ( currentline, "none", 4 ) == 0 )

                    {
                        OutputType = TYPE_NONE;
                        currentline += 4;

                    }

                    else
                    {
                        ShowWarn ( MSG_WARN_UnknownStringType );
                        currentline += strlen ( currentline );

                    }
                    OverSpace ( &currentline );
                    if ( *currentline )

                    {
                        ShowWarn ( MSG_WARN_ExtraCharacters );

                    }
                    continue;

                }

                else if ( Strnicmp ( currentline, "shortstrings", 12 ) == 0 )

                {
                    currentline += 12;
                    LongStrings = FALSE;
                    OverSpace ( &currentline );
                    if ( *currentline )

                    {
                        ShowWarn ( MSG_WARN_ExtraCharacters );

                    }
                    continue;

                }

            }
            currentline = line;
            while ( *currentline )

            {
                bytesread = ReadChar ( &currentline, bytes );
                if ( bytesread )

                {
                    if ( *bytes == '%' )

                    {
                        char            c;

                        switch ( c = *( currentline++ ) )

                        {
                            case 'b':
                                fputs ( BaseName, fpout );
                                break;
                            case 'n':
                                fprintf ( fpout, "%d", NumStrings );
                                break;
                            case 'v':
                                fprintf ( fpout, "%d", CatVersion );
                                break;
                            case 'l':
                                WriteString ( fpout, Language, -1,
                                              cs->LenBytes );
                                break;
                            case 'f':

                                {
                                    char           *tempstr;

                                    if ( ( c = *currentline++ ) == 'v' )

                                    {
                                        fputs ( VERS, fpout );

                                    }

                                    else
                                    {
                                        tempstr =
                                            AllocFileName ( CDFile, c - '0' );
                                        fputs ( tempstr, fpout );

                                        free(tempstr);

                                    }

                                }
                                break;
                            case 'o':

                                {
                                    char           *tempstr;

                                    tempstr =
                                        AllocFileName ( SourceFile,
                                                        *currentline++
                                                        - '0' );
                                    fputs ( tempstr, fpout );
                                    
                                    free(tempstr);

                                }
                                break;
                            case 'i':
                                NeedRepeat = TRUE;
                                if ( cs )
                                    fputs ( cs->ID_Str, fpout );
                                break;
                            case 'a':
                            case 't':
                            case 'd':
                            case 'x':
                            case 'c':
                            case '0':
                            case '1':
                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7':
                            case '8':
                            case '9':

                                {
                                    int             len = 0;

                                    while ( c >= '0' && c <= '9' )

                                    {
                                        len = ( c - '0' ) + len * 10;
                                        c = *currentline++;

                                    }
                                    if ( c == 'a' )

                                    {
                                        int             _len = len ? len : 4;
                                        char           *start;
                                        char            _StrLen[20 + 1];

                                        sprintf ( _StrLen, "%020lx",
                                                  ( unsigned long )cs->ID );
                                        start = &_StrLen[20 - _len * 2];
                                        while ( _len > 0 )

                                        {
                                            fprintf ( fpout, "\\x%.2s",
                                                      start );
                                            start += 2;
                                            _len--;

                                        }

                                    }
                                    if ( c == 't' )

                                    {
                                        int             _len = len ? len : 4;
                                        char           *start;
                                        char            _StrLen[20 + 1];

                                        sprintf ( _StrLen, "%020lx",
                                                  ( unsigned
                                                    long )( ( CalcRealLength
                                                              ( cs->CD_Str ) +
                                                              1 ) &
                                                            0xfffffe ) );
                                        start = &_StrLen[20 - _len * 2];
                                        while ( _len > 0 )

                                        {
                                            fprintf ( fpout, "\\x%.2s",
                                                      start );
                                            start += 2;
                                            _len--;

                                        }

                                    }
                                    if ( c == 'c' || c == 'd' || c == 'x' )

                                    {
                                        char            buffer[20];

                                        if ( c == 'c' )
                                            c = 'o';
                                        if ( len )
                                            sprintf ( buffer, "%%0%d%c",
                                                      len, c );

                                        else
                                            sprintf ( buffer, "%%%c", c );
                                        if ( cs )
                                            fprintf ( fpout, buffer, cs->ID );

                                    }
                                    NeedRepeat = TRUE;

                                }
                                break;
                            case 'e':
                                NeedRepeat = TRUE;
                                if ( cs )
                                    fprintf ( fpout, "%d", cs->Nr );
                                break;
                            case 's':
                                NeedRepeat = TRUE;
                                if ( cs )

                                {
                                    char           *idstr;
                                    unsigned long   len = 0;

                                    if ( cs->LenBytes )

                                    {
                                        idstr = cs->CD_Str;
                                        while ( *idstr )

                                        {
                                            bytesread =
                                                ReadChar ( &idstr, bytes );
                                            if ( bytesread )

                                            {
                                                ++len;

                                            }

                                        }

                                    }
                                    WriteString ( fpout, cs->CD_Str,
                                                  cs->LenBytes ? len : -1,
                                                  cs->LenBytes );

                                }
                                break;
                            case '(':
                                NeedRepeat = TRUE;
                                while ( *currentline && *currentline != ')' )

                                {
                                    bytesread =
                                        ReadChar ( &currentline, bytes );
                                    if ( bytesread && cs && cs->Next )

                                    {
                                        putc ( ( int )
                                               bytes[bytesread - 1], fpout );

                                    }

                                }
                                if ( !*currentline )

                                {
                                    ShowWarn ( MSG_WARN_NoTerminateBracket );

                                }

                                else
                                {
                                    ++currentline;

                                }
                                break;

                            // !!!! FIX !!!!
                            case 'z':

                                {
                                    int             diff =
                                        ( ( ( CalcRealLength ( cs->CD_Str ) +
                                              1 ) & 0xfffffe ) -
                                          ( CalcRealLength ( cs->CD_Str ) ) );
                                    NeedRepeat = TRUE;
                                    while ( diff > 0 )

                                    {
                                        fprintf ( fpout, "\\x00" );
                                        diff--;

                                    }
                                    break;

                                }
                            default:

                                {
                                    int             c = *currentline++;

                                    putc ( c, fpout );

                                }

                        }

                    }

                    else
                    {
                        putc ( ( int )bytes[bytesread - 1], fpout );

                    }

                }

            }
            putc ( '\n', fpout );

        }
        while ( NeedRepeat && cs && ( cs = cs->Next ) );
        free ( line );

    }
    fclose ( fpin );
    fclose ( fpout );

#ifdef __amigados
    SetProtection ( SourceFile, FILE_MASK );
#endif
}


//|
