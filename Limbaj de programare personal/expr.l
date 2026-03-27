%{
#include "globals.h"
#include "expr.tab.h" 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
%}

%option noyywrap
%option yylineno

/* Stare speciala pentru comentarii multi-linie */
%x COMMENT

%%

    /* CUVINTE CHEIE - TIPURI */

"piatra_filosofala"     { return INT_TYPE; } /* recunoaste tipul int */
"aur_topit"             { return FLOAT_TYPE; } /* recunoaste tipul float */
"pergament"             { return STRING_TYPE; } /* string */
"clarviziune"           { return BOOL_TYPE; } /* bool */

    /* CUVINTE CHEIE - CONTROL */

"daca_sorteaza"         { return IF; } /* if */
"altfel"                { return ELSE; } /* else */
"cat_e_luna"            { return WHILE; } /* while */
"return"                { return RETURN; } /* return */

    /* STRUCTURA PROGRAMULUI */

"turnul_de_fildes"      { return MAIN_BLOCK; } /* blocul principal (main) */
"incepe_vraja"          { return LBRACE; } /* inceput bloc { */
"sfarseste_vraja"       { return RBRACE; } /* sfarsit bloc } */

    /* CLASE SI OBIECTE */
 
"arcana"                { return CLASS; } /* declarare clasa */
"nou"                   { return NEW; } /* alocare obiect (new) */
"atinge"                { return DOT; } /* operator . */

    /* I/O SI ATRIBUIRE */

"Vorbeste_cu_duhurile"  { return PRINT; } /* instructiune print */
"leaga_de"              { return ASSIGN; } /* operator de atribuire */
"puf_de_pix"            { return SEMICOLON; } /* ; (sfarsit instructiune) */

    /* LITERALI BOOLEENI */

"lumina"                { yylval.int_val = 1; return BOOL_LITERAL; } /* true */
"intuneric"             { yylval.int_val = 0; return BOOL_LITERAL; } /* false */

    /* LITERALI NUMERICI */
    
[0-9]+\.[0-9]+          { yylval.float_val = atof(yytext); return FLOAT_LITERAL; } /* float: cifre.cifre */
[0-9]+                  { yylval.int_val = atoi(yytext); return INT_LITERAL; } /* int: cifre */

    /* LITERALI STRING */   

\"[^\"]*\"              { /* string intre ghilimele */
                            yylval.str = strdup(yytext + 1); 
                            yylval.str[strlen(yylval.str)-1] = '\0'; /* elimina ultimul " */
                            return STRING_LITERAL; 
                        }

    /* OPERATORI LOGICI SI ARITMETICI */

"&&"                     { return AND; } /* AND logic */
"||"                     { return OR; } /* OR logic */
"!"                      { return NOT; } /* NOT */
"=="                     { return EQ; } /* egalitate */
"!="                     { return NEQ; } /* diferit */
"<="                     { return LEQ; } /* <= */
">="                     { return GEQ; } /* >= */
"<"                      { return LT; } //* < */
">"                      { return GT; } /* > */
"+"                      { return PLUS; } /* adunare */
"-"                      { return MINUS; } /* scadere */
"*"                      { return MUL; } /* inmultire */
"/"                      { return DIV; } /* impartire */
"("                      { return LPAREN; } /* ( */
")"                      { return RPAREN; } /* ) */
","                      { return COMMA; } /* , */

    /* IDENTIFICATORI */

[a-zA-Z_][a-zA-Z0-9_]*   { yylval.str = strdup(yytext); return ID; } /* variabile, functii, clase */

    /* SPATII ALBE */

[ \t\r\n]+               { /* ignoram */ } /* ignoram spatii, tab-uri, newline */

    /* COMENTARII MULTI-LINIE */

"/*"                     { BEGIN(COMMENT); } /* inceput comentariu */
<COMMENT>"*/"            { BEGIN(INITIAL); } /* sfarsit comentariu */
<COMMENT>\n              { } /* newline in comentariu */
<COMMENT>.               { } /* orice caracter in comentariu */

    /* COMENTARII SINGLE-LINE */ 

"//".*                   { } /* // comentariu */

    /* CAZ DE EROARE */ 

.                        {  /* caracter necunoscut */
                           fprintf(stderr, "Eroare lex: caracter necunoscut la linia %d: %s\n", yylineno, yytext); 
                           return 0; 
                        }

%%

