
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser/parser.y"

#include <cstdio>
#include <iostream>
#include "../lexer/lexer.hpp"
#include "../ast/ast.hpp"

#include <string>
#include<stack>
using namespace std;


extern int lineno;
extern int int_counter;
extern int char_counter;
extern int array_int_counter;
extern int array_char_counter;


SymbolTable st;
FunctionTable ft;



/* Line 189 of yacc.c  */
#line 97 "parser/parser.cpp"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_eof = 0,
     T_and = 258,
     T_char = 259,
     T_div = 260,
     T_do = 261,
     T_else = 262,
     T_fun = 263,
     T_if = 264,
     T_int = 265,
     T_mod = 266,
     T_not = 267,
     T_nothing = 268,
     T_or = 269,
     T_ref = 270,
     T_return = 271,
     T_then = 272,
     T_var = 273,
     T_while = 274,
     T_writeInteger = 275,
     T_writeChar = 276,
     T_writeString = 277,
     T_readInteger = 278,
     T_readString = 279,
     T_readChar = 280,
     T_ascii = 281,
     T_chr = 282,
     T_strlen = 283,
     T_strcmp = 284,
     T_strcpy = 285,
     T_strcat = 286,
     T_id = 287,
     T_const_int = 288,
     T_const_char = 289,
     T_const_string = 290,
     T_geq = 291,
     T_leq = 292,
     T_assign = 293
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 24 "parser/parser.y"
   
   AST *program;
   int num;
   char *id;
   char op;
   char *const_char;
   char *const_str;
   Expr *expr;
   Stmt *stmt;
   Cond *cond; 
   Block *stmt_list;
   Func_def *func_def;
   Local_def_gen *local_def_gen;
   Header *header;
   Fpar_def_gen *fpar_def_gen;
   Fpar_def *fpar_def;
   Comma_id_gen *comma_id_gen;
   Type_gen *type_gen;
   Typos typos;
   MyType *type;
   Ret_type *ret_type;
   Fpar_type *fpar_type;
   Local_def *local_def;
   Func_decl *func_decl;
   Var_def *var_def;
   Func_call_stmt *func_call_stmt;
   Func_call_expr *func_call_expr;
   Comma_expr_gen *comma_expr_gen;
   L_value *l_value;
   Expr *expr_high;
   Cond *cond_high;
 



