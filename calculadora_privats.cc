#include "calculadora.hh"

calculadora::calculadora() {}

bool calculadora::es_int(string &s) const {
    for (int i = 0; i < s.size(); ++i) {
        if (not isdigit(s[i]) and s[i] != '-') return false; 
    }
    return true;
}

bool calculadora::es_llista(string &s) const {
    if (s[0] == '(') {
        if (s[1] == '(' or (s[1] == '-' and isdigit(s[2])) or isdigit(s[1]) or s[1] == ')') return true;
    }
    return false;
}

bool calculadora::es_op(string &s) {
	string t;
    if (s[0] == '(') {
        t = s.substr(1,s.find(' ')-1);
        if (t[t.size()-1] == ')') t.erase(t.size()-1, 1);
    }
    else t = s;
    if (t == "+") return true;
    else if (t == "-") return true;
    else if (t == "=") return true;
    else if (t == "<") return true;
    else if (t == "cons") return true;
    else if (t == "head") return true;
    else if (t == "tail") return true;
    else if (t == "not") return true;
    else if (t == "and") return true;
    else if (t == "or") return true;
    else if (t == "if") return true;
    else if (d.es_op(t)) return true;
    return false;
}

bool calculadora::es_bool(string &s) const {
    if (s== "0" or s== "1") return true;
    else return false;
}

bool calculadora::es_var() {
    int nucli = 0;
    int parentesi = 0;
    string p;
    istringstream flux(operacio);
    while (flux >> p) {
        parentesi += parentesis(p);
        if (parentesi == 0) ++nucli;
    }
    if (nucli == 2) return true;
    return false;
}

int calculadora::conta_operacions(string &s) {
	int x = 0, y;
	string p = s;
	istringstream flux(p);
	while (flux >> p) {
	    y = p.size()-1;
		while (p[y] == ')') p.erase(y,1);
		while (p[0] == '(') p.erase(0,1);
    	if (es_op(p)) {
    		++x;
    	}
	}
	return x;
}

bool calculadora::llista_de_llistes(string &s) {
	int x = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '(') ++x;
	}
	if (x > 1) return true;
	return false;
}

int calculadora::parentesis(string &s) {
    int x = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') ++x;
        else if (s[i] == ')') --x;
    }
    return x;
}

bool calculadora::no_def(string &s) {
    string p = s;
	for (int i = 0; i < p.size();) {
		if (p[i] == '(' or p[i] == ')') p.erase(i,1);
		else ++i;
	}
	istringstream flux(p);
	while (flux >> p) {
		if ((not es_int(p) and not es_llista(p) and not es_op(p))) return true;
	}
	return false;
}

string calculadora::esborra_parentesis(string &s) {
    if (s[0] == '(') s.erase(0,1);
    if (s[s.size()-1] == ')') s.erase(s.size()-1, 1);
    return s;
}
