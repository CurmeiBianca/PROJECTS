#include <iostream> // std::cout, std:cerr
#include <fstream> // std::ofstream
#include <cstdio> // FILE, fopen, fclose
#include <vector> // std::vector

#include "globals.h" // header-ul principal al compilatorului

using namespace std;

/* ==============================
    1. DEFINITII GLOBALE
    Aceste variabile sunt folosite de parser (Bison) si evaluatorul AST
    ============================== */
SymbolTable* globalTable = nullptr; // tabela de simboluri globala
SymbolTable* currentTable = nullptr; // tabela de simboluri curenta (scope activ)
std::vector<SymbolTable*> allTables; // vector cu toate tabelele de simboluri create

/* ==============================
    2. DECLARATII EXTERNE (Flex / Bison)
    ============================== */
extern int yyparse();
extern FILE* yyin;
extern int yylineno;

/* Declaratia functiei de dump din globals.h */
void dumpSymbolTables(std::ostream& out);

/* ==============================
    FUNCTIA MAINA
    ============================== */
int main(int argc, char* argv[]) 
{
    /* Verificam daca a fost furnizat fisierul sursa */
    if (argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " <source_file>" << endl;
        return 1;
    }

    /* ==============================
        3. INITIALIZARE SCOPE GLOBAL
        ============================== */
    globalTable = new SymbolTable("Global", nullptr); // cream tabela de simboluri globala
    currentTable = globalTable; // setam scope-ul curent ca fiind global

    /* Deschidem fisierul sursa pentru lexer */
    yyin = fopen(argv[1], "r");
    if (!yyin) 
    {
        cerr << "Nu s-a putut deschide fisierul: " << argv[1] << endl;
        return 1;
    }

    /* ==============================
    NOTA IMPORTANTA
    ==============================
    Mesajele:
    - Variable declared
    - Variable init
    - Class defined
    - Program parsed
    sunt afisate din expr.y, pe masura ce yyparse() analizeaza si evalueaza codul
    */

    /* ==============================
        4. EXECUTIE PARSER
        ============================== */
    int parse_result = yyparse(); // lansam analiza lexicala + sintactica 
    
    /* ==============================
        DUPA PPARSARE
        ============================== */
    if (parse_result == 0) 
    {
        /* Salvam tabelele de simboluri intr-un fisier */
        ofstream out_file("tables.txt");

        if (out_file.is_open()) 
        {
            dumpSymbolTables(out_file); 
            out_file.close();

            /* Mesaj de confirmare */
            cout << "=== Tabelele de simboluri salvate in tables.txt ===" << endl;
        }
    } 
    else 
    {
        /* Mesaj de eroare simplificat */
        cerr << "Error: Parsing failed at line " << yylineno << endl;
    }

    /* Inchidem fisierul de intrare */
    if (yyin) 
        fclose(yyin);

    /* Returnam rezultatul parserului */    
    return parse_result;
}
