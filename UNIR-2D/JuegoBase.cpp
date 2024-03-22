
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
// Archivo: JuegoBase.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


void JuegoBase::agregaActor (ActorBase * actor) {
    assert (actor != nullptr);
    if (! permiso_actores) {
        throw std::logic_error ("no es posible agregar nuevos actores");
    }
    //
    m_actores.push_back (actor);
    actor->inicia ();
}


void JuegoBase::extraeActor (ActorBase * actor) {
    assert (actor != nullptr);
    if (! permiso_actores) {
        throw std::logic_error ("no es posible extraer el actor");
    }
    //
    actor->termina ();
    std::vector<ActorBase *>::iterator r =  std::find (m_actores.begin (), m_actores.end (), actor);
    m_actores.erase (r);
}


void JuegoBase::extraeActores () {
    if (! permiso_actores) {
        throw std::logic_error ("no es posible extraer los actores");
    }
    //
    for (ActorBase * actor : m_actores) {
        actor->termina ();
    }
    m_actores.clear ();
}


void JuegoBase::actualizaActores (double segundos_tiempo) {
    permiso_actores = false;
    for (ActorBase * actor : m_actores) {
        actor->actualiza (segundos_tiempo);
    }
    permiso_actores = true;
}


void JuegoBase::presentaActores (Rendidor * rendidor) {
    permiso_actores = false;
    //
    int indice_z_minimo = std::numeric_limits <int>::max ();
    for (ActorBase * actor : m_actores) {
        if (actor->m_dibujos.size () > 0) {
            int candidato = actor->m_dibujos [0]->indiceZ ();
            if (candidato < indice_z_minimo) {
                indice_z_minimo = candidato;
            }
        }
        actor->presentados = 0;
    }
    //
    while (true) {
        bool presentar_agotado = true;
        for (ActorBase * actor : m_actores) {
            actor->presenta (rendidor, indice_z_minimo);
            if (actor->presentados < actor->m_dibujos.size ()) {
                presentar_agotado = false;
            }
        }
        if (presentar_agotado) {
            break;
        }
        indice_z_minimo ++;
    }
    //
    permiso_actores = true;
}


void JuegoBase::validaVacio () {
    assert (ActorBase  ::cuenta_instancias == 0);
    assert (Textura    ::cuenta_instancias == 0);
    assert (Fuentes    ::fuentes_cargadas  == 0);
    assert (Dibujable  ::cuenta_instancias == 0);
//    assert (BuzonSonido::cuenta_instancias == 0);
    assert (Sonido     ::cuenta_instancias == 0);
}
