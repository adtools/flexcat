/****************************************************************
   This file was created automatically by `FlexCat 2.6.7'
   from "catalogs/FlexCat.cd".

   Do NOT edit by hand!
****************************************************************/

/****************************************************************

   This file is a quick-hack-solution for all of you wanting
   to compile FlexCat on non-amiga platform. It creates
   necessary string tables (hardcoded ATM) and functions to
   make code work under any operating system.

   Carlos

****************************************************************/

#ifndef FlexCat_CAT_H
#define FlexCat_CAT_H

extern char *FlexCat_Strings[];

void OpenFlexCatCatalog( void );
void CloseFlexCatCatalog( void );

#define MSG_WARN_Warning FlexCat_Strings[0]
#define MSG_WARN_ExpectedHex FlexCat_Strings[1]
#define MSG_WARN_ExpectedOctal FlexCat_Strings[2]
#define MSG_WARN_NoLengthBytes FlexCat_Strings[3]
#define MSG_WARN_UnknownCDCommand FlexCat_Strings[4]
#define MSG_WARN_UnexpectedBlanks FlexCat_Strings[5]
#define MSG_WARN_NoIdentifier FlexCat_Strings[6]
#define MSG_WARN_NoLeadingBracket FlexCat_Strings[7]
#define MSG_WARN_DoubleID FlexCat_Strings[8]
#define MSG_WARN_DoubleIdentifier FlexCat_Strings[9]
#define MSG_WARN_NoMinLen FlexCat_Strings[10]
#define MSG_WARN_NoMaxLen FlexCat_Strings[11]
#define MSG_WARN_NoTrailingBracket FlexCat_Strings[12]
#define MSG_WARN_ExtraCharacters FlexCat_Strings[13]
#define MSG_WARN_NoString FlexCat_Strings[14]
#define MSG_WARN_ShortString FlexCat_Strings[15]
#define MSG_WARN_LongString FlexCat_Strings[16]
#define MSG_WARN_NoCTCommand FlexCat_Strings[17]
#define MSG_WARN_UnknownCTCommand FlexCat_Strings[18]
#define MSG_WARN_UnknownIdentifier FlexCat_Strings[19]
#define MSG_WARN_UnknownStringType FlexCat_Strings[20]
#define MSG_WARN_NoTerminateBracket FlexCat_Strings[21]
#define MSG_WARN_NoBinChars FlexCat_Strings[22]
#define MSG_WARN_CTGap FlexCat_Strings[23]
#define MSG_WARN_DoubleCTLanguage FlexCat_Strings[24]
#define MSG_WARN_DoubleCTVersion FlexCat_Strings[25]
#define MSG_WARN_WrongRcsId FlexCat_Strings[26]
#define MSG_ERR_MemoryError FlexCat_Strings[27]
#define MSG_ERR_NoCatalogDescription FlexCat_Strings[28]
#define MSG_ERR_NoCatalogTranslation FlexCat_Strings[29]
#define MSG_ERR_NoCTVersion FlexCat_Strings[30]
#define MSG_ERR_NoCatalog FlexCat_Strings[31]
#define MSG_ERR_NoNewCTFile FlexCat_Strings[32]
#define MSG_ERR_NoCTLanguage FlexCat_Strings[33]
#define MSG_ERR_NoSource FlexCat_Strings[34]
#define MSG_ERR_NoSourceDescription FlexCat_Strings[35]
#define MSG_ERR_NoCTArgument FlexCat_Strings[36]
#define MSG_UpToDate FlexCat_Strings[37]
#define MSG_CantCheckDate FlexCat_Strings[38]
#define MSG_TrailingEllipsis FlexCat_Strings[39]
#define MSG_TrailingBlanks FlexCat_Strings[40]
#define MSG_NoCTFileName FlexCat_Strings[41]
#define MSG_NoCatFileName FlexCat_Strings[42]
#define MSG_PrefsError FlexCat_Strings[43]
#define MSG_UsageHead FlexCat_Strings[44]
#define MSG_Usage FlexCat_Strings[45]

#endif
