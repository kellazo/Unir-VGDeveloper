// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoLibreDoble.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    EstadoJuegoLibreDoble::EstadoJuegoLibreDoble (int codigo) :
        EstadoJuegoComun {codigo} {
    }


    void EstadoJuegoLibreDoble::transita (const EstadoJuegoLibreDoble & destino) {
        valida (destino);
        if (traza_transitos) {
            std::cout << std::endl << this->nombre () << " ===> " << destino.nombre () << std::endl;
        }
        ponCodigo (destino);
    }


    void EstadoJuegoLibreDoble::valida (const EstadoJuegoComun & destino) {
        switch (* this) {
        case EstadoJuegoLibreDoble::inicial:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioRonda);
            break;
        case EstadoJuegoLibreDoble::inicioRonda:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoLibreDoble::mostrandoAyuda            ||
                    destino == EstadoJuegoLibreDoble::terminal                    );
            break;
        case EstadoJuegoLibreDoble::inicioTurnoNoElegido:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioTurnoConfirmacion   ||
                    destino == EstadoJuegoLibreDoble::mostrandoAyuda            ||
                    destino == EstadoJuegoLibreDoble::terminal                    );
            break;
        case EstadoJuegoLibreDoble::inicioTurnoConfirmacion:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoLibreDoble::inicioJugada              ||
                    destino == EstadoJuegoLibreDoble::mostrandoAyuda            ||
                    destino == EstadoJuegoLibreDoble::terminal                    );
            break;
        case EstadoJuegoComun::marcacionCaminoFicha:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioJugada              ||
                    destino == EstadoJuegoLibreDoble::preparacionDesplazamiento ||
                    destino == EstadoJuegoLibreDoble::marcacionCaminoFicha      ||
                    destino == EstadoJuegoLibreDoble::agotadosPuntosAccion      ||
                    destino == EstadoJuegoLibreDoble::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoLibreDoble::inicioRonda               ||
                    destino == EstadoJuegoLibreDoble::finalPartida              ||
                    destino == EstadoJuegoLibreDoble::mostrandoAyuda            ||
                    destino == EstadoJuegoLibreDoble::terminal                    );
            break;
        case EstadoJuegoComun::habilidadSimpleResultado:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioJugada              ||
                    destino == EstadoJuegoLibreDoble::agotadosPuntosAccion      ||
                    destino == EstadoJuegoLibreDoble::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoLibreDoble::inicioRonda               ||
                    destino == EstadoJuegoLibreDoble::finalPartida              ||
                    destino == EstadoJuegoLibreDoble::mostrandoAyuda            ||
                    destino == EstadoJuegoLibreDoble::terminal                    );
            break;
        case EstadoJuegoComun::oponenteHabilidadResultado:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioJugada              ||
                    destino == EstadoJuegoLibreDoble::agotadosPuntosAccion      ||
                    destino == EstadoJuegoLibreDoble::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoLibreDoble::inicioRonda               ||
                    destino == EstadoJuegoLibreDoble::finalPartida              ||
                    destino == EstadoJuegoLibreDoble::mostrandoAyuda            ||
                    destino == EstadoJuegoLibreDoble::terminal                    );
            break;
        case EstadoJuegoComun::areaHabilidadResultado:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioJugada              ||
                    destino == EstadoJuegoLibreDoble::agotadosPuntosAccion      ||
                    destino == EstadoJuegoLibreDoble::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoLibreDoble::inicioRonda               ||
                    destino == EstadoJuegoLibreDoble::finalPartida              ||
                    destino == EstadoJuegoLibreDoble::mostrandoAyuda            ||
                    destino == EstadoJuegoLibreDoble::terminal                    );
            break;
        case EstadoJuegoLibreDoble::agotadosPuntosAccion:
            aserta (destino,
                    destino == EstadoJuegoLibreDoble::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoLibreDoble::inicioRonda               ||
                    destino == EstadoJuegoLibreDoble::finalPartida              ||
                    destino == EstadoJuegoLibreDoble::mostrandoAyuda            ||
                    destino == EstadoJuegoLibreDoble::terminal                    );    
            break;
        default:
            EstadoJuegoComun::valida (destino);
            break;
        }
    }


    const string EstadoJuegoLibreDoble::nombre () const {    
        switch (* this) {
        case EstadoJuegoLibreDoble::inicioRonda: 
            return "inicioRonda";
        case EstadoJuegoLibreDoble::inicioTurnoNoElegido: 
            return "inicioTurnoNoElegido";
        case EstadoJuegoLibreDoble::inicioTurnoConfirmacion: 
            return "inicioTurnoConfirmacion";
        case EstadoJuegoLibreDoble::agotadosPuntosAccion: 
            return "agotadosPuntosAccion";
        default:
            return EstadoJuegoComun::nombre (); 
        }
        return "";
    }


}




