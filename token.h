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

#ifndef YY_YY_TOKEN_H_INCLUDED
# define YY_YY_TOKEN_H_INCLUDED
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
    TOKEN_EOF = 258,               /* TOKEN_EOF  */
    TOKEN_TIME = 259,              /* TOKEN_TIME  */
    TOKEN_TEMPO = 260,             /* TOKEN_TEMPO  */
    TOKEN_EQUALS = 261,            /* TOKEN_EQUALS  */
    TOKEN_NOTE = 262,              /* TOKEN_NOTE  */
    TOKEN_ALTERATION = 263,        /* TOKEN_ALTERATION  */
    TOKEN_DURATION = 264,          /* TOKEN_DURATION  */
    TOKEN_SECTION = 265,           /* TOKEN_SECTION  */
    TOKEN_REPEAT = 266,            /* TOKEN_REPEAT  */
    TOKEN_DIGIT = 267,             /* TOKEN_DIGIT  */
    TOKEN_COMMA = 268,             /* TOKEN_COMMA  */
    TOKEN_SEMICOLON = 269,         /* TOKEN_SEMICOLON  */
    TOKEN_LPAREN = 270,            /* TOKEN_LPAREN  */
    TOKEN_RPAREN = 271,            /* TOKEN_RPAREN  */
    TOKEN_LBRACKET = 272,          /* TOKEN_LBRACKET  */
    TOKEN_RBRACKET = 273,          /* TOKEN_RBRACKET  */
    TOKEN_PIPE = 274,              /* TOKEN_PIPE  */
    TOKEN_SLASH = 275,             /* TOKEN_SLASH  */
    TOKEN_LBRACE = 276,            /* TOKEN_LBRACE  */
    TOKEN_RBRACE = 277,            /* TOKEN_RBRACE  */
    TOKEN_IDENTIFIER = 278,        /* TOKEN_IDENTIFIER  */
    TOKEN_BAR_LINE = 279,          /* TOKEN_BAR_LINE  */
    TOKEN_REST = 280,              /* TOKEN_REST  */
    TOKEN_POINT = 281,             /* TOKEN_POINT  */
    TOKEN_UNKNOWN = 282,           /* TOKEN_UNKNOWN  */
    TOKEN_DOTTED = 283             /* TOKEN_DOTTED  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TOKEN_H_INCLUDED  */
