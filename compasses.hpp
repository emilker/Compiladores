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
    CompassesComma() noexcept;

    void destroy() noexcept override;
private:
    std::string comma;
};

class CompassesBarLine : public Compasses 
{   
public:
    CompassesBarLine() noexcept;

    void destroy() noexcept override;
private:
    std::string bar_line;
};

