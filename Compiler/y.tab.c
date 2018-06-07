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
#line 1 "proc.y" /* yacc.c:339  */

void yyerror (char const *s);
int yylex();
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include "symbol.h"
#include "y.tab.h"
#include "codegen.h"
//#define SIZE_NAME 128

extern char* yytext;
extern int currentScope;
void typeCheck(struct value_and_type,struct value_and_type);
void typeErrNotFound();
void typeErrRedeclared();
void typeErrMismatch();
id* temp;

#line 85 "y.tab.c" /* yacc.c:339  */

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
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROCESSOR = 258,
    IF = 259,
    ELSE = 260,
    WHILE = 261,
    FOR = 262,
    CONTINUE = 263,
    BREAK = 264,
    _REBOOT = 265,
    RETURN = 266,
    _HALT = 267,
    _SUSPEND = 268,
    INT = 269,
    REAL = 270,
    CHAR = 271,
    STRING = 272,
    STATIC = 273,
    VOID = 274,
    EQUAL = 275,
    DIFF = 276,
    GRTEQU = 277,
    LESEQU = 278,
    RAND = 279,
    ROR = 280,
    CONSTANT_REAL = 281,
    CONSTANT_CHAR = 282,
    CONSTANT_STRING = 283,
    CONSTANT_HEX = 284,
    CONSTANT_OCT = 285,
    SHL = 286,
    SHR = 287,
    SAR = 288,
    INC = 289,
    DEC = 290,
    ASSAR = 291,
    ASSHL = 292,
    ASSHR = 293,
    ASADD = 294,
    ASSUB = 295,
    ASDIV = 296,
    ASMOD = 297,
    ASMUL = 298,
    ASAND = 299,
    ASOR = 300,
    ASEOR = 301,
    CONSTANT_INT = 302,
    ID = 303
  };
#endif
/* Tokens.  */
#define PROCESSOR 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define FOR 262
#define CONTINUE 263
#define BREAK 264
#define _REBOOT 265
#define RETURN 266
#define _HALT 267
#define _SUSPEND 268
#define INT 269
#define REAL 270
#define CHAR 271
#define STRING 272
#define STATIC 273
#define VOID 274
#define EQUAL 275
#define DIFF 276
#define GRTEQU 277
#define LESEQU 278
#define RAND 279
#define ROR 280
#define CONSTANT_REAL 281
#define CONSTANT_CHAR 282
#define CONSTANT_STRING 283
#define CONSTANT_HEX 284
#define CONSTANT_OCT 285
#define SHL 286
#define SHR 287
#define SAR 288
#define INC 289
#define DEC 290
#define ASSAR 291
#define ASSHL 292
#define ASSHR 293
#define ASADD 294
#define ASSUB 295
#define ASDIV 296
#define ASMOD 297
#define ASMUL 298
#define ASAND 299
#define ASOR 300
#define ASEOR 301
#define CONSTANT_INT 302
#define ID 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "proc.y" /* yacc.c:355  */

char name[128];
struct value_and_type
{
	int type;
	char isID;
	long vali;
	double valr;
	char valc;
} vt;