/* Line 214 of yacc.c  */
#line 208 "parser/parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 220 "parser/parser.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   365

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNRULES -- Number of states.  */
#define YYNSTATES  217

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    40,     2,     2,     2,     2,
      46,    47,    45,    43,    50,    44,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    49,
      42,    39,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    51,     2,    52,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    10,    13,    20,    29,    30,
      34,    40,    45,    46,    50,    52,    54,    57,    58,    63,
      65,    67,    72,    75,    77,    79,    81,    84,    91,    93,
      98,   100,   103,   108,   115,   120,   123,   127,   133,   139,
     145,   151,   158,   165,   172,   176,   177,   180,   184,   190,
     194,   200,   201,   205,   207,   209,   214,   216,   218,   220,
     222,   224,   228,   232,   236,   240,   244,   248,   252,   257,
     262,   267,   272,   277,   284,   288,   291,   294,   296,   300,
     304,   308,   312,   316,   320,   324,   328,   332
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    -1,    59,    58,    72,    -1,    -1,
      68,    58,    -1,     8,    32,    46,    47,    48,    66,    -1,
       8,    32,    46,    61,    60,    47,    48,    66,    -1,    -1,
      49,    61,    60,    -1,    15,    32,    62,    48,    67,    -1,
      32,    62,    48,    67,    -1,    -1,    50,    32,    62,    -1,
      10,    -1,     4,    -1,    63,    65,    -1,    -1,    51,    33,
      52,    65,    -1,    63,    -1,    13,    -1,    63,    51,    52,
      65,    -1,    63,    65,    -1,    57,    -1,    69,    -1,    70,
      -1,    59,    49,    -1,    18,    32,    62,    48,    64,    49,
      -1,    49,    -1,    77,    38,    78,    49,    -1,    72,    -1,
      74,    49,    -1,     9,    80,    17,    71,    -1,     9,    80,
      17,    71,     7,    71,    -1,    19,    80,     6,    71,    -1,
      16,    49,    -1,    16,    78,    49,    -1,    20,    46,    78,
      47,    49,    -1,    21,    46,    78,    47,    49,    -1,    22,
      46,    32,    47,    49,    -1,    22,    46,    35,    47,    49,
      -1,    24,    46,    78,    50,    32,    47,    -1,    30,    46,
      77,    50,    77,    47,    -1,    31,    46,    77,    50,    77,
      47,    -1,    53,    73,    54,    -1,    -1,    73,    71,    -1,
      32,    46,    47,    -1,    32,    46,    78,    76,    47,    -1,
      32,    46,    47,    -1,    32,    46,    78,    76,    47,    -1,
      -1,    50,    78,    76,    -1,    32,    -1,    35,    -1,    77,
      51,    78,    52,    -1,    33,    -1,    34,    -1,    77,    -1,
      79,    -1,    75,    -1,    78,    43,    78,    -1,    78,    44,
      78,    -1,    78,    45,    78,    -1,    78,     5,    78,    -1,
      78,    11,    78,    -1,    23,    46,    47,    -1,    25,    46,
      47,    -1,    26,    46,    34,    47,    -1,    26,    46,    32,
      47,    -1,    27,    46,    33,    47,    -1,    27,    46,    32,
      47,    -1,    28,    46,    77,    47,    -1,    29,    46,    77,
      50,    77,    47,    -1,    46,    78,    47,    -1,    43,    78,
      -1,    44,    78,    -1,    81,    -1,    80,     3,    80,    -1,
      80,    14,    80,    -1,    78,    39,    78,    -1,    78,    40,
      78,    -1,    78,    41,    78,    -1,    78,    42,    78,    -1,
      78,    36,    78,    -1,    78,    37,    78,    -1,    46,    80,
      47,    -1,    12,    80,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   145,   145,   159,   163,   164,   168,   169,   173,   174,
     178,   179,   183,   184,   188,   189,   193,   197,   198,   202,
     203,   207,   208,   212,   213,   214,   218,   222,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   245,   249,   250,   254,   255,   259,
     260,   265,   266,   270,   271,   272,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   297,   298,   299,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   315,   316
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "T_eof", "error", "$undefined", "\"and\"", "\"char\"", "\"div\"",
  "\"do\"", "\"else\"", "\"fun\"", "\"if\"", "\"int\"", "\"mod\"",
  "\"not\"", "\"nothing\"", "\"or\"", "\"ref\"", "\"return\"", "\"then\"",
  "\"var\"", "\"while\"", "\"writeInteger\"", "\"writeChar\"",
  "\"writeString\"", "\"readInteger\"", "\"readString\"", "\"readChar\"",
  "\"ascii\"", "\"chr\"", "\"strlen\"", "\"strcmp\"", "\"strcpy\"",
  "\"strcat\"", "T_id", "\"const_int\"", "T_const_char", "T_const_string",
  "\">=\"", "\"<=\"", "\"<-\"", "'='", "'#'", "'>'", "'<'", "'+'", "'-'",
  "'*'", "'('", "')'", "':'", "';'", "','", "'['", "']'", "'{'", "'}'",
  "$accept", "program", "func_def", "local_def_gen", "header",
  "fpar_def_gen", "fpar_def", "comma_id_gen", "data_type", "type",
  "type_gen", "ret_type", "fpar_type", "local_def", "func_decl", "var_def",
  "stmt", "block", "stmt_list", "func_call_stmt", "func_call_expr",
  "comma_expr_gen", "l_value", "expr", "expr_high", "cond", "cond_high", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,    61,
      35,    62,    60,    43,    45,    42,    40,    41,    58,    59,
      44,    91,    93,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    65,    65,    66,
      66,    67,    67,    68,    68,    68,    69,    70,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    77,    77,    77,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    79,    79,    79,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    81,    81
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     0,     2,     6,     8,     0,     3,
       5,     4,     0,     3,     1,     1,     2,     0,     4,     1,
       1,     4,     2,     1,     1,     1,     2,     6,     1,     4,
       1,     2,     4,     6,     4,     2,     3,     5,     5,     5,
       5,     6,     6,     6,     3,     0,     2,     3,     5,     3,
       5,     0,     3,     1,     1,     4,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     4,     4,
       4,     4,     4,     6,     3,     2,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     4,     0,     1,     0,    23,     0,
       4,     4,    24,    25,     0,    12,    45,     3,    26,     5,
       0,    12,     0,     8,     0,     0,     0,    12,     0,     0,
       0,     0,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    53,    54,    28,    44,    46,    30,     0,
       0,     0,     0,    15,    14,    20,    19,     6,     8,     0,
      13,    17,     0,     0,     0,     0,     0,     0,     0,     0,
      53,    56,    57,     0,     0,     0,    60,    58,     0,    59,
       0,    77,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,    17,    11,     9,
       0,     0,    16,    27,    87,     0,     0,     0,     0,     0,
       0,     0,    75,    76,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,    53,     0,
       0,    47,    51,     0,     0,    10,     0,    22,     7,     0,
      66,    67,     0,     0,     0,     0,     0,     0,    49,    51,
      74,    86,    64,    65,    84,    85,    80,    81,    82,    83,
      61,    62,    63,    78,    79,    32,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,    55,    17,    17,
      69,    68,    71,    70,    72,     0,     0,     0,    37,    38,
      39,    40,     0,     0,     0,    51,    48,    21,    18,     0,
      50,    33,    41,    42,    43,    52,    73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     9,    10,    31,    23,    25,    56,    62,
     102,    57,    98,    11,    12,    13,    47,    48,    26,    49,
      76,   185,    77,    78,    79,    80,    81
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -155
static const yytype_int16 yypact[] =
{
       9,   -24,    44,  -155,    82,    14,  -155,    45,  -155,    38,
      13,    82,  -155,  -155,    11,    78,  -155,  -155,  -155,  -155,
     106,    78,   101,   114,   135,   127,     3,    78,   140,   126,
       0,   150,    78,    59,   222,   244,   222,   152,   154,   164,
     172,   173,   174,   175,  -155,  -155,  -155,  -155,  -155,   156,
     -37,   167,    59,  -155,  -155,  -155,  -155,  -155,   114,   178,
    -155,   184,   187,   222,   177,   191,   192,   197,   198,   200,
     206,  -155,  -155,   319,   319,   222,  -155,   202,   188,  -155,
      56,  -155,   319,  -155,    97,    75,   319,   319,    88,   319,
     141,   141,   269,  -155,   319,   319,    59,   207,  -155,  -155,
     126,   209,  -155,  -155,    58,   212,   213,    73,     7,   141,
     141,   294,    31,    31,   142,     6,   319,   319,   319,   319,
     319,   319,   319,   319,   319,   319,   319,   222,   222,   113,
     147,  -155,   113,   159,   169,   214,   215,     5,  -155,    48,
     145,  -155,    81,   116,     2,  -155,   -15,  -155,  -155,   211,
    -155,  -155,   217,   227,   228,   233,    50,   158,  -155,    81,
    -155,  -155,  -155,  -155,   196,   196,   196,   196,   196,   196,
      31,    31,  -155,  -155,   278,   275,  -155,   234,   235,   236,
     237,   257,   141,   141,   319,   252,  -155,  -155,   184,   184,
    -155,  -155,  -155,  -155,  -155,   141,   253,   113,  -155,  -155,
    -155,  -155,   258,   103,   104,    81,  -155,  -155,  -155,   121,
    -155,  -155,  -155,  -155,  -155,  -155,  -155
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -155,  -155,   291,   295,   307,   250,   279,   190,   -22,  -155,
     -93,   210,   218,  -155,  -155,  -155,  -126,   302,  -155,  -155,
    -155,  -154,   -26,    -7,  -155,   -34,  -155
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      50,    94,    85,   175,   147,   196,   176,   116,     5,   127,
     116,    61,    34,   117,    95,    20,   117,     1,   149,    35,
     128,     1,    36,    37,    38,    39,    20,    40,    84,   104,
      97,     7,    21,    41,    42,    43,   116,   188,    44,   154,
     155,   115,   117,    21,     6,   124,   125,   126,   124,   125,
     126,   215,    45,   161,   187,   181,    16,    46,    22,   127,
      14,   127,    18,    53,   139,   140,   112,   113,   114,    54,
     128,   211,   128,   129,    97,   130,   126,    15,   127,   133,
     134,   132,   137,   156,   157,   142,   116,   143,   144,   128,
       1,    16,   117,   173,   174,   207,   208,   194,   182,    95,
       7,    95,   116,    50,   159,   152,    50,   153,   117,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     135,   116,    34,   136,   124,   125,   126,   117,    24,    35,
      53,   184,    36,    37,    38,    39,    54,    40,    27,    55,
     124,   125,   126,    41,    42,    43,   131,   116,    44,    29,
     213,   214,   116,   117,    95,    95,   203,   204,   117,   124,
     125,   126,    45,    30,   116,   186,    16,    32,   216,   209,
     117,    50,    95,   138,   116,    33,    44,   205,   118,   119,
     117,   120,   121,   122,   123,   124,   125,   126,    52,   160,
     124,   125,   126,   116,   160,   183,    95,    59,    86,   117,
      87,   116,   124,   125,   126,    93,   177,   117,   195,    95,
      88,    28,   124,   125,   126,    96,   178,    51,    89,    90,
      91,    92,    60,   105,   118,   119,   100,   120,   121,   122,
     123,   124,   125,   126,    63,   101,   103,   106,   107,   124,
     125,   126,   149,   108,   109,    64,   110,    65,    66,    67,
      68,    69,   111,    95,    70,    71,    72,    44,   146,   150,
     151,   179,   180,   189,   190,    73,    74,    64,    75,    65,
      66,    67,    68,    69,   191,   192,    70,    71,    72,    44,
     193,   127,   197,   198,   199,   200,   201,    73,    74,   202,
      82,     3,    64,    83,    65,    66,    67,    68,    69,   206,
     210,    70,    71,    72,    44,   212,    19,     4,    99,    58,
     148,    17,    73,    74,   145,    82,   141,    64,     0,    65,
      66,    67,    68,    69,     0,     0,    70,    71,    72,    44,
       0,     0,     0,     0,     0,     0,     0,    73,    74,     0,
      82,   158,    64,     0,    65,    66,    67,    68,    69,     0,
       0,    70,    71,    72,    44,     0,     0,     0,     0,     0,
       0,     0,    73,    74,     0,    82
};

