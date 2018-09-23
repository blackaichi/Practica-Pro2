#include "Primitives.hh"

Primitives::Primitives() {}

int Primitives::stoi(string s) {
	istringstream f(s);
	int n;
	f >> n;
	return n;
}

string Primitives::to_string(int n) {
	ostringstream f;
	f << n;
	return f.str();
}

string Primitives::suma(string s, string p) {
	int n = stoi(s) + stoi(p);
	return to_string(n);
}

string Primitives::menys(string s) {
	int n = 0 - stoi(s);
	return to_string(n);
}

string Primitives::cons(string s, string p) {
	string o;
	o.push_back('(');
	o.append(s);
	if (p[0] == '(') p.erase(0,1);
	if (p[p.size() - 1] == ')') p.erase(p.size() - 1, 1);
	if (p != "") o.push_back(' ');
	o.append(p);
	o.push_back(')');
	return o;
}

string Primitives::head(string s) {
	if (s.find(' ') > s.find(')')) return s.substr(1, s.find(')')-1);
	return s.substr(1, s.find(' ')-1);
}

string Primitives::tail(string s) {
	if (s.find(' ') > s.find(')')) return s.erase(1, s.find(')')-1);
	else return s.erase(1, s.find(' '));
}

string Primitives::igual(string s, string p) {
	if (s == p) return "1";
	return "0";
}

string Primitives::mes_petit(string s, string p) {
	list<int> l1,l2;
	if (s[0] != '(') {
		if (stoi(s) < stoi(p)) return "1";
		return "0";
	}
	if (s[0] == '(') s.erase(0,1);
	if (s[s.size() - 1] == ')') s.erase(s.size() - 1, 1);
	if (p[0] == '(') p.erase(0,1);
	if (p[p.size() - 1] == ')') p.erase(p.size() - 1, 1);
	istringstream f(s);
	istringstream g(p);
	while (f >> s) {
		l1.push_back(stoi(s));
	}
	while (g >> p) {
		l2.push_back(stoi(p));
	}
	if (l1 < l2) return "1";
	return "0";
}

string Primitives::not_b(string s) {
	if (s == "1") return "0";
	return "1";
}

string Primitives::and_b(string s, string p) {
	if (s == "1" and p == "1") return "1";
	return "0";
}

string Primitives::or_b(string s, string p) {
	if (s == "0" and p == "0") return "0";
	return "1";
}
