// proyecto: Grupal/Juego
// arhivo:   principal.cpp
// versión:  1.1  (9-Ene-2023)


#include "juego.h"


int main () {
    try {
        std::setlocale (LC_ALL, "es_ES.utf8");
        juego::JuegoMesa * juego = new juego::JuegoMesa {};
        unir2d::Motor    * motor = new unir2d::Motor {};
        while (true) {
            motor->ejecuta (juego);
            if (juego->ejecucion () == unir2d::EjecucionJuego::cancelado) {
                break;
            }
        }
        delete juego;
        delete motor;
    } catch (const std::exception & excepcion) {
        std::cerr << std::endl;
        std::cerr << "********************************************************************************" << std::endl;
        std::cerr << "********************************************************************************" << std::endl;
        std::cerr << std::endl;
        std::cerr << "UNIR-2D :: Juego de Mesa" << std::endl;
        std::cerr << "------------------------" << std::endl;
        std::cerr << std::endl;
        std::cerr << excepcion.what () << std::endl;
        std::cerr << "********************************************************************************" << std::endl;
        std::cerr << "********************************************************************************" << std::endl;
        std::this_thread::sleep_for (std::chrono::milliseconds (5000));
    }
    return 0;    
}
