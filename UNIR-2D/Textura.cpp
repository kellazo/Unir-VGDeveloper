
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
// Archivo: Textura.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using std::filesystem::path;
using namespace unir2d;


void Textura::carga (path archivo) {
    if (iniciada) {
        throw std::runtime_error ("iniciada");
    }
    iniciada = true;
    para_rendir = false;
    //
    bool bien = texture.loadFromFile (archivo.string ().c_str ());
    if (! bien) {
        throw std::runtime_error {"archivo de carga de textura no encontrado: " + archivo.string ()};
    }
    //texture.setSmooth (true);
    rectg_textura = texture.getSize ();  
}


void Textura::suaviza () {
    assert (iniciada);
    assert (! para_rendir);
    this->texture.setSmooth (true);
}


void Textura::crea (Vector tamano) {
    if (iniciada) {
        throw std::runtime_error ("iniciada");
    }
    iniciada = true;
    para_rendir = true;
    //
    rectg_textura = sf::Vector2u {(unsigned int) tamano.x (), (unsigned int) tamano.y ()};
    rendible.create (rectg_textura.x, rectg_textura.y);
    rendible.clear ();
    rendida = false;
}
   

void Textura::dibuja (Imagen * imagen) {
    assert (iniciada);
    assert (para_rendir);
    imagen->dibuja (this);
    rendida = false;
}


void Textura::dibuja (Texto * texto) {
    assert (iniciada);
    assert (para_rendir);
    texto->dibuja (this);
    rendida = false;
}


const sf::Texture & Textura::entidad () {
    if (para_rendir) {
        if (! rendida) {
            rendible.display ();
            rendida = true;
        }
        return rendible.getTexture ();
    } else {
        return texture;
    }
}






