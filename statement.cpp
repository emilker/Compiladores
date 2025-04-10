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

void StatementSequence::print() noexcept
{
    first->print();
    next->print();
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

void Note::print()  noexcept
{
    if (note)
    {
        note->print();
    }

    if (alteration)
    {
        alteration->print();
    }

    if (duration)
    {
        duration->print();
    }
    
    if (dottes)
    {
        dottes->print();
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

void SectionDeclaration::print() noexcept
{
}

void SectionDeclaration::destroy() noexcept
{
}

void MeasureStatement::print()  noexcept
{
    left_Statement->print();
    right_Statement->print();
}

Value::Value(std::string v) noexcept
    : value{v}{}

std::string Value::get_value() noexcept
{
    return value;
}

void Value::print()  noexcept
{
    std::cout << value << std::endl;
}
void Value::destroy() noexcept
{
}

Time::Time(Statement *pulse_, Statement *figure_, Statement *body_) noexcept
    :  pulse{pulse_}, figure{figure_}, body{body_}  {}

void Time::print() noexcept
{
    if (pulse)
    {
        pulse->print();
    }

    if (figure)
    {
        figure->print();
    }

    if (body)
    {
        body->print();
    }
}

void Time::destroy() noexcept
{

}
/*
SectionReference::SectionReference(std::string id) noexcept
    : id{id}  {}

void SectionReference::semantic_analysisk(SymbolTable& symtab) noexcept
{
    resolved = symtab.lookup(id);

    if(!resolved) {
        throw std::runtime_error("Sección no definida: " + id);
    }
}

void SectionReference::destroy() noexcept
{
}
*/