#line 233 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 250 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   468

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  180

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    56,     2,     2,     2,    58,    51,     2,
      49,    50,    52,    53,    64,    54,     2,    57,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    65,
      59,    63,    60,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    67,    61,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    68,    62,    69,    55,     2,     2,     2,
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
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    63,    63,    77,    83,    89,    95,    96,   103,   105,
     107,   113,   115,   117,   119,   124,   125,   126,   127,   128,
     129,   133,   135,   140,   142,   144,   146,   151,   153,   155,
     160,   162,   164,   169,   171,   173,   175,   177,   182,   184,
     186,   191,   193,   198,   200,   205,   207,   212,   214,   219,
     221,   226,   228,   252,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   269,   275,   279,   286,   287,   290,
     292,   297,   298,   303,   304,   305,   310,   316,   317,   320,
     322,   323,   324,   325,   326,   327,   330,   331,   332,   336,
     336,   340,   341,   345,   346,   350,   351,   362,   361,   373,
     379,   380,   381,   385,   386,   390,   391,   396,   395
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROCESSOR", "IF", "ELSE", "WHILE",
  "FOR", "CONTINUE", "BREAK", "_REBOOT", "RETURN", "_HALT", "_SUSPEND",
  "INT", "REAL", "CHAR", "STRING", "STATIC", "VOID", "EQUAL", "DIFF",
  "GRTEQU", "LESEQU", "RAND", "ROR", "CONSTANT_REAL", "CONSTANT_CHAR",
  "CONSTANT_STRING", "CONSTANT_HEX", "CONSTANT_OCT", "SHL", "SHR", "SAR",
  "INC", "DEC", "ASSAR", "ASSHL", "ASSHR", "ASADD", "ASSUB", "ASDIV",
  "ASMOD", "ASMUL", "ASAND", "ASOR", "ASEOR", "CONSTANT_INT", "ID", "'('",
  "')'", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'",
  "'>'", "'^'", "'|'", "'='", "','", "';'", "'['", "']'", "'{'", "'}'",
  "$accept", "primary_expression", "postfix_expression",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "assignment_expression", "assignment_operator", "expression",
  "declaration", "declaration_specifiers", "init_declarator_list",
  "init_declarator", "type_specifier", "direct_declarator", "statement",
  "control_statement", "compound_statement", "$@1", "block_item_list",
  "block_item", "expression_statement", "selection_statement", "$@2",
  "iteration_statement", "jump_statement", "translation_unit",
  "processor_declaration", "$@3", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,    40,
      41,    38,    42,    43,    45,   126,    33,    47,    37,    60,
      62,    94,   124,    61,    44,    59,    91,    93,   123,   125
};
# endif

#define YYPACT_NINF -88

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-88)))

