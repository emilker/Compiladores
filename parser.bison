%{
#include <iostream>
#include <statement.hpp>
#include <string> 

#include "symbol_table.hpp"
SymbolTable symbolTable;  

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
          | section statement                                                           { $$ = new StatementSequence($1, $2); }
          | time statement                                                              { $$ = new StatementSequence($1, $2); }
          | idReference statement                                                       { $$ = new StatementSequence($1, $2); }
          | section                                                                     { $$ = $1; }
          | idReference                                                                 { $$ = $1; }
          | time                                                                        { $$ = $1; }
          | compasses                                                                   { $$ = $1; }
          ;          

time : TOKEN_TIME digit TOKEN_SLASH digit TOKEN_LBRACE body TOKEN_RBRACE                { $$ = new Time($2, $4, $6); }
     ;

section : TOKEN_SECTION id TOKEN_LBRACE compasses TOKEN_RBRACE                          { 
                                                                                          try 
                                                                                          {
                                                                                               $$ = new SectionDeclaration($2, $4, symbolTable); 
                                                                                          } catch (const std::exception& e) 
                                                                                          {
                                                                                               yyerror(e.what());
                                                                                               YYERROR;
                                                                                          }
                                                                                        }
        | TOKEN_REPEAT digit TOKEN_LBRACE compasses TOKEN_RBRACE                        {  $$ = new RepeatDeclaration($2, $4); }                                                         
        ; 

digit : TOKEN_DIGIT                                                                     { $$ = new Value(yytext); }
      ;
      
id : TOKEN_IDENTIFIER                                                                   { $$ = new Value(yytext); }                                  
   ;

idReference : TOKEN_IDENTIFIER                                                          {   
                                                                                          auto ID = new SectionReference(yytext,symbolTable);
                                                                                          auto ref = ID->semantic_analysis();
                                                                                          if (!ref) 
                                                                                          {
                                                                                               yyerror(yytext);
                                                                                               YYERROR;
                                                                                          }
                                                                                          $$ = ref;
                                                                                        }                                  
            ;

compasses : compasses TOKEN_BAR_LINE notes                                              { $$ = new CompassesBarLine($1, $3); }
          |  notes                                                                      { $$ = $1; }
          ;

notes: notes TOKEN_COMMA note                                                           { $$ = new CompassesComma($1, $3); }
     | note                                                                             { $$ = $1; } 
     ;   

note : notename duration                                                                { $$ = new Note($1, nullptr, $2, nullptr); }
     | notename duration dotted                                                         { $$ = new Note($1, nullptr, $2, $3); }   
     | notename alteration duration                                                     { $$ = new Note($1, $2, $3, nullptr); }  
     | notename alteration duration dotted                                              { $$ = new Note($1, $2, $3, $4); }  
     ;

notename  : TOKEN_NOTE                                                                  { $$ = new Value(yytext);}
          | TOKEN_REST                                                                  { $$ = new Value(yytext);}
          ;

duration : TOKEN_DURATION                                                               { $$ = new Value(yytext);}                    
         ;

alteration : TOKEN_ALTERATION                                                           { $$ = new Value(yytext);}                    
           ;

dotted : TOKEN_DOTTED                                                                   { $$ = new Value(yytext);}                    
       ;
        
body : statement                                                                        { $$ = $1; }
     ;
%%

int yyerror(const char* s)
{
    std::cerr << "Parse error:"<< s << std::endl;
    return 1;
}