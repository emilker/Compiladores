#pragma once
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Statement; // Declaración anticipada de la clase Statement
class Symbol {
public:
    std::string name;          // Nombre de la sección musical (ej. "intro", "estrofa")
    Statement* body;          // Puntero al AST que contiene las notas/compases de la sección
    int pulse;               // Numerador de la firma de compás (por defecto 4)
    int figure;             // Denominador de la firma de compás (por defecto 4 = negra)
        
    // Método factory para crear instancias compartidas
    static std::shared_ptr<Symbol> Build(std::string_view name, Statement* body) {
        return std::make_shared<Symbol>(name, body); // Crea un shared_ptr con nuevo Symbol
    }
        
    // Constructor que inicializa los miembros
    Symbol(std::string_view name, Statement* body) : name(name),body(body),pulse(4),figure(4) {}      // (compás común)
};

class SymbolTable {
public:
    // Define un tipo para la tabla de símbolos (mapa nombre -> símbolo)
    using TableType = std::unordered_map<std::string, std::shared_ptr<Symbol>>;
        
    // Define una pila de ámbitos (vector de tablas)
    using TableStack = std::vector<TableType>;
        
    // Constructor: inicializa la tabla con un ámbito global
    SymbolTable() { enter_scope(); } // Llama a enter_scope() al crear
        
    // Crea un nuevo ámbito (nivel de scope)
    void enter_scope() { 
        scopes.push_back({}); // Añade un nuevo mapa vacío al vector
    }
            
    // Elimina el ámbito más reciente
    bool exit_scope() { 
        if(scopes.empty()) return false; // Si no hay ámbitos, falla
        scopes.pop_back();              // Elimina el último ámbito
        return true;                    // Éxito
    }
        
    // Registra una nueva sección en el ámbito actual
    bool bind(const std::string& name, Statement* body) {
        if(scopes.empty()) return false; // Verifica que haya ámbitos
            
        auto& current = scopes.back();   // Obtiene el ámbito actual
            
        // Verifica si el nombre ya existe en el ámbito actual
        if(current.find(name) != current.end()) return false; 
            
        // Registra el nuevo símbolo
        current[name] = Symbol::Build(name, body);
        return true; // Éxito
    }
        
    // Busca una sección en todos los ámbitos (del más interno al más externo)
    std::shared_ptr<Symbol> lookup(std::string name) {
        // Itera desde el final (ámbito más interno) al inicio (global)
        for(auto it = scopes.rbegin(); it != scopes.rend(); ++it) 
        {
            auto found = it->find(name);  // Busca en este ámbito
            if(found != it->end()) 
            return found->second;     // Retorna si lo encuentra
        }
        return nullptr; // No encontrado
    }
        
private:
    TableStack scopes; // Pila de ámbitos (cada ámbito es un mapa de símbolos)
};


/*
    SymbolTable table;

    // Cuerpo de la sección "juses"
    // Cuerpo de la sección "jesus"

    table.enter_scope();

    // Registra primera sección
    table.bind_section("juses", body1);

    // Registra segunda sección
    table.bind_section("jesus", body2);

    scopes = [
        { // Ámbito 0 (global)
            "juses" => shared_ptr<Symbol> {
                name: "juses",
                body: StatementSequence(...), // Contiene las notas
                pulse: 4,
                figure: 4
            },
            "jesus" => shared_ptr<Symbol> {
                name: "jesus",
                body: StatementSequence(...), // Contiene sus notas
                pulse: 4,
                figure: 4
            }
        }
    ]
*/