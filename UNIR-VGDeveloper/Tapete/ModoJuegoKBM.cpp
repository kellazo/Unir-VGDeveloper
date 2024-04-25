// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoKBM.cpp
// versión:  1.1  (7-Abr-2024)


#include "tapete.h"


namespace tapete {


    ModoJuegoKBM::ModoJuegoKBM (JuegoMesaBase * juego) :
        estado_ {EstadoJuegoPares::inicial}, 
        estado_previo_ {EstadoJuegoPares::inicial}, 
        ModoJuegoComun {juego, estado_, estado_previo_} { 
    }


    EstadoJuegoKBM & ModoJuegoKBM::estado () {
        return estado_;
    }


    void ModoJuegoKBM::entraPartida () {
        try {
            validaEstado ({ EstadoJuegoKBM::inicial }); 
                            //  sin elegidos, sin atacante
            //
            assert (ModoJuegoBase::cuentaPersonajesIgual ());
            LadoTablero lado_inicial = ModoJuegoBase::eligeEquipoIniciativa ();
            ModoJuegoBase::asignaEquipoActual (lado_inicial);
            ModoJuegoBase::iniciaRondas ();
            //
            estado ().transita (EstadoJuegoKBM::inicioRonda);
            validaAtributos ();
            informaProceso ("entraPartida");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraPartida", excepcion);
        }
    }


    void ModoJuegoKBM::entraTurnoEleccion () {
        try {
            validaEstado ({ EstadoJuegoKBM::inicioRonda }); 
                            //  sin elegidos, sin atacante
            //
            ModoJuegoBase::atenuaMusica ();
            estado ().transita (EstadoJuegoKBM::inicioTurnoNoElegido);
            validaAtributos ();
            informaProceso ("entraTurnoEleccion");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraTurnoEleccion", excepcion);
        }
    }


    void ModoJuegoKBM::eligePersonaje (ActorPersonaje * personaje) {
        try {
            validaEstado ({ EstadoJuegoKBM::inicioTurnoNoElegido });
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
            estado ().transita (EstadoJuegoKBM::inicioTurnoConfirmacion);             
            validaAtributos ();
            informaProceso ("eligePersonaje");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("eligePersonaje", excepcion);
        }
    }


    void ModoJuegoKBM::revierteInicioTurno () {
        try {
            validaEstado ({ EstadoJuegoKBM::inicioTurnoConfirmacion });
                            //  elegidos ambos, sin atacante 
            //
            ModoJuegoBase::anulaEleccionPersonajes ();
            //
            estado ().transita (EstadoJuegoKBM::inicioTurnoNoElegido);
            validaAtributos ();
            informaProceso ("revierteInicioTurno");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("revierteInicioTurno", excepcion);
        }
    }


    void ModoJuegoKBM::entraInicioJugada () {
        try {
            validaEstado ({ EstadoJuegoKBM::inicioTurnoConfirmacion });
                            //  elegidos ambos, sin atacante 
            //
            ModoJuegoBase::estableceAtacante (ladoEquipoActual ());
            //
            estado ().transita (EstadoJuegoKBM::inicioJugada);
            validaAtributos ();
            informaProceso ("entraInicioJugada");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraInicioJugada", excepcion);
        }
    }


