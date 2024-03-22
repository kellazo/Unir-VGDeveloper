// proyecto: Grupal/Tapete
// arhivo:   ActorTablero.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {
    

    ActorTablero::ActorTablero (JuegoMesaBase * juego) {
        this->juego = juego;
    }


    ActorTablero::~ActorTablero () {
        juego = nullptr;
    }


    const string & ActorTablero::archivoBaldosas () {
        return archivo_baldosas;
    }
        
        
    void ActorTablero::ponArchivoBaldosas (const string & archivo) {
        archivo_baldosas = archivo;
    }


    const wstring & ActorTablero::nombreEquipo (LadoTablero lado_tablero) {
        if (lado_tablero == LadoTablero::Izquierda) {
            return nombre_equipo_izqrd;
        } else {
            return nombre_equipo_derch;
        }
    }


    const string & ActorTablero::ArchivoEscudo (LadoTablero lado_tablero) {
        if (lado_tablero == LadoTablero::Izquierda) {
            return archivo_escudo_izqrd;
        } else {
            return archivo_escudo_derch;
        }
    }


    void ActorTablero::equipa (LadoTablero lado_tablero, const wstring & nombre_equipo, const string & archivo_escudo) {
        if (lado_tablero == LadoTablero::Izquierda) {
            nombre_equipo_izqrd  = nombre_equipo;
            archivo_escudo_izqrd = archivo_escudo;
        } else {
            nombre_equipo_derch  = nombre_equipo;
            archivo_escudo_derch = archivo_escudo;
        }
    }


    const std::vector <Coord> & ActorTablero::sitiosMuros () const {
        return sitios_muros;
    }


    void ActorTablero::situaMuros (const GraficoMuros & grafico_muros) {
        this->grafico_muros = & grafico_muros;
    }


    void ActorTablero::validaGraficoMuros () {
        if (this->grafico_muros == nullptr) {
            throw std::logic_error ("no establecido");
        }
        for (int fl = 0; fl < RejillaTablero::filas; ++ fl) {            
            if (strlen ((* this->grafico_muros) [fl]) != columnasGraficoMuros) {
                throw std::logic_error (std::format (
                        "longitud inválida en la fila {}", fl));
            }
            for (int cl = 0; cl < columnasGraficoMuros; ++ cl) {
                int fila = fl + 1;
                int coln = 0;
                if (cl % 3 == 0) {
                    coln = (cl / 3) + 1;
                }
                char ch = (* this->grafico_muros) [fl] [cl];
                if (coln == 0) {
                    if (ch != ' ') {
                        throw std::logic_error (std::format (
                                "el carácter en la fila {}, columna {} debe ser un espacio en blanco", fl, cl));
                    }
                } else {
                    if ((fila % 2 == 0) != (coln % 2 == 0)) {
                        if (ch != ' ') {
                            throw std::logic_error (std::format (
                                    "el carácter en la fila {}, columna {} debe ser un espacio en blanco", fl, cl));
                        }
                    } else {
                        if (ch != 'O' && ch != '-') {
                            throw std::logic_error (std::format (
                                    "el carácter en la fila {}, columna {} debe ser: 'O' o '-'", fl, cl));
                        }
                    }
                }
            }
        }
    }


    void ActorTablero::calculaSitiosMuros () {
        for (int fl = 0; fl < RejillaTablero::filas; ++ fl) {            
            for (int cl = 0; cl < columnasGraficoMuros; ++ cl) {
                int fila = fl + 1;
                int coln = 0;
                if (cl % 3 == 0) {
                    coln = (cl / 3) + 1;
                }
                if (coln != 0) {
                    if ((fila % 2 == 0) == (coln % 2 == 0)) {
                        char ch = (* this->grafico_muros) [fl] [cl];
                        if (ch == 'O') {
                            sitios_muros.push_back (Coord {fila, coln});
                        }
                    }
                }
            }
        }
    }


    RejillaTablero & ActorTablero::rejilla () {
        return rejilla_tablero;
    }


    PresenciaActuante & ActorTablero::presencia (LadoTablero lado) {
        aserta (lado != LadoTablero::nulo, "parámatro 'lado_tablero' inválido");
        if (lado == LadoTablero::Izquierda) {
            return presencia_actuante_izqrd;
        } else {
            return presencia_actuante_derch;
        }
    }


    CuadroIndica & ActorTablero::indicador () {
        return cuadro_indica;
    }


    VistaCaminoCeldas & ActorTablero::vistaCamino () {
        return vista_camino_celdas;
    }


    ListadoAyuda & ActorTablero::listadoAyuda () {
        return listado_ayuda;
    }


    void ActorTablero::indicaPersonaje (LadoTablero lado, const wstring & cadena) {
        aserta (lado != LadoTablero::nulo, "parámatro 'lado_tablero' inválido");
        aserta (presencia (lado).visible (), "presencia del actuante no visible");
        //
        Vector poscn = presencia (lado).panel_retrato.posicion (); 
        poscn -= Vector {0, 24};
        //
        cuadro_indica.indica (poscn, cadena);
    }


    void ActorTablero::indicaHabilidad (LadoTablero lado, int indice_habilidad, const wstring & cadena) {
        aserta (lado != LadoTablero::nulo, "parámatro 'lado_tablero' inválido");
        aserta (presencia (lado).visible (), "presencia del actuante no visible");
        aserta (indice_habilidad < presencia (lado).personaje ()->habilidades ().size (), 
                "parámatro 'indice_habilidad' inválido");
        //
        Vector poscn = presencia (lado).paneles_habilidad [indice_habilidad].posicion (); 
        poscn -= Vector {0, 24};
        //
        cuadro_indica.indica (poscn, cadena);
    }


    void ActorTablero::desindica () {
        cuadro_indica.desindica ();
    }


    const string & ActorTablero::archivoSonidoEstablece () {
        return archivo_sonido_establece;
    }


    int ActorTablero::volumenSonidoEstablece () {
        return volumen_sonido_establece;
    }


    void ActorTablero::asignaSonidoEstablece (const string & archivo, int volumen) {
        archivo_sonido_establece = archivo;
        volumen_sonido_establece = volumen;
    }


    const string & ActorTablero::archivoSonidoDesplaza () {
        return archivo_sonido_desplaza;
    }


    int ActorTablero::volumenSonidoDesplaza () {
        return volumen_sonido_desplaza;
    }


    void ActorTablero::asignaSonidoDesplaza (const string & archivo, int volumen) {
        archivo_sonido_desplaza = archivo;
        volumen_sonido_desplaza = volumen;
    }


    void ActorTablero::emiteSonidoEstablece () {
        presencia_tablero.sonido_establece->suena ();
    }


    void ActorTablero::emiteSonidoDesplaza () {
        presencia_tablero.sonido_desplaza->suena ();
    }


    void ActorTablero::emiteSonidoHabilidad (Habilidad * habilidad) {
        presencia_habilidades.sonidos_habilidades [habilidad->indice ()]->suena ();
    }


    void ActorTablero::muestraDisplay (int digito_1, int digito_2) {
        presencia_tablero.imagenes_digitos_display [0]->seleccionaEstampa (1, digito_1 + 1);
        presencia_tablero.imagenes_digitos_display [1]->seleccionaEstampa (1, digito_2 + 1);
    }


    void ActorTablero::borraDisplay () {
        presencia_tablero.imagenes_digitos_display [0]->seleccionaEstampa (1, 11);
        presencia_tablero.imagenes_digitos_display [1]->seleccionaEstampa (1, 11);
    }


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    void ActorTablero::inicia () {
        ponPosicion (Vector {0, 0});
        //
        calculaSitiosMuros ();
        //
        presencia_tablero       .prepara ();
        rejilla_tablero         .prepara ();
        presencia_tablero       .reprepara ();
        presencia_actuante_izqrd.prepara ();
        presencia_actuante_derch.prepara ();
        presencia_habilidades   .prepara ();
        cuadro_indica           .prepara ();
        vista_camino_celdas     .prepara ();
        listado_ayuda           .prepara ();
    }


    void ActorTablero::termina () {
        extraeDibujos ();
        listado_ayuda           .libera ();
        vista_camino_celdas     .libera ();
        cuadro_indica           .libera ();
        presencia_actuante_izqrd.libera ();
        presencia_actuante_derch.libera ();
        presencia_habilidades   .libera ();
        rejilla_tablero         .libera ();
        presencia_tablero       .libera ();
    }


    void ActorTablero::actualiza (double tiempo_seg) {
        controlSobreRetrato ();
        controlSobreHabilidad ();
        controlRetratoPulsacion ();
        controlHabilidadPulsacion ();
        controlSobreCelda ();
        controlCeldaPulsacion ();
        controlAyudaPulsacion ();
        rejilla_tablero.refrescaMarcaje ();
    }
       

    void ActorTablero::controlSobreRetrato () {
        //
        SobreRetrato sobre_ahora;
        sobre_ahora.esta = false;
        //
        if (presencia_actuante_izqrd.panel_retrato.contiene (unir2d::Raton::posicion ())) {
            sobre_ahora.esta = true;
            sobre_ahora.lado = LadoTablero::Izquierda;
        }
        if (presencia_actuante_derch.panel_retrato.contiene (unir2d::Raton::posicion ())) {
            sobre_ahora.esta = true;
            sobre_ahora.lado = LadoTablero::Derecha;
        }
        //
        if (sobre_ahora.esta) {
            if (sobre_habilidad.esta) {
                juego->sucesos ()->saliendoHabilidad (sobre_habilidad.lado, sobre_habilidad.indice);               
                sobre_habilidad.esta = false;
            } else if (sobre_retrato.esta) {
                if (sobre_retrato.lado   == sobre_ahora.lado) {
                    // nada que hacer
                } else {
                    juego->sucesos ()->saliendoActuante (sobre_retrato.lado); 
                    sobre_retrato = sobre_ahora;                    
                    juego->sucesos ()->entrandoActuante (sobre_retrato.lado);
                }
            } else {
                //presencia (sobre_ahora.lado).indicaHabilidad (sobre_ahora.indice);
                sobre_retrato = sobre_ahora;
                juego->sucesos ()->entrandoActuante (sobre_retrato.lado);
            }
        } else {
            if (sobre_retrato.esta) {
                juego->sucesos ()->saliendoActuante (sobre_retrato.lado);               
                sobre_retrato.esta = false;
            } else {
                // nada que hacer
            }
        }
    }


    void ActorTablero::controlSobreHabilidad () {
        //
        SobreHabilidad sobre_ahora;
        sobre_ahora.esta = false;
        //
        for (int indc = 0; indc < presencia_actuante_izqrd.paneles_habilidad.size (); ++ indc) {
            if (presencia_actuante_izqrd.paneles_habilidad [indc].contiene (unir2d::Raton::posicion ())) {
                sobre_ahora.esta   = true;
                sobre_ahora.lado   = LadoTablero::Izquierda;
                sobre_ahora.indice = indc;
            }
        }
        for (int indc = 0; indc < presencia_actuante_derch.paneles_habilidad.size (); ++ indc) {
            if (presencia_actuante_derch.paneles_habilidad [indc].contiene (unir2d::Raton::posicion ())) {
                sobre_ahora.esta   = true;
                sobre_ahora.lado   = LadoTablero::Derecha;
                sobre_ahora.indice = indc;
            }
        }
        //
        if (sobre_ahora.esta) {
            if (sobre_retrato.esta) {
                juego->sucesos ()->saliendoActuante (sobre_habilidad.lado);               
                sobre_retrato.esta = false;
            } else if (sobre_habilidad.esta) {
                if (sobre_habilidad.lado   == sobre_ahora.lado &&
                    sobre_habilidad.indice == sobre_ahora.indice   ) {
                    // nada que hacer
                } else {
                    juego->sucesos ()->saliendoHabilidad (sobre_habilidad.lado, sobre_habilidad.indice); 
                    sobre_habilidad = sobre_ahora;                    
                    juego->sucesos ()->entrandoHabilidad (sobre_habilidad.lado, sobre_habilidad.indice);
                }
            } else {
                //presencia (sobre_ahora.lado).indicaHabilidad (sobre_ahora.indice);
                sobre_habilidad = sobre_ahora;
                juego->sucesos ()->entrandoHabilidad (sobre_habilidad.lado, sobre_habilidad.indice);
            }
        } else {
            if (sobre_habilidad.esta) {
                juego->sucesos ()->saliendoHabilidad (sobre_habilidad.lado, sobre_habilidad.indice);               
                sobre_habilidad.esta = false;
            } else {
                // nada que hacer
            }
        }
    }


    void ActorTablero::controlRetratoPulsacion () {
        bool dclic = unir2d::Raton::dobleClic ();
        bool sclic = unir2d::Raton::pulsando (unir2d::BotonRaton::izquierda);
        if (sclic) {
            if (presencia_actuante_izqrd.panel_retrato.contiene (unir2d::Raton::posicion ())) {       
                juego->sucesos ()->actuanteSeleccionado (LadoTablero::Izquierda);
            }
            if (presencia_actuante_derch.panel_retrato.contiene (unir2d::Raton::posicion ())) {    
                juego->sucesos ()->actuanteSeleccionado (LadoTablero::Derecha);
            }
        }
    }


    void ActorTablero::controlHabilidadPulsacion () {
        bool dclic = unir2d::Raton::dobleClic ();
        bool sclic = unir2d::Raton::pulsando (unir2d::BotonRaton::izquierda);
        if (sclic) {
            for (int indc = 0; indc < presencia_actuante_izqrd.paneles_habilidad.size (); ++ indc) {
                if (presencia_actuante_izqrd.paneles_habilidad [indc].contiene (unir2d::Raton::posicion ())) {
                    juego->sucesos ()->habilidadSeleccionada (LadoTablero::Izquierda, indc);
                }
            }
            for (int indc = 0; indc < presencia_actuante_derch.paneles_habilidad.size (); ++ indc) {
                if (presencia_actuante_derch.paneles_habilidad [indc].contiene (unir2d::Raton::posicion ())) {
                    juego->sucesos ()->habilidadSeleccionada (LadoTablero::Derecha, indc);
                }
            }
        }
    }


    void ActorTablero::controlSobreCelda () {
        //
        SobreCelda sobre_ahora;
        sobre_ahora.esta = false;
        //
        Coord coord {};
        Vector poscn = unir2d::Raton::posicion ();
        poscn -= PresenciaTablero::regionRejilla.posicion ();
        rejilla_tablero.localizaCelda (poscn, coord); 
        if (coord != Coord {0, 0}) { 
            sobre_ahora.esta  = true;
            sobre_ahora.celda = coord;
        }
        //
        if (sobre_ahora.esta) {
            if (sobre_celda.esta) {
                if (sobre_celda.celda == sobre_ahora.celda) {
                    // nada que hacer
                } else {
                    juego->sucesos ()->saliendoCelda (sobre_celda.celda); 
                    sobre_celda = sobre_ahora;                    
                    juego->sucesos ()->entrandoCelda (sobre_celda.celda);
                }
            } else {
                sobre_celda = sobre_ahora;
                juego->sucesos ()->entrandoCelda (sobre_celda.celda);
            }
        } else {
            if (sobre_celda.esta) {
                juego->sucesos ()->saliendoCelda (sobre_celda.celda);               
                sobre_celda.esta = false;
            } else {
                // nada que hacer
            }
        }
    }


    void ActorTablero::controlCeldaPulsacion () {
        bool dclic = unir2d::Raton::dobleClic ();
        bool sclic = unir2d::Raton::pulsando (unir2d::BotonRaton::izquierda);
        if (dclic || sclic) {
            Coord coord {};
            Vector poscn = unir2d::Raton::posicion ();
            poscn -= PresenciaTablero::regionRejilla.posicion ();
            rejilla_tablero.localizaCelda (poscn, coord); 
            if (coord != Coord {0, 0}) { 
                if (dclic) {
                    juego->sucesos ()->celdaSeleccionada (coord);
                } else if (sclic) {
                    juego->sucesos ()->celdaPulsada (coord);
                }
            }
        }
    }


    void ActorTablero::controlAyudaPulsacion () {
        bool dclic = unir2d::Raton::dobleClic ();
        bool sclic = unir2d::Raton::pulsando (unir2d::BotonRaton::izquierda);
        if (sclic) {
            Vector separa {unir2d::Raton::posicion () - PresenciaTablero::centro_ayuda};  
            if (unir2d::norma (separa) < PresenciaTablero::radio_ayuda) {
                juego->sucesos ()->ayudaSeleccionada ();
            }
        }
    }


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    void ActorTablero::aserta (bool expresion, const string & mensaje) {
        if (expresion) {
            return;
        }
        throw std::logic_error (mensaje);
    }


}