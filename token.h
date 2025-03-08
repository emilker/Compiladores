#pragma once

// Definir el enum antes de usarlo
typedef enum
{
    TOKEN_EOF = 0,
    TOKEN_KEY = 257,
    TOKEN_MAJOR = 258,
    TOKEN_CLEF = 259,
    TOKEN_TIME = 260,
    TOKEN_NOTE = 261,
    TOKEN_DURATION = 262,
    TOKEN_SECTION = 263,
    TOKEN_REPEAT = 264,
    TOKEN_DIGIT = 265,
    TOKEN_MINOR = 266,
    TOKEN_COMMA = 267,
    TOKEN_SEMICOLON = 268,
    TOKEN_LPAREN = 269,   // (
    TOKEN_RPAREN = 270,   // )
    TOKEN_LBRACKET = 271, // [
    TOKEN_RBRACKET = 272, // ]
    TOKEN_PIPE = 273,     // \}
    TOKEN_SLASH = 274,    // /
    TOKEN_LBRACE = 275,   // {
    TOKEN_RBRACE = 276,   // }
    TOKEN_IDENTIFIER = 277,
    TOKEN_BAR_LINE = 278, // |
    TOKEN_REST = 279,
    TOKEN_UNKNOWN = 280, 
}token_t;

inline const char* to_str(token_t t)
{
    switch (t)
    {
        case TOKEN_KEY: return "KEY";
        case TOKEN_MAJOR: return "MAJOR";
        case TOKEN_CLEF: return "CLEF";
        case TOKEN_TIME: return "TIME";
        case TOKEN_NOTE: return "NOTE";
        case TOKEN_DURATION: return "DURATION";
        case TOKEN_SECTION: return "SECTION";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_PIPE: return "PIPE";
        case TOKEN_BAR_LINE: return "BAR_LINE";
        case TOKEN_REST: return "REST";
        case TOKEN_SLASH: return "SLASH";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_REPEAT: return "REPEAT";
        case TOKEN_DIGIT: return "DIGIT";
        case TOKEN_MINOR: return "MINOR";
        default: return "UNKNOWN";
    }
}