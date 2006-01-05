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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 19 "gram.y"

#include <stdlib.h>
#include <stdio.h>
#include "reaction.h"
#include "intern.h"
#include "blib.h"

/* somewhere else in lex.l */
extern int yyerror(char*);
extern int yylex();
void CXParse( char* );

/* prototypes */
void begin_subroutine(char*);
void gen_spop();
void gen_scopy();
void gen_sswap();
void gen_unop(char);
void gen_binop(char);
void gen_comp(char);
void gen_print();
void gen_pushsymbol (char*);
void gen_popsymbol ( char*);
void gen_pushnumber (double);
void gen_pushstring (char*);
void gen_jump (char*);
void gen_label (char*);
void gen_if (void);
void gen_for ( char*, double step);
void gen_next ( char*, double);
void gen_then (void);
void gen_endif (void);
void gen_call(char*,int);
void gen_return(void);
void gen_while(void);
void gen_wend(void);
void gen_while_label(void);

/* internal compiler stack */
#define MAX_INT_STACK 2048
int intstack_count;
int intstacks[MAX_INT_STACK];

/* push an integer to stack */
void pushint(int x)
{
  intstacks[intstack_count] = x;
  intstack_count++;
}

/* pop an integer from stack */
int popint(void)
{
  intstack_count--;
  return intstacks[intstack_count];
}

/* swap two topmost integers on stack */
void swapint(void)
{
  int temp;

  temp = intstacks[intstack_count-1];
  intstacks[intstack_count-1] = intstacks[intstack_count-2];
  intstacks[intstack_count-2] = temp;
}

/* magic label */
#ifndef MAX_ID_LENGTH
#define MAX_ID_LENGTH 255
#endif
char* magiclabel(int i){
static char name[MAX_ID_LENGTH];
sprintf (name,"magic_%d",i);
return name;
}

/* local variables */
BList* bytecodes;
int autolabel;
int compile_error_code;
int compile_line_no;

/* macro: add code with error-checking */
#define ADD_CODE(code) { \
  if (compile_error_code) return; \
  (code) = code_add(); \
  if (!(code)) return; \
  if (compile_error_code) return; \
  }

/* add a new bytecode, return pointer to the code (NULL upon error) */
BSBytecode* code_add(void)
{
  BSBytecode *code;

  code = b_new( BSBytecode );
  code->type = -1;
  code->argc = 0;
  code->op = '\0';
  code->value = NULL;
  code->label = NULL;
  code->symbol = NULL;
  bytecodes = blist_append( bytecodes, code );
  return code;
}

/* create a bytecode to terminate program */
void gen_terminate (void)
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_TERMINATE;
}

/* create unconditional jump */
void gen_jump (char *label)
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_JUMP;
  code->label = b_strdup(label);
}

/* create a label */
void gen_label (char *label)
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_LABEL;
  code->label = b_strdup(label);
}

/* generate bytecode to pop (anything) from stack */
void gen_spop()
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_SPOP;
}

/* generate bytecode to copy topmost entry on stack */
void gen_scopy()
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_SCOPY;
}

/* generate bytecode to swap topmost entry on stack*/
void gen_sswap()
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_SSWAP;
}

/* create a bytecode to push a symbol */
void gen_pushsymbol ( char* symbol)
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_PUSHSYMBOL;
  code->symbol = b_strdup( symbol );
}

/* generate bytecode for unary operator */
void gen_unop( char o )
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_UNOP;
  code->op = o;

}

/* generate bytecode for unary operator */
void gen_binop( char o )
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_BINOP;
  code->op = o;

}

/* generate bytecode for comparation operator */
/* for possible operator, see BS_COMP_ constants */
void gen_comp( char o )
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_COMP;
  code->op = o;

}

void gen_print()
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_PRINT;
}

/* create a bytecode to pop stack to a symbol */
void gen_popsymbol ( char* symbol )
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_POPSYMBOL;
  code->symbol = b_strdup( symbol );
}

/* create a bytecode to push a number */
void gen_pushnumber (double number)
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_PUSHVALUE;
  code->value = bvariant_new_double( number );
}

