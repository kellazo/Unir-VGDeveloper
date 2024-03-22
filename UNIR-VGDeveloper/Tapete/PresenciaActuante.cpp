// proyecto: Grupal/Tapete
// arhivo:   PresenciaActuante.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    PresenciaActuante::PresenciaActuante (ActorTablero * actor_tablero, LadoTablero lado_tablero) {
        assert (lado_tablero != LadoTablero::nulo);  // no lanzar excepciones en los constructores
        this->actor_tablero = actor_tablero;
        this->lado_tablero = lado_tablero;
    }


    PresenciaActuante::~PresenciaActuante () {
        this->actor_tablero = nullptr;
    }


    void PresenciaActuante::prepara () {
        preparaPaneles ();
        preparaPersonaje ();
        preparaHabilidades ();
        preparaPuntosAccion ();
        preparaBarraVida ();
        preparaMarcas ();
        aserta (! visible_, "presencia visible");
        aserta (personaje_mostrado == nullptr, "sin personaje para mostrar");
    }


    void PresenciaActuante::libera () {
        delete imagen_barra_vida;
        imagen_barra_vida = nullptr;
        if (textura_barras_vida->cuentaUsos () == 0) {
            delete textura_barras_vida;
            textura_barras_vida = nullptr;
        }      
        //
        for (int indc = 0; indc < cuentaHabilidades; ++ indc) {
            delete imagen_marco_habilidad [indc];
            imagen_marco_habilidad [indc] = nullptr;
        }
        if (textura_marco_habilidad->cuentaUsos () == 0) {
            delete textura_marco_habilidad;
            textura_marco_habilidad = nullptr;
        }
        //
        for (int indc = 0; indc < cuentaPuntosAccion; ++ indc) {
            delete imagen_luces_punto_accion [indc];
            imagen_luces_punto_accion [indc] = nullptr;
        }
        if (textura_luces_punto_accion->cuentaUsos () == 0) {
            delete textura_luces_punto_accion;
            textura_luces_punto_accion = nullptr;
        }
        //
        delete imagen_marca_retrato;
        imagen_marca_retrato = nullptr;
        for (int indc = 0; indc < PresenciaActuante::cuentaHabilidades; ++ indc) {
            delete imagen_marca_habilidad [indc];
            imagen_marca_habilidad [indc] = nullptr;
        }
        if (textura_marca != nullptr && textura_marca->cuentaUsos () == 0) {
            delete textura_marca;
            textura_marca = nullptr;
        }
        //
        delete imagen_marco_personaje;
        imagen_marco_personaje = nullptr;
        if (textura_marco_personaje != nullptr && textura_marco_personaje->cuentaUsos () == 0) {
            delete textura_marco_personaje;
            textura_marco_personaje = nullptr;
        }
    }


    void PresenciaActuante::preparaPaneles () {
        float x = 0;
        if (lado_tablero == LadoTablero::Izquierda) {
            x = PresenciaTablero::regionPanelAbajoIzqrd.posicion ().x () + 8;
        } else {
            x =  PresenciaTablero::regionPanelAbajoDerch.posicion ().x () + 8;
        }
        float y = PresenciaTablero::regionPanelAbajoIzqrd.posicion ().y ();
        panel_abajo = Region {x, y, 500, 100};
        //
        y += 20;
        panel_retrato = Region {x, y, 79, 79};
        x += 82;
        y += 14;
        for (int indc = 0; indc < paneles_habilidad.size (); ++ indc) {
            paneles_habilidad [indc] = Region {x, y, 51, 54};
            x += 52;
        }
        //
    }


    void PresenciaActuante::preparaPersonaje () {
        if (textura_marco_personaje == nullptr) {
            textura_marco_personaje = new unir2d::Textura {};
            textura_marco_personaje->carga (JuegoMesaBase::carpetaActivos () + "marco_personaje.png");
        }
        //
        imagen_marco_personaje = new unir2d::Imagen {};
        imagen_marco_personaje->asigna (textura_marco_personaje);
        imagen_marco_personaje->ponPosicion (panel_abajo.posicion () + Vector {0, 20});
        imagen_marco_personaje->ponVisible (false);
        //
        actor_tablero->agregaDibujo (imagen_marco_personaje);
    }


    void PresenciaActuante::preparaHabilidades () {
        if (textura_marco_habilidad == nullptr) {
            textura_marco_habilidad = new unir2d::Textura {};
            textura_marco_habilidad->carga (JuegoMesaBase::carpetaActivos () + "marco_habilidad.png");
        }
        //
        Vector poscn = panel_abajo.posicion () + Vector {81, 34};
        for (int indc = 0; indc < cuentaHabilidades; ++ indc) {
            imagen_marco_habilidad [indc] = new unir2d::Imagen {};
            imagen_marco_habilidad [indc]->asigna (textura_marco_habilidad);
            imagen_marco_habilidad [indc]->ponPosicion (poscn);
            poscn += Vector {52, 0};
            imagen_marco_habilidad [indc]->ponVisible (false);
        }
        //
        for (int indc = 0; indc < PresenciaActuante::cuentaHabilidades; ++ indc) {
            actor_tablero->agregaDibujo (imagen_marco_habilidad [indc]);
        }
    }


    void PresenciaActuante::preparaPuntosAccion () {
        // no termino de ver claro el uso de GestorActivos
        if (textura_luces_punto_accion == nullptr) {
            textura_luces_punto_accion = new unir2d::Textura {};
            textura_luces_punto_accion->carga (JuegoMesaBase::carpetaActivos () + "piloto_colores.png");
        }
        // 
        Vector poscn = panel_abajo.posicion () + Vector {74, 0};
        for (int indc = 0; indc < cuentaPuntosAccion; ++ indc) {
            imagen_luces_punto_accion [indc] = new unir2d::Imagen {};
            imagen_luces_punto_accion [indc]->asigna (textura_luces_punto_accion);
            imagen_luces_punto_accion [indc]->defineEstampas (1, 25);
            imagen_luces_punto_accion [indc]->ponPosicion (poscn);
            poscn += Vector {26, 0};
            imagen_luces_punto_accion [indc]->ponVisible (false);
        }
        //
        for (int indc = 0; indc < PresenciaActuante::cuentaPuntosAccion; ++ indc) {
            actor_tablero->agregaDibujo (imagen_luces_punto_accion [indc]);
        }
    }


    void PresenciaActuante::preparaBarraVida () {
        if (textura_barras_vida == nullptr) {
            textura_barras_vida = new unir2d::Textura {};
            textura_barras_vida->carga (JuegoMesaBase::carpetaActivos () + "barras_larga_vida.png");
        }
        imagen_barra_vida = new unir2d::Imagen {};
        imagen_barra_vida->asigna (textura_barras_vida);
        imagen_barra_vida->defineEstampas (cuentaBarrasVida, 1);
        imagen_barra_vida->ponPosicion (panel_abajo.posicion () + Vector {81, 96});
        imagen_barra_vida->ponVisible (false);
        //
        actor_tablero->agregaDibujo (imagen_barra_vida);
    }


    void PresenciaActuante::preparaMarcas () {
        if (textura_marca == nullptr) {
            textura_marca = new unir2d::Textura {};
            textura_marca->carga (JuegoMesaBase::carpetaActivos () + "marca_amarilla_corta.png");
        }
        //
        imagen_marca_retrato = new unir2d::Imagen {};
        imagen_marca_retrato->asigna (textura_marca);
        imagen_marca_retrato->ponPosicion (panel_retrato.posicion () + Vector {5, 70});
        imagen_marca_retrato->ponVisible (false);
        //
        for (int indc = 0; indc < PresenciaActuante::cuentaHabilidades; ++ indc) {
            imagen_marca_habilidad [indc] = new unir2d::Imagen {};
            imagen_marca_habilidad [indc]->asigna (textura_marca);
            imagen_marca_habilidad [indc]->ponPosicion (paneles_habilidad [indc].posicion () + Vector {-9, 45});
            imagen_marca_habilidad [indc]->ponVisible (false);
        }
        //
        actor_tablero->agregaDibujo (imagen_marca_retrato);
        for (int indc = 0; indc < PresenciaActuante::cuentaHabilidades; ++ indc) {
            actor_tablero->agregaDibujo (imagen_marca_habilidad [indc]);
        }
    }


    void PresenciaActuante::muestra (ActorPersonaje * personaje) {
        aserta (! visible_, "presencia visible");
        //
        this->personaje_mostrado = personaje;

        imagen_marco_personaje->ponVisible (true);

        unir2d::Imagen * retrato = personaje->presencia ().imagenRetrato ();
        retrato->ponPosicion (panel_abajo.posicion () + Vector {2, 22});
        retrato->ponVisible (true);

        for (int indc = 0; indc < cuentaPuntosAccion; ++ indc) {
            imagen_luces_punto_accion [indc]->seleccionaEstampa (1, 1);
            imagen_luces_punto_accion [indc]->ponVisible (true);
        }

        for (int indc = 0; indc < cuentaHabilidades; ++ indc) {
            imagen_marco_habilidad [indc]->ponVisible (true);
        }


        std::vector <unir2d::Imagen *> lista_habld = 
                actor_tablero->presencia_habilidades.imagenesHabilidades (personaje);
        std::vector <unir2d::Imagen *> lista_fonds = 
                actor_tablero->presencia_habilidades.imagenesFondosHabilidad (personaje);
        for (int indc = 0; indc < lista_habld.size (); ++ indc) {
            lista_habld [indc]->ponPosicion (imagen_marco_habilidad [indc]->posicion () + Vector {2, 2});
            lista_fonds [indc]->ponPosicion (imagen_marco_habilidad [indc]->posicion () + Vector {2, 2});
            lista_habld [indc]->ponVisible (true);
            lista_fonds [indc]->ponVisible (true);
        }

        //int indc = 0;
        //for (unir2d::Imagen * imagen : 
        //            actor_tablero->presencia_habilidades.imagenesHabilidades (personaje)) {
        //    imagen->ponVisible (true);
        //    imagen->ponPosicion (imagen_marco_habilidad [indc]->posicion () + Vector {2, 2});
        //    indc ++;
        //}      

        imagen_barra_vida->seleccionaEstampa (indiceBarraVida (), 1);
        imagen_barra_vida->ponVisible (true);
        //
        visible_ = true;
    }


    void PresenciaActuante::oculta () {
        aserta (visible_, "presencia no visible");
        //
        imagen_marco_personaje->ponVisible (false);

        unir2d::Imagen * retrato = personaje_mostrado->presencia ().imagenRetrato ();
        retrato->ponVisible (false);

        for (int indc = 0; indc < cuentaPuntosAccion; ++ indc) {
            imagen_luces_punto_accion [indc]->ponVisible (false);
        }

        for (int indc = 0; indc < cuentaHabilidades; ++ indc) {
            imagen_marco_habilidad [indc]->ponVisible (false);
        }

        std::vector <unir2d::Imagen *> lista_habld = 
                actor_tablero->presencia_habilidades.imagenesHabilidades (personaje_mostrado);
        std::vector <unir2d::Imagen *> lista_fonds = 
                actor_tablero->presencia_habilidades.imagenesFondosHabilidad (personaje_mostrado);
        for (int indc = 0; indc < lista_habld.size (); ++ indc) {
            lista_habld [indc]->ponVisible (false);
            lista_fonds [indc]->ponVisible (false);
        }

        //for (unir2d::Imagen * imagen : 
        //            actor_tablero->presencia_habilidades.imagenesHabilidades (personaje_mostrado)) {
        //    imagen->ponVisible (false);
        //}
        imagen_barra_vida->ponVisible (false);
        //
        imagen_marca_retrato->ponVisible (false);
        for (int indc = 0; indc < PresenciaActuante::cuentaHabilidades; ++ indc) {
            imagen_marca_habilidad [indc]->ponVisible (false);
        }
        //
        visible_ = false;
        personaje_mostrado = nullptr;
    }


    bool PresenciaActuante::visible () {
        return visible_;
    }


    ActorPersonaje * PresenciaActuante::personaje () {
        return personaje_mostrado;
    }


    void PresenciaActuante::marcaRetrato () {
        desmarcaRetratoHabilidad ();
        imagen_marca_retrato->ponVisible (true);
    }


    void PresenciaActuante::marcaHabilidad (int indice) {
        desmarcaRetratoHabilidad ();
        imagen_marca_habilidad [indice]->ponVisible (true);
    }


    void PresenciaActuante::desmarcaRetratoHabilidad () {
        imagen_marca_retrato->ponVisible (false);
        for (int indc = 0; indc < PresenciaActuante::cuentaHabilidades; ++ indc) {
            imagen_marca_habilidad [indc]->ponVisible (false);
        }
    }


    void PresenciaActuante::iluminaPuntosAccion (int actuales, int en_juego) {
        int azules = actuales;
        int narnjs = en_juego;
        azules -= narnjs;
        for (int indc = 0; indc < cuentaPuntosAccion; ++ indc) {
            if (indc < azules) {
                imagen_luces_punto_accion [indc]->seleccionaEstampa (1, 15);
            } else if (indc < azules + narnjs) {
                imagen_luces_punto_accion [indc]->seleccionaEstampa (1, 5);
            } else {
                imagen_luces_punto_accion [indc]->seleccionaEstampa (1, 1);
            }
        }
    }


    void PresenciaActuante::refrescaBarraVida () {
        if (! visible_) {
            return;
        }
        imagen_barra_vida->seleccionaEstampa (indiceBarraVida (), 1);
    }
        

    int PresenciaActuante::indiceBarraVida () {
        float coefic = ((float) personaje_mostrado->vitalidad ()) / (float) ActorPersonaje::maximaVitalidad;
        int indice_vida = (int) (coefic * (PresenciaActuante::cuentaBarrasVida - 1)) + 1;
        assert (1 <= indice_vida && indice_vida <= PresenciaActuante::cuentaBarrasVida);
        return PresenciaActuante::cuentaBarrasVida - indice_vida + 1;
    }


    void PresenciaActuante::aserta (bool expresion, const string & mensaje) {
        if (expresion) {
            return;
        }
        throw std::logic_error (mensaje);
    }


}