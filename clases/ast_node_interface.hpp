#pragma once

#include <string>

class ASTNodeInterface
{
public:
    virtual ~ASTNodeInterface(); 

    virtual void destroy() noexcept = 0;

};

class Statement : public ASTNodeInterface
{
public:
    Statement() noexcept;
    
private :
};

class TimeDeclaration : public Statement
{
public:
    
    TimeDeclaration(int p, int f) noexcept;

    void destroy() noexcept override;

private:
    int pulse;   //numerador
    int figure;  //Denominador
};

class Declaration : public ASTNodeInterface
{
public:
    Declaration() noexcept;

};
class SectionDeclaration : public Declaration
{
public:
    SectionDeclaration(std::string) noexcept;

    void destroy() noexcept override;

private:
    std::string name;
};
 class RepeatDeclaration : public Declaration
{   
 public:
     RepeatDeclaration(int) noexcept;

     void destroy() noexcept override;
 private:
     int repeat;
};

class Note: public ASTNodeInterface
{
 public:
    virtual ~Note() noexcept = default;
    Note() noexcept;
 private:

};
 class SimpleNote : public Note
 {  
 public:
    SimpleNote(std::string, int) noexcept;
    void destroy() noexcept override;
 private:
    std::string note;
    int duracion;
 };
 class DottedNote : public Note
{
 public:
    DottedNote(std::string) noexcept;

    void destroy() noexcept override;
 private:
    std::string dotted_note;
};
 class AlteredNote : public Note
{
 public:
    AlteredNote(std::string) noexcept;

    void destroy() noexcept override;
 private:            
    std::string altered_note;
};
 class AlteredDottedNote : public Note
{       
 public:
    AlteredDottedNote(std::string) noexcept;
    void destroy() noexcept override;
 private:
    std::string altered_dotted_note;
};


class Compasses : public ASTNodeInterface
{
public:
    Compasses() noexcept;

private:

};
class CompassesComma : public Compasses 
{       
public:
    CompassesComma(Compasses*, Compasses*) noexcept;

    void destroy() noexcept override;
private:
    Compasses* left_Compasses;
    Compasses* right_Compasses;
};
class CompassesBarLine : public Compasses 
{   
public:
    CompassesBarLine(Compasses*,Compasses) noexcept;

    void destroy() noexcept override;
private:
    Compasses* left_Compasses;
    Compasses* right_Compasses;  
};

