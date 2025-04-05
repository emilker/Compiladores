#include "ast_node_interface.hpp"

// destructores

ASTNodeInterface::~ASTNodeInterface()
{
}

// Constructores

TimeDeclaration::TimeDeclaration(int p, int f) noexcept
: pulse{p}, figure{f}
{
}

Statement::Statement() noexcept
{
}

SimpleNote::SimpleNote(std::string note, int duracion) noexcept
: note{note}, duracion{duracion}//
{
}

DottedNote::DottedNote(std::string) noexcept
{
}

AlteredNote::AlteredNote(std::string) noexcept
{
}

AlteredDottedNote::AlteredDottedNote(std::string) noexcept
{
}

// Destroy

void SimpleNote::destroy() noexcept
{
}
void ASTNodeInterface::destroy() noexcept
{
}