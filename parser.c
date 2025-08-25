/* A Bison parser, made by GNU Bison 3.7.5.  */

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
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include "syntax_header.h"
    #include "tcode.h"
    #include "avm.h"
    #define  YY_DECL int alpha_yylex (void* ylval)
    int yylex(void);
    int  curr_scope=0; // current scope variable.
    int function_nested=0;
    int buf_counter=0;
    int namespace_flag=0;
    int for_flag=0;	
    int while_flag=0;
    int flagSemicolon=0;
    int flagLogical=0;
    char buf[50];
    extern int yylineno;
    extern char* yytext;
    int yyerror (char* yaccProvidedMessage);
    extern FILE* yyin;


#line 95 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_WHILE = 5,                      /* WHILE  */
  YYSYMBOL_FOR = 6,                        /* FOR  */
  YYSYMBOL_FUNCTION = 7,                   /* FUNCTION  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_BREAK = 9,                      /* BREAK  */
  YYSYMBOL_CONTINUE = 10,                  /* CONTINUE  */
  YYSYMBOL_AND = 11,                       /* AND  */
  YYSYMBOL_NOT = 12,                       /* NOT  */
  YYSYMBOL_OR = 13,                        /* OR  */
  YYSYMBOL_LOCAL = 14,                     /* LOCAL  */
  YYSYMBOL_TRUE = 15,                      /* TRUE  */
  YYSYMBOL_FALSE = 16,                     /* FALSE  */
  YYSYMBOL_NIL = 17,                       /* NIL  */
  YYSYMBOL_EQUAL = 18,                     /* EQUAL  */
  YYSYMBOL_PLUS = 19,                      /* PLUS  */
  YYSYMBOL_MINUS = 20,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 21,                  /* MULTIPLY  */
  YYSYMBOL_SLASH_F = 22,                   /* SLASH_F  */
  YYSYMBOL_PERCENT = 23,                   /* PERCENT  */
  YYSYMBOL_EQUAL_TWO = 24,                 /* EQUAL_TWO  */
  YYSYMBOL_NOT_EQUAL = 25,                 /* NOT_EQUAL  */
  YYSYMBOL_PLUS_TWO = 26,                  /* PLUS_TWO  */
  YYSYMBOL_MINUS_TWO = 27,                 /* MINUS_TWO  */
  YYSYMBOL_GREATER = 28,                   /* GREATER  */
  YYSYMBOL_LESS = 29,                      /* LESS  */
  YYSYMBOL_B_EQUAL = 30,                   /* B_EQUAL  */
  YYSYMBOL_L_EQUAL = 31,                   /* L_EQUAL  */
  YYSYMBOL_NUM = 32,                       /* NUM  */
  YYSYMBOL_FLOAT = 33,                     /* FLOAT  */
  YYSYMBOL_STRING = 34,                    /* STRING  */
  YYSYMBOL_LEFT_BRACKET = 35,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 36,             /* RIGHT_BRACKET  */
  YYSYMBOL_LEFT_SQ_BRACKET = 37,           /* LEFT_SQ_BRACKET  */
  YYSYMBOL_RIGHT_SQ_BRACKET = 38,          /* RIGHT_SQ_BRACKET  */
  YYSYMBOL_LEFT_PARENTH = 39,              /* LEFT_PARENTH  */
  YYSYMBOL_RIGHT_PARENTH = 40,             /* RIGHT_PARENTH  */
  YYSYMBOL_SEMICOLON = 41,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 42,                     /* COMMA  */
  YYSYMBOL_COLON = 43,                     /* COLON  */
  YYSYMBOL_NAMESPACE_ = 44,                /* NAMESPACE_  */
  YYSYMBOL_DOT = 45,                       /* DOT  */
  YYSYMBOL_DOT_TWO = 46,                   /* DOT_TWO  */
  YYSYMBOL_ID = 47,                        /* ID  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_stmts = 50,                     /* stmts  */
  YYSYMBOL_stmt = 51,                      /* stmt  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_53_2 = 53,                      /* $@2  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_M = 55,                         /* M  */
  YYSYMBOL_N = 56,                         /* N  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_assignexpr = 58,                /* assignexpr  */
  YYSYMBOL_59_3 = 59,                      /* $@3  */
  YYSYMBOL_primary = 60,                   /* primary  */
  YYSYMBOL_lvalue = 61,                    /* lvalue  */
  YYSYMBOL_member = 62,                    /* member  */
  YYSYMBOL_call = 63,                      /* call  */
  YYSYMBOL_callsuffix = 64,                /* callsuffix  */
  YYSYMBOL_normcall = 65,                  /* normcall  */
  YYSYMBOL_methodcall = 66,                /* methodcall  */
  YYSYMBOL_elist = 67,                     /* elist  */
  YYSYMBOL_exprs = 68,                     /* exprs  */
  YYSYMBOL_objectdef = 69,                 /* objectdef  */
  YYSYMBOL_indexed = 70,                   /* indexed  */
  YYSYMBOL_indexedelems = 71,              /* indexedelems  */
  YYSYMBOL_indexedelem = 72,               /* indexedelem  */
  YYSYMBOL_block = 73,                     /* block  */
  YYSYMBOL_74_4 = 74,                      /* $@4  */
  YYSYMBOL_funcdef = 75,                   /* funcdef  */
  YYSYMBOL_76_5 = 76,                      /* @5  */
  YYSYMBOL_77_6 = 77,                      /* $@6  */
  YYSYMBOL_78_7 = 78,                      /* $@7  */
  YYSYMBOL_79_8 = 79,                      /* @8  */
  YYSYMBOL_80_9 = 80,                      /* $@9  */
  YYSYMBOL_81_10 = 81,                     /* $@10  */
  YYSYMBOL_const = 82,                     /* const  */
  YYSYMBOL_idlist = 83,                    /* idlist  */
  YYSYMBOL_ifprefix = 84,                  /* ifprefix  */
  YYSYMBOL_elseprefix = 85,                /* elseprefix  */
  YYSYMBOL_ifstmt = 86,                    /* ifstmt  */
  YYSYMBOL_whilestart = 87,                /* whilestart  */
  YYSYMBOL_whilecond = 88,                 /* whilecond  */
  YYSYMBOL_while = 89,                     /* while  */
  YYSYMBOL_forprefix = 90,                 /* forprefix  */
  YYSYMBOL_91_11 = 91,                     /* $@11  */
  YYSYMBOL_92_12 = 92,                     /* $@12  */
  YYSYMBOL_93_13 = 93,                     /* $@13  */
  YYSYMBOL_for = 94,                       /* for  */
  YYSYMBOL_returnstmt = 95                 /* returnstmt  */
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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  70
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   558

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  195

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   130,   130,   133,   141,   144,   159,   160,   161,   162,
     170,   170,   179,   179,   188,   189,   190,   194,   196,   202,
     208,   214,   220,   226,   239,   253,   267,   281,   296,   309,
     342,   374,   377,   378,   380,   381,   387,   402,   426,   451,
     475,   499,   502,   502,   537,   542,   543,   544,   549,   552,
     563,   572,   583,   588,   591,   600,   603,   604,   639,   647,
     648,   651,   658,   672,   673,   676,   677,   680,   695,   713,
     716,   717,   720,   725,   725,   729,   748,   748,   729,   759,
     772,   772,   759,   786,   787,   788,   789,   795,   800,   803,
     810,   817,   820,   840,   846,   847,   854,   857,   873,   885,
     885,   885,   885,   900,   915,   919
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
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "WHILE",
  "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR",
  "LOCAL", "TRUE", "FALSE", "NIL", "EQUAL", "PLUS", "MINUS", "MULTIPLY",
  "SLASH_F", "PERCENT", "EQUAL_TWO", "NOT_EQUAL", "PLUS_TWO", "MINUS_TWO",
  "GREATER", "LESS", "B_EQUAL", "L_EQUAL", "NUM", "FLOAT", "STRING",
  "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_SQ_BRACKET", "RIGHT_SQ_BRACKET",
  "LEFT_PARENTH", "RIGHT_PARENTH", "SEMICOLON", "COMMA", "COLON",
  "NAMESPACE_", "DOT", "DOT_TWO", "ID", "$accept", "program", "stmts",
  "stmt", "$@1", "$@2", "expr", "M", "N", "term", "assignexpr", "$@3",
  "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "exprs", "objectdef", "indexed", "indexedelems",
  "indexedelem", "block", "$@4", "funcdef", "@5", "$@6", "$@7", "@8",
  "$@9", "$@10", "const", "idlist", "ifprefix", "elseprefix", "ifstmt",
  "whilestart", "whilecond", "while", "forprefix", "$@11", "$@12", "$@13",
  "for", "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
