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
     INT = 258,
     BOOL = 259,
     FLOAT = 260,
     VEC2 = 261,
     VEC3 = 262,
     VEC4 = 263,
     BVEC2 = 264,
     BVEC3 = 265,
     BVEC4 = 266,
     IVEC2 = 267,
     IVEC3 = 268,
     IVEC4 = 269,
     DP3 = 270,
     LIT = 271,
     RSQ = 272,
     PLUS = 273,
     MINUS = 274,
     MULT = 275,
     DIV = 276,
     POW = 277,
     ASSIGN = 278,
     TRUE_V = 279,
     FALSE_V = 280,
     INT_V = 281,
     FLOAT_V = 282,
     NOT = 283,
     AND = 284,
     OR = 285,
     EQ = 286,
     NEQ = 287,
     LT = 288,
     LE = 289,
     GT = 290,
     GE = 291,
     LP = 292,
     RP = 293,
     LB = 294,
     RB = 295,
     LBR = 296,
     RBR = 297,
     IF = 298,
     ELSE = 299,
     WHILE = 300,
     CONST = 301,
     ID = 302,
     SEMI = 303,
     COMMA = 304
   };
#endif
/* Tokens.  */
#define INT 258
#define BOOL 259
#define FLOAT 260
#define VEC2 261
#define VEC3 262
#define VEC4 263
#define BVEC2 264
#define BVEC3 265
#define BVEC4 266
#define IVEC2 267
#define IVEC3 268
#define IVEC4 269
#define DP3 270
#define LIT 271
#define RSQ 272
#define PLUS 273
#define MINUS 274
#define MULT 275
#define DIV 276
#define POW 277
#define ASSIGN 278
#define TRUE_V 279
#define FALSE_V 280
#define INT_V 281
#define FLOAT_V 282
#define NOT 283
#define AND 284
#define OR 285
#define EQ 286
#define NEQ 287
#define LT 288
#define LE 289
#define GT 290
#define GE 291
#define LP 292
#define RP 293
#define LB 294
#define RB 295
#define LBR 296
#define RBR 297
#define IF 298
#define ELSE 299
#define WHILE 300
#define CONST 301
#define ID 302
#define SEMI 303
#define COMMA 304




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 58 "parser.y"
{
  int num;
}
/* Line 1529 of yacc.c.  */
#line 151 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

