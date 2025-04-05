#include <expression.hpp>

using namespace std::literals;

Expression::~Expression() {}

Value::Value(int val) noexcept
    : value{val} {}

void Value::destroy() noexcept {}

int Value::eval() noexcept
{
    return value;
}

std::string Value::to_string() const noexcept
{
    return std::to_string(value);
}

BinaryOperation::BinaryOperation(Expression* e1, Expression* e2) noexcept
    : left_expression{e1}, right_expression{e2} {}

void BinaryOperation::destroy() noexcept
{
    left_expression->destroy();
    delete left_expression;
    left_expression = nullptr;
    right_expression->destroy();
    delete right_expression;
    right_expression = nullptr;
}


std::string BinaryOperation::to_string() const noexcept
{
    return "("s + left_expression->to_string() + operand_str() + right_expression->to_string() + ")"s;
}

int Addition::eval() noexcept
{
    return left_expression->eval() + right_expression->eval();
}

std::string Addition::operand_str() const noexcept
{
    return " + ";
}

int Subtraction::eval() noexcept
{
    return left_expression->eval() - right_expression->eval();
}

std::string Subtraction::operand_str() const noexcept
{
    return " - ";
}

int Multiplication::eval() noexcept
{
    return left_expression->eval() * right_expression->eval();
}

std::string Multiplication::operand_str() const noexcept
{
    return " * ";
}

int Division::eval() noexcept
{
    return left_expression->eval() / right_expression->eval();
}

std::string Division::operand_str() const noexcept
{
    return " / ";
}

int Module::eval() noexcept
{
    return left_expression->eval() % right_expression->eval();
}

std::string Module::operand_str() const noexcept
{
    return " % ";
}