#endif

#define YYPACT_NINF (-180)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-43)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     150,   -20,  -180,  -180,   -23,    94,  -180,  -180,   210,   -19,
    -180,  -180,  -180,   210,    16,    16,  -180,  -180,  -180,  -180,
     184,     6,  -180,    -1,  -180,    37,  -180,   150,   288,  -180,
    -180,  -180,   409,  -180,   -25,  -180,  -180,  -180,  -180,   150,
    -180,     9,  -180,  -180,  -180,  -180,   210,    20,  -180,    22,
    -180,   311,    10,    27,   501,  -180,   152,    73,    19,   -25,
      19,   150,   210,   264,    43,    47,    44,   357,    48,  -180,
    -180,  -180,  -180,  -180,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,  -180,  -180,  -180,   210,   210,
      42,    46,    72,  -180,  -180,  -180,   210,   210,    91,   210,
     150,   210,   379,   210,    58,  -180,  -180,  -180,  -180,    59,
      64,   239,   210,  -180,  -180,  -180,    66,  -180,  -180,    63,
     210,   210,    13,   152,  -180,  -180,  -180,   514,   514,   152,
     152,   152,   152,   438,    77,  -180,    65,   210,   459,    78,
    -180,   150,   401,  -180,    79,  -180,    71,  -180,    75,    63,
    -180,   210,   264,    44,   210,   527,   527,  -180,  -180,   210,
     501,  -180,  -180,  -180,  -180,  -180,  -180,    75,  -180,     7,
     480,  -180,  -180,    83,    84,   150,  -180,    12,  -180,    82,
    -180,  -180,  -180,  -180,   210,  -180,    90,  -180,  -180,   334,
      90,  -180,  -180,  -180,  -180
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,    96,    99,    79,     0,    10,    12,     0,     0,
      86,    87,    85,     0,     0,     0,    83,    88,    84,    73,
      64,     0,    16,     0,    49,     0,     2,     4,     0,    31,
      17,    41,    44,    52,    45,    46,    14,    15,    48,     0,
       6,     0,     7,    33,     8,     9,     0,     0,    75,     0,
     105,     0,     0,     0,    36,    50,    35,     0,    37,     0,
      40,     4,     0,    66,     0,     0,    71,     0,     0,    51,
       1,     3,    32,    32,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,    38,    39,     0,    64,
       0,     0,     0,    57,    59,    60,     0,    64,    94,     0,
       0,    64,     0,    64,     0,    80,   104,    11,    13,     0,
       0,     0,     0,    63,    67,    68,     0,    69,    34,    47,
       0,     0,    18,    19,    20,    21,    22,    25,    28,    26,
      23,    24,    27,     0,     0,    53,     0,     0,     0,     0,
      93,     0,     0,    98,     0,    92,     0,    76,    91,     0,
      74,     0,    66,    71,    64,    30,    29,    54,    61,    64,
      43,    55,    56,    95,    97,    33,   100,    91,    89,     0,
       0,    65,    70,     0,     0,     0,    32,     0,    81,     0,
      72,    58,    62,    33,     0,    77,     0,    90,   103,     0,
       0,    82,   101,    78,   102
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,   -17,   -38,  -180,  -180,    -5,   -71,  -156,  -180,
    -180,  -180,  -180,   -10,  -180,    52,  -180,  -180,  -180,   -72,
     -39,  -180,  -180,   -14,    14,  -179,  -180,   -15,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,   -33,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    52,    53,    28,   120,   101,    29,
      30,    92,    31,    32,    33,    34,    93,    94,    95,    64,
     113,    35,    65,   117,    66,    36,    61,    37,   104,   167,
     190,    49,   148,   186,    38,   169,    39,   141,    40,    41,
     100,    42,    43,    47,   176,   194,    44,    45
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,    98,   121,    54,    58,    60,    68,   191,    56,   175,
      71,   193,    96,     4,    97,    63,    67,   134,     8,    46,
       9,    10,    11,    12,    48,   139,    13,   188,    55,   144,
       9,   146,    14,    15,    76,    77,    78,    70,    16,    17,
      18,   102,   109,    20,   110,    21,    69,   178,    99,   179,
      23,   107,   185,    24,   179,    57,    88,   111,    89,   103,
      23,   105,   143,    24,    90,    91,    59,    59,   108,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
       4,   114,   173,   133,    63,   115,   116,   174,   119,   135,
     137,   138,    63,   136,   142,   140,    63,   147,    63,   149,
     150,    62,   154,   163,   159,   184,     8,   152,     9,    10,
      11,    12,   166,   171,    13,   155,   156,   158,   162,   165,
      14,    15,   168,   181,   182,    19,    16,    17,    18,   187,
     153,    20,   160,    21,   177,    50,     0,   183,    23,   172,
       0,    24,     0,     0,     0,     0,   170,     0,     0,    63,
       0,     0,     0,     1,    63,     2,     3,     4,     5,     6,
       7,     0,     8,     0,     9,    10,    11,    12,     0,     0,
      13,    74,    75,    76,    77,    78,    14,    15,     0,   189,
       0,     0,    16,    17,    18,    19,     0,    20,     0,    21,
       0,    22,     0,     0,    23,     0,     8,    24,     9,    10,
      11,    12,     0,     0,    13,     0,     0,     0,     0,     0,
      14,    15,     0,     0,     0,     0,    16,    17,    18,    62,
       0,    20,     8,    21,     9,    10,    11,    12,    23,     0,
      13,    24,     0,     0,     0,     0,    14,    15,     0,     0,
       0,     0,    16,    17,    18,     0,     0,    20,     0,    21,
      72,     0,    73,     0,    23,     0,     0,    24,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      84,     0,     0,     0,     0,    72,     0,    73,     0,     0,
       0,     0,   151,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,     0,     0,     0,    72,
       0,    73,     0,     0,     0,     0,   112,    74,    75,    76,
      77,    78,    79,    80,     0,     0,    81,    82,    83,    84,
       0,     0,    72,     0,    73,     0,     0,     0,     0,    85,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,    83,    84,     0,     0,    72,     0,    73,     0,     0,
       0,     0,   106,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,     0,     0,    72,     0,
      73,     0,     0,     0,     0,   192,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84,     0,
      72,     0,    73,     0,     0,     0,     0,   118,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      84,     0,    72,     0,    73,     0,     0,     0,     0,   145,
      74,    75,    76,    77,    78,    79,    80,   -42,     0,    81,
      82,    83,    84,     0,     0,    86,    87,     0,     0,     0,
       0,   164,     0,     0,     0,     0,    88,     0,    89,    72,
       0,    73,     0,     0,    90,    91,     0,    74,    75,    76,
      77,    78,    79,    80,     0,     0,    81,    82,    83,    84,
      72,     0,    73,     0,     0,     0,   157,     0,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      84,    72,     0,    73,     0,     0,     0,   161,     0,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      83,    84,    72,     0,    73,     0,   180,     0,     0,     0,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,    83,    84,    74,    75,    76,    77,    78,   -43,   -43,
       0,     0,    81,    82,    83,    84,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
       5,    39,    73,     8,    14,    15,    21,   186,    13,   165,
      27,   190,    37,     7,    39,    20,    21,    89,    12,    39,
      14,    15,    16,    17,    47,    97,    20,   183,    47,   101,
      14,   103,    26,    27,    21,    22,    23,     0,    32,    33,
      34,    46,    57,    37,    61,    39,    47,    40,    39,    42,
      44,    41,    40,    47,    42,    39,    37,    62,    39,    39,
      44,    39,   100,    47,    45,    46,    14,    15,    41,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       7,    38,   154,    88,    89,    38,    42,   159,    40,    47,
      18,    96,    97,    47,    99,     4,   101,    39,   103,    40,
      36,    35,    39,   141,    39,   176,    12,   112,    14,    15,
      16,    17,    41,   152,    20,   120,   121,    40,    40,    40,
      26,    27,    47,    40,    40,    35,    32,    33,    34,    47,
     116,    37,   137,    39,   167,    41,    -1,   175,    44,   153,
      -1,    47,    -1,    -1,    -1,    -1,   151,    -1,    -1,   154,
      -1,    -1,    -1,     3,   159,     5,     6,     7,     8,     9,
      10,    -1,    12,    -1,    14,    15,    16,    17,    -1,    -1,
      20,    19,    20,    21,    22,    23,    26,    27,    -1,   184,
      -1,    -1,    32,    33,    34,    35,    -1,    37,    -1,    39,
      -1,    41,    -1,    -1,    44,    -1,    12,    47,    14,    15,
      16,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,    35,
      -1,    37,    12,    39,    14,    15,    16,    17,    44,    -1,
      20,    47,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    32,    33,    34,    -1,    -1,    37,    -1,    39,
      11,    -1,    13,    -1,    44,    -1,    -1,    47,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    11,    -1,    13,    -1,    -1,
      -1,    -1,    43,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    -1,    -1,    11,
      -1,    13,    -1,    -1,    -1,    -1,    42,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      -1,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,    41,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    -1,    -1,    11,    -1,    13,    -1,    -1,
      -1,    -1,    41,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    -1,    -1,    11,    -1,
      13,    -1,    -1,    -1,    -1,    41,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    -1,
      11,    -1,    13,    -1,    -1,    -1,    -1,    40,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,    40,
      19,    20,    21,    22,    23,    24,    25,    18,    -1,    28,
      29,    30,    31,    -1,    -1,    26,    27,    -1,    -1,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    37,    -1,    39,    11,
      -1,    13,    -1,    -1,    45,    46,    -1,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      11,    -1,    13,    -1,    -1,    -1,    38,    -1,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    11,    -1,    13,    -1,    -1,    -1,    38,    -1,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31,    11,    -1,    13,    -1,    36,    -1,    -1,    -1,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    10,    12,    14,
      15,    16,    17,    20,    26,    27,    32,    33,    34,    35,
      37,    39,    41,    44,    47,    49,    50,    51,    54,    57,
      58,    60,    61,    62,    63,    69,    73,    75,    82,    84,
      86,    87,    89,    90,    94,    95,    39,    91,    47,    79,
      41,    54,    52,    53,    54,    47,    54,    39,    61,    63,
      61,    74,    35,    54,    67,    70,    72,    54,    75,    47,
       0,    50,    11,    13,    19,    20,    21,    22,    23,    24,
      25,    28,    29,    30,    31,    41,    26,    27,    37,    39,
      45,    46,    59,    64,    65,    66,    37,    39,    51,    39,
      88,    56,    54,    39,    76,    39,    41,    41,    41,    75,
      50,    54,    42,    68,    38,    38,    42,    71,    40,    40,
      55,    55,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    67,    47,    47,    18,    54,    67,
       4,    85,    54,    51,    67,    40,    67,    39,    80,    40,
      36,    43,    54,    72,    39,    54,    54,    38,    40,    39,
      54,    38,    40,    51,    40,    40,    41,    77,    47,    83,
      54,    68,    71,    67,    67,    56,    92,    83,    40,    42,
      36,    40,    40,    51,    55,    40,    81,    47,    56,    54,
      78,    73,    41,    73,    93
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      52,    51,    53,    51,    51,    51,    51,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    56,    57,    57,    57,    57,    57,    57,
      57,    57,    59,    58,    60,    60,    60,    60,    60,    61,
      61,    61,    61,    62,    62,    62,    63,    63,    63,    64,
      64,    65,    66,    67,    67,    68,    68,    69,    69,    70,
      71,    71,    72,    74,    73,    76,    77,    78,    75,    79,
      80,    81,    75,    82,    82,    82,    82,    82,    82,    83,
      83,    83,    84,    85,    86,    86,    87,    88,    89,    91,
      92,    93,    90,    94,    95,    95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       0,     3,     0,     3,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       4,     1,     0,     0,     3,     2,     2,     2,     2,     2,
       2,     1,     0,     4,     1,     1,     1,     3,     1,     1,
       2,     2,     1,     3,     4,     4,     4,     2,     6,     1,
       1,     3,     5,     2,     0,     3,     0,     3,     3,     2,
       3,     0,     5,     0,     4,     0,     0,     0,     9,     0,
       0,     0,     8,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     1,     2,     4,     1,     3,     3,     0,
       0,     0,    10,     7,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
  case 3: /* stmts: stmt stmts  */
