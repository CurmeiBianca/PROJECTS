/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "expr.y"

/* ==============================
    INCLUDERI STANDARD C/C++
    ============================== */

#include <iostream> // pentru cout, cerr
#include <fstream> // pentru lucrul cu fisiere
#include <string> // pentru std::string
#include <vector> // pentru std::vector
#include <cstdlib> // pentru exit()
#include <cstring> // pentru stddup()
#include "globals.h" // definitii: SymbolTable, ASTNode, DataType etc.

/* Permite folosirea directa a std::string, std::vector etc. */
using namespace std;

void yyerror(const char* s);
extern int yylex();
extern int yylineno;

/* Tabele de simboluri */
extern SymbolTable* globalTable; // tabela globala
extern SymbolTable* currentTable; // tabela scope-ului curent
extern std::vector<SymbolTable*> allTables; // lista tuturor tabelelor

/* ==============================
    Conversie string -> tip intern
    ============================== */
DataType getTypeFromStr(const string& s) 
{
    if (s == "piatra_filosofala") return T_INT; // int
    if (s == "aur_topit") return T_FLOAT; // float
    if (s == "clarviziune") return T_BOOL; // bool
    if (s == "pergament") return T_STRING; // string
    return T_UNKNOWN; // tip necunoscut
}

/* ==============================
    Verificare compatibilitate tipuri
    ============================== */
void checkType(DataType lhs, DataType rhs, const string& msg) 
{
    if(lhs != rhs) 
    { // daca tipurile nu coincid
        cerr << "Eroare semantica la linia " << yylineno << ": " << msg << endl;
        exit(1); // opreste compilarea
    }
}

