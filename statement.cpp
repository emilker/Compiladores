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

void StatementSequence::mostrar() noexcept
{
    std::cout << "StatementSequence\n";
    first->mostrar();
    next->mostrar();
}

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

void SimpleNote::mostrar()  noexcept
{
    std::cout<<"SimpleNote\n"<<note<<std::endl;
    std::cout<<"SimpleNote\n"<<duration<<std::endl;
}

void SimpleNote::destroy() noexcept {}

DottedNote::DottedNote(const std::string& n, const std::string& du, const std::string& dt) noexcept
    : note{n}, duration{du}, dotted{dt}  {}

void DottedNote::mostrar()  noexcept
{
}

void DottedNote::destroy() noexcept {}

AlteredNote::AlteredNote(const std::string &n, const std::string &al, const std::string &du) noexcept
    : note{n}, alteration{al}, duration{du} {}


    void AlteredNote::mostrar()  noexcept
{
}

void AlteredNote::destroy() noexcept {}

AlteredDottedNote::AlteredDottedNote(const std::string &n, const std::string &al, const std::string &du, const std::string& dt) noexcept
    : note{n}, alteration{al}, duration{du}, dotted{dt}  {}

void AlteredDottedNote::mostrar()  noexcept
{
}

void AlteredDottedNote::destroy() noexcept {}

void CompassesBarLine::mostrar()  noexcept
{
    std::cout << "CompassesBarLine\n";
    left_Statement->mostrar();
    right_Statement->mostrar();
}

void CompassesComma::mostrar()  noexcept
{
    std::cout << "CompassesComma\n";
    left_Statement->mostrar();
    right_Statement->mostrar();
}