#line 133 "parser.y"
                    {
        (yyval.stmt)=(yyvsp[-1].stmt);
         
        // if($2!=NULL && $1!=NULL){
        //         $$->breakList = mergeList($1->breakList, $2->breakList);
        //         $$->contList = mergeList($1->contList, $2->contList);   
        // }
        }
#line 1404 "parser.c"
    break;

  case 4: /* stmts: %empty  */
#line 141 "parser.y"
         {(yyval.stmt)=NULL;}
#line 1410 "parser.c"
    break;

  case 5: /* stmt: expr SEMICOLON  */
#line 144 "parser.y"
                     {
        namespace_flag=0; 
 
        if((yyvsp[-1].expr)->type==boolexpr_e || (yyvsp[-1].expr)->type==constbool_e){
        backPatch((yyvsp[-1].expr)->trueList,nextQuad());
        backPatch((yyvsp[-1].expr)->falseList,nextQuad()+2);

        emit(assign,newExpr_constBool(1),NULL,(yyvsp[-1].expr),-1,yylineno);
        emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
        emit(assign,newExpr_constBool(0),NULL,(yyvsp[-1].expr),-1,yylineno);
        
        }


        }
#line 1430 "parser.c"
    break;

  case 6: /* stmt: ifstmt  */
#line 159 "parser.y"
            {}
#line 1436 "parser.c"
    break;

  case 7: /* stmt: while  */
#line 160 "parser.y"
           {(yyval.stmt) = NULL;}
#line 1442 "parser.c"
    break;

  case 8: /* stmt: for  */
#line 161 "parser.y"
         {(yyval.stmt)=NULL;}
#line 1448 "parser.c"
    break;

  case 9: /* stmt: returnstmt  */
#line 162 "parser.y"
                {

        (yyvsp[0].stmt) = make_stmt((yyvsp[0].stmt));
        (yyvsp[0].stmt)->returnList = newList(nextQuad());
        push(returnst,(yyvsp[0].stmt)->returnList);
        emit(jump, NULL, NULL, newExpr(var_e), -1, yylineno);

    }
#line 1461 "parser.c"
    break;

  case 10: /* $@1: %empty  */
#line 170 "parser.y"
        { if(while_flag==0 && for_flag==0){
         yyerror("Break out of loop");
        }else{
                (yyvsp[0].stmt) = make_stmt((yyvsp[0].stmt));
                (yyvsp[0].stmt)->breakList = newList(nextQuad());
                push(breakst,(yyvsp[0].stmt)->breakList);
                emit(jump, NULL, NULL, NULL, -1, yylineno);
        } 
    }
#line 1475 "parser.c"
    break;

  case 12: /* $@2: %empty  */
#line 179 "parser.y"
              { if(while_flag==0 && for_flag==0){
            yyerror("Continue out of loop");
        }else{
                (yyvsp[0].stmt) = make_stmt((yyvsp[0].stmt));
                (yyvsp[0].stmt)->contList = newList(nextQuad());
                push(contst,(yyvsp[0].stmt)->contList);
                emit(jump, NULL, NULL, NULL, -1, yylineno);
        }  
    }
#line 1489 "parser.c"
    break;

  case 14: /* stmt: block  */
#line 188 "parser.y"
           {(yyval.stmt)=NULL;}
#line 1495 "parser.c"
    break;

  case 15: /* stmt: funcdef  */
#line 189 "parser.y"
             {}
#line 1501 "parser.c"
    break;

  case 16: /* stmt: SEMICOLON  */
#line 190 "parser.y"
               {(yyval.stmt)=NULL;}
#line 1507 "parser.c"
    break;

  case 17: /* expr: assignexpr  */
#line 194 "parser.y"
                 {(yyval.expr)=(yyvsp[0].expr); flagSemicolon=1;}
#line 1513 "parser.c"
    break;

  case 18: /* expr: expr PLUS expr  */