#line 121 "expr.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "expr.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT_LITERAL = 3,                /* INT_LITERAL  */
  YYSYMBOL_BOOL_LITERAL = 4,               /* BOOL_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 5,              /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_ID = 7,                         /* ID  */
  YYSYMBOL_INT_TYPE = 8,                   /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 9,                 /* FLOAT_TYPE  */
  YYSYMBOL_STRING_TYPE = 10,               /* STRING_TYPE  */
  YYSYMBOL_BOOL_TYPE = 11,                 /* BOOL_TYPE  */
  YYSYMBOL_CLASS = 12,                     /* CLASS  */
  YYSYMBOL_NEW = 13,                       /* NEW  */
  YYSYMBOL_DOT = 14,                       /* DOT  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_ELSE = 16,                      /* ELSE  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_RETURN = 18,                    /* RETURN  */
  YYSYMBOL_MAIN_BLOCK = 19,                /* MAIN_BLOCK  */
  YYSYMBOL_PRINT = 20,                     /* PRINT  */
  YYSYMBOL_LBRACE = 21,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 22,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 23,                 /* SEMICOLON  */
  YYSYMBOL_ASSIGN = 24,                    /* ASSIGN  */
  YYSYMBOL_LPAREN = 25,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 26,                    /* RPAREN  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_EQ = 31,                        /* EQ  */
  YYSYMBOL_NEQ = 32,                       /* NEQ  */
  YYSYMBOL_LT = 33,                        /* LT  */
  YYSYMBOL_GT = 34,                        /* GT  */
  YYSYMBOL_LEQ = 35,                       /* LEQ  */
  YYSYMBOL_GEQ = 36,                       /* GEQ  */
  YYSYMBOL_PLUS = 37,                      /* PLUS  */
  YYSYMBOL_MINUS = 38,                     /* MINUS  */
  YYSYMBOL_MUL = 39,                       /* MUL  */
  YYSYMBOL_DIV = 40,                       /* DIV  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_program = 42,                   /* program  */
  YYSYMBOL_43_1 = 43,                      /* $@1  */
  YYSYMBOL_global_declarations = 44,       /* global_declarations  */
  YYSYMBOL_class_definition = 45,          /* class_definition  */
  YYSYMBOL_46_2 = 46,                      /* $@2  */
  YYSYMBOL_optional_semicolon = 47,        /* optional_semicolon  */
  YYSYMBOL_class_body = 48,                /* class_body  */
  YYSYMBOL_function_definition = 49,       /* function_definition  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_parameters = 51,                /* parameters  */
  YYSYMBOL_param_list = 52,                /* param_list  */
  YYSYMBOL_local_vars = 53,                /* local_vars  */
  YYSYMBOL_global_variable_decl = 54,      /* global_variable_decl  */
  YYSYMBOL_variable_definition = 55,       /* variable_definition  */
  YYSYMBOL_type = 56,                      /* type  */
  YYSYMBOL_main_block = 57,                /* main_block  */
  YYSYMBOL_statements = 58,                /* statements  */
  YYSYMBOL_statement = 59,                 /* statement  */
  YYSYMBOL_assignment = 60,                /* assignment  */
  YYSYMBOL_function_call = 61,             /* function_call  */
  YYSYMBOL_call_arguments = 62,            /* call_arguments  */
  YYSYMBOL_arg_list = 63,                  /* arg_list  */
  YYSYMBOL_expression = 64                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   120,   120,   120,   131,   133,   134,   135,   143,   142,
     160,   160,   163,   165,   166,   174,   173,   216,   217,   221,
     226,   236,   238,   243,   250,   259,   275,   289,   290,   291,
     292,   293,   300,   320,   321,   328,   329,   330,   331,   332,
     333,   334,   341,   348,   358,   370,   371,   375,   376,   383,
     384,   385,   386,   387,   391,   397,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT_LITERAL",
  "BOOL_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL", "ID", "INT_TYPE",
  "FLOAT_TYPE", "STRING_TYPE", "BOOL_TYPE", "CLASS", "NEW", "DOT", "IF",
  "ELSE", "WHILE", "RETURN", "MAIN_BLOCK", "PRINT", "LBRACE", "RBRACE",
  "SEMICOLON", "ASSIGN", "LPAREN", "RPAREN", "COMMA", "AND", "OR", "NOT",
  "EQ", "NEQ", "LT", "GT", "LEQ", "GEQ", "PLUS", "MINUS", "MUL", "DIV",
  "$accept", "program", "$@1", "global_declarations", "class_definition",
  "$@2", "optional_semicolon", "class_body", "function_definition", "$@3",
  "parameters", "param_list", "local_vars", "global_variable_decl",
  "variable_definition", "type", "main_block", "statements", "statement",
  "assignment", "function_call", "call_arguments", "arg_list",
  "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-47)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -47,    13,   -47,   -47,   210,   -47,   -47,   -47,   -47,   -47,
       8,    -4,   -47,   -47,   -47,    -5,    14,   -47,    19,   -47,
     -47,   -20,   -47,    -1,    64,     3,   216,   -47,     5,     6,
      18,     3,    20,   -47,   -47,    23,    24,   -47,   -47,   -47,
     -47,    26,    46,     3,   -47,   163,    42,    43,    62,    55,
      65,     3,     3,     3,     3,    21,     3,   -47,   -47,    58,
     105,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,   -47,   216,   -47,    78,    71,   -47,    72,    63,
     163,    74,    70,   163,   120,   135,   -47,   150,    81,   -47,
     197,   176,   205,    52,    52,    52,    52,   -28,   -28,   -47,
     -47,    88,   107,    19,   -47,   -47,   -47,     3,   -47,     3,
      91,   102,   106,   -47,   -47,   -47,   163,   163,   -47,   -47,
     -47,   239,    86,    98,   112,   130,   104,   131,   -47,   -47,
     126,   -47,   141,   -47,   110,   -47
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     1,     0,    31,    27,    28,    29,    30,
       0,     0,     5,     6,     7,     0,     0,     3,     8,    33,
      23,    24,    26,     0,     0,     0,    17,    12,     0,     0,
       0,     0,     0,    32,    34,     0,     0,    49,    52,    50,
      51,    54,     0,     0,    53,    25,     0,    18,     0,     0,
       0,     0,    45,     0,     0,     0,     0,    35,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    15,     0,    19,     0,    10,    14,     0,     0,
      42,     0,    46,    47,     0,     0,    41,     0,     0,    56,
      66,    67,    65,    62,    61,    64,    63,    57,    58,    59,
      60,     0,     0,     0,    11,     9,    13,     0,    44,     0,
       0,     0,     0,    55,    21,    20,    43,    48,    33,    33,
      40,    33,     0,     0,     0,     0,     0,    37,    39,    22,
      24,    16,     0,    33,     0,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -47,   -47,   -47,   -47,   -47,   -47,   -47,   -47,   103,   -47,
     -47,   -47,   -47,   -47,   -46,   -25,   -47,   -45,   -47,   -47,
     -24,   -47,   -47,   -29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     4,    12,    23,   105,    49,    13,   101,
      46,    47,   121,    14,    15,    16,    17,    24,    34,    35,
      44,    81,    82,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      36,    48,    55,    78,    25,    26,    37,    38,    39,    40,
      41,    70,    71,     3,    60,    18,    42,    19,    20,    50,
      27,    21,    80,    83,    84,    85,    22,    87,    43,    51,
      52,    53,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    54,    86,    56,    57,    58,   102,    61,
      62,    52,    63,    59,    64,    65,    66,    67,    68,    69,
      70,    71,     5,     6,     7,     8,     9,    75,    72,    74,
      73,    28,    79,   122,   123,   124,   126,    76,   116,    29,
     117,    30,    31,    88,    32,   103,    33,   107,   134,    68,
      69,    70,    71,    28,   104,   106,   125,   109,    36,    36,
     108,    29,    36,    30,    31,    28,    32,   113,   127,   114,
      36,    28,   118,    29,   115,    30,    31,    28,    32,    29,
     128,    30,    31,   119,    32,    29,   131,    30,    31,   120,
      32,    89,   135,    61,    62,   129,    63,   130,    64,    65,
      66,    67,    68,    69,    70,    71,   110,   132,    61,    62,
      25,    63,    77,    64,    65,    66,    67,    68,    69,    70,
      71,   111,   133,    61,    62,     0,    63,     0,    64,    65,
      66,    67,    68,    69,    70,    71,   112,     0,    61,    62,
       0,    63,     0,    64,    65,    66,    67,    68,    69,    70,
      71,    61,    62,     0,    63,     0,    64,    65,    66,    67,
      68,    69,    70,    71,    61,     0,     0,    63,     0,    64,
      65,    66,    67,    68,    69,    70,    71,     5,     6,     7,
       8,     9,    10,     5,     6,     7,     8,     9,    63,    11,
      64,    65,    66,    67,    68,    69,    70,    71,    64,    65,
      66,    67,    68,    69,    70,    71,     5,     6,     7,     8,
       9,    75
};

