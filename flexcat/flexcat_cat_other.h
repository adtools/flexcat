/****************************************************************
   This file was created automatically by `FlexCat 2.6.5'
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

#ifndef flexcat_CAT_H
#define flexcat_CAT_H

extern char *flexcat_Strings[];

void OpenflexcatCatalog( void );
void CloseflexcatCatalog( void );

#define msgMemoryError flexcat_Strings[0]
#define msgWarning flexcat_Strings[1]
#define msgExpectedHex flexcat_Strings[2]
#define msgExpectedOctal flexcat_Strings[3]
#define msgNoCatalogDescription flexcat_Strings[4]
#define msgNoLengthBytes flexcat_Strings[5]
#define msgUnknownCDCommand flexcat_Strings[6]
#define msgUnexpectedBlanks flexcat_Strings[7]
#define msgNoIdentifier flexcat_Strings[8]
#define msgNoLeadingBracket flexcat_Strings[9]
#define msgDoubleID flexcat_Strings[10]
#define msgDoubleIdentifier flexcat_Strings[11]
#define msgNoMinLen flexcat_Strings[12]
#define msgNoMaxLen flexcat_Strings[13]
#define msgNoTrailingBracket flexcat_Strings[14]
#define msgExtraCharacters flexcat_Strings[15]
#define msgNoString flexcat_Strings[16]
#define msgShortString flexcat_Strings[17]
#define msgLongString flexcat_Strings[18]
#define msgNoCatalogTranslation flexcat_Strings[19]
#define msgNoCTCommand flexcat_Strings[20]
#define msgUnknownCTCommand flexcat_Strings[21]
#define msgNoCTVersion flexcat_Strings[22]
#define msgNoCTLanguage flexcat_Strings[23]
#define msgNoCatalog flexcat_Strings[24]
#define msgNoNewCTFile flexcat_Strings[25]
#define msgUnknownIdentifier flexcat_Strings[26]
#define msgNoSourceDescription flexcat_Strings[27]
#define msgNoSource flexcat_Strings[28]
#define msgUnknownStringType flexcat_Strings[29]
#define msgNoTerminateBracket flexcat_Strings[30]
#define msgUsage_1 flexcat_Strings[31]
#define msgUsage_2 flexcat_Strings[32]
#define msgUsage_3 flexcat_Strings[33]
#define msgUsage_4 flexcat_Strings[34]
#define msgUsage_5 flexcat_Strings[35]
#define msgUsage_6 flexcat_Strings[36]
#define msgUsage_7 flexcat_Strings[37]
#define msgUsage_8 flexcat_Strings[38]
#define msgUsage_9 flexcat_Strings[39]
#define msgUsage_10 flexcat_Strings[40]
#define msgUsage_11 flexcat_Strings[41]
#define msgNoCTArgument flexcat_Strings[42]
#define msgNoBinChars flexcat_Strings[43]
#define msgCTGap flexcat_Strings[44]
#define msgDoubleCTLanguage flexcat_Strings[45]
#define msgDoubleCTVersion flexcat_Strings[46]
#define msgWrongRcsId flexcat_Strings[47]
#define msgUsageHead flexcat_Strings[48]
#define msgPrefsError flexcat_Strings[49]
#define msgUsage_12 flexcat_Strings[50]
#define msgUsage_13 flexcat_Strings[51]
#define msgUsage_14 flexcat_Strings[52]
#define msgUpToDate flexcat_Strings[53]
#define msgCantCheckDate flexcat_Strings[54]
#define msgUsage_15 flexcat_Strings[55]
#define msgUsage_16 flexcat_Strings[56]
#define msgTrailingEllipsis flexcat_Strings[57]
#define msgTrailingSpaces flexcat_Strings[58]
#define msgUsage_17 flexcat_Strings[59]
#define msgUsage_18 flexcat_Strings[60]
#define msgNoCTFileName flexcat_Strings[61]
#define msgNoCatFileName flexcat_Strings[62]

#endif
