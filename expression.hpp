#pragma once

#include "ast_node_interface.hpp"

class Expression
{
public:
    virtual ~Expression();

    virtual void destroy() noexcept = 0;

    virtual int eval() noexcept = 0;
};

class Value : public Expression
{
public:
    Value(int val) noexcept;

    void destroy() noexcept override;

    int eval() noexcept override;

private:
    int value;
};