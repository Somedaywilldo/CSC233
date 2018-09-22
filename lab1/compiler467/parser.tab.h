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
     BTRUE = 279,
     BFALSE = 280,
     NOT = 281,
     AND = 282,
     OR = 283,
     EQ = 284,
     NEQ = 285,
     LT = 286,
     LE = 287,
     GT = 288,
     GE = 289,
     LP = 290,
     RP = 291,
     LB = 292,
     RB = 293,
     LBR = 294,
     RBR = 295,
     IF = 296,
     ELSE = 297,
     WHILE = 298,
     CONST = 299,
     ID = 300,
     SEMI = 301,
     COMMA = 302
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
#define BTRUE 279
#define BFALSE 280
#define NOT 281
#define AND 282
#define OR 283
#define EQ 284
#define NEQ 285
#define LT 286
#define LE 287
#define GT 288
#define GE 289
#define LP 290
#define RP 291
#define LB 292
#define RB 293
#define LBR 294
#define RBR 295
#define IF 296
#define ELSE 297
#define WHILE 298
#define CONST 299
#define ID 300
#define SEMI 301
#define COMMA 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 58 "parser.y"
{
  int num;
}
/* Line 1529 of yacc.c.  */
#line 147 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

