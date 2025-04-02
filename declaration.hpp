#pragma once

#include <string>
#include <string_view>

#include <ast_node_interface.hpp>

class Declaration : public ASTNodeInterface
{
public:
    Declaration() noexcept;

private:

};

class TimeDeclaration : public Declaration
{
public:
    TimeDeclaration(int, int) noexcept;

    void destroy() noexcept override;

private:
    int numerator;
    int denominator;
};

class SectionDeclaration : public Declaration
{
public:
    SectionDeclaration(std::string) noexcept;

    void destroy() noexcept override;

private:
    std::string name;
};

class RepeatDeclaration : public Declaration
{   
public:
    RepeatDeclaration(int) noexcept;

    void destroy() noexcept override;
private:
    int repeat;
};

class ExpressionDeclaration : public Declaration
{
public:
    ExpressionDeclaration() noexcept;

    void destroy() noexcept override;
private:
    std::string expression;
};