/* create a bytecode to push a string */
void gen_pushstring (char *string)
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_PUSHVALUE;
  code->value = bvariant_new_string( string );
}

/* create a conditional branch which jump to given autolabel if FALSE  */
void gen_if (void)
{
  BSBytecode *code;
  int i;

  i = autolabel++;
  pushint(i);
  ADD_CODE(code);
  code->type = PCODE_IF;
  code->label = b_strdup(magiclabel(i));
}

/* goto, then create autolabel */
void gen_then (void)
{
  int i;

  i = autolabel++;
  pushint(i);
  gen_jump(magiclabel(i));

  swapint();
  i = popint();
  gen_label(magiclabel(i));
}

/* create terminating label  */
void gen_endif (void)
{
  int i;

  i = popint();
  gen_label(magiclabel(i));
}

/* create necessary instructions for a loop */
void gen_for ( char* symbol, double step)
{
  BSBytecode* code;
  int i;

  gen_sswap();
  gen_popsymbol (symbol);

  i = autolabel++;
  pushint(i);
  gen_label(magiclabel(i));

  gen_scopy();
  gen_pushsymbol (symbol);

  gen_sswap();

  if ( step > 0 ) gen_comp( BS_COMP_LE );
  else gen_comp( BS_COMP_GE );

  i = autolabel++;
  pushint(i);
  ADD_CODE(code);
  code->type = PCODE_IF;
  code->label = b_strdup(magiclabel(i));
}

/* loop termination */
void gen_next ( char* symbol, double step)
{
  int i;

  gen_pushsymbol (symbol);
  gen_pushnumber (step);
  gen_binop( '+' );
  gen_popsymbol (symbol);

  swapint();
  i = popint();
  gen_jump (magiclabel(i));
  i = popint();
  gen_label (magiclabel(i));

  gen_spop();
}

/* Generate while() starting label */
void gen_while_label(void)
{
  int sl = autolabel++;
  pushint(sl);
  gen_label(magiclabel(sl));
}

/* Create an end label, push that on the stack,
  then create a conditional branch which jumps to the end label
  if false. */
void gen_while(void)
{
 BSBytecode *code;
 int el = autolabel++;
 pushint(el);
 ADD_CODE(code);
 code->type = PCODE_IF;
 code->label = b_strdup(magiclabel(el));
}
/* Pop the start label and generate an unconditional jump
   to it. Then pop the end label and write it. */
void gen_wend(void)
{
 int sl, el;
 el = popint();
 sl = popint();
 gen_jump(magiclabel(sl));
 gen_label(magiclabel(el));
}

void gen_call( char* name, int argc )
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_CALL;
  code->label = b_strdup(name);
  code->argc = argc;
}

/* spawn for a new subroutine */
void begin_subroutine( char* name )
{
  // hack: to prevent accidential stepping thru the subroutine
  // FIXME better mark it with 'sub' flag or something ?
  gen_terminate();

  // FIXME check for nested sub
  // NOTE no need to strdup() cause gen_label does that
  gen_label( name );

  return;
}

/* end of a subroutine */
void gen_return()
{
  BSBytecode *code;

  ADD_CODE(code);
  code->type = PCODE_RETURN;
}

/* parse the script, return list of bytecodes */
BList* reaction_parse( char *script )
{
  /* reset local variables first */
  bytecodes = 0;
  autolabel = 0;
  compile_line_no = 1;
  compile_error_code = 0;
  intstack_count = 0;

  /* this is in lex.l */
  CXParse( script );

  /* if error, return NULL */
  if (compile_error_code)
  {
    /* FIXME deallocate ? */
    return NULL;
    /* compile_lineno */;
  }


  /* make sure there's PCODE_TERMINATE */
  gen_terminate();

  return bytecodes;
}

