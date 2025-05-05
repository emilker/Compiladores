 #ifndef STATEMENT_HPP
 #define STATEMENT_HPP
 
 #include <string>
 #include <unordered_map>
 #include <stdexcept>
 
 class Statement {
 public:
     virtual ~Statement();
     virtual void print() noexcept = 0;
     virtual void destroy() noexcept = 0;
     virtual float pulse() noexcept = 0;
     virtual std::string get_value() noexcept { return ""; }
 };
 
 class StatementSequence : public Statement {
 public:
     StatementSequence(Statement* f, Statement* n) noexcept;
 
     void print() noexcept override;
     void destroy() noexcept override;
     float pulse() noexcept override;
 
 private:
     Statement* first;
     Statement* next;
 };
 
 class Compasses : public Statement {
 public:
     Compasses(Statement* c1, Statement* c2, bool time_);
 
     virtual void destroy() noexcept override;
     virtual std::string get_value() noexcept = 0;
 
 protected:
     Statement* left_Statement;
     Statement* right_Statement;
     float left_pulse;
     float right_pulse;
     bool time;
 };
 
 class CompassesBarLine : public Compasses {
 public:
     using Compasses::Compasses;
 
     void print() noexcept override;
     float pulse() noexcept override;
     float calculate_figure() noexcept;
     void destroy() noexcept override;
     std::string get_value() noexcept override;
 };
 
 class CompassesComma : public Compasses {
 public:
     using Compasses::Compasses;
 
     void print() noexcept override;
     float pulse() noexcept override;
     void destroy() noexcept override;
     std::string get_value() noexcept override;
 };
 
 class Note : public Statement {
 public:
     Note(Statement* note_, Statement* alteration_, Statement* duration_, Statement* dottes_) noexcept;
 
     void print() noexcept override;
     float pulse() noexcept override;
     void destroy() noexcept override;
     std::string get_value() noexcept override;
 
 private:
     Statement* note;
     Statement* alteration;
     Statement* duration;
     Statement* dottes;
 };
 
class SymbolTable;  // Forward declaration
 
 class SectionDeclaration : public Statement {
 public:
     SectionDeclaration(Statement* _id, Statement* _compass, SymbolTable& symtab);
 
     void print() noexcept override;
     void destroy() noexcept override;
     float pulse() noexcept override { return 0.0f; }
 
 private:
     Statement* id;
     Statement* compass;
     SymbolTable& symtab;
 };
 
 class Value : public Statement {
 public:
     explicit Value(std::string v) noexcept;
 
     void print() noexcept override;
     float pulse() noexcept override { return 0.0f; }
     void destroy() noexcept override;
     std::string get_value() noexcept override;
 
 private:
     std::string value;
 };
 
 class Time : public Statement {
 public:
     Time(Statement* pulse_, Statement* figure_, Statement* body_);
 
     void print() noexcept override;
     void destroy() noexcept override;
     float pulse() noexcept override { return 0.0f; }
 
 private:
     Statement* pulse_;
     Statement* figure_;
     Statement* body;
 };
 
 class SectionReference : public Statement {
 public:
     SectionReference(std::string id, SymbolTable& symtab) noexcept;
 
     void print() noexcept override;
     void destroy() noexcept override;
     float pulse() noexcept override;
     Statement* semantic_analysis() noexcept;
 
 private:
     std::string id;
     SymbolTable& symtab;
 };
 
 class RepeatDeclaration : public Statement {
 public:
     RepeatDeclaration(Statement* count, Statement* body) noexcept;
 
     void print() noexcept override;
     void destroy() noexcept override;
     float pulse() noexcept override;
 
 private:
     void repeat() noexcept;
 
     Statement* repeat_count;
     Statement* body;
 };
 
 
 #endif // STATEMENT_HPP
 