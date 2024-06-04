// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoKBM.cpp
// versión:  1.1  (9-Ene-2023)


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


    void SucesosJuegoKBM::pulsadoEspacio () {
        switch (modo ()->estado ()) {
        case EstadoJuegoKBM::inicioRonda:
        case EstadoJuegoKBM::inicioTurno:
            modo ()->entraInicioJugada ();
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

    void SucesosJuegoKBM::pulsadoEnter () {
        switch (modo ()->estado ()) {
            case EstadoJuegoKBM::inicioJugada:
            case EstadoJuegoKBM::preparacionDesplazamiento:
            case EstadoJuegoKBM::preparacionHabilidadOponente:
            case EstadoJuegoKBM::preparacionHabilidadArea:
                modo ()->pasarTurno();
                break;
        }
        
        unir2d::Teclado::consume (unir2d::Tecla::entrar);
    }

    void SucesosJuegoKBM::pulsadoEscape () {
        SucesosJuegoComun::pulsadoEscape ();
        unir2d::Teclado::consume (unir2d::Tecla::escape);
    }


}



