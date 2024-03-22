// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoPares.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    ModoJuegoPares::ModoJuegoPares (JuegoMesaBase * juego) :
        estado_ {EstadoJuegoPares::inicial}, 
        estado_previo_ {EstadoJuegoPares::inicial}, 
        ModoJuegoComun {juego, estado_, estado_previo_} { 
    }


    EstadoJuegoPares & ModoJuegoPares::estado () {
        return estado_;
    }


    void ModoJuegoPares::entraPartida () {
        try {
            validaEstado ({ EstadoJuegoPares::inicial }); 
                            //  sin elegidos, sin atacante
            //
            assert (ModoJuegoBase::cuentaPersonajesIgual ());
            ModoJuegoBase::iniciaRondas ();
            //
            estado ().transita (EstadoJuegoPares::inicioRonda);
            validaAtributos ();
            informaProceso ("entraPartida");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraPartida", excepcion);
        }
    }


    void ModoJuegoPares::entraTurnoEleccion () {
        try {
            validaEstado ({ EstadoJuegoPares::inicioRonda }); 
                            //  sin elegidos, sin atacante
            //
            ModoJuegoBase::atenuaMusica ();
            estado ().transita (EstadoJuegoPares::inicioTurnoNoElegidos);
            validaAtributos ();
            informaProceso ("entraTurnoEleccion");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraTurnoEleccion", excepcion);
        }
    }


    void ModoJuegoPares::eligePrimerPersonaje (ActorPersonaje * personaje) {
        try {
            validaEstado ({ EstadoJuegoPares::inicioTurnoNoElegidos });
                            //  sin elegidos, sin atacante
            //
            if (personaje->vitalidad () == 0 || personaje->puntosAccion () == 0) {
                return;
            }
            ModoJuegoBase::establecePersonajeElegido (personaje);
            //
            estado ().transita (EstadoJuegoPares::inicioTurnoElegidoUno);
            validaAtributos ();
            informaProceso ("eligePrimerPersonaje");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("eligePrimerPersonaje", excepcion);
        }
    }


    void ModoJuegoPares::eligeSegundoPersonaje (ActorPersonaje * personaje) {
        try {
            validaEstado ({ EstadoJuegoPares::inicioTurnoElegidoUno });
                            //  elegido UNO, sin atacante
            //
            if (personajeElegido (personaje->ladoTablero ()) != nullptr) {
                return;
            }
            if (personaje->vitalidad () == 0 || personaje->puntosAccion () == 0) {
                return;
            }
            ModoJuegoBase::establecePersonajeElegido (personaje);
            //
            estado ().transita (EstadoJuegoPares::inicioTurnoConfirmacion);             
            validaAtributos ();
            informaProceso ("eligeSegundoPersonaje");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("eligeSegundoPersonaje", excepcion);
        }
    }


    void ModoJuegoPares::revierteInicioTurno () {
        try {
            validaEstado ({ EstadoJuegoPares::inicioTurnoConfirmacion });
                            //  elegidos AMBOS, sin atacante 
            //
            ModoJuegoBase::anulaEleccionPersonajes ();
            //
            estado ().transita (EstadoJuegoPares::inicioTurnoNoElegidos);
            validaAtributos ();
            informaProceso ("revierteInicioTurno");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("revierteInicioTurno", excepcion);
        }
    }


    void ModoJuegoPares::entraInicioJugada () {
        try {
            validaEstado ({ EstadoJuegoPares::inicioTurnoConfirmacion });
                            //  elegidos AMBOS, sin atacante 
            //
            LadoTablero lado = ModoJuegoBase::eligeAtacanteIniciativa ();
            ModoJuegoBase::estableceAtacante (lado);
            //
            estado ().transita (EstadoJuegoPares::inicioJugada);
            validaAtributos ();
            informaProceso ("entraInicioJugada");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraInicioJugada", excepcion);
        }
    }


    void ModoJuegoPares::mueveFicha () {
        try {
            validaEstado ({ EstadoJuegoComun::marcacionCaminoFicha });
                            //  elegidos AMBOS, con atacante (NO agotado), modo acción desplaza   
                            //  una o más etapas camino, sin HABILIDAD, sin OPONENTE, sin celda área
            //
            if (this->etapasCamino ().size () < 2) {
                return;
            }
            ModoJuegoBase::mueveFichaCamino ();
            bool inicio_jugada;
            bool ataca_agotado;
            bool final_turno;
            asume (inicio_jugada, ataca_agotado, final_turno);
            //
            if (inicio_jugada) {
                estado ().transita (EstadoJuegoComun::inicioJugada);
            } else if (ataca_agotado) {
                estado ().transita (EstadoJuegoPares::agotadosPuntosAccion);
            } else if (final_turno) {
                estado ().transita (EstadoJuegoPares::finalTurno);
            }
            validaAtributos ();
            informaProceso ("mueveFicha");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("mueveFicha", excepcion);
        }
    }


    void ModoJuegoPares::asumeHabilidad () {
        try {
            validaEstado ({ 
                    EstadoJuegoComun::habilidadSimpleResultado,
                    // elegidos AMBOS, con atacante (NO agotado), modo acción HABILIDAD   
                    // sin etapas camino, con HABILIDAD SIMPLE, sin OPONENTE, sin celda área
                    EstadoJuegoComun::oponenteHabilidadResultado,
                    // elegidos AMBOS, con atacante (NO agotado), modo acción HABILIDAD   
                    // sin etapas camino, con HABILIDAD OPONENTE, con OPONENTE, sin celda área
                    EstadoJuegoComun::areaHabilidadResultado });
                    // elegidos AMBOS, con atacante (NO agotado), modo acción HABILIDAD   
                    // sin etapas camino, con HABILIDAD área, sin OPONENTE, con celda área
            //
            ModoJuegoBase::ocultaAleatorio100 ();
            bool inicio_jugada;
            bool ataca_agotado;
            bool final_turno;
            asume (inicio_jugada, ataca_agotado, final_turno);
            //
            if (inicio_jugada) {
                estado ().transita (EstadoJuegoComun::inicioJugada);
            } else if (ataca_agotado) {
                estado ().transita (EstadoJuegoPares::agotadosPuntosAccion);
            } else if (final_turno) {
                estado ().transita (EstadoJuegoPares::finalTurno);
            }
            validaAtributos ();
            informaProceso ("asumeHabilidad");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("asumeHabilidad", excepcion);
        }
    }


    void ModoJuegoPares::asume (
            bool & inicio_jugada, 
            bool & ataca_agotado, 
            bool & final_turno   ) {
        inicio_jugada = false;
        ataca_agotado = false;
        final_turno   = false;
        LadoTablero lado_activo = atacante ()->ladoTablero ();
        ModoJuegoBase::suprimeAtacante ();
        ModoJuegoBase::estableceAtacante (opuesto (lado_activo));
        ModoJuegoBase::avanzaJugada ();
        if (atacante ()->vitalidad () > 0 && atacante ()->puntosAccion () > 0) {
            inicio_jugada = true;
        } else {
            LadoTablero lado = atacante ()->ladoTablero ();
            ActorPersonaje * persj = personajeElegido (opuesto (lado));
            if (persj->vitalidad () > 0 && persj->puntosAccion () > 0) {
                ataca_agotado = true;
            } else {
                final_turno = true;
            }
        }
    }


    void ModoJuegoPares::ignoraPersonajeAgotado () {
        try {
            validaEstado ({ EstadoJuegoPares::agotadosPuntosAccion });
                            //  elegidos AMBOS, con atacante (agotado), modo acción NULO   
                            //  sin etapas camino, sin HABILIDAD, sin OPONENTE, sin celda área
            //
            LadoTablero lado_activo = atacante ()->ladoTablero ();
            ModoJuegoBase::suprimeAtacante ();
            ModoJuegoBase::estableceAtacante (opuesto (lado_activo));
            // 
            estado ().transita (EstadoJuegoPares::inicioJugada);
            validaAtributos ();
            informaProceso ("ignoraPersonajeAgotado");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("ignoraPersonajeAgotado", excepcion);
        }
    }


    void ModoJuegoPares::reiniciaTurno () {
        try {
            validaEstado ({ EstadoJuegoPares::finalTurno });
                            //  elegidos AMBOS, con atacante (agotado), modo acción NULO      
                            //  sin etapas camino, sin HABILIDAD, sin OPONENTE, sin celda área
            //
            ModoJuegoBase::suprimeAtacante ();
            ModoJuegoBase::anulaEleccionPersonajes ();
            //
            bool final_ronda   = false;
            bool final_partida = false;
            if (ModoJuegoBase::turnosDisponiblesAmbos ()) {
                ModoJuegoBase::avanzaTurno ();
            } else {
                final_ronda = true;
                if (ModoJuegoBase::rondasDisponibles ()) {
                    ModoJuegoBase::avanzaRonda ();
                } else {
                    final_partida = true;
                }
            }
            //
            if (final_partida) {
                estado ().transita (EstadoJuegoPares::finalPartida);
            } else {
                if (final_ronda) {
                    estado ().transita (EstadoJuegoPares::inicioRonda);
                } else {
                    estado ().transita (EstadoJuegoPares::inicioTurnoNoElegidos);
                }
            }
            validaAtributos ();
            informaProceso ("reiniciaTurno");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("reiniciaTurno", excepcion);
        }
    }


    void ModoJuegoPares::escribeEstado () {
        switch (estado ()) {
        case EstadoJuegoPares::inicioRonda:
            if (ronda () == 1) {
                juego ()->tablero ()->escribeMonitor (std::vector <string> 
                        { "Inicio de la partida.",
                          "Ronda de juego 1.",
                          "Pulsa 'espacio'."      },
                        {}                          );
            } else {
                juego ()->tablero ()->escribeMonitor (std::vector <string> 
                        { std::format ("Ronda de juego {}.", this->ronda ()),
                          "Pulsa 'espacio'."                                  },
                        {}                                                      );
            }
            break;
        case EstadoJuegoPares::inicioTurnoNoElegidos:
            if (ronda () == 1 && turno () == 1) {
                juego ()->tablero ()->escribeMonitor (std::vector <string> 
                        { "Selecciona un personaje.",
                          "Pulsa un retrato." },
                        {}                                  );
            } else {
                if (turno () == 1) {
                    juego ()->tablero ()->escribeMonitor (std::vector <string> 
                            { "Selecciona un personaje." },
                            {}                             );
                } else {
                    juego ()->tablero ()->escribeMonitor (std::vector <string> 
                            { "Nueva turno de juego.",
                              "Selecciona un personaje." },
                            {}                             );
                }
            }
            break;
        case EstadoJuegoPares::inicioTurnoElegidoUno:
            if (personajeElegido (LadoTablero::Izquierda) == nullptr) {
                juego ()->tablero ()->escribeMonitor (std::vector <string>  
                        { "Selecciona un segundo personaje del",
                          "equipo rojo."                        },
                        {}                                        );
            } else {
                juego ()->tablero ()->escribeMonitor (std::vector <string> 
                        { "Selecciona un segundo personaje del",
                          "equipo azul."                        },
                        {}                                        );           
            }
            break;
        case EstadoJuegoPares::inicioTurnoConfirmacion:
            juego ()->tablero ()->escribeMonitor (std::vector <string>  
                    { "Pulsa 'espacio' para confirmar, 'Esc'",
                      "para reintentar."                      },
                    {}                                          );
            break;
        case EstadoJuegoPares::agotadosPuntosAccion:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Puntos de acción agotados.",
                      L"Pulsa 'espacio'."           },
                    {}                               );
            break;
        case EstadoJuegoPares::finalTurno:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Agotados los puntos de acción de AMBOS",
                      L"personajes.",
                      L"Pulsa 'espacio'."                       },
                    {}                                            );
            break;
        default:
            ModoJuegoComun::escribeEstado ();
            break;
        } 
    }


    const string ModoJuegoPares::nombreModulo () {
        return "ModoJuegoPares";
    }


    void ModoJuegoPares::validaAtributos () {
        switch (estado ()) {
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        //                         | estado                      |        | equipo   | equipo   | elegidos | atacante | vivo   | agotado | modo      | etapas | habilidad | tipo     | personaje | área     |
        //                         |                             |        | inicial  | actual   |          |          |        |         | acción    | camino |           | accion   |           | celdas   |
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        case EstadoJuegoPares     ::inicial                      : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::terminal                     : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::inicioRonda                  : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::inicioTurnoNoElegidos        : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::inicioTurnoElegidoUno        : valida ( NULO     , NULO     , UNO      , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::inicioTurnoConfirmacion      : valida ( NULO     , NULO     , AMBOS    , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::inicioJugada                 : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::preparacionDesplazamiento    : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , DESPLAZAM , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::marcacionCaminoFicha         : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , DESPLAZAM , VARIOS , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::habilidadSimpleInvalida      : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::habilidadSimpleConfirmacion  : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::habilidadSimpleResultado     : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::preparacionHabilidadOponente : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::oponenteHabilidadInvalido    : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoPares     ::oponenteHabilidadConfirmacion: valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoPares     ::oponenteHabilidadCalculando  : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoPares     ::oponenteHabilidadResultado   : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoPares     ::preparacionHabilidadArea     : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::areaHabilidadInvalida        : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoPares     ::areaHabilidadConfirmacion    : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoPares     ::areaHabilidadCalculando      : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoPares     ::areaHabilidadResultado       : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoPares     ::agotadosPuntosAccion         : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , ignora , ignora  , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::finalTurno                   : valida ( NULO     , NULO     , AMBOS    , ASIGNADO , ignora , ignora  , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoPares     ::mostrandoAyuda               : valida ( ignora   , ignora   , ignora   , ignora   , ignora , ignora  , ignora    , ignora , ignora    , ignora   , ignora    , ignora   ); break;
        case EstadoJuegoPares     ::finalPartida                 : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        }
    }


}


