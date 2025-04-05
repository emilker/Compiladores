#include "statement.hpp"

TimeDeclaration::TimeDeclaration(int p, int f,const Body& _body) noexcept
    : pulse{p}, figure{f}, body{_body} {}