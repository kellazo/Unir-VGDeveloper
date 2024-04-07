// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoKBM.cpp
// versión:  1.1  (7-Abr-2024)


#include "tapete.h"


namespace tapete {


    SucesosJuegoKBM::SucesosJuegoKBM (JuegoMesaBase * juego, ModoJuegoKBM * modo) :
        SucesosJuegoComun (juego, modo) { 
    }


    ModoJuegoKBM * SucesosJuegoKBM::modo () {
        return static_cast <ModoJuegoKBM *> (SucesosJuegoComun::modo ());
    }


    void SucesosJuegoKBM::iniciado () {
        if (modo ()->estado () == EstadoJuegoComun::inicial) {
            modo ()->entraPartida ();
        }
    }


    void SucesosJuegoKBM::personajeSeleccionado (ActorPersonaje * personaje) {
        switch (modo ()->estado ()) {
        case EstadoJuegoKBM::inicioTurnoNoElegido:
            modo ()->eligePersonaje (personaje);
            break;
        default:
            SucesosJuegoComun::personajeSeleccionado (personaje);
            break;
        }
    }


    // si estamos en 'inicioTurnoConfirmacion' y el suceso es 'actuanteSeleccionado':
    // se inserta el suceso previo 'pulsadoEspacio'
    void SucesosJuegoKBM::actuanteSeleccionado (LadoTablero lado) {
        assert (lado != LadoTablero::nulo);
        if (modo ()->estado () == EstadoJuegoKBM::inicioTurnoConfirmacion) {
            //-----------------------------------------------------------
            // se efectuan dos transiciones seguidas:
            if (modo ()->ladoEquipoActual () != lado) {
                return;
            }
            modo ()->entraInicioJugada ();
            modo ()->entraAccionDesplazam ();
            return;
            //-----------------------------------------------------------
        }
        SucesosJuegoComun::actuanteSeleccionado (lado);
    }


    // si estamos en 'inicioTurnoConfirmacion' y el suceso es 'habilidadSeleccionada':
    // se inserta el suceso previo 'pulsadoEspacio'
    void SucesosJuegoKBM::habilidadSeleccionada (LadoTablero lado, int indice_habilidad) {
        assert (lado != LadoTablero::nulo);
        if (modo ()->estado () == EstadoJuegoKBM::inicioTurnoConfirmacion) {
            //-----------------------------------------------------------
            // se efectuan dos transiciones seguidas:
            if (modo ()->ladoEquipoActual () != lado) {
                return;
            }
            if (indice_habilidad >= modo ()->personajeElegido (lado)->habilidades ().size ()) {
                return;
            }
            modo ()->entraInicioJugada ();
            modo ()->entraAccionHabilidad (indice_habilidad);
            return;
            //-----------------------------------------------------------
        }
        SucesosJuegoComun::habilidadSeleccionada (lado, indice_habilidad);
    }


    void SucesosJuegoKBM::pulsadoEspacio () {
        switch (modo ()->estado ()) {
        case EstadoJuegoKBM::inicioRonda:
            modo ()->entraTurnoEleccion ();
            break;
        case EstadoJuegoKBM::inicioTurnoConfirmacion:
            modo ()->entraInicioJugada ();
            break;
        case EstadoJuegoKBM::agotadosPuntosAccion:
            modo ()->ignoraPersonajeAgotado ();
            break;
        case EstadoJuegoKBM::marcacionCaminoFicha:
            modo ()->mueveFicha ();
            break;  
        case EstadoJuegoKBM::habilidadSimpleResultado:
        case EstadoJuegoKBM::oponenteHabilidadResultado:
        case EstadoJuegoKBM::areaHabilidadResultado:
            modo ()->asumeHabilidad ();
            break;
        default:
            SucesosJuegoComun::pulsadoEspacio ();
            break;
        }        
        unir2d::Teclado::consume (unir2d::Tecla::espacio);
    }


    void SucesosJuegoKBM::pulsadoEscape () {
        switch (modo ()->estado ()) {
        case EstadoJuegoKBM::inicioTurnoConfirmacion:
            modo ()->revierteInicioTurno ();
            break;
        default:
            SucesosJuegoComun::pulsadoEscape ();
            break;
        }
        unir2d::Teclado::consume (unir2d::Tecla::escape);
    }


}



