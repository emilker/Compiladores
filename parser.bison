%{
#include <iostream>

#include <ast_node_interface.hpp>

#define YYSTYPE ASTNodeInterface*

extern int yylex();
extern char* yytext;
int yyerror(const char*);
ASTNodeInterface* parser_result{nullptr};
%}

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
               
declarations :  TOKEN_TIME TOKEN_DIGIT TOKEN_SLASH TOKEN_DIGIT          { $$ = new TimeDeclaration($2, $4); }
             |  TOKEN_SECTION TOKEN_IDENTIFIER expression               { $$ = new SectionDeclaration($2, $3); }
             |  TOKEN_REPEAT TOKEN_DIGIT expression                     { $$ = new RepeartDeclaration($2, $3); }
             ;

expression : TOKEN_LBRACE compasses TOKEN_RBRACE                        { $$ = $2; }
           | TOKEN_IDENTIFIER                                           { $$ = $1; }
           ;

compasses : compasses TOKEN_COMMA note                                  { $$ = new CompassesComma($1, $3); }
          | compasses TOKEN_BAR_LINE note                               { $$ = new CompassesBarLine($1, $3); }
          | note                                                        { $$ = $1; }
          ;

note : TOKEN_NOTE TOKEN_DURATION                                        { $$ = new SimpleNote($1, $2); }
     | TOKEN_NOTE TOKEN_DURATION TOKEN_DOTTED                           { $$ = new DottedNote($1, $2, $3); }
     | TOKEN_REST TOKEN_DURATION                                        { $$ = new SimpleNote($1, $2); }
     | TOKEN_NOTE TOKEN_ALTERATION TOKEN_DURATION                       { $$ = new SimpleNote($1, $2, $3); }
     | TOKEN_NOTE TOKEN_ALTERATION TOKEN_DURATION TOKEN_DOTTED          { $$ = new SimpleNote($1, $2, $3, $4); }
     ;
%%

int yyerror(const char* s)
{
    std::cerr << "Parse error:"<< s << std::endl;
    return 1;
}