/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/comp.y" /* yacc.c:339  */

// #include "functions.h"
#include "typecheck.h"
#include <iostream>
#include <cstring>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
using namespace std;

int yylex(void);
void yyerror(char *s,...);

#line 82 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 17 "src/comp.y" /* yacc.c:355  */

  int number;     /*integer value*/
  char* str;
  struct node *ptr;     /*node pointer */

#line 280 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 297 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1357

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  101
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  72
/* YYNRULES -- Number of rules.  */
#define YYNRULES  220
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  374

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   331

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    97,     2,     2,     2,    88,    95,     2,
      84,    85,    90,    86,    76,    87,    91,    89,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    99,    79,
      93,    96,    92,   100,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    82,     2,    83,    77,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    80,    78,    81,    98,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    94
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    84,    87,    91,    95,    97,   112,   131,
     180,   189,   202,   215,   230,   231,   241,   242,   254,   266,
     278,   279,   283,   284,   285,   286,   287,   288,   292,   293,
     300,   302,   322,   345,   360,   361,   386,   411,   412,   423,
     439,   440,   455,   469,   484,   500,   501,   512,   525,   526,
     541,   542,   558,   559,   591,   615,   616,   623,   624,   632,
     633,   649,   650,   666,   667,   668,   669,   670,   671,   672,
     673,   674,   675,   676,   680,   681,   685,   689,   690,   694,
     695,   696,   697,   698,   699,   703,   704,   708,   725,   748,
     749,   750,   751,   752,   756,   759,   762,   765,   768,   771,
     774,   777,   780,   783,   786,   789,   795,   802,   810,   819,
     824,   825,   829,   830,   834,   838,   839,   840,   841,   845,
     846,   850,   852,   853,   858,   859,   860,   864,   865,   869,
     870,   874,   875,   879,   886,   891,   897,   902,   904,   916,
     928,   934,   948,   953,   954,   955,   956,   960,   961,   966,
     967,   973,   974,   978,   991,   992,   996,   997,  1001,  1002,
    1006,  1007,  1008,  1012,  1013,  1014,  1015,  1016,  1017,  1018,
    1019,  1020,  1024,  1025,  1026,  1032,  1033,  1049,  1050,  1051,
    1052,  1053,  1054,  1058,  1059,  1060,  1064,  1065,  1073,  1081,
    1085,  1100,  1101,  1105,  1106,  1110,  1111,  1115,  1127,  1128,
    1129,  1133,  1146,  1159,  1160,  1161,  1162,  1166,  1167,  1168,
    1169,  1170,  1174,  1175,  1179,  1180,  1185,  1194,  1202,  1205,
    1211
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "CONST", "CASE", "CONTINUE",
  "DEFAULT", "DO", "DOUBLE", "ELSE", "ENUM", "EXTERN", "FLOAT", "FOR",
  "IF", "INLINE", "INT", "LONG", "IFX", "REGISTER", "RESTRICT", "RETURN",
  "SHORT", "SIGNED", "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION",
  "UNSIGNED", "VOID", "VOLATILE", "WHILE", "ALIGNAS", "ALIGNOF", "ATOMIC",
  "BOOL", "COMPLEX", "GENERIC", "IMAGINARY", "NORETURN", "STATIC_ASSERT",
  "THREAD_LOCAL", "FUNC_NAME", "AUTO", "BREAK", "GOTO", "TYPEDEF_NAME",
  "IDENTIFIER", "CONSTANT", "ENUMERATION_CONSTANT", "STRING_LITERAL",
  "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPE_NAME", "ELLIPSIS", "','",
  "'^'", "'|'", "';'", "'{'", "'}'", "'['", "']'", "'('", "')'", "'+'",
  "'-'", "'%'", "'/'", "'*'", "'.'", "'>'", "'<'", "SIZEOF", "'&'", "'='",
  "'!'", "'~'", "':'", "'?'", "$accept", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "M", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "E5", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "E3", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "statement", "labeled_statement",
  "compound_statement", "E1", "declaration_list", "statement_list",
  "expression_statement", "M4", "selection_statement", "M6", "M7",
  "iteration_statement", "jump_statement", "translation_unit",
  "external_declaration", "function_definition", "E2", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,    44,    94,   124,    59,
     123,   125,    91,    93,    40,    41,    43,    45,    37,    47,
      42,    46,    62,    60,   331,    38,    61,    33,   126,    58,
      63
};
# endif

#define YYPACT_NINF -230

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-230)))

