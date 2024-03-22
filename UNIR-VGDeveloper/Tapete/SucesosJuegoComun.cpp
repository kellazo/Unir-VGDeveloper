// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoComun.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    SucesosJuegoComun::SucesosJuegoComun (JuegoMesaBase * juego, ModoJuegoComun * modo) { 
        this->juego_   = juego;
        this->modo_ = modo;
    }


    SucesosJuegoComun::~SucesosJuegoComun () {
        this->modo_ = nullptr;
        this->juego_   = nullptr;
    }


    JuegoMesaBase * SucesosJuegoComun::juego () {
        return juego_;
    }


    ModoJuegoComun * SucesosJuegoComun::modo () {
        return modo_;
    }


    void SucesosJuegoComun::terminado () {
        if (modo ()->estado () != EstadoJuegoComun::inicial &&
            modo ()->estado () != EstadoJuegoComun::terminal  ) {
            modo ()->saltaFinalJuego ();
        }
    }


    void SucesosJuegoComun::entrandoActuante (LadoTablero lado) {
        assert (lado != LadoTablero::nulo);
        if (modo ()->estado () != EstadoJuegoComun::inicial &&
            modo ()->estado () != EstadoJuegoComun::terminal  ) {
            if (! juego ()->tablero ()->presencia (lado).visible ()) {
                return;
            }
            modo ()->anunciaActuante (lado);
        }
    }


    void SucesosJuegoComun::saliendoActuante (LadoTablero lado) {
        assert (lado != LadoTablero::nulo);
        if (modo ()->estado () != EstadoJuegoComun::inicial &&
            modo ()->estado () != EstadoJuegoComun::terminal  ) {
            if (! juego ()->tablero ()->presencia (lado).visible ()) {
                return;
            }
            modo ()->desanunciaActuante (lado);
        }
    }


    void SucesosJuegoComun::entrandoHabilidad (LadoTablero lado, int indice) {
        assert (lado != LadoTablero::nulo);
        if (modo ()->estado () != EstadoJuegoComun::inicial &&
            modo ()->estado () != EstadoJuegoComun::terminal  ) {
            PresenciaActuante & presencia = juego ()->tablero ()->presencia (lado);
            if (! presencia.visible ()) {
                return;
            }
            if (presencia.personaje ()->habilidades ().size () <= indice) {
                return;
            }
            modo ()->anunciaHabilidad (lado, indice);
        }
    }


    void SucesosJuegoComun::saliendoHabilidad (LadoTablero lado, int indice) {
        assert (lado != LadoTablero::nulo);
        if (modo ()->estado () != EstadoJuegoComun::inicial &&
            modo ()->estado () != EstadoJuegoComun::terminal  ) {
            PresenciaActuante & presencia = juego ()->tablero ()->presencia (lado);
            if (! presencia.visible ()) {
                return;
            }
            if (presencia.personaje ()->habilidades ().size () <= indice) {
                return;
            }
            modo ()->desanunciaHabilidad (lado, indice);
        }
    }


    void SucesosJuegoComun::entrandoFicha (ActorPersonaje * personaje) {
        if (modo ()->estado () != EstadoJuegoComun::inicial &&
            modo ()->estado () != EstadoJuegoComun::terminal  ) {
            modo ()->anunciaFicha (personaje);
        }
        if (modo ()->estado () == EstadoJuegoComun::preparacionDesplazamiento) {
            modo ()->marcaFichaCamino (personaje);
        }
    }


    void SucesosJuegoComun::saliendoFicha (ActorPersonaje * personaje) {
        if (modo ()->estado () != EstadoJuegoComun::inicial &&
            modo ()->estado () != EstadoJuegoComun::terminal  ) {
            modo ()->desanunciaFicha (personaje);
        }
        if (modo ()->estado () == EstadoJuegoComun::preparacionDesplazamiento) {
            modo ()->desmarcaFichaCamino (personaje);
        }
    }


    void SucesosJuegoComun::entrandoCelda (Coord celda) {
        if (modo ()->estado () == EstadoJuegoComun::marcacionCaminoFicha) {
            modo ()->marcaCeldaCamino (celda);
        }
    }


    void SucesosJuegoComun::saliendoCelda (Coord celda) {
        if (modo ()->estado () == EstadoJuegoComun::marcacionCaminoFicha) {
            modo ()->desmarcaCeldaCamino (celda);
        }
    }


    void SucesosJuegoComun::personajeSeleccionado (ActorPersonaje * personaje) {
        switch (modo ()->estado ()) {
        case EstadoJuegoComun::preparacionHabilidadOponente:
        case EstadoJuegoComun::oponenteHabilidadInvalido:
            modo ()->evaluaHabilidadOponente (personaje);
            break;
        case EstadoJuegoComun::mostrandoAyuda:
            modo ()->muestraAyuda (personaje);
            unir2d::Raton::consumePulsado (unir2d::BotonRaton::izquierda);
            break;
        }
    }


    void SucesosJuegoComun::actuanteSeleccionado (LadoTablero lado) {
        assert (lado != LadoTablero::nulo);
        switch (modo ()->estado ()) {
        case EstadoJuegoComun::inicioJugada:
        case EstadoJuegoComun::preparacionHabilidadOponente:
        case EstadoJuegoComun::preparacionHabilidadArea:
            if (modo ()->atacante ()->ladoTablero () != lado) {
                return;
            }
            modo ()->entraAccionDesplazam ();
            break;
        case EstadoJuegoComun::mostrandoAyuda:
            if (modo ()->atacante () != nullptr && 
                modo ()->atacante ()->ladoTablero () != lado) {
                return;
            }
            modo ()->muestraAyudaActuante ();
            unir2d::Raton::consumePulsado (unir2d::BotonRaton::izquierda);
            break;
        }
    }


    void SucesosJuegoComun::habilidadSeleccionada (LadoTablero lado, int indice_habilidad) {
        assert (lado != LadoTablero::nulo);
        switch (modo ()->estado ()) {
        case EstadoJuegoComun::inicioJugada:
        case EstadoJuegoComun::preparacionDesplazamiento:
        case EstadoJuegoComun::preparacionHabilidadOponente:
        case EstadoJuegoComun::preparacionHabilidadArea:
            if (modo ()->atacante ()->ladoTablero () != lado) {
                return;
            }
            if (indice_habilidad >= modo ()->atacante ()->habilidades ().size ()) {
                return;
            }
            modo ()->entraAccionHabilidad (indice_habilidad);
            break;
        case EstadoJuegoComun::habilidadSimpleInvalida:
            if (modo ()->atacante ()->ladoTablero () != lado) {
                return;
            }
            if (indice_habilidad >= modo ()->atacante ()->habilidades ().size ()) {
                return;
            }
            if (modo ()->atacante ()->habilidades () [indice_habilidad]->tipoEnfoque () == 
                        EnfoqueHabilidad::si_mismo) {
                modo ()->evaluaHabilidadSimple (indice_habilidad);
            }
            break;
        case EstadoJuegoComun::oponenteHabilidadInvalido:
            if (modo ()->atacante ()->ladoTablero () != lado) {
                return;
            }
            if (indice_habilidad >= modo ()->atacante ()->habilidades ().size ()) {
                return;
            }
            if (modo ()->atacante ()->habilidades () [indice_habilidad]->tipoEnfoque () == 
                        EnfoqueHabilidad::personaje) {
                modo ()->evaluaHabilidadOponente (indice_habilidad);
            }
            break;
        case EstadoJuegoComun::areaHabilidadInvalida:
            if (modo ()->atacante ()->ladoTablero () != lado) {
                return;
            }
            if (indice_habilidad >= modo ()->atacante ()->habilidades ().size ()) {
                return;
            }
            if (modo ()->atacante ()->habilidades () [indice_habilidad]->tipoEnfoque () == 
                        EnfoqueHabilidad::area) {
                modo ()->evaluaHabilidadArea (indice_habilidad);
            }
            break;
        }
    }


    void SucesosJuegoComun::fichaSeleccionada (ActorPersonaje * personaje) {
        // reenvia al método de 'suceso externo':
        personajeSeleccionado (personaje);
    }


    // si estamos en 'inicioJugada' y el suceso es 'fichaPulsada':
    // se insertan los sucesos previos: 'actuanteSeleccionado' y 'entrandoFicha'
    // con la condicion de que sea la ficha del atacante
    void SucesosJuegoComun::fichaPulsada (ActorPersonaje * personaje) {
        if (modo ()->estado () == EstadoJuegoComun::inicioJugada) {
            if (personaje == modo ()->atacante ()) {
                // se efectuan dos transiciones seguidas:
                //cambiado: SucesosJuegoComun::actuanteSeleccionado (personaje->ladoTablero ());
                modo ()->entraAccionDesplazam ();
                //cambiado: SucesosJuegoComun::entrandoFicha (personaje);
                modo ()->marcaFichaCamino (personaje);
            }
        }
        if (modo ()->estado () == EstadoJuegoComun::preparacionDesplazamiento) {
            if (modo ()->atacante () != personaje) {
                return;
            }
            modo ()->entraMarcacionCamino ();
        }
    }


    void SucesosJuegoComun::celdaSeleccionada (Coord celda) {
        switch (modo ()->estado ()) {
        case EstadoJuegoComun::preparacionHabilidadArea:
        case EstadoJuegoComun::areaHabilidadInvalida:
            modo ()->evaluaHabilidadArea (celda);
            break;
        }
    }


    void SucesosJuegoComun::celdaPulsada (Coord celda) {
        if (modo ()->estado () == EstadoJuegoComun::marcacionCaminoFicha) {
            if (celda == modo ()->atacante ()->sitioFicha ()) {
                // es un clic de repetición, hay que ignorarlo
                return;
            }
            if (modo ()->etapasCamino ().size () > 0 &&
                modo ()->etapasCamino ().back () == celda) {
                // es un clic de repetición, hay que ignorarlo
                return;
            }
            modo ()->fijaCeldaCamino (celda);
        }
    }


    void SucesosJuegoComun::ayudaSeleccionada () {
        if (modo ()->estado () != EstadoJuegoComun::inicial        &&
            modo ()->estado () != EstadoJuegoComun::terminal       &&
            modo ()->estado () != EstadoJuegoComun::mostrandoAyuda   ) {
            modo ()->muestraAyuda ();
        } else if (modo ()->estado () == EstadoJuegoComun::mostrandoAyuda) {
            modo ()->ocultaAyuda ();
        }
        unir2d::Raton::consumePulsado (unir2d::BotonRaton::izquierda);
    }


    void SucesosJuegoComun::pulsadoEspacio () {
        switch (modo ()->estado ()) {
        case EstadoJuegoComun::habilidadSimpleConfirmacion:
            modo ()->efectuaHabilidadSimple ();
            break;
        case EstadoJuegoComun::oponenteHabilidadConfirmacion:
            modo ()->efectuaHabilidadOponente ();
            break;
        case EstadoJuegoComun::areaHabilidadConfirmacion:
            modo ()->efectuaHabilidadArea ();
            break;
        }
    }


    void SucesosJuegoComun::pulsadoEscape () {
        switch (modo ()->estado ()) {
        case EstadoJuegoComun::marcacionCaminoFicha:
            modo ()->revierteAccionDesplazam ();
            break; 
        case EstadoJuegoComun::habilidadSimpleInvalida:
        case EstadoJuegoComun::habilidadSimpleConfirmacion:
            modo ()->revierteHabilidadSimple ();
            break;
        case EstadoJuegoComun::oponenteHabilidadInvalido:
        case EstadoJuegoComun::oponenteHabilidadConfirmacion:
            modo ()->revierteHabilidadOponente ();
            break;
        case EstadoJuegoComun::areaHabilidadInvalida:
        case EstadoJuegoComun::areaHabilidadConfirmacion:
            modo ()->revierteHabilidadArea ();
            break;
        case EstadoJuegoComun::mostrandoAyuda:
            modo ()->ocultaAyuda ();
            break;
        }
    }


    void SucesosJuegoComun::pulsadoArriba () {
        if (modo ()->estado () == EstadoJuegoComun::mostrandoAyuda) {
            modo ()->subeAyuda ();
            unir2d::Teclado::consume (unir2d::Tecla::arriba);
        }
    }


    void SucesosJuegoComun::pulsadoAbajo () {
        if (modo ()->estado () == EstadoJuegoComun::mostrandoAyuda) {
            modo ()->bajaAyuda ();
            unir2d::Teclado::consume (unir2d::Tecla::abajo);
        }
    }


    void SucesosJuegoComun::alarmaCalculo (unir2d::Tiempo & tiempo) {
        switch (modo ()->estado ()) {
        case EstadoJuegoComun::oponenteHabilidadCalculando:
            modo ()->calculaHabilidadOponente (tiempo);
            break;
        case EstadoJuegoComun::areaHabilidadCalculando:
            modo ()->calculaHabilidadArea (tiempo);
            break;
        }
    }


}