#define YYTABLE_NINF -80

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      31,   -35,    12,   -88,   -32,   -88,   -88,    17,    45,    48,
      49,    74,    76,   -88,    56,   -88,   -88,    84,    78,    79,
      80,    65,    69,    88,    89,    91,   -88,   -88,   -88,   -88,
      30,   -88,   -88,   368,   368,   -88,   191,   317,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,    21,   -88,   379,   -88,
     -49,    24,    43,   -17,    60,    90,    96,    97,   134,   135,
     -88,    20,   -88,   113,   -88,   -88,   -88,   -88,    14,   -88,
     -88,   -88,   -88,   -88,   412,   412,   274,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   412,   -88,   -88,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   412,   412,   -48,
     112,   -88,   -88,   -88,   379,   379,   379,   379,   379,   379,
     379,   379,   379,   379,   379,   379,   379,   379,   379,   379,
     379,   379,   412,   -88,   -88,    22,   -88,    10,   -88,   -88,
     -31,   -25,   274,   -88,   -88,   -88,   379,   -88,   -88,   -88,
     -49,   -49,    24,    24,    43,    43,    43,    43,   -17,   -17,
      60,    90,    96,    97,   134,   -88,   113,   -88,   412,   232,
     138,   192,   328,   -88,   -88,   -88,   -88,    99,   158,   192,
     -88,   192,   -14,   -88,   192,   -88,   -88,   192,   -88,   -88
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,   105,     0,     1,   106,     0,     0,     0,
       0,     0,     0,   107,     0,    89,   108,    79,     0,     0,
       0,     0,     0,     0,     0,     0,    75,    74,    73,     6,
       0,     4,     5,     0,     0,     3,     2,     0,    15,    16,
      17,    18,    19,    20,    95,     8,    11,    21,     0,    23,
      27,    30,    33,    38,    41,    43,    45,    47,    49,    51,
      64,     0,    93,     0,    68,    94,    85,    80,     0,    91,
      81,    82,    83,    84,     0,     0,     0,   103,   104,    87,
      86,    88,    67,     2,     0,    12,    13,    59,    60,    57,
      58,    55,    56,    54,    61,    63,    62,     0,     0,     0,
       0,     9,    10,    14,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,    76,     0,    69,    71,    90,    92,
       0,     0,     0,    52,    53,     7,     0,    24,    25,    26,
      28,    29,    31,    32,    37,    36,    34,    35,    39,    40,
      42,    44,    46,    48,    50,    65,     0,    66,     0,     0,
      97,    79,     0,    22,    70,    72,    78,     0,     0,    79,
     100,    79,     0,    77,    79,    98,   101,    79,    99,   102
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -88,   -88,   -88,    72,   -88,   -47,     0,     6,   -60,     7,
      50,    51,    52,    54,    47,   -88,   -87,   -88,   -37,   -88,
     -88,   -88,    19,   -23,   -88,   -57,   -88,   156,   -88,   -88,
     108,   -72,   -88,   -88,   -88,   -88,   -88,   175,   -88
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    98,    61,    62,
      63,   125,   126,    64,   127,    65,    66,    67,    17,    68,
      69,    70,    71,   169,    72,    73,     2,     3,    14
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      99,   103,   135,   104,   132,   111,   112,    82,   105,   106,
     133,   134,     5,     4,   100,     1,   122,     7,    18,   160,
      19,    20,    21,    22,    23,   161,    24,    25,    26,    27,
      28,    29,    30,   122,     1,   155,   177,   130,   131,   122,
      31,    32,   113,   114,    26,    27,    28,    99,    33,    34,
     122,   144,   145,   146,   147,   101,   102,   137,   138,   139,
     162,    35,    36,    37,     8,    38,    39,    40,    41,    42,
      43,   165,   167,   158,   109,   110,   159,   107,   108,    44,
     115,   116,    15,   128,   122,   123,   156,   157,    18,   163,
      19,    20,    21,    22,    23,    10,    24,    25,    26,    27,
      28,    29,    30,   168,   170,    85,    86,   140,   141,     9,
      31,    32,   175,    11,   176,   142,   143,   178,    33,    34,
     179,    12,   148,   149,    15,   172,    13,    74,    75,    76,
      77,    35,    36,    37,    78,    38,    39,    40,    41,    42,
      43,   117,    18,   -79,    19,    20,    21,    22,    23,    44,
      24,    25,    15,    79,    80,    29,    81,   118,   120,   119,
     121,   124,   136,   174,    31,    32,   173,   150,   154,   151,
      16,   152,    33,    34,   153,   164,   129,     6,     0,     0,
       0,     0,     0,     0,     0,    35,    36,    37,     0,    38,
      39,    40,    41,    42,    43,     0,    18,     0,    19,    20,
      21,    22,    23,    44,    24,    25,    15,     0,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,    33,    34,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,     0,    35,
      36,    37,     0,    38,    39,    40,    41,    42,    43,    29,
       0,     0,     0,     0,    97,     0,     0,    44,    31,    32,
      15,     0,     0,     0,     0,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,     0,    38,    39,    40,    41,    42,    43,     0,
       0,    29,     0,     0,     0,     0,     0,     0,     0,   166,
      31,    32,     0,     0,     0,     0,     0,     0,    33,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    36,    37,     0,    38,    39,    40,    41,    42,
      43,    26,    27,    28,    29,     0,     0,     0,     0,    44,
       0,     0,     0,    31,    32,    29,     0,     0,     0,     0,
       0,    33,    34,     0,    31,    32,     0,     0,     0,     0,
       0,     0,    33,    34,    35,    36,    37,     0,    38,    39,
      40,    41,    42,    43,     0,    35,    36,    37,   171,    38,
      39,    40,    41,    42,    43,    29,     0,     0,     0,     0,
       0,     0,     0,     0,    31,    32,    29,     0,     0,     0,
       0,     0,    33,    34,     0,    31,    32,     0,     0,     0,
       0,     0,     0,    33,    34,    35,    83,    84,     0,    38,
      39,    40,    41,    42,    43,     0,    35,    83,    37,    29,
      38,    39,    40,    41,    42,    43,     0,     0,    31,    32,
       0,     0,     0,     0,     0,     0,    33,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,     0,    38,    39,    40,    41,    42,    43
};