#define YYTABLE_NINF -110

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     708,  -230,  -230,  -230,   -27,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,  -230,
    -230,  -230,   -28,    15,  -230,   -25,   962,   962,  -230,    -4,
    -230,   962,   896,   -53,   -24,    79,  -230,  -230,    26,    65,
      42,  -230,  -230,    15,  -230,   -30,  -230,    39,  -230,  -230,
      85,   119,  -230,   807,  -230,   -25,  -230,   348,   136,   980,
    -230,   -53,  -230,   708,    65,    83,    -5,  -230,  -230,  -230,
    -230,   -28,  -230,   996,   896,   146,   995,  -230,   499,   137,
    1194,   123,   133,  -230,   151,   153,  1046,   154,   155,   161,
     192,   143,  -230,  -230,  1244,  1244,  -230,   444,  -230,  -230,
    -230,  1259,  -230,  -230,  -230,  -230,    28,   318,  1194,  -230,
     122,   107,   150,   112,   162,   148,   167,   173,   190,   -37,
    -230,  -230,    49,  -230,  -230,  -230,   174,   175,  -230,  -230,
    -230,  -230,  -230,   962,  -230,  -230,  -230,  -230,  -230,   171,
     738,  -230,    14,  1194,    65,  -230,  -230,   996,  -230,  -230,
    -230,   136,   995,   995,   837,  -230,   -29,   995,   176,   159,
    -230,   499,   499,  1063,  1194,  -230,    99,  1194,  -230,  -230,
     180,  -230,  1194,  -230,  -230,    -1,    78,   178,   444,  -230,
     211,  -230,  -230,  1194,  1113,   212,  -230,  -230,  -230,  -230,
    -230,  -230,  -230,  -230,  -230,  -230,  -230,  1194,  -230,  1194,
    1194,  1194,  1194,  1194,  1194,  1194,  1194,  1194,  1194,  1194,
    1194,  1194,  1194,  1194,  1194,  1194,  1194,  1194,  1194,  -230,
    -230,  -230,   499,   499,  -230,  -230,  -230,  -230,   -10,   181,
     189,  -230,    31,  -230,  -230,  -230,  -230,    45,  -230,   861,
    -230,  -230,  -230,  1194,   104,  -230,   168,  -230,  -230,   499,
    -230,   237,  -230,    32,  -230,    96,  1194,  -230,   499,  -230,
    1129,   625,     7,  -230,    47,  1194,   188,  -230,   -41,  -230,
     100,  -230,  -230,  -230,  -230,  -230,  -230,   122,   122,   107,
     107,   150,   150,   150,   150,   112,   112,   162,   148,   167,
     173,   190,   -33,  -230,  -230,   266,   595,  -230,    38,  -230,
    -230,   927,   232,  -230,   201,  -230,  -230,  -230,   -29,  -230,
    1194,  -230,   200,  1063,  -230,   499,   209,   202,  -230,  -230,
     205,  -230,   206,   207,    47,  1179,   777,  -230,  -230,  -230,
    1194,  -230,  1194,  -230,  -230,  -230,  -230,  -230,   996,  -230,
    -230,  -230,  -230,   210,  -230,  -230,  -230,  -230,  -230,  -230,
     213,  -230,   214,  -230,  -230,   499,  -230,  1194,  -230,  1194,
     499,  -230,  -230,  -230,   215,   499,   106,  -230,   222,  -230,
    -230,  -230,   499,  -230
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    95,   131,   100,     0,    90,    99,    97,    98,    93,
      96,   101,    91,   110,    89,   111,   102,    94,   132,    92,
     135,   105,     0,   143,   215,     0,    79,    81,   103,   109,
     104,    83,     0,   134,     0,    54,   212,   214,   126,     0,
       0,   147,   145,   144,    77,     0,    85,   220,    80,    82,
     108,     0,    84,   190,   191,     0,   219,     0,    54,     0,
     142,   133,     1,     0,     0,   129,     0,   127,   136,   148,
     146,     0,    78,     0,     0,     0,     0,   186,    54,    87,
       0,     0,     0,    54,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     4,     0,     0,   195,     0,    24,    25,
      23,     0,    22,    27,    26,     6,    16,    28,     0,    30,
      34,    37,    40,    45,    48,    50,    52,    55,    57,    59,
      61,    74,     0,   193,   177,   178,    54,    54,   179,    54,
     180,   181,   182,     0,   218,     2,   138,    28,    76,     0,
       0,   213,     0,     0,     0,   124,    86,     0,   172,    88,
     217,    54,     0,   116,     0,   112,     0,   118,    54,     0,
     208,     0,     0,     0,     0,   210,     0,     0,    54,   209,
       0,    54,     0,    17,    18,     0,   158,     0,     0,    20,
       0,    12,    13,     0,     0,     0,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    63,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   196,
     188,   187,     0,     0,   192,   137,   156,   141,   155,     0,
     149,   151,     0,   125,   130,   128,   175,     0,   216,     0,
     115,   107,   113,     0,     0,   119,   121,   117,   189,     0,
     185,     0,    54,     0,   211,     0,     0,   207,     0,     5,
       0,     0,   160,   159,   161,     0,     0,    11,     0,     8,
       0,    14,    10,    62,    33,    32,    31,    35,    36,    38,
      39,    43,    44,    42,    41,    46,    47,    49,    51,    53,
      56,    58,     0,    75,   194,   199,     0,   153,   160,   154,
     139,     0,     0,   140,    54,   173,   106,   122,     0,   114,
       0,   184,     0,     0,   197,     0,   201,     0,   183,   164,
       0,   168,     0,     0,   162,     0,     0,    29,    21,     7,
       0,     9,     0,    54,   150,   152,   157,   174,     0,   120,
     123,    54,   202,    54,   200,    54,   165,   169,   163,   166,
       0,   170,     0,    15,    60,     0,   176,     0,    54,     0,
       0,   167,   171,   198,     0,     0,     0,   203,     0,   205,
      54,   204,     0,   206
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -230,  -230,  -230,  -230,   -57,  -230,   -99,    22,    24,    12,
      20,    82,    77,    89,    90,   -35,    88,  -230,   -46,   -23,
    -230,   -79,   -76,    40,     1,  -230,   238,  -230,    93,  -230,
     261,  -230,   160,  -143,   -80,  -230,     5,  -230,   250,   172,
      35,   -19,   -26,  -230,   -13,  -230,  -128,  -230,    16,  -230,
     140,  -160,  -229,  -142,  -230,   -22,  -230,   -17,  -230,    56,
     241,  -149,  -230,  -230,   -36,  -230,  -230,  -230,  -230,   257,
    -230,  -230
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   105,   106,   270,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   133,   118,   119,   120,   121,
     197,   122,   139,    54,    55,    45,    46,    26,    27,    28,
      51,    29,   154,   155,   156,   244,   245,    30,    66,    67,
      31,    32,    33,   140,    34,    43,   322,   230,   231,   232,
     177,   323,   264,   149,   237,   123,   124,   125,    57,    58,
     127,   128,   129,   130,   317,   343,   131,   132,    35,    36,
      37,    74
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      63,    25,   137,    40,   159,   236,    47,   166,    61,   198,
      42,   242,   229,   138,   252,    56,   263,   176,   175,     2,
      20,    20,    38,   137,    20,    20,   216,    48,    49,    59,
      70,    60,    52,   324,   138,   218,    79,   173,   174,    20,
      24,   134,   329,   218,   179,    50,    71,    18,   162,    72,
     148,   137,    79,    39,    44,    22,    22,   150,    41,    22,
      22,    23,    23,   217,    25,    23,   332,   234,   299,   324,
     243,   144,   260,   240,   296,   218,   145,   247,    69,    62,
      23,   180,   181,   182,   259,   253,   137,    20,   255,   260,
     144,   261,   222,   175,   223,   233,   242,   138,   176,   175,
     274,   275,   276,    24,   268,    23,    64,   302,   218,    78,
     183,   157,   184,   126,    65,   -87,   303,   314,   -87,   185,
     260,   304,   296,   222,   148,   218,   305,    68,   219,   325,
     151,   326,   157,   256,   238,    73,   258,   246,   292,   250,
     251,   228,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     260,   271,   261,   262,   342,  -109,   327,   307,    23,   153,
     206,   207,   218,   224,   273,   218,   330,   316,   254,   143,
     308,   315,   218,   309,   320,   331,   137,   157,   157,   157,
     153,   370,   157,   202,   203,   293,   356,   138,   352,    76,
     294,   295,   160,   137,   208,   209,   204,   205,   137,   297,
     199,   200,   201,   157,   138,   298,    53,   313,   281,   282,
     283,   284,   210,   211,   277,   278,   152,   311,   279,   280,
     285,   286,   161,    73,   340,   163,   318,   164,   167,   168,
     169,   170,   171,   212,   213,   153,   153,   153,   262,   350,
     153,   214,   215,   137,   225,   220,   221,   248,   249,   257,
     267,   272,   228,   265,   138,   301,   300,   310,   137,   338,
     312,   153,    61,   328,   157,   137,   333,    40,   316,   138,
     366,   336,   337,   298,   341,   218,   354,   345,   346,   246,
     288,   347,   348,   344,   287,   358,   361,   228,   355,   362,
     368,   371,   228,   289,   291,   290,   357,   353,   359,   146,
     360,    75,   239,   339,   142,   148,   235,   335,   266,   158,
     141,   364,     0,   365,     0,     0,     0,   228,     0,     0,
       0,     0,   153,   363,     0,   372,     0,     0,   367,     0,
       0,     0,     0,   369,     0,     0,     0,     0,     0,     0,
     373,     1,     2,    80,    81,    82,    83,     3,     0,     4,
       5,     6,    84,    85,     0,     7,     8,     0,     9,     0,
      86,    10,    11,    12,    13,    87,    14,    15,    16,    17,
      18,    88,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,     0,    19,    89,    90,     0,    91,    92,     0,
      93,     0,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   196,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,     0,     0,    96,    53,     0,
       0,     0,    97,     0,    98,    99,     0,     0,   100,     0,
       0,     0,   101,   102,     0,   103,   104,     1,     2,     0,
       0,     0,     0,     3,     0,     4,     0,     6,     0,     0,
       0,     7,     8,     0,     0,     0,     0,    10,    11,     0,
      13,     0,     0,    15,    16,    17,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   135,    92,     0,    93,     0,    94,    95,
       0,     0,     0,     0,    80,    81,    82,    83,     0,     0,
       0,     0,     0,    84,    85,     0,     0,     0,    21,     0,
       0,    86,     0,     0,     0,     0,    87,     0,    97,     0,
      98,    99,    88,     0,   100,     0,     0,     0,   101,   102,
       0,   103,   104,     0,     0,    89,    90,     0,    91,    92,
       0,    93,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    96,    53,
       0,     0,     0,    97,     0,    98,    99,     0,     0,   100,
       0,     0,     0,   101,   102,     0,   103,   104,     1,     2,
       0,     0,     0,     0,     3,     0,     4,     5,     6,     0,
       0,     0,     7,     8,     0,     9,     0,     0,    10,    11,
      12,    13,     0,    14,    15,    16,    17,    18,     1,     2,
       0,     0,     0,     0,     3,     0,     4,     5,     6,     0,
      19,     0,     7,     8,    20,     9,     0,     0,    10,    11,
      12,    13,     0,    14,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
      19,     0,     0,     0,     0,     0,     0,   260,     0,   296,
     321,     0,     0,     0,     0,    23,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    21,
       0,     0,     0,     0,     0,     0,     0,   260,     0,   261,
     321,     1,     2,     0,     0,    23,     0,     3,     0,     4,
       5,     6,     0,     0,     0,     7,     8,     0,     9,     0,
       0,    10,    11,    12,    13,     0,    14,    15,    16,    17,
      18,     1,     2,     0,     0,     0,     0,     3,     0,     4,
       5,     6,     0,    19,     0,     7,     8,    20,     9,     0,
       0,    10,    11,    12,    13,     0,    14,    15,    16,    17,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     2,    21,    19,     0,     0,     3,   226,     4,     5,
       6,     0,    22,     0,     7,     8,     0,     9,    23,     0,
      10,    11,    12,    13,     0,    14,    15,    16,    17,    18,
       1,     2,    21,     0,     0,     0,     3,     0,     4,     5,
       6,     0,    19,   227,     7,     8,     0,     9,     0,     0,
      10,    11,    12,    13,     0,    14,    15,    16,    17,    18,
       1,     2,     0,     0,     0,     0,     3,     0,     4,     0,
       6,    21,    19,     0,     7,     8,     0,     0,     0,     0,
      10,    11,   351,    13,     1,     2,    15,    16,    17,    18,
       3,     0,     4,     0,     6,     0,     0,     0,     7,     8,
       0,     0,     0,     0,    10,    11,     0,    13,    77,     0,
      15,    16,    17,    18,     0,     0,     0,     0,     0,     1,
       2,     0,     0,     0,     0,     3,     0,     4,     5,     6,
       0,    21,     0,     7,     8,     0,     9,     0,   241,    10,
      11,    12,    13,     0,    14,    15,    16,    17,    18,     0,
       1,     2,     0,     0,     0,    21,     3,     0,     4,     5,
       6,    19,   306,     0,     7,     8,     0,     9,     0,     0,
      10,    11,    12,    13,     0,    14,    15,    16,    17,    18,
       0,     0,     0,     0,     0,     1,     2,     0,     0,     0,
      21,     3,    19,     4,     5,     6,    53,     0,     0,     7,
       8,     0,     9,     0,     0,    10,    11,    12,    13,     0,
      14,    15,    16,    17,    18,     0,     0,     0,     1,     2,
       0,    21,   334,     0,     3,     0,     4,    19,     6,     0,
       0,     0,     7,     8,     0,     0,     0,     0,    10,    11,
       0,    13,     0,     0,    15,    16,    17,    18,     0,   135,
      92,     0,    93,     0,    94,    95,    21,     0,     0,     0,
       0,     0,     0,     0,     0,   135,    92,     0,    93,     0,
      94,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   136,    97,     0,    98,    99,     0,    21,
     100,     0,     0,     0,   101,   102,   147,   103,   104,     0,
      97,     0,    98,    99,     0,     0,   100,     0,     0,     0,
     101,   102,     0,   103,   104,   135,    92,     0,    93,     0,
      94,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   135,    92,     0,    93,     0,    94,    95,     0,
       0,     0,     0,     0,     0,   165,     0,     0,     0,     0,
      97,     0,    98,    99,     0,     0,   100,     0,     0,     0,
     101,   102,    96,   103,   104,     0,     0,    97,     0,    98,
      99,     0,     0,   100,     0,     0,     0,   101,   102,     0,
     103,   104,   135,    92,     0,    93,     0,    94,    95,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   135,    92,
       0,    93,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,   269,    98,
      99,     0,     0,   100,     0,     0,     0,   101,   102,     0,
     103,   104,   319,    97,     0,    98,    99,     0,     0,   100,
       0,     0,     0,   101,   102,     0,   103,   104,   135,    92,
       0,    93,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,     0,   135,    92,     0,    93,     0,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   349,    97,     0,    98,    99,     0,     0,   100,
       0,     0,     0,   101,   102,     0,   103,   104,    97,     0,
      98,    99,     0,     0,   100,     0,     0,     0,   101,   102,
       0,   103,   104,   135,    92,     0,    93,     0,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,   135,    92,
       0,    93,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   172,     0,
      98,    99,     0,     0,   100,     0,     0,     0,   101,   102,
       0,   103,   104,   178,     0,    98,    99,     0,     0,   100,
       0,     0,     0,   101,   102,     0,   103,   104
};