#line 196 "parser.y"
                     {   
        (yyval.expr)=newExpr(arithexpr_e);
        (yyval.expr)->sym=newtemp();
        if((yyvsp[-2].expr)->type==constnum_e && (yyvsp[0].expr)->type==constnum_e) (yyval.expr)->type = constnum_e;
        emit(add,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);       
    }
#line 1524 "parser.c"
    break;

  case 19: /* expr: expr MINUS expr  */
#line 202 "parser.y"
                       {
        (yyval.expr)=newExpr(arithexpr_e);
        (yyval.expr)->sym=newtemp();
        if((yyvsp[-2].expr)->type==constnum_e && (yyvsp[0].expr)->type==constnum_e) (yyval.expr)->type = constnum_e;
        emit(sub,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);
    }
#line 1535 "parser.c"
    break;

  case 20: /* expr: expr MULTIPLY expr  */
#line 208 "parser.y"
                        {
        (yyval.expr)=newExpr(arithexpr_e);
        (yyval.expr)->sym=newtemp();
        if((yyvsp[-2].expr)->type==constnum_e && (yyvsp[0].expr)->type==constnum_e) (yyval.expr)->type = constnum_e;
        emit(mul,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);
    }
#line 1546 "parser.c"
    break;

  case 21: /* expr: expr SLASH_F expr  */
#line 214 "parser.y"
                       {
        (yyval.expr)=newExpr(arithexpr_e);
        (yyval.expr)->sym=newtemp();
        if((yyvsp[-2].expr)->type==constnum_e && (yyvsp[0].expr)->type==constnum_e) (yyval.expr)->type = constnum_e;
        emit(_div,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);
    }
#line 1557 "parser.c"
    break;

  case 22: /* expr: expr PERCENT expr  */
#line 220 "parser.y"
                       {
        (yyval.expr)=newExpr(arithexpr_e);
        (yyval.expr)->sym=newtemp();
        if((yyvsp[-2].expr)->type==constnum_e && (yyvsp[0].expr)->type==constnum_e) (yyval.expr)->type = constnum_e;
        emit(mod,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);
    }
#line 1568 "parser.c"
    break;

  case 23: /* expr: expr LESS expr  */