static const yytype_int16 yycheck[] =
{
      26,    38,    36,   129,    97,   159,   132,     5,    32,     3,
       5,    33,     9,    11,    51,    15,    11,     8,    33,    16,
      14,     8,    19,    20,    21,    22,    15,    24,    35,    63,
      52,    18,    32,    30,    31,    32,     5,    52,    35,    32,
      33,    75,    11,    32,     0,    43,    44,    45,    43,    44,
      45,   205,    49,    47,    52,    50,    53,    54,    47,     3,
      46,     3,    49,     4,    90,    91,    73,    74,    75,    10,
      14,   197,    14,    17,    96,    82,    45,    32,     3,    86,
      87,     6,    89,   109,   110,    92,     5,    94,    95,    14,
       8,    53,    11,   127,   128,   188,   189,    47,    50,    51,
      18,    51,     5,   129,   111,    32,   132,    34,    11,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
      32,     5,     9,    35,    43,    44,    45,    11,    50,    16,
       4,    50,    19,    20,    21,    22,    10,    24,    32,    13,
      43,    44,    45,    30,    31,    32,    49,     5,    35,    48,
      47,    47,     5,    11,    51,    51,   182,   183,    11,    43,
      44,    45,    49,    49,     5,    49,    53,    32,    47,   195,
      11,   197,    51,    32,     5,    48,    35,   184,    36,    37,
      11,    39,    40,    41,    42,    43,    44,    45,    48,    47,
      43,    44,    45,     5,    47,    50,    51,    47,    46,    11,
      46,     5,    43,    44,    45,    49,    47,    11,    50,    51,
      46,    21,    43,    44,    45,    48,    47,    27,    46,    46,
      46,    46,    32,    46,    36,    37,    48,    39,    40,    41,
      42,    43,    44,    45,    12,    51,    49,    46,    46,    43,
      44,    45,    33,    46,    46,    23,    46,    25,    26,    27,
      28,    29,    46,    51,    32,    33,    34,    35,    51,    47,
      47,    47,    47,    52,    47,    43,    44,    23,    46,    25,
      26,    27,    28,    29,    47,    47,    32,    33,    34,    35,
      47,     3,     7,    49,    49,    49,    49,    43,    44,    32,
      46,     0,    23,    49,    25,    26,    27,    28,    29,    47,
      47,    32,    33,    34,    35,    47,    11,     0,    58,    30,
     100,     9,    43,    44,    96,    46,    47,    23,    -1,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,
      46,    47,    23,    -1,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    56,    57,    59,    32,     0,    18,    57,    58,
      59,    68,    69,    70,    46,    32,    53,    72,    49,    58,
      15,    32,    47,    61,    50,    62,    73,    32,    62,    48,
      49,    60,    32,    48,     9,    16,    19,    20,    21,    22,
      24,    30,    31,    32,    35,    49,    54,    71,    72,    74,
      77,    62,    48,     4,    10,    13,    63,    66,    61,    47,
      62,    63,    64,    12,    23,    25,    26,    27,    28,    29,
      32,    33,    34,    43,    44,    46,    75,    77,    78,    79,
      80,    81,    46,    49,    78,    80,    46,    46,    46,    46,
      46,    46,    46,    49,    38,    51,    48,    63,    67,    60,
      48,    51,    65,    49,    80,    46,    46,    46,    46,    46,
      46,    46,    78,    78,    78,    80,     5,    11,    36,    37,
      39,    40,    41,    42,    43,    44,    45,     3,    14,    17,
      78,    49,     6,    78,    78,    32,    35,    78,    32,    77,
      77,    47,    78,    78,    78,    67,    51,    65,    66,    33,
      47,    47,    32,    34,    32,    33,    77,    77,    47,    78,
      47,    47,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    80,    80,    71,    71,    47,    47,    47,
      47,    50,    50,    50,    50,    76,    49,    52,    52,    52,
      47,    47,    47,    47,    47,    50,    76,     7,    49,    49,
      49,    49,    32,    77,    77,    78,    47,    65,    65,    77,
      47,    71,    47,    47,    47,    76,    47
};

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
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
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



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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

