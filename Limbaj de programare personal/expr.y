%{
/* ==============================
    INCLUDERI STANDARD C/C++
    ============================== */

#include <iostream> // pentru cout, cerr
#include <fstream> // pentru lucrul cu fisiere
#include <string> // pentru std::string
#include <vector> // pentru std::vector
#include <cstdlib> // pentru exit()
#include <cstring> // pentru stddup()
#include "globals.h" // definitii: SymbolTable, ASTNode, DataType etc.

/* Permite folosirea directa a std::string, std::vector etc. */
using namespace std;

void yyerror(const char* s);
extern int yylex();
extern int yylineno;

/* Tabele de simboluri */
extern SymbolTable* globalTable; // tabela globala
extern SymbolTable* currentTable; // tabela scope-ului curent
extern std::vector<SymbolTable*> allTables; // lista tuturor tabelelor

/* ==============================
    Conversie string -> tip intern
    ============================== */
DataType getTypeFromStr(const string& s) 
{
    if (s == "piatra_filosofala") return T_INT; // int
    if (s == "aur_topit") return T_FLOAT; // float
    if (s == "clarviziune") return T_BOOL; // bool
    if (s == "pergament") return T_STRING; // string
    return T_UNKNOWN; // tip necunoscut
}

/* ==============================
    Verificare compatibilitate tipuri
    ============================== */
void checkType(DataType lhs, DataType rhs, const string& msg) 
{
    if(lhs != rhs) 
    { // daca tipurile nu coincid
        cerr << "Eroare semantica la linia " << yylineno << ": " << msg << endl;
        exit(1); // opreste compilarea
    }
}
%}

/* ==============================
    Cod inclus in headerul Bison
    ============================== */
%code requires {
#include <vector>
#include <string>
#include "globals.h"

/* Structura pentru un parametru de functie */
struct Param 
{
    std::string type; // tipul parametrului
    std::string name; // numele parametrului
};
}

/* ==============================
    UNION - tipurile semantice
    ============================== */
%union 
{
    int int_val; // pentru literali int
    float float_val; // pentru literali float
    char* str; // pentru ID si stringuri
    ASTNode* ast; // pentru expresii/instructiuni
    std::vector<Param>* paramvec; // lista parametri
    std::vector<ASTNode*>* astlist; // lista de instructiuni
}

/* ==============================
    TOKENI CU VALORI
    ============================== */
%token <int_val> INT_LITERAL BOOL_LITERAL // literali int/bool
%token <float_val> FLOAT_LITERAL // literali float
%token <str> STRING_LITERAL ID // stringuri si identificatori

/* ==============================
    TOKENI FARA VALORI
    ============================== */
%token INT_TYPE FLOAT_TYPE STRING_TYPE BOOL_TYPE
%token CLASS NEW DOT IF ELSE WHILE RETURN MAIN_BLOCK PRINT
%token LBRACE RBRACE SEMICOLON ASSIGN LPAREN RPAREN COMMA
%token AND OR NOT EQ NEQ LT GT LEQ GEQ PLUS MINUS MUL DIV

/* ==============================
    PRECEDENTA OPERATORILOR
    ============================== */
%left OR
%left AND
%left EQ NEQ
%left LT GT LEQ GEQ
%left PLUS MINUS
%left MUL DIV
%right NOT

/* ==============================
    TIPURI PRODUSE DE REGULI
    ============================== */
%type <ast> expression statement function_call assignment variable_definition call_arguments arg_list
%type <astlist> statements
%type <str> type
%type <paramvec> parameters param_list

%%

/* ==============================
    REGULA DE START: program
    ============================== */
program:
    { 
        printf("=== Pornire analiza sintactica ===\n");
        if (globalTable) 
            allTables.push_back(globalTable); // salveaza tabela gloabal
    } 
    global_declarations main_block
;

/* ==============================
    DECLARATII GLOBALE
    ============================== */
global_declarations:
      /* empty */ // pot lipsi
    | global_declarations class_definition // clase
    | global_declarations function_definition // functii
    | global_declarations global_variable_decl // variabile globale
;

/* ==============================
    DEFINIRE CLASA
    ============================== */
class_definition:
    CLASS ID 
    {
        SymbolInfo info; // info despre clasa
        info.name = $2; // numele clase
        info.type = T_CLASS; // tip clasa
        info.classScope = new SymbolTable($2, currentTable); // scope nou
        allTables.push_back(info.classScope); // salveaza scope-ul
        currentTable->add($2, info); // adauga clasa in tabela curenta
        currentTable = info.classScope; // intra in scope-ul clasei
    }
    LBRACE class_body RBRACE optional_semicolon
    {
        printf("Class defined: %s\n", $2);
        currentTable = currentTable->parent; // iesire din clasa
    }
