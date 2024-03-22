// proyecto: Grupal/Tapete
// arhivo:   PresenciaPersonaje.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    PresenciaPersonaje::PresenciaPersonaje (ActorPersonaje * actor_personaje) {
        this->actor_personaje = actor_personaje;
    }


    PresenciaPersonaje::~PresenciaPersonaje () {
        this->actor_personaje = nullptr;
    }


    void PresenciaPersonaje::prepara () {
        //
        textura_retrato = new unir2d::Textura ();
        textura_retrato->carga (actor_personaje->archivo_retrato);
        //
        preparaPanel   (actor_personaje->lado_tablero, actor_personaje->indice_en_equipo);
        preparaTitulo  (actor_personaje->juego_->personajes (), actor_personaje);
        preparaRetratoLateral ();
        preparaBarraVida ();
        //
        preparaRetratoActuante ();
        //preparaHabilidadesActuante (actor_personaje);
        //
        preparaFicha ();
    }


    void PresenciaPersonaje::libera () {
        //
        delete imagen_ficha;
        imagen_ficha = nullptr;
        delete textura_ficha;
        textura_ficha = nullptr;
        //
        //if (textura_ficha_azul != nullptr && 
        //    textura_ficha_azul->cuentaUsos () == 0) {
        //    delete textura_ficha_azul;
        //    textura_ficha_azul = nullptr;
        //}      
        //if (textura_ficha_roja != nullptr && 
        //    textura_ficha_roja->cuentaUsos () == 0) {
        //    delete textura_ficha_roja;
        //    textura_ficha_roja = nullptr;
        //}      
        //
        //for (unir2d::Imagen * imgn : imagenes_habilidad_actuante) {
        //    delete imgn;
        //}
        //imagenes_habilidad_actuante.clear ();
        //
        delete imagen_retrato_actuante;
        imagen_retrato_actuante = nullptr;
        //
        delete imagen_barra_vida;
        imagen_barra_vida = nullptr;
        if (textura_barras_vida->cuentaUsos () == 0) {
            delete textura_barras_vida;
            textura_barras_vida = nullptr;
        }      
        //
        delete imagen_marco_retrato;
        imagen_marco_retrato = nullptr;
        if (textura_marco_retrato->cuentaUsos () == 0) {
            delete textura_marco_retrato;
            textura_marco_retrato = nullptr;
        }
        delete imagen_retrato_lateral;
        imagen_retrato_lateral = nullptr;
        delete fondo_retrato;
        fondo_retrato = nullptr;
        //
//        delete texto_nombre;
//        texto_nombre = nullptr;
        delete imagen_titulo;
        imagen_titulo = nullptr;
        if (textura_titulos->cuentaUsos () == 0) {
            delete textura_titulos;
            textura_titulos = nullptr;
        }
        //
        delete textura_retrato;
        textura_retrato = nullptr;
    }


    void PresenciaPersonaje::preparaPanel (LadoTablero lado_tablero, int indice_grupo) {
        aserta (lado_tablero != LadoTablero::nulo, "parámatro 'lado_tablero' inválido");
        float x = 0;
        if (lado_tablero == LadoTablero::Izquierda) {
            x = PresenciaTablero::regionPanelVertclIzqrd.posicion ().x () + 8;
        } else if (lado_tablero == LadoTablero::Derecha) {
            x = PresenciaTablero::regionPanelVertclDerch.posicion ().x () + 8;
        }
        float y = PresenciaTablero::regionPanelVertclIzqrd.posicion ().y () + 
                  indice_grupo * 135.0f + 68;
        panel_lateral = Region {x, y, 92, 128};
    }


    void PresenciaPersonaje::preparaTitulo (
            const std::vector <ActorPersonaje *> & lista_personajes, 
            ActorPersonaje *                       personaje_actual ) {
        constexpr int   filas_plnch =  6;
        constexpr int   colns_plnch =  2;
        constexpr float anchr_plnch = 89;
        constexpr float altra_plnch = 20;
        //
        if (textura_titulos == nullptr) {
            textura_titulos = new unir2d::Textura {};
            textura_titulos->crea (Vector {anchr_plnch * colns_plnch, altra_plnch * filas_plnch});
            //
            unir2d::Textura * textr_plnch = new unir2d::Textura {};
            textr_plnch->carga (JuegoMesaBase::carpetaActivos () + "plancha_titulo.png");
            unir2d::Imagen * imagn_plnch = new unir2d::Imagen {};
            imagn_plnch->asigna (textr_plnch);
            for (int fila = 0; fila < 6; ++ fila) {
                for (int coln = 0; coln < 2; ++ coln) {
                    imagn_plnch->ponPosicion (Vector {coln * anchr_plnch, fila * altra_plnch});
                    textura_titulos->dibuja (imagn_plnch);
                }
            }
            delete imagn_plnch;
            imagn_plnch = nullptr;
            delete textr_plnch;
            textr_plnch = nullptr;
            //
            unir2d::Texto * texto_nombr = new unir2d::Texto ("timesbi");
            texto_nombr->ponTamano (18);
            texto_nombr->ponColor (Color::GrisOscuro);
            for (const ActorPersonaje * actor_persj : lista_personajes) {
                int coln;
                if (actor_persj->lado_tablero == LadoTablero::Izquierda) {
                    coln = 0;
                } else {
                    coln = 1;
                }
                int fila = actor_persj->indice_en_equipo;
                texto_nombr->ponCadena (actor_persj->nombre_);
                float margen = (anchr_plnch - texto_nombr->anchura ()) / 2;
                texto_nombr->ponPosicion (
                        Vector {coln * anchr_plnch, fila * altra_plnch} + Vector {margen, -3});
                textura_titulos->dibuja (texto_nombr);
            }
            delete texto_nombr;
            texto_nombr = nullptr;
        }
        //
        imagen_titulo = new unir2d::Imagen {};
        imagen_titulo->asigna (textura_titulos);
        imagen_titulo->defineEstampas (filas_plnch, colns_plnch);
        int coln;
        if (personaje_actual->lado_tablero == LadoTablero::Izquierda) {
            coln = 1;
        } else {
            coln = 2;
        }
        int fila = personaje_actual->indice_en_equipo + 1;
        imagen_titulo->seleccionaEstampa (fila, coln);
        imagen_titulo->ponPosicion (panel_lateral.posicion () + Vector {2, 0});
        //
        actor_personaje->agregaDibujo (imagen_titulo);
    }


    void PresenciaPersonaje::preparaRetratoLateral () {
        fondo_retrato = new unir2d::Rectangulo {80, 80};
        fondo_retrato->ponPosicion (panel_lateral.posicion () + Vector {6, 26});
        fondo_retrato->ponColor (Color {0x50, 0x50, 0x50});
        //
        imagen_retrato_lateral = new unir2d::Imagen ();
        imagen_retrato_lateral->ponPosicion (panel_lateral.posicion () + Vector {10, 30});
        imagen_retrato_lateral->asigna (textura_retrato);
        //
        if (textura_marco_retrato == nullptr) {
            textura_marco_retrato = new unir2d::Textura {};
            textura_marco_retrato->carga (JuegoMesaBase::carpetaActivos () + "marco_75.png");
        }
        imagen_marco_retrato = new unir2d::Imagen ();
        imagen_marco_retrato->ponPosicion (panel_lateral.posicion () + Vector {0, 20});
        imagen_marco_retrato->asigna (textura_marco_retrato);
        //
        actor_personaje->agregaDibujo (fondo_retrato);
        actor_personaje->agregaDibujo (imagen_retrato_lateral);
        actor_personaje->agregaDibujo (imagen_marco_retrato);
    }


    int PresenciaPersonaje::indiceBarraVida () {
        float coefic = ((float) actor_personaje->vitalidad ()) / (float) ActorPersonaje::maximaVitalidad;
        int indice_vida = (int) (coefic * (PresenciaPersonaje::cuentaBarrasVida - 1)) + 1;
        assert (1 <= indice_vida && indice_vida <= PresenciaPersonaje::cuentaBarrasVida);
        return PresenciaPersonaje::cuentaBarrasVida - indice_vida + 1;
    }


    void PresenciaPersonaje::preparaBarraVida () {
        if (textura_barras_vida == nullptr) {
            textura_barras_vida = new unir2d::Textura {};
            textura_barras_vida->carga (JuegoMesaBase::carpetaActivos () + "barras_vida.png");
        }
        imagen_barra_vida = new unir2d::Imagen {};
        imagen_barra_vida->asigna (textura_barras_vida);
        imagen_barra_vida->defineEstampas (cuentaBarrasVida, 1);
        imagen_barra_vida->seleccionaEstampa (indiceBarraVida (), 1);
        imagen_barra_vida->ponPosicion (panel_lateral.posicion () + Vector {1, 112});
        //
        actor_personaje->agregaDibujo (imagen_barra_vida);
    }


    void PresenciaPersonaje::preparaRetratoActuante () {
        imagen_retrato_actuante = new unir2d::Imagen ();
        //imagen_retrato_actuante->ponPosicion (panel_lateral.posicion () + Vector {10, 38});
        imagen_retrato_actuante->asigna (textura_retrato);
        imagen_retrato_actuante->ponVisible (false);
        //
        actor_personaje->agregaDibujo (imagen_retrato_actuante);
    }


    void PresenciaPersonaje::preparaFicha () {
        textura_ficha = new unir2d::Textura {};
        textura_ficha->carga (actor_personaje->archivoFicha ());
        imagen_ficha = new unir2d::Imagen {};
        imagen_ficha->asigna (textura_ficha);
        //
        actor_personaje->agregaDibujo (imagen_ficha);
////////////////////////////////////////////////////////////////////////////////////////////////////
        //aserta (lado_tablero != LadoTablero::nulo, "parámatro 'lado_tablero' inválido");
        //if (textura_ficha_roja == nullptr) {
        //    textura_ficha_roja = new unir2d::Textura {};
        //    textura_ficha_roja->carga (JuegoMesaBase::carpetaActivos () + "ficha_roja.png");
        //}
        //if (textura_ficha_azul == nullptr) {
        //    textura_ficha_azul = new unir2d::Textura {};
        //    textura_ficha_azul->carga (JuegoMesaBase::carpetaActivos () + "ficha_azul.png");
        //}
        //imagen_ficha = new unir2d::Imagen {};
        //if (lado_tablero == LadoTablero::Izquierda) {
        //    imagen_ficha->asigna (textura_ficha_roja);
        //} else {
        //    imagen_ficha->asigna (textura_ficha_azul);
        //}
        ////
        //actor_personaje->agregaDibujo (imagen_ficha);
    }


    unir2d::Imagen * PresenciaPersonaje::imagenRetrato () const {
        return imagen_retrato_actuante;
    }


    void PresenciaPersonaje::indicaFicha (const wstring & cadena) {
        Vector poscn = RejillaTablero::centroHexagono (actor_personaje->sitio_ficha);
        poscn += PresenciaTablero::regionRejilla.posicion ();
        poscn -= PresenciaPersonaje::deslizaFicha;
        poscn -= Vector {0, 24};
        actor_personaje->juego_->tablero ()->indicador ().indica (poscn, cadena);
    }


    void PresenciaPersonaje::oscureceRetrato () {
        imagen_retrato_lateral->colorea (Color::Gris);
        // no me mola:
        //imagen_retrato_actuante->colorea (Color::Gris);
    }


    void PresenciaPersonaje::aclaraRetrato () {
        imagen_retrato_lateral->colorea (Color::Blanco);
        // no me mola:
        //imagen_retrato_actuante->colorea (Color::Blanco);
    }


    void PresenciaPersonaje::refrescaBarraVida () {
        imagen_barra_vida->seleccionaEstampa (indiceBarraVida (), 1);
    }


    void PresenciaPersonaje::aserta (bool expresion, const string & mensaje) {
        if (expresion) {
            return;
        }
        throw std::logic_error (mensaje);
    }


}

