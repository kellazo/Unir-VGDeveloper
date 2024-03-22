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


    void ActorMusica::inicia () {
        musica = new unir2d::Sonido {};
        musica->abre       (archivo_musica);
        musica->ponVolumen (volumen_musica);
    }


    void ActorMusica::termina () {
        delete musica;
        musica = nullptr;
    }


    void ActorMusica::actualiza (double tiempo_seg) {
        if (! iniciada) {
            musica->suena ();
            iniciada = true;
            return;
        } 
        if (! musica->sonando ()) {
            musica->repite ();
        }
    }


    void ActorMusica::bajaMusica () {
        int volumen = musica->volumen ();
        volumen = static_cast <int> (volumen * 0.3f);
        musica->ponVolumen (volumen);
    }


}