;

/* ; optional dupa clasa */
optional_semicolon: /* empty */ | SEMICOLON ;

/* Continutul clasei */
class_body:
      /* empty */
    | class_body variable_definition SEMICOLON
    | class_body function_definition
;

/* ==============================
    DEFINIRE FUNCTIE 
    ============================== */
function_definition:
    type ID LPAREN parameters RPAREN 
    {
        SymbolInfo info; // info functie
        info.name = $2; // nume functie
        info.type = getTypeFromStr($1); // tip return
        info.isFunction = true; // marcheaza functie
        info.returnType = info.type;
        
        SymbolTable* funcTable = new SymbolTable($2, currentTable); // scope functie
        allTables.push_back(funcTable);
        
        if($4) 
        { // daca exista parametri
            for(auto &p : *$4) 
            {
                ParamInfo pi;
                pi.name = p.name;
                pi.type = getTypeFromStr(p.type);
                info.params.push_back(pi);
                
                SymbolInfo pInfo;
                pInfo.name = p.name;
                pInfo.type = pi.type;
                pInfo.value = Value::defaultValue(pi.type);
                funcTable->add(p.name, pInfo); // parametru = variabila globala
            }
        }
        currentTable->add($2, info); // adauga functia
        currentTable = funcTable; // intra in functie
    }
    LBRACE local_vars statements RBRACE
    {
        printf("Function defined: %s\n", $2);
        currentTable = currentTable->parent; // iesire din functie
        if($4) 
            delete $4; // elibereaza parametrii
    }
;

/* ==============================
    PARAMETRII FUNCTIEI
    ============================== */
parameters:
      /* empty */ { $$ = new std::vector<Param>(); }
    | param_list { $$ = $1; }
;

param_list:
      type ID 
      { 
          $$ = new std::vector<Param>(); 
          $$->push_back({string($1), string($2)}); 
      }
    | param_list COMMA type ID 
      { 
          $1->push_back({string($3), string($4)}); 
          $$ = $1; 
      }
;

/* ==============================
    VARIABILE LOCALE
    ============================== */
local_vars:
      /* empty */
    | local_vars variable_definition SEMICOLON
;

/* Variabile globale */
global_variable_decl:
    variable_definition SEMICOLON
;

/* ==============================
    DEFINIRE VARIABILA
    ============================== */
variable_definition:
      type ID
    {
        SymbolInfo info;
        info.name = $2; info.type = getTypeFromStr($1);
        info.value = Value::defaultValue(info.type);
        currentTable->add($2, info);
        printf("Variable declared: %s\n", $2);
        $$ = nullptr;
    }
    | type ID ASSIGN expression
    {
        SymbolInfo info;
        info.name = $2; info.type = getTypeFromStr($1);
        checkType(info.type, $4->exprType, "Initializare invalida");
        info.value = Value::defaultValue(info.type);
        currentTable->add($2, info);

        ASTNode* assignNode = new ASTNode("leaga_de", new ASTNode($2), $4);

        if (currentTable == globalTable) 
            assignNode->evaluate(); // executa imediat global

        printf("Variable init: %s\n", $2);
        $$ = assignNode;
    }
    | CLASS ID ID 
    {
        SymbolInfo info;
        info.name = $3; info.type = T_CLASS; info.className = $2;
        currentTable->add($3, info);
        printf("Variable declared: %s (object of %s)\n", $3, $2);
        $$ = nullptr;
    }
;

/* ==============================
    TIPURI
    ============================== */
type:
      INT_TYPE { $$ = strdup("piatra_filosofala"); }
    | FLOAT_TYPE { $$ = strdup("aur_topit"); }
    | STRING_TYPE { $$ = strdup("pergament"); }
    | BOOL_TYPE { $$ = strdup("clarviziune"); }
    | ID { $$ = strdup($1); }
;

/* ==============================
    MAIN
    ============================== */
main_block:
    MAIN_BLOCK LBRACE statements RBRACE
    {
        printf("Main block executed.\n");
        if ($3) 
        {
            for (ASTNode* node : *$3) 
            {
                if (node) 
                    node->evaluate(); // executa fiecare instructiune
            }
        }
        printf("Program parsed successfully.\n");
        printf("=== Analiza sintactica finalizata ===\n");
    }
;

/* ==============================
    LISTA DE INSTRUCTIUNI
    ============================== */