static const yytype_int16 yycheck[] =
{
      37,    48,    50,    52,    76,    22,    23,    30,    57,    58,
      97,    98,     0,    48,    37,     3,    64,    49,     4,    50,
       6,     7,     8,     9,    10,    50,    12,    13,    14,    15,
      16,    17,    18,    64,     3,   122,    50,    74,    75,    64,
      26,    27,    59,    60,    14,    15,    16,    84,    34,    35,
      64,   111,   112,   113,   114,    34,    35,   104,   105,   106,
     132,    47,    48,    49,    47,    51,    52,    53,    54,    55,
      56,   158,   159,    63,    31,    32,    66,    53,    54,    65,
      20,    21,    68,    69,    64,    65,    64,    65,     4,   136,
       6,     7,     8,     9,    10,    47,    12,    13,    14,    15,
      16,    17,    18,   160,   161,    33,    34,   107,   108,    64,
      26,    27,   169,    64,   171,   109,   110,   174,    34,    35,
     177,    47,   115,   116,    68,   162,    50,    49,    49,    49,
      65,    47,    48,    49,    65,    51,    52,    53,    54,    55,
      56,    51,     4,     5,     6,     7,     8,     9,    10,    65,
      12,    13,    68,    65,    65,    17,    65,    61,    24,    62,
      25,    48,    50,     5,    26,    27,    67,   117,   121,   118,
      14,   119,    34,    35,   120,   156,    68,     2,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    -1,    51,
      52,    53,    54,    55,    56,    -1,     4,    -1,     6,     7,
       8,     9,    10,    65,    12,    13,    68,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    -1,    47,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    17,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    65,    26,    27,
      68,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    -1,    51,    52,    53,    54,    55,    56,    -1,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      26,    27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    -1,    51,    52,    53,    54,    55,
      56,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    -1,    26,    27,    17,    -1,    -1,    -1,    -1,
      -1,    34,    35,    -1,    26,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    47,    48,    49,    -1,    51,    52,
      53,    54,    55,    56,    -1,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    26,    27,    17,    -1,    -1,    -1,
      -1,    -1,    34,    35,    -1,    26,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    47,    48,    49,    -1,    51,
      52,    53,    54,    55,    56,    -1,    47,    48,    49,    17,
      51,    52,    53,    54,    55,    56,    -1,    -1,    26,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    -1,    51,    52,    53,    54,    55,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,   106,   107,    48,     0,   107,    49,    47,    64,
      47,    64,    47,    50,   108,    68,    97,    98,     4,     6,
       7,     8,     9,    10,    12,    13,    14,    15,    16,    17,
      18,    26,    27,    34,    35,    47,    48,    49,    51,    52,
      53,    54,    55,    56,    65,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    88,    89,    90,    93,    95,    96,    97,    99,   100,
     101,   102,   104,   105,    49,    49,    49,    65,    65,    65,
      65,    65,    93,    48,    49,    73,    73,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    63,    87,    88,
      93,    34,    35,    75,    52,    57,    58,    53,    54,    31,
      32,    22,    23,    59,    60,    20,    21,    51,    61,    62,
      24,    25,    64,    65,    48,    91,    92,    94,    69,   100,
      88,    88,   101,    86,    86,    50,    50,    75,    75,    75,
      76,    76,    77,    77,    78,    78,    78,    78,    79,    79,
      80,    81,    82,    83,    84,    86,    64,    65,    63,    66,
      50,    50,   101,    75,    92,    86,    67,    86,    95,   103,
      95,    50,    88,    67,     5,    95,    95,    50,    95,    95
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    71,    71,    71,    71,    71,    72,    72,
      72,    73,    73,    73,    73,    74,    74,    74,    74,    74,
      74,    75,    75,    76,    76,    76,    76,    77,    77,    77,
      78,    78,    78,    79,    79,    79,    79,    79,    80,    80,
      80,    81,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    88,    88,    89,    90,    90,    91,
      91,    92,    92,    93,    93,    93,    94,    94,    94,    95,
      95,    95,    95,    95,    95,    95,    96,    96,    96,    98,
      97,    99,    99,   100,   100,   101,   101,   103,   102,   102,
     104,   104,   104,   105,   105,   106,   106,   108,   107
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     1,     2,
       2,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     4,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     2,     1,     1,
       3,     1,     3,     1,     1,     1,     1,     4,     3,     0,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     0,
       4,     1,     2,     1,     1,     1,     2,     0,     6,     7,
       5,     6,     7,     2,     2,     1,     2,     0,    11
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
#line 64 "proc.y" /* yacc.c:1646  */
    {
			temp=findID((yyvsp[0].name));
			if(temp)
			{
			(yyval.vt).type=temp->type;
			(yyval.vt).isID=1;
			gen7(temp->type,"PUSH0",temp->seg,temp->ofst);
			}
			else
			{
			typeErrNotFound();
			}
		}
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 78 "proc.y" /* yacc.c:1646  */
    {
	(yyval.vt).type=TYP_INT;
	(yyval.vt).isID=0;
	genImmI("PUSH0I8 I ",(yyvsp[0].vt).vali);
	}
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 84 "proc.y" /* yacc.c:1646  */
    {
	(yyval.vt).type=TYP_REAL;
	(yyval.vt).isID=0;
	genImmR("PUSH0I8 R ",(yyvsp[0].vt).valr);
	}
#line 1557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 90 "proc.y" /* yacc.c:1646  */
    {
	(yyval.vt).type=TYP_CHAR;
	(yyval.vt).isID=0;
	genImmC("PUSH0I1 ",(yyvsp[0].vt).valc);
	}
#line 1567 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 97 "proc.y" /* yacc.c:1646  */
    {
	(yyval.vt)=(yyvsp[-1].vt);
	}
#line 1575 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 104 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1581 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 106 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[-1].vt);gen2OP("INC",(yyvsp[-1].vt).type);}
#line 1587 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 108 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[-1].vt);gen2OP("DEC",(yyvsp[-1].vt).type);}
#line 1593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 114 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 116 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 118 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 120 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);gen2OP_1((yyvsp[0].vt).type);}
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 124 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("AND");}
#line 1623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 125 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("MUL");}
#line 1629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 126 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("ADD");}
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 127 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("SUB");}
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 128 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("NOT");}
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 129 "proc.y" /* yacc.c:1646  */
    {gen2OP_0("?");}
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 134 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 136 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[-2].vt);}
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 141 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 143 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("MUL",(yyvsp[-2].vt).type);}
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 145 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("DIV",(yyvsp[-2].vt).type);}
#line 1683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 147 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("DIV",(yyvsp[-2].vt).type);}
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 152 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 154 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("ADD",(yyvsp[-2].vt).type);}
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 156 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("SUB",(yyvsp[-2].vt).type);}
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 161 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 163 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("SHL",(yyvsp[-2].vt).type);}
#line 1719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 165 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("SHR",(yyvsp[-2].vt).type);}
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 170 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 172 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);}
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 174 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);}
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 176 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);}
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 178 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);}
#line 1755 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 183 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 185 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);}
#line 1767 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 187 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);}
#line 1773 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 192 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 194 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("AND",(yyvsp[-2].vt).type);}
#line 1785 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 199 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 201 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("XOR",(yyvsp[-2].vt).type);}
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 208 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);gen2OP("OR",(yyvsp[-2].vt).type);}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 213 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1815 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 215 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);}
#line 1821 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 220 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 222 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt);}
#line 1833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 227 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1839 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 229 "proc.y" /* yacc.c:1646  */
    {
		//check id
		temp=findID((yyvsp[-2].name));
		if(temp)
			{
			//check type
			if(temp->type==(yyvsp[0].vt).type)
				{
				//assign value
				//copy the top stack to the target
				gen12((yyvsp[0].vt).type,"MOV",POINTER_STACK0,(yyvsp[0].vt).type==TYP_CHAR?-1:-8,temp->seg,temp->ofst);
				}
			else
				{
				//typeErrMismatch
				typeErrMismatch();
				}
			}
		else
			{
			typeErrNotFound();
			}
		}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 270 "proc.y" /* yacc.c:1646  */
    {
	//reset fast stack
	(yyval.vt)=(yyvsp[0].vt);
	//gen12(TYP_INT,"MOV",BASE_DATA,BASE_STACK0,BASE_DATA,POINTER_STACK0);
	}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 280 "proc.y" /* yacc.c:1646  */
    {
		typeCheck((yyvsp[-2].vt),(yyvsp[-1].vt));
		setMetaType((yyvsp[-2].vt).type);
		}
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 286 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 287 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 291 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 293 "proc.y" /* yacc.c:1646  */
    {typeCheck((yyvsp[-2].vt),(yyvsp[0].vt));(yyval.vt)=(yyvsp[-2].vt).type>(yyvsp[0].vt).type?(yyvsp[-2].vt):(yyvsp[0].vt);}
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 297 "proc.y" /* yacc.c:1646  */
    {(yyval.vt).type=TYP_META;}
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 298 "proc.y" /* yacc.c:1646  */
    {(yyval.vt)=(yyvsp[0].vt);}
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 303 "proc.y" /* yacc.c:1646  */
    {(yyval.vt).type=TYP_CHAR;}
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 304 "proc.y" /* yacc.c:1646  */
    {(yyval.vt).type=TYP_REAL;}
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 305 "proc.y" /* yacc.c:1646  */
    {(yyval.vt).type=TYP_INT;}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 311 "proc.y" /* yacc.c:1646  */
    {
		temp=addID(TYP_META,(yyvsp[0].name));
		if(!temp)
			typeErrRedeclared();
		}
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 316 "proc.y" /* yacc.c:1646  */
    {if((yyvsp[-1].vt).type!=TYP_INT) typeErrMismatch();}
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 330 "proc.y" /* yacc.c:1646  */
    {gen2(_HALT);}
