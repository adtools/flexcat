
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

#include <proto/exec.h>
#include <proto/dos.h>

#ifndef __amigaos4__
# define ZERO NULL
#endif

/// getft

/* Returns the time of change.
   Used for compatibility. */
int32 getft ( char *filename )
{
    BPTR            p_flock;
    int32          timestamp = 0;
    struct FileInfoBlock *p_fib;

    if ( ( p_fib = AllocDosObject ( DOS_FIB, NULL ) ) != NULL )
    {
        if ( ( p_flock = Lock ( filename, ACCESS_READ ) ) != ZERO )
        {
            Examine ( p_flock, p_fib );
            timestamp = p_fib->fib_Date.ds_Days * 86400;                /* days    */
            timestamp += p_fib->fib_Date.ds_Minute * 60;                /* minutes */
            timestamp += p_fib->fib_Date.ds_Tick / TICKS_PER_SECOND;    /* seconds */
            UnLock ( p_flock );
        }
        FreeDosObject ( DOS_FIB, p_fib );
    }

    return timestamp;
}

//|
