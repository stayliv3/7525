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
     STMT_NO_ARGS = 258,
     STMT_ONE_ARG = 259,
     STMT_TWO_ARGS = 260,
     MIMETYPE = 261,
     STRING = 262,
     INTEGER = 263
   };
#endif
#define STMT_NO_ARGS 258
#define STMT_ONE_ARG 259
#define STMT_TWO_ARGS 260
#define MIMETYPE 261
#define STRING 262
#define INTEGER 263




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 47 "boa_grammar.y"
typedef union YYSTYPE {
    char *	sval;
    int		ival;
    struct ccommand * cval;
} YYSTYPE;
/* Line 1275 of yacc.c.  */
#line 59 "y.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;



