#ifndef __LANGUAGE__
#define __LANGUAGE__

#define POOL_SIZE           16384

#define SRC_LANG_INC        "True"
#define SRC_LANG_DEC        "False"
#define SRC_LANG_PTR_INC    "!True"
#define SRC_LANG_PTR_DEC    "!False"
#define SRC_LANG_PUTC       "If(True)"
#define SRC_LANG_GETC       "!If(True)"
#define SRC_LANG_WHILE      "If(False)"
#define SRC_LANG_ENDWHILE   "!If(False)"

enum LANG_TOKEN { LANG_INC, LANG_DEC, LANG_PTR_INC, LANG_PTR_DEC, LANG_PUTC, LANG_GETC, LANG_WHILE, LANG_ENDWHILE };

#endif
