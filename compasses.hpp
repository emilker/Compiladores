#pragma once

#include <string>
#include <string_view>

#include <ast_node_interface.hpp>

class Compasses : public ASTNodeInterface
{
public:
    Compasses() noexcept;

private:

};

class CompassesComma : public Compasses 
{       
public:
    CompassesComma(Compasses*, Compasses*) noexcept;

    void destroy() noexcept override;
private:
    Compasses* left_Compasses;
    Compasses* right_Compasses;
};

class CompassesBarLine : public Compasses 
{   
public:
    CompassesBarLine(Compasses*,Compasses) noexcept;

    void destroy() noexcept override;
private:
    Compasses* left_Compasses;
    Compasses* right_Compasses;  
};