#line 226 "parser.y"
                    {            
        (yyval.expr)=newExpr(boolexpr_e);
        (yyval.expr)->sym=newtemp();

        (yyval.expr)->trueList = makeList(nextQuad());

        (yyval.expr)->falseList = makeList(nextQuad()+1);

        emit(if_less,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
       
    }
#line 1586 "parser.c"
    break;

  case 24: /* expr: expr B_EQUAL expr  */
#line 239 "parser.y"
                        {


        (yyval.expr)=newExpr(boolexpr_e);
        (yyval.expr)->sym=newtemp();

        (yyval.expr)->trueList = makeList(nextQuad());

        (yyval.expr)->falseList = makeList(nextQuad()+1);

        emit(if_greatereq,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }
#line 1605 "parser.c"
    break;

  case 25: /* expr: expr EQUAL_TWO expr  */
#line 253 "parser.y"
                          {


        (yyval.expr)=newExpr(boolexpr_e);
        (yyval.expr)->sym=newtemp();

        (yyval.expr)->trueList = makeList(nextQuad());

        (yyval.expr)->falseList = makeList(nextQuad()+1);

        emit(if_eq,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }
#line 1624 "parser.c"
    break;

  case 26: /* expr: expr GREATER expr  */
#line 267 "parser.y"
                       {

        (yyval.expr)=newExpr(boolexpr_e);
        (yyval.expr)->sym=newtemp();

        (yyval.expr)->trueList = makeList(nextQuad());

        (yyval.expr)->falseList = makeList(nextQuad()+1);


        emit(if_greater,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }
#line 1643 "parser.c"
    break;

  case 27: /* expr: expr L_EQUAL expr  */
#line 281 "parser.y"
                        {


        (yyval.expr)=newExpr(boolexpr_e);
        (yyval.expr)->sym=newtemp();

        (yyval.expr)->trueList = makeList(nextQuad());

        (yyval.expr)->falseList = makeList(nextQuad()+1);


        emit(if_lesseq,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }
#line 1663 "parser.c"
    break;

  case 28: /* expr: expr NOT_EQUAL expr  */
#line 296 "parser.y"
                         {

        (yyval.expr)=newExpr(boolexpr_e);
        (yyval.expr)->sym=newtemp();

        (yyval.expr)->trueList = makeList(nextQuad());

        (yyval.expr)->falseList = makeList(nextQuad()+1);

        emit(if_noteq,(yyvsp[-2].expr), (yyvsp[0].expr), (yyval.expr) ,-1 ,yylineno);

        emit(jump,NULL,NULL,NULL,-1,yylineno);
    }
#line 1681 "parser.c"
    break;

  case 29: /* expr: expr OR M expr  */
#line 309 "parser.y"
                     {  
          
            if((yyvsp[-3].expr)->type!=boolexpr_e)
        {     
                convert2Bool((yyvsp[-3].expr));
                (yyvsp[-3].expr)->trueList = makeList(nextQuad());
                (yyvsp[-3].expr)->falseList = makeList(nextQuad()+1);
                emit(if_eq,(yyvsp[-3].expr), newExpr_constBool(1), (yyval.expr) ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);
                (yyvsp[-1].int_val)= nextQuad();
            
        }
         if((yyvsp[0].expr)->type!=boolexpr_e)
        {    
               
                convert2Bool((yyvsp[0].expr));
                (yyvsp[0].expr)->trueList = makeList(nextQuad());
                (yyvsp[0].expr)->falseList = makeList(nextQuad()+1);
                emit(if_eq,(yyvsp[0].expr), newExpr_constBool(1), (yyval.expr) ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);

        }

        (yyval.expr)=newExpr(boolexpr_e);
        (yyval.expr)->sym=newtemp();
        backPatch((yyvsp[-3].expr)->falseList, (yyvsp[-1].int_val));
        backPatch((yyvsp[-3].expr)->trueList,nextQuad());
        // orQuad = $1->trueList->label;
       
        (yyval.expr)->trueList = mergeBackPatch((yyvsp[-3].expr)->trueList,(yyvsp[0].expr)->trueList);
        (yyval.expr)->falseList = (yyvsp[0].expr)->falseList;

    }
#line 1719 "parser.c"
    break;

  case 30: /* expr: expr AND M expr  */
#line 342 "parser.y"
                       {
        if((yyvsp[-3].expr)->type!=boolexpr_e)
        {      
                convert2Bool((yyvsp[-3].expr));
                (yyvsp[-3].expr)->trueList = makeList(nextQuad());
                (yyvsp[-3].expr)->falseList = makeList(nextQuad()+1);
                emit(if_eq,(yyvsp[-3].expr), newExpr_constBool(1), (yyval.expr) ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);
                      (yyvsp[-1].int_val)= nextQuad();
        }
         if((yyvsp[0].expr)->type!=boolexpr_e )
        {       
                convert2Bool((yyvsp[0].expr));
                (yyvsp[0].expr)->trueList = makeList(nextQuad());
                (yyvsp[0].expr)->falseList = makeList(nextQuad()+1);
                emit(if_eq,(yyvsp[0].expr), newExpr_constBool(1), (yyval.expr) ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);
          

        }
        (yyval.expr)=newExpr(boolexpr_e);
        (yyval.expr)->sym=newtemp();
        backPatch((yyvsp[-3].expr)->trueList, (yyvsp[-1].int_val));
        backPatch((yyvsp[-3].expr)->falseList,nextQuad()+2);
        
        (yyval.expr)->trueList = (yyvsp[0].expr)->trueList;
        (yyval.expr)->falseList = mergeBackPatch((yyvsp[-3].expr)->falseList,(yyvsp[0].expr)->falseList);
//   if(eimaiOr==1)
//   {
//           backPatch(orQuad,nextQuad()+2);
//   }
    }
#line 1756 "parser.c"
    break;

  case 31: /* expr: term  */
#line 374 "parser.y"
                {(yyval.expr)=(yyvsp[0].expr); }
#line 1762 "parser.c"
    break;

  case 32: /* M: %empty  */
#line 377 "parser.y"
    {(yyval.int_val)=nextQuad();}
#line 1768 "parser.c"
    break;

  case 33: /* N: %empty  */
#line 378 "parser.y"
   { (yyval.int_val) = nextQuad(); emit(jump,NULL,NULL,NULL,0,yylineno); }
#line 1774 "parser.c"
    break;

  case 34: /* term: LEFT_PARENTH expr RIGHT_PARENTH  */
#line 380 "parser.y"
                                      {(yyval.expr)=(yyvsp[-1].expr);}
#line 1780 "parser.c"
    break;

  case 35: /* term: MINUS expr  */
#line 381 "parser.y"
                   {
                check_arith((yyvsp[0].expr),yylineno);
                (yyval.expr) = newExpr(arithexpr_e);
                (yyval.expr)->sym = istempexpr((yyvsp[0].expr)) ? (yyvsp[0].expr)->sym : newtemp();
                emit(uminus,(yyvsp[0].expr), NULL, (yyval.expr),nextQuad(),yylineno);
      }
#line 1791 "parser.c"
    break;

  case 36: /* term: NOT expr  */
#line 387 "parser.y"
                  {
        flagLogical=1;
        if((yyvsp[0].expr)->type!=boolexpr_e)
        {      
               // convert2Bool($2);
                (yyvsp[0].expr)->trueList = makeList(nextQuad());
                (yyvsp[0].expr)->falseList = makeList(nextQuad()+1);
                emit(if_eq,(yyvsp[0].expr), newExpr_constBool(1), (yyval.expr) ,nextQuad(),yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+1,yylineno);               
        }
              (yyval.expr)=newExpr(boolexpr_e);
              (yyval.expr)->sym=newtemp();                            
              (yyval.expr)->trueList = (yyvsp[0].expr)->falseList;
              (yyval.expr)->falseList = (yyvsp[0].expr)->trueList;
      }
#line 1811 "parser.c"
    break;

  case 37: /* term: PLUS_TWO lvalue  */
#line 402 "parser.y"
                        {
                if((yyvsp[0].expr) != NULL && ((yyvsp[0].expr)->sym->type == LIB || (yyvsp[0].expr)->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }

                               else{                                        
                                flagSemicolon =1;
                                check_arith((yyvsp[0].expr),yylineno);
                                if ((yyvsp[0].expr)->type == tableitem_e) {
                                (yyval.expr) = emit_ifTableItem((yyvsp[0].expr));
                                emit(add, (yyval.expr), num_expr(1), (yyval.expr),nextQuad(),yylineno);
                                emit(tablesetelem, (yyvsp[0].expr), (yyvsp[0].expr)->index, (yyval.expr),nextQuad(),yylineno);
                                }
                                else {
                                emit(add, (yyvsp[0].expr), num_expr(1), (yyvsp[0].expr),nextQuad(),yylineno);
                                (yyval.expr) = newExpr(arithexpr_e);
                                (yyval.expr)->sym = newtemp();
                                emit(assign, (yyvsp[0].expr), NULL, (yyval.expr),-1,yylineno);
                                }}
                                                        
                        }
#line 1838 "parser.c"
    break;

  case 38: /* term: lvalue PLUS_TWO  */
#line 426 "parser.y"
                         {
               if((yyvsp[-1].expr) != NULL && ((yyvsp[-1].expr)->sym->type == LIB || (yyvsp[-1].expr)->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }
         else{
                                flagSemicolon =1;
                                // NA KANOYME AYTO
                                 check_arith((yyvsp[-1].expr),yylineno);
                                (yyval.expr) = newExpr(var_e);
                                (yyval.expr)->sym = newtemp();
                                if ((yyvsp[-1].expr)->type == tableitem_e) {
                                expr* val = emit_ifTableItem((yyvsp[-1].expr));
                                emit(assign, val, NULL, (yyval.expr),-1,yylineno);
                                emit(add, val, num_expr(1), val,nextQuad(),yylineno);
                                emit(tablesetelem, (yyvsp[-1].expr), (yyvsp[-1].expr)->index, val,nextQuad(),yylineno);
                                }
                                else {
                                emit(assign, (yyvsp[-1].expr), NULL, (yyval.expr),-1,yylineno);
                                emit(add, (yyvsp[-1].expr), num_expr(1), (yyvsp[-1].expr),nextQuad(),yylineno);
                                }
                                
                                }
      }
#line 1867 "parser.c"
    break;

  case 39: /* term: lvalue MINUS_TWO  */
#line 451 "parser.y"
                         {
                       if((yyvsp[-1].expr) != NULL && ((yyvsp[-1].expr)->sym->type == LIB || (yyvsp[-1].expr)->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }
              else{
                                flagSemicolon =1;
                                check_arith((yyvsp[-1].expr),yylineno);
                                (yyval.expr) = newExpr(var_e);
                                (yyval.expr)->sym = newtemp();
                                if ((yyvsp[-1].expr)->type == tableitem_e) {
                                expr* val = emit_ifTableItem((yyvsp[-1].expr));
                                emit(assign, val, NULL, (yyval.expr),-1,yylineno);
                                emit(sub, val, num_expr(1), val,nextQuad(),yylineno);
                                emit(tablesetelem, (yyvsp[-1].expr), (yyvsp[-1].expr)->index, val,nextQuad(),yylineno);
                                }
                                else {
                                emit(assign, (yyvsp[-1].expr), NULL, (yyval.expr),-1,yylineno);
                                emit(sub, (yyvsp[-1].expr), num_expr(1), (yyvsp[-1].expr),nextQuad(),yylineno);
                                }
                                
                                }
        
        }
#line 1896 "parser.c"
    break;

  case 40: /* term: MINUS_TWO lvalue  */
#line 475 "parser.y"
                         {
         if((yyvsp[0].expr) != NULL && ((yyvsp[0].expr)->sym->type == LIB || (yyvsp[0].expr)->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }
        else{ 
                                       
                                flagSemicolon =1;
                                check_arith((yyvsp[0].expr),yylineno);
                                if ((yyvsp[0].expr)->type == tableitem_e) {
                                (yyval.expr) = emit_ifTableItem((yyvsp[0].expr));
                                emit(sub, (yyval.expr), num_expr(1), (yyval.expr),nextQuad(),yylineno);
                                emit(tablesetelem, (yyvsp[0].expr), (yyvsp[0].expr)->index, (yyval.expr),nextQuad(),yylineno);
                                }
                                else {
                                emit(sub, (yyvsp[0].expr), num_expr(1), (yyvsp[0].expr),nextQuad(),yylineno);
                                (yyval.expr) = newExpr(arithexpr_e);
                                (yyval.expr)->sym = newtemp();
                                emit(assign, (yyvsp[0].expr), NULL, (yyval.expr),-1,yylineno);
                                }
                                }
                                                        
                        
      }
#line 1925 "parser.c"
    break;

  case 41: /* term: primary  */
#line 499 "parser.y"
               {(yyval.expr)=(yyvsp[0].expr);}
#line 1931 "parser.c"
    break;

  case 42: /* $@3: %empty  */
#line 502 "parser.y"
                   {                
                         if((yyvsp[0].expr) != NULL && ((yyvsp[0].expr)->sym->type == LIB || (yyvsp[0].expr)->sym->type == USERF))
                        {
                                yyerror("Symbol is function");
                        }       
                }
#line 1942 "parser.c"
    break;

  case 43: /* assignexpr: lvalue $@3 EQUAL expr  */
#line 508 "parser.y"
                     {
        flagSemicolon=1;
        if((yyvsp[0].expr)->type==boolexpr_e)
        {    
                backPatch((yyvsp[0].expr)->trueList,nextQuad());
                backPatch((yyvsp[0].expr)->falseList,nextQuad()+2);
                emit(assign,newExpr_constBool(1),NULL,(yyvsp[0].expr),0,yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
                emit(assign,newExpr_constBool(0),NULL,(yyvsp[0].expr),0,yylineno);
        }

        if ((yyvsp[-3].expr)!=NULL && (yyvsp[-3].expr)->type == tableitem_e){
                emit(
                tablesetelem,(yyvsp[-3].expr),(yyvsp[-3].expr)->index,(yyvsp[0].expr),nextQuad(),yylineno);
                (yyval.expr) = emit_ifTableItem((yyvsp[-3].expr));
                (yyval.expr)->type = assignexpr_e;
        }
        else
        {
                (yyval.expr)=newExpr(assignexpr_e);
                (yyval.expr)->sym=newtemp();
                emit(assign,(yyvsp[0].expr), NULL, (yyvsp[-3].expr) ,-1 ,yylineno); //x=2; 
                emit(assign,(yyvsp[-3].expr), NULL, (yyval.expr) ,-1 ,yylineno); //assign olo to assignment sto tmp
        }
       
    }
#line 1973 "parser.c"
    break;

  case 44: /* primary: lvalue  */
#line 537 "parser.y"
                 {   
        (yyval.expr)=(yyvsp[0].expr);
        //TSEKARE TO
         (yyval.expr) = emit_ifTableItem((yyvsp[0].expr));
        }
#line 1983 "parser.c"
    break;

  case 46: /* primary: objectdef  */
#line 543 "parser.y"
                    {}
#line 1989 "parser.c"
    break;

  case 47: /* primary: LEFT_PARENTH funcdef RIGHT_PARENTH  */
#line 544 "parser.y"
                                              {
                (yyval.expr) = newExpr(programfunc_e);
                (yyval.expr)->sym = tmpFuncName->sym;
                (yyval.expr)=(yyvsp[-1].expr);
        }
#line 1999 "parser.c"
    break;

  case 48: /* primary: const  */
#line 549 "parser.y"
                 {(yyval.expr)=(yyvsp[0].expr); }
#line 2005 "parser.c"
    break;

  case 49: /* lvalue: ID  */
#line 552 "parser.y"
            { 
        //if(is_Function(yylval.string_Val,curr_scope)==1){
                sym_t* result;
                result=lookup_X(curr_scope,yylval.string_Val,4,yylineno);   
                if(result==NULL){
                        yyerror("Variable with Function in between");
                }else{
                        (yyval.expr)=lvalue_expr(result);
                }         
        //}  
        }
#line 2021 "parser.c"
    break;

  case 50: /* lvalue: LOCAL ID  */
#line 563 "parser.y"
                  {
                sym_t* result;
                result=lookup_LocalVar(curr_scope,yylval.string_Val,0,yylineno);
                if(result==NULL){
                        yyerror("Exists as library function");
                }else{
                        (yyval.expr)=lvalue_expr(result);
                }         
        }
#line 2035 "parser.c"
    break;

  case 51: /* lvalue: NAMESPACE_ ID  */
#line 572 "parser.y"
                         {
                namespace_flag=1; 
                sym_t* result;
                strcpy(func_name,yylval.string_Val);  
                result= lookup_GlblVar(yylval.string_Val);
                if(result==NULL) {
                        yyerror("global symbol does not exist");
                }else{
                        (yyval.expr)=lvalue_expr(result);
                }
        }
#line 2051 "parser.c"
    break;

  case 52: /* lvalue: member  */
#line 583 "parser.y"
                 {
                       
                (yyval.expr)=(yyvsp[0].expr); }
#line 2059 "parser.c"
    break;

  case 53: /* member: lvalue DOT ID  */
#line 588 "parser.y"
                        { 
                 (yyval.expr) = member_item((yyvsp[-2].expr),(yyvsp[0].string_Val));
                }
#line 2067 "parser.c"
    break;

  case 54: /* member: lvalue LEFT_SQ_BRACKET expr RIGHT_SQ_BRACKET  */
#line 591 "parser.y"
                                                       {
                     
                flagSemicolon=1;
                (yyvsp[-3].expr) = emit_ifTableItem((yyvsp[-3].expr));
                (yyval.expr) = newExpr(tableitem_e);
                (yyval.expr)->sym = (yyvsp[-3].expr)->sym;
                (yyval.expr)->index = (yyvsp[-1].expr);

        }
#line 2081 "parser.c"
    break;

  case 55: /* member: call LEFT_SQ_BRACKET expr RIGHT_SQ_BRACKET  */
#line 600 "parser.y"
                                                    {flagSemicolon=1;}
#line 2087 "parser.c"
    break;

  case 56: /* call: call LEFT_PARENTH elist RIGHT_PARENTH  */
#line 603 "parser.y"
                                             {flagSemicolon=1; (yyval.expr)=make_call((yyvsp[-3].expr),(yyvsp[-1].expr),yylineno);}
#line 2093 "parser.c"
    break;

  case 57: /* call: lvalue callsuffix  */
#line 604 "parser.y"
                       {
                flagSemicolon=1;    
                if(namespace_flag==1){
                        sym_t* result;
                        result=lookup_GlblVar(func_name);
                        if(result==NULL){ yyerror("Not Found");
                        }
                        else{
                                (yyval.expr)=make_call((yyvsp[-1].expr),(yyvsp[0].call_f)->elist,yylineno);}

                }else{
                        sym_t* result;
                        if((yyvsp[0].call_f)->method==1){
                                result=lookup_X(curr_scope,(yyvsp[0].call_f)->name,2,yylineno);
                        }else{
                                result=lookup_X(curr_scope,(yyvsp[-1].expr)->sym->name,2,yylineno);
                        }
                        if(result==NULL) {yyerror("Variable with function in between");}
                        else{
                           (yyval.expr)=emit_ifTableItem((yyvsp[-1].expr));  
                           if((yyvsp[0].call_f)->method==1){
                                   expr *t=(yyvsp[-1].expr);
                                   (yyvsp[-1].expr)=emit_ifTableItem(member_item(t,(yyvsp[0].call_f)->name));
                                   expr *tmplist;
                                   tmplist=t;
                                   tmplist->next=(yyvsp[0].call_f)->elist;
                                   (yyvsp[0].call_f)->elist=tmplist;
                           }else{
                                   (yyvsp[-1].expr)=lvalue_expr(result);
                           }  
                           (yyval.expr)=make_call((yyvsp[-1].expr),(yyvsp[0].call_f)->elist,yylineno);
                        }
                        ;
                }
            }
#line 2133 "parser.c"
    break;

  case 58: /* call: LEFT_PARENTH funcdef RIGHT_PARENTH LEFT_PARENTH elist RIGHT_PARENTH  */
#line 639 "parser.y"
                                                                         {
                flagSemicolon=1;    
            //expr* funcCall = newExpr(programfunc_e);
            //funcCall->sym = $2->sym;
            (yyval.expr) = make_call(tmpFuncName,(yyvsp[-1].expr),yylineno);  //ftiaxto mori tebela plizz
    }
#line 2144 "parser.c"
    break;

  case 59: /* callsuffix: normcall  */
#line 647 "parser.y"
                     {(yyval.call_f)=(yyvsp[0].call_f);}
#line 2150 "parser.c"
    break;

  case 60: /* callsuffix: methodcall  */
#line 648 "parser.y"
                    {(yyval.call_f)=(yyvsp[0].call_f);}
#line 2156 "parser.c"
    break;

  case 61: /* normcall: LEFT_PARENTH elist RIGHT_PARENTH  */
#line 651 "parser.y"
                                           {
        (yyval.call_f)->elist=(yyvsp[-1].expr);
        (yyval.call_f)->method=0;
        (yyval.call_f)->name=NULL;
}
#line 2166 "parser.c"
    break;

  case 62: /* methodcall: DOT_TWO ID LEFT_PARENTH elist RIGHT_PARENTH  */
#line 658 "parser.y"
                                                        {
                sym_t* result;
                result=lookup_X(curr_scope,(yyvsp[-3].string_Val),2,yylineno); //sosto?
                if(result==NULL){
                        yyerror("Variable with function in between");
                }else{
                        (yyval.call_f)->elist=(yyvsp[-1].expr);
                        (yyval.call_f)->method=1;
                        (yyval.call_f)->name=result->name;
                }
        }
#line 2182 "parser.c"
    break;

  case 63: /* elist: expr exprs  */
#line 672 "parser.y"
                  {(yyval.expr)=(yyvsp[-1].expr); (yyval.expr)->next=(yyvsp[0].expr); }
#line 2188 "parser.c"
    break;

  case 64: /* elist: %empty  */
#line 673 "parser.y"
          {(yyval.expr)=NULL;}
#line 2194 "parser.c"
    break;

  case 65: /* exprs: COMMA expr exprs  */
#line 676 "parser.y"
                        {(yyval.expr)=(yyvsp[-1].expr); (yyval.expr)->next=(yyvsp[0].expr); }
#line 2200 "parser.c"
    break;

  case 66: /* exprs: %empty  */
#line 677 "parser.y"
          {(yyval.expr)=NULL;}
#line 2206 "parser.c"
    break;

  case 67: /* objectdef: LEFT_SQ_BRACKET elist RIGHT_SQ_BRACKET  */
#line 680 "parser.y"
                                                 {

        flagSemicolon=1;
        expr* newTableExpr = newExpr(newtable_e);
        newTableExpr->sym = newtemp();
        emit(tablecreate, newTableExpr, NULL, NULL,nextQuad(),yylineno);
        int i=0;
       while((yyvsp[-1].expr)!=NULL)
       { 
        emit(tablesetelem, newTableExpr, num_expr(i++), (yyvsp[-1].expr),nextQuad(),yylineno);
        (yyvsp[-1].expr)=(yyvsp[-1].expr)->next;
       }
        (yyval.expr) = newTableExpr;

 }
#line 2226 "parser.c"
    break;

  case 68: /* objectdef: LEFT_SQ_BRACKET indexed RIGHT_SQ_BRACKET  */
#line 695 "parser.y"
                                                   {

                flagSemicolon=1;
                expr* newTableExpr = newExpr(newtable_e);
                newTableExpr->sym = newtemp();
                emit(tablecreate, newTableExpr, NULL, NULL,nextQuad(),yylineno);
                while((yyvsp[-1].expr)!=NULL)
                { 

                        emit(tablesetelem, newTableExpr, (yyvsp[-1].expr), (yyvsp[-1].expr)->index,nextQuad(),yylineno);
                        (yyvsp[-1].expr)=(yyvsp[-1].expr)->next;
                }

                (yyval.expr) = newTableExpr;

        }
#line 2247 "parser.c"
    break;

  case 69: /* indexed: indexedelem indexedelems  */
#line 713 "parser.y"
                                 {(yyval.expr)=(yyvsp[-1].expr); (yyval.expr)->next=(yyvsp[0].expr);}
#line 2253 "parser.c"
    break;

  case 70: /* indexedelems: COMMA indexedelem indexedelems  */
#line 716 "parser.y"
                                             {(yyval.expr)=(yyvsp[-1].expr); (yyval.expr)->next=(yyvsp[0].expr);}
#line 2259 "parser.c"
    break;

  case 71: /* indexedelems: %empty  */
#line 717 "parser.y"
          {(yyval.expr)=NULL;}
#line 2265 "parser.c"
    break;

  case 72: /* indexedelem: LEFT_BRACKET expr COLON expr RIGHT_BRACKET  */
#line 720 "parser.y"
                                                       { (yyval.expr)=(yyvsp[-1].expr); (yyval.expr)->index=(yyvsp[-3].expr); }
#line 2271 "parser.c"
    break;

  case 73: /* $@4: %empty  */
#line 725 "parser.y"
                    {if(scope_flag==0){curr_scope++;} newDummyScope(curr_scope); scope_flag=0;}
#line 2277 "parser.c"
    break;

  case 74: /* block: LEFT_BRACKET $@4 stmts RIGHT_BRACKET  */
#line 725 "parser.y"
                                                                                                                    { deactivate(curr_scope); curr_scope--; }
#line 2283 "parser.c"
    break;

  case 75: /* @5: %empty  */
#line 729 "parser.y"
                    {
                flagSemicolon=1;    
                int result;
                result=lookup_FuncDef(curr_scope,yylval.string_Val,1,yylineno);
                if(result==1) {yyerror("Exists as library function");}
                else if(result==2){ yyerror("Variable and function have the same name");}
                else if(result==4) {yyerror("Function Redeclaration");}
                else{
                       // expr *arg1 expr *arg2, expr *result,unsigned int label , unsigned int line
                        (yyval.expr)=lvalue_expr(put((yyvsp[0].string_Val),USERF,"FUNC",yylineno,curr_scope)); 
                        (yyval.expr)->sym->address=nextQuad();                       
                        tmpFuncName =  (yyval.expr);
                        functionJump=nextQuad();
                        emit(jump, NULL, NULL, NULL, -1, yylineno);
                        emit(funcstart, (yyval.expr) , NULL,NULL,nextQuad() ,yylineno);
                        push(locals,currScopeOffset());
                        enterScopeSpace();
                        resetFormalArgsOffset();
               }
       }
#line 2308 "parser.c"
    break;

  case 76: /* $@6: %empty  */
#line 748 "parser.y"
                     {scope_flag=1; curr_scope++;}
#line 2314 "parser.c"
    break;

  case 77: /* $@7: %empty  */
#line 748 "parser.y"
                                                                        {function_nested++; enterScopeSpace(); resetFuncLocalsOffset();}
#line 2320 "parser.c"
    break;

  case 78: /* funcdef: FUNCTION ID @5 LEFT_PARENTH $@6 idlist RIGHT_PARENTH $@7 block  */
#line 748 "parser.y"
                                                                                                                                               { function_nested--;
                        (yyval.expr)=tmpFuncName;
                        (yyval.expr)->sym->totallocals=currScopeOffset();
                        exitScopeSpace();
                        exitScopeSpace();
                        restoreCurrScopeOffset(pop(locals));
                        patchList(pop(returnst),nextQuad());
                        emit(funcend,tmpFuncName, NULL, NULL , nextQuad() ,yylineno);
                        printf("next Quad function %d\n",nextQuad());
                        patchList(functionJump, nextQuad());
                }
#line 2336 "parser.c"
    break;

  case 79: /* @8: %empty  */
#line 759 "parser.y"
                 {       
                flagSemicolon=1;    
                snprintf(buf, 50, "_f%d", buf_counter);  
                (yyval.expr)=lvalue_expr(put(buf,USERF,"FUNC",yylineno,curr_scope)); 
                (yyval.expr)->sym->address=nextQuad();                       
                tmpFuncName =  (yyval.expr);
                functionJump=nextQuad();
                emit(jump, NULL, NULL, NULL, -1, yylineno);
                emit(funcstart, (yyval.expr), NULL,NULL ,nextQuad() ,yylineno);
                push(locals,currScopeOffset());
                enterScopeSpace();
                resetFormalArgsOffset();
                buf_counter++;
        }
#line 2355 "parser.c"
    break;

  case 80: /* $@9: %empty  */
#line 772 "parser.y"
                       {scope_flag=1; curr_scope++;}
#line 2361 "parser.c"
    break;

  case 81: /* $@10: %empty  */
#line 772 "parser.y"
                                                                          {function_nested++; enterScopeSpace(); resetFuncLocalsOffset();}
#line 2367 "parser.c"
    break;

  case 82: /* funcdef: FUNCTION @8 LEFT_PARENTH $@9 idlist RIGHT_PARENTH $@10 block  */
#line 772 "parser.y"
                                                                                                                                                  {
                        function_nested--;
                        (yyval.expr)=tmpFuncName;
                        (yyval.expr)->sym->totallocals=currScopeOffset();
                        exitScopeSpace();
                        exitScopeSpace();
                        restoreCurrScopeOffset(pop(locals));
                        patchList(pop(returnst),nextQuad());
                        emit(funcend,tmpFuncName, NULL, NULL , nextQuad() ,yylineno);
                        patchList(functionJump, nextQuad());
                        }
#line 2383 "parser.c"
    break;

  case 83: /* const: NUM  */
#line 786 "parser.y"
           {(yyval.expr)=num_expr(yylval.int_val);  }
#line 2389 "parser.c"
    break;

  case 84: /* const: STRING  */
#line 787 "parser.y"
               {  (yyval.expr)=newExpr_constString(yylval.string_Val);}
#line 2395 "parser.c"
    break;

  case 85: /* const: NIL  */
#line 788 "parser.y"
             {(yyval.expr)=newExpr(nil_e);}
#line 2401 "parser.c"
    break;

  case 86: /* const: TRUE  */
#line 789 "parser.y"
             {
        (yyval.expr)=newExpr_constBool(1);
        // $$->trueList = makeList(nextQuad());
        // $$->falseList = makeList(nextQuad()+1);

       }
#line 2412 "parser.c"
    break;

  case 87: /* const: FALSE  */
#line 795 "parser.y"
              {
        (yyval.expr)=newExpr_constBool(0);
        // $$->trueList = makeList(nextQuad());
        // $$->falseList = makeList(nextQuad()+1);
        }
#line 2422 "parser.c"
    break;

  case 88: /* const: FLOAT  */
#line 800 "parser.y"
              {(yyval.expr)=num_expr(yylval.real_val);}
#line 2428 "parser.c"
    break;

  case 89: /* idlist: ID  */
#line 803 "parser.y"
          {int result= lookup_Formal(curr_scope, yylval.string_Val,5,yylineno);
                if(result==1){
                yyerror("ID exists as library function");
                }else if(result==2){
                yyerror("Formal redeclaration");
                }
        }
#line 2440 "parser.c"
    break;

  case 90: /* idlist: idlist COMMA ID  */
#line 810 "parser.y"
                         {int result= lookup_Formal(curr_scope, yylval.string_Val,5,yylineno);
                if(result==1){
                yyerror("ID exists as library function");
                }else if(result==2){
                yyerror("Formal redeclaration");
                }
        }
#line 2452 "parser.c"
    break;

  case 91: /* idlist: %empty  */
#line 817 "parser.y"
          {}
#line 2458 "parser.c"
    break;

  case 92: /* ifprefix: IF LEFT_PARENTH expr RIGHT_PARENTH  */
#line 820 "parser.y"
                                           {
        flagSemicolon=1;
 if((yyvsp[-1].expr)->type==boolexpr_e)
        {    
        backPatch((yyvsp[-1].expr)->trueList,nextQuad());
        backPatch((yyvsp[-1].expr)->falseList,nextQuad()+2);
        emit(assign,newExpr_constBool(1),NULL,(yyvsp[-1].expr),0,yylineno);
        emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
        emit(assign,newExpr_constBool(0),NULL,(yyvsp[-1].expr),0,yylineno);
        }
        emit(
        if_eq, (yyvsp[-1].expr),
        newExpr_constBool(1),
        NULL, nextQuad() + 2, yylineno
        );
        (yyval.int_val) = nextQuad();
        emit(jump, NULL, NULL, NULL, 0, yylineno);

}
#line 2482 "parser.c"
    break;

  case 93: /* elseprefix: ELSE  */
#line 840 "parser.y"
                 {
        (yyval.int_val)=nextQuad();
        emit(jump, NULL, NULL, NULL, 0, yylineno);

}
#line 2492 "parser.c"
    break;

  case 94: /* ifstmt: ifprefix stmt  */
#line 846 "parser.y"
                       { patchLabel((yyvsp[-1].int_val),nextQuad()); }
#line 2498 "parser.c"
    break;

  case 95: /* ifstmt: ifprefix stmt elseprefix stmt  */
#line 847 "parser.y"
                                        {
                patchLabel((yyvsp[-3].int_val),(yyvsp[-1].int_val)+1);
                patchLabel((yyvsp[-1].int_val),nextQuad());
        }
#line 2507 "parser.c"
    break;

  case 96: /* whilestart: WHILE  */
#line 854 "parser.y"
                 { (yyval.int_val)=nextQuad(); while_flag++; }
#line 2513 "parser.c"
    break;

  case 97: /* whilecond: LEFT_PARENTH expr RIGHT_PARENTH  */
#line 857 "parser.y"
                                          {
        if((yyvsp[-1].expr)->type==boolexpr_e)
        {    
                backPatch((yyvsp[-1].expr)->trueList,nextQuad());
                backPatch((yyvsp[-1].expr)->falseList,nextQuad()+2);
                emit(assign,newExpr_constBool(1),NULL,(yyvsp[-1].expr),0,yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
                emit(assign,newExpr_constBool(0),NULL,(yyvsp[-1].expr),0,yylineno);
        }
        emit(if_eq, (yyvsp[-1].expr), newExpr_constBool(1), NULL, nextQuad()+2, yylineno);
        (yyval.int_val)=nextQuad();
        emit(jump,NULL,NULL,NULL,0, yylineno);
}
#line 2531 "parser.c"
    break;

  case 98: /* while: whilestart whilecond stmt  */
#line 873 "parser.y"
                                {
        emit(jump,NULL,NULL,NULL,(yyvsp[-2].int_val), yylineno);
        patchLabel((yyvsp[-1].int_val), nextQuad());
        patchList(pop(breakst), nextQuad());
        patchList(pop(contst), (yyvsp[-2].int_val));  
        while_flag--;

}
#line 2544 "parser.c"
    break;

  case 99: /* $@11: %empty  */
#line 885 "parser.y"
              {for_flag++;}
#line 2550 "parser.c"
    break;

  case 100: /* $@12: %empty  */
#line 885 "parser.y"
                                                          {namespace_flag=0;}
#line 2556 "parser.c"
    break;

  case 101: /* $@13: %empty  */
#line 885 "parser.y"
                                                                                               {namespace_flag=0;}
#line 2562 "parser.c"
    break;

  case 102: /* forprefix: FOR $@11 LEFT_PARENTH elist SEMICOLON $@12 M expr SEMICOLON $@13  */
#line 885 "parser.y"
                                                                                                                   {
        if((yyvsp[-2].expr)->type==boolexpr_e)
        {    
                backPatch((yyvsp[-2].expr)->trueList,nextQuad());
                backPatch((yyvsp[-2].expr)->falseList,nextQuad()+2);
                emit(assign,newExpr_constBool(1),NULL,(yyvsp[-2].expr),0,yylineno);
                emit(jump,NULL,NULL,NULL,nextQuad()+2,yylineno);
                emit(assign,newExpr_constBool(0),NULL,(yyvsp[-2].expr),0,yylineno);
        }
        (yyval.for_p) = malloc(sizeof(for_p));
        (yyval.for_p)->test=(yyvsp[-3].int_val);
        (yyval.for_p)->enter=nextQuad();
        emit(if_eq, (yyvsp[-2].expr), newExpr_constBool(1),NULL,0,yylineno);
}
#line 2581 "parser.c"
    break;

  case 103: /* for: forprefix N elist RIGHT_PARENTH N stmt N  */
#line 900 "parser.y"
                                             {
        patchLabel((yyvsp[-6].for_p)->enter, (yyvsp[-2].int_val)+1); 
        patchLabel((yyvsp[-5].int_val), nextQuad()); 
        patchLabel((yyvsp[-2].int_val), (yyvsp[-6].for_p)->test); 
        patchLabel((yyvsp[0].int_val), (yyvsp[-5].int_val)+1);

       patchList(pop(breakst), nextQuad());
       patchList(pop(contst), (yyvsp[-5].int_val)+1);
        for_flag--;
}
#line 2596 "parser.c"
    break;

  case 104: /* returnstmt: RETURN expr SEMICOLON  */
#line 915 "parser.y"
                                  {if(function_nested==0){yyerror("Return out of function");}
              else{ emit(ret,NULL,NULL,(yyvsp[-1].expr) ,nextQuad() ,yylineno);}
                printf("EIMAI RETURN STMT ME RESULT TYPE %d\n\n",(yyvsp[-1].expr)->type);
              }
#line 2605 "parser.c"
    break;

  case 105: /* returnstmt: RETURN SEMICOLON  */
#line 919 "parser.y"
                              {if(function_nested==0){yyerror("Return out of function");}
              else{emit(ret,NULL,NULL, NULL ,nextQuad() ,yylineno);}}
#line 2612 "parser.c"
    break;


#line 2616 "parser.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 923 "parser.y"



int yyerror(char* yaccProvideMessage){
    fprintf(stderr, "\x1B[31m" "ERROR, %s at line: %d\n" "\x1B[0m",yaccProvideMessage, yylineno);
}

int main(int argc,char** argv){
    init();
    FILE *f=fopen("output.txt","w");
    locals=newStack(NEW_SIZE);
    formals=newStack(NEW_SIZE);
    breakst=newStack(NEW_SIZE);
    contst=newStack(NEW_SIZE);
    returnst=newStack(NEW_SIZE);
    yyin = stdin; 
    yyparse();
    /*print_output();*/
   // print_quads(f);
    generate_mapping();
    writeBinary();
  
    FILE *b=fopen("binFile.abc","rb");
    readAll(b);
    avm_initialize();
    while(executionFinished==0){
        execute_cycle();
    }

    fclose(f);
    fclose(b);

}
