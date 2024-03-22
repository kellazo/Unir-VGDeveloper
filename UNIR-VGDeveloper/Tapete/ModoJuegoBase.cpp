// proyecto: Grupal/Tapete   
// arhivo:   ModoJuegoBase.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    ModoJuegoBase::ModoJuegoBase (JuegoMesaBase * juego) {
        this->juego_ = juego;
        lado_equipo_inicial = LadoTablero::nulo;
        lado_equipo_actual  = LadoTablero::nulo;
    }


    ModoJuegoBase::~ModoJuegoBase () {
        juego_ = nullptr;
    }


    //----------------------------------------------------------------------------------------------


    JuegoMesaBase * ModoJuegoBase::juego () {
        return juego_;
    }


    //----------------------------------------------------------------------------------------------


    float ModoJuegoBase::puntosAccionDeDesplaza () const {
        return puntos_accion_de_desplaza;
    }


    void ModoJuegoBase::configuraDesplaza (float puntos_accion_desplaza) {
        this->puntos_accion_de_desplaza = puntos_accion_desplaza;
    }


    //----------------------------------------------------------------------------------------------


    int ModoJuegoBase::ronda () const { 
        return ronda_;
    }


    int ModoJuegoBase::turno () const { 
        return turno_;
    };


    int ModoJuegoBase::jugada () const { 
        return jugada_;
    };


    //----------------------------------------------------------------------------------------------


    LadoTablero ModoJuegoBase::ladoEquipoInicial () const {
        return lado_equipo_inicial;
    }


    LadoTablero ModoJuegoBase::ladoEquipoActual  () const {
        return lado_equipo_actual;
    }


    //----------------------------------------------------------------------------------------------


    const std::vector <ActorPersonaje * > & ModoJuegoBase::factoresEquipos () const {
        return factores_equipos;
    }


    int ModoJuegoBase::indiceFactorEquipos () const {
        return indice_factor_equipos;
    }


    //----------------------------------------------------------------------------------------------


    ActorPersonaje * ModoJuegoBase::personajeElegido (LadoTablero lado_tablero) const { 
        aserta (lado_tablero != LadoTablero::nulo, "personajeElegido", "parámetro 'lado_tablero' inválido");
        //
        if (lado_tablero == LadoTablero::Izquierda) {
            return personaje_elegido_izqrd;
        } else {
            return personaje_elegido_derch;
        }
    }


    ActorPersonaje * ModoJuegoBase::atacante () const {
        return atacante_;
    }
    
    
    ModoAccionPersonaje ModoJuegoBase::modoAccion () const {
        return modo_accion;
    }


    //----------------------------------------------------------------------------------------------


    const std::vector <Coord> & ModoJuegoBase::etapasCamino () const {
        return etapas_camino;
    }


    Habilidad * ModoJuegoBase::habilidadAccion () const {
        return habilidad_accion;
    }


    ActorPersonaje * ModoJuegoBase::oponente () const {
        return oponente_;
    }
    
    
    const AreaCentradaCeldas & ModoJuegoBase::areaCeldas () const {
        return area_celdas;
    }


    //----------------------------------------------------------------------------------------------


    bool ModoJuegoBase::cuentaPersonajesIgual () {
        int lado_izqrd = 0;
        int lado_derch = 0;
        for (ActorPersonaje * persj : juego_->personajes ()) {
            if (persj->ladoTablero () == LadoTablero::Izquierda) {
                lado_izqrd ++;
            } else {
                lado_derch ++;
            }
        }
        return lado_izqrd == lado_derch;
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::iniciaRondas () {
        iniciaPersonajes ();
        restauraPersonajes ();
        ronda_  = 1;
        turno_  = 1;
        jugada_ = 1;
        if (trazar_avance) {
            std::cout << std::endl;
            std::cout << "Ronda = "  << ronda_  << "  ";
            std::cout << "Turno = "  << turno_  << "  ";
            std::cout << "Jugada = " << jugada_ << "  ";
        }
    }


    void ModoJuegoBase::avanzaJugada () {
        jugada_ ++;
        if (trazar_avance) {
            std::cout << std::endl;
            std::cout << "Ronda = "  << ronda_  << "  ";
            std::cout << "Turno = "  << turno_  << "  ";
            std::cout << "Jugada = " << jugada_ << "  ";
        }
    }


    void ModoJuegoBase::avanzaTurno () {
        turno_ ++;
        jugada_ = 1;
        if (trazar_avance) {
            std::cout << std::endl;
            std::cout << "Ronda = "  << ronda_  << "  ";
            std::cout << "Turno = "  << turno_  << "  ";
            std::cout << "Jugada = " << jugada_ << "  ";
        }
    }


    void ModoJuegoBase::avanzaRonda () {
        restauraPersonajes ();
        ronda_ ++;
        turno_ = 1;
        jugada_ = 1;
        if (trazar_avance) {
            std::cout << std::endl;
            std::cout << "Ronda = "  << ronda_  << "  ";
            std::cout << "Turno = "  << turno_  << "  ";
            std::cout << "Jugada = " << jugada_ << "  ";
        }
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::atenuaMusica () {
        juego_->musica ()->bajaMusica ();
    }


    //----------------------------------------------------------------------------------------------


    LadoTablero ModoJuegoBase::eligeEquipoIniciativa () {
        aserta (personaje_elegido_izqrd == nullptr, "eligeEquipoInicial", "personaje elegido izquierda");
        aserta (personaje_elegido_derch == nullptr, "eligeEquipoInicial", "personaje elegido derecha");
        aserta (atacante_ == nullptr,               "eligeEquipoInicial", "atacante asignado");
        //
        int inict_izqrd = -1;
        int inict_derch = -1;
        for (ActorPersonaje * persj : juego_->personajes ()) {
            if (persj->ladoTablero () == LadoTablero::Izquierda) {
                if (persj->iniciativa () > inict_izqrd) {
                    inict_izqrd = persj->iniciativa ();
                }
            } else {
                if (persj->iniciativa () > inict_derch) {
                    inict_derch = persj->iniciativa ();
                }
            }
        }
        //
        aserta (inict_izqrd > 0, "eligeEquipoInicial", "iniciativa izquierda nula");
        aserta (inict_derch > 0, "eligeEquipoInicial", "iniciativa derecha nula");
        //
        if (inict_izqrd > inict_derch) {
            return LadoTablero::Izquierda;
        }
        if (inict_derch > inict_izqrd) {
            return LadoTablero::Derecha;
        }
        //
        uint32_t azar = azarosa (2);
        if (azar == 0) {
            return LadoTablero::Izquierda;
        } else {
            return LadoTablero::Derecha;
        }
    }


    void ModoJuegoBase::asignaEquipoInicial (LadoTablero lado_tablero) {
        // lado_tablero puede ser nulo, no validar
        aserta (atacante_ == nullptr, "asignaEquipoInicial", "atacante asignado");
        //
        lado_equipo_inicial = lado_tablero;
    }


    void ModoJuegoBase::asignaEquipoActual (LadoTablero lado_tablero) {
        // lado_tablero puede ser nulo
        aserta (atacante_ == nullptr, "asignaEquipoActual", "atacante asignado");
        //
        lado_equipo_actual = lado_tablero;
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::estableceFactoresEquipos () {
        aserta (lado_equipo_inicial != LadoTablero::nulo, 
                                      "estableceFactoresEquipos", "lado del equipo inicial nulo");
        aserta (juego_->personajes (         lado_equipo_inicial) .size () == 
                juego_->personajes (opuesto (lado_equipo_inicial)).size ()   ,
                                      "estableceFactoresEquipos", "distinto número de personajes en los dos lados");
        aserta (atacante_ == nullptr, "estableceFactoresEquipos", "atacante asignado");
        aserta (factores_equipos.size () == 0, "", "");
        //
        int indice = 0;
        while (true) {
            factores_equipos.push_back (juego_->personajes (         lado_equipo_inicial ).at (indice));
            factores_equipos.push_back (juego_->personajes (opuesto (lado_equipo_inicial)).at (indice));
            indice ++;
            if (indice >= juego_->personajes (lado_equipo_inicial).size ()) {
                break;
            }
        }
    }


    void ModoJuegoBase::indexaFactorEquipos (int valor) {
        aserta (-1 <= valor && valor <= static_cast <int> (factores_equipos.size ()), 
                                      "indexaFactorEquipos", "parámetro 'valor' inválido");
        aserta (atacante_ == nullptr, "indexaFactorEquipos", "atacante asignado");
        //
        indice_factor_equipos = valor;
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::establecePersonajeElegido (ActorPersonaje * personaje) {
        aserta (personaje != nullptr, "establecePersonajeElegido", "parámetro 'personaje' inválido");
        aserta (personajeElegido (personaje->ladoTablero ()) == nullptr, 
                                      "establecePersonajeElegido", "personaje previamente elegido en su lado");
        aserta (atacante_ == nullptr, "establecePersonajeElegido", "atacante asignado");
        //
        if (personaje->ladoTablero () == LadoTablero::Izquierda) {
            personaje_elegido_izqrd = personaje;
        } else {
            personaje_elegido_derch = personaje;
        }
        //
        PresenciaActuante & presnc = juego_->tablero ()->presencia (personaje->ladoTablero ());
        aserta (! presnc.visible (), "establecePersonajeElegido", "ya hay un personaje visible en su lado");
        presnc.muestra (personaje);
        presnc.iluminaPuntosAccion (personaje->puntosAccion (), 0);
        presnc.refrescaBarraVida ();
        juego_->tablero ()->rejilla ().marcaCelda (personaje->sitioFicha (), ModoJuegoBase::color_elegido); 
        juego_->tablero ()->emiteSonidoEstablece ();
    }


    void ModoJuegoBase::anulaEleccionPersonajes () {
        aserta (atacante_ == nullptr, "anulaEleccionPersonajes", "atacante asignado");
        //
        personaje_elegido_izqrd = nullptr;
        personaje_elegido_derch = nullptr;
        //
        juego_->tablero ()->rejilla ().desmarcaCeldas (); 
        PresenciaActuante & presnc_izqrd = juego_->tablero ()->presencia (LadoTablero::Izquierda);
        if (presnc_izqrd.visible ()) {
            presnc_izqrd.oculta ();
        }
        PresenciaActuante & presnc_derch = juego_->tablero ()->presencia (LadoTablero::Derecha);
        if (presnc_derch.visible ()) {
            presnc_derch.oculta ();
        }
    }


    //----------------------------------------------------------------------------------------------


    LadoTablero ModoJuegoBase::eligeAtacanteIniciativa () {
        aserta (personaje_elegido_izqrd != nullptr, 
                                      "eligeAtacanteInicial", "personaje a la izquierda no elegido");
        aserta (personaje_elegido_derch != nullptr, 
                                      "eligeAtacanteInicial", "personaje a la derecha no elegido");
        aserta (atacante_ == nullptr, "eligeAtacanteInicial", "atacante asignado");
        //
        ActorPersonaje * persnj_izqrd = personajeElegido (LadoTablero::Izquierda);
        ActorPersonaje * persnj_derch = personajeElegido (LadoTablero::Derecha);
        if (persnj_izqrd->iniciativa () > persnj_derch->iniciativa ()) {
            return LadoTablero::Izquierda;;
        }
        if (persnj_izqrd->iniciativa () < persnj_derch->iniciativa ()) {
            return LadoTablero::Derecha;
        }
        //
        uint32_t azar = azarosa (2);
        if (azar == 0) {
            return LadoTablero::Izquierda;
        } else {
            return LadoTablero::Derecha;
        }
    }


    void ModoJuegoBase::estableceAtacante (LadoTablero lado_tablero) {
        aserta (lado_tablero != LadoTablero::nulo, 
                                      "estableceAtacante", "parámetro 'lado_tablero' inválido");
        aserta (personajeElegido (lado_tablero) != nullptr, 
                                      "estableceAtacante", "personaje no elegido en su lado");
        aserta (atacante_ == nullptr, "estableceAtacante", "atacante asignado");
        //
        atacante_        = personajeElegido (lado_tablero);
        modo_accion      = ModoAccionPersonaje::Nulo;
        etapas_camino    .clear ();
        habilidad_accion = nullptr;
        oponente_        = nullptr; 
        area_celdas      .clear ();
        //
        juego_->tablero ()->rejilla ().desmarcaCeldas (); 
        PresenciaActuante & presnc_izqrda = juego_->tablero ()->presencia (LadoTablero::Izquierda);
        if (presnc_izqrda.visible ()) {
            presnc_izqrda.oculta ();
        }
        PresenciaActuante & presnc_derch = juego_->tablero ()->presencia (LadoTablero::Derecha);
        if (presnc_derch.visible ()) {
            presnc_derch.oculta ();
        }
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (atacante_->ladoTablero ());
        presnc_ataca.muestra (atacante_);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), 0);
        presnc_ataca.refrescaBarraVida ();
        juego_->tablero ()->rejilla ().marcaCelda (atacante_->sitioFicha (), ModoJuegoBase::color_atacante, false);
    }


    void ModoJuegoBase::suprimeAtacante () {
        aserta (atacante_ != nullptr, "suprimeAtacante", "atacante no asignado");
        // posiblemente atacante agotado
        //
        area_celdas      .clear ();
        oponente_        = nullptr; 
        habilidad_accion = nullptr;
        etapas_camino    .clear ();
        modo_accion      = ModoAccionPersonaje::Nulo; 
        //
        PresenciaActuante & presnc_opone = juego_->tablero ()->presencia (opuesto (atacante_->ladoTablero ()));
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia(atacante_->ladoTablero ());
        aserta (! presnc_opone.visible (), "suprimeAtacante", "el oponente es visible");
        aserta (presnc_ataca.visible (),   "suprimeAtacante", "el atacante no es visible");
        presnc_ataca.oculta ();
        juego_->tablero ()->rejilla ().desmarcaCeldas ();
        //juego_->tablero ()->rejilla ().desmarcaCelda (atacante_->sitioFicha ());
        //
        atacante_ = nullptr;
    }


    void ModoJuegoBase::reiniciaAtacante () {
        aserta (atacante_ != nullptr, "reiniciaAtacante", "atacante no asignado");
        // atacante no agotado
        //
        area_celdas      .clear ();
        oponente_        = nullptr; 
        habilidad_accion = nullptr;
        etapas_camino    .clear ();
        modo_accion      = ModoAccionPersonaje::Nulo; 
        //
        PresenciaActuante & presnc_opone = juego_->tablero ()->presencia (opuesto (atacante_->ladoTablero ()));
        PresenciaActuante & presnc_ataca = juego_->tablero()->presencia(atacante_->ladoTablero());
        aserta (! presnc_opone.visible (), "reiniciaAtacante", "el oponente es visible");
        aserta (presnc_ataca.visible(),    "reiniciaAtacante", "el atacante no es visible");
        presnc_ataca.desmarcaRetratoHabilidad ();
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::estableceModoAccionDesplazam () {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr, "estableceAccionDesplazam", "atacante no asignado");
        //
        modo_accion      = ModoAccionPersonaje::Desplazamiento;
        habilidad_accion = nullptr;
        //
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (atacante_->ladoTablero ());
        presnc_ataca.marcaRetrato ();
        juego_->tablero ()->emiteSonidoEstablece ();
    }


    void ModoJuegoBase::estableceModoAccionHabilidad (int indice_habilidad) {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr, "estableceAccionHabilidad", "atacante no asignado");
        aserta (0 <= indice_habilidad && indice_habilidad < atacante_->habilidades ().size (),
                                      "estableceAccionHabilidad", "índice habilidad inválido");
        //
        modo_accion      = ModoAccionPersonaje::Habilidad;
        habilidad_accion = atacante_->habilidades () [indice_habilidad];
        //
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (atacante_->ladoTablero ());
        presnc_ataca.marcaHabilidad (indice_habilidad);
        juego_->tablero ()->emiteSonidoEstablece ();
    }


    void ModoJuegoBase::anulaModoAccion () {
        // solo usado en 'ModoJuegoComun'
        //
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (atacante_->ladoTablero ());
        presnc_ataca.desmarcaRetratoHabilidad ();
        //
        habilidad_accion = nullptr;
        modo_accion      = ModoAccionPersonaje::Nulo;
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::marcaCeldaInicio () {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr,           "marcaCeldaInicio", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "marcaCeldaInicio", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento,
                                                "marcaCeldaInicio", "modo de acción inválido");
        //
        if (juego_->tablero ()->vistaCamino ().celdaInicioMarcada ()) {
            return;
        }
        juego_->tablero ()->vistaCamino ().marcaCeldaInicio (atacante_->sitioFicha ());
    }


    void ModoJuegoBase::desmarcaCeldaInicio () {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr,           "desmarcaCeldaInicio", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "desmarcaCeldaInicio", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento,
                                                "desmarcaCeldaInicio", "modo de acción inválido");
        //
        juego_->tablero ()->vistaCamino ().desmarcaCeldaInicio ();
    }

        
    void ModoJuegoBase::iniciaCamino () {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr,           "iniciaCamino", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "iniciaCamino", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento,
                                                "iniciaCamino", "modo de acción inválido");
        //
        etapas_camino.push_back (atacante_->sitioFicha ());
        juego_->tablero ()->vistaCamino ().arrancaCamino ();
    }


    void ModoJuegoBase::validaEtapaCamino (
            Coord proxima_celda, bool & etapa_valida, int & puntos_en_juego) {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr,           "validaEtapaCamino", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "validaEtapaCamino", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento,
                                                "validaEtapaCamino", "modo de acción inválido");
        //
        if (! CalculoCaminos::celdaEnTablero (proxima_celda)) {
            etapa_valida = false;
            return;
        }
        if (CalculoCaminos::celdaOcupada (juego_, proxima_celda)) {
            etapa_valida = false;
            return;
        }
        if (! CalculoCaminos::etapaValidaCamino (juego_, proxima_celda)) {
            etapa_valida = false;
            return;
        }
        //
        puntos_en_juego = puntosEnJuegoCamino (proxima_celda);
        if (puntos_en_juego > atacante_->puntosAccion ()) {
            etapa_valida = false;
            return;
        }
        etapa_valida = true;
    }


    void ModoJuegoBase::marcaCeldaCamino (Coord proxima_celda, bool etapa_valida) {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr,           "marcaCeldaCamino", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "marcaCeldaCamino", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento,
                                                "marcaCeldaCamino", "modo de acción inválido");
        //
        Coord previa = etapas_camino.back ();
        juego_->tablero ()->vistaCamino ().marcaCeldaEtapa (proxima_celda, etapa_valida, previa);
    }


    void ModoJuegoBase::desmarcaCeldaCamino (Coord proxima_celda) {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr,           "desmarcaCeldaCamino", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "desmarcaCeldaCamino", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento,
                                                "desmarcaCeldaCamino", "modo de acción inválido");
        //
        juego_->tablero ()->vistaCamino ().desmarcaCeldaEtapa ();
    }


    void ModoJuegoBase::agregaEtapaCamino (Coord proxima_celda, int puntos_en_juego) {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr,           "agregaEtapaCamino", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "agregaEtapaCamino", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento,
                                                "agregaEtapaCamino", "modo de acción inválido");
        //
        etapas_camino.push_back (proxima_celda);
        juego_->tablero ()->vistaCamino ().fijaCeldaEtapa ();
        //
        atacante_->ponPuntosAccionEnJuego (puntos_en_juego);
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), puntos_en_juego);
    }


    void ModoJuegoBase::mueveFichaCamino () {
        aserta (atacante_ != nullptr,           "mueveFichaCamino", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "mueveFichaCamino", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento, 
                                                "mueveFichaCamino", "modo de acción erroneo");
        aserta (etapas_camino.size () > 0,      "mueveFichaCamino", "no hay etapas en el camino");
        //
        juego_->tablero ()->rejilla ().desmarcaCelda (atacante_->sitioFicha ());
        Coord nuevo_sitio = etapas_camino.back ();
        atacante_->ponSitioFicha (nuevo_sitio);
        etapas_camino.clear ();
        juego_->tablero ()->vistaCamino ().vaciaCamino ();
        juego_->tablero ()->rejilla ().marcaCelda (atacante_->sitioFicha (), ModoJuegoBase::color_atacante, false);
        atacante_->ponPuntosAccion (atacante_->puntosAccion () - atacante_->puntosAccionEnJuego ());
        atacante_->ponPuntosAccionEnJuego (0);
        if (atacante_->puntosAccion () == 0) {
            atacante_->presencia ().oscureceRetrato ();
        }
        //
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        aserta (presnc_ataca.visible (), "mueveFichaCamino", "el atacante no es visible");
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), 0);
        //
        juego_->tablero ()->emiteSonidoDesplaza ();
    }


    void ModoJuegoBase::anulaCamino () {
        // solo usado en 'ModoJuegoComun'
        //
        aserta (atacante_ != nullptr,           "anulaCamino", "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, "anulaCamino", "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Desplazamiento,
                                                "anulaCamino", "modo de acción inválido");
        //
        etapas_camino.clear ();
        juego_->tablero ()->vistaCamino ().vaciaCamino ();
        atacante_->ponPuntosAccionEnJuego (0);
        LadoTablero lado_atacante = atacante_->ladoTablero ();
        juego_->tablero ()->presencia (lado_atacante).iluminaPuntosAccion (atacante_->puntosAccion (), 0);
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::alea100 () {
        // solo usado en 'ModoJuegoComun'
        //
        valor_aleatorio_100 = azarosa (100);
    }


    void ModoJuegoBase::muestraAleatorio100 () {
        // solo usado en 'ModoJuegoComun'
        //
        int digt_1 = valor_aleatorio_100 / 10;
        int digt_2 = valor_aleatorio_100 % 10;
        juego_->tablero ()->muestraDisplay (digt_1, digt_2);
    }


    void ModoJuegoBase::ocultaAleatorio100 () {
        // solo usado en 'ModoJuegoComun'
        //
        juego_->tablero ()->borraDisplay ();
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::muestraAyudaGeneral () {
        // solo usado en 'ModoJuegoComun'
        //
        EscritorAyuda::escribeGeneral (* juego_);
        //
        juego_->tablero ()->emiteSonidoEstablece ();
    }


    void ModoJuegoBase::muestraAyudaPersonaje (ActorPersonaje * personaje) {
        // solo usado en 'ModoJuegoComun'
        //
        EscritorAyuda::escribePersonaje (* juego_, personaje);
        //
        juego_->tablero ()->emiteSonidoEstablece ();
    }


    void ModoJuegoBase::muestraAyudaCalculo () {
        // solo usado en 'ModoJuegoComun'
        //
        EscritorAyuda::escribeCalculo (* juego_);
        // 
        juego_->tablero ()->emiteSonidoEstablece ();
    }


    void ModoJuegoBase::sigueAyudaArriba () {
        // solo usado en 'ModoJuegoComun'
        //
        juego_->tablero ()->listadoAyuda ().deslizaArriba ();
     }


    void ModoJuegoBase::sigueAyudaAbajo () {
        // solo usado en 'ModoJuegoComun'
        //
        juego_->tablero ()->listadoAyuda ().deslizaAbajo ();
     }


    void ModoJuegoBase::ocultaAyuda () {
        // solo usado en 'ModoJuegoComun'
        //
        EscritorAyuda::borra (* juego_);
        //
        // no suena
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::validaHabilidadSimple (bool & uso_valido, int & puntos_en_juego) {
        // solo usado en 'ModoJuegoComun'
        //      
        asertaHabilidadSimple ("validaHabilidadSimple");
        // 
        puntos_en_juego = habilidad_accion->coste ();
        //
        if (puntos_en_juego > atacante_->puntosAccion ()) {
            uso_valido = false;
            return;
        }
        uso_valido = true;
    }


    void ModoJuegoBase::muestraHabilidadSimple (bool uso_valido, int puntos_en_juego) {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadSimple ("muestraHabilidadSimple");
        // 
        atacante_->ponPuntosAccionEnJuego (puntos_en_juego);
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), puntos_en_juego);
    }


    void ModoJuegoBase::ocultaHabilidadSimple () {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadSimple ("ocultaHabilidadSimple");
        // 
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), 0);
    }


    void ModoJuegoBase::aplicaHabilidadSimple () {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadSimple ("aplicaHabilidadSimple");
        // 
        juego_->sistemaAtaque ().calcula (atacante_, habilidad_accion);
        //
        atacante_->ponPuntosAccion (atacante_->puntosAccion () - atacante_->puntosAccionEnJuego ());
        atacante_->ponPuntosAccionEnJuego (0);
        if (atacante_->puntosAccion () == 0 ||
            atacante_->vitalidad ()    == 0   ) {
            atacante_->presencia ().oscureceRetrato ();
        }
        //
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), 0);
        presnc_ataca.refrescaBarraVida ();
        //presnc_ataca.desmarca ();
        //
        juego_->tablero ()->emiteSonidoHabilidad (habilidad_accion);
    }


    void ModoJuegoBase::asertaHabilidadSimple (const string & metodo) {
        aserta (atacante_ != nullptr,           metodo, "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, metodo, "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Habilidad,
                                                metodo, "modo de acción inválido");
        aserta (habilidad_accion != nullptr,    metodo, "habilidad nula");
        aserta (habilidad_accion->tipoEnfoque () == EnfoqueHabilidad::si_mismo,
                                                metodo, "enfoque habilidad inválido");
        aserta (habilidad_accion->tipoAcceso () == AccesoHabilidad::ninguno,
                                                metodo, "acceso habilidad inválido");
        aserta (habilidad_accion->antagonista () == Antagonista::si_mismo,
                                                metodo, "antagonista habilidad inválido");
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::estableceOponente (ActorPersonaje * personaje) {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadOponente ("estableceOponente", personaje);
        //
        oponente_ = personaje;
        if (oponente_->ladoTablero () == atacante_->ladoTablero ()) {
            return;
        }
        LadoTablero lado_opone = oponente_->ladoTablero ();
        PresenciaActuante & presnc_opone = juego_->tablero ()->presencia (lado_opone);
        presnc_opone.muestra (oponente_);
        presnc_opone.iluminaPuntosAccion (oponente_->puntosAccion (), 0);
        presnc_opone.refrescaBarraVida ();
        juego_->tablero ()->rejilla ().marcaCelda (oponente_->sitioFicha (), ModoJuegoBase::color_objetivo, true);
        //
        // no suena
        //juego_->tablero ()->emiteSonidoEstablece ();
    }


    void ModoJuegoBase::suprimeOponente () {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadOponente ("suprimeOponente", oponente_);
        //
        if (oponente_->ladoTablero () != atacante_->ladoTablero ()) {
            PresenciaActuante & presnc_opone = juego_->tablero ()->presencia (oponente_->ladoTablero ());
            if (presnc_opone.visible ()) {
                presnc_opone.oculta ();
            }
            juego_->tablero ()->rejilla ().desmarcaCelda (oponente_->sitioFicha ());
        }
        oponente_ = nullptr;
    }


    void ModoJuegoBase::validaAtaqueOponente (bool & acceso_valido, int & puntos_en_juego) {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadOponente ("validaAtaqueOponente", oponente_);
        //
        // no es así:
        //puntos_en_juego = puntosEnJuegoSegmento (
        //        atacante_->sitioFicha (), oponente_->sitioFicha ());
        puntos_en_juego = habilidad_accion->coste ();
        //
        float distn = distanciaCeldas (oponente_->sitioFicha (), atacante_->sitioFicha ()); 
        if (distn > habilidad_accion->alcance ()) {
            acceso_valido = false;
            return;
        }
        //
        if (habilidadAccion ()->tipoAcceso () == AccesoHabilidad::directo) {
            if (! CalculoCaminos::segmentoValido (
                    juego_, atacante_->sitioFicha (), oponente_->sitioFicha ())) {
                acceso_valido = false;
                return;
            }
        }
        if (puntos_en_juego > atacante_->puntosAccion ()) {
            acceso_valido = false;
            return;
        }
        acceso_valido = true;
    }


    void ModoJuegoBase::muestraAtaqueOponente (bool acceso_valido, int puntos_en_juego) {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadOponente ("muestraAtaqueOponente", oponente_);
        //
        if (habilidadAccion ()->tipoAcceso () == AccesoHabilidad::directo) {
            VistaCaminoCeldas & vista_camino = juego_->tablero ()->vistaCamino ();
            vista_camino.marcaCeldaInicio (atacante_->sitioFicha ());
            vista_camino.arrancaCamino ();
            vista_camino.marcaCeldaEtapa (
                    oponente_->sitioFicha (), acceso_valido, atacante_->sitioFicha ());
        }
        //
        atacante_->ponPuntosAccionEnJuego (puntos_en_juego);
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), puntos_en_juego);
    }


    void ModoJuegoBase::ocultaAtaqueOponente () {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadOponente ("ocultaAtaqueOponente", oponente_);
        //
        if (habilidadAccion ()->tipoAcceso () == AccesoHabilidad::directo) {
            VistaCaminoCeldas & vista_camino = juego_->tablero ()->vistaCamino ();
            vista_camino.vaciaCamino ();
        }
        //
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), 0);
    }


    void ModoJuegoBase::atacaOponente () {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadOponente ("atacaOponente", oponente_);
        //
        juego_->sistemaAtaque ().calcula (atacante_, habilidad_accion, oponente_, valor_aleatorio_100);
        //
        if (habilidadAccion ()->tipoAcceso () == AccesoHabilidad::directo) {
            VistaCaminoCeldas & vista_camino = juego_->tablero ()->vistaCamino ();
            vista_camino.vaciaCamino ();
        }
        if (oponente_->ladoTablero () != atacante_->ladoTablero ()) {
            PresenciaActuante & presnc_opone = juego_->tablero ()->presencia (oponente_->ladoTablero ());
            if (presnc_opone.visible ()) {
                presnc_opone.oculta ();
            }
            juego_->tablero ()->rejilla ().desmarcaCelda (oponente_->sitioFicha ());
        }
        //
        refrescaBarrasVida ();
        //
        refrescaPuntosAccion ();
        //presnc_ataca.desmarca ();
        //
        juego_->tablero ()->emiteSonidoHabilidad (habilidad_accion);
    }


    void ModoJuegoBase::asertaHabilidadOponente (const string & metodo, ActorPersonaje * oponentable) {
        aserta (atacante_ != nullptr,           metodo, "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, metodo, "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Habilidad,
                                                metodo, "modo de acción inválido");
        aserta (habilidad_accion != nullptr,    metodo, "habilidad nula");
        aserta (habilidad_accion->tipoEnfoque () == EnfoqueHabilidad::personaje,
                                                metodo, "enfoque habilidad inválido");
        aserta (habilidad_accion->tipoAcceso () != AccesoHabilidad::ninguno,
                                                metodo, "tipo de acceso inválido");
        aserta (habilidad_accion->antagonista () != Antagonista::si_mismo,
                                                metodo, "tipo de antagonista inválido");
        aserta (oponentable != nullptr,         metodo, "oponente no asignado");
        aserta (oponentable != atacante_,       metodo, "oponente igual a atacante");
        if (habilidad_accion->antagonista () == Antagonista::oponente) {
            aserta (oponentable->ladoTablero () != atacante_->ladoTablero (),
                                                metodo, "lado del tablero equivocado (el mismo)");
        } else {
            aserta (oponentable->ladoTablero () == atacante_->ladoTablero (),
                                                metodo, "lado del tablero equivocado (distinto)");
        }
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::estableceAreaHabilidad (Coord celda) {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadArea ("estableceAreaHabilidad", false);
        // 
        // ver comentario en AreaCentradaCeldas
        //
        CalculoCaminos::areaCeldas (juego_, celda, habilidad_accion->radioAlcance (), area_celdas);
        //
        // no suena
        //juego_->tablero ()->emiteSonidoEstablece ();
    }


    void ModoJuegoBase::anulaAreaHabilidad () {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadArea ("anulaAreaHabilidad", true);
        // 
        area_celdas.clear ();
    }


    void ModoJuegoBase::validaAtaqueArea  (bool & acceso_valido, int & puntos_en_juego) {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadArea ("validaAtaqueArea", true);
        // 
        // no es así:
        //puntos_en_juego = puntosEnJuegoSegmento (atacante_->sitioFicha (), celda_area);
        puntos_en_juego = habilidad_accion->coste ();
        //
        // ver comentario en AreaCentradaCeldas
        //
        Coord celda_area = area_celdas [0] [0];
        //
        if (! CalculoCaminos::celdaEnTablero (celda_area)) {
            acceso_valido = false;
            return;
        }
        if (CalculoCaminos::celdaEnMuro (juego_, celda_area)) {
            acceso_valido = false;
            return;
        }
        //
        float distn = distanciaCeldas (celda_area, atacante_->sitioFicha ()); 
        if (distn > habilidad_accion->alcance ()) {
            acceso_valido = false;
            return;
        }
        //
        if (habilidadAccion ()->tipoAcceso () == AccesoHabilidad::directo) {
            if (! CalculoCaminos::segmentoValido (juego_, atacante_->sitioFicha (), celda_area)) {
                acceso_valido = false;
                return;
            }
        }
        if (puntos_en_juego > atacante_->puntosAccion ()) {
            acceso_valido = false;
            return;
        }
        acceso_valido = true;
    }


    void ModoJuegoBase::muestraAtaqueArea (bool acceso_valido, int puntos_en_juego) {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadArea ("muestraAtaqueArea", true);
        // 
        marcaCeldasArea ();
        //
        if (habilidadAccion ()->tipoAcceso () == AccesoHabilidad::directo) {
            VistaCaminoCeldas & vista_camino = juego_->tablero ()->vistaCamino ();
            vista_camino.marcaCeldaInicio (atacante_->sitioFicha ());
            vista_camino.arrancaCamino ();
            Coord celda_area = area_celdas [0] [0];
            vista_camino.marcaCeldaEtapa (celda_area, acceso_valido, atacante_->sitioFicha ());
        }
        //
        atacante_->ponPuntosAccionEnJuego (puntos_en_juego);
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), puntos_en_juego);
    }


    void ModoJuegoBase::ocultaAtaqueArea () {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadArea ("ocultaAtaqueArea", true);
        // 
        desmarcaCeldasArea ();
        //
        if (habilidadAccion ()->tipoAcceso () == AccesoHabilidad::directo) {
            VistaCaminoCeldas & vista_camino = juego_->tablero ()->vistaCamino ();
            vista_camino.vaciaCamino ();
        }
        //
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), 0);
    }

    
    void ModoJuegoBase::atacaArea () {
        // solo usado en 'ModoJuegoComun'
        //
        asertaHabilidadArea ("atacaArea", true);
        // 
        std::vector <ActorPersonaje *> lista_oponentes {};
        personajesAreaCeldas (lista_oponentes);
        //
        juego_->sistemaAtaque ().calcula (
                atacante_, habilidad_accion, lista_oponentes, valor_aleatorio_100);
        //
        desmarcaCeldasArea ();
        if (habilidadAccion ()->tipoAcceso () == AccesoHabilidad::directo) {
            VistaCaminoCeldas & vista_camino = juego_->tablero ()->vistaCamino ();
            vista_camino.vaciaCamino ();
        }
        //
        refrescaBarrasVida ();
        //
        refrescaPuntosAccion ();
        //presnc_ataca.desmarca ();
        //
        juego_->tablero ()->emiteSonidoHabilidad (habilidad_accion);
    }

    
    void ModoJuegoBase::asertaHabilidadArea (const string & metodo, bool con_area) {
        aserta (atacante_ != nullptr,           metodo, "atacante no asignado");
        aserta (atacante_->puntosAccion () > 0, metodo, "atacante agotado");
        aserta (modo_accion == ModoAccionPersonaje::Habilidad,
                                                metodo, "modo de acción inválido");
        aserta (habilidad_accion != nullptr,    metodo, "habilidad nula");
        aserta (habilidad_accion->tipoEnfoque () == EnfoqueHabilidad::area,
                                                metodo, "enfoque habilidad inválido");
        aserta (habilidad_accion->tipoAcceso () != AccesoHabilidad::ninguno,
                                                metodo, "tipo de acceso inválido");
        aserta (habilidad_accion->antagonista () != Antagonista::si_mismo,
                                                metodo, "tipo de antagonista inválido");
        if (con_area) {
            aserta (! area_celdas.empty (),     metodo, "area de celdas vacía");
        }
    }
    

    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::iniciaTiempoCalculo () {
        juego_->tiempoCalculo ().inicia ();
    }


    void ModoJuegoBase::terminaTiempoCalculo () {
        juego_->tiempoCalculo ().termina ();
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::muestraIndicaActuante (LadoTablero lado_tablero) {
        // solo usado en 'ModoJuegoComun'
        //
        juego_->tablero ()->indicaPersonaje (
                lado_tablero, juego_->tablero ()->presencia (lado_tablero).personaje ()->nombre ());
    }


    void ModoJuegoBase::muestraIndicaHabilidad (LadoTablero lado_tablero, int indice_habilidad) {
        // solo usado en 'ModoJuegoComun'
        //
        PresenciaActuante & presnc = juego_->tablero ()->presencia (lado_tablero);
        Habilidad * habil = presnc.personaje ()->habilidades () [indice_habilidad];
        wstring tipo;
        switch (habil->tipoEnfoque ()) {
        case EnfoqueHabilidad::personaje:
            tipo = L"oponente";
            break;
        case EnfoqueHabilidad::area:
            if (habil->tipoAcceso () == AccesoHabilidad::directo) {
                tipo = L"área directa";
            } else {
                tipo = L"área indirecta";
            } 
            break;
        case EnfoqueHabilidad::si_mismo:
            tipo = L"simple";
            break;
        }
        wstring cadena = std::format (L"{} ({})", habil->nombre (), tipo);
        juego_->tablero ()->indicaHabilidad (lado_tablero, indice_habilidad, cadena);
    }


    void ModoJuegoBase::muestraIndicaFicha (ActorPersonaje * personaje) {
        // solo usado en 'ModoJuegoComun'
        //
        personaje->presencia ().indicaFicha (personaje->nombre ());
    }


    void ModoJuegoBase::ocultaIndicaciones () {
        // solo usado en 'ModoJuegoComun'
        //
        juego_->tablero ()->desindica ();
    }


    //----------------------------------------------------------------------------------------------


    bool ModoJuegoBase::rondasDisponibles () {
        //return limiteRondas () == 0 || ronda_ < limiteRondas ();
        return true;
    }


    bool ModoJuegoBase::turnosDisponiblesAmbos () {
        bool lado_izqrd = false;
        bool lado_derch = false;
        for (ActorPersonaje * persj : juego_->personajes ()) {
            if (persj->puntosAccion () > 0 && persj->vitalidad () > 0) {
                if (persj->ladoTablero () == LadoTablero::Izquierda) {
                    lado_izqrd = true;
                } else {
                    lado_derch = true;
                }
            }
        }
        return lado_izqrd && lado_derch;
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::anulaTotalmente () {
        lado_equipo_inicial = LadoTablero::nulo;
        lado_equipo_actual  = LadoTablero::nulo;
        factores_equipos.clear ();
        personaje_elegido_izqrd = nullptr;
        personaje_elegido_derch = nullptr;
        atacante_ = nullptr;
        modo_accion = ModoAccionPersonaje::Nulo;
        etapas_camino.clear ();
        juego_->tablero ()->vistaCamino ().vaciaCamino ();
        habilidad_accion = nullptr;
        oponente_ = nullptr;
        area_celdas.clear ();
    }


    //----------------------------------------------------------------------------------------------


    int ModoJuegoBase::azarosa (unsigned int contador) {
	    std::random_device semilla {};
        std::mt19937 generador {semilla ()};
	    std::uniform_int_distribution <unsigned int> distrb {0, contador - 1};
        return distrb (generador);
    }


    //----------------------------------------------------------------------------------------------


    int ModoJuegoBase::puntosEnJuegoCamino (Coord proxima_celda) const {
        float distn = 0.0f;
        for (int indc = 0; indc < etapas_camino.size (); ++ indc) {
            Coord previa = etapas_camino [indc];
            Coord etapa;
            if (indc == etapas_camino.size () - 1) {
                etapa = proxima_celda;
            } else {
                etapa = etapas_camino [indc + 1];
            }
            distn += unir2d::norma (
                    RejillaTablero::centroHexagono (etapa) -
                    RejillaTablero::centroHexagono (previa) );
        }
        int punts = static_cast <int> (std::round (distn / puntosAccionDeDesplaza ()));
        return punts;
    }


    float ModoJuegoBase::distanciaCeldas (Coord celda_origen, Coord celda_destino) const {
        float distn = unir2d::norma (
                RejillaTablero::centroHexagono (celda_destino) -
                RejillaTablero::centroHexagono (celda_origen)   );
        constexpr float unidad = static_cast <float> (RejillaTablero::ladoHexagono) * RejillaTablero::seno60_exacto * 2;
        return distn / unidad;
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::marcaCeldasArea () {
        for (int indc_radio = 0; indc_radio < area_celdas.size (); ++ indc_radio) {
            for (Coord celda : area_celdas [indc_radio]) {
                juego_->tablero ()->rejilla ().marcaCelda (celda, ModoJuegoBase::color_objetivo, true);
            }
        }
    }


    void ModoJuegoBase::desmarcaCeldasArea () {
        for (int indc_radio = 0; indc_radio < area_celdas.size (); ++ indc_radio) {
            for (Coord celda : area_celdas [indc_radio]) {
                juego_->tablero ()->rejilla ().desmarcaCelda (celda);
            }
        }
    }


    void ModoJuegoBase::personajesAreaCeldas (
            std::vector <ActorPersonaje *> & lista_oponentes) const {
        for (int indc_radio = 0; indc_radio < area_celdas.size (); ++ indc_radio) {
            for (Coord celda : area_celdas [indc_radio]) {
                for (ActorPersonaje * persj : juego_->personajes ()) {
                    if (persj->sitioFicha () == celda) {
                        lista_oponentes.push_back (persj);
                    }
                }
            }
        }
    }


    void ModoJuegoBase::iniciaPersonajes () {
        for (ActorPersonaje * persj : juego_->personajes ()) {
            persj->ponVitalidad (ActorPersonaje::maximaVitalidad);
            persj->presencia ().refrescaBarraVida ();
        }
    }


    void ModoJuegoBase::restauraPersonajes () {
        for (ActorPersonaje * persj : juego_->personajes ()) {
            persj->ponPuntosAccion (ActorPersonaje::maximoPuntosAccion);
            if (persj->vitalidad () > 0) {
                persj->presencia ().aclaraRetrato ();
            }
            for (TipoAtaque * ataque : juego_->ataques ()) {
                if (persj->apareceAtaque (ataque)) {
                    persj->restauraAtaque (ataque);
                }
            }
            for (TipoDefensa * defns : juego_->defensas ()) {
                if (persj->apareceDefensa (defns)) {
                    persj->restauraDefensa (defns);
                }
            }
        }
    }


    void ModoJuegoBase::refrescaBarrasVida () {
        for (ActorPersonaje * persj : juego_->personajes ()) {
            persj->presencia ().refrescaBarraVida ();
            if (persj->vitalidad () == 0) {
                persj->presencia ().oscureceRetrato ();
            }
        }
        PresenciaActuante & presnc_izqrd = juego_->tablero ()->presencia (LadoTablero::Izquierda);
        if (presnc_izqrd.visible ()) {
            presnc_izqrd.refrescaBarraVida ();
        } 
        PresenciaActuante & presnc_derch = juego_->tablero ()->presencia (LadoTablero::Derecha);
        if (presnc_derch.visible ()) {
            presnc_derch.refrescaBarraVida ();
        } 
    }


    void ModoJuegoBase::refrescaPuntosAccion () {
        atacante_->ponPuntosAccion (
                atacante_->puntosAccion () - atacante_->puntosAccionEnJuego ());
        atacante_->ponPuntosAccionEnJuego (0);
        if (atacante_->puntosAccion () == 0) {
            atacante_->presencia ().oscureceRetrato ();
        }
        LadoTablero lado_ataca = atacante_->ladoTablero ();
        PresenciaActuante & presnc_ataca = juego_->tablero ()->presencia (lado_ataca);
        presnc_ataca.iluminaPuntosAccion (atacante_->puntosAccion (), 0);
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::aserta (
            bool expresion, const string & metodo, const string & explicacion) const {
        if (expresion) {
            return;
        }
        throw ExcepcionValidacion {"ModoJuegoBase", metodo, explicacion};
    }


    //----------------------------------------------------------------------------------------------


    void ModoJuegoBase::almacenaInforme ( 
            const EstadoJuegoComun & estado,
            const string &           modulo, 
            const string &           metodo ) {
        informes_proceso.agregaInforme (estado, this, modulo, metodo);
    }


    const string ModoJuegoBase::textoInforme () const {
        return informes_proceso.textoInforme ();
    }


    void ModoJuegoBase::InformesProceso::agregaInforme (
                const EstadoJuegoComun & estado, 
                const ModoJuegoBase * proceso, 
                const string &           modulo, 
                const string &           metodo) {
        Informe * informe;
        prepara (informe);
        informe->tiempo  = std::chrono::system_clock::now (); 
        informe->estado  = estado.nombre ();
        informe->ronda_  = proceso->ronda_;
        informe->turno_  = proceso->turno_;
        informe->jugada_ = proceso->jugada_;
        informe->modulo  = modulo;
        informe->metodo  = metodo;
    }


    static string aString (std::chrono::system_clock::time_point momento) {
        std::time_t t = std::chrono::system_clock::to_time_t (momento);
        std::tm     tm {}; 
        localtime_s (& tm, & t);
        constexpr int ancho_buzon = 25;
        char buzon [ancho_buzon];
        std::strftime (buzon, ancho_buzon, "%T", & tm);
        return string {buzon};
    }


    const string ModoJuegoBase::InformesProceso::textoInforme () const {
        string retorno {};        
        for (int indc = 0; indc < lista_informes.size (); ++ indc) {
            Informe * informe = lista_informes [indc];
            if (informe == nullptr) {
                break;
            }
            retorno.append (aString (informe->tiempo));
            retorno.append (std::format ("  ( {}, {}, {} )", informe->ronda_,  informe->turno_, informe->jugada_));
            retorno.append (std::format ("  {:36}", informe->metodo));
            retorno.append (std::format ("  {}", informe->estado));
            retorno.append ("\n");
        }
        return retorno;
    }


    void ModoJuegoBase::InformesProceso::prepara (Informe * & informe) {
        int indc_vacio = -1;
        for (int indc = 0; indc < lista_informes.size (); ++ indc) {
            if (lista_informes [indc] == nullptr) {
                indc_vacio = indc;
                break;
            }
        }
        if (indc_vacio != -1) {
            informe = new Informe {};
            lista_informes [indc_vacio] = informe;
        } else {
            rota ();
            informe = lista_informes [lista_informes.size () - 1];
        }
    }


    void ModoJuegoBase::InformesProceso::rota () {
        Informe * primero = lista_informes [0];
        for (int indc = 1; indc < lista_informes.size (); ++ indc) {
            lista_informes [indc - 1] = lista_informes [indc];
        }
        lista_informes [lista_informes.size () - 1] = primero;
    }


}