static const yytype_int16 yycheck[] =
{
      35,     0,    59,    22,    80,   147,    25,    86,    34,   108,
      23,   154,   140,    59,   163,    32,   176,    97,    97,     4,
      49,    49,    49,    80,    49,    49,    63,    26,    27,    82,
      43,    84,    31,   262,    80,    76,    55,    94,    95,    49,
       0,    58,    83,    76,   101,    49,    76,    32,    83,    79,
      73,   108,    71,    80,    79,    84,    84,    74,    23,    84,
      84,    90,    90,   100,    63,    90,    99,   143,   228,   298,
      99,    76,    82,   153,    84,    76,    81,   157,    43,     0,
      90,    53,    54,    55,    85,   164,   143,    49,   167,    82,
      76,    84,   127,   172,   129,    81,   239,   143,   178,   178,
     199,   200,   201,    63,   183,    90,    80,    76,    76,    53,
      82,    76,    84,    57,    49,    76,    85,    85,    79,    91,
      82,    76,    84,   158,   147,    76,    81,    85,    79,    82,
      74,    84,    97,   168,   151,    96,   171,   156,   217,   161,
     162,   140,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
      82,   184,    84,   176,   313,    80,   265,   243,    90,    76,
      58,    59,    76,   133,   197,    76,    76,   256,    79,    96,
      76,    85,    76,    79,   260,    85,   243,   152,   153,   154,
      97,    85,   157,    86,    87,   218,   338,   243,   326,    80,
     222,   223,    79,   260,    92,    93,    56,    57,   265,   228,
      88,    89,    90,   178,   260,   228,    80,   252,   206,   207,
     208,   209,    60,    61,   202,   203,    80,   249,   204,   205,
     210,   211,    99,    96,   310,    84,   258,    84,    84,    84,
      79,    49,    99,    95,    77,   152,   153,   154,   261,   325,
     157,    78,    62,   310,    83,    81,    81,    81,    99,    79,
      49,    49,   261,    85,   310,    76,    85,    99,   325,   304,
      33,   178,   298,    85,   239,   332,    10,   296,   357,   325,
     359,    49,    81,   296,    84,    76,   332,    85,    83,   308,
     213,    85,    85,   315,   212,    85,    83,   296,   333,    85,
      85,    79,   301,   214,   216,   215,   341,   330,   343,    71,
     345,    50,   152,   308,    64,   338,   144,   301,   178,    78,
      63,   357,    -1,   358,    -1,    -1,    -1,   326,    -1,    -1,
      -1,    -1,   239,   355,    -1,   370,    -1,    -1,   360,    -1,
      -1,    -1,    -1,   365,    -1,    -1,    -1,    -1,    -1,    -1,
     372,     3,     4,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,    -1,    17,    18,    -1,    20,    -1,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    -1,    45,    46,    47,    -1,    49,    50,    -1,
      52,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    96,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    79,    80,    -1,
      -1,    -1,    84,    -1,    86,    87,    -1,    -1,    90,    -1,
      -1,    -1,    94,    95,    -1,    97,    98,     3,     4,    -1,
      -1,    -1,    -1,     9,    -1,    11,    -1,    13,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    -1,    23,    24,    -1,
      26,    -1,    -1,    29,    30,    31,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    55,
      -1,    -1,    -1,    -1,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,    14,    15,    -1,    -1,    -1,    74,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    27,    -1,    84,    -1,
      86,    87,    33,    -1,    90,    -1,    -1,    -1,    94,    95,
      -1,    97,    98,    -1,    -1,    46,    47,    -1,    49,    50,
      -1,    52,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      -1,    -1,    -1,    84,    -1,    86,    87,    -1,    -1,    90,
      -1,    -1,    -1,    94,    95,    -1,    97,    98,     3,     4,
      -1,    -1,    -1,    -1,     9,    -1,    11,    12,    13,    -1,
      -1,    -1,    17,    18,    -1,    20,    -1,    -1,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,     3,     4,
      -1,    -1,    -1,    -1,     9,    -1,    11,    12,    13,    -1,
      45,    -1,    17,    18,    49,    20,    -1,    -1,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    84,
      85,    -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    -1,    84,
      85,     3,     4,    -1,    -1,    90,    -1,     9,    -1,    11,
      12,    13,    -1,    -1,    -1,    17,    18,    -1,    20,    -1,
      -1,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,     3,     4,    -1,    -1,    -1,    -1,     9,    -1,    11,
      12,    13,    -1,    45,    -1,    17,    18,    49,    20,    -1,
      -1,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,    74,    45,    -1,    -1,     9,    49,    11,    12,
      13,    -1,    84,    -1,    17,    18,    -1,    20,    90,    -1,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
       3,     4,    74,    -1,    -1,    -1,     9,    -1,    11,    12,
      13,    -1,    45,    85,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
       3,     4,    -1,    -1,    -1,    -1,     9,    -1,    11,    -1,
      13,    74,    45,    -1,    17,    18,    -1,    -1,    -1,    -1,
      23,    24,    85,    26,     3,     4,    29,    30,    31,    32,
       9,    -1,    11,    -1,    13,    -1,    -1,    -1,    17,    18,
      -1,    -1,    -1,    -1,    23,    24,    -1,    26,    81,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,     3,
       4,    -1,    -1,    -1,    -1,     9,    -1,    11,    12,    13,
      -1,    74,    -1,    17,    18,    -1,    20,    -1,    81,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    -1,
       3,     4,    -1,    -1,    -1,    74,     9,    -1,    11,    12,
      13,    45,    81,    -1,    17,    18,    -1,    20,    -1,    -1,
      23,    24,    25,    26,    -1,    28,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,    -1,
      74,     9,    45,    11,    12,    13,    80,    -1,    -1,    17,
      18,    -1,    20,    -1,    -1,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    -1,    -1,    -1,     3,     4,
      -1,    74,    75,    -1,     9,    -1,    11,    45,    13,    -1,
      -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    23,    24,
      -1,    26,    -1,    -1,    29,    30,    31,    32,    -1,    49,
      50,    -1,    52,    -1,    54,    55,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,    -1,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    84,    -1,    86,    87,    -1,    74,
      90,    -1,    -1,    -1,    94,    95,    80,    97,    98,    -1,
      84,    -1,    86,    87,    -1,    -1,    90,    -1,    -1,    -1,
      94,    95,    -1,    97,    98,    49,    50,    -1,    52,    -1,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    50,    -1,    52,    -1,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,
      84,    -1,    86,    87,    -1,    -1,    90,    -1,    -1,    -1,
      94,    95,    79,    97,    98,    -1,    -1,    84,    -1,    86,
      87,    -1,    -1,    90,    -1,    -1,    -1,    94,    95,    -1,
      97,    98,    49,    50,    -1,    52,    -1,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      -1,    52,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,
      87,    -1,    -1,    90,    -1,    -1,    -1,    94,    95,    -1,
      97,    98,    83,    84,    -1,    86,    87,    -1,    -1,    90,
      -1,    -1,    -1,    94,    95,    -1,    97,    98,    49,    50,
      -1,    52,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50,    -1,    52,    -1,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    84,    -1,    86,    87,    -1,    -1,    90,
      -1,    -1,    -1,    94,    95,    -1,    97,    98,    84,    -1,
      86,    87,    -1,    -1,    90,    -1,    -1,    -1,    94,    95,
      -1,    97,    98,    49,    50,    -1,    52,    -1,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,    50,
      -1,    52,    -1,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    -1,
      86,    87,    -1,    -1,    90,    -1,    -1,    -1,    94,    95,
      -1,    97,    98,    84,    -1,    86,    87,    -1,    -1,    90,
      -1,    -1,    -1,    94,    95,    -1,    97,    98
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     9,    11,    12,    13,    17,    18,    20,
      23,    24,    25,    26,    28,    29,    30,    31,    32,    45,
      49,    74,    84,    90,   124,   125,   128,   129,   130,   132,
     138,   141,   142,   143,   145,   169,   170,   171,    49,    80,
     142,   141,   145,   146,    79,   126,   127,   142,   125,   125,
      49,   131,   125,    80,   124,   125,   158,   159,   160,    82,
      84,   143,     0,   116,    80,    49,   139,   140,    85,   141,
     145,    76,    79,    96,   172,   131,    80,    81,   160,   142,
       5,     6,     7,     8,    14,    15,    22,    27,    33,    46,
      47,    49,    50,    52,    54,    55,    79,    84,    86,    87,
      90,    94,    95,    97,    98,   102,   103,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   117,   118,
     119,   120,   122,   156,   157,   158,   160,   161,   162,   163,
     164,   167,   168,   116,   158,    49,    83,   105,   119,   123,
     144,   170,   139,    96,    76,    81,   127,    80,   120,   154,
     158,   160,    80,   129,   133,   134,   135,   141,   161,   123,
      79,    99,   116,    84,    84,    79,   122,    84,    84,    79,
      49,    99,    84,   105,   105,   122,   135,   151,    84,   105,
      53,    54,    55,    82,    84,    91,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    96,   121,   107,    88,
      89,    90,    86,    87,    56,    57,    58,    59,    92,    93,
      60,    61,    95,    77,    78,    62,    63,   100,    76,    79,
      81,    81,   116,   116,   124,    83,    49,    85,   125,   147,
     148,   149,   150,    81,   123,   140,   154,   155,   158,   133,
     135,    81,   134,    99,   136,   137,   142,   135,    81,    99,
     156,   156,   162,   122,    79,   122,   116,    79,   116,    85,
      82,    84,   145,   152,   153,    85,   151,    49,   122,    85,
     104,   120,    49,   120,   107,   107,   107,   108,   108,   109,
     109,   110,   110,   110,   110,   111,   111,   112,   113,   114,
     115,   117,   122,   120,   156,   156,    84,   142,   145,   152,
      85,    76,    76,    85,    76,    81,    81,   123,    76,    79,
      99,   156,    33,   116,    85,    85,   122,   165,   156,    83,
     123,    85,   147,   152,   153,    82,    84,   107,    85,    83,
      76,    85,    99,    10,    75,   149,    49,    81,   116,   137,
     123,    84,   162,   166,   156,    85,    83,    85,    85,    83,
     123,    85,   147,   120,   119,   116,   154,   116,    85,   116,
     116,    83,    85,   156,   165,   116,   122,   156,    85,   156,
      85,    79,   116,   156
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   101,   102,   102,   102,   102,   103,   103,   103,   103,
     103,   103,   103,   103,   104,   104,   105,   105,   105,   105,
     105,   105,   106,   106,   106,   106,   106,   106,   107,   107,
     108,   108,   108,   108,   109,   109,   109,   110,   110,   110,
     111,   111,   111,   111,   111,   112,   112,   112,   113,   113,
     114,   114,   115,   115,   116,   117,   117,   118,   118,   119,
     119,   120,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   122,   122,   123,   124,   124,   125,
     125,   125,   125,   125,   125,   126,   126,   127,   127,   128,
     128,   128,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   130,   130,   130,   131,
     132,   132,   133,   133,   134,   135,   135,   135,   135,   136,
     136,   137,   137,   137,   138,   138,   138,   139,   139,   140,
     140,   141,   141,   142,   142,   143,   143,   143,   143,   143,
     143,   143,   144,   145,   145,   145,   145,   146,   146,   147,
     147,   148,   148,   149,   149,   149,   150,   150,   151,   151,
     152,   152,   152,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   154,   154,   154,   155,   155,   156,   156,   156,
     156,   156,   156,   157,   157,   157,   158,   158,   158,   158,
     159,   160,   160,   161,   161,   162,   162,   163,   164,   164,
     164,   165,   166,   167,   167,   167,   167,   168,   168,   168,
     168,   168,   169,   169,   170,   170,   171,   171,   171,   171,
     172
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     0,     1,     3,     1,     3,     1,
       5,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     2,     3,     1,
       2,     1,     2,     1,     2,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     6,     5,     2,     0,
       1,     1,     1,     2,     3,     2,     1,     2,     1,     1,
       3,     1,     2,     3,     4,     5,     2,     1,     3,     1,
       3,     1,     1,     2,     1,     1,     3,     4,     3,     5,
       5,     4,     0,     1,     2,     2,     3,     1,     2,     1,
       3,     1,     3,     2,     2,     1,     1,     3,     1,     2,
       1,     1,     2,     3,     2,     3,     3,     4,     2,     3,
       3,     4,     1,     3,     4,     1,     4,     1,     1,     1,
       1,     1,     1,     4,     4,     3,     2,     3,     3,     4,
       1,     1,     3,     1,     3,     1,     2,     4,     6,     3,
       5,     1,     1,     7,     9,     8,    10,     3,     2,     2,
       2,     3,     1,     3,     1,     1,     5,     4,     3,     2,
       0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 69 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb((yyvsp[0].str));
					char *a=primaryExpr((yyvsp[0].str));
					if(a){
						string as(a);
						(yyval.ptr)->isInit = lookup((yyvsp[0].str))->is_init;
			                        (yyval.ptr)->nodeType = as;
			                        string key((yyvsp[0].str));
			                        (yyval.ptr)->exprType = 3;
			                        (yyval.ptr)->nodeKey = key;
						}
						else{
							yyerror("Error : %s not declared",(yyvsp[0].str));
							(yyval.ptr)->nodeType=string("");
						}
					}
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 84 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb((yyvsp[0].str));
								//TO ADD SOME THING REMEBBER************************
							}
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 87 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb((yyvsp[0].str));
	  				(yyval.ptr)->nodeType=string("char*");
					(yyval.ptr)->isInit=1;
					}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 91 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[-1].ptr);}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 95 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 97 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("[ ]", NULL, (yyvsp[-3].ptr), (yyvsp[-1].ptr));
					 if((yyvsp[-3].ptr)->isInit==1&&(yyvsp[-1].ptr)->isInit==1) (yyval.ptr)->isInit=1;
					 char *s=postfixExpr((yyvsp[-3].ptr)->nodeType,1);
					 if(s&&isInt((yyvsp[-1].ptr)->nodeType)){
					 	string as(s);
						(yyval.ptr)->nodeType=as;
					 }
					 else if(!isInt((yyvsp[-1].ptr)->nodeType)){
						yyerror("Error : array index not a int");
					 }
					 else{
						yyerror("Error : array indexed with more indeces than its dimension");
					 }
					}
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 112 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[-2].ptr);
					(yyval.ptr)->isInit=1;
				char* s = postfixExpr((yyvsp[-2].ptr)->nodeType, 2);
				if(s){
					string as(s);
					(yyval.ptr)->nodeType =as;
					if((yyvsp[-2].ptr)->exprType==3){
						string funcArgs = funcArgList((yyvsp[-2].ptr)->nodeKey);
						if(!(funcArgs==string(""))) {
							yyerror("Error : \'%s\' function call requires arguments to be passed \n     \'%s %s\( %s \)\'",((yyvsp[-2].ptr)->nodeKey).c_str(),((yyval.ptr)->nodeType).c_str(),((yyvsp[-2].ptr)->nodeKey).c_str(),funcArgs.c_str());
						}
					}
				}
				else{
					yyerror("Error : Invalid Function call");
				}																
				currArguments=string("");
				}
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 131 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("postfix_expression", NULL, (yyvsp[-3].ptr), (yyvsp[-1].ptr));
							if((yyvsp[-1].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							char* s = postfixExpr((yyvsp[-3].ptr)->nodeType, 3);
							if(s){
								string as(s);
								(yyval.ptr)->nodeType =as;
								if((yyvsp[-3].ptr)->exprType==3){
									string funcArgs = funcArgList((yyvsp[-3].ptr)->nodeKey);
									char* a =new char();
									string temp1 = currArguments;
									string temp2 = funcArgs;
									string typeA,typeB;
									string delim = string(",");
									unsigned f1=1;
									unsigned f2=1;
									int argNo = 0;
									while(f1!=-1 && f2!=-1){
										f1 = temp1.find_first_of(delim);
										f2 = temp2.find_first_of(delim);
										argNo++;
										if(f1==-1) typeA = temp1; else{ typeA = temp1.substr(0,f1); temp1 = temp1.substr(f1+1);}
										if(f2==-1) typeB = temp2 ; else{ typeB = temp2.substr(0,f2); temp2 = temp2.substr(f2+1); }
										if(typeB==string("...")) break;
										a = validAssign(typeA,typeB);
										if(a){
											if(!strcmp(a,"warning")) { yyerror("Warning : Passing argumnet %d of \'%s\' from incompatible pointer type.\n Note : expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",argNo,((yyvsp[-3].ptr)->nodeKey).c_str(),typeB.c_str(),typeA.c_str(),((yyval.ptr)->nodeType).c_str(),((yyvsp[-3].ptr)->nodeKey).c_str(),funcArgs.c_str()); }
										}
										else{
											yyerror("Error : Incompatible type for argument %d of \'%s\' .\n Note : expected \'%s\' but argument is of type \'%s\'\n     \'%s %s\( %s \)\'",argNo,((yyvsp[-3].ptr)->nodeKey).c_str(),typeB.c_str(),typeA.c_str(),((yyval.ptr)->nodeType).c_str(),((yyvsp[-3].ptr)->nodeKey).c_str(),funcArgs.c_str());
										}
										if((f1!=-1)&&(f2!=-1)){
											continue;
										}else if(f2!=-1){
											if(!(temp2==string("..."))) yyerror("Error : Too few arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",((yyvsp[-3].ptr)->nodeKey).c_str(),((yyval.ptr)->nodeType).c_str(),((yyvsp[-3].ptr)->nodeKey).c_str(),funcArgs.c_str());
											break;
										}else if(f1!=-1){
											yyerror("Error : Too many arguments for the function \'%s\'\n    \'%s %s\( %s \)\'",((yyvsp[-3].ptr)->nodeKey).c_str(),((yyval.ptr)->nodeType).c_str(),((yyvsp[-3].ptr)->nodeKey).c_str(),funcArgs.c_str());
											break;
										}else{ break; }
									}
										
								}

							}
							else {
								yyerror("Error : Invalid Function call");
							}
								currArguments=string("");
							}
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 180 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb(" . ", NULL, (yyvsp[-2].ptr), term_symb((yyvsp[0].str)));
											string as((yyvsp[0].str));
											int k = structLookup((yyvsp[-2].ptr)->nodeType, as);
											if(k==1) yyerror("Error : \'.\' is an invalid operator on \'%s\'", (yyvsp[-2].ptr)->nodeKey.c_str() );
											else if(k==2) yyerror("Error : \'%s\' is not a member of struct \'%s\'", (yyvsp[0].str),(yyvsp[-2].ptr)->nodeKey.c_str() );
											else (yyval.ptr)->nodeType = structMemberType((yyvsp[-2].ptr)->nodeType, as);
											(yyval.ptr)->nodeKey = (yyvsp[-2].ptr)->nodeKey+ string(".") + as;
											}
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 189 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("->", NULL, (yyvsp[-2].ptr), term_symb((yyvsp[0].str)));
											string as((yyvsp[0].str));
											string as1 = ((yyvsp[-2].ptr)->nodeType).substr(0,((yyvsp[-2].ptr)->nodeType).length()-1);
											int k = structLookup(as1, as);
											cout<<k<<endl;
											if(k==1){ yyerror("Error : \'%s\' is an invalid operator on \'%s\'", (yyvsp[-1].str), (yyvsp[-2].ptr)->nodeKey.c_str() );
											}
											else if(k==2){ yyerror("Error : \'%s\' is not a member of struct \'%s\'", (yyvsp[0].str),(yyvsp[-2].ptr)->nodeKey.c_str() );
											}
											else (yyval.ptr)->nodeType = structMemberType(as1, as);
											(yyval.ptr)->nodeKey = (yyvsp[-2].ptr)->nodeKey+ string("->") + as;
											}
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 202 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=  non_term_symb("++", NULL,(yyvsp[-1].ptr), NULL);
												if((yyvsp[-1].ptr)->isInit==1) (yyval.ptr)->isInit=1;
												char* s = postfixExpr((yyvsp[-1].ptr)->nodeType, 6);
												if(s){
													string as(s);
													(yyval.ptr)->nodeType =as;
													(yyval.ptr)->iVal = (yyvsp[-1].ptr)->iVal +1;
												}
												else {
													yyerror("Error : Increment not defined for this type");
												}
												}
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 215 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=  non_term_symb("--", NULL,(yyvsp[-1].ptr), NULL);
												if((yyvsp[-1].ptr)->isInit==1) (yyval.ptr)->isInit =1;
												char* s = postfixExpr((yyvsp[-1].ptr)->nodeType, 7);
												if(s){
													string as(s);
													(yyval.ptr)->nodeType =as;
												    (yyval.ptr)->iVal = (yyvsp[-1].ptr)->iVal -1;
												}
												else {
													yyerror("Error : Decrement not defined for this type");
												}
												}
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 230 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);if((yyvsp[0].ptr)->isInit==1)(yyval.ptr)->isInit = 1; currArguments = (yyvsp[0].ptr)->nodeType;}
#line 2085 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 231 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb((yyvsp[-1].str),NULL,(yyvsp[-2].ptr), (yyvsp[0].ptr));
								char* a =  argumentExpr((yyvsp[-2].ptr)->nodeType, (yyvsp[0].ptr)->nodeType, 2);
								string as(a);
								(yyval.ptr)->nodeType = as;
								if((yyvsp[-2].ptr)->isInit == 1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
								currArguments = currArguments +string(",")+ (yyvsp[0].ptr)->nodeType;
								}
