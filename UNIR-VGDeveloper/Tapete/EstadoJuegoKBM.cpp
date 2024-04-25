// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoKBM.cpp
// versión:  1.1  (7-Abr-2024)


#include "tapete.h"


namespace tapete {


    EstadoJuegoKBM::EstadoJuegoKBM (int codigo) :
        EstadoJuegoComun {codigo} {
    }


    void EstadoJuegoKBM::transita (const EstadoJuegoKBM & destino) {
        valida (destino);
        if (traza_transitos) {
            std::cout << std::endl << this->nombre () << " ===> " << destino.nombre () << std::endl;
        }
        ponCodigo (destino);
    }


    void EstadoJuegoKBM::valida (const EstadoJuegoComun & destino) {
        switch (* this) {
        case EstadoJuegoKBM::inicial:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioRonda);
            break;
        case EstadoJuegoKBM::inicioRonda:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoKBM::mostrandoAyuda            ||
                    destino == EstadoJuegoKBM::terminal                    );
            break;
        case EstadoJuegoKBM::inicioTurnoNoElegido:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioTurnoConfirmacion   ||
                    destino == EstadoJuegoKBM::mostrandoAyuda            ||
                    destino == EstadoJuegoKBM::terminal                    );
            break;
        case EstadoJuegoKBM::inicioTurnoConfirmacion:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoKBM::inicioJugada              ||
                    destino == EstadoJuegoKBM::mostrandoAyuda            ||
                    destino == EstadoJuegoKBM::terminal                    );
            break;
        case EstadoJuegoComun::marcacionCaminoFicha:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioJugada              ||
                    destino == EstadoJuegoKBM::preparacionDesplazamiento ||
                    destino == EstadoJuegoKBM::marcacionCaminoFicha      ||
                    destino == EstadoJuegoKBM::agotadosPuntosAccion      ||
                    destino == EstadoJuegoKBM::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoKBM::inicioRonda               ||
                    destino == EstadoJuegoKBM::finalPartida              ||
                    destino == EstadoJuegoKBM::mostrandoAyuda            ||
                    destino == EstadoJuegoKBM::terminal                    );
            break;
        case EstadoJuegoComun::habilidadSimpleResultado:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioJugada              ||
                    destino == EstadoJuegoKBM::agotadosPuntosAccion      ||
                    destino == EstadoJuegoKBM::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoKBM::inicioRonda               ||
                    destino == EstadoJuegoKBM::finalPartida              ||
                    destino == EstadoJuegoKBM::mostrandoAyuda            ||
                    destino == EstadoJuegoKBM::terminal                    );
            break;
        case EstadoJuegoComun::oponenteHabilidadResultado:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioJugada              ||
                    destino == EstadoJuegoKBM::agotadosPuntosAccion      ||
                    destino == EstadoJuegoKBM::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoKBM::inicioRonda               ||
                    destino == EstadoJuegoKBM::finalPartida              ||
                    destino == EstadoJuegoKBM::mostrandoAyuda            ||
                    destino == EstadoJuegoKBM::terminal                    );
            break;
        case EstadoJuegoComun::areaHabilidadResultado:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioJugada              ||
                    destino == EstadoJuegoKBM::agotadosPuntosAccion      ||
                    destino == EstadoJuegoKBM::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoKBM::inicioRonda               ||
                    destino == EstadoJuegoKBM::finalPartida              ||
                    destino == EstadoJuegoKBM::mostrandoAyuda            ||
                    destino == EstadoJuegoKBM::terminal                    );
            break;
        case EstadoJuegoKBM::agotadosPuntosAccion:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioTurnoNoElegido      ||
                    destino == EstadoJuegoKBM::inicioRonda               ||
                    destino == EstadoJuegoKBM::finalPartida              ||
                    destino == EstadoJuegoKBM::mostrandoAyuda            ||
                    destino == EstadoJuegoKBM::terminal                    );    
            break;
        default:
            EstadoJuegoComun::valida (destino);
            break;
        }
    }


    const string EstadoJuegoKBM::nombre () const {    
        switch (* this) {
        case EstadoJuegoKBM::inicioRonda: 
            return "inicioRonda";
        case EstadoJuegoKBM::inicioTurnoNoElegido: 
            return "inicioTurnoNoElegido";
        case EstadoJuegoKBM::inicioTurnoConfirmacion: 
            return "inicioTurnoConfirmacion";
        case EstadoJuegoKBM::agotadosPuntosAccion: 
            return "agotadosPuntosAccion";
        default:
            return EstadoJuegoComun::nombre (); 
        }
        return "";
    }


}




