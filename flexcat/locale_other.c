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

/****************************************************************

   This file provide at least the minimal compatiblity with
   AmigaOS catalog system on other platforms. It creates
   necessary string tables (hardcoded ATM) and functions to
   make code work under any operating system.

   Carlos

****************************************************************/

void OpenFlexCatCatalog( void )
{}
void CloseFlexCatCatalog( void )
{}

char * flexcat_Strings[63] = {
    (char *)"Out of memory!",
    (char *)"%s, Line %d; warning: ",
    (char *)"Expected hex character (one of [0-9a-fA-F]).",
    (char *)"Expected octal character (one of [0-7]).",
    (char *)"Cannot open catalog description %s.",
    (char *)"LengthBytes > %d (sizeof long) not possible.",
    (char *)"Unknown catalog description command",
    (char *)"Unexpected blanks.",
    (char *)"Missing identifier.",
    (char *)"Missing '('.",
    (char *)"ID number used twice.",
    (char *)"Identifier redeclared.",
    (char *)"Expected MinLen (character '/').",
    (char *)"Expected MaxLen (character '/').",
    (char *)"Expected ')'.",
    (char *)"Extra characters at the end of the line.",
    (char *)"Unexpected end of file (missing catalog string).",
    (char *)"String too short.",
    (char *)"String too long.",
    (char *)"Cannot open catalog translation file %s.",
    (char *)"Missing catalog translation command. (Expected second '#'.)",
    (char *)"Unknown catalog translation command.",
    (char *)"Missing catalog translation version; use either ##version\n"\
	"or ##rcsid and ##name.",
    (char *)"Missing catalog translation language.",
    (char *)"Cannot open catalog file %s.",
    (char *)"Cannot create catalog translation file %s.",
    (char *)"%s missing in catalog description.",
    (char *)"Cannot open source description file %s.",
    (char *)"Cannot open source file %s.",
    (char *)"Unknown string type.",
    (char *)"Unexpected end of line. (Missing ')')",
    (char *)"  CDFILE        Catalog description file to scan",
    (char *)"  CTFILE        Catalog translation file to scan",
    (char *)"  CATALOG       Catalog file to create",
    (char *)"  NEWCTFILE     Catalog translation file to create",
    (char *)"  SOURCES       Sources to create; must be something like sfile=sdfile,\n"\
	"                where sfile is a sourcefile and sdfile is a source\n"\
	"                description file",
    (char *)"  WARNCTGAPS    Warn symbols missing in CT file",
    (char *)"  NOOPTIM       Do not skip unchanged strings (equal in both #?.cd and #?.ct)",
    (char *)"  FILL          Use descriptor texts if translation are missing",
    (char *)"  FLUSH         Flush memory when catalog is written",
    (char *)"  NOBEEP        Suppress DisplayBeep()'s on error and warnings",
    (char *)"  QUIET         Suppress warning messages",
    (char *)"Creating a catalog needs a catalog translation file as argument.\n",
    (char *)"Binary characters in stringtype None.",
    (char *)"ID %s missing in CT file.",
    (char *)"Catalog language declared twice.",
    (char *)"Catalog version declared twice.",
    (char *)"Incorrect rcs ID (must be similar to\n"\
	"'$Date$ $Revision$')",
    (char *)"Usage",
    (char *)"Error processing FlexCat.prefs variable, falling back to defaults.\n"\
	"Preferences template: ",
    (char *)"  NOLANGTOLOWER Prevents #language name from being lowercased",
    (char *)"  NOBUFFEREDIO  Disables IO buffers",
    (char *)"  MODIFIED      Creates the catalog only when #?.c(d|t) files were changed",
    (char *)"File %s is up to date",
    (char *)"Cannot get the datestamp of %s",
    (char *)"  COPYMSGNEW    Turns on copying ***NEW*** markers while updating #?.ct file",
    (char *)"  OLDMSGNEW     If old #?.ct file is using other marker, specify it here",
    (char *)"Original string has a trailing ellipsis (...)",
    (char *)"Original string has a trailing spaces",
    (char *)"  NOSPACE       Removes the space being usually put between ';' and the comment",
    (char *)"  NOAUTODATE    Do not use current date in version string. Use from\n"\
	"                .ct instead",
    (char *)"Catalog translation file name not specified at command-line or as base name in description.",
    (char *)"Catalog file name not specified at command-line or as base name in description."
};
