#include "flexcat.h"
#include "flexcat_cat.h"
#include "readprefs.h"
#include "swapfuncs.h"
#include "showfuncs.h"
#include "scancd.h"
#include "scanct.h"
#include "createcat.h"
#include "globals.h"

/// FUNC: CreateCTFile

/* This creates a new catalog translation file. */
void CreateCTFile ( char *NewCTFile )
{
    FILE           *fp;
    struct CDLine  *cd;
    struct CatString *cs;
    struct CatalogChunk *cc;
    char           *line;

    if ( !CatVersionString && !CatRcsId )
    {
        ScanLine = 1;
    // ##version,##rcsid,##name are not valid for *.cd-files
    // ShowWarn(msgNoCTVersion);
    }

    if ( !( fp = fopen ( NewCTFile, "w" ) ) )
    {
        ShowError ( msgNoNewCTFile );
    }

    if ( !NoBufferedIO )
        setvbuf ( fp, NULL, _IOFBF, buffer_size );

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
            char            dateStr[10];

            long            tim;
            struct tm      *t;

            time ( &tim );
            t = localtime ( &tim );

            strftime ( dateStr, sizeof ( dateStr ), "%d.%m.%y", t );

            fprintf ( fp, "## version $V" );
            fprintf ( fp, "%c", 50 + 19 );      // E
            if ( CatVersion )
                fprintf ( fp, "R: <name>.ct %d.0 (%s)\n", CatVersion,
                          dateStr );
            else
                fprintf ( fp, "R: <name>.ct <ver>.0 (%s)\n", dateStr );
        }
    }

    {
        if ( CatLanguage == NULL )
        {
#ifdef __amigados
            char            lang[80];

            if ( GetVar ( "language", lang, 80, NULL ) != 0 )
            {
                CatLanguage = lang;
            }
#else
            char           *lang = NULL;

            if ( ( lang = getenv ( "ENV:Language" ) ) != NULL )
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
                CatLanguage = lang;
            }
            if ( lang )
            {
                free ( lang );
                CatLanguage = NULL;
            }

#endif
        }

        fprintf ( fp, "## language %s\n## codeset %d\n;\n",
                  CatLanguage ? CatLanguage : "X", CodeSet );
    }

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
}

//|
