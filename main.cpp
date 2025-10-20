#include "MotorResolucion.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Imprime encabezado del programa
void imprimirEncabezado() {
    cout << "\n============================================" << endl;
    cout << "  MOTOR DE INFERENCIA POR RESOLUCION" << endl;
    cout << "        (Sin Variables - Entrada Generica)" << endl;
    cout << "============================================" << endl;
}

// Funcion auxiliar: recorta espacios al inicio y final
static inline string trim(const string &s) {
    auto b = s.find_first_not_of(" \t\r\n");
    if (b==string::npos) return "";
    auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e-b+1);
}

// Parsea un token individual a Literal.
// ejemplos de token: "~A", "B", "C"
Literal parseTokenToLiteral(const string &token) {
    string t = trim(token);
    bool neg = false;
    if (!t.empty() && t[0] == '~') {
        neg = true;
        t = trim(t.substr(1));
    }
    return Literal(t, neg);
}

// Parsea una linea como: "~A v B v C" o "A" a una Clausula
Clausula parseLineToClausula(const string &line) {
    Clausula c;
    string s = line;
    // normaliza separadores: '|' -> 'v'
    for (char &ch : s) if (ch == '|') ch = 'v';
    stringstream ss(s);
    string token;
    while (getline(ss, token, 'v')) {
        string tok = trim(token);
        if (tok.empty()) continue;
        c.literales.insert(parseTokenToLiteral(tok));
    }
    return c;
}

// Carga clausulas desde un stream (archivo o stdin).
// Se ignoran lineas vacias o que empiecen con '#'
vector<Clausula> loadClausesFromStream(istream &in) {
    vector<Clausula> clauses;
    string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;
        clauses.push_back(parseLineToClausula(line));
    }
    return clauses;
}

int main(int argc, char *argv[]) {
    imprimirEncabezado();

    MotorResolucion motor;

    cout << "Modo: lectura de una clausula por linea" << endl;
    cout << "Formato de literal: '~Nombre' o 'Nombre'. Separador de literales: 'v' o '|'." << endl;
    cout << "Lineas vacias o que empiezan con '#' se ignoran." << endl;
   
    vector<Clausula> clauses;

    // Si se pasa un argumento, se interpreta como nombre de archivo de clausulas
    if (argc > 1) {
        ifstream fin(argv[1]);
        if (!fin) {
            cerr << "No se pudo abrir archivo: " << argv[1] << endl;
            return 1;
        }
        clauses = loadClausesFromStream(fin);
    } else {
        // Modo interactivo: leer clausulas desde stdin hasta una linea vacia
        cout << "Introduce clausulas (termina con linea vacia o Ctrl+Z/Enter):" << endl;
        string line;
        ostringstream buf;
        while (true) {
            if (!getline(cin, line)) break;
            if (trim(line).empty()) break;
            buf << line << '\n';
        }
        istringstream inbuf(buf.str());
        clauses = loadClausesFromStream(inbuf);
    }

    // Mostrar y agregar clausulas al motor
    cout << "\nClausulas leidas: " << clauses.size() << endl;
    for (size_t i = 0; i < clauses.size(); ++i) {
        cout << i+1 << ". ";
        bool first = true;
        for (const Literal &lit : clauses[i].literales) {
            if (!first) cout << " v ";
            first = false;
            if (lit.negado) cout << "~";
            cout << lit.nombre;
        }
        cout << endl;
        motor.agregarClausula(clauses[i]);
    }

    // Pedir la sentencia (consulta) a demostrar
    cout << "\nIntroduzca la sentencia a demostrar: ";
    string queryLine;
    if (!getline(cin, queryLine) || trim(queryLine).empty()) {
        cerr << "No se proporciono consulta. Abortando." << endl;
        return 1;
    }
    Clausula qcl = parseLineToClausula(queryLine);
    if (qcl.literales.empty()) {
        cerr << "Consulta invalida." << endl;
        return 1;
    }
    // Tomar la primera literal como consulta
    Literal query = *qcl.literales.begin();

    // Ejecuta la demostracion por refutacion en el motor
    bool resultado = motor.demostrarPorRefutacion(query);

    cout << "\n============================================" << endl;
    cout << "            VEREDICTO FINAL" << endl;
    cout << "============================================" << endl;

    if (resultado) {
        cout << "\nResultado: La sentencia fue demostrada" << endl;
    } else {
        cout << "\nResultado: No se pudo demostrar la sentencia" << endl;
    }

    cout << "============================================\n" << endl;
    return 0;
}
