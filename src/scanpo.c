/*
 * $Id$
 *
 * Copyright (C) 1993-1999 Jochen Wiedmann and Marcin Orlowski
 * Copyright (C) 2002-2014 FlexCat Open Source Team
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

#ifdef AMIGA
  #include <proto/locale.h>  /* This is to get locale.library/IsAlpha() */
#endif

#include <errno.h>
#include <limits.h>
#include <time.h>

#include "flexcat.h"
#include "showfuncs.h"
#include "readprefs.h"
#include "globals.h"
#include "utils.h"
#include "createcat.h"

extern char *CatVersionString;
extern char *CatLanguage;
extern char *CatRcsId;
extern char *CatName;
extern int   CodeSet;
extern int   CT_Scanned;

#define IS_NUMBER_OR_LETTER(c) (((c) >= '0' && (c) <= '9') || \
                                ((c) >= 'a' && (c) <= 'z') || \
                                ((c) >= 'A' && (c) <= 'Z'))

#if defined(__amigaos3__) || defined(__MORPHOS__)
char *strptime(const char *string, const char *fmt, struct tm *res);
#endif

/// ScanCTFile

/* This function scans a PO-style format catalog description/translation file.

   Inputs: pofile - name of the description/translation file to scan.
   Result: TRUE if successful, FALSE otherwise.
*/
int ScanPOFile(char *pofile)
{
  FILE *fp;
  char *newline, *line;
  int Result = TRUE;
  int CodeSet_checked = FALSE;
  int revision_found = FALSE;
  int inHeader = TRUE;
  int NextID = 0;
  const char *PoSrcCharset = NULL;
  const char *CatDstCharset = NULL;
  char CatVersionDate[255] = "";
  char CatProjectName[255] = "";
  struct CatString *cs = NULL;
  struct CatString **csptr = &FirstCatString;
  int inMsgID = FALSE;
  int inMsgSTR = FALSE;

  ScanFile = pofile;
  ScanLine = 0;
  if((fp = fopen(pofile, "r")) == NULL)
    ShowErrorQuick(MSG_ERR_NOCATALOGTRANSLATION, pofile);

  if(!NoBufferedIO)
    setvbuf(fp, NULL, _IOFBF, buffer_size);

  while(!feof(fp) && (line = newline = ReadLine(fp, TRUE)) != NULL)
  {
    if(inHeader == TRUE)
    {
      if(*line == '\0')
      {
        inHeader = FALSE;

        // we found the end of the header so lets check if we have all
        // we require to continue
        if(CatVersion > 0 && CatRevision > 0 && CatVersionDate[0] != '\0' && CatProjectName[0] != '\0' &&
           CatVersionString == NULL)
        {
          char buf[255];

          snprintf(buf, sizeof(buf), "$VER: %s.catalog %d.%d (%s)", CatProjectName, CatVersion, CatRevision, CatVersionDate);
          CatVersionString = AllocString(buf);
        }
      }
      else switch(*line)
      {
        case '#':
        {
          // comment lines start with #
          // but they may contain some valueable information for catalog
          // file creation. So lets parse these lines as well
          while(*line == '#' || *line == ' ' || *line == '\t')
            ++line;

          if(Strnicmp(line, "version", 7) == 0)
          {
            line += 8;
            OverSpace(&line);
            CatVersion = strtol(line, &line, 0);
          }
          else if(Strnicmp(line, "revision", 8) == 0)
          {
            line += 9;
            OverSpace(&line);
            CatRevision = strtol(line, &line, 0);
            revision_found = TRUE;
          }
          else if(revision_found == FALSE &&
                  Strnicmp(line, "$Id: ", 5) == 0)
          {
            char *p;

            line += 6;
            p = line;

            // search second space
            p = strchr(p, ' ');
            if(p != NULL)
            {
              p++;
              CatRevision = strtol(p, &p, 0);
            }
          }
          else if(revision_found == FALSE &&
                  Strnicmp(line, "$Revision: ", 11) == 0)
          {
            line += 12;
            CatRevision = strtol(line, &line, 0);
          }
        }
        break;

        case '"':
        {
          if(Strnicmp(line, "\"Language: ", 11) == 0)
          {
            char *p;
            const char *language = NULL;

            if(CatLanguage)
              ShowError(MSG_ERR_DOUBLECTLANGUAGE);

            // set iso-8859-1 as default
            CodeSet = 4;
            CatDstCharset = "iso-8859-1";

            line += 11;
            p = strchr(line, '\\');
            if(p != NULL)
              *p = '\0';

            if(Stricmp(line, "bs") == 0)
            {
              language = "bosanski";
              CodeSet = 5;
              CatDstCharset = "iso-8859-2";
            }
            else if(Stricmp(line, "hr") == 0)
            {
              language = "croatian";
              CodeSet = 112;
              CatDstCharset = "iso-8859-16";
            }
            else if(Stricmp(line, "cs") == 0)
            {
              language = "czech";
              CodeSet = 5;
              CatDstCharset = "iso-8859-2";
            }
            else if(Stricmp(line, "da") == 0)
            {
              language = "danish";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "nl") == 0)
            {
              language = "dutch";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "en_GB") == 0)
              language = "english-british";
            else if(Stricmp(line, "fi") == 0)
            {
              language = "suomi";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "fr") == 0)
            {
              language = "français";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "de") == 0)
            {
              language = "deutsch";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "el") == 0)
            {
              language = "greek";
              CodeSet = 10;
              CatDstCharset = "iso-8859-7";
            }
            else if(Stricmp(line, "hu") == 0)
            {
              language = "magyar";
              CodeSet = 112;
              CatDstCharset = "iso-8859-16";
            }
            else if(Stricmp(line, "it") == 0)
            {
              language = "italiano";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "no") == 0)
            {
              language = "norsk";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "pl") == 0)
            {
              language = "polski";
              CodeSet = 112;
              CatDstCharset = "iso-8859-16";
            }
            else if(Stricmp(line, "pt_BR") == 0)
              language = "português-brasil";
            else if(Stricmp(line, "pt") == 0)
              language = "português";
            else if(Stricmp(line, "ru") == 0)
            {
              language = "russian";
              CodeSet = 2104;
              #if defined(AMIGA)
              CatDstCharset = "Amiga-1251";
              #else
              CatDstCharset = "windows-1251"; // iconv doesn't know anything about Amiga-1251 :(
              #endif
            }
            else if(Stricmp(line, "sr") == 0)
            {
              language = "srpski";
              CodeSet = 112;
              CatDstCharset = "iso-8859-16";
            }
            else if(Stricmp(line, "sl") == 0)
            {
              language = "slovensko";
              CodeSet = 5;
              CatDstCharset = "iso-8859-2";
            }
            else if(Stricmp(line, "es") == 0)
            {
              language = "español";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "sv") == 0)
            {
              language = "svenska";
              CodeSet = 111;
              CatDstCharset = "iso-8859-15";
            }
            else if(Stricmp(line, "tr") == 0)
            {
              language = "türkçe";
              CodeSet = 12;
              CatDstCharset = "iso-8859-9";
            }

            if(language != NULL)
              CatLanguage = AddCatalogChunk(strdup("LANG"), language);
          }
          else if(Strnicmp(line, "\"Language-Team: ", 16) == 0)
          {
            char *p;

            line += 16;
            p = strchr(line, '\\');
            if(p != NULL)
              *p = '\0';

            AddCatalogChunk(strdup("AUTH"), line);
          }
          else if(CodeSet_checked == FALSE &&
                  Strnicmp(line, "\"Content-Type: ", 15) == 0)
          {
            char *p;

            line += 16;
            p = strstr(line, "charset=");
            if(p != NULL)
            {
              char *q;

              p += 8;

              q = strchr(p, '\\');
              if(q != NULL)
                *q = '\0';

              PoSrcCharset = strdup(p);
            }

            CodeSet_checked = TRUE;
          }
          else if(Strnicmp(line, "\"PO-Revision-Date: ", 19) == 0)
          {
            struct tm tm;

            line += 19;
            memset(&tm, 0, sizeof(tm));
            strptime(line, "%Y-%m-%d", &tm);
            strftime(CatVersionDate, sizeof(CatVersionDate), "%d.%m.%Y", &tm);
          }
          else if(Strnicmp(line, "\"Project-Id-Version: ", 21) == 0)
          {
            char *p;

            line += 21;
            p = strchr(line, '\\');
            if(p != NULL)
              *p = '\0';

            strcpy(CatProjectName, line);
          }
        }
        break;
      }
    }
    else
    {
      // check if we found a line starting with "msgctxt" as that signals us
      // a new catalog string should be added
      if(Strnicmp(line, "msgctxt \"", 9) == 0)
      {
        char *idstr;

        // we found a new 'msgctxt' lets clear cs
        cs = NULL;
        inMsgID = FALSE;
        inMsgSTR = FALSE;

        line += 9;

        /* Check for blanks at the start of line. */
        if(*line == ' ' || *line == '\t')
        {
          ShowError(MSG_ERR_UNEXPECTEDBLANKS);
          OverSpace(&line);
        }

        idstr = line;
        while(IS_NUMBER_OR_LETTER(*line) || *line == '_')
          ++line;

        if(idstr == line)
        {
          ShowError(MSG_ERR_NOIDENTIFIER);
          Result = FALSE;
        }
        else
        {
          int found;

          if((cs = malloc(sizeof(*cs))) == NULL)
            MemError();

          // search for the next catstring ID in case the ID
          // specifier is missing "(//)" in the msgctxt
          do
          {
            struct CatString *scs;

            found = TRUE;
            for(scs = FirstCatString; scs != NULL; scs = scs->Next)
            {
              if(scs->ID == NextID)
              {
                found = FALSE;
                ++NextID;
                break;
              }
            }
          }
          while(found == FALSE);

          cs->Next = NULL;
          cs->ID = NextID;
          cs->MinLen = 0;
          cs->MaxLen = -1;
          cs->CD_Str = (char *)"";
          cs->CT_Str = NULL;
          cs->NotInCT = TRUE;
          cs->POformat = TRUE;

          if((cs->ID_Str = malloc((line - idstr) + 1)) == NULL)
            MemError();

          strncpy(cs->ID_Str, idstr, line - idstr);
          cs->ID_Str[line - idstr] = '\0';
          OverSpace(&line);

          /* Check if next char in line is '('? (//) */
          if(*line != '(')
          {
            ShowError(MSG_ERR_NO_LEADING_BRACKET, cs->ID_Str);
            Result = FALSE;
          }
          else
          {
            struct CatString *scs;

            ++line;
            OverSpace(&line);

            /* Check for default config of line (//) */
            if(*line != '/')
            {
              if(*line == '+')
                NextID = cs->ID = NextID + strtol(line, &line, 0);
              else if(*line == '$')
              {
                line++;
                cs->ID = NextID = strtol(line, &line, 16);
              }
              else
                cs->ID = NextID = strtol(line, &line, 0);

              OverSpace(&line);
            }

            /* Check for already used identifier. */
            for(scs = FirstCatString; scs != NULL; scs = scs->Next)
            {
              if(scs->ID == cs->ID)
              {
                ShowError(MSG_ERR_DOUBLE_ID, cs->ID_Str);
                Result = FALSE;
              }
              if(strcmp(cs->ID_Str, scs->ID_Str) == 0)
              {
                ShowError(MSG_ERR_DOUBLE_IDENTIFIER, cs->ID_Str);
                Result = FALSE;
              }
            }

            /* Check for min/len values (//) */
            if(*line != '/')
            {
              ShowWarn(MSG_ERR_NO_MIN_LEN, cs->ID_Str);
              Result = FALSE;
            }
            else
            {
              ++line;
              OverSpace(&line);
              if(*line != '/')
              {
                cs->MinLen = strtol(line, &line, 0);
                OverSpace(&line);
              }
              if(*line != '/')
              {
                ShowWarn(MSG_ERR_NO_MAX_LEN, cs->ID_Str);
                Result = FALSE;
              }
              else
              {
                ++line;
                OverSpace(&line);
                if(*line != ')')
                {
                  cs->MaxLen = strtol(line, &line, 0);
                  OverSpace(&line);
                }
                if(*line != ')')
                {
                  ShowError(MSG_ERR_NO_TRAILING_BRACKET, cs->ID_Str);
                  Result = FALSE;
                }
                else
                {
                  ++line;
                  OverSpace(&line);
                  if(*line && *line != '\"')
                    ShowError(MSG_ERR_EXTRA_CHARACTERS_ID, cs->ID_Str);
                }
              }
            }
          }

          //printf("ID_Str: '%s' (%d)\n", cs->ID_Str, cs->ID);

          cs->Nr = NumStrings;
          cs->LenBytes = 0;
          *csptr = cs;
          csptr = &cs->Next;
          ++NumStrings;
        }
      }
      else if(cs != NULL)
      {
        char *p;

        // make sure double-backslashes end up in single
        // back slashes
        while((p = strstr(line, "\\\\033")))
          memmove(p, p+1, strlen(p));

        // unquote the string
        if(line[strlen(line)-1] == '"')
          line[strlen(line)-1] = '\0';

        if(Strnicmp(line, "msgid \"", 7) == 0)
        {
          line += 7;

          // if the string starts with <EMPTY> we out to remove
          // the rest of the string!
          if(strncmp(line, "<EMPTY>", 7) == 0)
            *line = '\0';

          if(strlen(line) > 0)
            cs->CD_Str = ConvertString(line, PoSrcCharset, CatDstCharset);
          else
          {
            cs->CD_Str = malloc(1);
            cs->CD_Str[0] = '\0';
          }

          //printf("CD_Str: '%s' '%s'\n", cs->CD_Str, line);

          inMsgID = TRUE;
          inMsgSTR = FALSE;
        }
        else if(Strnicmp(line, "msgstr \"", 8) == 0)
        {
          line += 8;

          if(strlen(line) > 0)
            cs->CT_Str = ConvertString(line, PoSrcCharset, CatDstCharset);
          else
          {
            cs->CT_Str = malloc(1);
            cs->CT_Str[0] = '\0';
          }

          cs->NotInCT = FALSE;

          //printf("CT_Str: '%s'\n", cs->CT_Str);

          inMsgSTR = TRUE;
          inMsgID = FALSE;
        }
        else if(*line == '"') // line starts with "
        {
          line++;

          if(inMsgID == TRUE)
          {
            char *t = ConvertString(line, PoSrcCharset, CatDstCharset);

            cs->CD_Str = AddString(cs->CD_Str, t);

            //printf("CD_Str2: '%s' '%s'\n", cs->CD_Str, line);

            free(t);
          }
          else if(inMsgSTR == TRUE)
          {
            char *t = ConvertString(line, PoSrcCharset, CatDstCharset);

            cs->CT_Str = AddString(cs->CD_Str, t);

            //printf("CT_Str2: '%s' '%s'\n", cs->CT_Str, line);

            free(t);
          }
        }
      }
    }
  }

  /*
  printf("CatVersion: %d.%d\n", CatVersion, CatRevision);
  printf("CatVersionDate: '%s'\n", CatVersionDate);
  printf("CatVersionString: '%s'\n", CatVersionString);
  printf("CatLanguage: '%s'\n", CatLanguage);
  printf("PoSrcCharset: '%s'\n", PoSrcCharset);
  printf("CatDstCharset: '%s'\n", CatDstCharset);
  */

  if(!CodeSet_checked)
    ShowErrorQuick(MSG_ERR_NOCTCODESET);

  if(!(CatVersionString || (CatRcsId && CatName)))
    ShowErrorQuick(MSG_ERR_NOCTVERSION);

  // check consistenty of translations found
  for(cs = FirstCatString; cs != NULL; cs = cs->Next)
  {
    if(cs->CT_Str == NULL)
      ShowWarnQuick(MSG_ERR_MISSINGTRANSLATION, cs->ID_Str);
    else
    {
      size_t reallen;
      size_t cd_len;

      /* Get string length */
      reallen = strlen(cs->CT_Str);
      cd_len = strlen(cs->CD_Str);

      if(cs->MinLen > 0 && reallen < (size_t)cs->MinLen)
        ShowWarnQuick(MSG_ERR_STRING_TOO_SHORT, cs->ID_Str);

      if(cs->MaxLen > 0 && reallen > (size_t)cs->MaxLen)
        ShowWarnQuick(MSG_ERR_STRING_TOO_LONG, cs->ID_Str);

      // check for empty translations
      if(cd_len > 0 && reallen == 0)
        ShowWarnQuick(MSG_ERR_EMPTYTRANSLATION, cs->ID_Str);

      /* Check for trailing ellipsis. */
      if(reallen >= 3 && cd_len >= 3)
      {
        if(strcmp(&cs->CD_Str[cd_len - 3], "...") == 0 &&
           strcmp(&cs->CT_Str[reallen - 3], "...") != 0)
        {
          ShowWarnQuick(MSG_ERR_TRAILING_ELLIPSIS, cs->ID_Str);
        }

        if(strcmp(&cs->CD_Str[cd_len - 3], "...") != 0 &&
           strcmp(&cs->CT_Str[reallen - 3], "...") == 0)
        {
          ShowWarnQuick(MSG_ERR_NO_TRAILING_ELLIPSIS, cs->ID_Str);
        }
      }

      /* Check for trailing spaces. */
      if(reallen >= 1 && cd_len >= 1)
      {
        if(strcmp(&cs->CD_Str[cd_len - 1], " ") == 0 &&
           strcmp(&cs->CT_Str[reallen - 1], " ") != 0)

        {
          ShowWarnQuick(MSG_ERR_TRAILING_BLANKS, cs->ID_Str);
        }

        if(strcmp(&cs->CD_Str[cd_len - 1], " ") != 0 &&
           strcmp(&cs->CT_Str[reallen - 1], " ") == 0)

        {
          ShowWarnQuick(MSG_ERR_NO_TRAILING_BLANKS, cs->ID_Str);
        }
      }

      /* Check for matching placeholders */
      if(reallen >= 1 && cd_len >= 1)
      {
        char *cdP = cs->CD_Str;
        char *ctP = cs->CT_Str;

        do
        {
          cdP = strchr(cdP, '%');
          ctP = strchr(ctP, '%');

          if(cdP == NULL && ctP == NULL)
          {
            // no more placeholders, bail out
            break;
          }
          else if(cdP != NULL && ctP != NULL)
          {
            // skip the '%' sign
            cdP++;
            ctP++;

            // check the placeholder only if the '%' is followed by an
            // alpha-numerical character or another percent sign
            if(IS_NUMBER_OR_LETTER(*cdP) || *cdP == '%')
            {
              if(*cdP != *ctP)
              {
                ShowWarnQuick(MSG_ERR_MISMATCHING_PLACEHOLDERS, cs->ID_Str);

                break;
              }

              // skip the second '%' sign
              if(*cdP == '%')
                  cdP++;
              if(*ctP == '%')
                  ctP++;
            }
            else if(IS_NUMBER_OR_LETTER(*ctP) || *ctP == '%')
            {
              // the translation uses a placeholder while the description
              // uses none.
              ShowWarnQuick(MSG_ERR_EXCESSIVE_PLACEHOLDERS, cs->ID_Str);

              break;
            }
          }
          else if(cdP != NULL && ctP == NULL)
          {
            // skip the '%' sign
            cdP++;

            // check if really a placeholder follows or just another percent sign
            // the original string is allowed to contain more single percent signs than the translated string
            if(IS_NUMBER_OR_LETTER(*cdP) || *cdP == '%')
            {
              // the description uses at least one more placeholder than the translation
              ShowWarnQuick(MSG_ERR_MISSING_PLACEHOLDERS, cs->ID_Str);
            }

            break;
          }
          else if(cdP == NULL && ctP != NULL)
          {
            // skip the '%' sign
            ctP++;

            // check if really a placeholder follows or just another percent sign
            // the translated string is allowed to contain more single percent signs than the original string
            if(IS_NUMBER_OR_LETTER(*ctP) || *ctP == '%')
            {
              // the translation uses at least one more placeholder than the description
              ShowWarnQuick(MSG_ERR_EXCESSIVE_PLACEHOLDERS, cs->ID_Str);
            }

            break;
          }
        }
        while(TRUE);
      }
    }
  }

  if(line != NULL)
    free(line);

  fclose(fp);

  if(WarnCTGaps)
  {
    for(cs = FirstCatString; cs != NULL; cs = cs->Next)
    {
      if(cs->CT_Str == NULL)
      {
        ShowWarn(MSG_ERR_CTGAP, cs->ID_Str);
      }
    }
  }

  if(Result)
    CT_Scanned = TRUE;

  return(Result);
}

///

