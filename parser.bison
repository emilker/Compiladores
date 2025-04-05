%{
#include <iostream>
#include <statement.hpp>
#include <string> 

#define YYSTYPE Statement*

extern int yylex();
extern char* yytext;
int yyerror(const char*);

Statement* parser_result{nullptr};

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
program : statement                                                   { parser_result = $1; }
        ;                                              
statement : compasses statement                                       { $$ = new StatementSequence($1, $2); }
          | compasses                                                 { $$ = $1; }
          ;

compasses : compasses TOKEN_COMMA note                                { $$ = new CompassesComma($1, $3); }                           
          | compasses TOKEN_BAR_LINE note                             { $$ = new CompassesBarLine($1, $3); }
          | note                                                      { $$ = $1; }  
          ;


note : TOKEN_NOTE TOKEN_DURATION                                      { $$ = new SimpleNote("hola", "jesus"); }
     | TOKEN_NOTE TOKEN_DURATION TOKEN_DOTTED                         { $$ = new DottedNote(std::string(yytext), std::string(yytext), std::string(yytext)); } 
     | TOKEN_REST TOKEN_DURATION                                      { $$ = new SimpleNote(std::string(yytext), std::string(yytext)); }  
     | TOKEN_NOTE TOKEN_ALTERATION TOKEN_DURATION                     { $$ = new AlteredNote(std::string(yytext), std::string(yytext), std::string(yytext)); }  
     | TOKEN_NOTE TOKEN_ALTERATION TOKEN_DURATION TOKEN_DOTTED        { $$ = new AlteredDottedNote(std::string(yytext), std::string(yytext), std::string(yytext), std::string(yytext)); }  
     ;
%%

int yyerror(const char* s)
{
    std::cerr << "Parse error:"<< s << std::endl;
    return 1;
}