/* Line 1455 of yacc.c  */
#line 146 "parser/parser.y"
    { (yyval.program) = (yyvsp[(1) - (1)].func_def);
       // std::cout << "AST: " << *$1<<std::endl; 
         (yyvsp[(1) - (1)].func_def)->sem(); 
        //std::cout<<"SEM COMPLETED"<<std::endl;
        (yyvsp[(1) - (1)].func_def)->preCompile();
        //std::cout<<"preCompile COMPLETED"<<std::endl;
       
        (yyvsp[(1) - (1)].func_def)->llvm_compile_and_dump(); 
        
        ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 159 "parser/parser.y"
    { (yyval.func_def) = new Func_def((yyvsp[(1) - (3)].header), (yyvsp[(2) - (3)].local_def_gen), (yyvsp[(3) - (3)].stmt_list)); /*st.closeScope();*/ ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 163 "parser/parser.y"
    { (yyval.local_def_gen) = nullptr; ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 164 "parser/parser.y"
    { (yyval.local_def_gen) = new Local_def_gen((yyvsp[(1) - (2)].local_def), (yyvsp[(2) - (2)].local_def_gen)); ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 168 "parser/parser.y"
    { (yyval.header) = new Header((yyvsp[(2) - (6)].id), nullptr, nullptr, (yyvsp[(6) - (6)].ret_type));  ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 169 "parser/parser.y"
    { (yyval.header) = new Header((yyvsp[(2) - (8)].id), (yyvsp[(4) - (8)].fpar_def), (yyvsp[(5) - (8)].fpar_def_gen), (yyvsp[(8) - (8)].ret_type)); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 173 "parser/parser.y"
    { (yyval.fpar_def_gen) = nullptr; ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 174 "parser/parser.y"
    { (yyval.fpar_def_gen) = new Fpar_def_gen((yyvsp[(2) - (3)].fpar_def), (yyvsp[(3) - (3)].fpar_def_gen)); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 178 "parser/parser.y"
    { (yyval.fpar_def) = new Fpar_def(true, (yyvsp[(2) - (5)].id), (yyvsp[(3) - (5)].comma_id_gen), (yyvsp[(5) - (5)].fpar_type)); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 179 "parser/parser.y"
    { (yyval.fpar_def) = new Fpar_def(false, (yyvsp[(1) - (4)].id), (yyvsp[(2) - (4)].comma_id_gen), (yyvsp[(4) - (4)].fpar_type)); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 183 "parser/parser.y"
    { (yyval.comma_id_gen) = nullptr; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 184 "parser/parser.y"
    { (yyval.comma_id_gen) = new Comma_id_gen((yyvsp[(2) - (3)].id), (yyvsp[(3) - (3)].comma_id_gen)); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 188 "parser/parser.y"
    { (yyval.typos) =  TYPE_int; ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 189 "parser/parser.y"
    { (yyval.typos) =  TYPE_char; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 193 "parser/parser.y"
    { (yyval.type) = new MyType((yyvsp[(1) - (2)].typos), (yyvsp[(2) - (2)].type_gen)); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 197 "parser/parser.y"
    { (yyval.type_gen) = nullptr; ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 198 "parser/parser.y"
    { (yyval.type_gen) = new Type_gen((yyvsp[(2) - (4)].num), (yyvsp[(4) - (4)].type_gen)); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 202 "parser/parser.y"
    { (yyval.ret_type) = new Ret_type((yyvsp[(1) - (1)].typos)); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 203 "parser/parser.y"
    { (yyval.ret_type) = new Ret_type(TYPE_nothing); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 207 "parser/parser.y"
    { (yyval.fpar_type) = new Fpar_type((yyvsp[(1) - (4)].typos), (yyvsp[(4) - (4)].type_gen), 1); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 208 "parser/parser.y"
    { (yyval.fpar_type) = new Fpar_type((yyvsp[(1) - (2)].typos), (yyvsp[(2) - (2)].type_gen), 0); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 212 "parser/parser.y"
    { (yyval.local_def) = new Local_def((yyvsp[(1) - (1)].func_def), nullptr, nullptr); ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 213 "parser/parser.y"
    { (yyval.local_def) = new Local_def(nullptr, (yyvsp[(1) - (1)].func_decl), nullptr); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 214 "parser/parser.y"
    { (yyval.local_def) = new Local_def(nullptr, nullptr, (yyvsp[(1) - (1)].var_def)); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 218 "parser/parser.y"
    { (yyval.func_decl) = new Func_decl((yyvsp[(1) - (2)].header)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 222 "parser/parser.y"
    { (yyval.var_def) = new Var_def((yyvsp[(2) - (6)].id), (yyvsp[(3) - (6)].comma_id_gen), (yyvsp[(5) - (6)].type)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 226 "parser/parser.y"
    { (yyval.stmt) = nullptr; ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 227 "parser/parser.y"
    { (yyval.stmt) = new Assign((yyvsp[(1) - (4)].l_value), (yyvsp[(3) - (4)].expr)); ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 228 "parser/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt_list); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 229 "parser/parser.y"
    { (yyval.stmt) = (yyvsp[(1) - (2)].func_call_stmt); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 230 "parser/parser.y"
    { (yyval.stmt) = new If((yyvsp[(2) - (4)].cond), (yyvsp[(4) - (4)].stmt), nullptr); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 231 "parser/parser.y"
    { (yyval.stmt) = new If((yyvsp[(2) - (6)].cond), (yyvsp[(4) - (6)].stmt), (yyvsp[(6) - (6)].stmt)); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 232 "parser/parser.y"
    { (yyval.stmt) = new While((yyvsp[(2) - (4)].cond), (yyvsp[(4) - (4)].stmt)); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 233 "parser/parser.y"
    { (yyval.stmt) = new Return(nullptr); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 234 "parser/parser.y"
    { (yyval.stmt) = new Return((yyvsp[(2) - (3)].expr)); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 235 "parser/parser.y"
    { (yyval.stmt) = new Write_Integer((yyvsp[(3) - (5)].expr)); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 236 "parser/parser.y"
    { (yyval.stmt) = new Write_Char((yyvsp[(3) - (5)].expr)); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 237 "parser/parser.y"
    { (yyval.stmt) = new Write_String((yyvsp[(3) - (5)].id),nullptr,0); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 238 "parser/parser.y"
    { (yyval.stmt) = new Write_String(nullptr,(yyvsp[(3) - (5)].const_str),1); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 239 "parser/parser.y"
    { (yyval.stmt) = new ReadString((yyvsp[(3) - (6)].expr), (yyvsp[(5) - (6)].id)); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 240 "parser/parser.y"
    { (yyval.stmt) = new StrCpy((yyvsp[(3) - (6)].l_value), (yyvsp[(5) - (6)].l_value)); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 241 "parser/parser.y"
    { (yyval.stmt) = new StrCat((yyvsp[(3) - (6)].l_value), (yyvsp[(5) - (6)].l_value)); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 245 "parser/parser.y"
    { (yyval.stmt_list) = (yyvsp[(2) - (3)].stmt_list);  ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 249 "parser/parser.y"
    { (yyval.stmt_list) = new Block(); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 250 "parser/parser.y"
    { (yyvsp[(1) - (2)].stmt_list)->append_stmt((yyvsp[(2) - (2)].stmt)); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 254 "parser/parser.y"
    { (yyval.func_call_stmt) = new Func_call_stmt((yyvsp[(1) - (3)].id), nullptr, nullptr); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 255 "parser/parser.y"
    { (yyval.func_call_stmt) = new Func_call_stmt((yyvsp[(1) - (5)].id), (yyvsp[(3) - (5)].expr), (yyvsp[(4) - (5)].comma_expr_gen)); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 259 "parser/parser.y"
    { (yyval.func_call_expr) = new Func_call_expr((yyvsp[(1) - (3)].id), nullptr, nullptr); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 260 "parser/parser.y"
    { (yyval.func_call_expr) = new Func_call_expr((yyvsp[(1) - (5)].id), (yyvsp[(3) - (5)].expr), (yyvsp[(4) - (5)].comma_expr_gen)); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 265 "parser/parser.y"
    { (yyval.comma_expr_gen) = nullptr; ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 266 "parser/parser.y"
    { (yyval.comma_expr_gen) = new Comma_expr_gen((yyvsp[(2) - (3)].expr), (yyvsp[(3) - (3)].comma_expr_gen)); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 270 "parser/parser.y"
    { (yyval.l_value) = new L_value(nullptr,nullptr,(yyvsp[(1) - (1)].id),nullptr,1); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 271 "parser/parser.y"
    { (yyval.l_value) = new L_value(nullptr, nullptr, nullptr, (yyvsp[(1) - (1)].const_str),2); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 272 "parser/parser.y"
    { (yyval.l_value) = new L_value((yyvsp[(1) - (4)].l_value), (yyvsp[(3) - (4)].expr),nullptr, nullptr,3 ); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 276 "parser/parser.y"
    { (yyval.expr) = new IntConst((yyvsp[(1) - (1)].num)); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 277 "parser/parser.y"
    { (yyval.expr) = new Const_char((yyvsp[(1) - (1)].const_char)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 278 "parser/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].l_value); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 279 "parser/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].expr_high); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 280 "parser/parser.y"
    { (yyval.expr) = (yyvsp[(1) - (1)].func_call_expr); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 281 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr),"+",(yyvsp[(3) - (3)].expr)); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 282 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr),"-",(yyvsp[(3) - (3)].expr)); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 283 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr),"*",(yyvsp[(3) - (3)].expr)); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 284 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr),"/",(yyvsp[(3) - (3)].expr)); ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 285 "parser/parser.y"
    { (yyval.expr) = new BinOp((yyvsp[(1) - (3)].expr),"%",(yyvsp[(3) - (3)].expr)); ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 286 "parser/parser.y"
    { (yyval.expr) = new ReadInteger(); ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 287 "parser/parser.y"
    { (yyval.expr) = new ReadChar(); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 288 "parser/parser.y"
    { (yyval.expr) = new Ascii((yyvsp[(3) - (4)].const_char),nullptr,0); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 289 "parser/parser.y"
    { (yyval.expr) = new Ascii(nullptr,(yyvsp[(3) - (4)].id),1); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 290 "parser/parser.y"
    { (yyval.expr) = new Chr((yyvsp[(3) - (4)].num),nullptr,0); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 291 "parser/parser.y"
    { (yyval.expr) = new Chr(-1,(yyvsp[(3) - (4)].id),1); ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 292 "parser/parser.y"
    { (yyval.expr) = new Strlen((yyvsp[(3) - (4)].l_value)); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 293 "parser/parser.y"
    { (yyval.expr) = new StrCmp((yyvsp[(3) - (6)].l_value), (yyvsp[(5) - (6)].l_value)); ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 297 "parser/parser.y"
    { (yyval.expr_high) = (yyvsp[(2) - (3)].expr); ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 298 "parser/parser.y"
    { (yyval.expr_high) = new UnOp('+', (yyvsp[(2) - (2)].expr)); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 299 "parser/parser.y"
    { (yyval.expr_high) = new UnOp('-', (yyvsp[(2) - (2)].expr)); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 303 "parser/parser.y"
    { (yyval.cond) = (yyvsp[(1) - (1)].cond_high); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 304 "parser/parser.y"
    { (yyval.cond) = new Cond((yyvsp[(1) - (3)].cond), "&", (yyvsp[(3) - (3)].cond)); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 305 "parser/parser.y"
    { (yyval.cond) = new Cond((yyvsp[(1) - (3)].cond), "|", (yyvsp[(3) - (3)].cond)); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 306 "parser/parser.y"
    { (yyval.cond) = new Compare((yyvsp[(1) - (3)].expr), "=", (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 307 "parser/parser.y"
    { (yyval.cond) = new Compare((yyvsp[(1) - (3)].expr), "#", (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 308 "parser/parser.y"
    { (yyval.cond) = new Compare((yyvsp[(1) - (3)].expr), ">", (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 309 "parser/parser.y"
    { (yyval.cond) = new Compare((yyvsp[(1) - (3)].expr), "<", (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 310 "parser/parser.y"
    { (yyval.cond) = new Compare((yyvsp[(1) - (3)].expr), "g", (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 311 "parser/parser.y"
    { (yyval.cond) = new Compare((yyvsp[(1) - (3)].expr), "l", (yyvsp[(3) - (3)].expr)); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 315 "parser/parser.y"
    { (yyval.cond_high) = (yyvsp[(2) - (3)].cond); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 316 "parser/parser.y"
    { (yyval.cond_high) = new Cond((yyvsp[(2) - (2)].cond),"!",nullptr); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2233 "parser/parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
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
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 323 "parser/parser.y"


int main() {
  int result = yyparse();
 // if (result == 0) printf("Success.\n");
  return result;

}
