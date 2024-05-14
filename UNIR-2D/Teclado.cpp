
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
// Archivo: Teclado.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"
#include <Windows.h>

using namespace unir2d;


void Teclado::configura (Rendidor * rendidor) {
    window = rendidor->window;
    winHandle = rendidor->window->getSystemHandle ();
}


void Teclado::sondea () {
    if (GetFocus () != winHandle) {
        return;
    }
    sondea (Tecla::arriba,    VK_UP);
	sondea (Tecla::abajo,     VK_DOWN);
	sondea (Tecla::izquierda, VK_LEFT);
	sondea (Tecla::derecha,   VK_RIGHT);
	sondea (Tecla::A,         'A');
	sondea (Tecla::S,         'S');
	sondea (Tecla::D,         'D');
	sondea (Tecla::W,         'W');
	sondea (Tecla::entrar,    VK_RETURN);
	sondea (Tecla::espacio,   VK_SPACE);
	sondea (Tecla::escape,    VK_ESCAPE);
}


void Teclado::sondea (Tecla tecla, int virtual_key) {
    SHORT estado = GetKeyState (virtual_key);
    int indice = static_cast <int> (tecla);
    if (estado & 0b10000000) {
        s_pulsada [indice] = true;
    } else {
        s_pulsada   [indice] = false;
        s_consumida [indice] = false;
    }
}


bool Teclado::pulsando (Tecla tecla) {
    int indice = static_cast <int> (tecla);
    if (s_consumida [indice]) {
        return false;
    }
    return s_pulsada [indice];
}


void Teclado::consume (Tecla tecla) {
    int indice = static_cast <int> (tecla);
    s_consumida [indice] = true;
}

bool Teclado::cualquierTecla() {
    sf::Event event;
    while (window->waitEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
            return true;
    }

}