#line 2097 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 241 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2103 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 242 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("++", NULL, NULL, (yyvsp[0].ptr));
							if((yyvsp[0].ptr)->isInit == 1 ) (yyval.ptr)->isInit=1;
							char* s = postfixExpr((yyvsp[0].ptr)->nodeType, 6);
							if(s){
								string as(s);
								(yyval.ptr)->nodeType =as;
								(yyval.ptr)->iVal = (yyvsp[0].ptr)->iVal +1;
							}
							else {
								yyerror("Error : Increment not defined for this type");
							}
							}
#line 2120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 254 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("--", NULL, NULL, (yyvsp[0].ptr));
							(yyval.ptr)->iVal =(yyvsp[0].ptr)->iVal -1;
							if((yyvsp[0].ptr)->isInit == 1 ) (yyval.ptr)->isInit=1;
							char* s = postfixExpr((yyvsp[0].ptr)->nodeType, 7);
							if(s){
								string as(s);
								(yyval.ptr)->nodeType =as;
							}
							else {
								yyerror("Error : Decrement not defined for this type");
							}			
							}
#line 2137 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 266 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("unary_expression", NULL, (yyvsp[-1].ptr), (yyvsp[0].ptr));
						(yyval.ptr)->iVal = (yyvsp[0].ptr)->iVal;
						if( (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
						char* a= unaryExpr((yyvsp[-1].ptr)->name, (yyvsp[0].ptr)->nodeType, 1);
						if(a){
							string as(a);
							(yyval.ptr)->nodeType= as;
						}
						else{
							yyerror("Error : Type inconsistent with operator %s", (yyvsp[-1].ptr)->name.c_str());
						}
						}
#line 2154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 278 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb((yyvsp[-1].str), NULL, NULL, (yyvsp[0].ptr));(yyval.ptr)->nodeType = string("int");(yyval.ptr)->isInit=1;}
#line 2160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 279 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb((yyvsp[-3].str), NULL, NULL, (yyvsp[-1].ptr));(yyval.ptr)->nodeType = string("int");(yyval.ptr)->isInit=1;}
#line 2166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 283 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("&");}
#line 2172 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 284 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("*");}
#line 2178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 285 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("+");}
#line 2184 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 286 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("-");}
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 287 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("~");}
#line 2196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 288 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("!");}
#line 2202 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 292 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2208 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 293 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("cast_expression", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
						(yyval.ptr)->nodeType = (yyvsp[-2].ptr)->nodeType;
        					if((yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
						}
#line 2217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 300 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2223 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 302 "src/comp.y" /* yacc.c:1646  */
    {
			(yyval.ptr) = non_term_symb("*", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
			char* a=multilplicativeExpr((yyvsp[-2].ptr)->nodeType, (yyvsp[0].ptr)->nodeType, '*');
			if(a){
				int k;
				if(strcmp(a,"int")==0){
					//$$=nonTerminal("*int",NULL,$1,$3);
					(yyval.ptr)->nodeType = string("long long");
				}
				else if (strcmp(a, "float")==0){
					//$$=nonTerminal("*float",NULL,$1,$3);
					(yyval.ptr)->nodeType = string("long double");
				}
			}
			else{
				//$$=nonTerminal("*",NULL,$1,$3);
				yyerror("Error : Incompatible type for * operator");
			}
			if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
		}
#line 2248 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 322 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("/", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
														if ((yyvsp[0].ptr)->iVal != 0)
															(yyval.ptr)->iVal = (yyvsp[-2].ptr)->iVal/ (yyvsp[0].ptr)->iVal;
														char* a=multilplicativeExpr((yyvsp[-2].ptr)->nodeType, (yyvsp[0].ptr)->nodeType, '/');
														if(a){int k;
															if(!strcmp(a,"int")){
																//$$=nonTerminal("/int",NULL,$1,$3);
																(yyval.ptr)->nodeType = string("long long");
															
															}
															else if (!strcmp(a,"float")){
																//$$=nonTerminal("/float",NULL,$1,$3);
																(yyval.ptr)->nodeType = string("long double");
															
															}
														}
														else{
															//$$=nonTerminal("/",NULL,$1,$3);
															yyerror("Error : Incompatible type for / operator");
														}
														if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
													}
#line 2275 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 345 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("%", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
							if((yyvsp[0].ptr)->iVal != 0) (yyval.ptr)->iVal = (yyvsp[-2].ptr)->iVal % (yyvsp[0].ptr)->iVal;
							char* a=multilplicativeExpr((yyvsp[-2].ptr)->nodeType, (yyvsp[0].ptr)->nodeType, '/');
							if(!strcmp(a,"int")){
								(yyval.ptr)->nodeType= string("long long");
									
							}
							else {
								yyerror("Error : Incompatible type for % operator");
							}
							if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							}
