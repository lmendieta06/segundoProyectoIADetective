#include "Logica.h"

Literal::Literal(string n, bool neg) : nombre(n), negado(neg) {}

bool Literal::operator==(const Literal& otro) const {
    return nombre == otro.nombre && negado == otro.negado;
}

bool Literal::operator<(const Literal& otro) const {
    if (nombre != otro.nombre) return nombre < otro.nombre;
    return negado < otro.negado;
}

bool Literal::esComplementario(const Literal& otro) const {
    return nombre == otro.nombre && negado != otro.negado;
}

string Literal::toString() const {
    return (negado ? "~" : "") + nombre;
}

Clausula::Clausula() {}

Clausula::Clausula(vector<Literal> lits) {
    for (const auto& lit : lits) {
        literales.insert(lit);
    }
}

bool Clausula::esVacia() const {
    return literales.empty();
}

bool Clausula::operator==(const Clausula& otra) const {
    return literales == otra.literales;
}

bool Clausula::operator<(const Clausula& otra) const {
    return literales < otra.literales;
}

string Clausula::toString() const {
    if (esVacia()) return "[]";
    
    string resultado = "{";
    bool primero = true;
    for (const auto& lit : literales) {
        if (!primero) resultado += " v ";
        resultado += lit.toString();
        primero = false;
    }
    resultado += "}";
    return resultado;
}