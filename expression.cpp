#include "expression.hpp"

Expression::~Expression() {}

Value::Value(int val) noexcept
    : value{val} {}

void Value::destroy() noexcept {}

int Value::eval() noexcept
{
    return value;
}