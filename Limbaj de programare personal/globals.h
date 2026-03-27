#ifndef GLOBALS_H
#define GLOBALS_H
/* ==============================    
    HEADER GUARD
    Previne includerea multipla a acestui fisier
    ============================== */

/* ==============================
    BIBLIOTECI STANDARD C++
    ============================== */
#include <string> // std::string
#include <vector> // std::vector
#include <map> // std::map
#include <iostream> // std::cout, std::endl
#include <fstream> // std::ofstream, std::ifstream

/* ==============================
    TIPURI DE DATE ALE LIMBAJULUI
    ============================== */
enum DataType 
{ 
    T_INT, // int
    T_FLOAT, // float
    T_BOOL, // bool
    T_STRING, // string
    T_CLASS, // clasa
    T_VOID, // void (pentru functii)     
    T_UNKNOWN // tip necunoscut
};


/* ==============================
    STRUCTURA VALUE
    Wrapper pentru valori (Cerinta IV)
    ============================== */
struct Value 
{
    DataType type; // tipul valorii
    int iVal; // valoare int
    float fVal; // valoare float
    bool bVal; // valoare bool
    std::string sVal; // valoare string

    /* Constructor implicit */
    Value() : type(T_UNKNOWN), iVal(0), fVal(0.0f), bVal(false), sVal("") {}

    /* Creeaza o valoare default pentru un tip */
    static Value defaultValue(DataType t) 
    {
        Value v; v.type = t;
        if (t == T_STRING) 
            v.sVal = "";
        return v;
    }

    /* Afiseaza valoarea in functie de tip */
    void print() const 
    {
        if (type == T_INT) 
            std::cout << iVal;
        else if (type == T_FLOAT) 
            std::cout << fVal;
        else if (type == T_BOOL) 
            std::cout << (bVal ? "true" : "false");
        else if (type == T_STRING) 
            std::cout << sVal;
        else 
            std::cout << "null";
    }
};

/* ==============================
    PARAMETRU DE FUNCTIE
    ============================== */
struct ParamInfo 
{
    std::string name; // numele parametrului
    DataType type; // tipul parametrului
};

/* ==============================
    DECLARATII INAINTE
    ============================== */
struct SymbolTable;
/* Tabela de simboluri curenta (scope activ) */
extern SymbolTable* currentTable; 

/* ==============================
    NOD AST (ARBORE DE SINTAXA ABSTRACTA)
    ============================== */
struct ASTNode 
{
    std::string op; // operator sau literal
    ASTNode *left, *right; // copil stang, drept
    DataType exprType; // tipul expresiei
    Value constValue; // valoare constanta (daca exista)

    /* Constructor pentru un nod fara copii */
    ASTNode(const std::string& o) : op(o), left(nullptr), right(nullptr), exprType(T_UNKNOWN) {}
    /* Constructor pentru un nod cu copii */
    ASTNode(const std::string& o, ASTNode* l, ASTNode* r) : op(o), left(l), right(r), exprType(T_UNKNOWN) {}

    /* Evalueaza expresia reprezentata de nod */
    Value evaluate(); 
};

/* ==============================
    INFORMATII DESPRE SIMBOL
    ============================== */
struct SymbolInfo 
{
    std::string name; // numele simbolului
    DataType type; // tipul simbolului
    Value value;  // valoarea simbolului

    /* Informatii pentru functii */
    bool isFunction = false;
    DataType returnType = T_UNKNOWN;
    std::vector<ParamInfo> params;

    /* Informatii pentru clase / instante */
    SymbolTable* classScope = nullptr;
    std::string className; // numele clasei (pentru instanțe)
};

/* ==============================
    TABELE DE SIMBOLURI
    ============================== */
struct SymbolTable 
{
    std::string name; // numele scope-ului
    SymbolTable* parent; // pointer catre scope-ul parinte
    std::map<std::string, SymbolInfo> symbols; // simboluri

    /* Constructor */
    SymbolTable(const std::string& n, SymbolTable* p = nullptr) : name(n), parent(p) {}

    /* Adauga un simbol */
    bool add(const std::string& id, const SymbolInfo& info) 
    {
        if (symbols.count(id)) 
            return false; // simbol deja existent
        symbols[id] = info;
        return true;
    }

    /* Cautam un simbol (recursiv in parinti) */
    SymbolInfo* lookup(const std::string& id) 
    {
        if (symbols.count(id)) 
            return &symbols[id];
        if (parent) 
            return parent->lookup(id);
        return nullptr;
    }
};

/* Lista tuturor tabelelor de simboluri */
extern std::vector<SymbolTable*> allTables;

/* ==============================
    CONVERSIE TIP -> STRING
    ============================== */
inline std::string typeToStr(DataType t) 
{
    switch(t) 
    {
        case T_INT: return "int"; 
        case T_FLOAT: return "float";
        case T_BOOL: return "bool"; 
        case T_STRING: return "string";
        case T_CLASS: return "class"; 
        default: return "unknown";
    }
}

