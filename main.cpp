#include "MotorResolucion.h"
#include <iostream>

using namespace std;

void imprimirEncabezado() {
    cout << "\n============================================" << endl;
    cout << "  MOTOR DE INFERENCIA POR RESOLUCION" << endl;
    cout << "        (Sin Variables - Parte 1)" << endl;
    cout << "============================================" << endl;
}

void imprimirMisterio() {
    cout << "\n--------------------------------------------" << endl;
    cout << "   CASO: EL MISTERIO DE LA MANSION" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "\nCONTEXTO:" << endl;
    cout << "El Sr. Blackwood fue encontrado muerto" << endl;
    cout << "en su mansion. Hay tres sospechosos:" << endl;
    cout << "  - El Mayordomo" << endl;
    cout << "  - El Jardinero" << endl;
    cout << "  - La Cocinera" << endl;
}

int main() {
    imprimirEncabezado();
    imprimirMisterio();
    
    MotorResolucion motor;
    
    cout << "\nPISTAS:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "1. Mayordomo en cocina -> NO cometio crimen" << endl;
    cout << "2. Crimen a las 10pm Y Mayordomo NO -> Jardinero O Cocinera" << endl;
    cout << "3. Cocinera preparando cena -> NO cometio crimen" << endl;
    cout << "4. Fue Jardinero -> tijeras manchadas" << endl;
    cout << "5. Tijeras NO manchadas (evidencia)" << endl;
    cout << "6. Mayordomo en cocina (testimonio)" << endl;
    cout << "7. Crimen a las 10pm (forense)" << endl;
    cout << "8. Cocinera preparando cena (testigos)" << endl;
    cout << "\nPREGUNTA: Fue la Cocinera quien cometio el crimen?" << endl;
    
    cout << "\n\n============================================" << endl;
    cout << "   CONVERSION A FORMA NORMAL CONJUNTIVA" << endl;
    cout << "============================================" << endl;
    
    // 1. MayordomoCocina => ~CrimenMayordomo
    Clausula c1;
    c1.literales.insert(Literal("MayordomoCocina", true));
    c1.literales.insert(Literal("CrimenMayordomo", true));
    cout << "\n1. ~MayordomoCocina v ~CrimenMayordomo" << endl;
    motor.agregarClausula(c1);
    
    // 2. (Crimen10pm ^ ~CrimenMayordomo) => (CrimenJardinero v CrimenCocinera)
    Clausula c2;
    c2.literales.insert(Literal("Crimen10pm", true));
    c2.literales.insert(Literal("CrimenMayordomo", false));
    c2.literales.insert(Literal("CrimenJardinero", false));
    c2.literales.insert(Literal("CrimenCocinera", false));
    cout << "2. ~Crimen10pm v CrimenMayordomo v CrimenJardinero v CrimenCocinera" << endl;
    motor.agregarClausula(c2);
    
    // 3. CocineraCena => ~CrimenCocinera
    Clausula c3;
    c3.literales.insert(Literal("CocineraCena", true));
    c3.literales.insert(Literal("CrimenCocinera", true));
    cout << "3. ~CocineraCena v ~CrimenCocinera" << endl;
    motor.agregarClausula(c3);
    
    // 4. CrimenJardinero => TijerasManchadas
    Clausula c4;
    c4.literales.insert(Literal("CrimenJardinero", true));
    c4.literales.insert(Literal("TijerasManchadas", false));
    cout << "4. ~CrimenJardinero v TijerasManchadas" << endl;
    motor.agregarClausula(c4);
    
    // 5. ~TijerasManchadas
    Clausula c5;
    c5.literales.insert(Literal("TijerasManchadas", true));
    cout << "5. ~TijerasManchadas" << endl;
    motor.agregarClausula(c5);
    
    // 6. MayordomoCocina
    Clausula c6;
    c6.literales.insert(Literal("MayordomoCocina", false));
    cout << "6. MayordomoCocina" << endl;
    motor.agregarClausula(c6);
    
    // 7. Crimen10pm
    Clausula c7;
    c7.literales.insert(Literal("Crimen10pm", false));
    cout << "7. Crimen10pm" << endl;
    motor.agregarClausula(c7);
    
    // 8. CocineraCena
    Clausula c8;
    c8.literales.insert(Literal("CocineraCena", false));
    cout << "8. CocineraCena" << endl;
    motor.agregarClausula(c8);
    
    // Demostrar
    bool resultado = motor.demostrarPorRefutacion(Literal("CrimenCocinera", false));
    
    cout << "\n============================================" << endl;
    cout << "            VEREDICTO FINAL" << endl;
    cout << "============================================" << endl;
    
    if (resultado) {
        cout << "\nCASO RESUELTO: La COCINERA es CULPABLE" << endl;
        cout << "\nRazonamiento por eliminacion:" << endl;
        cout << "  - Mayordomo: Tiene coartada (en cocina)" << endl;
        cout << "  - Jardinero: No pudo ser (tijeras limpias)" << endl;
        cout << "  - Cocinera: UNICA sospechosa posible" << endl;
        cout << "\nPor lo tanto, fue la Cocinera.\n" << endl;
    } else {
        cout << "\nNo se pudo demostrar culpabilidad.\n" << endl;
    }
    
    cout << "============================================\n" << endl;
    
    return 0;
}