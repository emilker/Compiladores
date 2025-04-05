#include "statement.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std::literals;

Statement::~Statement()
{
}

StatementSequence::StatementSequence(Statement *f, Statement *n) noexcept
    : first(f), next(n) {}

void StatementSequence::destroy() noexcept
{
    first->destroy();
    delete first;
    first = nullptr;
    next->destroy();
    delete next;
    next = nullptr;
}

Compasses::Compasses(Statement* c1, Statement* c2) noexcept
    : left_Statement{c1}, right_Statement{c2} {}

void Compasses::destroy() noexcept
{
    left_Statement->destroy();
    delete left_Statement;
    left_Statement = nullptr;
    right_Statement->destroy();
    delete right_Statement;
    right_Statement = nullptr;
}

SimpleNote::SimpleNote(const std::string& n,const std::string& d) noexcept
    : note{n},duration{d}  {}

void SimpleNote::mostrar() const noexcept
{
    std::cout<<"SimpleNote\n"<<note<<std::endl;
    std::cout<<"SimpleNote\n"<<duration<<std::endl;
}

void SimpleNote::destroy() noexcept {}

DottedNote::DottedNote(const std::string& n, const std::string& du, const std::string& dt) noexcept
    : note{n}, duration{du}, dotted{dt}  {}

void DottedNote::destroy() noexcept {}

AlteredNote::AlteredNote(const std::string &n, const std::string &al, const std::string &du) noexcept
    : note{n}, alteration{al}, duration{du} {}

void AlteredNote::destroy() noexcept {}

AlteredDottedNote::AlteredDottedNote(const std::string &n, const std::string &al, const std::string &du, const std::string& dt) noexcept
    : note{n}, alteration{al}, duration{du}, dotted{dt}  {}

void AlteredDottedNote::destroy() noexcept {}
