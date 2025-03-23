%{
#include "token.h"
%}

SPACE        [ \t\n\r]
DIGIT        [1-8]
LETTER       [A-Za-z]
NOTE         [A-G][#bn]?[1-8]?
DURATION     [qhesw]
TIME         "time"
SECTION      "section"
REPEAT       "repeat"
BAR_LINE     "|"
REST         "-"
DOTTED       "."
SHARP        "#"
COMMA        ","
SEMICOLON     ";"
LPAREN       "\("
RPAREN       "\)"
LBRACKET     "\["
RBRACKET     "\]"
PIPE         "\\"
SLASH        "/"
LBRACE       "\{"
RBRACE       "\}"
POINT        "\." 

%%
{SPACE}      {}
{DIGIT}      { return TOKEN_DIGIT; }
{TIME}       { return TOKEN_TIME; }
{NOTE}       { return TOKEN_NOTE; }
{SHARP}      { return TOKEN_SHARP; }
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
{POINT}      { return TOKEN_POINT; }

{LETTER}({LETTER}|{DIGIT}|_)* { return TOKEN_IDENTIFIER; }

.            { return TOKEN_UNKNOWN; }

%%

int yywrap() { return 1; }