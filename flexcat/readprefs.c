
/*
 * FUNC: ReadPrefs
 */

#include "flexcat.h"
#include "flexcat_cat.h"


int             WarnCTGaps = FALSE;     /* Warn missing symbols in CT file. */
int             NoOptim = FALSE;        /*  Put string into catalog even
                                           if translation is equal to
                                           description. */
int             Fill = FALSE;   /* It translation of given string
                                   is missing or it's empty, write
                                   string descriptor from #?.cd
                                   file instead. */
int             DoExpunge = FALSE;      /*  If TRUE FlexCat will do AVAIL
                                           FLUSH alike after catalog save */
int             NoBeep = FALSE; /*  if TRUE, FlexCat won't call
                                   DisplayBeep() any longer */
int             Quiet = FALSE;  /*  Forces FlexCat to shut up */
int             LANGToLower = TRUE;     /* Shall we do ToLower() on lang's 
                                           name? Some #?.language seems to
                                           be broken, so we allow workaround */
int             NoBufferedIO = FALSE;   /* Shall we do buffered ID */
int             Modified = FALSE;       /* Shall we write the catalog ONLY 
                                           if #?.catalog is younger than
                                           #?.c(d|t) files? */
char            Msg_New[MAX_NEW_STR_LEN] = "***NEW***"; /* new strings in updated #?.ct */
int             CopyNEWs = FALSE;       /* Shall we write the Msg_New into new strings? */
char            Old_Msg_New[MAX_NEW_STR_LEN] = "; ***NEW***";   /* old newstring (above) used in old
                                                                   CT file. Now we look if it's present
                                                                   and copy it into new CT if user does
                                                                   upgrade (flexcat CD CT newctfile CT */
int             NoSpace = FALSE;        /* do want to strip the space usually 
                                           placed between ';' and original 
                                           string? */
int             NoAutoDate = FALSE;     /* to catalog date will be written
                                           from translation or current date */

char            prefs_sddir[MAXPATHLEN] = "\0";

/// ReadPrefs

/* Fill in options from preferences file */
char ReadPrefs ( void )
{
    char            result = FALSE;

#if defined(__amigados)

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
        NOSPACE,
        NOAUTODATE,
        ARGS_COUNT
    };

    char            template[] =
        "SDDIR/K,MSG_NEW/K,WARNCTGAPS/S,NOOPTIM/S,FILL/S,FLUSH/S,NOBEEP/S,QUIET/S,NOLANGTOLOWER/S,NOBUFFEREDIO/S,MODIFIED/S,COPYMSGNEW/S,OLDMSGNEW/K,NOSPACE/S,NOAUTODATE/S";
    LONG            Results[ARGS_COUNT] = { 0 };
    char           *prefs;
    struct RDArgs  *rda;
    struct RDArgs  *rdargs;

    if ( ( prefs = getenv ( FLEXCAT_PREFS ) ) != NULL )
    {
        prefs = realloc ( prefs, strlen ( prefs ) + 1 );
        strcat ( prefs, "\n" );

        if ( ( rda = AllocDosObject ( DOS_RDARGS, TAG_DONE ) ) != NULL )
        {
            rda->RDA_Source.CS_Buffer = prefs;
            rda->RDA_Source.CS_Length = strlen ( prefs );
            rda->RDA_Source.CS_CurChr = 0;
            rda->RDA_Flags |= RDAF_NOPROMPT;

            if ( ( rdargs = ReadArgs ( template, Results, rda ) ) != NULL )
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
                LANGToLower = Results[NOLANGTOLOWER];
                Modified = Results[MODIFIED];
                NoBufferedIO = Results[NOBUFFEREDIO];
                CopyNEWs = Results[COPYMSGNEW];
                NoSpace = Results[NOSPACE];
                NoAutoDate = Results[NOAUTODATE];
                if ( Results[OLDMSGNEW] )
                    sprintf ( Old_Msg_New, "; %s",
                              ( char * )Results[OLDMSGNEW] );

                FreeArgs ( rdargs );

                result = TRUE;
            }
            else
            {
                fputs ( ( char * )msgPrefsError, stderr );
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
#endif
    return ( result );
}

//|
