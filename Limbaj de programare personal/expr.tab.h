/* A Bison parser, made by GNU Bison 3.8.2.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_EXPR_TAB_H_INCLUDED
# define YY_YY_EXPR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 54 "expr.y"

#include <vector>
#include <string>
#include "globals.h"

/* Structura pentru un parametru de functie */
struct Param 
{
    std::string type; // tipul parametrului
    std::string name; // numele parametrului
};

#line 62 "expr.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT_LITERAL = 258,             /* INT_LITERAL  */
    BOOL_LITERAL = 259,            /* BOOL_LITERAL  */
    FLOAT_LITERAL = 260,           /* FLOAT_LITERAL  */
    STRING_LITERAL = 261,          /* STRING_LITERAL  */
    ID = 262,                      /* ID  */
    INT_TYPE = 263,                /* INT_TYPE  */
    FLOAT_TYPE = 264,              /* FLOAT_TYPE  */
    STRING_TYPE = 265,             /* STRING_TYPE  */
    BOOL_TYPE = 266,               /* BOOL_TYPE  */
    CLASS = 267,                   /* CLASS  */
    NEW = 268,                     /* NEW  */
    DOT = 269,                     /* DOT  */
    IF = 270,                      /* IF  */
    ELSE = 271,                    /* ELSE  */
    WHILE = 272,                   /* WHILE  */
    RETURN = 273,                  /* RETURN  */
    MAIN_BLOCK = 274,              /* MAIN_BLOCK  */
    PRINT = 275,                   /* PRINT  */
    LBRACE = 276,                  /* LBRACE  */
    RBRACE = 277,                  /* RBRACE  */
    SEMICOLON = 278,               /* SEMICOLON  */
    ASSIGN = 279,                  /* ASSIGN  */
    LPAREN = 280,                  /* LPAREN  */
    RPAREN = 281,                  /* RPAREN  */
    COMMA = 282,                   /* COMMA  */
    AND = 283,                     /* AND  */
    OR = 284,                      /* OR  */
    NOT = 285,                     /* NOT  */
    EQ = 286,                      /* EQ  */
    NEQ = 287,                     /* NEQ  */
    LT = 288,                      /* LT  */
    GT = 289,                      /* GT  */
    LEQ = 290,                     /* LEQ  */
    GEQ = 291,                     /* GEQ  */
    PLUS = 292,                    /* PLUS  */
    MINUS = 293,                   /* MINUS  */
    MUL = 294,                     /* MUL  */
    DIV = 295                      /* DIV  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 71 "expr.y"

    int int_val; // pentru literali int
    float float_val; // pentru literali float
    char* str; // pentru ID si stringuri
    ASTNode* ast; // pentru expresii/instructiuni
    std::vector<Param>* paramvec; // lista parametri
    std::vector<ASTNode*>* astlist; // lista de instructiuni

#line 128 "expr.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_EXPR_TAB_H_INCLUDED  */
