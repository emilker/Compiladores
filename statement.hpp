#pragma once

#include <string>
#include <utility> 
//#include "symbol_table.hpp"

class Statement
{
public:
    virtual ~Statement();

    virtual void destroy() noexcept = 0;

    virtual void print()  noexcept = 0;

    virtual std::string get_value() noexcept = 0; 

};

class Time : public Statement
{
public:
    Time(Statement* pulse_, Statement* figure_, Statement* body_) noexcept;
    
    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario    
    
    void destroy() noexcept override;

private:
    Statement* pulse;
    Statement* figure;
    Statement* body; 
};

class Note : public Statement
{  
public:
    Note(Statement* note_, Statement* alteration_, Statement* duration_, Statement* dottes_) noexcept;
    
    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario
    
    void destroy() noexcept override;

private:
    Statement* note;
    Statement* duration;
    Statement* dottes;
    Statement* alteration;  
};

class SectionDeclaration : public Statement
{
public:
    SectionDeclaration(Statement* id,Statement* compass) noexcept;
   
    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario
    
    void destroy() noexcept override;

private:
    Statement* id;
    Statement* compass;
};

class StatementSequence : public Statement 
{
public:
    StatementSequence(Statement* f, Statement* n) noexcept;

    void print()  noexcept;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario

    void destroy() noexcept override;
        
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

};

class MeasureStatement : public Compasses 
{       
public:
    using Compasses::Compasses; 

    void print()  noexcept override;

    std::string get_value() noexcept override { return ""; } // Implementar según sea necesario

};

class Value: public Statement
{
public:
    Value(std::string v) noexcept;

    std::string get_value() noexcept; 

    void print()  noexcept override;

    void destroy() noexcept override;

private:
    std::string value;
};
