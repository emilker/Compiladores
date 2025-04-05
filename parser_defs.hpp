#pragma once

#include <string>
#include "ast_node_interface.hpp"  // Incluir la definición de ASTNodeInterface

union YYSTYPE {
    ASTNodeInterface* node;
    std::string* str;
    int num;
};


