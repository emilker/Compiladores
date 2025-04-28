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
class StatementSequence : public Statement 
{
public:
    StatementSequence(Statement* f, Statement* n) noexcept;

    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario

    void destroy() noexcept override;

    float pulse() noexcept override;
        
private:
    Statement* first;
    Statement* next;
};
class Time : public Statement
{
public:
    Time(Statement* pulse_, Statement* figure_, Statement* body_);
    
    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario    
    
    void destroy() noexcept override;

    float pulse() noexcept override { return 0.0f; } // Implementar según sea necesario

private:
    Statement* pulse_;
    Statement* figure_;
    Statement* body; 
};
class Value: public Statement
{
public:
    Value(std::string v) noexcept;

    std::string get_value() noexcept;

    void print()  noexcept;

    void destroy() noexcept override;

    float pulse() noexcept override { return 0.0f; } // Implementar según sea necesario

private:
    std::string value;
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

class Compasses : public Statement
{
public:
    Compasses(Statement* c1, Statement* c2, bool time_);

    void destroy() noexcept override;

protected:
    Statement* left_Statement;
    Statement* right_Statement;
    float compass_pulse;
    float left_pulse;
    float right_pulse;
    bool time;
};
class CompassesComma : public Compasses 
{       
public:
    using Compasses::Compasses; 

    void print()  noexcept;

    void destroy() noexcept override;

    float pulse() noexcept;

    std::string get_value() noexcept override;
};

class CompassesBarLine : public Compasses 
{   
public:
    using Compasses::Compasses; 

    void print()  noexcept;

    float pulse() noexcept;

    float calculate_figure() noexcept;

    void destroy() noexcept override;

    std::string get_value() noexcept override; // Implementar según sea necesario
};
class SectionDeclaration : public Statement
{
public:
    SectionDeclaration(Statement* id,Statement* compass, SymbolTable& symtab);
   
    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario
    
    void destroy() noexcept override;

    float pulse() noexcept override { return 0.0f; } // Implementar según sea necesario

private:
    Statement* id;
    Statement* compass;
    SymbolTable& symtab; // Referencia a la tabla de símbolos
};

class SectionReference : public Statement 
{
public:
    SectionReference(std::string id, SymbolTable& symtab) noexcept;
        
    Statement* semantic_analysis() noexcept; 

    void print()  noexcept;

    std::string get_value() noexcept override { return id; } // Implementar según sea necesario

    void destroy() noexcept override;

    float pulse() noexcept;

private:
    std::string id;
    SymbolTable& symtab; // Referencia a la tabla de símbolos
};
class RepeatDeclaration : public Statement {
public:
    RepeatDeclaration(Statement* count, Statement* body) noexcept;

    void repeat() noexcept;
        
    void print() noexcept;
        
    std::string get_value() noexcept override { return ""; } 

    float pulse() noexcept;
        
    void destroy() noexcept override;
    
private:
        
    Statement* repeat_count;
        
    Statement* body;
};
    