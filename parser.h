/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    WHILE = 260,                   /* WHILE  */
    FOR = 261,                     /* FOR  */
    FUNCTION = 262,                /* FUNCTION  */
    RETURN = 263,                  /* RETURN  */
    BREAK = 264,                   /* BREAK  */
    CONTINUE = 265,                /* CONTINUE  */
    AND = 266,                     /* AND  */
    NOT = 267,                     /* NOT  */
    OR = 268,                      /* OR  */
    LOCAL = 269,                   /* LOCAL  */
    TRUE = 270,                    /* TRUE  */
    FALSE = 271,                   /* FALSE  */
    NIL = 272,                     /* NIL  */
    EQUAL = 273,                   /* EQUAL  */
    PLUS = 274,                    /* PLUS  */
    MINUS = 275,                   /* MINUS  */
    MULTIPLY = 276,                /* MULTIPLY  */
    SLASH_F = 277,                 /* SLASH_F  */
    PERCENT = 278,                 /* PERCENT  */
    EQUAL_TWO = 279,               /* EQUAL_TWO  */
    NOT_EQUAL = 280,               /* NOT_EQUAL  */
    PLUS_TWO = 281,                /* PLUS_TWO  */
    MINUS_TWO = 282,               /* MINUS_TWO  */
    GREATER = 283,                 /* GREATER  */
    LESS = 284,                    /* LESS  */
    B_EQUAL = 285,                 /* B_EQUAL  */
    L_EQUAL = 286,                 /* L_EQUAL  */
    NUM = 287,                     /* NUM  */
    FLOAT = 288,                   /* FLOAT  */
    STRING = 289,                  /* STRING  */
    LEFT_BRACKET = 290,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 291,           /* RIGHT_BRACKET  */
    LEFT_SQ_BRACKET = 292,         /* LEFT_SQ_BRACKET  */
    RIGHT_SQ_BRACKET = 293,        /* RIGHT_SQ_BRACKET  */
    LEFT_PARENTH = 294,            /* LEFT_PARENTH  */
    RIGHT_PARENTH = 295,           /* RIGHT_PARENTH  */
    SEMICOLON = 296,               /* SEMICOLON  */
    COMMA = 297,                   /* COMMA  */
    COLON = 298,                   /* COLON  */
    NAMESPACE_ = 299,              /* NAMESPACE_  */
    DOT = 300,                     /* DOT  */
    DOT_TWO = 301,                 /* DOT_TWO  */
    ID = 302                       /* ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define NOT 267
#define OR 268
#define LOCAL 269
#define TRUE 270
#define FALSE 271
#define NIL 272
#define EQUAL 273
#define PLUS 274
#define MINUS 275
#define MULTIPLY 276
#define SLASH_F 277
#define PERCENT 278
#define EQUAL_TWO 279
#define NOT_EQUAL 280
#define PLUS_TWO 281
#define MINUS_TWO 282
#define GREATER 283
#define LESS 284
#define B_EQUAL 285
#define L_EQUAL 286
#define NUM 287
#define FLOAT 288
#define STRING 289
#define LEFT_BRACKET 290
#define RIGHT_BRACKET 291
#define LEFT_SQ_BRACKET 292
#define RIGHT_SQ_BRACKET 293
#define LEFT_PARENTH 294
#define RIGHT_PARENTH 295
#define SEMICOLON 296
#define COMMA 297
#define COLON 298
#define NAMESPACE_ 299
#define DOT 300
#define DOT_TWO 301
#define ID 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "parser.y"
int int_val; 
double real_val; 
char* string_Val; 
unsigned int unint_val;
struct sym_t* sym;
struct expr* expr;
struct stmt_t* stmt;
struct call* call_f;
struct for_p* for_p;

#line 172 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