#line 2292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 360 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2298 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 361 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("+", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
								(yyval.ptr)->iVal = (yyvsp[-2].ptr)->iVal + (yyvsp[0].ptr)->iVal;
								char *a = additiveExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType,'+');
								char *q=new char();
								string p;
								if(a){
									string as(a);
									p = string("+")+as;
									strcpy(q,p.c_str());
								}
								else q = "+";
								//$$=nonTerminal(q,NULL,$1,$3);
								if(a){ 
									string as(a);
									if(!strcmp(a,"int")) (yyval.ptr)->nodeType=string("long long");
									else if(!strcmp(a,"real")) (yyval.ptr)->nodeType=string("long double");
									else (yyval.ptr)->nodeType=as; // for imaginary and complex returns
				
								}
								else {
									yyerror("Error : Incompatible type for + operator");
								}
								if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
								}
#line 2327 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 386 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("-", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
								(yyval.ptr)->iVal = (yyvsp[-2].ptr)->iVal - (yyvsp[0].ptr)->iVal;
								char *a = additiveExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType,'-');
								char *q = new char();
								string p;
								if(a){ string as(a);
									p =string("-")+as;
									strcpy(q,p.c_str());
								}
								//$$=nonTerminal(q,NULL,$1,$3);
								if(a){ 
									string as(a);
									if(!strcmp(a,"int")) (yyval.ptr)->nodeType=string("long long");
									else if(!strcmp(a,"real")) (yyval.ptr)->nodeType=string("long double");
									else (yyval.ptr)->nodeType=as;   // for imaginary and complex returns
									
								}
								else {
									yyerror("Error : Incompatible type for - operator");
								}
								if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
								}
#line 2354 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 411 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 412 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2((yyvsp[-1].str), (yyvsp[-2].ptr), NULL, (yyvsp[0].ptr));
							char* a = shiftExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType);                        
							if(a){
								(yyval.ptr)->nodeType = (yyvsp[-2].ptr)->nodeType;
							}
							else{
								yyerror("Error : Invalid operands to binary <<");
							}
							if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							}
#line 2375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 423 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2((yyvsp[-1].str), (yyvsp[-2].ptr), NULL, (yyvsp[0].ptr));
														//$$ = nonTerminal2(">>", $1, NULL, $3);
														char* a = shiftExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType);
														if(a){
															(yyval.ptr)->nodeType = (yyvsp[-2].ptr)->nodeType;
															
														}
														else{
															yyerror("Error : Invalid operands to binary >>");
														}

							if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							}
#line 2393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 439 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2399 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 440 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("<", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
							char* a=relationalExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType,"<");
							if(a) { 
								if(!strcmp(a,"bool")) (yyval.ptr)->nodeType = string("bool");
								else if(!strcmp(a,"Bool")){
									(yyval.ptr)->nodeType = string("bool");
									yyerror("Warning : comparison between pointer and integer");
								}
							}	
							else {
								yyerror("Error : invalid operands to binary <");
							}
							if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							}
#line 2418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 455 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb(">", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
							char* a=relationalExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType,">");
							if(a){ 
								if(!strcmp(a,"bool")) (yyval.ptr)->nodeType = string("bool");
								else if(!strcmp(a,"Bool")){
									(yyval.ptr)->nodeType = string("bool");
									yyerror("Warning : comparison between pointer and integer");
								}
							}else {
								yyerror("Error : invalid operands to binary >");
							}
							if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							}
#line 2436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 469 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb((yyvsp[-1].str), NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
							char* a=relationalExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType,"<=");
							if(a){
								if(!strcmp(a,"bool")) (yyval.ptr)->nodeType = string("bool");
								else if(!strcmp(a,"Bool")){
									(yyval.ptr)->nodeType = string("bool");
									yyerror("Warning : comparison between pointer and integer");
								}
								
							}else {
								yyerror("Error : invalid operands to binary <=");
							}
							if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							}
#line 2455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 484 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb((yyvsp[-1].str), NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
							char* a=relationalExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType,">=");
							if(a){  
								if(!strcmp(a,"bool")) (yyval.ptr)->nodeType = string("bool");
								else if(!strcmp(a,"Bool")){
									(yyval.ptr)->nodeType = string("bool");
									yyerror("Warning : comparison between pointer and integer");
								}	
							}else {
								yyerror("Error : invalid operands to binary >=");
							}
							if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							}
#line 2473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 500 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 501 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("==", (yyvsp[-2].ptr), NULL, (yyvsp[0].ptr));
						    char* a = equalityExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType);
						    if(a){ if(!strcmp(a,"true")){
							    yyerror("Warning : Comparision between pointer and Integer");
							    }
							    (yyval.ptr)->nodeType = "bool";
						    }
						   else{ yyerror("Error :Invalid operands to binary =="); }
						   if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
                                                   }
