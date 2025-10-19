#ifndef LOGICA_H
#define LOGICA_H

#include <string>
#include <set>
#include <vector>

using namespace std;

// Representa un literal (proposición con o sin negación)
struct Literal {
    string nombre;
    bool negado;
    
    Literal(string n, bool neg = false);
    bool operator==(const Literal& otro) const;
    bool operator<(const Literal& otro) const;
    bool esComplementario(const Literal& otro) const;
    string toString() const;
};

// Representa una cláusula (disyunción de literales)
class Clausula {
public:
    set<Literal> literales;
    
    Clausula();
    Clausula(vector<Literal> lits);
    bool esVacia() const;
    bool operator==(const Clausula& otra) const;
    bool operator<(const Clausula& otra) const;
    string toString() const;
};

#endif