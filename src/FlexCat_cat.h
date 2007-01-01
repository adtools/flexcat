
/****************************************************************

   This file was created automatically by `FlexCat 2.7-dev'
   from "catalogs/FlexCat.cd".

   Do NOT edit by hand!

****************************************************************/

#ifndef FlexCat_CAT_H
#define FlexCat_CAT_H


#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

void LocalizeStringArray(STRPTR *Array);
void OpenFlexCatCatalog ();
void CloseFlexCatCatalog();

struct FC_String
{
   const char *Str;
   const LONG Id;
};

extern struct FC_String FlexCat_Strings[];

#define MSG_USAGE_HEAD (FlexCat_Strings[0].Str)
#define _MSG_USAGE_HEAD 0
#define MSG_USAGE (FlexCat_Strings[1].Str)
#define _MSG_USAGE 1
#define MSG_FILEUPTODATE (FlexCat_Strings[2].Str)
#define _MSG_FILEUPTODATE 2
#define MSG_ERR_WARNING (FlexCat_Strings[3].Str)
#define _MSG_ERR_WARNING 3
#define MSG_ERR_EXPECTEDHEX (FlexCat_Strings[4].Str)
#define _MSG_ERR_EXPECTEDHEX 4
#define MSG_ERR_EXPECTEDOCTAL (FlexCat_Strings[5].Str)
#define _MSG_ERR_EXPECTEDOCTAL 5
#define MSG_ERR_NOLENGTHBYTES (FlexCat_Strings[6].Str)
#define _MSG_ERR_NOLENGTHBYTES 6
#define MSG_ERR_UNKNOWNCDCOMMAND (FlexCat_Strings[7].Str)
#define _MSG_ERR_UNKNOWNCDCOMMAND 7
#define MSG_ERR_UNEXPECTEDBLANKS (FlexCat_Strings[8].Str)
#define _MSG_ERR_UNEXPECTEDBLANKS 8
#define MSG_ERR_NOIDENTIFIER (FlexCat_Strings[9].Str)
#define _MSG_ERR_NOIDENTIFIER 9
#define MSG_ERR_NOLEADINGBRACKET (FlexCat_Strings[10].Str)
#define _MSG_ERR_NOLEADINGBRACKET 10
#define MSG_ERR_DOUBLEID (FlexCat_Strings[11].Str)
#define _MSG_ERR_DOUBLEID 11
#define MSG_ERR_DOUBLEIDENTIFIER (FlexCat_Strings[12].Str)
#define _MSG_ERR_DOUBLEIDENTIFIER 12
#define MSG_ERR_NOMINLEN (FlexCat_Strings[13].Str)
#define _MSG_ERR_NOMINLEN 13
#define MSG_ERR_NOMAXLEN (FlexCat_Strings[14].Str)
#define _MSG_ERR_NOMAXLEN 14
#define MSG_ERR_NOTRAILINGBRACKET (FlexCat_Strings[15].Str)
#define _MSG_ERR_NOTRAILINGBRACKET 15
#define MSG_ERR_EXTRACHARACTERS (FlexCat_Strings[16].Str)
#define _MSG_ERR_EXTRACHARACTERS 16
#define MSG_ERR_MISSINGSTRING (FlexCat_Strings[17].Str)
#define _MSG_ERR_MISSINGSTRING 17
#define MSG_ERR_STRINGTOOSHORT (FlexCat_Strings[18].Str)
#define _MSG_ERR_STRINGTOOSHORT 18
#define MSG_ERR_STRINGTOOLONG (FlexCat_Strings[19].Str)
#define _MSG_ERR_STRINGTOOLONG 19
#define MSG_ERR_UNKNOWNCTCOMMAND (FlexCat_Strings[20].Str)
#define _MSG_ERR_UNKNOWNCTCOMMAND 20
#define MSG_ERR_UNKNOWNIDENTIFIER (FlexCat_Strings[21].Str)
#define _MSG_ERR_UNKNOWNIDENTIFIER 21
#define MSG_ERR_UNKNOWNSTRINGTYPE (FlexCat_Strings[22].Str)
#define _MSG_ERR_UNKNOWNSTRINGTYPE 22
#define MSG_ERR_NOTERMINATEBRACKET (FlexCat_Strings[23].Str)
#define _MSG_ERR_NOTERMINATEBRACKET 23
#define MSG_ERR_NOBINCHARS (FlexCat_Strings[24].Str)
#define _MSG_ERR_NOBINCHARS 24
#define MSG_ERR_CTGAP (FlexCat_Strings[25].Str)
#define _MSG_ERR_CTGAP 25
#define MSG_ERR_DOUBLECTLANGUAGE (FlexCat_Strings[26].Str)
#define _MSG_ERR_DOUBLECTLANGUAGE 26
#define MSG_ERR_DOUBLECTVERSION (FlexCat_Strings[27].Str)
#define _MSG_ERR_DOUBLECTVERSION 27
#define MSG_ERR_WRONGRCSID (FlexCat_Strings[28].Str)
#define _MSG_ERR_WRONGRCSID 28
#define MSG_ERR_NOMEMORY (FlexCat_Strings[29].Str)
#define _MSG_ERR_NOMEMORY 29
#define MSG_ERR_NOCATALOGDESCRIPTION (FlexCat_Strings[30].Str)
#define _MSG_ERR_NOCATALOGDESCRIPTION 30
#define MSG_ERR_NOCATALOGTRANSLATION (FlexCat_Strings[31].Str)
#define _MSG_ERR_NOCATALOGTRANSLATION 31
#define MSG_ERR_NOCTVERSION (FlexCat_Strings[32].Str)
#define _MSG_ERR_NOCTVERSION 32
#define MSG_ERR_NOCATALOG (FlexCat_Strings[33].Str)
#define _MSG_ERR_NOCATALOG 33
#define MSG_ERR_NONEWCTFILE (FlexCat_Strings[34].Str)
#define _MSG_ERR_NONEWCTFILE 34
#define MSG_ERR_NOCTLANGUAGE (FlexCat_Strings[35].Str)
#define _MSG_ERR_NOCTLANGUAGE 35
#define MSG_ERR_NOSOURCE (FlexCat_Strings[36].Str)
#define _MSG_ERR_NOSOURCE 36
#define MSG_ERR_NOSOURCEDESCRIPTION (FlexCat_Strings[37].Str)
#define _MSG_ERR_NOSOURCEDESCRIPTION 37
#define MSG_ERR_NOCTARGUMENT (FlexCat_Strings[38].Str)
#define _MSG_ERR_NOCTARGUMENT 38
#define MSG_ERR_CANTCHECKDATE (FlexCat_Strings[39].Str)
#define _MSG_ERR_CANTCHECKDATE 39
#define MSG_ERR_TRAILINGELLIPSIS (FlexCat_Strings[40].Str)
#define _MSG_ERR_TRAILINGELLIPSIS 40
#define MSG_ERR_TRAILINGBLANKS (FlexCat_Strings[41].Str)
#define _MSG_ERR_TRAILINGBLANKS 41
#define MSG_ERR_NOCTFILENAME (FlexCat_Strings[42].Str)
#define _MSG_ERR_NOCTFILENAME 42
#define MSG_ERR_NOCATFILENAME (FlexCat_Strings[43].Str)
#define _MSG_ERR_NOCATFILENAME 43
#define MSG_ERR_BADPREFS (FlexCat_Strings[44].Str)
#define _MSG_ERR_BADPREFS 44
#define MSG_ERR_NOTRAILINGBLANKS (FlexCat_Strings[45].Str)
#define _MSG_ERR_NOTRAILINGBLANKS 45

#endif