#line 2494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 512 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("!=", (yyvsp[-2].ptr), NULL, (yyvsp[0].ptr));
						    char* a = equalityExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType);
						    if(a){   if(!strcmp(a,"true")){
							    yyerror("Warning : Comparision between pointer and Integer");
							    }
							    (yyval.ptr)->nodeType = "bool";
						    }
						   else{ yyerror("Error :Invalid operands to binary !="); }
						   if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
                                                   }
#line 2509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 525 "src/comp.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr);}
#line 2515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 526 "src/comp.y" /* yacc.c:1646  */
    {
               (yyval.ptr) = non_term_symb("&",NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
               char* a = bitwiseExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType);
               if(a){
                  if(!strcmp(a,"true")) { (yyval.ptr)->nodeType = string("bool"); }
                  else{   (yyval.ptr)->nodeType = string("long long");}
               }
               else {
                 yyerror("Error :Invalid operands to the binary &");
               }
                 if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
          }
#line 2532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 541 "src/comp.y" /* yacc.c:1646  */
    { (yyval.ptr) = (yyvsp[0].ptr);}
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 542 "src/comp.y" /* yacc.c:1646  */
    {
           (yyval.ptr) = non_term_symb("^", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
               char* a = bitwiseExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType);
               if(a){
                  if(!strcmp(a,"true")) { (yyval.ptr)->nodeType = string("bool"); }
                  else{   (yyval.ptr)->nodeType = string("long long");}
               }
               else {
                 yyerror("Error :Invalid operands to the binary ^");
               }
                 if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;

        }
#line 2556 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 558 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2562 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 559 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("|", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
								char* a = bitwiseExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType);
								if(a){
									if(!strcmp(a,"true")) { (yyval.ptr)->nodeType = string("bool"); }
									else{   (yyval.ptr)->nodeType = string("long long");}
						
								}
								else {
									yyerror("Error :Invalid operands to the binary |");
								}
									if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
							
								}
#line 2580 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 591 "src/comp.y" /* yacc.c:1646  */
    {
           (yyval.number) = getNextIndex();
 }
#line 2588 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 615 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 616 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2((yyvsp[-1].str), (yyvsp[-2].ptr), NULL, (yyvsp[0].ptr));
								(yyval.ptr)->nodeType == string("bool");
								if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
								}
#line 2603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 623 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 624 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2((yyvsp[-1].str), (yyvsp[-2].ptr), NULL, (yyvsp[0].ptr));
								//$$ = nonTerminal2("||", $1,NULL, $3);
								if((yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;
								(yyval.ptr)->nodeType == string("bool");
								}
#line 2619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 632 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 633 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("logical_expr ? expr : conditional_expr", (yyvsp[-4].ptr), (yyvsp[-2].ptr), (yyvsp[0].ptr));
										(yyval.ptr)->rVal = -11;
										char* a = conditionalExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType);
										if(a){
											string as(a);
											(yyval.ptr)->nodeType = string("int");
										}
										else{

											yyerror("Error :Type mismatch in conditional expression");
										}
										if((yyvsp[-4].ptr)->isInit==1 && (yyvsp[-2].ptr)->isInit==1 && (yyvsp[0].ptr)->isInit==1) (yyval.ptr)->isInit=1;																		
										}
#line 2643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 649 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 650 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2((yyvsp[-1].str), (yyvsp[-2].ptr), NULL, (yyvsp[0].ptr));
									char* a = assignmentExpr((yyvsp[-2].ptr)->nodeType,(yyvsp[0].ptr)->nodeType,(yyvsp[-1].str));
									if(a){
											if(!strcmp(a,"true")){ (yyval.ptr)->nodeType = (yyvsp[-2].ptr)->nodeType;
											}
											if(!strcmp(a,"warning")){ (yyval.ptr)->nodeType = (yyvsp[-2].ptr)->nodeType;
												yyerror("Warning : Assignment with incompatible pointer type");
												}
											
											}
										else{ yyerror("Error : Incompatible types when assigning type \'%s\' to \'%s\' ",((yyvsp[-2].ptr)->nodeType).c_str(),((yyvsp[0].ptr)->nodeType).c_str()); }
									if((yyvsp[-2].ptr)->exprType==3){ if((yyvsp[0].ptr)->isInit==1) update_isInit((yyvsp[-2].ptr)->nodeKey); }
									}
#line 2667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 666 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "=";}
#line 2673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 667 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "*=";}
#line 2679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 668 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "/=";}
#line 2685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 669 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "%=";}
#line 2691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 670 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "+=";}
#line 2697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 671 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "-=";}
#line 2703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 672 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "<<=";}
#line 2709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 673 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = ">>=";}
#line 2715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 674 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "&=";}
#line 2721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 675 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "^=";}
#line 2727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 676 "src/comp.y" /* yacc.c:1646  */
    {(yyval.str) = "|=";}
#line 2733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 680 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 681 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("expression ','", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));(yyval.ptr)->nodeType = string("void");}
#line 2745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 685 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 689 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[-1].ptr);}
#line 2757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 690 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("declaration", NULL, (yyvsp[-2].ptr), (yyvsp[-1].ptr));}
#line 2763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 694 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 695 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("declaration_specifiers", NULL, (yyvsp[-1].ptr), (yyvsp[0].ptr));}
#line 2775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 696 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 697 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("declaration_specifiers", NULL, (yyvsp[-1].ptr), (yyvsp[0].ptr));}
#line 2787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 698 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 699 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("declaration_specifiers", NULL, (yyvsp[-1].ptr), (yyvsp[0].ptr));}
#line 2799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 703 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 2805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 704 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("init_declaration_list", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));}
#line 2811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 708 "src/comp.y" /* yacc.c:1646  */
    {
		(yyval.ptr) = (yyvsp[0].ptr);
		if((yyvsp[0].ptr)->exprType==1){ 
			char *t=new char();
        	strcpy(t,((yyvsp[0].ptr)->nodeType).c_str());
        	char *key =new char();
        	strcpy(key,((yyvsp[0].ptr)->nodeKey).c_str());
        	if(scopeLookup((yyvsp[0].ptr)->nodeKey)){
                yyerror("Error : redeclaration of \'%s\'",key);
        	}else if((yyvsp[0].ptr)->nodeType==string("void")){
        	    yyerror("Error : Variable or field \'%s\' declared void",key);
        	}else {  
				insertSymbol(*curr,key,t,(yyvsp[0].ptr)->size,0,0);
			}
            (yyval.ptr)->place = pair<string, sEntry*>((yyvsp[0].ptr)->nodeKey, lookup((yyvsp[0].ptr)->nodeKey));
        }
	}
#line 2833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 725 "src/comp.y" /* yacc.c:1646  */
    {
		(yyval.ptr) = non_term_symb("=", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
		if((yyvsp[-2].ptr)->exprType==1||(yyvsp[-2].ptr)->exprType==15){ 
			char *t=new char();
            strcpy(t,((yyvsp[-2].ptr)->nodeType).c_str());
            char *key =new char();
            strcpy(key,((yyvsp[-2].ptr)->nodeKey).c_str());
        if(scopeLookup((yyvsp[-2].ptr)->nodeKey)){
			yyerror("Error : Redeclaration of \'%s\'",key);
            }else if((yyvsp[-2].ptr)->nodeType==string("void")){
                 yyerror("Error : Variable or field \'%s\' declared void",key);
            }
            else { 
				if((yyval.ptr)->exprType==15) { 
					insertSymbol(*curr,key,t,((yyvsp[0].ptr)->exprType*(yyvsp[-2].ptr)->iVal),0,1); 
				}
                insertSymbol(*curr,key,t,(yyvsp[-2].ptr)->size,0,1);
            }
        }
	}
#line 2858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 748 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=term_symb((yyvsp[0].str));}
#line 2864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 749 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=term_symb((yyvsp[0].str));}
#line 2870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 750 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=term_symb((yyvsp[0].str));}
#line 2876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 751 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=term_symb((yyvsp[0].str));}
#line 2882 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 752 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=term_symb((yyvsp[0].str));}
#line 2888 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 756 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 759 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 762 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2912 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 765 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 768 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 771 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2936 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 774 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 777 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 780 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 783 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].ptr));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].ptr));
									(yyval.ptr) = (yyvsp[0].ptr);}
#line 2968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 786 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].ptr));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].ptr));
									(yyval.ptr) = (yyvsp[0].ptr);}
#line 2976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 789 "src/comp.y" /* yacc.c:1646  */
    {if(typeName==string(""))typeName = string((yyvsp[0].str));
                   					else typeName = typeName+string(" ")+string((yyvsp[0].str));
									(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 2984 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 795 "src/comp.y" /* yacc.c:1646  */
    {string as((yyvsp[-4].str));
									(yyval.ptr) = non_term_symb("struct_or_union_specifier", (yyvsp[-4].str), (yyvsp[-5].ptr), (yyvsp[-1].ptr));
									if(endStructTable(as)){
									(yyval.ptr)->nodeType = string("STRUCT_")+as; }
									else yyerror("Error : struct \'%s\' is already defined\n", (yyvsp[-4].str));
									}
#line 2995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 802 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("struct_or_union_specifier", NULL, (yyvsp[-4].ptr), (yyvsp[-1].ptr));
											structCounter++;
											string as = to_string(structCounter);
											if(endStructTable(as)){
											(yyval.ptr)->nodeType = string("STRUCT_")+as; }
											else yyerror("Error : struct \'%s\' is already defined\n", (yyvsp[-3].str));
											}
#line 3007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 810 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("struct_or_union_specifier", (yyvsp[0].str), (yyvsp[-1].ptr), NULL);
													string as((yyvsp[0].str));
													as = "STRUCT_" + as;
													if(isStruct(as)) (yyval.ptr)->nodeType = as;
													else yyerror("Error : No struct \'%s\' is defined",(yyvsp[0].str));
													}
#line 3018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 819 "src/comp.y" /* yacc.c:1646  */
    {
           makeStructTable();
  }
