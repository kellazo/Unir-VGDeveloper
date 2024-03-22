// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoComun.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    ModoJuegoComun::ModoJuegoComun (JuegoMesaBase * juego, EstadoJuegoComun & estado, EstadoJuegoComun & estado_previo) :
        estado_ {estado}, 
        estado_previo_ {estado_previo},
        ModoJuegoBase {juego} {
    }


    ModoJuegoComun::~ModoJuegoComun () {
        validaEstado ({ EstadoJuegoComun::terminal });
        //
    }


    EstadoJuegoComun & ModoJuegoComun::estado () {
        return estado_;
    }


    EstadoJuegoComun & ModoJuegoComun::estadoPrevio () {
        return estado_previo_;
    }


    void ModoJuegoComun::saltaFinalJuego () {
        try {
            validaEstado (false, {
                    EstadoJuegoComun::inicial,
                    EstadoJuegoComun::terminal });
            //
            ModoJuegoBase::anulaTotalmente ();
            //
            estado ().transita (EstadoJuegoComun::terminal);
            validaAtributos ();
            informaProceso ("saltaFinalJuego");
        } catch (const std::exception & excepcion) {
            excepciona ("saltaFinalJuego", excepcion);
        }
    }


    void ModoJuegoComun::anunciaActuante (LadoTablero lado) {
        try {
            validaEstado (false, {
                    EstadoJuegoComun::inicial,
                    EstadoJuegoComun::terminal });
            //
            ModoJuegoBase::muestraIndicaActuante (lado);
        } catch (const std::exception & excepcion) {
            excepciona ("anunciaActuante", excepcion);
        }
    }


    void ModoJuegoComun::desanunciaActuante (LadoTablero lado) {
        try {
            validaEstado (false, {
                    EstadoJuegoComun::inicial,
                    EstadoJuegoComun::terminal });
            //
            ModoJuegoBase::ocultaIndicaciones ();
        } catch (const std::exception & excepcion) {
            excepciona ("desanunciaActuante", excepcion);
        }
    }


    void ModoJuegoComun::anunciaHabilidad (LadoTablero lado, int indice) {
        try {
            validaEstado (false, {
                    EstadoJuegoComun::inicial,
                    EstadoJuegoComun::terminal });
            //
            ModoJuegoBase::muestraIndicaHabilidad (lado, indice);
        } catch (const std::exception & excepcion) {
            excepciona ("anunciaHabilidad", excepcion);
        }
    }


    void ModoJuegoComun::desanunciaHabilidad (LadoTablero lado, int indice) {
        try {
            validaEstado (false, {
                    EstadoJuegoComun::inicial,
                    EstadoJuegoComun::terminal });
            //
            ModoJuegoBase::ocultaIndicaciones ();
        } catch (const std::exception & excepcion) {
            excepciona ("desanunciaHabilidad", excepcion);
        }
    }


    void ModoJuegoComun::anunciaFicha (ActorPersonaje * personaje) {
        try {
            validaEstado (false, {
                    EstadoJuegoComun::inicial,
                    EstadoJuegoComun::terminal });
            //
            ModoJuegoBase::muestraIndicaFicha (personaje);
        } catch (const std::exception & excepcion) {
            excepciona ("anunciaFicha", excepcion);
        }
    }


    void ModoJuegoComun::desanunciaFicha (ActorPersonaje * personaje) {
        try {
            validaEstado (false, {
                    EstadoJuegoComun::inicial,
                    EstadoJuegoComun::terminal });
            //
            ModoJuegoBase::ocultaIndicaciones ();
        } catch (const std::exception & excepcion) {
            excepciona ("desanunciaFicha", excepcion);
        }
    }


    void ModoJuegoComun::entraAccionDesplazam () {
        try {
            validaEstado ({ 
                    EstadoJuegoComun::inicioJugada,
                    // con atacante (no agotado), modo acción nulo  
                    // sin etapas camino, sin habilidad, sin oponente, sin celda área
                    EstadoJuegoComun::preparacionHabilidadOponente,
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad oponente, sin oponente, sin celda área
                    EstadoJuegoComun::preparacionHabilidadArea });
                    // con atacante (no agotado), modo acción habilidad  
                    // sin etapas camino, con habilidad área, sin oponente, sin celda área
            //            
            ModoJuegoBase::estableceModoAccionDesplazam ();
            //
            estado ().transita (EstadoJuegoComun::preparacionDesplazamiento);
            validaAtributos ();
            informaProceso ("entraAccionDesplazam");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraAccionDesplazam", excepcion);
        }
    }


    void ModoJuegoComun::entraMarcacionCamino () {
        try {
            validaEstado ({ EstadoJuegoComun::preparacionDesplazamiento });
                            //  con atacante (no agotado), modo acción desplaza 
                            //  sin etapas camino, sin habilidad, sin oponente, sin celda área 
            //
            // cuando se inicia un camino con 'marcaFichaCamino' y se cancela inmediatamente, puede
            // quedar la ficha del personaje desmarcada y con el ratón situado encima de ella; 
            // para que no aparezca un error, se marca la ficha antes de iniciar el camino
            ModoJuegoBase::marcaCeldaInicio ();
            ModoJuegoBase::iniciaCamino ();
            //
            estado ().transita (EstadoJuegoComun::marcacionCaminoFicha);
            validaAtributos ();
            informaProceso ("entraMarcacionCamino");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraMarcacionCamino", excepcion);
        }
    }


    void ModoJuegoComun::marcaFichaCamino (ActorPersonaje * personaje) {
        try {
            validaEstado ({ EstadoJuegoComun::preparacionDesplazamiento });  
                            //  con atacante (no agotado), modo acción desplaza  
                            //  sin etapas camino, sin habilidad, sin oponente, sin celda área 
            //
            if (atacante () != personaje) {
                return;
            }
            ModoJuegoBase::marcaCeldaInicio ();
            //
            estado ().transita (EstadoJuegoComun::preparacionDesplazamiento);
            validaAtributos ();
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("marcaFichaCamino", excepcion);
        }
    }


    void ModoJuegoComun::desmarcaFichaCamino (ActorPersonaje * personaje) {
        try {
            validaEstado ({ EstadoJuegoComun::preparacionDesplazamiento });  
                            //  con atacante (no agotado), modo acción desplaza  
                            //  sin etapas camino, sin habilidad, sin oponente, sin celda área 
            //
            if (atacante () != personaje) {
                return;
            }
            ModoJuegoBase::desmarcaCeldaInicio ();
            //
            estado ().transita (EstadoJuegoComun::preparacionDesplazamiento);
            validaAtributos ();
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("desmarcaFichaCamino", excepcion);
        }
    }


    void ModoJuegoComun::marcaCeldaCamino (Coord celda) {
        try {
            validaEstado ({ EstadoJuegoComun::marcacionCaminoFicha });  
                            //  con atacante (no agotado), modo acción desplaza  
                            //  una o más etapas camino, sin habilidad, sin oponente, sin celda área 
            //
            bool valida;
            int puntos;
            ModoJuegoBase::validaEtapaCamino (celda, valida, puntos);
            ModoJuegoBase::marcaCeldaCamino (celda, valida);
            //
            // este transito no aporta nada y confunde mucho 
            //estado ().transita (EstadoJuegoComun::marcacionCaminoFicha);
            validaAtributos ();
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("marcaCeldaCamino", excepcion);
        }
    }


    void ModoJuegoComun::desmarcaCeldaCamino (Coord celda) {
        try {
            validaEstado ({ EstadoJuegoComun::marcacionCaminoFicha });  
                            //  con atacante (no agotado), modo acción desplaza  
                            //  una o más etapas camino, sin habilidad, sin oponente, sin celda área 
            //
            ModoJuegoBase::desmarcaCeldaCamino (celda);
            //
            // este transito no aporta nada y confunde mucho 
            //estado ().transita (EstadoJuegoComun::marcacionCaminoFicha);
            validaAtributos ();
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("desmarcaCeldaCamino", excepcion);
        }
    }


    void ModoJuegoComun::fijaCeldaCamino (Coord celda) {
        try {
            validaEstado ({ EstadoJuegoComun::marcacionCaminoFicha });
                            //  con atacante (no agotado), modo acción desplaza   
                            //  una o más etapas camino, sin habilidad, sin oponente, sin celda área
            //
            bool valida;
            int  puntos;
            ModoJuegoBase::validaEtapaCamino (celda, valida, puntos);
            if (valida) {
                ModoJuegoBase::agregaEtapaCamino (celda, puntos);
            }
            //
            estado ().transita (EstadoJuegoComun::marcacionCaminoFicha);
            validaAtributos ();
            informaProceso ("fijaCeldaCamino");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("fijaCeldaCamino", excepcion);
        }
    }


    void ModoJuegoComun::revierteAccionDesplazam () {
        try {
            validaEstado ({ EstadoJuegoComun::marcacionCaminoFicha });
                            //  con atacante (no agotado), modo acción desplaza   
                            //  una o más etapas camino, sin habilidad, sin oponente, sin celda área
            //
            ModoJuegoBase::anulaCamino ();
            //
            estado ().transita (EstadoJuegoComun::preparacionDesplazamiento);
            validaAtributos ();
            informaProceso ("revierteAccionDesplazam");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("revierteAccionDesplazam", excepcion);
        }
    }


    void ModoJuegoComun::entraAccionHabilidad (int indice_habilidad) {
        try {
            validaEstado ({ 
                    EstadoJuegoComun::inicioJugada,
                    // con atacante (no agotado), modo acción nulo  
                    // sin etapas camino, sin habilidad, sin oponente, sin celda área
                    EstadoJuegoComun::preparacionDesplazamiento,
                    // con atacante (no agotado), modo acción desplaza 
                    // sin etapas camino, sin habilidad, sin oponente, sin celda área 
                    EstadoJuegoComun::preparacionHabilidadOponente,
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad oponente, sin oponente, sin celda área
                    EstadoJuegoComun::preparacionHabilidadArea        });
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad área, sin oponente, sin celda área
            //
            if (atacante ()->habilidades () [indice_habilidad] == habilidadAccion ()) {
                return;
            }
            ModoJuegoBase::estableceModoAccionHabilidad (indice_habilidad);
            bool valido = true;
            int puntos  = 0;
            if (habilidadAccion ()->tipoEnfoque () == EnfoqueHabilidad::si_mismo) {
                ModoJuegoBase::validaHabilidadSimple  (valido, puntos);
                ModoJuegoBase::muestraHabilidadSimple (valido, puntos);
            }
            //
            switch (habilidadAccion ()->tipoEnfoque ()) {
            case EnfoqueHabilidad::si_mismo:
                if (! valido) {
                    estado ().transita (EstadoJuegoComun::habilidadSimpleInvalida);
                } else {
                    estado ().transita (EstadoJuegoComun::habilidadSimpleConfirmacion);
                }
                break;
            case EnfoqueHabilidad::personaje:
                estado ().transita (EstadoJuegoComun::preparacionHabilidadOponente);
                break;
            case EnfoqueHabilidad::area:
                estado ().transita (EstadoJuegoComun::preparacionHabilidadArea);
                break;
            }
            validaAtributos ();
            informaProceso ("entraAccionHabilidad");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("entraAccionHabilidad", excepcion);
        }
    }


    void ModoJuegoComun::evaluaHabilidadSimple (int indice_habilidad) {
        try {
            validaEstado ({ EstadoJuegoComun::habilidadSimpleInvalida });
                            //  con atacante (no agotado), modo acción habilidad   
                            //  sin etapas camino, con habilidad simple, sin oponente, sin celda área
            //
            if (atacante ()->habilidades () [indice_habilidad] == habilidadAccion ()) {
                return;
            }
            ModoJuegoBase::estableceModoAccionHabilidad (indice_habilidad);
            bool valido;
            int puntos;
            ModoJuegoBase::validaHabilidadSimple    (valido, puntos);
            ModoJuegoBase::muestraHabilidadSimple (valido, puntos);
            //
            if (! valido) {
                estado ().transita (EstadoJuegoComun::habilidadSimpleInvalida);
            } else {
                estado ().transita (EstadoJuegoComun::habilidadSimpleConfirmacion);
            }
            validaAtributos ();
            informaProceso ("evaluaHabilidadSimple");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("evaluaHabilidadSimple", excepcion);
        }
    }


    void ModoJuegoComun::efectuaHabilidadSimple () {
        try {
            validaEstado ({ EstadoJuegoComun::habilidadSimpleConfirmacion });
                            //  elegidos ambos, con atacante (no agotado), modo acción habilidad   
                            //  sin etapas camino, con habilidad simple, sin oponente, sin celda área
            //
            ModoJuegoBase::aplicaHabilidadSimple ();
            //
            estado ().transita (EstadoJuegoComun::habilidadSimpleResultado);
            validaAtributos ();
            informaProceso ("efectuaHabilidadSimple");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("efectuaHabilidadSimple", excepcion);
        }
    }

    
    void ModoJuegoComun::revierteHabilidadSimple () {
        try {
            validaEstado ({ 
                    EstadoJuegoComun::habilidadSimpleInvalida,
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad simple, sin oponente, sin celda área
                    EstadoJuegoComun::habilidadSimpleConfirmacion });
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad simple, sin oponente, sin celda área
            //
            ModoJuegoBase::ocultaHabilidadSimple (); 
            ModoJuegoBase::anulaModoAccion ();
            //
            estado ().transita (EstadoJuegoComun::inicioJugada);
            validaAtributos ();
            informaProceso ("revierteHabilidadSimple");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("revierteHabilidadSimple", excepcion);
        }
    }


    void ModoJuegoComun::evaluaHabilidadOponente (int indice_habilidad) {
        try {
            validaEstado ({ EstadoJuegoComun::oponenteHabilidadInvalido });
                            //  con atacante (no agotado), modo acción habilidad   
                            //  sin etapas camino, con habilidad oponente, con oponente, sin celda área
            //
            if (atacante ()->habilidades () [indice_habilidad] == habilidadAccion ()) {
                return;
            }
            ModoJuegoBase::ocultaAtaqueOponente ();
            ModoJuegoBase::estableceModoAccionHabilidad (indice_habilidad);
            bool valido;
            int puntos;
            ModoJuegoBase::validaAtaqueOponente  (valido, puntos);
            ModoJuegoBase::muestraAtaqueOponente (valido, puntos);
            //
            if (! valido) {  // la habilidad no se puede usar con el oponente
                estado ().transita (EstadoJuegoComun::oponenteHabilidadInvalido);
            } else {
                estado ().transita (EstadoJuegoComun::oponenteHabilidadConfirmacion);
            }
            validaAtributos ();
            informaProceso ("evaluaHabilidadOponente(habilidad)");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("evaluaHabilidadOponente(habilidad)", excepcion);
        }
    }


    void ModoJuegoComun::evaluaHabilidadOponente (ActorPersonaje * personaje) {    
        try {
            validaEstado ({ 
                    EstadoJuegoComun::preparacionHabilidadOponente,
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad oponente, sin oponente, sin celda área
                    EstadoJuegoComun::oponenteHabilidadInvalido       });
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad oponente, con oponente, sin celda área
            //
            if (atacante () == personaje) {
                return;
            }
            if (oponente () == personaje) {
                return;
            }
            if (habilidadAccion ()->antagonista () == Antagonista::aliado) {
                if (atacante ()->ladoTablero () != personaje->ladoTablero ()) {
                    return;
                }
            } else {
                if (atacante ()->ladoTablero () == personaje->ladoTablero ()) {
                    return;
                }
            }
            if (oponente () != nullptr) {
                ModoJuegoBase::ocultaAtaqueOponente ();
                ModoJuegoBase::suprimeOponente ();
            }
            ModoJuegoBase::estableceOponente (personaje);
            bool valido;
            int puntos;
            ModoJuegoBase::validaAtaqueOponente  (valido, puntos);
            ModoJuegoBase::muestraAtaqueOponente (valido, puntos);
            //
            if (! valido) {  // la habilidad no se puede usar con el oponente
                estado ().transita (EstadoJuegoComun::oponenteHabilidadInvalido);
            } else {
                estado ().transita (EstadoJuegoComun::oponenteHabilidadConfirmacion);
            }
            validaAtributos ();
            informaProceso ("evaluaHabilidadOponente(personaje)");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("evaluaHabilidadOponente(personaje)", excepcion);
        }
    }


    void ModoJuegoComun::efectuaHabilidadOponente () {
        try {
            validaEstado ({ EstadoJuegoComun::oponenteHabilidadConfirmacion });
                            //  elegidos ambos, con atacante (no agotado), modo acción habilidad   
                            //  sin etapas camino, con habilidad oponente, con oponente, sin celda área
            //
            if (habilidadAccion ()->antagonista () == Antagonista::aliado) {
                ModoJuegoBase::atacaOponente ();
            } else {
                ModoJuegoBase::iniciaTiempoCalculo ();
            }
            //
            if (habilidadAccion ()->antagonista () == Antagonista::aliado) {
                estado ().transita (EstadoJuegoComun::oponenteHabilidadResultado);
            } else {
                estado ().transita (EstadoJuegoComun::oponenteHabilidadCalculando);
            }
            validaAtributos ();
            informaProceso ("efectuaHabilidadOponente");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("efectuaHabilidadOponente", excepcion);
        }
    }


    void ModoJuegoComun::calculaHabilidadOponente (unir2d::Tiempo & tiempo) {
        try {
            validaEstado ({ EstadoJuegoComun::oponenteHabilidadCalculando });
                            //  elegidos ambos, con atacante (no agotado), modo acción habilidad   
                            //  sin etapas camino, con habilidad oponente, con oponente, sin celda área
            //
            double segundos = tiempo.segundos ();
            if (segundos < segundos_calculo) {
                ModoJuegoBase::alea100 ();
                ModoJuegoBase::muestraAleatorio100 ();
            } else {                
                ModoJuegoBase::terminaTiempoCalculo ();
                ModoJuegoBase::atacaOponente ();
            }
            //
            if (segundos < segundos_calculo) {
                // este transito no aporta nada y confunde mucho 
                //estado ().transita (EstadoJuegoComun::oponenteHabilidadCalculando);
            } else {
                estado ().transita (EstadoJuegoComun::oponenteHabilidadResultado);
            }
            validaAtributos ();
            if (segundos >= segundos_calculo) {
                informaProceso ("calculaHabilidadOponente");
            }
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("calculaHabilidadOponente", excepcion);
        }
    }


    void ModoJuegoComun::revierteHabilidadOponente () {
        try {
            validaEstado ({ 
                    EstadoJuegoComun::oponenteHabilidadInvalido,
                    // con atacante (no agotado), modo acción habilidad  
                    // sin etapas camino, con habilidad oponente, con oponente, sin celda área
                    EstadoJuegoComun::oponenteHabilidadConfirmacion });
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad oponente, con oponente, sin celda área
            //
            ModoJuegoBase::ocultaAtaqueOponente ();
            ModoJuegoBase::suprimeOponente ();
            //
            estado ().transita (EstadoJuegoComun::preparacionHabilidadOponente);
            validaAtributos ();
            informaProceso ("revierteHabilidadOponente");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("revierteHabilidadOponente", excepcion);
        }
    }


    void ModoJuegoComun::evaluaHabilidadArea (int indice_habilidad) {
        try {
            validaEstado ({ EstadoJuegoComun::areaHabilidadInvalida });
                            //  con atacante (no agotado), modo acción habilidad   
                            //  sin etapas camino, con habilidad área, sin oponente, con celda área
            //
            if (atacante ()->habilidades () [indice_habilidad] == habilidadAccion ()) {
                return;
            }
            ModoJuegoBase::ocultaAtaqueArea ();
            ModoJuegoBase::estableceModoAccionHabilidad (indice_habilidad);
            bool valido;
            int puntos;
            ModoJuegoBase::validaAtaqueArea  (valido, puntos);
            ModoJuegoBase::muestraAtaqueArea (valido, puntos);
            //
            if (! valido) {  // la habilidad no se puede usar con el área indicada
                estado ().transita (EstadoJuegoComun::areaHabilidadInvalida);
            } else {
                estado ().transita (EstadoJuegoComun::areaHabilidadConfirmacion);
            }
            validaAtributos ();
            informaProceso ("evaluaHabilidadArea(habilidad)");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("evaluaHabilidadArea(habilidad)", excepcion);
        }
    }


    void ModoJuegoComun::evaluaHabilidadArea (Coord celda) {
        try {
            validaEstado ({ 
                    EstadoJuegoComun::preparacionHabilidadArea,
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad área, sin oponente, sin celda área
                    EstadoJuegoComun::areaHabilidadInvalida       });
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad área, sin oponente, con celda área
            //
            // esto es raro, no creo que suceda:
            if (! CalculoCaminos::celdaEnTablero (celda)) {
                return;
            }
            if (! areaCeldas ().empty ()) {
                Coord celda_area = areaCeldas () [0] [0];
                if (celda_area == celda) {
                    return;
                }
            }
            if (atacante ()->sitioFicha () == celda) {
                return;
            }
            if (! areaCeldas ().empty ()) {
                ModoJuegoBase::ocultaAtaqueArea ();
                ModoJuegoBase::anulaAreaHabilidad ();
            }
            ModoJuegoBase::estableceAreaHabilidad (celda);
            bool valido;
            int puntos;
            ModoJuegoBase::validaAtaqueArea  (valido, puntos);
            ModoJuegoBase::muestraAtaqueArea (valido, puntos);
            //
            if (! valido) {  // la habilidad no se puede usar con el área indicada
                estado ().transita (EstadoJuegoComun::areaHabilidadInvalida);
            } else {
                estado ().transita (EstadoJuegoComun::areaHabilidadConfirmacion);
            }
            validaAtributos ();
            informaProceso ("evaluaHabilidadArea(celda)");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("evaluaHabilidadArea(celda)", excepcion);
        }
    }


    void ModoJuegoComun::efectuaHabilidadArea () {
        try {
            validaEstado ({ EstadoJuegoComun::areaHabilidadConfirmacion });
                            //  elegidos ambos, con atacante (no agotado), modo acción habilidad   
                            //  sin etapas camino, con habilidad área, sin oponente, con celda área
            //
            if (habilidadAccion ()->antagonista () == Antagonista::aliado) {
                ModoJuegoBase::atacaArea ();
            } else {
                ModoJuegoBase::iniciaTiempoCalculo ();
            }
            //
            if (habilidadAccion ()->antagonista () == Antagonista::aliado) {
                estado ().transita (EstadoJuegoComun::areaHabilidadResultado);
            } else {
                estado ().transita (EstadoJuegoComun::areaHabilidadCalculando);
            }
            validaAtributos ();
            informaProceso ("efectuaHabilidadArea");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("efectuaHabilidadArea", excepcion);
        }
    }


    void ModoJuegoComun::calculaHabilidadArea (unir2d::Tiempo & tiempo) {
        try {
            validaEstado ({ EstadoJuegoComun::areaHabilidadCalculando });
                            //  elegidos ambos, con atacante (no agotado), modo acción habilidad   
                            //  sin etapas camino, con habilidad área, sin oponente, con celda área
            //
            double segundos = tiempo.segundos ();
            if (segundos < segundos_calculo) {
                ModoJuegoBase::alea100 ();
                ModoJuegoBase::muestraAleatorio100 ();
            } else {
                ModoJuegoBase::terminaTiempoCalculo ();
                ModoJuegoBase::atacaArea ();
            }
            //
            if (segundos < segundos_calculo) {
                // este transito no aporta nada y confunde mucho 
                //estado ().transita (EstadoJuegoComun::areaHabilidadCalculando);
            } else {
                estado ().transita (EstadoJuegoComun::areaHabilidadResultado);
            }
            validaAtributos ();
            if (segundos >= segundos_calculo) {
                informaProceso ("calculaHabilidadArea");
            }
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("calculaHabilidadArea", excepcion);
        }
    }


    void ModoJuegoComun::revierteHabilidadArea () {
        try {
            validaEstado ({ 
                    EstadoJuegoComun::areaHabilidadInvalida,
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad área, sin oponente, con celda área
                    EstadoJuegoComun::areaHabilidadConfirmacion });
                    // con atacante (no agotado), modo acción habilidad   
                    // sin etapas camino, con habilidad área, sin oponente, con celda área
            //
            ModoJuegoBase::ocultaAtaqueArea ();
            ModoJuegoBase::anulaAreaHabilidad ();
            //
            estado ().transita (EstadoJuegoComun::preparacionHabilidadArea);
            validaAtributos ();
            informaProceso ("revierteHabilidadArea");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("revierteHabilidadArea", excepcion);
        }
    }


    void ModoJuegoComun::muestraAyuda () {
        try {
            validaEstado (false, {
                    EstadoJuegoComun::inicial,
                    // elegidos ambos, con atacante (no agotado), modo acción habilidad  
                    // sin etapas camino, con habilidad simple, sin oponente, sin celda área 
                    EstadoJuegoComun::terminal,
                    // elegidos ambos, con atacante (no agotado), modo acción habilidad  
                    // sin etapas camino, con habilidad oponente, con oponente, sin celda área 
                    EstadoJuegoComun::mostrandoAyuda });
                    // elegidos ambos, con atacante (no agotado), modo acción habilidad  
                    // sin etapas camino, con habilidad área, sin oponente, con celda área    
            //
            if (estado () == EstadoJuegoComun::habilidadSimpleResultado   ||
                estado () == EstadoJuegoComun::oponenteHabilidadResultado ||
                estado () == EstadoJuegoComun::areaHabilidadResultado       ) {
                ModoJuegoBase::muestraAyudaCalculo ();
            } else {
                ModoJuegoBase::muestraAyudaGeneral ();
            }
            //
            estadoPrevio ().conserva (estado ());
            estado ().transita (EstadoJuegoComun::mostrandoAyuda);
            validaAtributos ();
            informaProceso ("muestraAyuda");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("muestraAyuda", excepcion);
        }
    }


    void ModoJuegoComun::muestraAyuda (ActorPersonaje * personaje) {
        try {
            validaEstado ({ EstadoJuegoComun::mostrandoAyuda });
            //
            ModoJuegoBase::muestraAyudaPersonaje (personaje);
            //
            estado ().transita (EstadoJuegoComun::mostrandoAyuda);
            validaAtributos ();
            informaProceso ("muestraAyuda(personaje)");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("muestraAyuda(personaje)", excepcion);
        }
    }
    
        
    void ModoJuegoComun::muestraAyudaActuante () {
        try {
            validaEstado ({ EstadoJuegoComun::mostrandoAyuda });
            //
            if (estadoPrevio () == EstadoJuegoComun::habilidadSimpleResultado   ||
                estadoPrevio () == EstadoJuegoComun::oponenteHabilidadResultado ||
                estadoPrevio () == EstadoJuegoComun::areaHabilidadResultado       ) {
                ModoJuegoBase::muestraAyudaCalculo ();
            } else {
                ModoJuegoBase::muestraAyudaGeneral ();
            }
            //
            estado ().transita (EstadoJuegoComun::mostrandoAyuda);
            validaAtributos ();
            informaProceso ("muestraAyudaActuante");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("muestraAyudaActuante", excepcion);
        }
    }


    void ModoJuegoComun::subeAyuda () {
        try {
            validaEstado ({ EstadoJuegoComun::mostrandoAyuda });
            //
            ModoJuegoBase::sigueAyudaArriba ();
        } catch (const std::exception & excepcion) {
            excepciona ("subeAyuda", excepcion);
        }
    }


    void ModoJuegoComun::bajaAyuda () {
        try {
            validaEstado ({ EstadoJuegoComun::mostrandoAyuda });
            //
            ModoJuegoBase::sigueAyudaAbajo ();
        } catch (const std::exception & excepcion) {
            excepciona ("bajaAyuda", excepcion);
        }
    }


    void ModoJuegoComun::ocultaAyuda () {
        try {
            validaEstado ({ EstadoJuegoComun::mostrandoAyuda });
            //
            ModoJuegoBase::ocultaAyuda ();
            //
            estado ().transita (estadoPrevio ());
            validaAtributos ();
            informaProceso ("ocultaAyuda");
            escribeEstado ();
        } catch (const std::exception & excepcion) {
            excepciona ("ocultaAyuda", excepcion);
        }
    }


    const string ModoJuegoComun::nombreModulo () {
        return "ModoJuegoComun";
    }


    void ModoJuegoComun::validaEstado (const std::initializer_list <int> & estados) {
        validaEstado (true, estados);
    }


    void ModoJuegoComun::validaEstado (bool coincide, const std::initializer_list <int> & estados) {
        if (coincide) {
            for (int prueba : estados) {
                if (estado () == prueba) {
                    return;
                }
            }
            throw ExcepcionEstado (estado ());
        } else {
            for (int prueba : estados) {
                if (estado () == prueba) {
                    throw ExcepcionEstado (estado ());
                }
            }
        }
    }


    void ModoJuegoComun::valida (
            SimboloValida simbolo_equipo_inicial,
            SimboloValida simbolo_equipo_actual,
            SimboloValida simbolo_elegidos, 
            SimboloValida simbolo_atacante_, 
            SimboloValida simbolo_vivo,
            SimboloValida simbolo_agotado, 
            SimboloValida simbolo_modo_accion, 
            SimboloValida simbolo_etapas_camino, 
            SimboloValida simbolo_habilidad, 
            SimboloValida simbolo_tipo_accion, 
            SimboloValida simbolo_oponente_, 
            SimboloValida simbolo_area_celdas) {
        //----------------------------------------------------------------------
        switch (simbolo_equipo_inicial) {
        case ignora:
            break;
        case NULO:
            aserta (ladoEquipoInicial () == LadoTablero::nulo, "ladoEquipoInicial", simbolo_equipo_inicial);
            break;
        case ASIGNADO:
            aserta (ladoEquipoInicial () != LadoTablero::nulo, "ladoEquipoInicial", simbolo_equipo_inicial);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_equipo_actual) {
        case ignora:
            break;
        case NULO:
            aserta (ladoEquipoActual () == LadoTablero::nulo, "ladoEquipoActual", simbolo_equipo_actual);
            break;
        case ASIGNADO:
            aserta (ladoEquipoActual () != LadoTablero::nulo, "ladoEquipoActual", simbolo_equipo_actual);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_elegidos) {
        case ignora:
            break;
        case NINGUNO:
            aserta (personajeElegido (LadoTablero::Izquierda) == nullptr &&
                    personajeElegido (LadoTablero::Derecha  ) == nullptr   , "personajeElegido", simbolo_elegidos);
            break;
        case UNO:
            aserta ((personajeElegido (LadoTablero::Izquierda) != nullptr &&
                     personajeElegido (LadoTablero::Derecha  ) == nullptr   ) ||
                    (personajeElegido (LadoTablero::Izquierda) == nullptr &&
                     personajeElegido (LadoTablero::Derecha  ) != nullptr   )   , "personajeElegido", simbolo_elegidos);
            break;
        case AMBOS:
            aserta (personajeElegido (LadoTablero::Izquierda) != nullptr &&
                    personajeElegido (LadoTablero::Derecha  ) != nullptr   , "personajeElegido", simbolo_elegidos);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_atacante_) {
        case ignora:
            break;
        case NULO:
            aserta (atacante () == nullptr, "atacante", simbolo_atacante_);
            break;
        case ASIGNADO:
            aserta (atacante () != nullptr, "atacante", simbolo_atacante_);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_vivo) {
        case ignora:
            break;
        case NO:
            aserta (atacante ()->vitalidad () == 0, "vitalidad", simbolo_agotado);
            break;
        case SI:
            aserta (atacante ()->vitalidad () > 0, "puntosAccion", simbolo_agotado);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_agotado) {
        case ignora:
            break;
        case NO:
            aserta (atacante ()->puntosAccion () != 0, "puntosAccion", simbolo_agotado);
            break;
        case SI:
            aserta (atacante ()->puntosAccion () == 0, "puntosAccion", simbolo_agotado);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_modo_accion) {
        case ignora:
            break;
        case NULO:
            aserta (modoAccion () == ModoAccionPersonaje::Nulo, "modoAccion", simbolo_modo_accion);
            break;
        case DESPLAZAM:
            aserta (modoAccion () == ModoAccionPersonaje::Desplazamiento, "modoAccion", simbolo_modo_accion);
            break;
        case HABILIDAD:
            aserta (modoAccion () == ModoAccionPersonaje::Habilidad, "modoAccion", simbolo_modo_accion); 
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_etapas_camino) {
        case ignora:
            break;
        case CERO:
            aserta (this->etapasCamino ().size () == 0, "etapasCamino", simbolo_etapas_camino);
            break;
        case VARIOS:
            aserta (this->etapasCamino ().size () > 0, "etapasCamino", simbolo_etapas_camino); 
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_habilidad) {
        case ignora:
            break;
        case NULO:
            aserta (habilidadAccion () == nullptr, "habilidadAccion", simbolo_habilidad);
            break;
        case ASIGNADO:
            aserta (habilidadAccion () != nullptr, "habilidadAccion", simbolo_habilidad);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_tipo_accion) {
        case ignora:
            break;
        case SIMPLE:
            aserta (habilidadAccion ()->tipoEnfoque () == EnfoqueHabilidad::si_mismo, "tipoEnfoque", simbolo_tipo_accion);
            break;
        case OPONENTE:
            aserta (habilidadAccion ()->tipoEnfoque () == EnfoqueHabilidad::personaje, "tipoEnfoque", simbolo_tipo_accion);
            break;
        case AREA:
            aserta (habilidadAccion ()->tipoEnfoque () == EnfoqueHabilidad::area, "tipoEnfoque", simbolo_tipo_accion);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_oponente_) {
        case ignora:
            break;
        case NULO:
            aserta (oponente () == nullptr, "oponente", simbolo_oponente_);
            break;
        case ASIGNADO:
            aserta (oponente () != nullptr, "oponente", simbolo_oponente_);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------
        switch (simbolo_area_celdas) {
        case ignora:
            break;
        case VACIO:
            aserta (areaCeldas ().empty (), "areaCeldas", simbolo_area_celdas);
            break;
        case NO_VACIO:
            aserta (! areaCeldas ().empty (), "areaCeldas", simbolo_area_celdas);
            break;
        default:
            assert (false);
            break;
        }
        //----------------------------------------------------------------------        
    }


    void ModoJuegoComun::informaProceso (const string & metodo) {
        ModoJuegoBase::almacenaInforme (estado_, nombreModulo (), metodo);
    }


    void ModoJuegoComun::aserta (bool expresion, const string & atributo, SimboloValida simbolo) {
        if (expresion) {
            return;
        }
        string condicion {};
        switch (simbolo) {
        case NO:
            condicion = "NO";
            break;
        case SI: 
            condicion = "SI";  
            break;
        case NINGUNO: 
            condicion = "NINGUNO";  
            break;
        case UNO: 
            condicion = "UNO";  
            break;
        case AMBOS: 
            condicion = "AMBOS";  
            break;
        case NULO: 
            condicion = "NULO";  
            break;
        case ASIGNADO: 
            condicion = "ASIGNADO";  
            break;
        case CERO: 
            condicion = "CERO";  
            break;
        case VARIOS: 
            condicion = "VARIOS";  
            break;
        case DESPLAZAM: 
            condicion = "DESPLAZAM";  
            break;
        case HABILIDAD: 
            condicion = "HABILIDAD";  
            break;
        case SIMPLE: 
            condicion = "SIMPLE";  
            break;
        case OPONENTE: 
            condicion = "OPONENTE";  
            break;
        case AREA: 
            condicion = "AREA";  
            break;
        case VACIO: 
            condicion = "VACIO";  
            break;
        case NO_VACIO: 
            condicion = "NO_VACIO";  
            break;
        }
        throw ExcepcionValidacion {atributo, condicion};
    }


    void ModoJuegoComun::excepciona (const string & metodo, const std::exception & excepcion) {
        throw ExcepcionProcesoJuego {nombreModulo (), metodo, excepcion, * this};
    }


    void ModoJuegoComun::escribeEstado () {
         switch (estado ()) {
        case EstadoJuegoComun::inicial:
            break;
        case EstadoJuegoComun::terminal:
            break;
        case EstadoJuegoComun::inicioJugada:
            juego ()->tablero ()->escribeMonitor (std::vector <string>
                    { "Selecciona el retrato para mover la",
                        "ficha o selecciona una habilidad."   },
                    {}                                        );
            break;
        case EstadoJuegoComun::preparacionDesplazamiento:
            juego ()->tablero ()->escribeMonitor (std::vector <string>
                    { "Marca el camino comenzando en la",
                      "ficha del personaje."             },
                    {}                                     );
            break;
        case EstadoJuegoComun::marcacionCaminoFicha:
            juego ()->tablero ()->escribeMonitor (std::vector <string>
                    { "Marca las etapas del camino. Despues",
                      "pulsa 'espacio' para mover la ficha",
                      "o 'Esc' para cancelar."               },
                    {}                                         );
            break;
        case EstadoJuegoComun::habilidadSimpleInvalida:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"La habilidad no se puede usar." },
                    { habilidadAccion ()->nombre ()     });
            break;
        case EstadoJuegoComun::habilidadSimpleConfirmacion:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Pulsa 'espacio' para usar la",
                      L"habilidad, 'Esc' para cancelar."},
                    { habilidadAccion ()->nombre () }     );
            break;
        //case EstadoJuegoComun::habilidadSimpleCalculando:
        //    juego ()->tablero ()->escribeMonitor (std::vector <wstring>
        //            { L"Calculando.",
        //              L"Espera."},
        //            { habilidadAccion ()->nombre () }     );
        //    break;
        case EstadoJuegoComun::habilidadSimpleResultado:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Habilidad usada.",
                      L"Pulsa 'espacio'.",
                      L"O pulsa en 'interrogación'."},
                    { habilidadAccion ()->nombre () }     );
            break;
        case EstadoJuegoComun::preparacionHabilidadOponente:
            if (habilidadAccion ()->antagonista () == Antagonista::aliado) {
                juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                        { L"Selecciona un aliado." },
                        { habilidadAccion ()->nombre () });
            } else {
                juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                        { L"Selecciona un oponente." },
                        { habilidadAccion ()->nombre () });
            }
            break;
        case EstadoJuegoComun::oponenteHabilidadInvalido:
            if (habilidadAccion ()->antagonista () == Antagonista::aliado) {
                juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                        { L"La habilidad no se puede usar con",
                          L"ese aliado."                        },
                        { std::format (L"{} a favor de {}", 
                                    atacante ()->nombre (), 
                                    oponente ()->nombre ()),
                          habilidadAccion ()->nombre ()      });
            } else {
                juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                        { L"La habilidad no se puede usar contra",
                          L"ese oponente."                        },
                        { std::format (L"{} contra {}", 
                                    atacante ()->nombre (), 
                                    oponente ()->nombre ()),
                          habilidadAccion ()->nombre ()      });
            }
            break;
        case EstadoJuegoComun::oponenteHabilidadConfirmacion:
            if (habilidadAccion ()->antagonista () == Antagonista::aliado) {
                juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                        { L"Pulsa 'espacio' para usar la",
                          L"habilidad, 'Esc' para cancelar." },
                        { std::format (L"{} a favor de {}", 
                                    atacante ()->nombre (), 
                                    oponente ()->nombre ()),
                          habilidadAccion ()->nombre ()      });
            } else {
                juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                        { L"Pulsa 'espacio' para usar la",
                          L"habilidad, 'Esc' para cancelar." },
                        { std::format (L"{} contra {}", 
                                    atacante ()->nombre (), 
                                    oponente ()->nombre ()),
                          habilidadAccion ()->nombre ()      });
            }
            break;
        case EstadoJuegoComun::oponenteHabilidadCalculando:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Calculando.",
                      L"Espera."},
                    { habilidadAccion ()->nombre () }     );
            break;
        case EstadoJuegoComun::oponenteHabilidadResultado:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Habilidad usada.",
                      L"Pulsa 'espacio'."},
                    { habilidadAccion ()->nombre () }     );
            break;
        case EstadoJuegoComun::preparacionHabilidadArea:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Selecciona una celda para usar la",
                      L"habilidad sobre un área."          },
                    { habilidadAccion ()->nombre () }        );
            break;
        case EstadoJuegoComun::areaHabilidadInvalida:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"La habilidad no se puede usar sobre",
                      L"esas celdas."                         },
                    { habilidadAccion ()->nombre () }          );
            break;
        case EstadoJuegoComun::areaHabilidadConfirmacion:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Pulsa 'espacio' para usar la",
                      L"habilidad, 'Esc' para cancelar." },
                    { habilidadAccion ()->nombre () });
            break;
        case EstadoJuegoComun::areaHabilidadCalculando:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Calculando.",
                      L"Espera."},
                    { habilidadAccion ()->nombre () }     );
            break;
        case EstadoJuegoComun::areaHabilidadResultado:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Habilidad usada.",
                      L"Pulsa 'espacio'."},
                    { habilidadAccion ()->nombre () }     );
            break;
        case EstadoJuegoComun::mostrandoAyuda:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Pulsa la interrogación para cerrar ",
                      L"la ayuda."},
                    {  }     );
            break;
        case EstadoJuegoComun::finalPartida:
            juego ()->tablero ()->escribeMonitor (std::vector <wstring>
                    { L"Agotados todos los rondas de juego",
                      L"La partida ha terminado."            },
                    {}                                         );
            break;
        default:
            assert (false);
            break;
        } 
    }


}

