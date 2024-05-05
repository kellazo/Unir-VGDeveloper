// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoKBM.cpp
// versión:  1.1  (9-Ene-2023)


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
                    destino == EstadoJuegoKBM::inicioJugada                  ||
                    destino == EstadoJuegoKBM::mostrandoAyuda                ||
                    destino == EstadoJuegoKBM::terminal                        );
            break;
        case EstadoJuegoKBM::inicioTurno:
            aserta (destino,
                    destino == EstadoJuegoKBM::inicioJugada                  ||
                    destino == EstadoJuegoKBM::mostrandoAyuda                ||
                    destino == EstadoJuegoKBM::terminal                        );
            break;                                                              
        case EstadoJuegoComun::marcacionCaminoFicha:                            
            aserta (destino,                                                    
                    destino == EstadoJuegoKBM::inicioJugada                  ||
                    destino == EstadoJuegoKBM::preparacionDesplazamiento     ||
                    destino == EstadoJuegoKBM::marcacionCaminoFicha          ||
                    destino == EstadoJuegoKBM::inicioTurno                   ||
                    destino == EstadoJuegoKBM::inicioRonda                   ||
                    destino == EstadoJuegoKBM::finalPartida                  ||
                    destino == EstadoJuegoKBM::mostrandoAyuda                ||
                    destino == EstadoJuegoKBM::terminal                        );
            break;                                                              
        case EstadoJuegoComun::habilidadSimpleResultado:                        
            aserta (destino,                                                    
                    destino == EstadoJuegoKBM::inicioJugada                  ||
                    destino == EstadoJuegoKBM::inicioTurno                   ||
                    destino == EstadoJuegoKBM::inicioRonda                   ||
                    destino == EstadoJuegoKBM::finalPartida                  ||
                    destino == EstadoJuegoKBM::mostrandoAyuda                ||
                    destino == EstadoJuegoKBM::terminal                        );
            break;                                                              
        case EstadoJuegoComun::oponenteHabilidadResultado:                      
            aserta (destino,                                                    
                    destino == EstadoJuegoKBM::inicioJugada                  ||
                    destino == EstadoJuegoKBM::inicioTurno                   ||
                    destino == EstadoJuegoKBM::inicioRonda                   ||
                    destino == EstadoJuegoKBM::finalPartida                  ||
                    destino == EstadoJuegoKBM::mostrandoAyuda                ||
                    destino == EstadoJuegoKBM::terminal                        );
            break;                                                              
        case EstadoJuegoComun::areaHabilidadResultado:                          
            aserta (destino,                                                    
                    destino == EstadoJuegoKBM::inicioJugada                  ||
                    destino == EstadoJuegoKBM::inicioTurno                   ||
                    destino == EstadoJuegoKBM::inicioRonda                   ||
                    destino == EstadoJuegoKBM::finalPartida                  ||
                    destino == EstadoJuegoKBM::mostrandoAyuda                ||
                    destino == EstadoJuegoKBM::terminal                        );
            break;
        default:
            EstadoJuegoComun::valida (destino);
            break;
        }
        //
        // por fin:
    }


    const string EstadoJuegoKBM::nombre () const {    
        switch (* this) {
        case EstadoJuegoKBM::inicioRonda: 
            return "inicioRonda";
        case EstadoJuegoKBM::inicioTurno: 
            return "inicioTurno";
        default:
            return EstadoJuegoComun::nombre (); 
        }
        return "";
    }


}




