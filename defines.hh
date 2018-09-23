#ifndef DEFINES_HH
#define DEFINES_HH

/**
    @file defines.hh
    @brief Especificació de la classe defines
*/

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <list>
using namespace std;

/*
    * Classe defines
*/

/** 
    @class defines
    @brief Representa el conjunt d'operacions
    per representar les variables d'una calculadora
*/

class defines {

private:
    typedef map <string,string>::iterator mit_var;
    struct funcio {
        list <string> l;
        string expresio;
    };
    typedef map <string,funcio>::iterator mit_op;
    /** @brief Funcions consultores */
    funcio f;
    map <string, string> def_var;
    map <string, string> def_op_sec; 
    map <string, funcio> def_op;   
    string s, p;
    
    /**
        @brief funcio per buidar l'struct 
        \pre: un struct f = F no buit
        \post: un struct F buit
    */
    
    void neteja_funcio(funcio &f);
    
    /**
        @brief funcio booleana per saber si es una variable definida o no
        \pre: s = S
        \post: retorna cert si es una variable definida, altrament fals
    */
    
    bool es_variab(string &s);

public:

    // Constructora
    /**
        @brief Creadora per defecte
        \pre: cert
        \post: El resultat és un paràmetre buit.
    */
    
    defines();
    
    /** 
        @brief Consultor per guardar la variable i un enter 
        en un map
        \pre: ens entra un string (nom de la variable) i un string (valor de la variable) 
        \post: guardem al nostre map var_int 
    */
    
    void definir_var(string &s, string &p);
     
    /**
        @brief Consultor per guardar la variable i l'string de l'expressió
        en un map
        \pre: ens entra un string s = S
        \post:  guardem al nostre map la variable i l'expressio
    */
    
    void definir_operacio(string &s);
    
    /**
        @brief funcio per escriure al canal de sortida la variable i el seu contingut
        \pre: cert
        \post: escriu pel canal de sortida el nom de la variable i el seu valor
    */
    
    void escriu_var();
    
    /**
        @brief funcio per escriure pel canal de sortida el nom de la nova operacio i
        el total de variables
        \pre: cert 
        \post: escriu pel canal de sortida la nova operacio i el total de variables
    */
    
    void escriu_operacio();
    
    /**
        @brief funcio per substituir les variables pel seu valor emmagatzemat
        \pre: s = S
        \post: S amb les variables modificades
    */
    
    void substituir_var(string &s);
    
    /**
        @brief funcio booleana per saber si a l'entrada hi ha alguna variable definida
        \pre: s = S
        \post: retorna cert si hi ha alguna variable definida, altrament fals
    */
    
    bool eval_var(string &s);
    
    /**
        @brief funcio booleana per saber si a l'entrada hi ha alguna nova operacio definida
        \pre: s = S
        \post: retorna cert si hi ha alguna nova operacio definida, altrament fals 
    */
    
    bool es_op(string &s);
    
    /**
        @brief funcionar per substituir les noves operacions definides pel seu contingut
        \pre: s = S
        \post: retorna una expressio amb el contingut de les operacions definides
    */
    
    string eval_def_op(string &s, list<string> &l_op);

};

#endif