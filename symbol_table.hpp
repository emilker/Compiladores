#pragma once
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Statement; 
class Symbol 
{
public:
    std::string name;       
    Statement* measures;          
        
    static std::shared_ptr<Symbol> Build(std::string_view name, Statement* measures) {
        return std::make_shared<Symbol>(name, measures); // Crea un shared_ptr con nuevo Symbol
    }
        
    Symbol(std::string_view name, Statement* measures) : name(name), measures(measures) {}   
};

class SymbolTable 
{
public:
    using TableType = std::unordered_map<std::string, std::shared_ptr<Symbol>>;
    using TableStack = std::vector<TableType>;
        
    SymbolTable() { enter_scope(); } // Llama a enter_scope() al crear
        
    void enter_scope() { 
        scopes.push_back({}); 
    }
            
    // Elimina el ámbito más reciente
    bool exit_scope() { 
        if(scopes.empty()) return false; 
        scopes.pop_back();       
        return true;                   
    }
        
    bool bind(const std::string& name, Statement* measures) {
        if(scopes.empty()) return false; // Verifica que haya ámbitos
            
        auto& current = scopes.back(); 
            
        // Verifica si el nombre ya existe en el ámbito actual
        if(current.find(name) != current.end()) return false; 
            
        // Registra el nuevo símbolo
        current[name] = Symbol::Build(name, measures);
        return true; 
    }
        
    std::shared_ptr<Symbol> lookup(std::string name) {

        if(scopes.empty()) return nullptr;

        // Itera desde el final (ámbito más interno) al inicio (global)
        for(auto it = scopes.rbegin(); it != scopes.rend(); ++it) 
        {
            auto found = it->find(name); 
            if(found != it->end()) 
            return found->second;   // Retorna el símbolo encontrado
        }
        return nullptr;
    }
        
private:
    TableStack scopes; 
};