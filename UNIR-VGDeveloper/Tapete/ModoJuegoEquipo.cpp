// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoEquipo.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    ModoJuegoEquipo::ModoJuegoEquipo (JuegoMesaBase * juego) : 
        estado_ {EstadoJuegoPares::inicial}, 
        estado_previo_ {EstadoJuegoPares::inicial}, 
        ModoJuegoComun {juego, estado_, estado_previo_} { 
    }


    EstadoJuegoEquipo & ModoJuegoEquipo::estado () {
        return estado_;
    }


    void ModoJuegoEquipo::entraPartida () {
        try {
            validaEstado ({ EstadoJuegoEquipo::inicial }); 
                            //  sin elegidos, sin atacante, sin equipo actuante
            //
            assert (ModoJuegoBase::cuentaPersonajesIgual ());
            LadoTablero lado_inicial = ModoJuegoBase::eligeEquipoIniciativa ();
            ModoJuegoBase::asignaEquipoInicial (lado_inicial);
            ModoJuegoBase::estableceFactoresEquipos ();
            ModoJuegoBase::indexaFactorEquipos (-1);
            ModoJuegoBase::iniciaRondas ();
            //
            estado ().transita (EstadoJuegoEquipo::inicioRonda);
            validaAtributos ();
            informaProceso ("entraPartida");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraPartida", excepcion);
        }
    }


    void ModoJuegoEquipo::entraInicioJugada () {
        try {
            validaEstado ({ 
                    EstadoJuegoEquipo::inicioRonda,
                    // sin elegidos, sin atacante 
                    EstadoJuegoEquipo::inicioTurno    });
                    // sin elegidos, sin atacante 
            //
            ModoJuegoBase::atenuaMusica ();
            bool encontrada;
            buscaJugada (encontrada);
            assert (encontrada);
            ActorPersonaje * persj = factoresEquipos ().at (indiceFactorEquipos ());
            ModoJuegoBase::establecePersonajeElegido (persj);
            ModoJuegoBase::estableceAtacante (persj->ladoTablero ());
            //
            estado ().transita (EstadoJuegoEquipo::inicioJugada);
            validaAtributos ();
            informaProceso ("entraInicioJugada");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraInicioJugada", excepcion);
        }
    }


    void ModoJuegoEquipo::mueveFicha () {
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
            bool inicio_turno ;
            bool inicio_ronda ;
            bool final_partida;
            asume (inicio_jugada, inicio_turno, inicio_ronda, final_partida);
            //
            if (inicio_jugada) {
                estado ().transita (EstadoJuegoComun::inicioJugada);
            } else if (inicio_turno) {
                estado ().transita (EstadoJuegoEquipo::inicioTurno);
            } else if (inicio_ronda) {
                estado ().transita (EstadoJuegoEquipo::inicioRonda);
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


    void ModoJuegoEquipo::asumeHabilidad () {
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
            bool inicio_turno ;
            bool inicio_ronda ;
            bool final_partida;
            asume (inicio_jugada, inicio_turno, inicio_ronda, final_partida);
            //
            if (inicio_jugada) {
                estado ().transita (EstadoJuegoComun::inicioJugada);
            } else if (inicio_turno) {
                estado ().transita (EstadoJuegoEquipo::inicioTurno);
            } else if (inicio_ronda) {
                estado ().transita (EstadoJuegoEquipo::inicioRonda);
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


    void ModoJuegoEquipo::asume (
            bool & inicio_jugada, 
            bool & inicio_turno, 
            bool & inicio_ronda, 
            bool & final_partida) {
        inicio_turno  = false;
        inicio_ronda  = false;
        final_partida = false;
        ModoJuegoBase::suprimeAtacante ();
        ModoJuegoBase::anulaEleccionPersonajes ();
        buscaJugada (inicio_jugada);
        if (inicio_jugada) {
            ActorPersonaje * persj = factoresEquipos ().at (indiceFactorEquipos ());
            ModoJuegoBase::establecePersonajeElegido (persj);
            ModoJuegoBase::estableceAtacante (persj->ladoTablero ());
        } else {
            if (ModoJuegoBase::turnosDisponiblesAmbos ()) {
                ModoJuegoBase::avanzaTurno ();
                ModoJuegoBase::indexaFactorEquipos (-1);
                inicio_turno = true;
            } else {
                if (ModoJuegoBase::rondasDisponibles ()) {
                    ModoJuegoBase::avanzaRonda ();
                    ModoJuegoBase::indexaFactorEquipos (-1);
                    inicio_ronda = true;
                } else {
                    ModoJuegoBase::asignaEquipoInicial (LadoTablero::nulo);
                    final_partida = true;
                }
            }
        }
    }


    void ModoJuegoEquipo::buscaJugada (bool & encontrada) {
        while (true) {
            if (indiceFactorEquipos () == -1) {
                indexaFactorEquipos (0);
            } else {
                indexaFactorEquipos (indiceFactorEquipos () + 1);
                if (indiceFactorEquipos () >= factoresEquipos ().size ()) {
                    encontrada = false;
                    return;
                }
                ModoJuegoBase::avanzaJugada ();
            }
            ActorPersonaje * persj = factoresEquipos ().at (indiceFactorEquipos ());
            if (persj->vitalidad () > 0 && persj->puntosAccion () > 0) {
                encontrada = true;
                return;
            }
        }
    }


    void ModoJuegoEquipo::escribeEstado () {
        switch (estado ()) {
        case EstadoJuegoEquipo::inicioRonda:
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
        case EstadoJuegoEquipo::inicioTurno:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Nueva turno de juego.",
                      L"Pulsa 'espacio'."                       },
                    {}                                            );
            break;
        default:
            ModoJuegoComun::escribeEstado ();
            break;
        } 
    }


    const string ModoJuegoEquipo::nombreModulo () {
        return "ModoJuegoEquipo";
    }


    void ModoJuegoEquipo::validaAtributos () {
        switch (estado ()) {
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        //                         | estado                      |        | equipo   | equipo   | elegidos | atacante | vivo   | agotado | modo      | etapas | habilidad | tipo     | personaje | área     |
        //                         |                             |        | inicial  | actual   |          |          |        |         | acción    | camino |           | accion   |           | celdas   |
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        case EstadoJuegoEquipo    ::inicial                      : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::terminal                     : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::inicioRonda                  : valida ( ASIGNADO , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::inicioTurno                  : valida ( ASIGNADO , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        //                                                                                                                                                                                                              
        //                                                                                                                                                                                                               
        case EstadoJuegoEquipo    ::inicioJugada                 : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::preparacionDesplazamiento    : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , DESPLAZAM , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::marcacionCaminoFicha         : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , DESPLAZAM , VARIOS , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::habilidadSimpleInvalida      : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::habilidadSimpleConfirmacion  : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::habilidadSimpleResultado     : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::preparacionHabilidadOponente : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::oponenteHabilidadInvalido    : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoEquipo    ::oponenteHabilidadConfirmacion: valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoEquipo    ::oponenteHabilidadCalculando  : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoEquipo    ::oponenteHabilidadResultado   : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoEquipo    ::preparacionHabilidadArea     : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , VACIO    ); break;
        case EstadoJuegoEquipo    ::areaHabilidadInvalida        : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoEquipo    ::areaHabilidadConfirmacion    : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoEquipo    ::areaHabilidadCalculando      : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoEquipo    ::areaHabilidadResultado       : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        //                                                                                                                                                                                                                 
        //                                                                                                                                                                                                                  
        case EstadoJuegoEquipo    ::mostrandoAyuda               : valida ( ignora   , ignora   , ignora   , ignora   , ignora , ignora  , ignora    , ignora , ignora    , ignora   , ignora    , ignora   ); break;
        case EstadoJuegoEquipo    ::finalPartida                 : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        }
    }


}






