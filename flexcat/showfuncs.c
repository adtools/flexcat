#include "flexcat.h"
#include "flexcat_cat.h"
#include "readprefs.h"
#include "globals.h"
#include "utils.h"

/// FUNC: ShowError

/* This shows an error message and terminates */
void ShowError ( const char *msg, ... )
{
    char          **ptr = ( char ** )&msg;

//  if(!Quiet)
    {
        fprintf ( stderr, ptr[0], ptr[1], ptr[2], ptr[3], ptr[4] );
        putc ( '\n', stderr );
    }

#if defined(__amigados)
    NumberOfWarnings++;
#endif

    MyExit ( 10 );
}

//|

/// FUNC: MemError

/* This shows the message: Memory error. */
void MemError ( void )
{
    ShowError ( msgMemoryError, NULL );
}

//|

/// FUNC: ShowWarn

/* This shows a warning */
void ShowWarn ( const char *msg, ... )
{
    char          **ptr = ( char ** )&msg;

    if ( !Quiet )
    {
        fprintf ( stderr, ( char * )msgWarning, ScanFile, ScanLine );
        fprintf ( stderr, ptr[0], ptr[1], ptr[2], ptr[3], ptr[4] );
        putc ( '\n', stderr );
    }

    NumberOfWarnings++;
    GlobalReturnCode = 5;
}

//|
