/**
    @file Primitives.hh
    @brief Especificacio de la classe Primitives
*/

#ifndef PRIMITIVES_HH
#define PRIMITIVES_HH

#include <iostream>
#include <list>
#include <sstream>
#include <string>
using namespace std;

/* 
    classe Primitives
*/

/** 
    @class Primitives
    @brief Representa totes les operacions primitives a evaluar
*/

class Primitives {

private:
    /** @brief Identificador dels valors */
    string s, p, o;
    int n;
    
    /**
        @brief funcio per transformar un string a enter
        \pre s = S
        \post retorna un enter
    */
    
    int stoi(string s);
    
    /**
        @brief funcio per transformar un enter a string
        \pre n = N
        \post retorna un string
    */
    string to_string(int n);
		
public:
    //Constructor
    /**
        @brief Creadora per defecte
        \pre Cert.
        \post El resultat es una Primitiva no inicialitzada
    
    */
    Primitives();
    
    /**
        @brief funcio per sumar el valor de 2 enters en format string
        \pre s = S i p = P
        \post El resultat es la suma entera dels dos strings
    */
    
    string suma(string s, string p);

    /**
        @brief funcio per intercanviar el signe de l'enter en format string
        \pre s = S
        \post El resultat es S amb el signe intercanviat
    */

    string menys(string s);
    
    /**
        @brief funcio per colocar l'enter rebut a la primera posició de la llista
        \pre s = S, p = P
        \post P conté S al principi de la llista
    */
    
    string cons(string s, string p);
    
    /**
        @brief funcio per retornar el primer element d'una llista no buida
        \pre s = S
        \post El resultat es el valor del primer element de S
    */
    
    string head(string s);
    
    /**
        @brief funcio que retorna una llista eliminant el primer element
        \pre s = S
        \poat El resultat es una llista sense el primer element
    */
    
    string tail(string s);
    
    /**
        @brief funcio que retorna 1 si els 2 elements son iguals o 0 si son diferents
        \pre s = S, p = P
        \post Escriu el resultar d'evaluar si son iguals o no S i P
    */
    
    string igual(string s, string p);
    
    /**
        @brief Funcio que retorna 1 si el primer element es mes petit que el segon i 0 al reves
        \pre s = S, p = P
        \post Retorna el resultat d'evaluar si S es mes petit que P
    */
    
    string mes_petit(string s, string p);
    
    /**
        @brief funcio que retorna 1 si x es 0 i 0 si x es 1
        \pre s = S i S es un bolea
        \post retorna un resultat boolea d'evaluar S
    */
    
    string not_b(string s);
    
    /**
        @brief funcio que retorna un bolea a l'evaluar un and
        \pre s = S, p = P
        \post retorna un resultat boolea a l'evaluar S i P
    */
    
    string and_b(string s, string p);
    
    /**
        @brief funcio que retorna 1 si un dels 2 casos es cert, 0 si els 2 son fals
        \pre s = S, p = P
    */
    
    string or_b(string s, string p);
    
};

#endif