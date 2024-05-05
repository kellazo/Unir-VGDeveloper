// proyecto: Grupal/Tapete
// arhivo:   ActorMusica.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    ActorMusica::ActorMusica (JuegoMesaBase * juego) {
        this->juego            = juego;
    }


    ActorMusica::~ActorMusica () {
        juego = nullptr;
    }


    string ActorMusica::archivoMusica () {
        return archivo_musica;
    }


    int ActorMusica::volumenMusica () {
        return volumen_musica;
    }


    void ActorMusica::asignaMusica (const string & archivo, int volumen) {
        archivo_musica = archivo;
        volumen_musica = volumen;
    }

    // INICIO GUILLEM //
     
    string ActorMusica::archivoMusicaLoop () {
        return archivo_musica_loop;
    }


    int ActorMusica::volumenMusicaLoop () {
        return volumen_musica_loop;
    }


    void ActorMusica::asignaMusicaLoop (const string& archivo, int volumen) {
        archivo_musica_loop = archivo;
        volumen_musica_loop = volumen;
    }
    // FIN GUILLEM //

    void ActorMusica::inicia () {
        musica = new unir2d::Sonido {};
        musica->abre       (archivo_musica);
        musica->ponVolumen (volumen_musica);
        // INICIO GUILLEM //
        musica_loop = new unir2d::Sonido{};
        musica_loop->abre       (archivo_musica_loop);
        musica_loop->ponVolumen (volumen_musica_loop);
        // FIN GUILLEM //

    }


    void ActorMusica::termina () {
        delete musica;
        musica = nullptr;
        // INICIO GUILLEM //
        delete musica_loop;
        musica_loop = nullptr;
        // FIN GUILLEM //
    }


    void ActorMusica::actualiza (double tiempo_seg) {
        
        // INICIO GUILLEM //
        // original
        /* if (!iniciada) {
          musica->suena();
          iniciada = true;
          return;
         }
        if (! musica->sonando ()) {
            musica->repite ();
        }*/
        
        if (!iniciada) {
             musica->suena();
              iniciada = true;
             return;
         }
        if (! musica->sonando()) {
            if (!iniciada_loop) {
                musica_loop->suena();
                iniciada_loop = true;
                return;
            }
            if (!musica_loop->sonando()) {
                musica_loop->repite ();
            }
        }
        // FIN GUILLEM //
    }


    void ActorMusica::bajaMusica() {
        int volumen = musica->volumen();
        volumen = static_cast <int> (volumen * 0.3f);
        musica->ponVolumen(volumen);
    }
    // INICIO GUILLEM //
    
    void ActorMusica::bajaMusicaLoop() {
        int volumen = musica_loop->volumen();
        volumen = static_cast <int> (volumen * 0.3f);
        musica_loop->ponVolumen(volumen);
    }
    // FIN GUILLEM //


}

