
/*
 * GetFD
 */

#include <proto/exec.h>
#include <proto/dos.h>
#include <debug.h>

/// getft

/* Returns the time of change.
   Used for compatibility */
long getft ( char *filename )
{
    BPTR            p_flock;
    long            timestamp = 0;
    struct FileInfoBlock *p_fib;

    if ( ( p_fib = AllocDosObject ( DOS_FIB, NULL ) ) != NULL )
    {
        if ( ( p_flock = Lock ( filename, ACCESS_READ ) ) != NULL )
        {
            Examine ( p_flock, p_fib );
            timestamp = p_fib->fib_Date.ds_Days * 86400;        // days
            timestamp += p_fib->fib_Date.ds_Minute * 60;        // minutes
            timestamp += p_fib->fib_Date.ds_Tick / TICKS_PER_SECOND;    // seconds
            DEBUG ( kprintf ( "getft() = %ld\n", timestamp ) );
            UnLock ( p_flock );
        }
        FreeDosObject ( DOS_FIB, p_fib );
    }

    return timestamp;
}

//|
