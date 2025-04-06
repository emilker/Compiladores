#pragma once

#include <string>
#include <utility> 

class Statement
{
public:
    virtual ~Statement();

    virtual void destroy() noexcept = 0;

   // virtual int eval() noexcept = 0;

   virtual void mostrar()  noexcept = 0;

    //virtual std::string to_string()  noexcept = 0;
};


class Time : public Statement
{
public:
    Time(Statement* tiempo_, Statement* figure_, Statement* body_) noexcept;
    
    void mostrar()  noexcept;
    
    void destroy() noexcept override;

    //  int eval() noexcept override;

    //  std::string to_string()  noexcept override;

private:
    Statement* tiempo;
    Statement* figure;
    Statement* body; 
};




class Note : public Statement
{  
public:
    Note(Statement* note_, Statement* alteration_, Statement* duration_, Statement* dottes_) noexcept;
    
    void mostrar()  noexcept;
    
    void destroy() noexcept override;

    //  int eval() noexcept override;
  
    //  std::string to_string()  noexcept override;
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
   
    void mostrar()  noexcept;
    
    void destroy() noexcept override;

private:
    Statement* id;
    Statement* compass;
};

class StatementSequence : public Statement 
{
public:
    StatementSequence(Statement* f, Statement* n) noexcept;

    void mostrar()  noexcept;

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

class CompassesComma : public Compasses 
{       
public:
    using Compasses::Compasses; 

    void mostrar()  noexcept override;

  //  int eval() noexcept override;

  //  std::string operand_str()  noexcept override;

};

class CompassesBarLine : public Compasses 
{   
public:
    using Compasses::Compasses; 

    //  int eval() noexcept override;

    void mostrar()  noexcept override;

    //  std::string operand_str()  noexcept override;
 
};

class Value: public Statement
{
public:
    Value(std::string v) noexcept;

    Value(std::pair<std::string, std::string> v) noexcept;

    void mostrar()  noexcept override;

    void destroy() noexcept override;

private:
    std::string value;
    std::pair<std::string, std::string> value_measure;
};
