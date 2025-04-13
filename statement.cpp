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
    if(first) first->print();
    if(next) next->print();
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

float StatementSequence::pulse() noexcept
{                          
    float pulse = 0.0f;
    if (first) {
        pulse = first->pulse();
    }
    if (next) {
        pulse = next->pulse();
    }
    return pulse;
}

Compasses::Compasses(Statement* c1, Statement* c2) noexcept
    : left_Statement{c1}, right_Statement{c2}, left_pulse{0.0f},right_pulse{0.0f}  {}

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
   std::cout << left_Statement->get_value() << " |  " << right_Statement->get_value() << std::endl;
}
 float CompassesBarLine::pulse() noexcept
{ 
    if (left_Statement) 
    {
        left_pulse = left_Statement->pulse();
        //std::cout << " left_pulse: " << left_pulse;
    }

    if (right_Statement) 
    {
        right_pulse = right_Statement->pulse();
        //std::cout << " right_pulse: " << right_pulse;
    }

    if (left_pulse == right_pulse)
    {
        //std::cout << " Pulsos iguales en CompassesBarLine" << std::endl;
        return left_pulse;  
    } else 
    {
       // std::cout << " Pulsos desiguales en CompassesBarLine" << std::endl; 
        return 0.0f; // O lanza una excepción más descriptiva
    }
}
float CompassesBarLine::calculate_figure() noexcept
{  
    return 0.0f;
}

void CompassesBarLine::destroy() noexcept
{
    left_Statement->destroy();
    delete left_Statement;
    left_Statement = nullptr;
    right_Statement->destroy();
    delete right_Statement;
    right_Statement = nullptr;
}

std::string CompassesBarLine::get_value() noexcept
{
    return left_Statement->get_value() + " | " + right_Statement->get_value();
}

void CompassesComma::print() noexcept{}

void CompassesComma::destroy() noexcept
{
    if (left_Statement) {
        left_Statement->destroy();
        delete left_Statement;
        left_Statement = nullptr;
    }
    if (right_Statement) {
        right_Statement->destroy();
        delete right_Statement;
        right_Statement = nullptr;
    }
}

std::string CompassesComma::get_value() noexcept
{
    return left_Statement->get_value() + " , " + right_Statement->get_value();
}

float CompassesComma::pulse() noexcept
{
    left_pulse = left_Statement ? left_Statement->pulse() : 0.0f;
    right_pulse = right_Statement ? right_Statement->pulse() : 0.0f;
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
    note->destroy();    
    delete note;
    note = nullptr;
    alteration->destroy();
    delete alteration;
    alteration = nullptr;
    duration->destroy();
    delete duration;
    duration = nullptr;
    dottes->destroy();
    delete dottes;
    dottes = nullptr;
}

SectionDeclaration::SectionDeclaration(Statement* _id, Statement* _compass, SymbolTable& symtab)
 : id{_id}, compass{_compass}, symtab{symtab} 
{
    std::string Id = id->get_value();  
    
    if (!symtab.bind(Id, compass) )
    {
        throw std::runtime_error("Sección ya definida: " + Id);
    }
}

void SectionDeclaration::print() noexcept{}

void SectionDeclaration::destroy() noexcept
{
    id->destroy();
    delete id;
    id = nullptr;
    compass->destroy();
    delete compass;
    compass = nullptr;
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
void Value::destroy() noexcept {}

Time::Time(Statement *pulse_, Statement *figure_, Statement *body_)
    :  pulse_{pulse_}, figure_{figure_}, body{body_}  
{
    int Pulse = std::stoi(pulse_->get_value());
    int Figure = std::stoi(figure_->get_value());

    static std::unordered_map<int, float> FIGURES = {
        {1, 4}, {2, 2}, {4, 1}, {8, 0.5}, {16, 0.25}
    };

    auto it = FIGURES.find(Figure);
    if(it == FIGURES.end()) {
        throw std::runtime_error("Figura no válida:");
    }
    if ( !(it->second*Pulse) == body->pulse() )
    {
        throw std::runtime_error("Pulsos desiguales en Time");
    }

}

void Time::print() noexcept
{
    if (body) body->print();
}

void Time::destroy() noexcept
{
    pulse_->destroy();
    delete pulse_;
    pulse_ = nullptr;
    figure_->destroy();
    delete figure_;
    figure_ = nullptr;
    body->destroy();
    delete body;
    body = nullptr;
}

SectionReference::SectionReference(std::string id, SymbolTable& symtab ) noexcept
    : id{id}, symtab{symtab} {}

Statement* SectionReference::semantic_analysis() noexcept
{
    auto resolved = symtab.lookup(id);

    if(!resolved) {
        std::runtime_error("Sección no definida: "s + id);
        return nullptr; // O lanza una excepción más descriptiva
    }
    
    return resolved->body; // Asigna el cuerpo de la sección referenciada
}

void SectionReference::print() noexcept
{
    auto resolved = symtab.lookup(id);

    if(!resolved) 
    {
        std::runtime_error("Sección no definida: "s + id);
        return; // O lanza una excepción más descriptiva
    }
    resolved->body->print(); // Imprime el cuerpo de la sección referenciada
}

void SectionReference::destroy() noexcept{}

float SectionReference::pulse() noexcept
{
    auto resolved = symtab.lookup(id);

    if(!resolved) 
    {
        return 0.0; // O lanza una excepción más descriptiva
    }
    return resolved->body->pulse(); // Imprime el cuerpo de la sección referenciada
}

RepeatDeclaration::RepeatDeclaration(Statement* count, Statement* body) noexcept
    : repeat_count(count), body(body) {}

void RepeatDeclaration::repeat() noexcept
{
}

void RepeatDeclaration::print() noexcept {

    int count = std::stoi(repeat_count->get_value());

    for (int i = 0; i < count; ++i) 
    {
        if (body) body->print();  
    }
}

float RepeatDeclaration::pulse() noexcept
{
    if(body) {
        return body->pulse(); // O lanza una excepción más descriptiva
    }
}

void RepeatDeclaration::destroy() noexcept
{
    repeat_count->destroy();
    delete repeat_count;
    repeat_count = nullptr;
    body->destroy();
    delete body;
    body = nullptr;
}