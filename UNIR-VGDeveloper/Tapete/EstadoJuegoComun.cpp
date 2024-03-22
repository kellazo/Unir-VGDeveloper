// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoComun.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    EstadoJuegoComun::EstadoJuegoComun () {
        this->codigo = EstadoJuegoComun::terminal;
    }


    EstadoJuegoComun::EstadoJuegoComun (int codigo) {
        this->codigo = codigo;
    }


    EstadoJuegoComun::operator int () const { 
        return codigo; 
    }


    void EstadoJuegoComun::transita (const EstadoJuegoComun & destino) {
        valida (destino);
        if (traza_transitos) {
            std::cout << std::endl << this->nombre () << " ===> " << destino.nombre () << std::endl;
        }
        ponCodigo (destino);
    }


    void EstadoJuegoComun::conserva (const EstadoJuegoComun & estado) {
        ponCodigo (estado.codigo);
    }


    void EstadoJuegoComun::valida (const EstadoJuegoComun & destino) {
        switch (* this) {
        case EstadoJuegoComun::terminal:
            aserta (destino,
                    false);
            break;
        case EstadoJuegoComun::inicioJugada:
            aserta (destino,
                    destino == EstadoJuegoComun::preparacionDesplazamiento      ||  
                    destino == EstadoJuegoComun::habilidadSimpleInvalida        ||
                    destino == EstadoJuegoComun::habilidadSimpleConfirmacion    ||
                    destino == EstadoJuegoComun::preparacionHabilidadOponente   ||
                    destino == EstadoJuegoComun::preparacionHabilidadArea       ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::preparacionDesplazamiento:
            aserta (destino,
                    destino == EstadoJuegoComun::preparacionDesplazamiento      || 
                    destino == EstadoJuegoComun::marcacionCaminoFicha           ||
                    destino == EstadoJuegoComun::habilidadSimpleInvalida        ||
                    destino == EstadoJuegoComun::habilidadSimpleConfirmacion    ||
                    destino == EstadoJuegoComun::preparacionHabilidadOponente   ||
                    destino == EstadoJuegoComun::preparacionHabilidadArea       ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::habilidadSimpleInvalida:
            aserta (destino,
                    destino == EstadoJuegoComun::inicioJugada                   ||
                    destino == EstadoJuegoComun::habilidadSimpleInvalida        ||
                    destino == EstadoJuegoComun::habilidadSimpleConfirmacion    ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::habilidadSimpleConfirmacion:
            aserta (destino,
                    destino == EstadoJuegoComun::inicioJugada                   ||
                    destino == EstadoJuegoComun::habilidadSimpleResultado       ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::preparacionHabilidadOponente:
            aserta (destino,
                    destino == EstadoJuegoComun::preparacionDesplazamiento      ||
                    destino == EstadoJuegoComun::habilidadSimpleInvalida        ||
                    destino == EstadoJuegoComun::habilidadSimpleConfirmacion    ||
                    destino == EstadoJuegoComun::preparacionHabilidadOponente   ||
                    destino == EstadoJuegoComun::oponenteHabilidadInvalido      ||
                    destino == EstadoJuegoComun::oponenteHabilidadConfirmacion  ||
                    destino == EstadoJuegoComun::preparacionHabilidadArea       ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::oponenteHabilidadInvalido:
            aserta (destino,
                    destino == EstadoJuegoComun::preparacionHabilidadOponente   ||
                    destino == EstadoJuegoComun::oponenteHabilidadInvalido      ||
                    destino == EstadoJuegoComun::oponenteHabilidadConfirmacion  ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                        );
            break;
        case EstadoJuegoComun::oponenteHabilidadConfirmacion:
            aserta (destino,
                    destino == EstadoJuegoComun::preparacionHabilidadOponente   ||
                    destino == EstadoJuegoComun::oponenteHabilidadCalculando    ||
                    destino == EstadoJuegoComun::oponenteHabilidadResultado     ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::oponenteHabilidadCalculando:
            aserta (destino,
                    destino == EstadoJuegoComun::oponenteHabilidadCalculando    ||
                    destino == EstadoJuegoComun::oponenteHabilidadResultado     ||                    
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::preparacionHabilidadArea:
            aserta (destino,
                    destino == EstadoJuegoComun::preparacionDesplazamiento      ||
                    destino == EstadoJuegoComun::habilidadSimpleInvalida        ||
                    destino == EstadoJuegoComun::habilidadSimpleConfirmacion    ||
                    destino == EstadoJuegoComun::preparacionHabilidadOponente   ||
                    destino == EstadoJuegoComun::preparacionHabilidadArea       ||
                    destino == EstadoJuegoComun::areaHabilidadInvalida          ||
                    destino == EstadoJuegoComun::areaHabilidadConfirmacion      ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::areaHabilidadInvalida:
            aserta (destino,
                    destino == EstadoJuegoComun::preparacionHabilidadArea       ||
                    destino == EstadoJuegoComun::areaHabilidadInvalida          ||
                    destino == EstadoJuegoComun::areaHabilidadConfirmacion      ||
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::areaHabilidadConfirmacion:
            aserta (destino,
                    destino == EstadoJuegoComun::preparacionHabilidadArea       ||
                    destino == EstadoJuegoComun::areaHabilidadCalculando        ||                    
                    destino == EstadoJuegoComun::areaHabilidadResultado         ||                    
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::areaHabilidadCalculando:
            aserta (destino,
                    destino == EstadoJuegoComun::areaHabilidadCalculando        ||
                    destino == EstadoJuegoComun::areaHabilidadResultado         ||                    
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::mostrandoAyuda:
            aserta (destino,
                    destino != EstadoJuegoComun::inicial                          );
                    //destino == EstadoJuegoComun::habilidadSimpleResultado       ||
                    //destino == EstadoJuegoComun::oponenteHabilidadResultado     ||
                    //destino == EstadoJuegoComun::areaHabilidadResultado         ||
                    //destino == EstadoJuegoComun::terminal                         );
            break;
        case EstadoJuegoComun::finalPartida:
            aserta (destino,
                    destino == EstadoJuegoComun::mostrandoAyuda                 ||
                    destino == EstadoJuegoComun::terminal                         );    
            break;
        default:
            aserta (destino,
                    false);
            break;
        }
    }


    void EstadoJuegoComun::ponCodigo (int valor) {
        this->codigo = valor;
    }


    const string EstadoJuegoComun::nombre () const {    
        switch (* this) {
        case EstadoJuegoComun::inicial:   
            return "inicial";
        case EstadoJuegoComun::terminal:   
            return "terminal";
        case EstadoJuegoComun::inicioJugada:   
            return "inicioJugada";
        case EstadoJuegoComun::preparacionDesplazamiento:   
            return "preparacionDesplazamiento";
        case EstadoJuegoComun::marcacionCaminoFicha:   
            return "marcacionCaminoFicha";
        case EstadoJuegoComun::habilidadSimpleInvalida:   
            return "habilidadSimpleInvalida";
        case EstadoJuegoComun::habilidadSimpleConfirmacion:   
            return "habilidadSimpleConfirmacion";
        case EstadoJuegoComun::habilidadSimpleResultado:   
            return "habilidadSimpleResultado";
        case EstadoJuegoComun::preparacionHabilidadOponente:   
            return "preparacionHabilidadOponente";
        case EstadoJuegoComun::oponenteHabilidadInvalido:   
            return "oponenteHabilidadInvalido";
        case EstadoJuegoComun::oponenteHabilidadConfirmacion:   
            return "oponenteHabilidadConfirmacion";
        case EstadoJuegoComun::oponenteHabilidadCalculando:   
            return "oponenteHabilidadCalculando";
        case EstadoJuegoComun::oponenteHabilidadResultado:   
            return "oponenteHabilidadResultado";
        case EstadoJuegoComun::preparacionHabilidadArea:   
            return "preparacionHabilidadArea";
        case EstadoJuegoComun::areaHabilidadInvalida:   
            return "areaHabilidadInvalida";
        case EstadoJuegoComun::areaHabilidadConfirmacion:   
            return "areaHabilidadConfirmacion";
        case EstadoJuegoComun::areaHabilidadCalculando:   
            return "areaHabilidadCalculando";
        case EstadoJuegoComun::areaHabilidadResultado:   
            return "areaHabilidadResultado";
        case EstadoJuegoComun::mostrandoAyuda:
            return "mostrandoAyuda";
        case EstadoJuegoComun::finalPartida:   
            return "finalPartida";
        default:
            assert (false);
        }
        return "";
    }


    void EstadoJuegoComun::aserta (const EstadoJuegoComun & destino, bool condicion) const {
        if (condicion) {
            return;
        }
        throw std::logic_error ("Transito inadmisible:  " + nombre () + " ===> " + destino.nombre ());
    }

}