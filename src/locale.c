
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
   { "Usage:", 0 },
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
	"  OLDMSGNEW      Custom marker in old translation", 1 },
   { "File '%s' is up to date", 2 },
   { "%s, line %d - warning: ", 100 },
   { "expected hex character (one of [0-9a-fA-F])", 101 },
   { "expected octal character (one of [0-7])", 102 },
   { "lengthbytes cannot be larger than %d (sizeof long)", 103 },
   { "unknown catalog description command", 104 },
   { "unexpected blanks", 105 },
   { "missing identifier", 106 },
   { "missing '('", 107 },
   { "ID number used twice", 108 },
   { "identifier declared twice", 109 },
   { "expected MinLen (character '/')", 110 },
   { "expected MaxLen (character '/')", 111 },
   { "missing ')'", 112 },
   { "extra characters at the end of the line", 113 },
   { "unexpected end of file (missing catalog strings)", 114 },
   { "string too short", 115 },
   { "string too long", 116 },
   { "unknown command in translation", 117 },
   { "'%s' missing in catalog description", 118 },
   { "unknown string type", 119 },
   { "unexpected end of line (missing ')')", 120 },
   { "binary characters in string type None", 121 },
   { "'%s' missing in catalog translation", 122 },
   { "catalog language declared twice", 123 },
   { "catalog version declared twice", 124 },
   { "incorrect RCS Id", 125 },
   { "Out of memory!", 126 },
   { "Cannot open catalog description '%s'.", 127 },
   { "Cannot open catalog translation '%s'.", 128 },
   { "Missing catalog translation version. Use either\n"\
	"'## version' or '## rcsid' and '## name'.", 129 },
   { "Cannot open catalog file '%s'.", 130 },
   { "Cannot create catalog translation '%s'.", 131 },
   { "Missing catalog translation language.", 132 },
   { "Cannot open source file '%s'.", 133 },
   { "Cannot open source description file '%s'.", 134 },
   { "Creating a catalog requires a translation file.", 135 },
   { "Cannot get datestamp of '%s'", 136 },
   { "Original string has a trailing ellipsis ('...')", 137 },
   { "Original string has trailing blanks", 138 },
   { "Catalog translation file name not specified at "\
	"command line or as basename in description.", 139 },
   { "Catalog file name not specified at command line or "\
	"as basename in description.", 140 },
   { "Error processing 'FlexCat.prefs' variable, falling back to defaults.\n"\
	"Template: ", 141 },
   { "Original string doesn't have trailing blanks", 142 },
   { "Invalid language in catalog translation file.\n"\
	"Language MUST be a string with alphabetical\n"\
	"characters and no inlined or trailing spaces.", 143 },
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
