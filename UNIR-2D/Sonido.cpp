
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
// Archivo: Sonido.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


void Sonido::carga (path archivo) {
    es_sonido = true;
    bool bien = sound_buffer.loadFromFile (archivo.string ().c_str ());
    if (! bien) {
        throw std::runtime_error {"archivo de carga de Sonido no encontrado: " + archivo.string ()};
    }
    sound.setBuffer (sound_buffer);
}


void Sonido::abre (path archivo) {
    es_musica = true;
    bool bien = music.openFromFile (archivo.string ().c_str ());
    if (! bien) {
        throw std::runtime_error {"archivo de carga de Sonido no encontrado: " + archivo.string ()};
    }
}


int Sonido::volumen () {
    if (es_sonido) {
        return static_cast <int> (sound.getVolume ());
    }
    if (es_musica) {
        return static_cast <int> (music.getVolume ());
    }
    return 0;
}
        
        
void Sonido::ponVolumen (int valor) {
    if (es_sonido) {
        sound.setVolume (static_cast <float> (valor));
    }
    if (es_musica) {
        music.setVolume (static_cast <float> (valor));
    }
}


bool Sonido::sonando () {
    if (es_musica) {
        return music.getStatus () == sf::SoundSource::Status::Playing;
    }
    return false;
}


void Sonido::suena () {
    if (es_sonido) {
        sound.play ();
    }
    if (es_musica) {
        music.play ();
    }
}


void Sonido::para () {
    if (es_sonido) {
        sound.stop ();
    }
    if (es_musica) {
        music.stop ();
    }
}


void Sonido::repite () {
    if (es_musica) {
        music.setPlayingOffset (sf::seconds(0.0f));
        music.play ();
    }
}




