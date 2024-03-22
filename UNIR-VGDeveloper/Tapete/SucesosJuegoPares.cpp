// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoPares.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    SucesosJuegoPares::SucesosJuegoPares (JuegoMesaBase * juego, ModoJuegoPares * modo) :
        SucesosJuegoComun (juego, modo) { 
    }


    ModoJuegoPares * SucesosJuegoPares::modo () {
        return static_cast <ModoJuegoPares *> (SucesosJuegoComun::modo ());
    }


    void SucesosJuegoPares::iniciado () {
        if (modo ()->estado () == EstadoJuegoComun::inicial) {
            modo ()->entraPartida ();
        }
    }


    void SucesosJuegoPares::personajeSeleccionado (ActorPersonaje * personaje) {
        switch (modo ()->estado ()) {
        case EstadoJuegoPares::inicioTurnoNoElegidos:
            modo ()->eligePrimerPersonaje (personaje);
            break;
        case EstadoJuegoPares::inicioTurnoElegidoUno:
            modo ()->eligeSegundoPersonaje (personaje);
            break;
        default:
            SucesosJuegoComun::personajeSeleccionado (personaje);
            break;
        }
    }


    void SucesosJuegoPares::pulsadoEspacio () {
        switch (modo ()->estado ()) {
        case EstadoJuegoPares::inicioRonda:
            modo ()->entraTurnoEleccion ();
            break;
        case EstadoJuegoPares::inicioTurnoConfirmacion:
            modo ()->entraInicioJugada ();
            break;
        case EstadoJuegoPares::agotadosPuntosAccion:
            modo ()->ignoraPersonajeAgotado ();
            break;
        case EstadoJuegoPares::marcacionCaminoFicha:
            modo ()->mueveFicha ();
            break;  
        case EstadoJuegoPares::habilidadSimpleResultado:
        case EstadoJuegoPares::oponenteHabilidadResultado:
        case EstadoJuegoPares::areaHabilidadResultado:
            modo ()->asumeHabilidad ();
            break;
        case EstadoJuegoPares::finalTurno:
            modo ()->reiniciaTurno ();
            break;
        default:
            SucesosJuegoComun::pulsadoEspacio ();
            break;
        }        
        unir2d::Teclado::consume (unir2d::Tecla::espacio);
    }


    void SucesosJuegoPares::pulsadoEscape () {
        switch (modo ()->estado ()) {
        case EstadoJuegoPares::inicioTurnoConfirmacion:
            modo ()->revierteInicioTurno ();
            break;
        default:
            SucesosJuegoComun::pulsadoEscape ();
            break;
        }
        unir2d::Teclado::consume (unir2d::Tecla::escape);
    }


}


