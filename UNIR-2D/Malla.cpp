
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
// Archivo: Malla.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


Malla::~Malla () {
    if (textura != nullptr) {
        textura->cuenta_usos --;
    }
}


void Malla::asigna (Textura * textura) {
    this->textura = textura;
    this->vertices.setPrimitiveType (sf::Triangles);
    textura->cuenta_usos ++;
}


void Malla::define (int triangulos) {
    this->total_vertices = triangulos;
    this->vertices.resize (triangulos * 3);
}


void Malla::asigna (int indice, TrianguloMalla triangulo) {
    assert (0 <= indice && indice < this->total_vertices);
    //
    for (int i = 0; i < 3; ++ i) {
        int vrtx = indice * 3 + i;
        Vector punto = triangulo.puntos [i];
        Vector texel = triangulo.texels [i];
        this->vertices [vrtx].position  = sf::Vector2f {punto.x (), punto.y ()};
        this->vertices [vrtx].texCoords = sf::Vector2f {texel.x (), texel.y ()};
    }
}


void Malla::dibuja (const Transforma & contenedor, Rendidor * rendidor) {
	//
    sf::Transformable objeto {};
	Dibujable::situa (objeto, contenedor, this->m_transforma);
	//
    sf::RenderStates states {};
    states.transform = objeto.getTransform ();
    states.texture = & textura->entidad ();
    //
	rendidor->window->draw (this->vertices, states);
}


