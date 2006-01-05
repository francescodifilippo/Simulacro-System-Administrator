/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SYMBOL = 258,
     STRSYMBOL = 259,
     NUMBER = 260,
     STRING = 261,
     T_ENDOFFILE = 262,
     T_SEPARATOR = 263,
     T_MOD = 264,
     T_NOT = 265,
     T_OR = 266,
     T_AND = 267,
     T_XOR = 268,
     T_EQ = 269,
     T_NE = 270,
     T_LT = 271,
     T_LE = 272,
     T_GT = 273,
     T_GE = 274,
     T_IF = 275,
     T_THEN = 276,
     T_ELSE = 277,
     T_ENDIF = 278,
     T_LET = 279,
     T_FOR = 280,
     T_TO = 281,
     T_STEP = 282,
     T_NEXT = 283,
     T_WHILE = 284,
     T_WEND = 285,
     T_PRINT = 286,
     T_SUB = 287,
     T_END = 288,
     T_RANDOMIZE = 289,
     UBITNOT = 290,
     UNOT = 291,
     UMINUS = 292
   };
#endif
#define SYMBOL 258
#define STRSYMBOL 259
#define NUMBER 260
#define STRING 261
#define T_ENDOFFILE 262
#define T_SEPARATOR 263
#define T_MOD 264
#define T_NOT 265
#define T_OR 266
#define T_AND 267
#define T_XOR 268
#define T_EQ 269
#define T_NE 270
#define T_LT 271
#define T_LE 272
#define T_GT 273
#define T_GE 274
#define T_IF 275
#define T_THEN 276
#define T_ELSE 277
#define T_ENDIF 278
#define T_LET 279
#define T_FOR 280
#define T_TO 281
#define T_STEP 282
#define T_NEXT 283
#define T_WHILE 284
#define T_WEND 285
#define T_PRINT 286
#define T_SUB 287
#define T_END 288
#define T_RANDOMIZE 289
#define UBITNOT 290
#define UNOT 291
#define UMINUS 292




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 448 "gram.y"
typedef union YYSTYPE {
  char* symbol;
  double number;
  char* string;
  } YYSTYPE;
/* Line 1275 of yacc.c.  */
#line 117 "gram.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



