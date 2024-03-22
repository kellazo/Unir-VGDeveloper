// proyecto: Grupal/Tapete
// arhivo:   PresenciaHabilidades.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    PresenciaHabilidades::PresenciaHabilidades (ActorTablero * actor_tablero) {
        this->actor_tablero = actor_tablero;
    }


    PresenciaHabilidades::~PresenciaHabilidades () {
        actor_tablero = nullptr;
    }


    std::vector <unir2d::Imagen *> PresenciaHabilidades::imagenesHabilidades (ActorPersonaje * personaje) {
        return imagenes_habilidades [personaje->indice ()];
    }


    std::vector <unir2d::Imagen *> PresenciaHabilidades::imagenesFondosHabilidad (ActorPersonaje * personaje) {
        return imagenes_fondos [personaje->indice ()];
    }


    void PresenciaHabilidades::prepara () {
        texturas_fondos     .resize (actor_tablero->juego->habilidades ().size ());
        texturas_habilidades.resize (actor_tablero->juego->habilidades ().size ());
        for (int indc = 0; indc < texturas_habilidades.size (); ++ indc) {
            Habilidad * habld = actor_tablero->juego->habilidades () [indc];
            texturas_fondos      [indc] = new unir2d::Textura {};
            texturas_habilidades [indc] = new unir2d::Textura {};
            texturas_fondos      [indc]->carga (habld->archivoFondoImagen ());
            texturas_habilidades [indc]->carga (habld->archivoImagen ());
        }
        imagenes_fondos     .resize (actor_tablero->juego->personajes ().size ());
        imagenes_habilidades.resize (actor_tablero->juego->personajes ().size ());
        for (int indc_persj = 0; indc_persj < imagenes_habilidades.size (); ++ indc_persj) {
            ActorPersonaje * persj = actor_tablero->juego->personajes () [indc_persj];
            imagenes_fondos      [indc_persj].resize (persj->habilidades ().size ());
            imagenes_habilidades [indc_persj].resize (persj->habilidades ().size ());
            for (int indc_habld = 0; indc_habld < imagenes_habilidades [indc_persj].size (); ++ indc_habld) {
                Habilidad * habld = persj->habilidades () [indc_habld];
                imagenes_fondos      [indc_persj] [indc_habld] = new unir2d::Imagen {};
                imagenes_habilidades [indc_persj] [indc_habld] = new unir2d::Imagen {};
                imagenes_fondos      [indc_persj] [indc_habld]->asigna (texturas_fondos      [habld->indice ()]);
                imagenes_habilidades [indc_persj] [indc_habld]->asigna (texturas_habilidades [habld->indice ()]);
                imagenes_fondos      [indc_persj] [indc_habld]->ponVisible (false);   
                imagenes_habilidades [indc_persj] [indc_habld]->ponVisible (false);   
                actor_tablero->agregaDibujo (imagenes_fondos      [indc_persj] [indc_habld]);
                actor_tablero->agregaDibujo (imagenes_habilidades [indc_persj] [indc_habld]);
            }
        }
        sonidos_habilidades.resize (actor_tablero->juego->habilidades ().size ());
        for (int indc = 0; indc < texturas_habilidades.size (); ++ indc) {
            Habilidad * habld = actor_tablero->juego->habilidades () [indc];
            sonidos_habilidades [indc] = new unir2d::Sonido {};
            sonidos_habilidades [indc]->carga (habld->archivoSonido ());
        }
    }


    void PresenciaHabilidades::libera () {
        for (int indc = 0; indc < sonidos_habilidades.size (); ++ indc) {
            delete sonidos_habilidades [indc];
        }
        sonidos_habilidades.clear ();
        //
        for (int indc_persj = 0; indc_persj < imagenes_habilidades.size (); ++ indc_persj) {
            for (int indc_habld = 0; indc_habld < imagenes_habilidades [indc_persj].size (); ++ indc_habld) {
                delete imagenes_habilidades [indc_persj] [indc_habld];
                delete imagenes_fondos      [indc_persj] [indc_habld];
            }
            imagenes_habilidades [indc_persj].clear ();
            imagenes_fondos      [indc_persj].clear ();
        }
        imagenes_habilidades.clear ();
        imagenes_fondos     .clear ();
        for (int indc = 0; indc < texturas_habilidades.size (); ++ indc) {
            aserta (texturas_habilidades [indc]->cuentaUsos () == 0, "recursos cautivos");
            aserta (texturas_fondos      [indc]->cuentaUsos () == 0, "recursos cautivos");
            delete texturas_habilidades [indc];
            delete texturas_fondos      [indc];
        }
        texturas_habilidades.clear ();
        texturas_fondos     .clear ();
    }


    void PresenciaHabilidades::aserta (bool expresion, const string & mensaje) {
        if (expresion) {
            return;
        }
        throw std::logic_error (mensaje);
    }


}