#line 1962 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 331 "proc.y" /* yacc.c:1646  */
    {gen2(_REBOOT);}
#line 1968 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 332 "proc.y" /* yacc.c:1646  */
    {gen2(_SUSPEND);}
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 336 "proc.y" /* yacc.c:1646  */
    {currentScope++;}
#line 1980 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 336 "proc.y" /* yacc.c:1646  */
    {leaveScope();}
#line 1986 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 352 "proc.y" /* yacc.c:1646  */
    {
	{
	//reset fast stack
	gen12(TYP_INT,"MOV",BASE_DATA,BASE_STACK0,BASE_DATA,POINTER_STACK0);
	}
	}
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 362 "proc.y" /* yacc.c:1646  */
    {
	//here is the branch operation section
	genFlagRelated("JMPC <flag> ",flagMarker);
	fStackPush(flagMarker,TYP_BRANCH_FALSE);
	flagMarker++;
	}
#line 2008 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 369 "proc.y" /* yacc.c:1646  */
    {
	//recover the flag
	genFlagRelated("#",fStackPop());
	}
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 396 "proc.y" /* yacc.c:1646  */
    {
		//check first
		temp = addID(TYP_PROC,(yyvsp[-7].name));
		if(!temp)
			typeErrRedeclared();
		genPHeader((yyvsp[-7].name),(yyvsp[-5].vt).vali,(yyvsp[-3].vt).vali,(yyvsp[-1].vt).vali);
		gen(".code;start\n");
		}
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 405 "proc.y" /* yacc.c:1646  */
    {
		gen(";ended");
		}
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2042 "y.tab.c" /* yacc.c:1646  */
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
#line 410 "proc.y" /* yacc.c:1906  */

#include <stdio.h>
//#include "symbol.h"
//extern char yytext[];
extern int column;

void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
void typeCheck(struct value_and_type l,struct value_and_type r)
{
printf("$%d#%d$",l.type,r.type);
if(l.type==TYP_META || r.type==TYP_META || l.type==r.type) return;
	printf("type checking failure:%d/%d/",l.type,r.type);
	yyerror(yytext);
	exit(-1);
}

void typeErrNotFound()
{
	printf("type error : cannot find declaration.");
	yyerror(yytext);
	exit(-1);
}
void typeErrRedeclared()
{
	printf("type error : identifier name override.");
	yyerror(yytext);
	exit(-1);
}
void typeErrMismatch()
{
	printf("type error : type mismatch.");
	yyerror(yytext);
	exit(-1);
}
