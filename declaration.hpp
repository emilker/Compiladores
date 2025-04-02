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
    TimeDeclaration() noexcept;

    void destroy() noexcept override;

private:
    std::string time;
};

class SectionDeclaration : public Declaration
{
public:
    SectionDeclaration() noexcept;

    void destroy() noexcept override;

private:
    std::string section;
};

class RepartDeclaration : public Declaration
{   
public:
    RepartDeclaration() noexcept;

    void destroy() noexcept override;
private:
    std::string repart;
};

class ExpressionDeclaration : public Declaration
{
public:
    ExpressionDeclaration() noexcept;

    void destroy() noexcept override;
private:
    std::string expression;
};
