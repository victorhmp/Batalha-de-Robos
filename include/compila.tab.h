/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMt = 258,
     ID = 259,
     ADDt = 260,
     SUBt = 261,
     MULt = 262,
     DIVt = 263,
     ASGN = 264,
     OPEN = 265,
     CLOSE = 266,
     RETt = 267,
     EOL = 268,
     EQt = 269,
     NEt = 270,
     LTt = 271,
     LEt = 272,
     GTt = 273,
     GEt = 274,
     ABRE = 275,
     FECHA = 276,
     SEP = 277,
     IF = 278,
     WHILE = 279,
     FUNC = 280,
     PRINT = 281,
     NEG = 282,
     PWR = 283
   };
#endif
/* Tokens.  */
#define NUMt 258
#define ID 259
#define ADDt 260
#define SUBt 261
#define MULt 262
#define DIVt 263
#define ASGN 264
#define OPEN 265
#define CLOSE 266
#define RETt 267
#define EOL 268
#define EQt 269
#define NEt 270
#define LTt 271
#define LEt 272
#define GTt 273
#define GEt 274
#define ABRE 275
#define FECHA 276
#define SEP 277
#define IF 278
#define WHILE 279
#define FUNC 280
#define PRINT 281
#define NEG 282
#define PWR 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 24 "./src/compila.y"
{
  double val;
  /* symrec *cod; */
  char cod[30];
}
/* Line 1529 of yacc.c.  */
#line 111 "compila.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