/* compiler error, to be called from yyparse() */
/* TO DO: create a verbose error handler */
void compile_error (long lineno, char* msg, char* yytext, int socket)
{
  //compile_error_code = CXERROR_PARSE;
  compile_error_code = -1;
  fprintf( stderr, "error line %ld: %s before '%s'\n", lineno, msg, yytext );
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 448 "gram.y"
typedef union YYSTYPE {
  char* symbol;
  double number;
  char* string;
  } YYSTYPE;
/* Line 191 of yacc.c.  */
#line 587 "gram.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 599 "gram.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   271

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  27
/* YYNRULES -- Number of rules. */
#define YYNRULES  83
/* YYNRULES -- Number of states. */
#define YYNSTATES  151

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,     2,
      47,    48,    38,    37,    35,    36,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    49,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    41,     2,    43,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      44,    45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     6,     8,    12,    13,    15,    17,    19,
      22,    24,    27,    29,    31,    33,    35,    39,    41,    44,
      48,    52,    54,    56,    58,    62,    64,    66,    68,    72,
      76,    80,    84,    88,    92,    96,   100,   104,   108,   111,
     114,   117,   120,   123,   128,   133,   134,   136,   140,   142,
     144,   145,   146,   155,   158,   159,   160,   172,   175,   176,
     177,   178,   186,   188,   191,   194,   196,   198,   202,   206,
     208,   209,   210,   214,   218,   222,   225,   229,   233,   237,
     241,   245,   249,   253
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      51,     0,    -1,    52,     7,    -1,    53,    -1,    52,     8,
      53,    -1,    -1,    57,    -1,    56,    -1,    54,    -1,    24,
      54,    -1,    55,    -1,    24,    55,    -1,    67,    -1,    70,
      -1,    58,    -1,    63,    -1,    31,    74,    75,    -1,    34,
      -1,    34,    57,    -1,     3,    14,    57,    -1,     4,    14,
      56,    -1,     4,    -1,    60,    -1,     6,    -1,    56,    37,
      56,    -1,     5,    -1,     3,    -1,    59,    -1,    47,    57,
      48,    -1,    57,     9,    57,    -1,    57,    37,    57,    -1,
      57,    36,    57,    -1,    57,    38,    57,    -1,    57,    39,
      57,    -1,    57,    40,    57,    -1,    57,    11,    57,    -1,
      57,    12,    57,    -1,    57,    13,    57,    -1,    36,    57,
      -1,    10,    57,    -1,    32,     3,    -1,    32,     4,    -1,
      33,    32,    -1,     3,    47,    61,    48,    -1,     4,    47,
      61,    48,    -1,    -1,    62,    -1,    61,    35,    62,    -1,
      57,    -1,    56,    -1,    -1,    -1,    20,    76,    64,    21,
      52,    65,    66,    23,    -1,    22,    52,    -1,    -1,    -1,
      25,     3,    14,    57,    26,    57,    69,    68,     8,    52,
      28,    -1,    27,    73,    -1,    -1,    -1,    -1,    29,    71,
      76,    72,     8,    52,    30,    -1,     5,    -1,    37,     5,
      -1,    36,     5,    -1,    57,    -1,    56,    -1,    74,    35,
      57,    -1,    74,    35,    56,    -1,    49,    -1,    -1,    -1,
      47,    76,    48,    -1,    76,    11,    76,    -1,    76,    12,
      76,    -1,    10,    76,    -1,    57,    14,    57,    -1,    57,
      15,    57,    -1,    57,    16,    57,    -1,    57,    17,    57,
      -1,    57,    18,    57,    -1,    57,    19,    57,    -1,    56,
      14,    56,    -1,    56,    15,    56,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   495,   495,   499,   500,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   516,   520,
     524,   528,   529,   530,   531,   535,   536,   537,   538,   539,
     540,   541,   542,   543,   544,   545,   546,   547,   548,   549,
     553,   554,   555,   560,   565,   570,   571,   572,   576,   577,
     581,   582,   581,   588,   589,   593,   593,   598,   599,   603,
     603,   603,   608,   608,   608,   611,   612,   613,   615,   620,
     621,   624,   625,   626,   627,   628,   629,   630,   631,   632,
     633,   634,   635,   636
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SYMBOL", "STRSYMBOL", "NUMBER",
  "STRING", "T_ENDOFFILE", "T_SEPARATOR", "T_MOD", "T_NOT", "T_OR",
  "T_AND", "T_XOR", "T_EQ", "T_NE", "T_LT", "T_LE", "T_GT", "T_GE", "T_IF",
  "T_THEN", "T_ELSE", "T_ENDIF", "T_LET", "T_FOR", "T_TO", "T_STEP",
  "T_NEXT", "T_WHILE", "T_WEND", "T_PRINT", "T_SUB", "T_END",
  "T_RANDOMIZE", "','", "'-'", "'+'", "'*'", "'/'", "'^'", "'|'", "'&'",
  "'~'", "UBITNOT", "UNOT", "UMINUS", "'('", "')'", "';'", "$accept",
  "program", "statement_list", "statement", "assignment",
  "string_assignment", "string_expression", "expression", "subroutine",
  "subroutine_call", "string_subroutine_call", "call_list", "call_item",
  "conditional", "@1", "@2", "conditional_else", "loop", "@3", "loopstep",
  "while_loop", "@4", "@5", "constant", "printlist", "semicolon",
  "comparison", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    44,    45,    43,    42,    47,
      94,   124,    38,   126,   290,   291,   292,    40,    41,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      55,    56,    56,    56,    56,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    58,    58,    59,    60,    61,    61,    61,    62,    62,
      64,    65,    63,    66,    66,    68,    67,    69,    69,    71,
      72,    70,    73,    73,    73,    74,    74,    74,    74,    75,
      75,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     2,     1,     3,     0,     1,     1,     1,     2,
       1,     2,     1,     1,     1,     1,     3,     1,     2,     3,
       3,     1,     1,     1,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     2,     2,     4,     4,     0,     1,     3,     1,     1,
       0,     0,     8,     2,     0,     0,    11,     2,     0,     0,
       0,     7,     1,     2,     2,     1,     1,     3,     3,     1,
       0,     0,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       5,    26,    21,    25,    23,     0,    71,     0,     0,    59,
       0,     0,     0,    17,     0,     0,     0,     0,     3,     8,
      10,     7,     6,    14,    27,    22,    15,    12,    13,     0,
      45,     0,    45,    26,    39,    21,    71,    71,     0,     0,
      50,     0,     0,     9,    11,     0,    71,    66,    65,    70,
      40,    41,    42,    18,    38,     0,     1,     2,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
      49,    48,     0,    46,    20,     0,    39,    75,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,    71,
       0,     0,    60,     0,    69,    16,    28,     4,    24,    29,
      35,    36,    37,    31,    30,    32,    33,    34,     0,    43,
      44,    72,    82,    83,    76,    77,    78,    79,    80,    81,
      73,    74,     5,     0,     0,    68,    67,    47,    51,     0,
       5,    54,    58,     0,     5,     0,     0,    55,    61,    53,
      52,    62,     0,     0,    57,     0,    64,    63,     5,     0,
      56
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    72,    73,    26,    90,   131,   135,    27,   145,   137,
      28,    46,   124,   144,    49,    95,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -105
static const short yypact[] =
{
     105,    -7,     0,  -105,  -105,     1,    86,    30,    25,  -105,
     139,    50,   -15,     1,     1,     1,    46,    60,  -105,  -105,
    -105,    57,   212,  -105,  -105,  -105,  -105,  -105,  -105,     1,
     139,    89,   139,    40,  -105,    54,    86,    86,     6,   193,
      88,    83,    90,  -105,  -105,    91,    86,    57,   212,    17,
    -105,  -105,  -105,   212,  -105,   155,  -105,  -105,   105,    89,
       1,     1,     1,     1,     1,     1,     1,     1,     1,   212,
      57,   212,   -12,  -105,    57,    -6,  -105,  -105,   142,    -9,
      89,    89,     1,     1,     1,     1,     1,     1,    86,    86,
      81,     1,    88,   139,  -105,  -105,  -105,  -105,  -105,   231,
     217,   217,   217,    34,    34,    66,    66,  -105,   139,  -105,
    -105,  -105,    57,    57,   226,   226,   226,   226,   226,   226,
    -105,  -105,   105,   161,    99,    57,   212,  -105,   104,     1,
     105,    92,   207,     8,   105,    93,    14,  -105,  -105,   104,
    -105,  -105,   108,   112,  -105,   110,  -105,  -105,   105,     7,
    -105
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
    -105,  -105,  -104,    63,   116,   119,    39,    -5,  -105,  -105,
    -105,   103,    23,  -105,  -105,  -105,  -105,  -105,  -105,  -105,
    -105,  -105,  -105,  -105,  -105,  -105,   -24
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
      34,    39,    88,    89,    33,    48,     3,    29,    53,    54,
      55,     5,    77,    79,    31,    58,    58,    52,   128,   141,
      80,    81,    92,   108,    69,    71,   133,    71,    45,   108,
     139,    76,    78,    41,    42,   150,   109,    14,   138,   111,
      30,    39,   110,    59,   149,    38,    56,    32,    15,    47,
     142,   143,    93,    50,    51,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   120,   121,    94,    57,    58,    70,
      74,    70,    66,    67,    68,    38,    38,   114,   115,   116,
     117,   118,   119,    39,    39,    38,   123,    30,   126,    33,
      35,     3,     4,    35,    59,     4,    36,    29,    98,    88,
      89,    32,   122,    71,    31,    91,    68,   130,     1,     2,
       3,     4,    58,   146,   134,     5,   140,   147,   148,   112,
     113,    97,    14,    43,   132,     6,    44,    38,    38,     7,
       8,   127,   125,    37,     9,    75,    10,    11,    12,    13,
       0,    14,    33,    35,     3,     4,     0,    70,     0,     5,
       0,    60,    15,    61,    62,    63,    82,    83,    84,    85,
      86,    87,     0,     0,    60,     0,    61,    62,    63,     0,
      60,     0,    61,    62,    63,    14,     0,     0,    64,    65,
      66,    67,    68,     0,     0,     0,    15,   129,     0,     0,
      96,    64,    65,    66,    67,    68,     0,    64,    65,    66,
      67,    68,    60,    96,    61,    62,    63,    82,    83,    84,
      85,    86,    87,     0,     0,     0,    60,     0,    61,    62,
      63,    60,     0,    61,    62,    63,    60,     0,     0,    64,
      65,    66,    67,    68,   136,    60,     0,     0,     0,    63,
       0,     0,     0,    64,    65,    66,    67,    68,    64,    65,
      66,    67,    68,    64,    65,    66,    67,    68,     0,     0,
       0,     0,    64,    65,    66,    67,    68,    64,    65,    66,
      67,    68
};

static const short yycheck[] =
{
       5,     6,    11,    12,     3,    10,     5,    14,    13,    14,
      15,    10,    36,    37,    14,     8,     8,    32,   122,     5,
      14,    15,    46,    35,    29,    30,   130,    32,     3,    35,
     134,    36,    37,     3,     4,    28,    48,    36,    30,    48,
      47,    46,    48,    37,   148,     6,     0,    47,    47,    10,
      36,    37,    35,     3,     4,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    88,    89,    49,     7,     8,    30,
      31,    32,    38,    39,    40,    36,    37,    82,    83,    84,
      85,    86,    87,    88,    89,    46,    91,    47,    93,     3,
       4,     5,     6,     4,    37,     6,    10,    14,    59,    11,
      12,    47,    21,   108,    14,    14,    40,     8,     3,     4,
       5,     6,     8,     5,    22,    10,    23,     5,     8,    80,
      81,    58,    36,     7,   129,    20,     7,    88,    89,    24,
      25,   108,    93,    47,    29,    32,    31,    32,    33,    34,
      -1,    36,     3,     4,     5,     6,    -1,   108,    -1,    10,
      -1,     9,    47,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    -1,     9,    -1,    11,    12,    13,    -1,
       9,    -1,    11,    12,    13,    36,    -1,    -1,    36,    37,
      38,    39,    40,    -1,    -1,    -1,    47,    26,    -1,    -1,
      48,    36,    37,    38,    39,    40,    -1,    36,    37,    38,
      39,    40,     9,    48,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    -1,    -1,    -1,     9,    -1,    11,    12,
      13,     9,    -1,    11,    12,    13,     9,    -1,    -1,    36,
      37,    38,    39,    40,    27,     9,    -1,    -1,    -1,    13,
      -1,    -1,    -1,    36,    37,    38,    39,    40,    36,    37,
      38,    39,    40,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    40,    36,    37,    38,
      39,    40
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     3,     4,     5,     6,    10,    20,    24,    25,    29,
      31,    32,    33,    34,    36,    47,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    63,    67,    70,    14,
      47,    14,    47,     3,    57,     4,    10,    47,    56,    57,
      76,     3,     4,    54,    55,     3,    71,    56,    57,    74,
       3,     4,    32,    57,    57,    57,     0,     7,     8,    37,
       9,    11,    12,    13,    36,    37,    38,    39,    40,    57,
      56,    57,    61,    62,    56,    61,    57,    76,    57,    76,
      14,    15,    14,    15,    16,    17,    18,    19,    11,    12,
      64,    14,    76,    35,    49,    75,    48,    53,    56,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    35,    48,
      48,    48,    56,    56,    57,    57,    57,    57,    57,    57,
      76,    76,    21,    57,    72,    56,    57,    62,    52,    26,
       8,    65,    57,    52,    22,    66,    27,    69,    30,    52,
      23,     5,    36,    37,    73,    68,     5,     5,     8,    52,
      28
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 495 "gram.y"
    { YYACCEPT; }
    break;

  case 6:
#line 504 "gram.y"
    { gen_spop(); }
    break;

  case 7:
#line 505 "gram.y"
    { gen_spop(); }
    break;

  case 17:
#line 515 "gram.y"
    { gen_call("RANDOMIZE",0); gen_spop(); }
    break;

  case 18:
#line 516 "gram.y"
    { gen_call("RANDOMIZE",1); gen_spop(); }
    break;

  case 19:
#line 520 "gram.y"
    { gen_popsymbol(yyvsp[-2].symbol);b_free(yyvsp[-2].symbol); }
    break;

  case 20:
#line 524 "gram.y"
    { gen_popsymbol(yyvsp[-2].symbol);b_free(yyvsp[-2].symbol); }
    break;

  case 21:
#line 528 "gram.y"
    { gen_pushsymbol(yyvsp[0].symbol);b_free(yyvsp[0].symbol); }
    break;

  case 23:
#line 530 "gram.y"
    { gen_pushstring(yyvsp[0].string); b_free(yyvsp[0].string); }
    break;

  case 24:
#line 531 "gram.y"
    { gen_binop('#'); }
    break;

  case 25:
#line 535 "gram.y"
    { gen_pushnumber(yyvsp[0].number); }
    break;

  case 26:
#line 536 "gram.y"
    { gen_pushsymbol(yyvsp[0].symbol);b_free(yyvsp[0].symbol); }
    break;

  case 29:
#line 539 "gram.y"
    { gen_binop('%'); }
    break;

  case 30:
#line 540 "gram.y"
    { gen_binop('+'); }
    break;

  case 31:
#line 541 "gram.y"
    { gen_binop('-'); }
    break;

  case 32:
#line 542 "gram.y"
    { gen_binop('*'); }
    break;

  case 33:
#line 543 "gram.y"
    { gen_binop('/'); }
    break;

  case 34:
#line 544 "gram.y"
    { gen_binop('!'); }
    break;

  case 35:
#line 545 "gram.y"
    { gen_binop('|'); }
    break;

  case 36:
#line 546 "gram.y"
    { gen_binop('&'); }
    break;

  case 37:
#line 547 "gram.y"
    { gen_binop('^'); }
    break;

  case 38:
#line 548 "gram.y"
    { gen_unop('-');}
    break;

  case 39:
#line 549 "gram.y"
    { gen_unop('~'); }
    break;

  case 40:
#line 553 "gram.y"
    { begin_subroutine(yyvsp[0].symbol);b_free(yyvsp[0].symbol); }
    break;

  case 41:
#line 554 "gram.y"
    { begin_subroutine(yyvsp[0].symbol);b_free(yyvsp[0].symbol); }
    break;

  case 42:
#line 555 "gram.y"
    { gen_return(); }
    break;

  case 43:
#line 560 "gram.y"
    { gen_call(yyvsp[-3].symbol,yyvsp[-1].number); b_free(yyvsp[-3].symbol); }
    break;

  case 44:
#line 565 "gram.y"
    { gen_call(yyvsp[-3].symbol,yyvsp[-1].number); b_free(yyvsp[-3].symbol); }
    break;

  case 45:
#line 570 "gram.y"
    { yyval.number = 0; }
    break;

  case 46:
#line 571 "gram.y"
    { yyval.number = 1; }
    break;

  case 47:
#line 572 "gram.y"
    { yyval.number = yyvsp[-2].number + 1; }
    break;

  case 50:
#line 581 "gram.y"
    { gen_if(); }
    break;

  case 51:
#line 582 "gram.y"
    { gen_then(); }
    break;

  case 52:
#line 584 "gram.y"
    { gen_endif(); }
    break;

  case 55:
#line 593 "gram.y"
    { gen_for (yyvsp[-5].symbol, yyvsp[0].number); }
    break;

  case 56:
#line 594 "gram.y"
    { gen_next(yyvsp[-9].symbol, yyvsp[-4].number);b_free(yyvsp[-9].symbol); }
    break;

  case 57:
#line 598 "gram.y"
    { yyval.number = yyvsp[0].number; }
    break;

  case 58:
#line 599 "gram.y"
    { yyval.number = 1.0; }
    break;

  case 59:
#line 603 "gram.y"
    { gen_while_label(); }
    break;

  case 60:
#line 603 "gram.y"
    { gen_while(); }
    break;

  case 61:
#line 604 "gram.y"
    { gen_wend(); }
    break;

  case 62:
#line 608 "gram.y"
    {yyval.number=yyvsp[0].number;}
    break;

  case 63:
#line 608 "gram.y"
    {yyval.number=yyvsp[0].number;}
    break;

  case 64:
#line 608 "gram.y"
    {yyval.number=-yyvsp[0].number;}
    break;

  case 65:
#line 611 "gram.y"
    { gen_print(); }
    break;

  case 66:
#line 612 "gram.y"
    { gen_print(); }
    break;

  case 67:
#line 614 "gram.y"
    { gen_pushstring(" "); gen_print(); gen_print(); }
    break;

  case 68:
#line 616 "gram.y"
    { gen_pushstring(" "); gen_print(); gen_print(); }
    break;

  case 70:
#line 621 "gram.y"
    { gen_pushstring("\n");gen_print(); }
    break;

  case 73:
#line 626 "gram.y"
    { gen_comp(BS_COMP_OR); }
    break;

  case 74:
#line 627 "gram.y"
    { gen_comp(BS_COMP_AND); }
    break;

  case 75:
#line 628 "gram.y"
    { gen_comp(BS_COMP_NOT); }
    break;

  case 76:
#line 629 "gram.y"
    { gen_comp(BS_COMP_EQ);  }
    break;

  case 77:
#line 630 "gram.y"
    { gen_comp(BS_COMP_NE);  }
    break;

  case 78:
#line 631 "gram.y"
    { gen_comp(BS_COMP_LT);  }
    break;

  case 79:
#line 632 "gram.y"
    { gen_comp(BS_COMP_LE);  }
    break;

  case 80:
#line 633 "gram.y"
    { gen_comp(BS_COMP_GT);  }
    break;

  case 81:
#line 634 "gram.y"
    { gen_comp(BS_COMP_GE);  }
    break;

  case 82:
#line 635 "gram.y"
    { gen_comp(BS_COMP_SEQ); }
    break;

  case 83:
#line 636 "gram.y"
    { gen_comp(BS_COMP_SNE); }
    break;


    }

/* Line 1000 of yacc.c.  */
#line 1946 "gram.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 638 "gram.y"


