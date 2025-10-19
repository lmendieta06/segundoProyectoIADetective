#include "MotorResolucion.h"
#include <iostream>
#include <vector>

using namespace std;

void MotorResolucion::agregarClausula(const Clausula& c) {
    clausulas.insert(c);
}

ResultadoResolucion MotorResolucion::resolverClausulas(const Clausula& c1, const Clausula& c2) {
    Clausula resolvente;
    bool encontroComplementario = false;
    Literal litComplementario("", false);
    
    // Buscar literales complementarios
    for (const auto& lit1 : c1.literales) {
        for (const auto& lit2 : c2.literales) {
            if (lit1.esComplementario(lit2)) {
                if (encontroComplementario) {
                    return ResultadoResolucion(false, Clausula());
                }
                encontroComplementario = true;
                litComplementario = lit1;
            }
        }
    }
    
    if (!encontroComplementario) {
        return ResultadoResolucion(false, Clausula());
    }
    
    // Crear resolvente
    for (const auto& lit : c1.literales) {
        if (!(lit == litComplementario)) {
            resolvente.literales.insert(lit);
        }
    }
    
    Literal litComp2(litComplementario.nombre, !litComplementario.negado);
    for (const auto& lit : c2.literales) {
        if (!(lit == litComp2)) {
            resolvente.literales.insert(lit);
        }
    }
    
    return ResultadoResolucion(true, resolvente);
}

bool MotorResolucion::demostrarPorRefutacion(const Literal& objetivo) {
    cout << "\n========================================" << endl;
    cout << "    DEMOSTRACION POR REFUTACION" << endl;
    cout << "========================================" << endl;
    cout << "Objetivo: " << objetivo.toString() << endl;
    
    Literal negObjetivo(objetivo.nombre, !objetivo.negado);
    Clausula clausulaNegada;
    clausulaNegada.literales.insert(negObjetivo);
    
    cout << "\nPASO 1: Negar objetivo -> " << clausulaNegada.toString() << endl;
    
    set<Clausula> conjuntoActual = clausulas;
    conjuntoActual.insert(clausulaNegada);
    
    cout << "\nPASO 2: Base de conocimiento:" << endl;
    int i = 1;
    for (const auto& c : conjuntoActual) {
        cout << "  " << i++ << ". " << c.toString() << endl;
    }
    
    set<Clausula> nuevas;
    int iteracion = 1;
    
    while (true) {
        cout << "\n--- Iteracion " << iteracion++ << " ---" << endl;
        
        vector<Clausula> listaClausulas(conjuntoActual.begin(), conjuntoActual.end());
        bool encontroResolvente = false;
        
        for (size_t i = 0; i < listaClausulas.size(); i++) {
            for (size_t j = i + 1; j < listaClausulas.size(); j++) {
                ResultadoResolucion resultado = resolverClausulas(listaClausulas[i], listaClausulas[j]);
                
                if (resultado.exito) {
                    encontroResolvente = true;
                    cout << "  Resolver: " << listaClausulas[i].toString() << endl;
                    cout << "      con: " << listaClausulas[j].toString() << endl;
                    cout << "  Resultado: " << resultado.resolvente.toString() << endl;
                    
                    if (resultado.resolvente.esVacia()) {
                        cout << "\n========================================" << endl;
                        cout << "   CLAUSULA VACIA ENCONTRADA: []" << endl;
                        cout << "========================================" << endl;
                        cout << "\nCONCLUSION: " << objetivo.toString() << " es VERDADERO\n" << endl;
                        return true;
                    }
                    
                    nuevas.insert(resultado.resolvente);
                }
            }
        }
        
        if (!encontroResolvente) {
            cout << "  (Sin nuevas resoluciones)" << endl;
        }
        
        bool hayNuevas = false;
        for (const auto& nueva : nuevas) {
            if (conjuntoActual.find(nueva) == conjuntoActual.end()) {
                hayNuevas = true;
                conjuntoActual.insert(nueva);
            }
        }
        
        if (!hayNuevas) {
            cout << "\n========================================" << endl;
            cout << "   No se generaron nuevas clausulas" << endl;
            cout << "========================================" << endl;
            cout << "\nCONCLUSION: " << objetivo.toString() << " NO SE PUEDE DEMOSTRAR\n" << endl;
            return false;
        }
        
        nuevas.clear();
    }
}