
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

int     WarnCTGaps = FALSE;                             /* Warn for missing symbols in CT file. */
int     NoOptim = FALSE;                                /* Put string into catalog even
                                                           if translation is equal to
                                                           description. */
int     Fill = FALSE;                                   /* If translation of given string
                                                           is missing or empty, write
                                                           string descriptor from #?.cd
                                                           file instead. */
int     DoExpunge = FALSE;                              /* If TRUE, FlexCat will do an AVAIL
                                                           FLUSH-alike call after saving the catalog. */
int     NoBeep = FALSE;                                 /* If TRUE, FlexCat won't call
                                                           DisplayBeep() any longer. */
int     Quiet = FALSE;                                  /* Forces FlexCat to shut up. */
int     LANGToLower = TRUE;                             /* Shall we do ToLower() on lang's name ?
                                                           Some #?.language drivers seem to be
                                                           broken, so we provide a workaround. */
int     NoBufferedIO = FALSE;                           /* Shall we do buffered I/O ? */
int     Modified = FALSE;                               /* Shall we write the catalog ONLY 
                                                           if #?.catalog is newer than
                                                           #?.c(d|t) files ? */
char    Msg_New[MAX_NEW_STR_LEN] = "***NEW***";         /* New strings in updated #?.ct */
int     CopyNEWs = FALSE;                               /* Shall we write the Msg_New into new strings ? */
char    Old_Msg_New[MAX_NEW_STR_LEN] = "; ***NEW***";   /* Old new string (above) used in old
                                                           CT file. Now we look if it's present
                                                           and copy it into new CT if the user
                                                           upgrades (flexcat CD CT newctfile CT */


char    prefs_sddir[MAXPATHLEN] = "\0";

/// ReadPrefs

/* Fill in options from preferences file. */

char ReadPrefs ( void )
{
    char            result = FALSE;

#ifdef __amigados

#define MAX_PREFS_LEN 512
#define FLEXCAT_PREFS "flexcat.prefs"

    enum
    { SDDIR,
        MSG_NEW,
        WARNCTGAPS,
        NOOPTIM,
        FILL,
        FLUSH,
        NOBEEP,
        QUIET,
        NOLANGTOLOWER,
        NOBUFFEREDIO,
        MODIFIED,
        COPYMSGNEW,
        OLDMSGNEW,
        ARGS_COUNT
    };

    char            template[] =
        "SDDIR/K,MSG_NEW/K,WARNCTGAPS/S,NOOPTIM/S,FILL/S,FLUSH/S,NOBEEP/S,QUIET/S,NOLANGTOLOWER/S,NOBUFFEREDIO/S,MODIFIED/S,COPYMSGNEW/S,OLDMSGNEW/K";
    LONG            Results[ARGS_COUNT] = { 0 };
    char           *prefs;
    struct RDArgs  *rda;
    struct RDArgs  *rdargs;

    if ( ( prefs = malloc ( 2048 ) ) != NULL )
    {
        if ( GetVar ( FLEXCAT_PREFS, prefs, 80, 0 ) != -1 )
        {
            prefs = realloc ( prefs, strlen ( prefs ) + 1 );
            strcat ( prefs, "\n" );

            if ( ( rda = AllocDosObject ( DOS_RDARGS, TAG_DONE ) ) != NULL )
            {
                rda->RDA_Source.CS_Buffer = prefs;
                rda->RDA_Source.CS_Length = strlen ( prefs );
                rda->RDA_Source.CS_CurChr = 0;
                rda->RDA_Flags |= RDAF_NOPROMPT;

                if ( ( rdargs =
                       ReadArgs ( template, Results, rda ) ) != NULL )
                {
                    if ( Results[SDDIR] )
                        strncpy ( prefs_sddir, ( char * )Results[SDDIR],
                                  MAXPATHLEN );

                    if ( Results[MSG_NEW] )
                        strncpy ( Msg_New, ( char * )Results[MSG_NEW],
                                  MAX_NEW_STR_LEN );

                    WarnCTGaps = Results[WARNCTGAPS];
                    NoOptim = Results[NOOPTIM];
                    Fill = Results[FILL];
                    DoExpunge = Results[FLUSH];
                    NoBeep = Results[NOBEEP];
                    Quiet = Results[QUIET];
                    LANGToLower = !Results[NOLANGTOLOWER];
                    Modified = Results[MODIFIED];
                    NoBufferedIO = Results[NOBUFFEREDIO];
                    CopyNEWs = Results[COPYMSGNEW];
                    if ( Results[OLDMSGNEW] )
                        sprintf ( Old_Msg_New, "; %s",
                                  ( char * )Results[OLDMSGNEW] );

                    FreeArgs ( rdargs );

                    result = TRUE;
                }
                else
                {
                    fputs ( ( char * )MSG_PrefsError, stderr );
                    fputs ( ( char * )template, stderr );
                    fputs ( ( char * )"\n", stderr );
                    DisplayBeep ( NULL );
                }
                FreeDosObject ( DOS_RDARGS, rda );
            }
            else
            {
                fputs ( "Error processing prefs.\nCan't AllocDosObject()\n",
                        stderr );
            }
            free ( prefs );
        }
    }
#endif
    return ( result );
}

//|
