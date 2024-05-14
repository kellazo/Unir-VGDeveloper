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

        // INICIO GUILLEM //
        string archivoMusicaLoop();
        int    volumenMusicaLoop ();
        void asignaMusicaLoop (const string& archivo_musica, int volumen);

        void bajaMusicaLoop ();
        // FIN GUILLEM //

    protected:

        void inicia () override;
        void termina () override;

        void actualiza (double tiempo_seg) override;

    private:

        JuegoMesaBase * juego {}; 

        string archivo_musica {};
        int    volumen_musica {};

        unir2d::Sonido * musica {};

        // INICIO GUILLEM //
        string archivo_musica_loop{};
        int    volumen_musica_loop {};
        unir2d::Sonido * musica_loop {};
        bool iniciada_loop {};
        // FIN GUILLEM //

        bool iniciada {};


    };


}

