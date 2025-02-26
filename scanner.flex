%{
#include "token.h"
%}

SPACE        [ \t\n\r]
DIGIT        [1-8]
LETTER       [A-Za-z]
NOTE         [CDEFGAB][#bn]?[1-8]
DURATION     (Negra|Blanca|Corchea|Semicorchea)(R)?
PLAY_SOUND   "play_sound"
PLAY_CHORD   "play_chord"
COMMA        ","
LPAREN       "\("
RPAREN       "\)"
LBRACKET     "\["
RBRACKET     "\]"

%%
{SPACE}      {}
{PLAY_SOUND} { return TOKEN_PLAY_SOUND; }
{PLAY_CHORD} { return TOKEN_PLAY_CHORD; }
{NOTE}       { return TOKEN_NOTE; }
{DURATION}   { return TOKEN_DURATION; }
{COMMA}      { return TOKEN_COMMA; }
{LPAREN}     { return TOKEN_LPAREN; }
{RPAREN}     { return TOKEN_RPAREN; }
{LBRACKET}   { return TOKEN_LBRACKET; }
{RBRACKET}   { return TOKEN_RBRACKET; }

{LETTER}({LETTER}|{DIGIT}|_)* { return TOKEN_IDENTIFIER; }
%%

int yywrap() { return 1; }