statements:
      /* empty */ { $$ = new std::vector<ASTNode*>(); }
    | statements statement { if($2) $1->push_back($2); $$ = $1; }
;

/* ==============================
    INSTRUCTIUNI
    ============================== */
statement:
      assignment SEMICOLON { $$ = $1; }
    | function_call SEMICOLON { $$ = $1; }
    | IF LPAREN expression RPAREN LBRACE statements RBRACE { $$ = nullptr; }
    | IF LPAREN expression RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE { $$ = nullptr; }
    | WHILE LPAREN expression RPAREN LBRACE statements RBRACE { $$ = nullptr; }
    | PRINT LPAREN expression RPAREN SEMICOLON { $$ = new ASTNode("PRINT", $3, nullptr); }
    | RETURN expression SEMICOLON { $$ = nullptr; }
;

/* ==============================
    ATRIBUIRI
    ============================== */
assignment:
      ID ASSIGN expression
    {
        SymbolInfo* s = currentTable->lookup($1);
        if(!s) { yyerror("Nedeclarat"); exit(1); }
        checkType(s->type, $3->exprType, "Incompatibil");
        $$ = new ASTNode("leaga_de", new ASTNode($1), $3);
    }
    | ID DOT ID ASSIGN expression
    {
        $$ = new ASTNode("leaga_de", new ASTNode($3), $5);
    }
;

/* ==============================
    APEL FUNCTIE
    ============================== */
function_call:
      ID LPAREN call_arguments RPAREN 
      { 
          SymbolInfo* s = currentTable->lookup($1);
          $$ = new ASTNode("OTHER");
          $$->exprType = (s ? s->returnType : T_INT); 
      }
;

/* ==============================
    ARGUMENTE FUNCTIE
    ============================== */
call_arguments:
      /* empty */ { $$ = nullptr; }
    | arg_list { $$ = $1; }
;

arg_list:
      expression { $$ = $1; }
    | arg_list COMMA expression { $$ = $3; }
;

/* ==============================
    EXPRESII
    ============================== */
expression:
      INT_LITERAL { $$ = new ASTNode(to_string($1)); $$->exprType = T_INT; }
    | FLOAT_LITERAL { $$ = new ASTNode(to_string($1)); $$->exprType = T_FLOAT; }
    | STRING_LITERAL { $$ = new ASTNode("\"" + string($1) + "\""); $$->exprType = T_STRING; }
    | BOOL_LITERAL { $$ = new ASTNode($1 == 1 ? "true" : "false"); $$->exprType = T_BOOL; }
    | function_call 
      { 
          $$ = $1; 
      }
    | ID 
      {
        SymbolInfo* s = currentTable->lookup($1);
        if(!s) { yyerror("Nedeclarat"); exit(1); }
        $$ = new ASTNode($1); $$->exprType = s->type;
      }
    | NEW ID LPAREN RPAREN 
      { 
        $$ = new ASTNode("OTHER"); 
        $$->exprType = T_CLASS; 
      }
    | LPAREN expression RPAREN { $$ = $2; }
    | expression PLUS expression  { $$ = new ASTNode("+", $1, $3); $$->exprType = $1->exprType; }
    | expression MINUS expression { $$ = new ASTNode("-", $1, $3); $$->exprType = $1->exprType; }
    | expression MUL expression   { $$ = new ASTNode("*", $1, $3); $$->exprType = $1->exprType; }
    | expression DIV expression   { $$ = new ASTNode("/", $1, $3); $$->exprType = $1->exprType; }
    | expression GT expression    { $$ = new ASTNode(">", $1, $3); $$->exprType = T_BOOL; }
    | expression LT expression    { $$ = new ASTNode("<", $1, $3); $$->exprType = T_BOOL; }
    | expression GEQ expression   { $$ = new ASTNode(">=", $1, $3); $$->exprType = T_BOOL; }
    | expression LEQ expression   { $$ = new ASTNode("<=", $1, $3); $$->exprType = T_BOOL; }
    | expression EQ expression    { $$ = new ASTNode("==", $1, $3); $$->exprType = T_BOOL; }
    | expression AND expression   { $$ = new ASTNode("&&", $1, $3); $$->exprType = T_BOOL; }
    | expression OR expression    { $$ = new ASTNode("||", $1, $3); $$->exprType = T_BOOL; }
;


%%

/* ==============================
    TRATARE ERORI
    ============================== */
void yyerror(const char* s) 
{
    fprintf(stderr, "Eroare la linia %d: %s\n", yylineno, s);
}

