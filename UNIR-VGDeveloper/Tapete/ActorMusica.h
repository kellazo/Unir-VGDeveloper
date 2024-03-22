// proyecto: Grupal/Tapete
// archivo:  ActorMusica.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class JuegoMesaBase;


    class ActorMusica : public unir2d::ActorBase {
    public:

        explicit ActorMusica (JuegoMesaBase * juego);
        ~ActorMusica ();

        string archivoMusica ();
        int    volumenMusica ();
        void asignaMusica (const string & archivo_musica, int volumen);

        void bajaMusica ();

    protected:

        void inicia () override;
        void termina () override;

        void actualiza (double tiempo_seg) override;

    private:

        JuegoMesaBase * juego {}; 

        string archivo_musica {};
        int    volumen_musica {};

        unir2d::Sonido * musica {};

        bool iniciada {};

    };


}

