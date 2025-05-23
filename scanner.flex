%{
#include "token.h"
%}

/* Definiciones de expresiones regulares */
SPACE        [ \t\n\r]
DIGIT        [0-9]+
LETTER       [A-Za-z]
NOTE         [A-G][1-8]?
ALTERATION   [#b] 
DURATION     [qhesw]
TIME         "time"
SECTION      "section"
REPEAT       "repeat"
TEMPO        "tempo"
EQUALS       "="
BAR_LINE     "|"
REST         "-"
DOTTED       "."
COMMA        ","
SEMICOLON    ";"
LPAREN       "("
RPAREN       ")"
LBRACKET     "["
RBRACKET     "]"
PIPE         "\\"
SLASH        "/"
LBRACE       "{"
RBRACE       "}" 

%%
{SPACE}      { /* ignorar espacios */ }
{TIME}       { return TOKEN_TIME; }
{TEMPO}      { return TOKEN_TEMPO;}
{EQUALS}     { return TOKEN_EQUALS;}
{NOTE}       { return TOKEN_NOTE; }
{ALTERATION} { return TOKEN_ALTERATION; }
{DOTTED}     { return TOKEN_DOTTED; }
{DURATION}   { return TOKEN_DURATION; }
{SECTION}    { return TOKEN_SECTION; }
{REPEAT}     { return TOKEN_REPEAT; }
{COMMA}      { return TOKEN_COMMA; }
{SEMICOLON}  { return TOKEN_SEMICOLON; }
{LPAREN}     { return TOKEN_LPAREN; }
{RPAREN}     { return TOKEN_RPAREN; }
{LBRACKET}   { return TOKEN_LBRACKET; }
{RBRACKET}   { return TOKEN_RBRACKET; }
{PIPE}       { return TOKEN_PIPE; }
{SLASH}      { return TOKEN_SLASH; }
{LBRACE}     { return TOKEN_LBRACE; }
{RBRACE}     { return TOKEN_RBRACE; }
{BAR_LINE}   { return TOKEN_BAR_LINE; }
{REST}       { return TOKEN_REST; }
{DIGIT}      { return TOKEN_DIGIT; }


{LETTER}({LETTER}|{DIGIT}|_)* { return TOKEN_IDENTIFIER; }

.            { return TOKEN_UNKNOWN; }
%%

int yywrap() { return 1; }