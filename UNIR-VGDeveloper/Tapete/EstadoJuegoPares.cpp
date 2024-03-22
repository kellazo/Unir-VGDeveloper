// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoPares.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    EstadoJuegoPares::EstadoJuegoPares (int codigo) :
        EstadoJuegoComun {codigo} {
    }


    void EstadoJuegoPares::transita (const EstadoJuegoPares & destino) {
        valida (destino);
        if (traza_transitos) {
            std::cout << std::endl << this->nombre () << " ===> " << destino.nombre () << std::endl;
        }
        ponCodigo (destino);
    }


    void EstadoJuegoPares::valida (const EstadoJuegoComun & destino) {
        switch (* this) {
        case EstadoJuegoPares::inicial:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioRonda);
            break;
        case EstadoJuegoPares::inicioRonda:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioTurnoNoElegidos          ||
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );
            break;
        case EstadoJuegoPares::inicioTurnoNoElegidos:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioTurnoElegidoUno          ||
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );
            break;
        case EstadoJuegoPares::inicioTurnoElegidoUno:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioTurnoConfirmacion        ||
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );
            break;
        case EstadoJuegoPares::inicioTurnoConfirmacion:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioTurnoNoElegidos          ||
                    destino == EstadoJuegoPares::inicioJugada                   ||
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );
            break;
        case EstadoJuegoPares::marcacionCaminoFicha:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioJugada                   ||
                    destino == EstadoJuegoPares::preparacionDesplazamiento      ||
                    destino == EstadoJuegoPares::marcacionCaminoFicha           ||
                    destino == EstadoJuegoPares::agotadosPuntosAccion           ||
                    destino == EstadoJuegoPares::finalTurno                     ||
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );
            break;
        case EstadoJuegoPares::habilidadSimpleResultado:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioJugada                   ||
                    destino == EstadoJuegoPares::agotadosPuntosAccion           ||
                    destino == EstadoJuegoPares::finalTurno                     ||                    
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );
            break;
        case EstadoJuegoPares::oponenteHabilidadResultado:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioJugada                   ||
                    destino == EstadoJuegoPares::agotadosPuntosAccion           ||
                    destino == EstadoJuegoPares::finalTurno                     ||                    
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );
            break;
        case EstadoJuegoPares::areaHabilidadResultado:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioJugada                   ||
                    destino == EstadoJuegoPares::agotadosPuntosAccion           ||
                    destino == EstadoJuegoPares::finalTurno                     ||                    
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );
            break;
        case EstadoJuegoPares::agotadosPuntosAccion:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioJugada                   ||
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );    
            break;
        case EstadoJuegoPares::finalTurno:
            aserta (destino,
                    destino == EstadoJuegoPares::inicioTurnoNoElegidos          ||
                    destino == EstadoJuegoPares::inicioRonda                    ||
                    destino == EstadoJuegoPares::finalPartida                   ||
                    destino == EstadoJuegoPares::mostrandoAyuda                 ||
                    destino == EstadoJuegoPares::terminal                         );    
            break;
        default:
            EstadoJuegoComun::valida (destino);
            break;
        }
        //
        // por fin:
    }


    const string EstadoJuegoPares::nombre () const {    
        switch (* this) {
        case EstadoJuegoPares::inicioRonda: 
            return "inicioRonda";
        case EstadoJuegoPares::inicioTurnoNoElegidos: 
            return "inicioTurnoNoElegidos";
        case EstadoJuegoPares::inicioTurnoElegidoUno: 
            return "inicioTurnoElegidoUno";
        case EstadoJuegoPares::inicioTurnoConfirmacion: 
            return "inicioTurnoConfirmacion";
        case EstadoJuegoPares::agotadosPuntosAccion: 
            return "agotadosPuntosAccion";
        case EstadoJuegoPares::finalTurno: 
            return "finalTurno";
        default:
            return EstadoJuegoComun::nombre (); 
        }
        return "";
    }


}