static const yytype_int16 yycheck[] =
{
      24,    26,    31,    49,    24,    25,     3,     4,     5,     6,
       7,    39,    40,     0,    43,     7,    13,    21,    23,    14,
      21,     7,    51,    52,    53,    54,     7,    56,    25,    24,
      25,    25,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    25,    23,    25,    23,    23,    73,    28,
      29,    25,    31,     7,    33,    34,    35,    36,    37,    38,
      39,    40,     7,     8,     9,    10,    11,    12,    26,     7,
      27,     7,     7,   118,   119,   121,   121,    22,   107,    15,
     109,    17,    18,    25,    20,     7,    22,    24,   133,    37,
      38,    39,    40,     7,    23,    23,   121,    27,   122,   123,
      26,    15,   126,    17,    18,     7,    20,    26,    22,    21,
     134,     7,    21,    15,     7,    17,    18,     7,    20,    15,
      22,    17,    18,    21,    20,    15,    22,    17,    18,    23,
      20,    26,    22,    28,    29,    23,    31,     7,    33,    34,
      35,    36,    37,    38,    39,    40,    26,    16,    28,    29,
      24,    31,    49,    33,    34,    35,    36,    37,    38,    39,
      40,    26,    21,    28,    29,    -1,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    26,    -1,    28,    29,
      -1,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    28,    29,    -1,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    28,    -1,    -1,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,     7,     8,     9,
      10,    11,    12,     7,     8,     9,    10,    11,    31,    19,
      33,    34,    35,    36,    37,    38,    39,    40,    33,    34,
      35,    36,    37,    38,    39,    40,     7,     8,     9,    10,
      11,    12
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    42,    43,     0,    44,     7,     8,     9,    10,    11,
      12,    19,    45,    49,    54,    55,    56,    57,     7,    21,
      23,     7,     7,    46,    58,    24,    25,    21,     7,    15,
      17,    18,    20,    22,    59,    60,    61,     3,     4,     5,
       6,     7,    13,    25,    61,    64,    51,    52,    56,    48,
      14,    24,    25,    25,    25,    64,    25,    23,    23,     7,
      64,    28,    29,    31,    33,    34,    35,    36,    37,    38,
      39,    40,    26,    27,     7,    12,    22,    49,    55,     7,
      64,    62,    63,    64,    64,    64,    23,    64,    25,    26,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    50,    56,     7,    23,    47,    23,    24,    26,    27,
      26,    26,    26,    26,    21,     7,    64,    64,    21,    21,
      23,    53,    58,    58,    55,    56,    58,    22,    22,    23,
       7,    22,    16,    21,    58,    22
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    43,    42,    44,    44,    44,    44,    46,    45,
      47,    47,    48,    48,    48,    50,    49,    51,    51,    52,
      52,    53,    53,    54,    55,    55,    55,    56,    56,    56,
      56,    56,    57,    58,    58,    59,    59,    59,    59,    59,
      59,    59,    60,    60,    61,    62,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     0,     2,     2,     2,     0,     7,
       0,     1,     0,     3,     2,     0,    10,     0,     1,     2,
       4,     0,     3,     2,     2,     4,     3,     1,     1,     1,
       1,     1,     4,     0,     2,     2,     2,     7,    11,     7,
       5,     3,     3,     5,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* $@1: %empty  */
#line 120 "expr.y"
    { 
        printf("=== Pornire analiza sintactica ===\n");
        if (globalTable) 
            allTables.push_back(globalTable); // salveaza tabela gloabal
    }
#line 1287 "expr.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 143 "expr.y"
    {
        SymbolInfo info; // info despre clasa
        info.name = (yyvsp[0].str); // numele clase
        info.type = T_CLASS; // tip clasa
        info.classScope = new SymbolTable((yyvsp[0].str), currentTable); // scope nou
        allTables.push_back(info.classScope); // salveaza scope-ul
        currentTable->add((yyvsp[0].str), info); // adauga clasa in tabela curenta
        currentTable = info.classScope; // intra in scope-ul clasei
    }
#line 1301 "expr.tab.c"
    break;

  case 9: /* class_definition: CLASS ID $@2 LBRACE class_body RBRACE optional_semicolon  */
#line 153 "expr.y"
    {
        printf("Class defined: %s\n", (yyvsp[-5].str));
        currentTable = currentTable->parent; // iesire din clasa
    }
#line 1310 "expr.tab.c"
    break;

  case 15: /* $@3: %empty  */
#line 174 "expr.y"
    {
        SymbolInfo info; // info functie
        info.name = (yyvsp[-3].str); // nume functie
        info.type = getTypeFromStr((yyvsp[-4].str)); // tip return
        info.isFunction = true; // marcheaza functie
        info.returnType = info.type;
        
        SymbolTable* funcTable = new SymbolTable((yyvsp[-3].str), currentTable); // scope functie
        allTables.push_back(funcTable);
        
        if((yyvsp[-1].paramvec)) 
        { // daca exista parametri
            for(auto &p : *(yyvsp[-1].paramvec)) 
            {
                ParamInfo pi;
                pi.name = p.name;
                pi.type = getTypeFromStr(p.type);
                info.params.push_back(pi);
                
                SymbolInfo pInfo;
                pInfo.name = p.name;
                pInfo.type = pi.type;
                pInfo.value = Value::defaultValue(pi.type);
                funcTable->add(p.name, pInfo); // parametru = variabila globala
            }
        }
        currentTable->add((yyvsp[-3].str), info); // adauga functia
        currentTable = funcTable; // intra in functie
    }
#line 1344 "expr.tab.c"
    break;

  case 16: /* function_definition: type ID LPAREN parameters RPAREN $@3 LBRACE local_vars statements RBRACE  */
#line 204 "expr.y"
    {
        printf("Function defined: %s\n", (yyvsp[-8].str));
        currentTable = currentTable->parent; // iesire din functie
        if((yyvsp[-6].paramvec)) 
            delete (yyvsp[-6].paramvec); // elibereaza parametrii
    }
#line 1355 "expr.tab.c"
    break;

  case 17: /* parameters: %empty  */
#line 216 "expr.y"
                  { (yyval.paramvec) = new std::vector<Param>(); }
#line 1361 "expr.tab.c"
    break;

  case 18: /* parameters: param_list  */
#line 217 "expr.y"
                 { (yyval.paramvec) = (yyvsp[0].paramvec); }
#line 1367 "expr.tab.c"
    break;

  case 19: /* param_list: type ID  */
#line 222 "expr.y"
      { 
          (yyval.paramvec) = new std::vector<Param>(); 
          (yyval.paramvec)->push_back({string((yyvsp[-1].str)), string((yyvsp[0].str))}); 
      }
#line 1376 "expr.tab.c"
    break;

  case 20: /* param_list: param_list COMMA type ID  */
#line 227 "expr.y"
      { 
          (yyvsp[-3].paramvec)->push_back({string((yyvsp[-1].str)), string((yyvsp[0].str))}); 
          (yyval.paramvec) = (yyvsp[-3].paramvec); 
      }
#line 1385 "expr.tab.c"
    break;

  case 24: /* variable_definition: type ID  */
#line 251 "expr.y"
    {
        SymbolInfo info;
        info.name = (yyvsp[0].str); info.type = getTypeFromStr((yyvsp[-1].str));
        info.value = Value::defaultValue(info.type);
        currentTable->add((yyvsp[0].str), info);
        printf("Variable declared: %s\n", (yyvsp[0].str));
        (yyval.ast) = nullptr;
    }
#line 1398 "expr.tab.c"
    break;

  case 25: /* variable_definition: type ID ASSIGN expression  */
#line 260 "expr.y"
    {
        SymbolInfo info;
        info.name = (yyvsp[-2].str); info.type = getTypeFromStr((yyvsp[-3].str));
        checkType(info.type, (yyvsp[0].ast)->exprType, "Initializare invalida");
        info.value = Value::defaultValue(info.type);
        currentTable->add((yyvsp[-2].str), info);

        ASTNode* assignNode = new ASTNode("leaga_de", new ASTNode((yyvsp[-2].str)), (yyvsp[0].ast));

        if (currentTable == globalTable) 
            assignNode->evaluate(); // executa imediat global

        printf("Variable init: %s\n", (yyvsp[-2].str));
        (yyval.ast) = assignNode;
    }
#line 1418 "expr.tab.c"
    break;

  case 26: /* variable_definition: CLASS ID ID  */
#line 276 "expr.y"
    {
        SymbolInfo info;
        info.name = (yyvsp[0].str); info.type = T_CLASS; info.className = (yyvsp[-1].str);
        currentTable->add((yyvsp[0].str), info);
        printf("Variable declared: %s (object of %s)\n", (yyvsp[0].str), (yyvsp[-1].str));
        (yyval.ast) = nullptr;
    }
#line 1430 "expr.tab.c"
    break;

  case 27: /* type: INT_TYPE  */
#line 289 "expr.y"
               { (yyval.str) = strdup("piatra_filosofala"); }
#line 1436 "expr.tab.c"
    break;

  case 28: /* type: FLOAT_TYPE  */
#line 290 "expr.y"
                 { (yyval.str) = strdup("aur_topit"); }
#line 1442 "expr.tab.c"
    break;

  case 29: /* type: STRING_TYPE  */
#line 291 "expr.y"
                  { (yyval.str) = strdup("pergament"); }
#line 1448 "expr.tab.c"
    break;

  case 30: /* type: BOOL_TYPE  */
#line 292 "expr.y"
                { (yyval.str) = strdup("clarviziune"); }
#line 1454 "expr.tab.c"
    break;

  case 31: /* type: ID  */
#line 293 "expr.y"
         { (yyval.str) = strdup((yyvsp[0].str)); }
#line 1460 "expr.tab.c"
    break;

  case 32: /* main_block: MAIN_BLOCK LBRACE statements RBRACE  */
#line 301 "expr.y"
    {
        printf("Main block executed.\n");
        if ((yyvsp[-1].astlist)) 
        {
            for (ASTNode* node : *(yyvsp[-1].astlist)) 
            {
                if (node) 
                    node->evaluate(); // executa fiecare instructiune
            }
        }
        printf("Program parsed successfully.\n");
        printf("=== Analiza sintactica finalizata ===\n");
    }
#line 1478 "expr.tab.c"
    break;

  case 33: /* statements: %empty  */
#line 320 "expr.y"
                  { (yyval.astlist) = new std::vector<ASTNode*>(); }
#line 1484 "expr.tab.c"
    break;

  case 34: /* statements: statements statement  */
#line 321 "expr.y"
                           { if((yyvsp[0].ast)) (yyvsp[-1].astlist)->push_back((yyvsp[0].ast)); (yyval.astlist) = (yyvsp[-1].astlist); }
#line 1490 "expr.tab.c"
    break;

  case 35: /* statement: assignment SEMICOLON  */
#line 328 "expr.y"
                           { (yyval.ast) = (yyvsp[-1].ast); }
#line 1496 "expr.tab.c"
    break;

  case 36: /* statement: function_call SEMICOLON  */
#line 329 "expr.y"
                              { (yyval.ast) = (yyvsp[-1].ast); }
#line 1502 "expr.tab.c"
    break;

  case 37: /* statement: IF LPAREN expression RPAREN LBRACE statements RBRACE  */
#line 330 "expr.y"
                                                           { (yyval.ast) = nullptr; }
#line 1508 "expr.tab.c"
    break;

  case 38: /* statement: IF LPAREN expression RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE  */
#line 331 "expr.y"
                                                                                         { (yyval.ast) = nullptr; }
#line 1514 "expr.tab.c"
    break;

  case 39: /* statement: WHILE LPAREN expression RPAREN LBRACE statements RBRACE  */
#line 332 "expr.y"
                                                              { (yyval.ast) = nullptr; }
#line 1520 "expr.tab.c"
    break;

  case 40: /* statement: PRINT LPAREN expression RPAREN SEMICOLON  */
#line 333 "expr.y"
                                               { (yyval.ast) = new ASTNode("PRINT", (yyvsp[-2].ast), nullptr); }
#line 1526 "expr.tab.c"
    break;

  case 41: /* statement: RETURN expression SEMICOLON  */
#line 334 "expr.y"
                                  { (yyval.ast) = nullptr; }
#line 1532 "expr.tab.c"
    break;

  case 42: /* assignment: ID ASSIGN expression  */
#line 342 "expr.y"
    {
        SymbolInfo* s = currentTable->lookup((yyvsp[-2].str));
        if(!s) { yyerror("Nedeclarat"); exit(1); }
        checkType(s->type, (yyvsp[0].ast)->exprType, "Incompatibil");
        (yyval.ast) = new ASTNode("leaga_de", new ASTNode((yyvsp[-2].str)), (yyvsp[0].ast));
    }
#line 1543 "expr.tab.c"
    break;

  case 43: /* assignment: ID DOT ID ASSIGN expression  */
#line 349 "expr.y"
    {
        (yyval.ast) = new ASTNode("leaga_de", new ASTNode((yyvsp[-2].str)), (yyvsp[0].ast));
    }
#line 1551 "expr.tab.c"
    break;

  case 44: /* function_call: ID LPAREN call_arguments RPAREN  */
#line 359 "expr.y"
      { 
          SymbolInfo* s = currentTable->lookup((yyvsp[-3].str));
          (yyval.ast) = new ASTNode("OTHER");
          (yyval.ast)->exprType = (s ? s->returnType : T_INT); 
      }
#line 1561 "expr.tab.c"
    break;

  case 45: /* call_arguments: %empty  */
#line 370 "expr.y"
                  { (yyval.ast) = nullptr; }
#line 1567 "expr.tab.c"
    break;

  case 46: /* call_arguments: arg_list  */
#line 371 "expr.y"
               { (yyval.ast) = (yyvsp[0].ast); }
#line 1573 "expr.tab.c"
    break;

  case 47: /* arg_list: expression  */
#line 375 "expr.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1579 "expr.tab.c"
    break;

  case 48: /* arg_list: arg_list COMMA expression  */
#line 376 "expr.y"
                                { (yyval.ast) = (yyvsp[0].ast); }
#line 1585 "expr.tab.c"
    break;

  case 49: /* expression: INT_LITERAL  */
#line 383 "expr.y"
                  { (yyval.ast) = new ASTNode(to_string((yyvsp[0].int_val))); (yyval.ast)->exprType = T_INT; }
#line 1591 "expr.tab.c"
    break;

  case 50: /* expression: FLOAT_LITERAL  */
#line 384 "expr.y"
                    { (yyval.ast) = new ASTNode(to_string((yyvsp[0].float_val))); (yyval.ast)->exprType = T_FLOAT; }
#line 1597 "expr.tab.c"
    break;

  case 51: /* expression: STRING_LITERAL  */
#line 385 "expr.y"
                     { (yyval.ast) = new ASTNode("\"" + string((yyvsp[0].str)) + "\""); (yyval.ast)->exprType = T_STRING; }
#line 1603 "expr.tab.c"
    break;

  case 52: /* expression: BOOL_LITERAL  */
#line 386 "expr.y"
                   { (yyval.ast) = new ASTNode((yyvsp[0].int_val) == 1 ? "true" : "false"); (yyval.ast)->exprType = T_BOOL; }
#line 1609 "expr.tab.c"
    break;

  case 53: /* expression: function_call  */
#line 388 "expr.y"
      { 
          (yyval.ast) = (yyvsp[0].ast); 
      }
#line 1617 "expr.tab.c"
    break;

  case 54: /* expression: ID  */
#line 392 "expr.y"
      {
        SymbolInfo* s = currentTable->lookup((yyvsp[0].str));
        if(!s) { yyerror("Nedeclarat"); exit(1); }
        (yyval.ast) = new ASTNode((yyvsp[0].str)); (yyval.ast)->exprType = s->type;
      }
#line 1627 "expr.tab.c"
    break;

  case 55: /* expression: NEW ID LPAREN RPAREN  */
#line 398 "expr.y"
      { 
        (yyval.ast) = new ASTNode("OTHER"); 
        (yyval.ast)->exprType = T_CLASS; 
      }
#line 1636 "expr.tab.c"
    break;

  case 56: /* expression: LPAREN expression RPAREN  */
#line 402 "expr.y"
                               { (yyval.ast) = (yyvsp[-1].ast); }
#line 1642 "expr.tab.c"
    break;

  case 57: /* expression: expression PLUS expression  */
#line 403 "expr.y"
                                  { (yyval.ast) = new ASTNode("+", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = (yyvsp[-2].ast)->exprType; }
#line 1648 "expr.tab.c"
    break;

  case 58: /* expression: expression MINUS expression  */
#line 404 "expr.y"
                                  { (yyval.ast) = new ASTNode("-", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = (yyvsp[-2].ast)->exprType; }
#line 1654 "expr.tab.c"
    break;

  case 59: /* expression: expression MUL expression  */
#line 405 "expr.y"
                                  { (yyval.ast) = new ASTNode("*", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = (yyvsp[-2].ast)->exprType; }
#line 1660 "expr.tab.c"
    break;

  case 60: /* expression: expression DIV expression  */
#line 406 "expr.y"
                                  { (yyval.ast) = new ASTNode("/", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = (yyvsp[-2].ast)->exprType; }
#line 1666 "expr.tab.c"
    break;

  case 61: /* expression: expression GT expression  */
#line 407 "expr.y"
                                  { (yyval.ast) = new ASTNode(">", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = T_BOOL; }
#line 1672 "expr.tab.c"
    break;

  case 62: /* expression: expression LT expression  */
#line 408 "expr.y"
                                  { (yyval.ast) = new ASTNode("<", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = T_BOOL; }
#line 1678 "expr.tab.c"
    break;

  case 63: /* expression: expression GEQ expression  */
#line 409 "expr.y"
                                  { (yyval.ast) = new ASTNode(">=", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = T_BOOL; }
#line 1684 "expr.tab.c"
    break;

  case 64: /* expression: expression LEQ expression  */
#line 410 "expr.y"
                                  { (yyval.ast) = new ASTNode("<=", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = T_BOOL; }
#line 1690 "expr.tab.c"
    break;

  case 65: /* expression: expression EQ expression  */
#line 411 "expr.y"
                                  { (yyval.ast) = new ASTNode("==", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = T_BOOL; }
#line 1696 "expr.tab.c"
    break;

  case 66: /* expression: expression AND expression  */
#line 412 "expr.y"
                                  { (yyval.ast) = new ASTNode("&&", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = T_BOOL; }
#line 1702 "expr.tab.c"
    break;

  case 67: /* expression: expression OR expression  */
#line 413 "expr.y"
                                  { (yyval.ast) = new ASTNode("||", (yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast)->exprType = T_BOOL; }
#line 1708 "expr.tab.c"
    break;


#line 1712 "expr.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 417 "expr.y"


/* ==============================
    TRATARE ERORI
    ============================== */
void yyerror(const char* s) 
{
    fprintf(stderr, "Eroare la linia %d: %s\n", yylineno, s);
}