    void ModoJuegoKBM::mueveFicha () {
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
                estado ().transita (EstadoJuegoKBM::agotadosPuntosAccion);
            } else if (inicio_turno) {
                estado ().transita (EstadoJuegoKBM::inicioTurnoNoElegido);
            } else if (inicio_ronda) {
                estado ().transita (EstadoJuegoKBM::inicioRonda);
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


    void ModoJuegoKBM::asumeHabilidad () {
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
                estado ().transita (EstadoJuegoKBM::agotadosPuntosAccion);
            } else if (inicio_turno) {
                estado ().transita (EstadoJuegoKBM::inicioTurnoNoElegido);
            } else if (inicio_ronda) {
                estado ().transita (EstadoJuegoKBM::inicioRonda);
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


    void ModoJuegoKBM::ignoraPersonajeAgotado () {
        try {
            validaEstado ({ EstadoJuegoKBM::agotadosPuntosAccion });
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
                estado ().transita (EstadoJuegoKBM::inicioTurnoNoElegido);
            } else if (inicio_ronda) {
                estado ().transita (EstadoJuegoKBM::inicioRonda);
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


    void ModoJuegoKBM::asume (
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
        ModoJuegoBase::reiniciaAtacante ();
        if (atacante ()->vitalidad () == 0 || atacante ()->puntosAccion () == 0) {
            ataca_agotado = true;
        } else {
            ModoJuegoBase::avanzaJugada ();
            inicio_jugada = true;
        }
    }


    void ModoJuegoKBM::escribeEstado () {
        string juga {}; 
        switch (estado ()) {
        case EstadoJuegoKBM::inicioRonda:
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
        case EstadoJuegoKBM::inicioTurnoNoElegido:
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
        case EstadoJuegoKBM::inicioTurnoConfirmacion:
            juego ()->tablero ()->escribeMonitor (std::vector <string>  
                    { "Pulsa 'espacio' para confirmar, 'Esc'",
                      "para reintentar."                      },
                    {}                                          );
            break;
        case EstadoJuegoComun::inicioJugada:
            juego ()->tablero ()->escribeMonitor (std::vector <string>
                    { juga,
                        "Selecciona el retrato para mover la",
                        "ficha o selecciona una habilidad."   },
                    {}                                        );
            break;
        case EstadoJuegoKBM::agotadosPuntosAccion:
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


    const string ModoJuegoKBM::nombreModulo () {
        return "ModoJuegoKBM";
    }


    void ModoJuegoKBM::validaAtributos () {
        switch (estado ()) {
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        //                         | estado                      |        | equipo   | equipo   | elegidos | atacante | vivo   | agotado | modo      | etapas | habilidad | tipo     | personaje | área     |
        //                         |                             |        | inicial  | actual   |          |          |        |         | acción    | camino |           | accion   |           | celdas   |
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        case EstadoJuegoKBM::inicial                      : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::terminal                     : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::inicioRonda                  : valida ( NULO     , ASIGNADO , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::inicioTurnoNoElegido         : valida ( NULO     , ASIGNADO , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        //                                                                                                                                                                                                                   
        case EstadoJuegoKBM::inicioTurnoConfirmacion      : valida ( NULO     , ASIGNADO , UNO      , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::inicioJugada                 : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::preparacionDesplazamiento    : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , DESPLAZAM , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::marcacionCaminoFicha         : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , DESPLAZAM , VARIOS , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::habilidadSimpleInvalida      : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::habilidadSimpleConfirmacion  : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::habilidadSimpleResultado     : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::preparacionHabilidadOponente : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::oponenteHabilidadInvalido    : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoKBM::oponenteHabilidadConfirmacion: valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoKBM::oponenteHabilidadCalculando  : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoKBM::oponenteHabilidadResultado   : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoKBM::preparacionHabilidadArea     : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , VACIO    ); break;
        case EstadoJuegoKBM::areaHabilidadInvalida        : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoKBM::areaHabilidadConfirmacion    : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoKBM::areaHabilidadCalculando      : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoKBM::areaHabilidadResultado       : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoKBM::agotadosPuntosAccion         : valida ( NULO     , ASIGNADO , UNO      , ASIGNADO , ignora , ignora  , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        //                                                                                                                                                                                                                  
        case EstadoJuegoKBM::mostrandoAyuda               : valida ( ignora   , ignora   , ignora   , ignora   , ignora , ignora  , ignora    , ignora , ignora    , ignora   , ignora    , ignora   ); break;
        case EstadoJuegoKBM::finalPartida                 : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        }
    }


}






