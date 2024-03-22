
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
// Archivo: ActorBase.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include <math.h>
#include "UNIR-2D.h"

using namespace unir2d;


void ActorBase::agregaDibujo (Dibujable * dibujo) {
    assert (dibujo != nullptr);
    m_dibujos.push_back (dibujo);
    int indice = static_cast <int> (m_dibujos.size ()) - 1;
    while (true) {
        if (indice < 1) {
            break;
        }
        if (m_dibujos [indice - 1]->indiceZ () <= m_dibujos [indice]->indiceZ ()) {
            break;
        }
        Dibujable * paso =  m_dibujos [indice - 1];
        m_dibujos [indice - 1] =  m_dibujos [indice];
        m_dibujos [indice] = paso;
        indice --;
    }
}


void ActorBase::extraeDibujo (Dibujable * dibujo) {
    assert (dibujo != nullptr);
    std::vector<Dibujable *>::iterator r =  std::find (m_dibujos.begin (), m_dibujos.end (), dibujo);
    if (r != m_dibujos.end ()) {
        m_dibujos.erase (r);
    }
}


void ActorBase::extraeDibujos () {
    m_dibujos.clear ();
}


void ActorBase::inicia () {
}


void ActorBase::termina () {
}


void ActorBase::actualiza (double tiempo_seg) {
}


void ActorBase::presenta (Rendidor * rendidor, int indice_z) {
    while (true) {
        if (this->presentados >= this->m_dibujos.size ()) {
            break;
        }
        Dibujable * dibujo = this->m_dibujos [this->presentados];
        if (dibujo->indiceZ () > indice_z) {
            break;
        }
        if (dibujo->indiceZ () == indice_z) {
            presentados ++;
            if (dibujo->visible ()) {
                dibujo->dibuja (this->m_transforma, rendidor);
            }
        }

    }
    //for (Dibujable * dibujo : this->m_dibujos) {
    //    if (dibujo->indiceZ () == indice_z) {
    //        presentados ++;
    //        if (dibujo->visible ()) {
    //            dibujo->dibuja (this->m_transforma, rendidor);
    //        }
    //    }
    //}
    if (presentados == m_dibujos.size ()) {
        if (diana) {
            dibujaDiana (rendidor);
        }
    }
}


inline sf::Vertex sfmlVertex (Vector v, sf::Color color) {
    return sf::Vertex {sf::Vector2f {v.x (), v.y ()}, color};
}


void ActorBase::dibujaDiana (Rendidor * rendidor) {
    Vector posc = m_transforma.posicion ();
    float  sen  = std::sin (m_transforma.rotacion ());
    float  cos  = std::cos (m_transforma.rotacion ());
    float  lngt = 100;

    Vector pnt_1 {      lngt * cos,       lngt * sen};
    Vector pnt_2 {    - lngt * sen,       lngt * cos};
    Vector pnt_3 {- (lngt-1) * cos, - (lngt-1) * sen};
    Vector pnt_4 {  (lngt-1) * sen, - (lngt-1) * cos};

    constexpr int dim = 8;
    sf::Vertex vertices [dim] {    
            sfmlVertex (posc        , sf::Color::Red),
            sfmlVertex (posc + pnt_1, sf::Color::Red),         
            sfmlVertex (posc        , sf::Color::Green),
            sfmlVertex (posc + pnt_2, sf::Color::Green),
            sfmlVertex (posc        , sf::Color::Yellow),
            sfmlVertex (posc + pnt_3, sf::Color::Yellow),
            sfmlVertex (posc        , sf::Color::Blue),
            sfmlVertex (posc + pnt_4, sf::Color::Blue),
    };

    rendidor->window->draw (vertices, dim, sf::Lines);
}


