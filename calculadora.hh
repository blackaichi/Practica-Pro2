#ifndef CALCULADORA_HH
#define CALCULADORA_HH

/**
    @file calculadora.hh
    @brief Especificació de la classe calculadora
*/

#include "Primitives.hh"
#include "defines.hh"

/*
    * Classe calculadora
*/

/**
    @class calculadora
    @brief Representa el conjunt d'operacions bàsiques
    per representar una calculadora
*/

class calculadora {

private:

    string s, operacio;
    Primitives p;
    defines d;
    
    /**
         @brief funcio per saber si l'string es un valor enter
         \pre s = S
         \post retorna cert si es un enter, altrament fals
    */
    
    bool es_int(string &s) const;
        
    /**
        @brief funcio per saber si l'string es una llista d'enters
        \pre s = S
        \post retorna cert si S es una llista, altrament fals
    */
    
    bool es_llista(string &s) const;
        
    /**
        @brief funcio per saber si l'string es una operacio
        \pre s = S
        \post retorna cert si S es una operacio, altrament fals
    */
    
    bool es_op(string &s);
        
    /**
        @brief funcio per saber si l'string es un boolea 
        \pre s = S
        \post retorna cert si S es un boolea. altrament fals
    */
    
    bool es_bool(string &s) const;
        
    /**
        @brief funcio per saber si l'string es una variable
        \pre Entra el parametre implicit
        \post Retorna cert si es variable, altrament es funcio d'operacio
    */
    
    bool es_var();
    
    /**
        @brief funcio per saber el total d'operacions en l'string
        \pre s = S
        \post retorna el numero total d'operacions
    */
    
    int conta_operacions(string &s);
    
    /**
        @brief funcio per saber si l'string es una llista de llistes
        \pre s = S
        \post retorna cert si es una llista de llista, altrament fals
    */
    
    bool llista_de_llistes(string &s);
    
    /**
        @brief funcio per saber quants parentesis tenim
        \pre s = S
        \post retorna la quantitat de parentesis oberts menys tancats
    */
    
    int parentesis(string &s);
    
    /**
        @brief funcio per saber si compleix que sigui enter, llista d'enter o qualsevol operacio
        \pre s = S
        \post retorna cert si no es ni enter, ni llista d'enter, ni operacions, altrament es fals
    */

    bool no_def(string &s);
    
    /**
        @brief funcio per esborrar els parentesis exteriors
        \pre s = S
        \post retorna S sense els parentesis exteriors
    */
    
    string esborra_parentesis(string &s);

public:

    // Constructora
    /**
        @brief Creadora per defecte
        \pre: cert
        \post: El resultat és un paràmetre buit.
    */
    
    calculadora();
    
    /**
        @brief Consultora per dir si l'string es define o no
        \pre: entra un string
        \post: retornarem 0 si s != "define", 1 si ho es 
    */  
    
    bool es_define();
    
    /**
        @brief Consultora per evaluar parentesis
        \pre: cert
        \post: si la cua te mateix nombre de parentesis oberts que tancats retorna 1, sino 0 
    */ 
    
    bool ok_operacio();
    
    /**
        @brief Operacio per afegir l'string a la cua
        \pre: entren dos strings
        \post: afegeix els strings entrat a la cua 
    */ 
    
    void afegeix_operacio(string &s);
    
    /**
        @brief Operacio per retornar un string de la cua
        \pre: cert
        \post: retorna un string amb els valors de la cua 
    */ 
    
    string consulta_operacio();
    
    /**
        @brief funcio per normalitzar el parametre implicit
        \pre cert
        \post retorna el parametre implicit sense espais de mes
        */
    
    void normalitza();
    
    /** 
        @brief Accio per escriure totes les variables emmagatzemades
        \pre: cert
        \post: escriu totes les variables separades per un salt de linia
    */
    
    void escriu_memoria();
    
    /**
        @brief funcio per buidar el parametre implicit
        \pre el parametre implicit no buit
        \post retorna el paraetre implicit buit
    */

    void neteja_operacio();
    
    /**
        @brief funcio per escriure el parametre implicit
        \pre parametre implicit
        \post Escriu pel canal de sortida el parametre implicit
    */

    void escriure_operacio();
    
    /**
        @brief funcio per recorrer l'string i fer iteracions cada cop que es trobi una nova operacio
        \pre s = S
        \post Retorna el resultat d'evaluar tota l'expressio
    */

    string recursiva(string &s);
    
    /**
        @brief funcio per saber si tractar una variable o nova operacio i cridar a les subfuncions corresponents
        \pre parametre implicit
        \post crida a les subfuncions depenent de si es una variable o una nova operacio
    */

    void soluciona_define();
    
};

#endif