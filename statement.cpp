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
    : left_Statement{c1}, right_Statement{c2}  {}

void Compasses::destroy() noexcept
{
    left_Statement->destroy();
    delete left_Statement;
    left_Statement = nullptr;
    right_Statement->destroy();
    delete right_Statement;
    right_Statement = nullptr;
}


void CompassesBarLine::print() noexcept
{
   std::cout << left_Statement->get_value() << " | " << right_Statement->get_value() << std::endl;
}

float CompassesBarLine::pulse() noexcept
{
    left_pulse += left_Statement->pulse();
    right_pulse += right_Statement->pulse();

    if (left_pulse != right_pulse){
        std::cout << "left_pulse: " << left_pulse << std::endl;
        std::cout << "right_pulse: " << right_pulse << std::endl;
        std::cerr << "Error: Pulsos desiguales en CompassesBarLine" << std::endl;
        return 0.0f; // O lanza una excepción más descriptiva
     }
    return left_pulse;
}

float CompassesBarLine::calculate_figure() noexcept
{  
    return 0.0f;
}

void CompassesBarLine::destroy() noexcept
{
}

void CompassesComma::print() noexcept
{
}

void CompassesComma::destroy() noexcept
{
}

std::string CompassesComma::get_value() noexcept
{
    return left_Statement->get_value() + " , " + right_Statement->get_value();
}

float CompassesComma::pulse() noexcept
{
    if(left_Statement) left_pulse += left_Statement->pulse();

    if(right_Statement) right_pulse += right_Statement->pulse();

    return left_pulse + right_pulse;
}

Note::Note(Statement* note_, Statement* alteration_, Statement* duration_, Statement* dottes_) noexcept
    : note{note_}, alteration{alteration_}, duration{duration_}, dottes{dottes_}  {}

void Note::print()  noexcept
{
    if (note) note->print();
    if (alteration) alteration->print();
    if (duration) duration->print();
    if (dottes) dottes->print();
}

std::string Note::get_value() noexcept
{
    return (note ? note->get_value() : "") + (alteration ? alteration->get_value() : "") + (duration ? duration->get_value() : "") + (dottes ? dottes->get_value() : "");
  
}
float Note::pulse() noexcept
{
    static std::unordered_map<std::string, float> durations = {
        {"w", 4}, {"h", 2}, {"q", 1}, {"e", 0.5}, {"s", 0.25}
    };

    auto it = durations.find(duration->get_value());
    if(it == durations.end()) {
        std::cerr << "Duración no válida: " << duration->get_value() << std::endl;
        return 0.0f; // O lanza una excepción más descriptiva
    }
    return it->second;
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
    :  Pulse{pulse_}, figure{figure_}, body{body_}  {}

void Time::print() noexcept
{
    if (Pulse) Pulse->print();
    if (figure) figure->print();
    if (body) body->print();
}

void Time::destroy() noexcept
{
}

SectionReference::SectionReference(std::string id, SymbolTable& symtab ) noexcept
    : id{id}, symtab{symtab} {}

Statement* SectionReference::semantic_analysis() noexcept
{
    auto resolved = symtab.lookup(id);

    if(!resolved) {
        std::runtime_error("Sección no definida: "s + id);
    }
    return resolved->body; // Asigna el cuerpo de la sección referenciada
}

void SectionReference::print() noexcept
{
}

void SectionReference::destroy() noexcept
{
}