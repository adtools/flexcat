/****************************************************************
   This file was created automatically by `FlexCat 2.7-dev'
   from "catalogs/FlexCat.cd".

   Do NOT edit by hand!
****************************************************************/

/* Include files */
#include <libraries/gadtools.h>
#include <proto/locale.h>
#include <string.h>

#include "FlexCat_cat.h"

/* Variables */
struct FC_String FlexCat_Strings[] =
{
   { "%s, line %d - warning: ", 0 },
   { "expected hex character (one of [0-9a-fA-F])", 1 },
   { "expected octal character (one of [0-7])", 2 },
   { "lengthbytes cannot be larger than %d (sizeof long)", 3 },
   { "unknown catalog description command", 4 },
   { "unexpected blanks", 5 },
   { "missing identifier", 6 },
   { "missing '('", 7 },
   { "ID number used twice", 8 },
   { "identifier declared twice", 9 },
   { "expected MinLen (character '/')", 10 },
   { "expected MaxLen (character '/')", 11 },
   { "expected ')'", 12 },
   { "extra characters at the end of the line", 13 },
   { "unexpected end of file (missing catalog strings)", 14 },
   { "string too short", 15 },
   { "string too long", 16 },
   { "missing command in translation (expected a second '#')", 17 },
   { "unknown command in translation", 18 },
   { "'%s' missing in catalog description", 19 },
   { "unknown string type", 20 },
   { "unexpected end of line (missing ')')", 21 },
   { "binary characters in string type None", 22 },
   { "'%s' missing in catalog translation", 23 },
   { "catalog language declared twice", 24 },
   { "catalog version declared twice", 25 },
   { "incorrect RCS Id", 26 },
   { "Out of memory!", 27 },
   { "Cannot open catalog description '%s'.", 28 },
   { "Cannot open catalog translation '%s'.", 29 },
   { "Missing catalog translation version. Use either\n"\
	"'## version' or '## rcsid' and '## name'.", 30 },
   { "Cannot open catalog file '%s'.", 31 },
   { "Cannot create catalog translation '%s'.", 32 },
   { "Missing catalog translation language.", 33 },
   { "Cannot open source file '%s'.", 34 },
   { "Cannot open source description file '%s'.", 35 },
   { "Creating a catalog requires a translation file.", 36 },
   { "File '%s' is up to date", 37 },
   { "Cannot get datestamp of '%s'", 38 },
   { "Original string has a trailing ellipsis ('...')", 39 },
   { "Original string has trailing blanks", 40 },
   { "Catalog translation file name not specified at "\
	"command line or as basename in description.", 41 },
   { "Catalog file name not specified at command line or "\
	"as basename in description.", 42 },
   { "Error processing 'FlexCat.prefs' variable, falling back to defaults.\n"\
	"Template: ", 43 },
   { "Usage:", 44 },
   { "  CDFILE         Catalog description file to scan\n"\
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
	"  OLDMSGNEW      Custom marker in old translation", 45 },
   { NULL, 0 }
};

static struct Catalog *FlexCatCatalog;

void OpenFlexCatCatalog()
{
   if (LocaleBase)
   {
      if ((FlexCatCatalog = OpenCatalog(NULL, "FlexCat.catalog",
     			          OC_BuiltInLanguage, "english",
     			          OC_Version, 3,
     			          TAG_DONE
                                 ))
         )
      {
         struct FC_String *fc;

         for (fc = FlexCat_Strings; fc->Str; fc++)
         {
            fc->Str = (char *)GetCatalogStr(FlexCatCatalog, fc->Id, fc->Str);
         }
      }
   }
}

void CloseFlexCatCatalog()
{
   if (FlexCatCatalog)
   {
      CloseCatalog(FlexCatCatalog);
   }
}

void LocalizeStringArray(STRPTR *Array)
{
   STRPTR *x;

   for (x = Array; *x != NULL; x++)
   {
      *x = strdup(FlexCat_Strings[(int)*x].Str);
   }
}

