
/****************************************************************

   This file was created automatically by `FlexCat 2.9'
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
   { "%s, line %d - warning:", 100 },
   { "%s, line %d - ERROR:", 101 },
   { "expected hex character (one of [0-9a-fA-F])", 102 },
   { "expected octal character (one of [0-7])", 103 },
   { "lengthbytes cannot be larger than %d (sizeof long)", 104 },
   { "unknown catalog description command", 105 },
   { "unexpected blanks", 106 },
   { "missing identifier", 107 },
   { "missing '('", 108 },
   { "ID number used twice", 109 },
   { "identifier declared twice", 110 },
   { "expected MinLen (character '/')", 111 },
   { "expected MaxLen (character '/')", 112 },
   { "missing ')'", 113 },
   { "extra characters at the end of the line", 114 },
   { "unexpected end of file (missing catalog strings)", 115 },
   { "string too short", 116 },
   { "string too long", 117 },
   { "unknown command in translation", 118 },
   { "'%s' missing in catalog description", 119 },
   { "unknown string type", 120 },
   { "unexpected end of line (missing ')')", 121 },
   { "binary characters in string type None", 122 },
   { "'%s' missing in catalog translation", 123 },
   { "catalog language declared twice", 124 },
   { "catalog version declared twice", 125 },
   { "incorrect RCS Id", 126 },
   { "out of memory!", 127 },
   { "cannot open catalog description '%s'", 128 },
   { "cannot open catalog translation '%s'", 129 },
   { "missing catalog translation version\n"\
	"Use either '## version' or '## rcsid' and '## name'", 130 },
   { "cannot open catalog file '%s'", 131 },
   { "cannot create catalog translation '%s'", 132 },
   { "missing catalog translation language", 133 },
   { "cannot open source file '%s'", 134 },
   { "cannot open source description file '%s'", 135 },
   { "creating a catalog requires a translation file", 136 },
   { "cannot get datestamp of '%s'", 137 },
   { "original string has a trailing ellipsis ('...')", 138 },
   { "original string has trailing blanks", 139 },
   { "Catalog translation file name not specified at "\
	"command line or as basename in description", 140 },
   { "catalog file name not specified at command line or "\
	"as basename in description", 141 },
   { "error processing 'FlexCat.prefs' variable, falling back to defaults\n"\
	"Template:", 142 },
   { "original string doesn't have trailing blanks", 143 },
   { "invalid language in catalog translation file\n"\
	"Language MUST be a string with alphabetical characters and no inlined or trailing spaces", 144 },
   { "original string doesn't have a trailing ellipsis ('...')", 145 },
   { "catalog codeset declared twice", 146 },
   { "invalid codeset in catalog translation file\n"\
	"Codeset MUST be a decimal number without any trailing spaces", 147 },
   { "missing catalog translation codeset", 148 },
   { "%s - ERROR:", 149 },
   { "invalid version string in catalog translation file\n"\
	"Version should be something like\n"\
	"## version $VER: name version.revision (date)\n"\
	"without any spaces in the name", 150 },
   { "mismatching placeholders", 151 },
   { "missing placeholders", 152 },
   { "excessive placeholders", 153 },
   { "%s - Warning:", 154 },
   { "missing translation for identifier '%s'", 155 },
   { "empty translation for identifier '%s'", 156 },
   { "mismatching trailing control characters", 157 },
   { "non-ASCII character 0x%02x found in original string", 158 },
   { NULL, 0 }
};

static struct Catalog *FlexCatCatalog;

void OpenFlexCatCatalog()
{
   if(LocaleBase != NULL)
   {
      if ((FlexCatCatalog = OpenCatalog(NULL, (STRPTR)"FlexCat.catalog",
                                         OC_BuiltInLanguage, (STRPTR)"english",
                                         OC_Version, 3,
                                         TAG_DONE)) != NULL)
      {
         struct FC_String *fc;

         for(fc = FlexCat_Strings; fc->Str; fc++)
         {
            fc->Str = (const char *)GetCatalogStr(FlexCatCatalog, fc->Id, (STRPTR)fc->Str);
         }
      }
   }
}

void CloseFlexCatCatalog()
{
   if(FlexCatCatalog != NULL)
   {
      CloseCatalog(FlexCatCatalog);
      FlexCatCatalog = NULL;
   }
}

void LocalizeStringArray(STRPTR *Array)
{
   STRPTR *x;

   for(x = Array; *x != NULL; x++)
   {
      *x = strdup(FlexCat_Strings[(int)*x].Str);
   }
}