/* ==============================
    AFISARE TABELE DE SIMBOLURI
    Cerinta I + Cerinta II
    ============================== */
inline void dumpSymbolTables(std::ostream& out) 
{
    for (auto st : allTables) 
    {

        /* Afisam numele scope-ului */
        out << "=== Symbol Table: " << st->name;
        if (st->parent) 
            out << " (Parent Scope: " << st->parent->name << ")";
        else 
            out << " (Global Scope)";
        out << " ===\n";

        /* Iteram prin simboluri */
        for (auto const& [id, info] : st->symbols) 
        {
            out << "  " << id << " : ";
            
            /* Diferentiem intre clasa si instanta */
            if (info.type == T_CLASS && !info.className.empty()) 
            {
                out << "instance of " << info.className;
            } 
            else 
            {
                out << typeToStr(info.type);
            }

            /* Daca simbolul este functie */
            if (info.isFunction) 
            {
                out << " (Return: " << typeToStr(info.returnType) << ", Params: ";
                for (size_t i=0; i<info.params.size(); ++i) 
                {
                    out << info.params[i].name << ":" << typeToStr(info.params[i].type) << (i < info.params.size()-1 ? ", " : "");
                }
                out << ")";
            } 
            /* Daca simbolul este variabila */
            else 
            {
                out << " | Value: ";
                if (info.type == T_INT) 
                    out << info.value.iVal;
                else if (info.type == T_FLOAT) 
                    out << info.value.fVal;
                else if (info.type == T_BOOL) 
                    out << (info.value.bVal ? "lumina" : "intuneric");
                else if (info.type == T_STRING) 
                    out << "\"" << info.value.sVal << "\"";
                else if (info.type == T_CLASS) 
                    out << "{object}";
            }
            out << "\n";
        }
        out << "\n";
    }
}

/* ==============================
    EVALUAREA UNUI NOD AST
    ============================== */
inline Value ASTNode::evaluate() 
{

    /* Nod frunza */
    if (!left && !right) 
    {

        /* Literal string */
        if (op[0] == '\"') 
        { 
            Value v; 
            v.type = T_STRING; 
            v.sVal = op.substr(1, op.size()-2); 
            return v;
        }
        
        /* Literal numeric */
        if (isdigit(op[0]) || (op[0] == '-' && isdigit(op[1]))) 
        {
            Value v;
            if (op.find('.') != std::string::npos) 
            { 
                v.type = T_FLOAT; 
                v.fVal = std::stof(op); 
            }
            else 
            { 
                v.type = T_INT; 
                v.iVal = std::stoi(op); 
            }
            return v;
        }

        /* Literal boolean */
        if (op == "true" || op == "false" || op == "lumina" || op == "intuneric") 
        {
            Value v; 
            v.type = T_BOOL; 
            v.bVal = (op == "true" || op == "lumina"); 
            return v;
        }

        /* Variabila */
        SymbolInfo* s = currentTable->lookup(op);
        if (s) 
            return s->value;

        return Value::defaultValue(exprType);
    }

    /* PRINT */
    if (op == "PRINT") 
    {
        Value val = left->evaluate();
        std::cout << "[ARCANA PRINT]: "; 
        val.print(); 
        std::cout << std::endl;
        return val;
    }

    if (op == "leaga_de") 
    { 
        Value rhs = right->evaluate();
        SymbolInfo* lhs = currentTable->lookup(left->op);
        if (lhs) 
            lhs->value = rhs;
        return rhs;
    }

    /* Operatii binare */
    Value l = left->evaluate();
    Value r = right->evaluate();
    Value res; res.type = l.type;

    if (op == "+") 
    {
        if (l.type == T_INT) 
            res.iVal = l.iVal + r.iVal;
        else 
            res.fVal = l.fVal + r.fVal;
    } 
    else if (op == "-") 
    {
        if (l.type == T_INT) 
            res.iVal = l.iVal - r.iVal;
        else 
            res.fVal = l.fVal - r.fVal;
    } 
    else if (op == "*") 
    {
        if (l.type == T_INT) 
            res.iVal = l.iVal * r.iVal;
        else 
            res.fVal = l.fVal * r.fVal;
    } 
    else if (op == "/") 
    {
        if (l.type == T_INT) 
            res.iVal = (r.iVal != 0) ? l.iVal / r.iVal : 0;
        else 
            res.fVal = (r.fVal != 0.0f) ? l.fVal / r.fVal : 0.0f;
    } 
    else if (op == ">") 
    {
        res.type = T_BOOL;
        if (l.type == T_INT) 
            res.bVal = l.iVal > r.iVal;
        else 
            res.bVal = l.fVal > r.fVal;
    } 
    else if (op == "&&") 
    {
        res.type = T_BOOL; 
        res.bVal = l.bVal && r.bVal;
    }

    return res;
}

#endif

