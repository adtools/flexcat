
/****************************************************************

   This file was created automatically by `FlexCat 2.7'
   from "catalogs/FlexCat.cd".

   Do NOT edit by hand!

****************************************************************/

/* Copyright (C) 1993-1999 by Jochen Wiedmann and Marcin Orlowski
 * Copyright (C) 2002-2010 by the FlexCat Open Source Team
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

   This file provides at least minimal compatibility with
   the AmigaOS catalog system on other platforms. It creates
   the necessary string tables (hardcoded ATM) and functions
   to make code work under any operating system.

   Carlos

****************************************************************/

void OpenFlexCatCatalog( void )
{}
void CloseFlexCatCatalog( void )
{}

const char * FlexCat_Strings[61] = {
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
	"  OLDMSGNEW      Custom marker in old translation",
    "File '%s' is up to date",
    "%s, line %d - warning:",
    "%s, line %d - ERROR:",
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
    "missing ')'",
    "extra characters at the end of the line",
    "unexpected end of file (missing catalog strings)",
    "string too short",
    "string too long",
    "unknown command in translation",
    "'%s' missing in catalog description",
    "unknown string type",
    "unexpected end of line (missing ')')",
    "binary characters in string type None",
    "'%s' missing in catalog translation",
    "catalog language declared twice",
    "catalog version declared twice",
    "incorrect RCS Id",
    "out of memory!",
    "cannot open catalog description '%s'",
    "cannot open catalog translation '%s'",
    "missing catalog translation version\n"\
	"Use either '## version' or '## rcsid' and '## name'",
    "cannot open catalog file '%s'",
    "cannot create catalog translation '%s'",
    "missing catalog translation language",
    "cannot open source file '%s'",
    "cannot open source description file '%s'",
    "creating a catalog requires a translation file",
    "cannot get datestamp of '%s'",
    "original string has a trailing ellipsis ('...')",
    "original string has trailing blanks",
    "Catalog translation file name not specified at "\
	"command line or as basename in description",
    "catalog file name not specified at command line or "\
	"as basename in description",
    "error processing 'FlexCat.prefs' variable, falling back to defaults\n"\
	"Template:",
    "original string doesn't have trailing blanks",
    "invalid language in catalog translation file\n"\
	"Language MUST be a string with alphabetical characters and no inlined or trailing spaces",
    "original string doesn't have a trailing ellipsis ('...')",
    "catalog codeset declared twice",
    "invalid codeset in catalog translation file\n"\
	"Codeset MUST be a decimal number without any trailing spaces",
    "missing catalog translation codeset",
    "%s - ERROR:",
    "invalid version string in catalog translation file\n"\
	"Version should be something like\n"\
	"## version $VER: name version.revision (date)\n"\
	"without any spaces in the name",
    "mismatching placeholders",
    "missing placeholders",
    "excessive placeholders",
    "%s - Warning:",
    "missing translation for identifier '%s'",
    "empty translation for identifier '%s'",
    "mismatching trailing control characters"
};
