// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoEquipo.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    SucesosJuegoEquipo::SucesosJuegoEquipo (JuegoMesaBase * juego, ModoJuegoEquipo * modo) :
        SucesosJuegoComun (juego, modo) { 
    }


    ModoJuegoEquipo * SucesosJuegoEquipo::modo () {
        return static_cast <ModoJuegoEquipo *> (SucesosJuegoComun::modo ());
    }


    void SucesosJuegoEquipo::iniciado () {
        if (modo ()->estado () == EstadoJuegoComun::inicial) {
            modo ()->entraPartida ();
        }
    }


    void SucesosJuegoEquipo::pulsadoEspacio () {
        switch (modo ()->estado ()) {
        case EstadoJuegoEquipo::inicioRonda:
        case EstadoJuegoEquipo::inicioTurno:
            modo ()->entraInicioJugada ();
            break;
        case EstadoJuegoEquipo::marcacionCaminoFicha:
            modo ()->mueveFicha ();
            break;  
        case EstadoJuegoEquipo::habilidadSimpleResultado:
        case EstadoJuegoEquipo::oponenteHabilidadResultado:
        case EstadoJuegoEquipo::areaHabilidadResultado:
            modo ()->asumeHabilidad ();
            break;
        default:
            SucesosJuegoComun::pulsadoEspacio ();
            break;
        }        
        unir2d::Teclado::consume (unir2d::Tecla::espacio);
    }


    void SucesosJuegoEquipo::pulsadoEscape () {
        SucesosJuegoComun::pulsadoEscape ();
        unir2d::Teclado::consume (unir2d::Tecla::escape);
    }


}



