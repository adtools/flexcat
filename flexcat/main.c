
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
 ******************************************************************
 ** If you use GoldED or any other text editor featuring folding **
 ** you may want to set up "///" as fold opening phrase, and     **
 ** "//|" as closing one, as this source is using it.            **
 **                                                Marcin        **
 ******************************************************************
 */

#include "flexcat.h"
#include "flexcat_cat.h"
#include "readprefs.h"
#include "showfuncs.h"
#include "swapfuncs.h"
#include "scanct.h"
#include "scancd.h"
#include "createcat.h"
#include "createct.h"
#include "utils.h"
#include "globals.h"
#include "createcatsrc.h"

/// FUNC: main

/* Finally the main function. Does nothing special except for scanning
	the arguments. */
int main ( int argc, char *argv[] )
{
    char           *cdfile, *ctfile, *newctfile, *catalog;
    char           *source, *template, makenewct = FALSE, makecatalog = FALSE;
    int             i;

    if ( argc == 0 )            // Aztec's entry point for workbench programs
    {
        fprintf ( stderr, "FlexCat can't be run from Workbench!\n\n" );
        fprintf ( stderr, "Open a Shell session and type FlexCat ?\n" );
        fprintf ( stderr, "for more information\n" );
        exit ( 5 );
    }

    cdfile = ctfile = newctfile = catalog = NULL;

    OpenFlexCatCatalog (  );

// Big Endian vs Little Endian (both supported ;-)
    if ( !SwapChoose (  ) )
    {
        fprintf ( stderr, "FlexCat is unable to determine the\n" );
        fprintf ( stderr, "the byte order used by your system.\n" );
        fprintf ( stderr, "It's neither Little nor Big Endian?!.\n" );
        exit ( 5 );
    }
#ifdef __amigados
    ReadPrefs (  );
#endif

    if ( argc == 1 )
    {
        Usage (  );
    }

    for ( i = 1; i < argc; i++ )
    {
        if ( strnicmp ( argv[i], "catalog=", 8 ) == 0 )
        {
            catalog = argv[i] + 8;
            makecatalog = TRUE;
        }
        else if ( stricmp ( argv[i], "catalog" ) == 0 )
        {
            catalog = NULL;
            makecatalog = TRUE;
        }
        else if ( stricmp ( argv[i], "nooptim" ) == 0 )
        {
            NoOptim = TRUE;
        }
        else if ( stricmp ( argv[i], "fill" ) == 0 )
        {
            Fill = TRUE;
        }
        else if ( stricmp ( argv[i], "quiet" ) == 0 )
        {
            Quiet = TRUE;
        }
        else if ( stricmp ( argv[i], "flush" ) == 0 )
        {
            DoExpunge = TRUE;
        }
        else if ( stricmp ( argv[i], "nobeep" ) == 0 )
        {
            NoBeep = TRUE;
        }
        else if ( stricmp ( argv[i], "nobufferedio" ) == 0 )
        {
            NoBufferedIO = TRUE;
        }
        else if ( strnicmp ( argv[i], "newctfile=", 10 ) == 0 )
        {
            newctfile = argv[i] + 10;
            makenewct = TRUE;
        }
        else if ( strnicmp ( argv[i], "newctfile", 10 ) == 0 )
        {
            newctfile = NULL;
            makenewct = TRUE;
        }
        else if ( stricmp ( argv[i], "nolangtolower" ) == 0 )
        {
            LANGToLower = FALSE;
        }
        else if ( stricmp ( argv[i], "modified" ) == 0 )
        {
            Modified = TRUE;
        }
        else if ( stricmp ( argv[i], "warnctgaps" ) == 0 )
        {
            WarnCTGaps = TRUE;
        }
        else if ( stricmp ( argv[i], "copymsgnew" ) == 0 )
        {
            CopyNEWs = TRUE;
        }
        else if ( stricmp ( argv[i], "nospace" ) == 0 )
        {
            NoSpace = TRUE;
        }
        else if ( stricmp ( argv[i], "noautodate" ) == 0 )
        {
            NoAutoDate = TRUE;
        }
        else if ( stricmp ( argv[i], "oldmsgnew" ) == 0 )
        {
            sprintf ( Old_Msg_New, "; %s", argv[++i] );
        }
        else if ( cdfile == NULL )
        {
            if ( stricmp ( argv[i], "?" ) == 0 ||
                 stricmp ( argv[i], "-h" ) == 0 ||
                 stricmp ( argv[i], "help" ) == 0 ||
                 stricmp ( argv[i], "--help" ) == 0 )
            {
                Usage (  );
            }
            if ( !ScanCDFile ( cdfile = argv[i] ) )
            {
                MyExit ( 10 );
            }
        }
        else if ( strchr ( argv[i], '=' ) )
        {
            source = ( char * )AllocString ( argv[i] );
            *( template = strchr ( source, '=' ) ) = '\0';
            ++template;

            CreateSourceFile ( source, template, cdfile );
        }
        else
        {
            if ( ctfile )
            {
                Usage (  );
            }
            ctfile = argv[i];
        }
    }

#ifdef __amigados
    if ( Modified )
    {
        if ( cdfile && ctfile && catalog )
        {
            long            cd_time, ct_time, cat_time;

            if ( ( cd_time = getft ( cdfile ) ) != -1 )
            {
                if ( ( ct_time = getft ( ctfile ) ) != -1 )
                {
                    if ( ( cat_time = getft ( catalog ) ) == -1 )
                        cat_time = 0;

                    if ( ( cat_time > ct_time ) && ( cat_time > cd_time ) )
                    {
                        if ( !Quiet )
                        {
                            fprintf ( stderr, ( char * )msgUpToDate,
                                      catalog );
                            putc ( '\n', stderr );
                        }

                        MyExit ( GlobalReturnCode );
                    }
                    else
                    {
                        if ( !Quiet )
                        {
                            fprintf ( stderr, "--> %s", catalog );
                            putc ( '\n', stderr );
                        }
                    }
                }
                else
                {
                    ShowError ( msgCantCheckDate, ctfile );
                }
            }
            else
            {
                ShowError ( msgCantCheckDate, cdfile );
            }
        }
    }
#endif

    if ( ctfile )
    {
        if ( !ScanCTFile ( ctfile ) )
            MyExit ( 10 );
    }

    if ( makecatalog == TRUE )
    {
        if ( !ctfile )
        {
            fprintf ( stderr, ( char * )msgNoCTArgument );
            Usage (  );
        }
        CreateCat ( catalog );
    }

    if ( makenewct == TRUE )
    {
        CreateCTFile ( newctfile );
    }
    MyExit ( GlobalReturnCode );
}

//|
