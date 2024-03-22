// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoEquipo.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    EstadoJuegoEquipo::EstadoJuegoEquipo (int codigo) :
        EstadoJuegoComun {codigo} {
    }


    void EstadoJuegoEquipo::transita (const EstadoJuegoEquipo & destino) {
        valida (destino);
        if (traza_transitos) {
            std::cout << std::endl << this->nombre () << " ===> " << destino.nombre () << std::endl;
        }
        ponCodigo (destino);
    }


    void EstadoJuegoEquipo::valida (const EstadoJuegoComun & destino) {
        switch (* this) {
        case EstadoJuegoEquipo::inicial:
            aserta (destino,
                    destino == EstadoJuegoEquipo::inicioRonda);
            break;
        case EstadoJuegoEquipo::inicioRonda:
            aserta (destino,
                    destino == EstadoJuegoEquipo::inicioJugada                  ||
                    destino == EstadoJuegoEquipo::mostrandoAyuda                ||
                    destino == EstadoJuegoEquipo::terminal                        );
            break;
        case EstadoJuegoEquipo::inicioTurno:
            aserta (destino,
                    destino == EstadoJuegoEquipo::inicioJugada                  ||
                    destino == EstadoJuegoEquipo::mostrandoAyuda                ||
                    destino == EstadoJuegoEquipo::terminal                        );
            break;                                                              
        case EstadoJuegoComun::marcacionCaminoFicha:                            
            aserta (destino,                                                    
                    destino == EstadoJuegoEquipo::inicioJugada                  ||
                    destino == EstadoJuegoEquipo::preparacionDesplazamiento     ||
                    destino == EstadoJuegoEquipo::marcacionCaminoFicha          ||
                    destino == EstadoJuegoEquipo::inicioTurno                   ||
                    destino == EstadoJuegoEquipo::inicioRonda                   ||
                    destino == EstadoJuegoEquipo::finalPartida                  ||
                    destino == EstadoJuegoEquipo::mostrandoAyuda                ||
                    destino == EstadoJuegoEquipo::terminal                        );
            break;                                                              
        case EstadoJuegoComun::habilidadSimpleResultado:                        
            aserta (destino,                                                    
                    destino == EstadoJuegoEquipo::inicioJugada                  ||
                    destino == EstadoJuegoEquipo::inicioTurno                   ||
                    destino == EstadoJuegoEquipo::inicioRonda                   ||
                    destino == EstadoJuegoEquipo::finalPartida                  ||
                    destino == EstadoJuegoEquipo::mostrandoAyuda                ||
                    destino == EstadoJuegoEquipo::terminal                        );
            break;                                                              
        case EstadoJuegoComun::oponenteHabilidadResultado:                      
            aserta (destino,                                                    
                    destino == EstadoJuegoEquipo::inicioJugada                  ||
                    destino == EstadoJuegoEquipo::inicioTurno                   ||
                    destino == EstadoJuegoEquipo::inicioRonda                   ||
                    destino == EstadoJuegoEquipo::finalPartida                  ||
                    destino == EstadoJuegoEquipo::mostrandoAyuda                ||
                    destino == EstadoJuegoEquipo::terminal                        );
            break;                                                              
        case EstadoJuegoComun::areaHabilidadResultado:                          
            aserta (destino,                                                    
                    destino == EstadoJuegoEquipo::inicioJugada                  ||
                    destino == EstadoJuegoEquipo::inicioTurno                   ||
                    destino == EstadoJuegoEquipo::inicioRonda                   ||
                    destino == EstadoJuegoEquipo::finalPartida                  ||
                    destino == EstadoJuegoEquipo::mostrandoAyuda                ||
                    destino == EstadoJuegoEquipo::terminal                        );
            break;
        default:
            EstadoJuegoComun::valida (destino);
            break;
        }
        //
        // por fin:
    }


    const string EstadoJuegoEquipo::nombre () const {    
        switch (* this) {
        case EstadoJuegoEquipo::inicioRonda: 
            return "inicioRonda";
        case EstadoJuegoEquipo::inicioTurno: 
            return "inicioTurno";
        default:
            return EstadoJuegoComun::nombre (); 
        }
        return "";
    }


}




