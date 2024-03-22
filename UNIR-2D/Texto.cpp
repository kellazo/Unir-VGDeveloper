
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
// Archivo: Texto.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


Texto::Texto (const string & fuente) {
    if (! fuentes.tabla_fuentes.contains (fuente)) {
        fuentes.carga (fuente);
    }
    sf::Font * font = fuentes.tabla_fuentes.at (fuente);
    m_texto.setFont (* font);
    fuentes.cuenta_usos ++;
}


Texto::~Texto () {
    fuentes.cuenta_usos --;
    if (fuentes.cuenta_usos == 0) {
        fuentes.descarga ();
    }
}


float Texto::anchura () {
    return this->m_texto.getGlobalBounds ().width;
}


void Texto::dibuja (const Transforma & contenedor, Rendidor * rendidor) {
    Dibujable::situa (this->m_texto, contenedor, this->m_transforma);
    rendidor->window->draw (this->m_texto);

    //sf::Transformable objeto {};
    //Dibujable::situa (objeto, contenedor, this->m_transforma);
    //sf::RenderStates states {};
    //states.transform = objeto.getTransform ();
    //rendidor->window->draw (this->m_texto, states);
}


void Texto::dibuja (Textura * textura) {
    this->m_texto.setPosition (m_transforma.posicion ().x (), m_transforma.posicion ().y ());
    textura->rendible.draw (this->m_texto);

    //sf::Transformable objeto {};
    //Dibujable::situa (objeto, contenedor, this->m_transforma);
    //sf::RenderStates states {};
    //states.transform = objeto.getTransform ();
    //rendidor->window->draw (this->m_texto, states);
}
