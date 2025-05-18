#ifndef STATEMENT_HPP
#define STATEMENT_HPP
 
#include <string>
#include <unordered_map>
#include <stdexcept>

#include "symbol_table.hpp"

class AudioGenerator;
class Statement
{
public:
    virtual ~Statement();
    virtual void print() noexcept = 0;
    virtual void destroy() noexcept = 0;
    virtual float pulse() noexcept = 0;
    virtual bool semantic_analysis(SymbolTable& symbol_table) {return true;};
    virtual bool resolve_name(SymbolTable& symbol_table) {return true;};
    virtual std::string get_value() noexcept { return ""; }
    virtual void generate_sound(AudioGenerator& audio_gen) {};
    
};
 
class StatementSequence : public Statement 
{
public:
    StatementSequence(Statement* f, Statement* n) noexcept;
 
    void print() noexcept override;
    void destroy() noexcept override;
    float pulse() noexcept override;
    bool semantic_analysis(SymbolTable& symbol_table) noexcept;
    bool resolve_name(SymbolTable& symbol_table) noexcept;
    void generate_sound(AudioGenerator& audio_gen) noexcept override;

private:
    Statement* first;
    Statement* next;
};
 
class Measures : public Statement 
{
public:
    Measures(Statement* c1, Statement* c2, bool time_);
 
    void destroy() noexcept override;
    float pulse() noexcept = 0;
    std::string get_value() noexcept = 0;
    
protected:
    Statement* left_Sequence;
    Statement* right_Sequence;
    float left_pulse;
    float right_pulse;
    bool time;
};

class MeasureSequence : public Measures
{
public:
    using Measures::Measures;
 
    void print() noexcept override;
    float pulse() noexcept override;
    void destroy() noexcept override;
    std::string get_value() noexcept override;
    bool semantic_analysis(SymbolTable& symbol_table) noexcept;
    void generate_sound(AudioGenerator& audio_gen) noexcept override;
};
 
class NotesSequence : public Measures 
{
public:
    using Measures::Measures;
 
    void print() noexcept override;
    float pulse() noexcept override;
    void destroy() noexcept override;
    std::string get_value() noexcept override;
    bool semantic_analysis(SymbolTable& symbol_table) noexcept;
    void generate_sound(AudioGenerator& audio_gen) noexcept override;
};

class Note : public Statement 
{
public:
    Note(Statement* note_, Statement* alteration_, Statement* duration_, Statement* dottes_, bool time_) noexcept;
 
    void print() noexcept override;
    float pulse() noexcept override;
    void destroy() noexcept override;
    std::string get_value() noexcept override;
    bool semantic_analysis(SymbolTable& symbol_table) noexcept;
    void generate_sound(AudioGenerator& audio_gen) noexcept override;
 
private:
    Statement* note;
    Statement* alteration;
    Statement* duration;
    Statement* dottes;
    bool time;
};
 
class SectionDeclaration : public Statement 
{
public:
    SectionDeclaration(Statement* _id, Statement* _measures);
 
    void print() noexcept override;
    void destroy() noexcept override;
    float pulse() noexcept override { return 0.0f; }
    bool resolve_name(SymbolTable& symbol_table) noexcept;
 
private:
    Statement* id;
    Statement* measures;
};
 
class Value : public Statement 
{
public:
    Value(std::string v) noexcept;
 
    void print() noexcept override;
    float pulse() noexcept override { return 0.0f; }
    void destroy() noexcept override;
    std::string get_value() noexcept override;

private:
    std::string value;
};
 
class Time : public Statement 
{
public:
    Time(Statement* pulse_, Statement* figure_, Statement* body_);
 
    void print() noexcept override;
    void destroy() noexcept override;
    float pulse() noexcept override { return 1000; }
    bool semantic_analysis(SymbolTable& symbol_table) noexcept;
    bool resolve_name(SymbolTable& symbol_table) noexcept;
    void generate_sound(AudioGenerator& audio_gen) noexcept override;
 
private:
    Statement* pulse_;
    Statement* figure_;
    Statement* body;
};

class Tempo :  public Statement
{
public:
    Tempo(Statement* FIGURE, Statement* BPM);

    void print() noexcept;
    void destroy() noexcept;
    float pulse() noexcept override { return static_cast<float>(BPM_); }

    bool semantic_analysis(SymbolTable& symbol_table) noexcept;
    bool resolve_name(SymbolTable& symbol_table) noexcept;
    void generate_sound(AudioGenerator& audio_gen) noexcept override;

private:
    Statement* figure_;
    Statement* bpm_;
    double BPM_;
};

class SectionReference : public Statement 
{
public:
    SectionReference(std::string id) noexcept;
 
    void print() noexcept override;
    void destroy() noexcept override;
    float pulse() noexcept override;
    bool resolve_name(SymbolTable& symbol_table) noexcept;
    bool semantic_analysis(SymbolTable& symbol_table) noexcept;
    void generate_sound(AudioGenerator& audio_gen) noexcept override;
 
private:
    std::string id;
    Statement* measures;
};
 
class RepeatDeclaration : public Statement 
{
public:
    RepeatDeclaration(Statement* count, Statement* measures_) noexcept;

    void print() noexcept override;
    void destroy() noexcept override;
    float pulse() noexcept override;
    bool semantic_analysis(SymbolTable& symbol_table) noexcept;
    void generate_sound(AudioGenerator& audio_gen) noexcept override;
 
private:
    Statement* repeat_count;
    Statement* measures;
};

#endif // STATEMENT_HPP
 