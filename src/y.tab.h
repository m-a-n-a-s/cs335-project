/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR = 258,
    CONST = 259,
    CASE = 260,
    CONTINUE = 261,
    DEFAULT = 262,
    DO = 263,
    DOUBLE = 264,
    ELSE = 265,
    ENUM = 266,
    EXTERN = 267,
    FLOAT = 268,
    FOR = 269,
    IF = 270,
    INLINE = 271,
    INT = 272,
    LONG = 273,
    IFX = 274,
    REGISTER = 275,
    RESTRICT = 276,
    RETURN = 277,
    SHORT = 278,
    SIGNED = 279,
    STATIC = 280,
    STRUCT = 281,
    SWITCH = 282,
    TYPEDEF = 283,
    UNION = 284,
    UNSIGNED = 285,
    VOID = 286,
    VOLATILE = 287,
    WHILE = 288,
    ALIGNAS = 289,
    ALIGNOF = 290,
    ATOMIC = 291,
    BOOL = 292,
    COMPLEX = 293,
    GENERIC = 294,
    IMAGINARY = 295,
    NORETURN = 296,
    STATIC_ASSERT = 297,
    THREAD_LOCAL = 298,
    FUNC_NAME = 299,
    AUTO = 300,
    BREAK = 301,
    GOTO = 302,
    TYPEDEF_NAME = 303,
    IDENTIFIER = 304,
    CONSTANT = 305,
    ENUMERATION_CONSTANT = 306,
    STRING_LITERAL = 307,
    PTR_OP = 308,
    INC_OP = 309,
    DEC_OP = 310,
    LEFT_OP = 311,
    RIGHT_OP = 312,
    LE_OP = 313,
    GE_OP = 314,
    EQ_OP = 315,
    NE_OP = 316,
    AND_OP = 317,
    OR_OP = 318,
    MUL_ASSIGN = 319,
    DIV_ASSIGN = 320,
    MOD_ASSIGN = 321,
    ADD_ASSIGN = 322,
    SUB_ASSIGN = 323,
    LEFT_ASSIGN = 324,
    RIGHT_ASSIGN = 325,
    AND_ASSIGN = 326,
    XOR_ASSIGN = 327,
    OR_ASSIGN = 328,
    TYPE_NAME = 329,
    ELLIPSIS = 330,
    SIZEOF = 331
  };
#endif
/* Tokens.  */
#define CHAR 258
#define CONST 259
#define CASE 260
#define CONTINUE 261
#define DEFAULT 262
#define DO 263
#define DOUBLE 264
#define ELSE 265
#define ENUM 266
#define EXTERN 267
#define FLOAT 268
#define FOR 269
#define IF 270
#define INLINE 271
#define INT 272
#define LONG 273
#define IFX 274
#define REGISTER 275
#define RESTRICT 276
#define RETURN 277
#define SHORT 278
#define SIGNED 279
#define STATIC 280
#define STRUCT 281
#define SWITCH 282
#define TYPEDEF 283
#define UNION 284
#define UNSIGNED 285
#define VOID 286
#define VOLATILE 287
#define WHILE 288
#define ALIGNAS 289
#define ALIGNOF 290
#define ATOMIC 291
#define BOOL 292
#define COMPLEX 293
#define GENERIC 294
#define IMAGINARY 295
#define NORETURN 296
#define STATIC_ASSERT 297
#define THREAD_LOCAL 298
#define FUNC_NAME 299
#define AUTO 300
#define BREAK 301
#define GOTO 302
#define TYPEDEF_NAME 303
#define IDENTIFIER 304
#define CONSTANT 305
#define ENUMERATION_CONSTANT 306
#define STRING_LITERAL 307
#define PTR_OP 308
#define INC_OP 309
#define DEC_OP 310
#define LEFT_OP 311
#define RIGHT_OP 312
#define LE_OP 313
#define GE_OP 314
#define EQ_OP 315
#define NE_OP 316
#define AND_OP 317
#define OR_OP 318
#define MUL_ASSIGN 319
#define DIV_ASSIGN 320
#define MOD_ASSIGN 321
#define ADD_ASSIGN 322
#define SUB_ASSIGN 323
#define LEFT_ASSIGN 324
#define RIGHT_ASSIGN 325
#define AND_ASSIGN 326
#define XOR_ASSIGN 327
#define OR_ASSIGN 328
#define TYPE_NAME 329
#define ELLIPSIS 330
#define SIZEOF 331

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "src/comp.y" /* yacc.c:1909  */

  int number;     /*integer value*/
  char* str;
  struct node *ptr;     /*node pointer */

#line 212 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
