%{
#include <iostream>

#include <expression.hpp>

#define YYSTYPE Expression*

extern int yylex();
extern char* yytext;
int yyerror(const char*);
%}






extern int yylex();
extern char* yytext;
int yyerror(const char*);
Expression* parser_result{nullptr};








%token TOKEN_EOF
%token TOKEN_TIME
%token TOKEN_NOTE
%token TOKEN_ALTERATION
%token TOKEN_DURATION
%token TOKEN_SECTION
%token TOKEN_REPEAT
%token TOKEN_DIGIT
%token TOKEN_COMMA
%token TOKEN_SEMICOLON
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_LBRACKET
%token TOKEN_RBRACKET
%token TOKEN_PIPE
%token TOKEN_SLASH
%token TOKEN_LBRACE
%token TOKEN_RBRACE
%token TOKEN_IDENTIFIER
%token TOKEN_BAR_LINE
%token TOKEN_REST
%token TOKEN_POINT
%token TOKEN_UNKNOWN
%token TOKEN_DOTTED

%%
program : statement;

statement : declarations statement 
          | compasses statement
          | declarations
          | compasses
          ;
               
declarations :  TOKEN_TIME TOKEN_DIGIT TOKEN_SLASH TOKEN_DIGIT
             |  TOKEN_SECTION TOKEN_IDENTIFIER expression
             |  TOKEN_REPEAT TOKEN_DIGIT expression 
             ;

expression : TOKEN_LBRACE compasses TOKEN_RBRACE
           ;

compasses : compasses TOKEN_COMMA note
          | compasses TOKEN_BAR_LINE note
          | note 
          ;

note : TOKEN_NOTE TOKEN_DURATION 
     | TOKEN_NOTE TOKEN_DURATION TOKEN_DOTTED
     | TOKEN_REST TOKEN_DURATION
     | TOKEN_NOTE TOKEN_ALTERATION TOKEN_DURATION
     | TOKEN_NOTE TOKEN_ALTERATION TOKEN_DURATION TOKEN_DOTTED
     ;
%%

int yyerror(const char* s)
{
    std::cerr << "Parse error:"<< s << std::endl;
    return 1;
}