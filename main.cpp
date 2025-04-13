#include <iostream>
#include <fstream>
#include <cstdlib>

#include <statement.hpp>

extern FILE* yyin;
extern int yyparse();
extern Statement* parser_result;

void usage(const char* program_name) 
{
    std::cerr << "Usage: " << program_name << " input_file\n";
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        usage(argv[0]);
    }

    yyin = fopen(argv[1], "r");

    if (!yyin) 
    {
        std::cerr << "Could not open " << argv[1] << std::endl;
        exit(EXIT_FAILURE);
    }

    int result = yyparse();

    if (result == 0)
    {
        std::cout << "Parse successful!\n" << std::endl;
        parser_result->print();
        parser_result->pulse();
        //parser_result->destroy();
    }
    else
    {
        std::cout << "Parse failed!\n" << std::endl;
    }

    return 0;
}
