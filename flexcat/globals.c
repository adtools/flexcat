#include "flexcat.h"

/// Globals
char           *BaseName = "";  /* Basename of catalog description */
char           *Language = "english";   /* Language of catalog description */
int             CatVersion = 0; /* Version of catalog to be opened */
int             LengthBytes = 0;        /* Number of bytes to preceed a
                                           created string and containing
                                           its length. */
int             NumStrings = 0; /* Number of catalog strings */
char           *ScanFile;       /*  File currently scanned */
int             ScanLine;       /*  Line currently scanned */
int             GlobalReturnCode = 0;   /*  Will be 5, if warnings appear */
int             NumberOfWarnings = 0;   /* We count warnings to be smart
                                           and not to do Beep bombing, but
                                           call DisplayBeep() only once */
int             buffer_size = 2048;     /* Size of the IO buffer */
char            VersTag[] = VERSTAG;
//|
