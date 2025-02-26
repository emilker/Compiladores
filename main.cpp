#include <iostream>
#include <fstream>
#include <cstdlib>
#include "token.h"

extern FILE* yyin;
extern char* yytext;

int yylex();
const char* to_str(token_t t);

void usage(const char* program_name) {
    std::cerr << "Usage: " << program_name << " input_file\n";
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        usage(argv[0]);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        std::cerr << "Could not open " << argv[1] << std::endl;
        exit(EXIT_FAILURE);
    }

    while (true) {
        token_t t = static_cast<token_t>(yylex());
        if (t == TOKEN_EOF) {
            std::cout << "End of file\n";
            break;
        }
        std::cout << "Token: " << to_str(t) << " value: " << yytext << std::endl;
    }

    fclose(yyin);
    return 0;
}
