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

extern void     MyExit ( int Code );
extern char    *AllocString ( const char *str );
extern char    *AddCatalogChunk ( char *ID, const char *string );
extern int      gethex ( int c );
extern int      getoctal ( int c );
extern char    *ReadLine ( FILE * fp, int AllowComment );
extern void     OverSpace ( char **strptr );
extern void     Expunge ( void );
extern int      ReadChar ( char **strptr, char *dest );
extern char    *AllocFileName ( char *filename, int howto );
extern char    *AddFileName ( char *pathname, char *filename );
extern void     Usage ( void );
