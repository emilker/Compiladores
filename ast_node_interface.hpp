#pragma once

#include <forward_list>
#include <string>
#include <string_view>

class Statement;
class Declaration;
class Compasses;
class Expression;
class Note;


class ASTNodeInterface
{
public:
    virtual ~ASTNodeInterface() noexcept;

    virtual void destroy() noexcept = 0;
};