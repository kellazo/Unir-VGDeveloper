
// UNIR-2D :: Motor de juego mínimo para la programación de microjuegos en 2 dimensiones.
// 
// Copyright (C) 2022 UNIR-Universidad Internacional de La Rioja. 
// Todos los derechos reservados. 
// El sofware se entrega solo para uso educativo, sin ninguna garantía de adecuación para ningún 
// proposito particular.
// 
// Bibliotecas de código usadas: 
//   1) SFML - Simple and Fast Multimedia Library. Licencia: https://www.sfml-dev.org/license.php  
// 
// Archivo: Rendidor.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


/// @cond


void Rendidor::abre (JuegoBase * juego) {
    Vector posicion;
    Vector tamano;
    juego->regionVentana (posicion, tamano);        
    window = new sf::RenderWindow (
                sf::VideoMode((unsigned) tamano.x (), 
                              (unsigned) tamano.y () ), 
                juego->tituloVentana (),
                sf::Style::Titlebar | sf::Style::Close);
    window->setPosition (sf::Vector2i ((int) posicion.x (), (int) posicion.y ())); 
    //window->setVerticalSyncEnabled (true);
}


void Rendidor::cierra () {
    window->close();
}


void Rendidor::limpia () {
    window->clear(sf::Color(150, 150, 150, 255));
}


void Rendidor::muestra () {
    window->display();
}


bool Rendidor::cerrado () {
    sf::Event event;
    while (window->pollEvent (event)) {
        if (event.type == sf::Event::Closed) {
            return true;
        }
        //if (event.type == sf::Event::KeyPressed) {
        //    if (event.key.code == sf::Keyboard::Escape) {
        //        return true;
        //    }
        //}
    }
    return false;
}


/// @endcond

