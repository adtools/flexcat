/****************************************************************
   This file was created automatically by `FlexCat 2.6.7'
   from "catalogs/FlexCat.cd".

   Do NOT edit by hand!
****************************************************************/

/* Copyright (C) 2005 Pavel Fedin <sonic_amiga@rambler.ru>
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

char * FlexCat_Strings[46] = {
    "%s, line %d - warning: ",
    "expected hex character (one of [0-9a-fA-F])",
    "expected octal character (one of [0-7])",
    "lengthbytes cannot be larger than %d (sizeof long)",
    "unknown catalog description command",
    "unexpected blanks",
    "missing identifier",
    "missing '('",
    "ID number used twice",
    "identifier declared twice",
    "expected MinLen (character '/')",
    "expected MaxLen (character '/')",
    "expected ')'",
    "extra characters at the end of the line",
    "unexpected end of file (missing catalog strings)",
    "string too short",
    "string too long",
    "missing command in translation (expected a second '#')",
    "unknown command in translation",
    "'%s' missing in catalog description",
    "unknown string type",
    "unexpected end of line (missing ')')",
    "binary characters in string type None",
    "'%s' missing in catalog translation",
    "catalog language declared twice",
    "catalog version declared twice",
    "incorrect RCS Id",
    "Out of memory!",
    "Cannot open catalog description '%s'.",
    "Cannot open catalog translation '%s'.",
    "Missing catalog translation version. Use either\n"\
	"'## version' or '## rcsid' and '## name'.",
    "Cannot open catalog file '%s'.",
    "Cannot create catalog translation '%s'.",
    "Missing catalog translation language.",
    "Cannot open source file '%s'.",
    "Cannot open source description file '%s'.",
    "Creating a catalog requires a translation file.",
    "File '%s' is up to date",
    "Cannot get datestamp of '%s'",
    "Original string has a trailing ellipsis ('...')",
    "Original string has trailing blanks",
    "Catalog translation file name not specified at "\
	"command line or as basename in description.",
    "Catalog file name not specified at command line or "\
	"as basename in description.",
    "Error processing 'FlexCat.prefs' variable, falling back to defaults.\n"\
	"Template: ",
    "Usage:",
    "  CDFILE         Catalog description file to scan\n"\
	"  CTFILE         Catalog translation file to scan\n"\
	"  CATALOG        Catalog file to create\n"\
	"  NEWCTFILE      Catalog translation file to create\n"\
	"  SOURCES        Sources to create; must be something like SFILE=SDFILE,\n"\
	"                 where SFILE is a source file and SDFILE is a source\n"\
	"                 description file\n"\
	"  WARNCTGAPS     Warn about identifiers missing in translation\n"\
	"  NOOPTIM        Do not skip unchanged strings in translation/description\n"\
	"  FILL           Fill missing identifiers with original text\n"\
	"  FLUSH          Flush memory after the catalog is created\n"\
	"  NOBEEP         No DisplayBeep() on errors and warnings\n"\
	"  QUIET          No warnings\n"\
	"  NOLANGTOLOWER  Prevent #language name from being lowercased\n"\
	"  NOBUFFEREDIO   Disable I/O buffers\n"\
	"  MODIFIED       Create catalog only if description/translation have changed\n"\
	"  COPYMSGNEW     Copy ***NEW*** markers over from old translation\n"\
	"  OLDMSGNEW      Custom marker in old translation\n"\
	"  NOSPACE        Removes the space being usually put between ';' and the comment\n"\
	"  NOAUTODATE     Do not use current date in version string. Use from\n"\
	"                 .ct instead"
};
