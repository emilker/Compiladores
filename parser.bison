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
program : statement                                                                     { parser_result = $1; }
        ;                                              
statement : compasses statement                                                         { $$ = new StatementSequence($1, $2); }
          | secction statement 
          | secction
          | compasses                                                                   { $$ = $1; }
          ;          
          

secction :  TOKEN_SECTION id TOKEN_LBRACE compasses TOKEN_RBRACE                        { $$ = new SectionDeclaration($2, $4); }
         |  TOKEN_REPEAT digit TOKEN_LBRACE compasses TOKEN_RBRACE                      { $$ = new SectionDeclaration($2, $4); }
         ; 

digit : TOKEN_DIGIT                                                                     { $$ = new Value(yytext); }
      ;
      
id : TOKEN_IDENTIFIER                                                                   { $$ = new Value(yytext); }                                  
         ;

compasses : compasses TOKEN_COMMA note                                                  { $$ = new CompassesComma($1, $3); }                           
          | compasses TOKEN_BAR_LINE note                                               { $$ = new CompassesBarLine($1, $3); }
          | note                                                                        { $$ = $1; }  
          ;


note : notename duration                                                                  { $$ = new Note($1, nullptr, $2, nullptr); }
     | notename duration dotted                                                           { $$ = new Note($1, nullptr, $2, $3); }   
     | notename alteration duration                                                       { $$ = new Note($1, $2, $3, nullptr); }  
     | notename alteration duration dotted                                                { $$ = new Note($1, $2, $3, $4); }  
     ;

notename  : TOKEN_NOTE                                                                    { $$ = new Value(yytext);}
          | TOKEN_REST                                                                    { $$ = new Value(yytext);}
          ;

duration : TOKEN_DURATION                                                                 { $$ = new Value(yytext);}                    
          ;

alteration :TOKEN_ALTERATION                                                              { $$ = new Value(yytext);}                    
          ;

dotted : TOKEN_DOTTED                                                                     { $$ = new Value(yytext);}                    
          ;

time : TOKEN_TIME TOKEN_DIGIT TOKEN_SLASH TOKEN_DIGIT                                     { $$ = new Value(std::make_pair($2,$4));}
     ;

%%

int yyerror(const char* s)
{
    std::cerr << "Parse error:"<< s << std::endl;
    return 1;
}