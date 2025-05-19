#include <iostream>
#include <fstream>
#include <cstdlib>

#include "symbol_table.hpp"
#include "audiogenerator.hpp"
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
        SymbolTable symbolTable;  
        std::cout << "Parse successful!\n" << std::endl;
       
        if (parser_result->resolve_name(symbolTable))
        {
            std::cout << "Name resolution successful!\n" << std::endl;
        }
        else
        {
            std::cout << "Name resolution failed!\n" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        if (parser_result->semantic_analysis())
        {
            std::cout << "Semantic analysis successful!\n" << std::endl;
        }
        else
        {
            std::cerr << "Semantic analysis failed!\n" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        AudioGenerator audio_gen;
        audio_gen.start_recording("Melodia.wav");
        parser_result->generate_sound(audio_gen);
        audio_gen.stop_recording();
        
        parser_result->destroy();
    }
    else
    {
        std::cout << "Parse failed!\n" << std::endl;
    }

    return 0;
}
