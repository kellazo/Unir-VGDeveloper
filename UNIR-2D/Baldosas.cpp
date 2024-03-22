
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
// Archivo: Imagen.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


Baldosas::~Baldosas () {
    if (textura != nullptr) {
        textura->cuenta_usos --;
    }
}


void Baldosas::asigna (Textura * textura) {
    this->textura = textura;
    this->preparado = false;
    textura->cuenta_usos ++;
}


void Baldosas::defineEstampas (int filas, int columnas) {
    assert (filas >= 1);
    assert (columnas >= 1);
    //
    filas_estampas = filas;
    colns_estampas = columnas;
    this->preparado = false;
}


void Baldosas::defineSuperficie (int filas, int columnas) {
    assert (filas >= 1);
    assert (columnas >= 1);
    //
    filas_baldosas = filas;
    colns_baldosas = columnas;
    this->preparado = false;
}


void Baldosas::mapea (const std::vector <uint32_t> & tabla_indices) {
    int total_superf = filas_baldosas * colns_baldosas;
    assert (tabla_indices.size () == total_superf);
    //
    int ancho_estmp = textura->rectg_textura.x / this->colns_estampas;
    int alto__estmp = textura->rectg_textura.y / this->filas_estampas; 
    //
    this->vertices.setPrimitiveType (sf::Quads);
    this->vertices.resize (filas_baldosas * colns_baldosas * 4);
    //
    for (int i = 0; i < this->filas_baldosas; ++ i) {
        for (int j = 0; j < this->colns_baldosas; ++ j) {
            //
            int index_balds = i * colns_baldosas + j;
            int index_estmp = tabla_indices [index_balds];
            int coln__estmp = index_estmp % colns_estampas;  // faltaría sumar 1
            int fila__estmp = index_estmp / colns_estampas;  // faltaría sumar 1
            //
            int index_vertc = index_balds * 4;
            float izqrd, derch, arrba, abajo; 
            //
            izqrd = (float) ( j      * ancho_estmp);
            derch = (float) ((j + 1) * ancho_estmp); 
            arrba = (float) ( i      * alto__estmp);
            abajo = (float) ((i + 1) * alto__estmp); 
            this->vertices [index_vertc    ].position = sf::Vector2f (izqrd, arrba);  
            this->vertices [index_vertc + 1].position = sf::Vector2f (derch, arrba); 
            this->vertices [index_vertc + 2].position = sf::Vector2f (derch, abajo); 
            this->vertices [index_vertc + 3].position = sf::Vector2f (izqrd, abajo); 
            //
            izqrd = (float) ( coln__estmp      * ancho_estmp);
            derch = (float) ((coln__estmp + 1) * ancho_estmp); 
            arrba = (float) ( fila__estmp      * alto__estmp);
            abajo = (float) ((fila__estmp + 1) * alto__estmp); 
            this->vertices [index_vertc    ].texCoords = sf::Vector2f (izqrd, arrba);
            this->vertices [index_vertc + 1].texCoords = sf::Vector2f (derch, arrba);
            this->vertices [index_vertc + 2].texCoords = sf::Vector2f (derch, abajo);
            this->vertices [index_vertc + 3].texCoords = sf::Vector2f (izqrd, abajo);
        }
    }
    //
    this->preparado = true;
}


void Baldosas::dibuja (const Transforma & contenedor, Rendidor * rendidor) {
    assert (this->preparado);
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


