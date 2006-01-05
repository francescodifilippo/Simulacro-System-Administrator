/*  This file is part of the BScript project
    Copyright (C) 1999-2004 Ariya Hidayat <ariya@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#ifndef BSCRIPT_H
#define BSCRIPT_H

#include "blib.h"

typedef struct _BSInterpreter BSInterpreter;
struct _BSInterpreter
{
  char *name;
};

BSInterpreter* bs_interpreter_create();
void bs_interpreter_destroy( BSInterpreter* );
void bs_interpreter_run( BSInterpreter*, char*, int socket );
void bs_interpreter_run_file( BSInterpreter*, char*, int socket );

typedef struct _BSSymbol BSSymbol;
struct _BSSymbol
{
  char* name;
  int type;
  double number;
  char* string;
};

typedef struct _BSModule BSModule;
struct _BSModule
{
  char *name;
  char *code;
  BList *bytecodes;
  BHash *objects;
  BHash *builtin_functions;
};


BSModule* bs_module_create( char *name );
void bs_module_destroy( BSModule *module );
void bs_module_set_code( BSModule *module, char* code, int socket );
void bs_module_load_file( BSModule *module, char* filename, int socket );
void bs_module_execute ( BSModule *module, int socket );
void bs_module_dump ( BSModule *module );
BSSymbol* bs_module_access_symbol( BSModule *module, char *name );

typedef struct _BSContext BSContext;
struct _BSContext
{
  BSModule *module;
  void *stack;
  int program_counter;
  BVariant *result;
};

BSContext* bs_context_create( BSModule *module );
void bs_context_destroy( BSContext *context );
void bs_context_execute( BSContext *context , int socket);
void bs_context_dump( BSContext *context );

int bs_eval_user_function( BSContext *context, char *function, int narg );
int bs_eval_builtin_function( BSContext *context, char *function, int narg );

typedef struct _BSBytecode BSBytecode;
struct _BSBytecode
{
  int type;        /* type of bytecode */
  int argc;        /* no of arg for function call */
  char op;         /* operator type */
  char *label;     /* label for jump/call */
  BVariant *value; /* immediate value to push */
  char *symbol;    /* symbol to push/pop */
};

#endif
