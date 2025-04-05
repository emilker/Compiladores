#pragma once

#include "ast_node_interface.hpp"

class Statement : public ASTNodeInterface
{
    //Emty
};

class TimeDeclaration : public Statement
{
public:
    TimeDeclaration(int p, int f, const Body& _body) noexcept;

private:
    int pulse;  //Numerador 
    int figure; //Denominador
    Body body;  //Cuerpo del statement
};