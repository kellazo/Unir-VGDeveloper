
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


Imagen::~Imagen () {
    if (textura != nullptr) {
        textura->cuenta_usos --;
    }
}


void Imagen::asigna (Textura * textura) {
    this->textura = textura;
    sprite.setTexture (textura->entidad ());
    textura->cuenta_usos ++;
}


void Imagen::colorea (Color color) {    
    coloreado = true;
    this->color = color;        
}


void Imagen::defineEstampas (int filas, int columnas) {
    assert (filas >= 1);
    assert (columnas >= 1);
    //
    filas_estampas = filas;
    colns_estampas = columnas;
}


void Imagen::seleccionaEstampa (int fila, int columna) {
    fila_seleccion = fila;
    coln_seleccion = columna;
}


void Imagen::dibuja (const Transforma & contenedor, Rendidor * rendidor) {
    if (this->filas_estampas != 1 || this->colns_estampas != 1) {
        int ancho = this->textura->rectg_textura.x / colns_estampas;
        int alto  = this->textura->rectg_textura.y / filas_estampas; 
        int x = ancho * (this->coln_seleccion - 1);
        int y = alto  * (this->fila_seleccion - 1);
        this->sprite.setTextureRect (sf::IntRect (x, y, ancho, alto));    
    }
    Dibujable::situa (this->sprite, contenedor, this->m_transforma);
    if (this->coloreado) {
        this->sprite.setColor (sf::Color (
                this->color.rojo (),
                this->color.verde (),
                this->color.azul (),
                this->color.alfa ()  ));
    }
    //
    rendidor->window->draw (this->sprite);
}


void Imagen::dibuja (Textura * textura) {
    if (this->filas_estampas != 1 || this->colns_estampas != 1) {
        int ancho = textura->rectg_textura.x / this->colns_estampas;
        int alto  = textura->rectg_textura.y / this->filas_estampas; 
        int x = ancho * (coln_seleccion - 1);
        int y = alto  * (fila_seleccion - 1);
        this->sprite.setTextureRect (sf::IntRect (x, y, ancho, alto));    
    }
    sprite.setPosition (this->m_transforma.posicion ().x (), this->m_transforma.posicion ().y ());
    if (this->coloreado) {
        this->sprite.setColor (sf::Color (
                this->color.rojo (),
                this->color.verde (),
                this->color.azul (),
                this->color.alfa ()  ));
    }
    //
    textura->rendible.draw (this->sprite);
}


