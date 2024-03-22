// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoLibreDoble.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    ModoJuegoLibreDoble::ModoJuegoLibreDoble (JuegoMesaBase * juego) :
        estado_ {EstadoJuegoPares::inicial}, 
        estado_previo_ {EstadoJuegoPares::inicial}, 
        ModoJuegoComun {juego, estado_, estado_previo_} { 
    }


    EstadoJuegoLibreDoble & ModoJuegoLibreDoble::estado () {
        return estado_;
    }


    void ModoJuegoLibreDoble::entraPartida () {
        try {
            validaEstado ({ EstadoJuegoLibreDoble::inicial }); 
                            //  sin elegidos, sin atacante
            //
            assert (ModoJuegoBase::cuentaPersonajesIgual ());
            LadoTablero lado_inicial = ModoJuegoBase::eligeEquipoIniciativa ();
            ModoJuegoBase::asignaEquipoActual (lado_inicial);
            ModoJuegoBase::iniciaRondas ();
            //
            estado ().transita (EstadoJuegoLibreDoble::inicioRonda);
            validaAtributos ();
            informaProceso ("entraPartida");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraPartida", excepcion);
        }
    }


    void ModoJuegoLibreDoble::entraTurnoEleccion () {
        try {
            validaEstado ({ EstadoJuegoLibreDoble::inicioRonda }); 
                            //  sin elegidos, sin atacante
            //
            ModoJuegoBase::atenuaMusica ();
            estado ().transita (EstadoJuegoLibreDoble::inicioTurnoNoElegido);
            validaAtributos ();
            informaProceso ("entraTurnoEleccion");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraTurnoEleccion", excepcion);
        }
    }


    void ModoJuegoLibreDoble::eligePersonaje (ActorPersonaje * personaje) {
        try {
            validaEstado ({ EstadoJuegoLibreDoble::inicioTurnoNoElegido });
                            //  sin elegidos, sin atacante
            //
            if (personaje->vitalidad () == 0 || personaje->puntosAccion () == 0) {
                return;
            }
            if (personaje->ladoTablero () != ladoEquipoActual ()) {
                return;
            }
            ModoJuegoBase::establecePersonajeElegido (personaje);
            //
            estado ().transita (EstadoJuegoLibreDoble::inicioTurnoConfirmacion);             
            validaAtributos ();
            informaProceso ("eligePersonaje");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("eligePersonaje", excepcion);
        }
    }


    void ModoJuegoLibreDoble::revierteInicioTurno () {
        try {
            validaEstado ({ EstadoJuegoLibreDoble::inicioTurnoConfirmacion });
                            //  elegidos ambos, sin atacante 
            //
            ModoJuegoBase::anulaEleccionPersonajes ();
            //
            estado ().transita (EstadoJuegoLibreDoble::inicioTurnoNoElegido);
            validaAtributos ();
            informaProceso ("revierteInicioTurno");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("revierteInicioTurno", excepcion);
        }
    }


    void ModoJuegoLibreDoble::entraInicioJugada () {
        try {
            validaEstado ({ EstadoJuegoLibreDoble::inicioTurnoConfirmacion });
                            //  elegidos ambos, sin atacante 
            //
            ModoJuegoBase::estableceAtacante (ladoEquipoActual ());
            //
            estado ().transita (EstadoJuegoLibreDoble::inicioJugada);
            validaAtributos ();
            informaProceso ("entraInicioJugada");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraInicioJugada", excepcion);
        }
    }


    void ModoJuegoLibreDoble::mueveFicha () {
        try {
            validaEstado ({ EstadoJuegoComun::marcacionCaminoFicha });
                            //  elegidos ambos, con atacante (no agotado), modo acción desplaza   
                            //  una o más etapas camino, sin habilidad, sin personaje, sin celda área
            //
            if (this->etapasCamino ().size () < 2) {
                return;
            }
            ModoJuegoBase::mueveFichaCamino ();
            bool inicio_jugada; 
            bool ataca_agotado; 
            bool inicio_turno; 
            bool inicio_ronda; 
            bool final_partida;
            asume (inicio_jugada, ataca_agotado, inicio_turno, inicio_ronda, final_partida);
            //
            if (inicio_jugada) {
                estado ().transita (EstadoJuegoComun::inicioJugada);
            } else if (ataca_agotado) {
                estado ().transita (EstadoJuegoLibreDoble::agotadosPuntosAccion);
            } else if (inicio_turno) {
                estado ().transita (EstadoJuegoLibreDoble::inicioTurnoNoElegido);
            } else if (inicio_ronda) {
                estado ().transita (EstadoJuegoLibreDoble::inicioRonda);
            } else if (final_partida) {
                estado ().transita (EstadoJuegoComun::finalPartida);
            } 
            validaAtributos ();
            informaProceso ("mueveFicha");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("mueveFicha", excepcion);
        }
    }


    void ModoJuegoLibreDoble::asumeHabilidad () {
        try {
            validaEstado ({ 
                    EstadoJuegoComun::habilidadSimpleResultado,
                    // elegidos ambos, con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad simple, sin personaje, sin celda área
                    EstadoJuegoComun::oponenteHabilidadResultado,
                    // elegidos ambos, con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad personaje, con personaje, sin celda área
                    EstadoJuegoComun::areaHabilidadResultado });
                    // elegidos ambos, con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad área, sin personaje, con celda área
            //
            ModoJuegoBase::ocultaAleatorio100 ();
            bool inicio_jugada; 
            bool ataca_agotado; 
            bool inicio_turno; 
            bool inicio_ronda; 
            bool final_partida;
            asume (inicio_jugada, ataca_agotado, inicio_turno, inicio_ronda, final_partida);
            //
            if (inicio_jugada) {
                estado ().transita (EstadoJuegoComun::inicioJugada);
            } else if (ataca_agotado) {
                estado ().transita (EstadoJuegoLibreDoble::agotadosPuntosAccion);
            } else if (inicio_turno) {
                estado ().transita (EstadoJuegoLibreDoble::inicioTurnoNoElegido);
            } else if (inicio_ronda) {
                estado ().transita (EstadoJuegoLibreDoble::inicioRonda);
            } else if (final_partida) {
                estado ().transita (EstadoJuegoComun::finalPartida);
            } 
            validaAtributos ();
            informaProceso ("asumeHabilidad");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("asumeHabilidad", excepcion);
        }
    }


    void ModoJuegoLibreDoble::ignoraPersonajeAgotado () {
        try {
            validaEstado ({ EstadoJuegoLibreDoble::agotadosPuntosAccion });
                            //  elegidos ambos, con atacante (agotado), modo acción nulo   
                            //  sin etapas camino, sin habilidad, sin personaje, sin celda área
            //
            ModoJuegoBase::suprimeAtacante ();
            ModoJuegoBase::anulaEleccionPersonajes ();
            ModoJuegoBase::asignaEquipoActual (opuesto (ladoEquipoActual ()));
            bool inicio_turno  = false; 
            bool inicio_ronda  = false; 
            bool final_partida = false;
            if (turnosDisponiblesAmbos ()) {
                ModoJuegoBase::avanzaTurno ();
                inicio_turno = true;
            } else {
                if (rondasDisponibles ()) {
                    ModoJuegoBase::avanzaRonda ();
                    inicio_ronda = true;
                } else {
                    ModoJuegoBase::asignaEquipoActual (LadoTablero::nulo);            
                    final_partida = true;
                }
            }
            // 
            if (inicio_turno) {
                estado ().transita (EstadoJuegoLibreDoble::inicioTurnoNoElegido);
            } else if (inicio_ronda) {
                estado ().transita (EstadoJuegoLibreDoble::inicioRonda);
            } else if (final_partida) {
                estado ().transita (EstadoJuegoComun::finalPartida);
            } 
            validaAtributos ();
            informaProceso ("ignoraPersonajeAgotado");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("ignoraPersonajeAgotado", excepcion);
        }
    }


    void ModoJuegoLibreDoble::asume (
            bool & inicio_jugada, 
            bool & ataca_agotado, 
            bool & inicio_turno, 
            bool & inicio_ronda, 
            bool & final_partida) {
        inicio_jugada = false;
        ataca_agotado = false;
        inicio_turno  = false;
        inicio_ronda  = false;
        final_partida = false;
        if (jugada () > 1) {
            ModoJuegoBase::suprimeAtacante ();
            ModoJuegoBase::anulaEleccionPersonajes ();
            ModoJuegoBase::asignaEquipoActual (opuesto (ladoEquipoActual ()));
            if (turnosDisponiblesAmbos ()) {
                ModoJuegoBase::avanzaTurno ();
                inicio_turno = true;
            } else {
                if (rondasDisponibles ()) {
                    ModoJuegoBase::avanzaRonda ();
                    inicio_ronda = true;
                } else {
                    ModoJuegoBase::asignaEquipoActual (LadoTablero::nulo);            
                    final_partida = true;
                }
            }
        } else {
            ModoJuegoBase::reiniciaAtacante ();
            if (atacante ()->vitalidad () == 0 || atacante ()->puntosAccion () == 0) {
                ataca_agotado = true;
            } else {
                ModoJuegoBase::avanzaJugada ();
                inicio_jugada = true;
            }
        }
    }


    void ModoJuegoLibreDoble::escribeEstado () {
        string juga {}; 
        switch (estado ()) {
        case EstadoJuegoLibreDoble::inicioRonda:
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
        case EstadoJuegoLibreDoble::inicioTurnoNoElegido:
            if (ladoEquipoActual () == LadoTablero::Izquierda) {
                juego ()->tablero ()->escribeMonitor (std::vector <string>  
                        { "Selecciona un personaje del equipo",
                          "rojo.",
                          "Pulsa un retrato."            },
                        {}                                             );
            } else {
                juego ()->tablero ()->escribeMonitor (std::vector <string> 
                        { "Selecciona un personaje del equipo",
                          "azul.",
                          "Pulsa un retrato."       },
                        {}                                        );           
            }
            break;
        case EstadoJuegoLibreDoble::inicioTurnoConfirmacion:
            juego ()->tablero ()->escribeMonitor (std::vector <string>  
                    { "Pulsa 'espacio' para confirmar, 'Esc'",
                      "para reintentar."                      },
                    {}                                          );
            break;
        case EstadoJuegoComun::inicioJugada:
            if (jugada () == 1) {
                juga = "Primera jugada";
            } else {
                juga = "Segunda jugada.";
            }
            juego ()->tablero ()->escribeMonitor (std::vector <string>
                    { juga,
                        "Selecciona el retrato para mover la",
                        "ficha o selecciona una habilidad."   },
                    {}                                        );
            break;
        case EstadoJuegoLibreDoble::agotadosPuntosAccion:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Puntos de acción agotados.",
                      L"Pulsa 'espacio'."           },
                    {}                               );
            break;
        default:
            ModoJuegoComun::escribeEstado ();
            break;
        } 
    }


    const string ModoJuegoLibreDoble::nombreModulo () {
        return "ModoJuegoLibreDoble";
    }


    void ModoJuegoLibreDoble::validaAtributos () {
        switch (estado ()) {
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        //                         | estado                      |        | equipo   | equipo   | elegidos | atacante | vivo   | agotado | modo      | etapas | habilidad | tipo     | personaje | área     |
        //                         |                             |        | inicial  | actual   |          |          |        |         | acción    | camino |           | accion   |           | celdas   |
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        case EstadoJuegoLibreDoble::inicial                      : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::terminal                     : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::inicioRonda                  : valida ( NULO     , ASIGNADO , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::inicioTurnoNoElegido         : valida ( NULO     , ASIGNADO , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        //                                                                                                                                                                                                                   
        case EstadoJuegoLibreDoble::inicioTurnoConfirmacion      : valida ( NULO     , ASIGNADO , UNO      , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::inicioJugada                 : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::preparacionDesplazamiento    : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , DESPLAZAM , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::marcacionCaminoFicha         : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , DESPLAZAM , VARIOS , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::habilidadSimpleInvalida      : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::habilidadSimpleConfirmacion  : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::habilidadSimpleResultado     : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::preparacionHabilidadOponente : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::oponenteHabilidadInvalido    : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoLibreDoble::oponenteHabilidadConfirmacion: valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoLibreDoble::oponenteHabilidadCalculando  : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoLibreDoble::oponenteHabilidadResultado   : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoLibreDoble::preparacionHabilidadArea     : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , VACIO    ); break;
        case EstadoJuegoLibreDoble::areaHabilidadInvalida        : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoLibreDoble::areaHabilidadConfirmacion    : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoLibreDoble::areaHabilidadCalculando      : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoLibreDoble::areaHabilidadResultado       : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoLibreDoble::agotadosPuntosAccion         : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , ignora , ignora  , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        //                                                                                                                                                                                                                  
        case EstadoJuegoLibreDoble::mostrandoAyuda               : valida ( ignora   , ignora   , ignora   , ignora   , ignora , ignora  , ignora    , ignora , ignora    , ignora   , ignora    , ignora   ); break;
        case EstadoJuegoLibreDoble::finalPartida                 : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        }
    }


}






