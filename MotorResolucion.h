#ifndef MOTOR_RESOLUCION_H
#define MOTOR_RESOLUCION_H

#include "Logica.h"
#include <set>
#include <utility>

// Estructura para retornar resultado de resolución
struct ResultadoResolucion {
    bool exito;
    Clausula resolvente;
    
    ResultadoResolucion(bool e, Clausula r) : exito(e), resolvente(r) {}
};

class MotorResolucion {
private:
    set<Clausula> clausulas;
    
public:
    void agregarClausula(const Clausula& c);
    ResultadoResolucion resolverClausulas(const Clausula& c1, const Clausula& c2);
    bool demostrarPorRefutacion(const Literal& objetivo);
};

#endif