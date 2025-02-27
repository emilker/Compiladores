#pragma once

// Definir el enum antes de usarlo
typedef enum
{
    TOKEN_EOF = 0,
    TOKEN_PLAY_SOUND = 258,
    TOKEN_PLAY_CHORD = 259,
    TOKEN_NOTE = 260,
    TOKEN_DURATION = 261,
    TOKEN_COMMA = 262,
    TOKEN_LPAREN = 263,   // (
    TOKEN_RPAREN = 264,   // )
    TOKEN_LBRACKET = 265, // [
    TOKEN_RBRACKET = 266, // ]
    TOKEN_IDENTIFIER = 267,
    TOKEN_UNKNOWN = 268
}token_t;

inline const char* to_str(token_t t)
{
    switch (t)
    {
        case TOKEN_PLAY_SOUND: return "PLAY_SOUND";
        case TOKEN_PLAY_CHORD: return "PLAY_CHORD";
        case TOKEN_NOTE: return "NOTE";
        case TOKEN_DURATION: return "DURATION";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        default: return "UNKNOWN";
    }
}