#line 3026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 824 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 3032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 825 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 3038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 829 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 830 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("struct_declaration_list", NULL, (yyvsp[-1].ptr), (yyvsp[0].ptr));}
#line 3050 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 834 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("struct_declaration", NULL, (yyvsp[-2].ptr), (yyvsp[-1].ptr));typeName = string("");}
#line 3056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 838 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("specifier_qualifier_list", NULL, (yyvsp[-1].ptr), (yyvsp[0].ptr));}
#line 3062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 839 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 840 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("specifier_qualifier_list", NULL, (yyvsp[-1].ptr), (yyvsp[0].ptr));}
#line 3074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 841 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3080 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 845 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 846 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("struct_declarator_list",NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));}
#line 3092 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 850 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);
				if(!insertStructSymbol((yyvsp[0].ptr)->nodeKey, (yyvsp[0].ptr)->nodeType, (yyvsp[0].ptr)->size, 0, 0)) yyerror(" : \'%s\' is already declared in the same struct", (yyvsp[0].ptr)->nodeKey.c_str());}
#line 3099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 852 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3105 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 853 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("struct_declarator", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));
										if(!insertStructSymbol((yyvsp[-2].ptr)->nodeKey, (yyvsp[-2].ptr)->nodeType, (yyvsp[-2].ptr)->size, 0, 1)) yyerror("Error : \'%s\' is already declared in the same struct", (yyvsp[-2].ptr)->nodeKey.c_str());}
#line 3112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 858 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("enum_specifier", (yyvsp[-3].str), NULL, (yyvsp[-1].ptr));}
#line 3118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 859 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_3("enum_specifier", (yyvsp[-4].str),(yyvsp[-3].str), (yyvsp[-1].ptr),NULL);}
#line 3124 "y.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 860 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_3("enum_specifier",(yyvsp[-1].str), (yyvsp[0].str),NULL, NULL);}
#line 3130 "y.tab.c" /* yacc.c:1646  */
    break;

  case 127:
#line 864 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 128:
#line 865 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("enumerator_list", NULL, (yyvsp[-2].ptr),  (yyvsp[0].ptr));}
#line 3142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 129:
#line 869 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 3148 "y.tab.c" /* yacc.c:1646  */
    break;

  case 130:
#line 870 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("=",NULL, term_symb((yyvsp[-2].str)), (yyvsp[0].ptr));}
#line 3154 "y.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 874 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 3160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 875 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb((yyvsp[0].str));}
#line 3166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 879 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("declarator", NULL, (yyvsp[-1].ptr), (yyvsp[0].ptr));
								if((yyvsp[0].ptr)->exprType==1){(yyval.ptr)->nodeType=(yyvsp[0].ptr)->nodeType+(yyvsp[-1].ptr)->nodeType;
									(yyval.ptr)->nodeKey = (yyvsp[0].ptr)->nodeKey;
									(yyval.ptr)->exprType=1;}
								if((yyvsp[0].ptr)->exprType==2){ funcName = (yyvsp[0].ptr)->nodeKey; funcType = (yyvsp[0].ptr)->nodeType; }
								char* a = new char();
								strcpy(a,((yyval.ptr)->nodeType).c_str());(yyval.ptr)->size = getSize(a);}
#line 3178 "y.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 886 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);
						if((yyvsp[0].ptr)->exprType==2){ funcName=(yyvsp[0].ptr)->nodeKey; funcType = (yyvsp[0].ptr)->nodeType;}}
#line 3185 "y.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 891 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=term_symb((yyvsp[0].str));
				(yyval.ptr)->exprType=1;(yyval.ptr)->nodeKey=string((yyvsp[0].str));
				(yyval.ptr)->nodeType=typeName;
				char* a =new char();
                strcpy(a,typeName.c_str());
				(yyval.ptr)->size = getSize(a);}
#line 3196 "y.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 897 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[-1].ptr);
						if((yyvsp[-1].ptr)->exprType==1){ (yyval.ptr)->exprType=1;
                                          (yyval.ptr)->nodeKey=(yyvsp[-1].ptr)->nodeKey;
                                          (yyval.ptr)->nodeType=(yyvsp[-1].ptr)->nodeType;}
						}
#line 3206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 902 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("direct_declarator", NULL, (yyvsp[-3].ptr), (yyvsp[-1].ptr));}
#line 3212 "y.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 904 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = square("direct_declarator", (yyvsp[-2].ptr));
				     	if((yyvsp[-2].ptr)->exprType==1){ (yyval.ptr)->exprType=1;
                                     	(yyval.ptr)->nodeKey=(yyvsp[-2].ptr)->nodeKey;
                                     	(yyval.ptr)->nodeType=(yyvsp[-2].ptr)->nodeType+string("*");}
					char* a = new char();
					strcpy(a,((yyval.ptr)->nodeType).c_str());
					(yyval.ptr)->size = getSize(a);
					strcpy(a,((yyvsp[-2].ptr)->nodeType).c_str());
					(yyval.ptr)->exprType=15;
					(yyval.ptr)->iVal=getSize(a);
					}
#line 3228 "y.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 916 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("direct_declarator", NULL, (yyvsp[-4].ptr), (yyvsp[-1].ptr));
							if((yyvsp[-4].ptr)->exprType==1){ (yyval.ptr)->nodeKey=(yyvsp[-4].ptr)->nodeKey;
							(yyval.ptr)->exprType=2;
							(yyval.ptr)->nodeType=(yyvsp[-4].ptr)->nodeType;
							insertFuncArguments((yyvsp[-4].ptr)->nodeKey,funcArguments);
							funcArguments=string("");
							char* a = new char();
							strcpy(a,((yyval.ptr)->nodeType).c_str());
							(yyval.ptr)->size = getSize(a);
							}
							}
#line 3244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 928 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("direct_declarator", NULL, (yyvsp[-4].ptr), (yyvsp[-1].ptr));
							char* a = new char();
							strcpy(a,((yyval.ptr)->nodeType).c_str());
							(yyval.ptr)->size = getSize(a);
							}
#line 3254 "y.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 934 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = parentheses("direct_declarator", (yyvsp[-3].ptr));
							if((yyvsp[-3].ptr)->exprType==1){
								(yyval.ptr)->nodeKey=(yyvsp[-3].ptr)->nodeKey;
								insertFuncArguments((yyvsp[-3].ptr)->nodeKey,string(""));
								(yyval.ptr)->exprType=2;
								funcArguments = string("");
							}
							(yyval.ptr)->nodeType=(yyvsp[-3].ptr)->nodeType;
							char* a = new char();
							strcpy(a,((yyval.ptr)->nodeType).c_str());
							(yyval.ptr)->size = getSize(a);
							}
#line 3271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 948 "src/comp.y" /* yacc.c:1646  */
    {   typeName =string("");
                          funcArguments = string("");
                           paramTable();  }
#line 3279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 953 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=term_symb("*");(yyval.ptr)->nodeType=string("*");}
#line 3285 "y.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 954 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("*",NULL,(yyvsp[0].ptr),NULL);(yyval.ptr)->nodeType=string("*");}
#line 3291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 955 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("*",NULL,(yyvsp[0].ptr),NULL);(yyval.ptr)->nodeType=string("*")+(yyvsp[0].ptr)->nodeType;}
#line 3297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 956 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("*",NULL,(yyvsp[-1].ptr),(yyvsp[0].ptr));(yyval.ptr)->nodeType=string("*")+(yyvsp[0].ptr)->nodeType;}
#line 3303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 960 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3309 "y.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 961 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("type_qualifier_list",NULL,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 3315 "y.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 966 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3321 "y.tab.c" /* yacc.c:1646  */
    break;

  case 150:
#line 967 "src/comp.y" /* yacc.c:1646  */
    {	funcArguments = funcArguments+string(",...");
					(yyval.ptr)=non_term_symb("parameter_type_list",NULL,(yyvsp[-2].ptr),term_symb("ELLIPSIS"));
					}
#line 3329 "y.tab.c" /* yacc.c:1646  */
    break;

  case 151:
#line 973 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3335 "y.tab.c" /* yacc.c:1646  */
    break;

  case 152:
#line 974 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("parameter_list",NULL,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 3341 "y.tab.c" /* yacc.c:1646  */
    break;

  case 153:
