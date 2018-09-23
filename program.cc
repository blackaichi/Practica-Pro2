/**
    @mainpage Practica d'una calculadora en format Lisp
    Es construeix un programa modular on gestionarem les operacions
    i on documentem els elements publics i privats
*/

/** 
    @file main.cc
    @brief Programa principal per l'exercici "Calculadora"
*/

#include "calculadora.hh"

/**
    @brief Codi del programa principal
*/

int main() {
    string s, aux;
    calculadora c;
    while (getline (cin, s) and s != "****") {
        c.neteja_operacio();
        if (s != "") {
            c.afegeix_operacio(s);
            aux = " ";
            while (not c.ok_operacio()) {
                getline(cin, s);
                c.afegeix_operacio(aux);
                c.afegeix_operacio(s);
            }
            c.normalitza();
            s = c.consulta_operacio();
            if (c.es_define()) {
                c.soluciona_define();
            }
            else {
                s = c.recursiva(s);
                c.neteja_operacio();
                c.afegeix_operacio(s);
                c.escriure_operacio();
            }
        }
    }
    c.escriu_memoria();
}