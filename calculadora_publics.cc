#include "calculadora.hh"

bool calculadora::es_define() {
    string p;
    istringstream flux(operacio);
    flux >> p;
    if (p == "(define") return true;
    return false;
}

bool calculadora::ok_operacio() {
    int cont = 0;
    for (int i = 0; i < operacio.size(); ++i) {
        if (operacio[i] == '(') ++cont;
        if (operacio[i] == ')') --cont;
    }
    if (cont == 0) return true;
    return false;
}

void calculadora::afegeix_operacio(string &s) {
    operacio.append(s);
}

string calculadora::consulta_operacio() {
    return operacio;
}

void calculadora::normalitza() {
	string s, p;
	int i;
    while (operacio[0] == ' ') {
        operacio.erase(0,1);
    }
    while (operacio[operacio.size()-1] == ' ') {
        operacio.erase(operacio.size()-1,1);
    }
    for (int i = 0; i < operacio.size();) {
        if ((operacio[i] == ' ' and operacio[i+1] == ' ') or (operacio[i] == ' ' and operacio[i+1] == ')')) operacio.erase(i,1);
        else if (operacio[i] == '(' and operacio[i+1] == ' ') operacio.erase(i+1,1);
        else ++i;
    }
    istringstream flux(operacio);
    while (flux >> s) {
    	p = s;
    	i = 0;
    	if (s[0] == '-') i = 1;
    	while (s[i] == '0' and isdigit(s[i+1])) s.erase(i,1);
    	if (i == 1 and s[i] == '0') s.erase(0,1);
    	operacio.replace(operacio.find(p),p.size(),s);
    }
}

void calculadora::escriu_memoria() {
    d.escriu_var();
    d.escriu_operacio();
}

void calculadora::neteja_operacio() {
    operacio.clear();
}

void calculadora::escriure_operacio() {
    cout << operacio << endl;
}