#line 978 "src/comp.y" /* yacc.c:1646  */
    {

          //paramTable();
         if((yyvsp[0].ptr)->exprType==1){ char *t=new char();
                     strcpy(t,((yyvsp[0].ptr)->nodeType).c_str());
                     char *key =new char();
                     strcpy(key,((yyvsp[0].ptr)->nodeKey).c_str());
                  if(scopeLookup((yyvsp[0].ptr)->nodeKey)){ yyerror("Error : redeclaration of %s",key);}
                   else {  insertSymbol(*curr,key,t,(yyvsp[0].ptr)->size,0,1);}
                if(funcArguments==string(""))funcArguments=((yyvsp[0].ptr)->nodeType);
               else funcArguments= funcArguments+string(",")+((yyvsp[0].ptr)->nodeType);
                     }
        (yyval.ptr)=non_term_symb("parameter_declaration",NULL,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 3359 "y.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 991 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("parameter_declaration",NULL,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 3365 "y.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 992 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3371 "y.tab.c" /* yacc.c:1646  */
    break;

  case 156:
#line 996 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=term_symb((yyvsp[0].str));}
#line 3377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 157:
#line 997 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("identifier_list",NULL,(yyvsp[-2].ptr),term_symb((yyvsp[0].str)));}
#line 3383 "y.tab.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1001 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3389 "y.tab.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1002 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("type_name",NULL,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 3395 "y.tab.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1006 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3401 "y.tab.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1007 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3407 "y.tab.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1008 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=non_term_symb("abstract_declarator",NULL,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 3413 "y.tab.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1012 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[-1].ptr);}
#line 3419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1013 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("[ ]");}
#line 3425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1014 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[-1].ptr);}
#line 3431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1015 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("direct_abstract_declarator" , "[ ]", (yyvsp[-2].ptr),NULL);}
#line 3437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1016 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("direct_abstract_declarator",NULL, (yyvsp[-3].ptr), (yyvsp[-1].ptr));}
#line 3443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1017 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("( )");}
#line 3449 "y.tab.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1018 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[-1].ptr);}
#line 3455 "y.tab.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1019 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("direct_abstract_declarator","( )", (yyvsp[-2].ptr),NULL);}
#line 3461 "y.tab.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1020 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("direct_abstract_declarator", NULL, (yyvsp[-3].ptr), (yyvsp[-1].ptr));}
#line 3467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1024 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3473 "y.tab.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1025 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[-1].ptr); (yyval.ptr)->nodeType = (yyvsp[-1].ptr)->nodeType+string("*");}
#line 3479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1026 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("initializer", (yyvsp[-1].str), (yyvsp[-2].ptr) ,NULL);
									(yyval.ptr)->nodeType = (yyvsp[-2].ptr)->nodeType+string("*"); (yyval.ptr)->exprType =(yyvsp[-2].ptr)->exprType;
								}
#line 3487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1032 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);(yyval.ptr)->exprType=1;}
#line 3493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1033 "src/comp.y" /* yacc.c:1646  */
    {
          (yyval.ptr) = non_term_symb("initializer_list", NULL, (yyvsp[-3].ptr) ,(yyvsp[0].ptr));
          (yyval.ptr)->nodeType = (yyvsp[-3].ptr)->nodeType;
           char* a =validAssign((yyvsp[-3].ptr)->nodeType,(yyvsp[-1].number)->nodeType);
               if(a){
                    if(!strcmp(a,"true")){ ; }
                    if(!strcmp(a,"warning")){ ;
                         yyerror("Warning : Assignment with incompatible pointer type");
                         }
                     }
                else{ yyerror("Error : Incompatible types when initializing type \'%s\' to \'%s\' ",((yyvsp[-3].ptr)->nodeType).c_str(),((yyvsp[-1].number)->nodeType).c_str()); }
           (yyval.ptr)->exprType = (yyvsp[-3].ptr)->exprType+1;
        }
#line 3511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1049 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3517 "y.tab.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1050 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1051 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1052 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1053 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1054 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1058 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("labeled_statement", NULL, term_symb((yyvsp[-3].str)), (yyvsp[0].ptr));}
#line 3553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1059 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("labeled_statement", term_symb("CASE"), (yyvsp[-2].ptr), (yyvsp[0].ptr));}
#line 3559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1060 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("labeled_statement", NULL, term_symb("DEFAULT"), (yyvsp[0].ptr));}
#line 3565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1064 "src/comp.y" /* yacc.c:1646  */
    {isFunc=0;(yyval.ptr) = term_symb("{ }");}
#line 3571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1065 "src/comp.y" /* yacc.c:1646  */
    {if(blockSym){ string s((yyvsp[-2].str));
                                    s=s+string(".csv");
                                    string u((yyvsp[-2].str));
                                    //printSymTables(curr,s);
                                    //updateSymTable(u); blockSym--;
									
                                 } (yyval.ptr) = (yyvsp[-1].ptr);
                               }
#line 3584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1073 "src/comp.y" /* yacc.c:1646  */
    {if(blockSym){ string s((yyvsp[-2].str));
                                    s=s+string(".csv");
                                    string u((yyvsp[-2].str));
                                    //printSymTables(curr,s);
                                    //updateSymTable(u); blockSym--;
									
                                 } (yyval.ptr) = (yyvsp[-1].ptr);
                               }
#line 3597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1081 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("compound_statement",NULL, (yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 3603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1085 "src/comp.y" /* yacc.c:1646  */
    { if(isFunc==0) {symNumber++;
                        symFileName = /*string("symTableFunc")+to_string(funcSym)*/funcName+string("Block")+to_string(symNumber);
                        //scope=S_BLOCK;
                        //makeSymTable(symFileName,scope,string("12345"));
                        char * y=new char();
                        strcpy(y,symFileName.c_str());
                        (yyval.str) = y;
                        //blockSym++;
                        }
                       isFunc=0;
              }
#line 3619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1100 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 3625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1101 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("declaration_list", NULL, (yyvsp[-2].ptr), (yyvsp[-1].number));}
#line 3631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1105 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1106 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("statement_list", NULL, (yyvsp[-2].ptr), (yyvsp[-1].number));}
#line 3643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1110 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb(";");}
#line 3649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1111 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[-1].ptr);}
#line 3655 "y.tab.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1115 "src/comp.y" /* yacc.c:1646  */
    {
                        //if($3->truelist.begin()==$3->truelist.end()){
                        //    int k = emit(pair<string, sEntry*>("GOTO", lookup("goto")),pair<string, sEntry*>("IF", lookup("if")), $3->place, pair<string, sEntry*>("", NULL ),0);
                        //    int k1 = emit(pair<string, sEntry*>("GOTO", lookup("goto")),pair<string, sEntry*>("", NULL), pair<string, sEntry*>("", NULL), pair<string, sEntry*>("", NULL ),0);
                        //    $3->truelist.push_back(k);
                        //    $3->falselist.push_back(k1);
                        //}
                        (yyval.ptr) = (yyvsp[-1].ptr);
  }
#line 3669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1127 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("IF (expr) stmt ELSE stmt", (yyvsp[-5].ptr), (yyvsp[-3].ptr), (yyvsp[0].ptr));}
#line 3675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1128 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("IF (expr) stmt", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));}
#line 3681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1129 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("SWITCH (expr) stmt", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));}
#line 3687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1133 "src/comp.y" /* yacc.c:1646  */
    {
                        //if($1->truelist.begin()==$1->truelist.end()){
                        //    int k = emit(pair<string, sEntry*>("GOTO", lookup("goto")),pair<string, sEntry*>("IF", lookup("if")), $1->place, pair<string, sEntry*>("", NULL ),0);
                        //    int k1 = emit(pair<string, sEntry*>("GOTO", lookup("goto")),pair<string, sEntry*>("", NULL), pair<string, sEntry*>("", NULL), pair<string, sEntry*>("", NULL ),0);
                        //    $1->truelist.push_back(k);
                        //    $1->falselist.push_back(k1);
						//}
                        (yyval.ptr) = (yyvsp[0].ptr);
  }
#line 3701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1146 "src/comp.y" /* yacc.c:1646  */
    {
                        //if($1->truelist.begin()==$1->truelist.end()){
                        //    int k = emit(pair<string, sEntry*>("GOTO", lookup("goto")),pair<string, sEntry*>("IF", lookup("if")), $1->place, pair<string, sEntry*>("", NULL ),0);
                        //    int k1 = emit(pair<string, sEntry*>("GOTO", lookup("goto")),pair<string, sEntry*>("", NULL), pair<string, sEntry*>("", NULL), pair<string, sEntry*>("", NULL ),0);
                        //    $1->truelist.push_back(k);
                        //    $1->falselist.push_back(k1);
						//}

                        (yyval.ptr) = (yyvsp[0].ptr);
  }
#line 3716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1159 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("WHILE (expr) stmt", NULL, (yyvsp[-3].ptr), (yyvsp[0].ptr));}
#line 3722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1160 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("DO stmt WHILE (expr)", NULL, (yyvsp[-6].ptr), (yyvsp[-2].ptr));}
#line 3728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1161 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_2("FOR (expr_stmt expr_stmt) stmt", (yyvsp[-5].ptr), (yyvsp[-3].ptr), (yyvsp[0].ptr));}
#line 3734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1162 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb_5("FOR (expr_stmt expr_stmt expr) stmt", NULL, (yyvsp[-7].ptr), (yyvsp[-5].ptr), (yyvsp[-3].ptr), (yyvsp[0].ptr));}
#line 3740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 207:
#line 1166 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("jump_statement", NULL, term_symb("GOTO"), term_symb((yyvsp[-1].str)));}
#line 3746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 208:
#line 1167 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("continue");}
#line 3752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1168 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("break");}
#line 3758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 210:
#line 1169 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = term_symb("return");}
#line 3764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 211:
#line 1170 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("jump_statement", NULL, term_symb("return"), (yyvsp[-1].ptr));}
#line 3770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 212:
#line 1174 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = (yyvsp[0].ptr);}
#line 3776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 213:
#line 1175 "src/comp.y" /* yacc.c:1646  */
    {(yyval.ptr) = non_term_symb("translation_unit", NULL, (yyvsp[-2].ptr), (yyvsp[0].ptr));}
#line 3782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 214:
#line 1179 "src/comp.y" /* yacc.c:1646  */
    {typeName=string("");(yyval.ptr) = (yyvsp[0].ptr);}
#line 3788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 215:
#line 1180 "src/comp.y" /* yacc.c:1646  */
    {typeName=string("");(yyval.ptr) = (yyvsp[0].ptr);}
#line 3794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 216:
#line 1186 "src/comp.y" /* yacc.c:1646  */
    {      typeName=string("");
                string s((yyvsp[-2].str));
                string u = s+string(".csv");
                printSymTables(curr,u);
                symNumber=0;
               updateSymTable(s);
                (yyval.ptr) = non_term_symb_4("function_definition", (yyvsp[-4].ptr), (yyvsp[-3].ptr), (yyvsp[-1].ptr), (yyvsp[0].ptr), NULL);
         }
#line 3807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 217:
#line 1194 "src/comp.y" /* yacc.c:1646  */
    {
              typeName=string("");
              string s((yyvsp[-1].str));string u =s+string(".csv");
              printSymTables(curr,u);
              symNumber=0;
              updateSymTable(s);
              (yyval.ptr) = non_term_symb_2("function_definition", (yyvsp[-3].ptr), (yyvsp[-2].ptr), (yyvsp[0].ptr));
            }
#line 3820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1202 "src/comp.y" /* yacc.c:1646  */
    { (yyval.ptr) = non_term_symb_2("function_definition",(yyvsp[-2].ptr),(yyvsp[-1].ptr),(yyvsp[0].ptr));
														//DOUBTFULL
													}
#line 3828 "y.tab.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1205 "src/comp.y" /* yacc.c:1646  */
    { (yyval.ptr) = non_term_symb_2("function_definition", (yyvsp[-1].ptr),NULL,(yyvsp[0].ptr));
									//DOUBTFULL
									}
#line 3836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 220:
#line 1211 "src/comp.y" /* yacc.c:1646  */
    { typeName=string("");scope = S_FUNC;
                                         isFunc = 1;
                                         funcSym++;
                                         symFileName = funcName;//string("symTableFunc")+to_string(funcSym);
                                         makeSymTable(symFileName,scope,funcType);
                                         char* y= new char();
                                         strcpy(y,symFileName.c_str());
                                         (yyval.str) = y;
       }
#line 3850 "y.tab.c" /* yacc.c:1646  */
    break;


#line 3854 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1222 "src/comp.y" /* yacc.c:1906  */

