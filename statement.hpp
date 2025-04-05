#pragma once

#include <string>

class Statement
{
public:
    virtual ~Statement();

    virtual void destroy() noexcept = 0;

   // virtual int eval() noexcept = 0;

   virtual void mostrar()  noexcept = 0;

    //virtual std::string to_string()  noexcept = 0;
};

class SimpleNote : public Statement
{  
public:
    SimpleNote(const std::string& n, const std::string& d) noexcept;
    
    void mostrar()  noexcept;
    
    void destroy() noexcept override;

    //  int eval() noexcept override;
  
    //  std::string to_string()  noexcept override;
private:
    std::string note;
    std::string duration;
};

class DottedNote : public Statement
{
public:
    DottedNote(const std::string& n, const std::string& du, const std::string& dt) noexcept;

    void mostrar()  noexcept;

    void destroy() noexcept override;
private:
    std::string note;
    std::string duration;
    std::string dotted;
};

class AlteredNote : public Statement
{
public:
    AlteredNote(const std::string& n, const std::string& al, const std::string& du ) noexcept;
    
    void mostrar()  noexcept;

    void destroy() noexcept override;
private: 
    std::string note;
    std::string alteration;
    std::string duration;           
};

class AlteredDottedNote : public Statement
{       
public:
    AlteredDottedNote(const std::string& n, const std::string& al, const std::string& du, const std::string& dt) noexcept;

    void mostrar()  noexcept;

    void destroy() noexcept override;
private:
    std::string note;
    std::string alteration;
    std::string duration;
    std::string dotted;
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