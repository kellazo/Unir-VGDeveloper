// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoKBM.cpp
// versión:  1.1  (9-Ene-2023)


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
                            //  sin elegidos, sin atacante, sin equipo actuante
            //
            assert (ModoJuegoBase::cuentaPersonajesIgual ());
            LadoTablero lado_inicial = ModoJuegoBase::eligeEquipoIniciativa ();
            ModoJuegoBase::asignaEquipoInicial (lado_inicial);
            ModoJuegoBase::estableceFactoresEquipos ();
            ModoJuegoBase::indexaFactorEquipos (-1);
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


    void ModoJuegoKBM::entraInicioJugada () {
        try {
            validaEstado ({ 
                    EstadoJuegoKBM::inicioRonda,
                    // sin elegidos, sin atacante 
                    EstadoJuegoKBM::inicioTurno    });
                    // sin elegidos, sin atacante 
            //
            ModoJuegoBase::atenuaMusica ();
           //INICIO GUILLEM //
             ModoJuegoBase::atenuaMusicaLoop ();
           // FIN GUILLEM //
            bool encontrada;
            buscaJugada (encontrada);
            assert (encontrada);
            ActorPersonaje * persj = factoresEquipos ().at (indiceFactorEquipos ());
            ModoJuegoBase::establecePersonajeElegido (persj);
            ModoJuegoBase::estableceAtacante (persj->ladoTablero ());
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
            bool inicio_turno ;
            bool inicio_ronda ;
            bool final_partida;
            asume (inicio_jugada, inicio_turno, inicio_ronda, final_partida);
            //
            if (inicio_jugada) {
                estado ().transita (EstadoJuegoComun::inicioJugada);
            } else if (inicio_turno) {
                estado ().transita (EstadoJuegoKBM::inicioTurno);
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
            bool inicio_turno ;
            bool inicio_ronda ;
            bool final_partida;
            asume (inicio_jugada, inicio_turno, inicio_ronda, final_partida);
            //
            if (inicio_jugada) {
                estado ().transita (EstadoJuegoComun::inicioJugada);
            } else if (inicio_turno) {
                estado ().transita (EstadoJuegoKBM::inicioTurno);
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


    void ModoJuegoKBM::asume (
            bool & inicio_jugada, 
            bool & inicio_turno, 
            bool & inicio_ronda, 
            bool & final_partida) {
        inicio_turno  = false;
        inicio_ronda  = false;
        final_partida = false;

        comprobarFinalPartida(final_partida);

        if(final_partida){
            inicio_jugada = false;
            ModoJuegoBase::suprimeAtacante ();
            ModoJuegoBase::anulaEleccionPersonajes ();
            ModoJuegoBase::asignaEquipoInicial (LadoTablero::nulo);
        }else{
            buscaJugada (inicio_jugada);

            if (inicio_jugada){
                ActorPersonaje * persj = factoresEquipos ().at (indiceFactorEquipos ());
                if (persj->puntosAccion () == 20) {
                    ModoJuegoBase::establecePersonajeElegido (persj);
                    ModoJuegoBase::estableceAtacante (persj->ladoTablero ());
                    inicio_turno = true;
                    ModoJuegoBase::avanzaTurno ();
    
                }else{
                    ModoJuegoBase::avanzaJugada ();
                    ModoJuegoBase::reiniciaAtacante ();
                }
            } else {
                ModoJuegoBase::avanzaRonda ();
                ModoJuegoBase::indexaFactorEquipos (-1);
                inicio_ronda = true;
            }
        }
    }


    void ModoJuegoKBM::comprobarFinalPartida (bool & final_partida) {
        if(ModoJuegoBase::oponente()){
            ActorPersonaje * persj = ModoJuegoBase::oponente();
            string nombre(persj->nombre().begin(), persj->nombre().end());

            if(persj->vitalidad () == 0){
                //CASO 1: Muere un personaje clave
                if (nombre == "Dana" || nombre == "Jason" || nombre == "Sophie" || nombre == "Pete"){
                    final_partida = true;
                    return;
                }

                //CASO 2: Mueren Espectro y Esqueleto (PROTOTIPO)
                ActorPersonaje * otroMonstruo = factoresEquipos ().at ((nombre == "Espectro") ? 1 : 0);
                if(nombre == "Espectro" && otroMonstruo->vitalidad () == 0){
                    final_partida = true;
                    return;
                }
            }
        }
        return;
    }


    void ModoJuegoKBM::buscaJugada (bool & encontrada) {
        if (indiceFactorEquipos () == -1) {
            indexaFactorEquipos (0);
        }
        while (true) {
            ActorPersonaje * persj = factoresEquipos ().at (indiceFactorEquipos ());

            if (persj->vitalidad () > 0 && persj->puntosAccion () > 0) {
                encontrada = true;
                return;
            }else{
                if(ModoJuegoBase::atacante()){
                    ModoJuegoBase::suprimeAtacante ();
                    ModoJuegoBase::anulaEleccionPersonajes ();
                }  
                indexaFactorEquipos (indiceFactorEquipos () + 1);
                if (indiceFactorEquipos () >= factoresEquipos ().size ()) {
                    encontrada = false;
                    return;
                }
            }
        }
    }


    void ModoJuegoKBM::escribeEstado () {
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
        case EstadoJuegoKBM::inicioTurno:
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


    const string ModoJuegoKBM::nombreModulo () {
        return "ModoJuegoKBM";
    }


    void ModoJuegoKBM::validaAtributos () {
        switch (estado ()) {
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        //                         | estado                      |        | equipo   | equipo   | elegidos | atacante | vivo   | agotado | modo      | etapas | habilidad | tipo     | personaje | área     |
        //                         |                             |        | inicial  | actual   |          |          |        |         | acción    | camino |           | accion   |           | celdas   |
        //                         +-----------------------------+        +----------+----------+----------+----------+--------+---------+-----------+--------+-----------+----------+-----------+----------+
        case EstadoJuegoKBM    ::inicial                      : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::terminal                     : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::inicioRonda                  : valida ( ASIGNADO , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::inicioTurno                  : valida ( ASIGNADO , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        //                                                                                                                                                                                                              
        //                                                                                                                                                                                                               
        case EstadoJuegoKBM    ::inicioJugada                 : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , NULO      , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::preparacionDesplazamiento    : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , DESPLAZAM , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::marcacionCaminoFicha         : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , DESPLAZAM , VARIOS , NULO      , ignora   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::habilidadSimpleInvalida      : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::habilidadSimpleConfirmacion  : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::habilidadSimpleResultado     : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , SIMPLE   , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::preparacionHabilidadOponente : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::oponenteHabilidadInvalido    : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoKBM    ::oponenteHabilidadConfirmacion: valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoKBM    ::oponenteHabilidadCalculando  : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoKBM    ::oponenteHabilidadResultado   : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , OPONENTE , ASIGNADO  , VACIO    ); break;
        case EstadoJuegoKBM    ::preparacionHabilidadArea     : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , VACIO    ); break;
        case EstadoJuegoKBM    ::areaHabilidadInvalida        : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoKBM    ::areaHabilidadConfirmacion    : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoKBM    ::areaHabilidadCalculando      : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , SI     , NO      , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        case EstadoJuegoKBM    ::areaHabilidadResultado       : valida ( ASIGNADO , NULO     , UNO      , ASIGNADO , ignora , ignora  , HABILIDAD , CERO   , ASIGNADO  , AREA     , NULO      , NO_VACIO ); break;
        //                                                                                                                                                                                                                 
        //                                                                                                                                                                                                                  
        case EstadoJuegoKBM    ::mostrandoAyuda               : valida ( ignora   , ignora   , ignora   , ignora   , ignora , ignora  , ignora    , ignora , ignora    , ignora   , ignora    , ignora   ); break;
        case EstadoJuegoKBM    ::finalPartida                 : valida ( NULO     , NULO     , NINGUNO  , NULO     , ignora , ignora  , ignora    , CERO   , NULO      , ignora   , NULO      , VACIO    ); break;
        }
    }


}