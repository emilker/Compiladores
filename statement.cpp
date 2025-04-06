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

Note::Note(Statement* note_, Statement* alteration_, Statement* duration_, Statement* dottes_) noexcept
    : note{note_}, alteration{alteration_}, duration{duration_}, dottes{dottes_}  {}

void Note::mostrar()  noexcept
{
    if (note)
    {
        note->mostrar();
    }

    if (alteration)
    {
        alteration->mostrar();
    }

    if (duration)
    {
        duration->mostrar();
    }
    
    if (dottes)
    {
        dottes->mostrar();
    }
}

void Note::destroy() noexcept
{
    delete note;
    delete alteration;
    delete duration;
    delete dottes;
    note = nullptr;
    alteration = nullptr;
    dottes = nullptr;
}

SectionDeclaration::SectionDeclaration(Statement* _id, Statement* _compass) noexcept
 : id{_id}, compass{_compass}{}

void SectionDeclaration::mostrar() noexcept
{
}

void SectionDeclaration::destroy() noexcept
{
}

void CompassesBarLine::mostrar()  noexcept
{
    left_Statement->mostrar();
    right_Statement->mostrar();
}

void CompassesComma::mostrar()  noexcept
{
    left_Statement->mostrar();
    right_Statement->mostrar();
}

Value::Value(std::string v) noexcept
    : value{v}{}

void Value::mostrar()  noexcept
{
    std::cout << value << std::endl;
}
void Value::destroy() noexcept
{
}

Time::Time(Statement *tiempo_, Statement *figure_, Statement *body_) noexcept
    :  tiempo{tiempo_}, figure{figure_}, body{body_}  {}

void Time::mostrar() noexcept
{
    if (tiempo)
    {
        tiempo->mostrar();
    }

    if (figure)
    {
        figure->mostrar();
    }

    if (body)
    {
        body->mostrar();
    }
}

void Time::destroy() noexcept
{

}
