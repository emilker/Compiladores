#pragma once

#include <string>
#include <utility> 
#include "symbol_table.hpp"

class Statement
{
public:
    virtual ~Statement();

    virtual void destroy() noexcept = 0;

    virtual void print()  noexcept = 0;

    virtual std::string get_value() noexcept = 0; 

    virtual float pulse() noexcept = 0;

};

class Time : public Statement
{
public:
    Time(Statement* pulse_, Statement* figure_, Statement* body_) noexcept;
    
    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario    
    
    void destroy() noexcept override;

    float pulse() noexcept override { return 0.0f; } // Implementar según sea necesario

private:
    Statement* Pulse;
    Statement* figure;
    Statement* body; 
};

class Note : public Statement
{  
public:
    Note(Statement* note_, Statement* alteration_, Statement* duration_, Statement* dottes_) noexcept;
    
    void print()  noexcept;

    std::string get_value() noexcept override;

    float pulse() noexcept;
    
    void destroy() noexcept override;

private:
    Statement* note;
    Statement* alteration; 
    Statement* duration;
    Statement* dottes;
     
};

class SectionDeclaration : public Statement
{
public:
    SectionDeclaration(Statement* id,Statement* compass) noexcept;
   
    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario
    
    void destroy() noexcept override;

    float pulse() noexcept override { return 0.0f; } // Implementar según sea necesario

private:
    Statement* id;
    Statement* compass;
};

class SectionReference : public Statement 
{
public:
    SectionReference(std::string id, SymbolTable& symtab) noexcept;
        
    Statement* semantic_analysis() noexcept; 


    void print()  noexcept override;

    std::string get_value() noexcept override { return id; } // Implementar según sea necesario

    void destroy() noexcept override;

    float pulse() noexcept override { return 0.0f; } // Implementar según sea necesario

private:
    std::string id;
    SymbolTable& symtab; // Referencia a la tabla de símbolos
};
class StatementSequence : public Statement 
{
public:
    StatementSequence(Statement* f, Statement* n) noexcept;

    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario

    void destroy() noexcept override;

    float pulse() noexcept override { return 0.0f; } // Implementar según sea necesario
        
private:
    Statement* first;
    Statement* next;
};
class Compasses : public Statement
{
public:
    Compasses(Statement* c1, Statement* c2) noexcept;

    void destroy() noexcept override;

protected:
    Statement* left_Statement;
    Statement* right_Statement;
    float left_pulse;
    float right_pulse;

};
class CompassesComma : public Compasses 
{       
public:
    using Compasses::Compasses; 

    void print()  noexcept override;

    void destroy() noexcept override;

    float pulse() noexcept;

    std::string get_value() noexcept override;
};

class CompassesBarLine : public Compasses 
{   
public:
    using Compasses::Compasses; 

    void print()  noexcept override;

    float pulse() noexcept;

    float calculate_figure() noexcept;

    void destroy() noexcept override;

    std::string get_value() noexcept override { return "hola"; } // Implementar según sea necesario
};


class Value: public Statement
{
public:
    Value(std::string v) noexcept;

    std::string get_value() noexcept;

    void print()  noexcept override;

    void destroy() noexcept override;

    float pulse() noexcept override { return 0.0f; } // Implementar según sea necesario

private:
    std::string value;
};
