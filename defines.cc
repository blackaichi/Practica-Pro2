#include "defines.hh"

defines::defines() {}

void defines::neteja_funcio(funcio &f) {
    f.l.clear();
    f.expresio.clear();
}

bool defines::es_variab(string &s) {
    string p = s;
    if (p[0] == '(') p.erase(0,1);
    if (p[p.size()-1] == ')') p.erase(p.size()-1,1);
    if (def_var.find(p) != def_var.end()) return true;
    else return false;
}

void defines::definir_var(string &s, string &p) {
    def_var[s] = p;
}

void defines::definir_operacio(string &s) {
    funcio f;
    neteja_funcio(f);
    list<string>::iterator it = f.l.begin();
    bool trobat=false;
    istringstream flux(s);
    string nom;
    flux >> nom;
    string var;
    while (flux >> var and !trobat) {
        if (var[0]=='(') var.erase(0,1);
    	if (var[var.size()-1]==')') {
			trobat=true; 
			var.erase(var.size()-1,1);
		}
		if (var != "") {
		    f.l.insert(it,var);
		}
    }
	string g; 
	f.expresio.append(var);
	if (var[0] == '(') {
    	f.expresio.push_back(' ');
    	flux >> g;
    	f.expresio.append(g);
    	while (flux >> g) {
    	    f.expresio.push_back(' ');
    	    f.expresio.append(g);
    	}
	}
	def_op[nom]=f;
	cout << nom << " #" << f.l.size() << endl;
}

void defines::escriu_var() {
    cout << "Variables:" << endl;
    for (mit_var it = def_var.begin(); it != def_var.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
}

void defines::escriu_operacio() {
    cout << "Operacions:" << endl;
	mit_op it1 = def_op.begin();
	for (; it1 != def_op.end(); ++it1) {
		int i = it1->second.l.size();
		cout << it1->first  << " #" << i << endl;
    }
}

void defines::substituir_var(string &s) {
    mit_var itf;
    int x, n = 0;
    string p, aux;
    p = s;
    for (int i = 0; i < p.size();) {
        if (p[i] == '(' or p[i] == ')') p.erase(i,1);
        else ++i;
    }
    istringstream flux(p);
    while (flux>>p) {
        if (es_variab(p)) {
    		itf = def_var.find(p);
    		if (itf != def_var.end()) { 
    			x = s.find(itf->first,n);
    			s = s.replace(x,itf->first.size(),itf->second);
    		}
		    else s = "indefinit";
        }
        n = s.find(' ',n+1);
	}
}

bool defines::eval_var(string &s) {
    string p = s;
    for (int i = 0; i < p.size();) {
        if (p[i] == '(' or p[i] == ')') p.erase(i,1);
        else ++i;
    }
    istringstream flux(p);
    while (flux>>p) {
        if (es_variab(p)) {
            return true;
        }
    }
    return false;
}

bool defines::es_op(string &s) {
    mit_op it = def_op.find(s);
    if (it != def_op.end()) return true;
    return false;
}

string defines::eval_def_op(string &s, list<string> &l_op) {
    string t, edx;
    list<string> l1; 
    map<string,funcio>::iterator it = def_op.find(s);
    if (it != def_op.end()) {
        t = it->second.expresio;
        edx = it->second.expresio;
        l1 = it->second.l;
    }
    if (l1.size() != l_op.size()) return "indefinit";
    list<string>::iterator itl = l1.begin();
    list<string>::iterator it_op = l_op.begin();
    for (; itl != l1.end(); ++itl) {
        def_op_sec[*itl]=*it_op;
        ++it_op;
    }
    string g = edx;
    
    for (int i = 0; i < edx.size();) {
        if (edx[i] == '(' or edx[i] == ')') edx.erase(i,1);
        else ++i;
    }
    cerr << "estic?1" << endl;
	int n;
	string l;
    for (mit_var itf = def_op_sec.begin(); itf != def_op_sec.end(); ++itf) {
    	istringstream f(edx);
        n = 0;
        bool b = false;
        while (f >> l and not b) {
            if (l == itf->first) b = true;
            cerr << "l: " << l << ' ' << "itf" << itf->first << endl;
        }
        cerr << "entrem aqui//////" << endl;
        if (not b) cerr << "var no trobada" << endl;
        while (n != -1 and b) {
            n = g.find(itf->first,n);
            if (n == 0 and (g[n+itf->first.size()] == 0 or g[n+itf->first.size()] == 32 or g[n+itf->first.size()] == 40 or g[n+itf->first.size()] == 41)) {
                cerr << "1" << endl;
                n = g.find(itf->first,n);
                cerr << "n: " << n << ' ' << itf->first.size() << endl;
                g = g.replace(n,itf->first.size(),itf->second);
            }
            else if ((g[n+itf->first.size()] == 0 or g[n+itf->first.size()] == 32 or g[n+itf->first.size()] == 40 or g[n+itf->first.size()] == 41) and (g[n-1] == 0 or g[n-1] == 32 or g[n-1] == 40 or g[n-1] == 41)) {
                cerr << "2" << endl;
                n = g.find(itf->first,n);
                cerr << "n: " << n << ' ' << itf->first.size() << endl;
                g = g.replace(n,itf->first.size(),itf->second);
                cerr << "explota" << endl;
            }
            else if (n == g.size()-(itf->first.size()) and (g[n-1] == 0 or g[n-1] == 32 or g[n-1] == 40 or g[n-1] == 41)) {
                cerr << "3" << endl;
                n = g.find(itf->first,n);
                cerr << "n: " << n << ' ' << itf->first.size() << endl;
                g = g.replace(n,itf->first.size(),itf->second);
            }
            n = g.find(itf->first,n+1);
        }
    }
 
    cerr << "estic?2" << endl;
 
    def_op_sec.clear();
    return g;
}
