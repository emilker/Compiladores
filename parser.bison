%{
#include <iostream>

extern int yylex();
extern char* yytext;
int yyerror(const char*);
%}

%token TOKEN_EOF
%token TOKEN_KEY
%token TOKEN_MAJOR
%token TOKEN_CLEF
%token TOKEN_TIME
%token TOKEN_NOTE
%token TOKEN_DURATION
%token TOKEN_SECTION
%token TOKEN_REPEAT
%token TOKEN_DIGIT
%token TOKEN_MINOR
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

%%
program : statement;

statement : assignment statement 
          | section statement 
          | compasses statement
          | assignment
          | section
          | compasses
          ;
               
assignment :  time 
           |  key
           |  clef
           ;
           
time : TOKEN_TIME TOKEN_DIGIT TOKEN_SLASH TOKEN_DIGIT
     ;

key  : TOKEN_KEY TOKEN_NOTE TOKEN_MAJOR
     | TOKEN_KEY TOKEN_NOTE TOKEN_MINOR
     ;

clef : TOKEN_CLEF TOKEN_NOTE
     ;           

section : TOKEN_SECTION TOKEN_IDENTIFIER expression
        | TOKEN_REPEAT TOKEN_DIGIT expression 
        ;

expression : TOKEN_LBRACE compasses TOKEN_RBRACE
            ;

compasses : compasses TOKEN_COMMA note
          | compasses TOKEN_BAR_LINE note
          | note 
          ;

note : TOKEN_NOTE TOKEN_DURATION 
     | TOKEN_NOTE TOKEN_DURATION TOKEN_POINT
     | TOKEN_REST TOKEN_DURATION
     ;
%%

int yyerror(const char* s)
{
    std::cerr << "Parse error:"<< s << std::endl;
    return 1;
}