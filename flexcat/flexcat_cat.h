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

#define MSG_WARN_Warning (FlexCat_Strings[0].Str)
#define _MSG_WARN_Warning 0
#define MSG_WARN_ExpectedHex (FlexCat_Strings[1].Str)
#define _MSG_WARN_ExpectedHex 1
#define MSG_WARN_ExpectedOctal (FlexCat_Strings[2].Str)
#define _MSG_WARN_ExpectedOctal 2
#define MSG_WARN_NoLengthBytes (FlexCat_Strings[3].Str)
#define _MSG_WARN_NoLengthBytes 3
#define MSG_WARN_UnknownCDCommand (FlexCat_Strings[4].Str)
#define _MSG_WARN_UnknownCDCommand 4
#define MSG_WARN_UnexpectedBlanks (FlexCat_Strings[5].Str)
#define _MSG_WARN_UnexpectedBlanks 5
#define MSG_WARN_NoIdentifier (FlexCat_Strings[6].Str)
#define _MSG_WARN_NoIdentifier 6
#define MSG_WARN_NoLeadingBracket (FlexCat_Strings[7].Str)
#define _MSG_WARN_NoLeadingBracket 7
#define MSG_WARN_DoubleID (FlexCat_Strings[8].Str)
#define _MSG_WARN_DoubleID 8
#define MSG_WARN_DoubleIdentifier (FlexCat_Strings[9].Str)
#define _MSG_WARN_DoubleIdentifier 9
#define MSG_WARN_NoMinLen (FlexCat_Strings[10].Str)
#define _MSG_WARN_NoMinLen 10
#define MSG_WARN_NoMaxLen (FlexCat_Strings[11].Str)
#define _MSG_WARN_NoMaxLen 11
#define MSG_WARN_NoTrailingBracket (FlexCat_Strings[12].Str)
#define _MSG_WARN_NoTrailingBracket 12
#define MSG_WARN_ExtraCharacters (FlexCat_Strings[13].Str)
#define _MSG_WARN_ExtraCharacters 13
#define MSG_WARN_NoString (FlexCat_Strings[14].Str)
#define _MSG_WARN_NoString 14
#define MSG_WARN_ShortString (FlexCat_Strings[15].Str)
#define _MSG_WARN_ShortString 15
#define MSG_WARN_LongString (FlexCat_Strings[16].Str)
#define _MSG_WARN_LongString 16
#define MSG_WARN_NoCTCommand (FlexCat_Strings[17].Str)
#define _MSG_WARN_NoCTCommand 17
#define MSG_WARN_UnknownCTCommand (FlexCat_Strings[18].Str)
#define _MSG_WARN_UnknownCTCommand 18
#define MSG_WARN_UnknownIdentifier (FlexCat_Strings[19].Str)
#define _MSG_WARN_UnknownIdentifier 19
#define MSG_WARN_UnknownStringType (FlexCat_Strings[20].Str)
#define _MSG_WARN_UnknownStringType 20
#define MSG_WARN_NoTerminateBracket (FlexCat_Strings[21].Str)
#define _MSG_WARN_NoTerminateBracket 21
#define MSG_WARN_NoBinChars (FlexCat_Strings[22].Str)
#define _MSG_WARN_NoBinChars 22
#define MSG_WARN_CTGap (FlexCat_Strings[23].Str)
#define _MSG_WARN_CTGap 23
#define MSG_WARN_DoubleCTLanguage (FlexCat_Strings[24].Str)
#define _MSG_WARN_DoubleCTLanguage 24
#define MSG_WARN_DoubleCTVersion (FlexCat_Strings[25].Str)
#define _MSG_WARN_DoubleCTVersion 25
#define MSG_WARN_WrongRcsId (FlexCat_Strings[26].Str)
#define _MSG_WARN_WrongRcsId 26
#define MSG_ERR_MemoryError (FlexCat_Strings[27].Str)
#define _MSG_ERR_MemoryError 27
#define MSG_ERR_NoCatalogDescription (FlexCat_Strings[28].Str)
#define _MSG_ERR_NoCatalogDescription 28
#define MSG_ERR_NoCatalogTranslation (FlexCat_Strings[29].Str)
#define _MSG_ERR_NoCatalogTranslation 29
#define MSG_ERR_NoCTVersion (FlexCat_Strings[30].Str)
#define _MSG_ERR_NoCTVersion 30
#define MSG_ERR_NoCatalog (FlexCat_Strings[31].Str)
#define _MSG_ERR_NoCatalog 31
#define MSG_ERR_NoNewCTFile (FlexCat_Strings[32].Str)
#define _MSG_ERR_NoNewCTFile 32
#define MSG_ERR_NoCTLanguage (FlexCat_Strings[33].Str)
#define _MSG_ERR_NoCTLanguage 33
#define MSG_ERR_NoSource (FlexCat_Strings[34].Str)
#define _MSG_ERR_NoSource 34
#define MSG_ERR_NoSourceDescription (FlexCat_Strings[35].Str)
#define _MSG_ERR_NoSourceDescription 35
#define MSG_ERR_NoCTArgument (FlexCat_Strings[36].Str)
#define _MSG_ERR_NoCTArgument 36
#define MSG_UpToDate (FlexCat_Strings[37].Str)
#define _MSG_UpToDate 37
#define MSG_CantCheckDate (FlexCat_Strings[38].Str)
#define _MSG_CantCheckDate 38
#define MSG_TrailingEllipsis (FlexCat_Strings[39].Str)
#define _MSG_TrailingEllipsis 39
#define MSG_TrailingBlanks (FlexCat_Strings[40].Str)
#define _MSG_TrailingBlanks 40
#define MSG_NoCTFileName (FlexCat_Strings[41].Str)
#define _MSG_NoCTFileName 41
#define MSG_NoCatFileName (FlexCat_Strings[42].Str)
#define _MSG_NoCatFileName 42
#define MSG_PrefsError (FlexCat_Strings[43].Str)
#define _MSG_PrefsError 43
#define MSG_UsageHead (FlexCat_Strings[44].Str)
#define _MSG_UsageHead 44
#define MSG_Usage (FlexCat_Strings[45].Str)
#define _MSG_Usage 45

#endif
