
/****************************************************************
   This file was created automatically by `FlexCat 2.6.2'
   from "Catalogs_Src/FlexCat.cd".

   Do NOT edit by hand!
****************************************************************/

/* Include files */
#include <libraries/gadtools.h>
#include <proto/locale.h>
#include "flexcat.h"

/* Variables */
struct FC_String FlexCat_Strings[] = {
    {"Out of memory!", 0},
    {"%s, Line %d; warning: ", 1},
    {"Expected hex character (one of [0-9a-fA-F]).", 2},
    {"Expected octal character (one of [0-7]).", 3},
    {"Cannot open catalog description %s.", 4},
    {"LengthBytes > %d (sizeof long) not possible.", 5},
    {"Unknown catalog description command", 6},
    {"Unexpected blanks.", 7},
    {"Missing identifier.", 8},
    {"Missing '('.", 9},
    {"ID number used twice.", 10},
    {"Identifier redeclared.", 11},
    {"Expected MinLen (character '/').", 12},
    {"Expected MaxLen (character '/').", 13},
    {"Expected ')'.", 14},
    {"Extra characters at the end of the line.", 15},
    {"Unexpected end of file (missing catalog string).", 16},
    {"String too short.", 17},
    {"String too long.", 18},
    {"Cannot open catalog translation file %s.", 19},
    {"Missing catalog translation command. (Expected second '#'.)", 20},
    {"Unknown catalog translation command.", 21},
    {"Missing catalog translation version; use either ##version\nor ##rcsid and ##name.", 22},
    {"Missing catalog translation language.", 23},
    {"Cannot open catalog file %s.", 24},
    {"Cannot create catalog translation file %s.", 25},
    {"%s missing in catalog description.", 26},
    {"Cannot open source description file %s.", 27},
    {"Cannot open source file %s.", 28},
    {"Unknown string type.", 29},
    {"Unexpected end of line. (Missing ')')", 30},
    {"  CDFILE        Catalog description file to scan", 31},
    {"  CTFILE        Catalog translation file to scan", 32},
    {"  CATALOG       Catalog file to create", 33},
    {"  NEWCTFILE     Catalog translation file to create", 34},
    {"  SOURCES       Sources to create; must be something like sfile=sdfile,\n                where sfile is a sourcefile and sdfile is a source\n                description file", 35},
    {"  WARNCTGAPS    Warn symbols missing in CT file", 36},
    {"  NOOPTIM       Do not skip unchanged strings (equal in both #?.cd and #?.ct)", 37},
    {"  FILL          Use descriptor texts if translation are missing", 38},
    {"  FLUSH         Flush memory when catalog is written", 39},
    {"  NOBEEP        Suppress DisplayBeep()'s on error and warnings", 40},
    {"  QUIET         Suppress warning messages", 41},
    {"Creating a catalog needs a catalog translation file as argument.\n",
     42},
    {"Binary characters in stringtype None.", 43},
    {"ID %s missing in CT file.", 44},
    {"Catalog language declared twice.", 45},
    {"Catalog version declared twice.", 46},
    {"Incorrect rcs ID (must be similar to\n'$Date$ $Revision$')", 47},
    {"Usage", 48},
    {"Error processing FlexCat.prefs variable, falling back to defaults.\nPreferences template: ", 49},
    {"  NOLANGTOLOWER Prevents #language name from being lowercased", 50},
    {"  NOBUFFEREDIO  Disables IO buffers", 51},
    {"  MODIFIED      Creates the catalog only when #?.c(d|t) files were changed", 52},
    {"File %s is up to date", 53},
    {"Cannot get the datestamp of %s", 54},
    {"  COPYMSGNEW    Turns on copying ***NEW*** markers while updating #?.ct file", 55},
    {"  OLDMSGNEW     If old #?.ct file is using other marker, specify it here", 56},
    {"Original string has a trailing ellipsis (...)", 57},
    {"Original string has a trailing spaces", 58},
    {"  NOSPACE       Removes the space being usually put between ';' and the comment", 59},
    {"  NOAUTODATE    Do not use current date in version string. Use from\n                .ct instead", 60},
    {"Catalog translation file name not specified at command-line or as base name in description.", 61},
    {"Catalog file name not specified at command-line or as base name in description.", 62},
    {NULL, 0}
};

static struct Catalog *FlexCatCatalog;


void OpenFlexCatCatalog (  )
{
    if ( LocaleBase )
    {
        if ( ( FlexCatCatalog = OpenCatalog ( NULL, "FlexCat.catalog",
                                              OC_BuiltInLanguage, "english",
                                              OC_Version, 0,
                                              TAG_DONE ) ) != NULL )
        {
            struct FC_String *fc;

            for ( fc = FlexCat_Strings; fc->Str; fc++ )
            {
                fc->Str = GetCatalogStr ( FlexCatCatalog, fc->Id, fc->Str );
            }
        }
    }
}

void CloseFlexCatCatalog (  )
{
    if ( FlexCatCatalog )
    {
        CloseCatalog ( FlexCatCatalog );
    }
}

void LocalizeStringArray ( STRPTR * Array )
{
    STRPTR         *x;

    for ( x = Array; *x; x++ )
    {
        *x = FlexCat_Strings[( int )*x].Str;
    }
}
