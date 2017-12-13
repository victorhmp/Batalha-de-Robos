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
     DIRt = 260,
     ADDt = 261,
     SUBt = 262,
     MULt = 263,
     DIVt = 264,
     ASGN = 265,
     OPEN = 266,
     CLOSE = 267,
     RETt = 268,
     EOL = 269,
     MOVEt = 270,
     DEPOSt = 271,
     RECOt = 272,
     ATAt = 273,
     ATRt = 274,
     EQt = 275,
     NEt = 276,
     LTt = 277,
     LEt = 278,
     GTt = 279,
     GEt = 280,
     ABRE = 281,
     FECHA = 282,
     SEP = 283,
     IF = 284,
     WHILE = 285,
     FUNC = 286,
     PRINT = 287,
     NEG = 288,
     PWR = 289
   };
#endif
/* Tokens.  */
#define NUMt 258
#define ID 259
#define DIRt 260
#define ADDt 261
#define SUBt 262
#define MULt 263
#define DIVt 264
#define ASGN 265
#define OPEN 266
#define CLOSE 267
#define RETt 268
#define EOL 269
#define MOVEt 270
#define DEPOSt 271
#define RECOt 272
#define ATAt 273
#define ATRt 274
#define EQt 275
#define NEt 276
#define LTt 277
#define LEt 278
#define GTt 279
#define GEt 280
#define ABRE 281
#define FECHA 282
#define SEP 283
#define IF 284
#define WHILE 285
#define FUNC 286
#define PRINT 287
#define NEG 288
#define PWR 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 33 "./src/compila.y"
{
  double val;
  /* symrec *cod; */
  char cod[30];
}
/* Line 1529 of yacc.c.  */
#line 123 "compila.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

