%{
#include "token.h"
%}

SPACE        [ \t\n\r]
DIGIT        [1-8]
LETTER       [A-Za-z]
NOTE         [CDEFGAB][#bn]?[1-8]?
DURATION     [-]?[qhes]
TIME         "time"
KEY          "key"
MAJOR        "major"
MINOR        "minor"
CLEF         "clef"
SECTION      "section"
REPEAT       "repeat"
BAR_LINE     "|"
REST         "-"
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

%%
{SPACE}      {}
{DIGIT}      { return TOKEN_DIGIT; }
{TIME}       { return TOKEN_TIME; }
{NOTE}       { return TOKEN_NOTE; }
{DURATION}   { return TOKEN_DURATION; }
{KEY}        { return TOKEN_KEY; }
{MAJOR}      { return TOKEN_MAJOR; }
{MINOR}      { return TOKEN_MINOR; }
{CLEF}       { return TOKEN_CLEF; }
{SECTION}    { return TOKEN_SECTION; }
{REPEAT}     { return TOKEN_REPEAT; }
{COMMA}      { return TOKEN_COMMA; }
{SEMICOLON}  { return TOKEN_SEMICOLON; }
{LPAREN}     { return TOKEN_LPAREN; }
{RPAREN}     { return TOKEN_RPAREN; }
{LBRACKET}   { return TOKEN_LBRACKET; }
{RBRACKET}   { return TOKEN_RBRACKET; }
{PIPE}       { return TOKEN_PIPE; }
{LBRACE}     { return TOKEN_LBRACE; }
{RBRACE}     { return TOKEN_RBRACE; }
{BAR_LINE}   { return TOKEN_BAR_LINE; }
{REST}       { return TOKEN_REST; }

{LETTER}({LETTER}|{DIGIT}|_)* { return TOKEN_IDENTIFIER; }

.            { return TOKEN_UNKNOWN; }

%%

int yywrap() { return 1; }