string calculadora::recursiva(string &s) {
	string a, b, c, e, aux, op;
	int x, n;
	if (d.eval_var(s)) { 
	    d.substituir_var(s);
	}
	if (no_def(s)) return "indefinit";
	x = conta_operacions(s);
	if (x == 0 or s == "indefinit") { 
	    if (llista_de_llistes(s)) {
	        return "indefinit";
	    }
	    return s;
	}
	else {
    	if (es_llista(s)) {
    		s = esborra_parentesis(s);
    		op.clear();
    		op.push_back('(');
			istringstream flux(s);
    		while (flux >> s and op != "indefinit") {
    			if (es_op(s)) {
			        n = 0;
			        n += parentesis(s);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            s.push_back(' ');
			            s.append(aux);
			        }
			        op.append(recursiva(s));
			        if (op == "(indefinit" or op.find("indefinit") != -1) return "indefinit";
			        op.push_back(' ');
			    }
			    else if (es_int(s)) {
			    	op.append(s);
			        op.push_back(' ');
			    }
			    else return "indefinit";
    		}
    		op.erase(op.size()-1,1);
    		op.push_back(')');
    		if (llista_de_llistes(op)) return "indefinit";
    		return op;
    	}
    	s = esborra_parentesis(s);
	    istringstream flux(s);
	    flux >> s;
	    if (s=="+") {
		    flux >> a;
		    if (es_op(a)) {
		        n = 0;
		        n += parentesis(a);
		        while (n != 0) {
		            flux >> aux;
		            n += parentesis(aux);
		            a.push_back(' ');
		            a.append(aux);
		        }
		        a = recursiva(a);
		    }
		    if (a == "" or not es_int(a)) return "indefinit";
		    flux >> b;
		    if (es_op(b)) {
		        n = 0;
		        n += parentesis(b);
		        while (n != 0) {
		            flux >> aux;
		            n += parentesis(aux);
		            b.push_back(' ');
		            b.append(aux);
		        }
		        b = recursiva(b);
		    }
		    if (b == "" or not es_int(b)) return "indefinit";
		    flux >> c;
		    if (c != "") return "indefinit";
		    return p.suma(a,b);
		}
		else if (s=="-") {
		    flux >> a;
		    if (es_op(a)) {
		        n = 0;
		        n += parentesis(a);
		        while (n != 0) {
		            flux >> aux;
		            n += parentesis(aux);
		            a.push_back(' ');
		            a.append(aux);
		        }
		        a = recursiva(a);
		    }
		    if (a == "" or not es_int(a)) return "indefinit";
		    flux >> b;
		    if (b != "") return "indefinit";
		    return p.menys(a);
		}
	    else if (s=="cons") {
		   	flux >> a;
		    if (es_op(a)) {
		        n = 0;
		        n += parentesis(a);
		        while (n != 0) {
		            flux >> aux;
		            n += parentesis(aux);
		            a.push_back(' ');
		            a.append(aux);
		        }
		        a = recursiva(a);
		    }
		    if (a == "" or not es_int(a)) return "indefinit";
		    flux >> b;
		    if (es_llista(b)) {
		    	n = 0;
		    	n += parentesis(b);
		    	while (n != 0) {
		    		flux >> aux;
		    		n += parentesis(aux);
		    		b.push_back(' ');
		    		b.append(aux);
		    	}
		   		b = esborra_parentesis(b);
		   		op.clear();
		   		op.push_back('(');
		   		istringstream flux (b);
		   		while (flux >> b and op != "indefinit") {
		   			if (es_op(b)) {
				        n = 0;
				        n += parentesis(b);
				        while (n != 0) {
				            flux >> aux;
				            n += parentesis(aux);
				            b.push_back(' ');
				            b.append(aux);
				        }
				        b = recursiva(b);
				        if (not es_int(b) or b == "indefinit") return "indefinit";
				        op.append(b);
				        op.push_back(' ');
				    }
				    else if (es_int(b)) {
				    	op.append(b);
				        op.push_back(' ');
				    }
				    else op = "indefinit";
		   		}
		   		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
		   		if (op != "indefinit") op.push_back(')');
		   		b = op;
		   	}
		    else if (es_op(b)) {
		        n = 0;
		        n += parentesis(b);
		        while (n != 0) {
		            flux >> aux;
		            n += parentesis(aux);
		            b.push_back(' ');
		            b.append(aux);
		        }
		        b = recursiva(b);
		    }
		    if (b == "" or not es_llista(b) or b == "indefinit" or llista_de_llistes(b)) return "indefinit";
		    flux >> c;
		    if (c != "") return "indefinit";
		    return p.cons(a,b);
		}
		else if (s=="tail") {
			    flux >> a;
		    	if (es_llista(a)) {
			    	n = 0;
			    	n += parentesis(a);
			    	while (n != 0) {
			    		flux >> aux;
			    		n += parentesis(aux);
			    		a.push_back(' ');
			    		a.append(aux);
			    	}
		    		a = esborra_parentesis(a);
		    		op.clear();
		    		op.push_back('(');
		    		istringstream flux (a);
		    		while (flux >> a and op != "indefinit") {
		    			if (es_op(a)) {
					        n = 0;
					        n += parentesis(a);
					        while (n != 0) {
					            flux >> aux;
					            n += parentesis(aux);
					            a.push_back(' ');
					            a.append(aux);
					        }
					        a = recursiva(a);
					        if (not es_int(a) or a == "indefinit") return "indefinit";
					        op.append(a);
					        op.push_back(' ');
					    }
					    else if (es_int(a)) {
					    	op.append(a);
					        op.push_back(' ');
					    }
					    else op = "indefinit";
		    		}
		    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
		    		if (op != "indefinit") op.push_back(')');
		    		a = op;
		    	}
			    else if (es_op(a)) {
			        n = 0;
			        n += parentesis(a);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            a.push_back(' ');
			            a.append(aux);
			        }
			        a = recursiva(a);
			    }
			    if (a == "" or not es_llista(a) or a == "()" or llista_de_llistes(a)) return "indefinit";
			    flux >> b;
			    if (b != "") return "indefinit";
			    return p.tail(a);
		    }
	    else if (s=="head") {
    	    flux >> a;
	    	if (es_llista(a)) {
		    	n = 0;
		    	n += parentesis(a);
		    	while (n != 0) {
		    		flux >> aux;
		    		n += parentesis(aux);
		    		a.push_back(' ');
		    		a.append(aux);
		    	}
	    		a = esborra_parentesis(a);
	    		op.clear();
	    		op.push_back('(');
	    		istringstream flux (a);
	    		while (flux >> a and op != "indefinit") {
	    			if (es_op(a)) {
				        n = 0;
				        n += parentesis(a);
				        while (n != 0) {
				            flux >> aux;
				            n += parentesis(aux);
				            a.push_back(' ');
				            a.append(aux);
				        }
				        a = recursiva(a);
				        if (not es_int(a) or a == "indefinit") return "indefinit";
				        op.append(a);
				        op.push_back(' ');
				    }
				    else if (es_int(a)) {
				    	op.append(a);
				        op.push_back(' ');
				    }
				    else op = "indefinit";
	    		}
	    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
	    		if (op != "indefinit") op.push_back(')');
	    		a = op;
	    	}
		    else if (es_op(a)) {
		        n = 0;
		        n += parentesis(a);
		        while (n != 0) {
		            flux >> aux;
		            n += parentesis(aux);
		            a.push_back(' ');
		            a.append(aux);
		        }
		        a = recursiva(a);
		    }
		    if (a == "" or not es_llista(a) or a == "()" or llista_de_llistes(a)) return "indefinit";
		    flux >> b;
		    if (b != "") return "indefinit";
		    return p.head(a);
    	}
	    else if (s=="=") {
	    	    bool enter1 = true;
	    	    bool enter2 = true;
	    	    flux >> a;
			    if (es_llista(a)) {
			    	enter1 = false;
			    	n = 0;
			    	n += parentesis(a);
			    	while (n != 0) {
			    		flux >> aux;
			    		n += parentesis(aux);
			    		a.push_back(' ');
			    		a.append(aux);
			    	}
		    		a = esborra_parentesis(a);
		    		op.clear();
		    		op.push_back('(');
		    		istringstream flux (a);
		    		while (flux >> a and op != "indefinit") {
		    			if (es_op(a)) {
					        n = 0;
					        n += parentesis(a);
					        while (n != 0) {
					            flux >> aux;
					            n += parentesis(aux);
					            a.push_back(' ');
					            a.append(aux);
					        }
					        a = recursiva(a);
					        if (not es_int(a) or a == "indefinit") return "indefinit";
					        op.append(a);
					        op.push_back(' ');
					    }
					    else if (es_int(a)) {
					    	op.append(a);
					        op.push_back(' ');
					    }
					    else op = "indefinit";
		    		}
		    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
		    		if (op != "indefinit") op.push_back(')');
		    		a = op;
		    	}
			    else if (es_op(a)) {
			        n = 0;
			        n += parentesis(a);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            a.push_back(' ');
			            a.append(aux);
			        }
			        a = recursiva(a);
			        if (es_llista(a)) enter1 = false;
			    }
	    	    if (a == "" or (not es_llista(a) and not es_int(a)) or llista_de_llistes(a)) return "indefinit";
			    flux >> b;
			    if (es_llista(b)) {
			    	enter2 = false;
			    	n = 0;
			    	n += parentesis(b);
			    	while (n != 0) {
			    		flux >> aux;
			    		n += parentesis(aux);
			    		b.push_back(' ');
			    		b.append(aux);
			    	}
		    		b = esborra_parentesis(b);
		    		op.clear();
		    		op.push_back('(');
		    		istringstream flux (b);
		    		while (flux >> b and op != "indefinit") {
		    			if (es_op(b)) {
					        n = 0;
					        n += parentesis(b);
					        while (n != 0) {
					            flux >> aux;
					            n += parentesis(aux);
					            b.push_back(' ');
					            b.append(aux);
					        }
					        b = recursiva(b);
					        if (not es_int(b) or b == "indefinit") return "indefinit";
					        op.append(b);
					        op.push_back(' ');
					    }
					    else if (es_int(b)) {
					    	op.append(b);
					        op.push_back(' ');
					    }
					    else op = "indefinit";
		    		}
		    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
		    		if (op != "indefinit") op.push_back(')');
		    		b = op;
		    	}
			    else if (es_op(b)) {
			        n = 0;
			        n += parentesis(b);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            b.push_back(' ');
			            b.append(aux);
			        }
			        b = recursiva(b);
			        if (es_llista(b)) enter2 = false;
			    }
			    if (b == "" or (not es_llista(b) and not es_int(b)) or enter1 != enter2 or llista_de_llistes(b)) return "indefinit";
			    flux >> c;
			    if (c != "") return "indefinit";
			    return p.igual(a,b);
	    	}
	    else if (s=="<") {
	    	    bool enter1 = true;
	    	    bool enter2 = true;
	    	    flux >> a;
			    if (es_llista(a)) {
			    	enter1 = false;
			    	n = 0;
			    	n += parentesis(a);
			    	while (n != 0) {
			    		flux >> aux;
			    		n += parentesis(aux);
			    		a.push_back(' ');
			    		a.append(aux);
			    	}
		    		a = esborra_parentesis(a);
		    		op.clear();
		    		op.push_back('(');
		    		istringstream flux (a);
		    		while (flux >> a and op != "indefinit") {
		    			if (es_op(a)) {
					        n = 0;
					        n += parentesis(a);
					        while (n != 0) {
					            flux >> aux;
					            n += parentesis(aux);
					            a.push_back(' ');
					            a.append(aux);
					        }
					        a = recursiva(a);
					        if (not es_int(a) or a == "indefinit") return "indefinit";
					        op.append(a);
					        op.push_back(' ');
					    }
					    else if (es_int(a)) {
					    	op.append(a);
					        op.push_back(' ');
					    }
					    else op = "indefinit";
		    		}
		    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
		    		if (op != "indefinit") op.push_back(')');
		    		a = op;
		    	}
			    else if (es_op(a)) {
			        n = 0;
			        n += parentesis(a);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            a.push_back(' ');
			            a.append(aux);
			        }
			        a = recursiva(a);
			        if (es_llista(a)) enter1 = false;
			    }
	    	    if (a == "" or (not es_int(a) and not es_llista(a)) or llista_de_llistes(a)) return "indefinit";
			    flux >> b;
			    if (es_llista(b)) {
			    	enter2 = false;
			    	n = 0;
			    	n += parentesis(b);
			    	while (n != 0) {
			    		flux >> aux;
			    		n += parentesis(aux);
			    		b.push_back(' ');
			    		b.append(aux);
			    	}
		    		b = esborra_parentesis(b);
		    		op.clear();
		    		op.push_back('(');
		    		istringstream flux (b);
		    		while (flux >> b and op != "indefinit") {
		    			if (es_op(b)) {
					        n = 0;
					        n += parentesis(b);
					        while (n != 0) {
					            flux >> aux;
					            n += parentesis(aux);
					            b.push_back(' ');
					            b.append(aux);
					        }
					        b = recursiva(b);
					        if (not es_int(b) or b == "indefinit") return "indefinit";
					        op.append(b);
					        op.push_back(' ');
					    }
					    else if (es_int(b)) {
					    	op.append(b);
					        op.push_back(' ');
					    }
					    else op = "indefinit";
		    		}
		    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
		    		if (op != "indefinit") op.push_back(')');
		    		b = op;
		    	}
			    else if (es_op(b)) {
			        n = 0;
			        n += parentesis(b);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            b.push_back(' ');
			            b.append(aux);
			        }
			        b = recursiva(b);
			        if (es_llista(b)) enter2 = false;
			    }
			    if (b == "" or (not es_llista(b) and not es_int(b)) or enter1 != enter2 or llista_de_llistes(b)) return "indefinit";
			    flux >> c;
			    if (c != "") return "indefinit";
			    return p.mes_petit(a,b);
	    	}
	    else if (s=="not") {
	    	    flux >> a;
	    	    if (es_op(a)) {
			        n = 0;
			        n += parentesis(a);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            a.push_back(' ');
			            a.append(aux);
			        }
			        a = recursiva(a);
			    }
	    	    if (not es_bool(a) or a == "") return "indefinit";
	    	    flux >> b;
	    	    if (b != "") return "indefinit";
	    	    return p.not_b(a);
	    	}
	    else if (s=="and") {
	    	    flux >> a;
			    if (es_op(a)) {
			        n = 0;
			        n += parentesis(a);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            a.push_back(' ');
			            a.append(aux);
			        }
			        a = recursiva(a);
			    }
	    	    if (a == "" or not es_bool(a)) return "indefinit";
			    flux >> b;
			    if (es_op(b)) {
			        n = 0;
			        n += parentesis(b);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            b.push_back(' ');
			            b.append(aux);
			        }
			        b = recursiva(b);
			    }
			    if (b == "" or not es_bool(b)) return "indefinit";
			    flux >> c;
			    if (c != "") return "indefinit";
			    return p.and_b(a,b);
	    	}
	    else if (s=="or") {
	    	    flux >> a;
			    if (es_op(a)) {
			        n = 0;
			        n += parentesis(a);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            a.push_back(' ');
			            a.append(aux);
			        }
			        a = recursiva(a);
			    }
	    	    if (a == "" or not es_bool(a)) return "indefinit";
			    flux >> b;
			    if (es_op(b)) {
			        n = 0;
			        n += parentesis(b);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            b.push_back(' ');
			            b.append(aux);
			        }
			        b = recursiva(b);
			    }
			    if (b == "" or not es_bool(b)) return "indefinit";
			    flux >> c;
			    if (c != "") return "indefinit";
			    return p.or_b(a,b);
	    	}
	    else if (s=="if") {
	    	    flux >> a;
			    if (es_op(a)) {
			        n = 0;
			        n += parentesis(a);
			        while (n != 0) {
			            flux >> aux;
			            n += parentesis(aux);
			            a.push_back(' ');
			            a.append(aux);
			        }
			        a = recursiva(a);
			    }
	    	    if (a == "" or not es_bool(a)) return "indefinit";
	    	    if (a == "1") {
	        	    flux >> b;
	    		    if (es_llista(b)) {
				    	n = 0;
				    	n += parentesis(b);
				    	while (n != 0) {
				    		flux >> aux;
				    		n += parentesis(aux);
				    		b.push_back(' ');
				    		b.append(aux);
				    	}
			    		b = esborra_parentesis(b);
			    		op.clear();
			    		op.push_back('(');
			    		istringstream flux (b);
			    		while (flux >> b and op != "indefinit") {
			    			if (es_op(b)) {
						        n = 0;
						        n += parentesis(b);
						        while (n != 0) {
						            flux >> aux;
						            n += parentesis(aux);
						            b.push_back(' ');
						            b.append(aux);
						        }
						        b = recursiva(b);
						        if (not es_int(b) or b == "indefinit") return "indefinit";
						        op.append(b);
						        op.push_back(' ');
						    }
						    else if (es_int(b)) {
						    	op.append(b);
						        op.push_back(' ');
						    }
						    else op = "indefinit";
			    		}
			    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
			    		if (op != "indefinit") op.push_back(')');
			    		b = op;
		    		}
	    		    else if (es_op(b)) {
	    		        n = 0;
	    		        n += parentesis(b);
	    		        while (n != 0) {
	    		            flux >> aux;
	    		            n += parentesis(aux);
	    		            b.push_back(' ');
	    		            b.append(aux);
	    		        }
	    		        b = recursiva(b);
	    		    }
	    		    if (b == "" or (not es_llista(b) and not es_int(b)) or b == "indefinit" or llista_de_llistes(b)) return "indefinit";
	    		    c.clear();
	        	    flux >> c;
	        	    if (c=="") return "indefinit";
	    		    n = 0;
	    		    n += parentesis(c);
	    	    	while (n != 0) {
	    	    		flux >> aux;
	    	    	    n += parentesis(aux);
	    	    	    c.push_back(' ');
	    	    	    c.append(aux);
	    	    	}
	    	    	if (c == "") return "indefinit";
	    		    flux >> e;
	    		    if (e != "") return "indefinit";
	    		    return b;
	    	    }
	    	    else {
	    	    	flux >> b;
	    		    n = 0;
	    		    n += parentesis(b);
	    		    while (n != 0) {
	    		        flux >> aux;
	    		        n += parentesis(aux);
	    		        b.push_back(' ');
	    		        b.append(aux);
	    		    }
	    		    if (b == "") return "indefinit";
	        	    flux >> c;
	    		    if (es_llista(c)) {
				    	n = 0;
				    	n += parentesis(c);
				    	while (n != 0) {
				    		flux >> aux;
			    			n += parentesis(aux);
			    			c.push_back(' ');
			    			c.append(aux);
			    		}
			    		c = esborra_parentesis(c);
			    		op.clear();
			    		op.push_back('(');
			    		istringstream flux (c);
			    		while (flux >> c and op != "indefinit") {
			    			if (es_op(c)) {
						        n = 0;
						        n += parentesis(c);
						        while (n != 0) {
						            flux >> aux;
						            n += parentesis(aux);
						            c.push_back(' ');
						            c.append(aux);
						        }
						        c = recursiva(c);
						        if (not es_int(c) or c == "indefinit") return "indefinit";
						        op.append(c);
						        op.push_back(' ');
						    }
						    else if (es_int(c)) {
						    	op.append(c);
						        op.push_back(' ');
						    }
						    else op = "indefinit";
			    		}
			    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
			    		if (op != "indefinit") op.push_back(')');
			    		c = op;
			    	}
	    		    else if (es_op(c)) {
	    		        n = 0;
	    		        n += parentesis(c);
	    		        while (n != 0) {
	    		            flux >> aux;
	    		            n += parentesis(aux);
	    		            c.push_back(' ');
	    		            c.append(aux);
	    		        }
	    		        c = recursiva(c);
	    		    }
	    		    if (c == "" or (not es_llista(c) and not es_int(c)) or llista_de_llistes(c)) return "indefinit";
	    		    flux >> e;
			    	if (e != "") return "indefinit";
	    		    return c;
	    	    }
	    	}
	    else if (this->d.es_op(s)) {
	    	list<string> l_op;
	    	list<string>:: iterator it_op = l_op.begin();
	    	while (flux >> a) {
				if (es_op(a)) {
				    n = 0;
				    n += parentesis(a);
				    while (n != 0) {
				        flux >> aux;
				        n += parentesis(aux);
				        a.push_back(' ');
				        a.append(aux);
				    }
				    a = recursiva(a);
				}
				else if (es_llista(a)) {
			    	n = 0;
			    	n += parentesis(a);
			    	while (n != 0) {
			    		flux >> aux;
			    		n += parentesis(aux);
			    		a.push_back(' ');
			    		a.append(aux);
			    	}
		    		a = esborra_parentesis(a);
		    		op.clear();
		    		op.push_back('(');
		    		istringstream flux (a);
		    		while (flux >> a and op != "indefinit") {
		    			if (es_op(a)) {
					        n = 0;
					        n += parentesis(a);
					        while (n != 0) {
					            flux >> aux;
					            n += parentesis(aux);
					            a.push_back(' ');
					            a.append(aux);
					        }
					        op.append(recursiva(a));
					        op.push_back(' ');
					    }
					    else if (es_int(a)) {
					    	op.append(a);
					        op.push_back(' ');
					    }
					    else op = "indefinit";
		    		}
		    		if (op[op.size()-1] == ' ') op.erase(op.size()-1,1);
		    		if (op != "indefinit") op.push_back(')');
		    		a = op;
		    	}
				if (a == "" or (not es_int(a) and not es_llista(a)) or llista_de_llistes(a)) return "indefinit";
				l_op.insert(it_op,a);
	    	}
			string fg;
			fg = d.eval_def_op(s,l_op);
			if (no_def(fg)) return "indefinit";
			else {
				return recursiva(fg);
			}
	    }
    }
    return "indefinit";
}

void calculadora::soluciona_define() {
    string nom, valor;
    operacio = esborra_parentesis(operacio);
    operacio.erase(0, 7);
    if (es_var()) {
        istringstream flux(operacio);
        flux >> nom;
        operacio.erase(0,nom.size()+1); 
        operacio = recursiva(operacio);
        valor = operacio;
        if (valor != "indefinit") d.definir_var(nom, valor);
        operacio.clear();
        operacio.append(nom);
        operacio.push_back(' ');
        operacio.append(valor);
        cout << operacio << endl;
    }
    else {
        d.definir_operacio(operacio);
    }
}
