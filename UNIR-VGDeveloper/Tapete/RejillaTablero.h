// proyecto: Grupal/Tapete
// archivo:  RejillaTablero.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class RejillaTablero {
    public:

        static constexpr int   ladoHexagono  = 20;
        static constexpr float seno60        = 0.85f;
        static constexpr float seno60_exacto = 0.866f;

        static constexpr float distanciaCeldas = ladoHexagono * seno60 * 2;

        static constexpr int filas    = 51;
        static constexpr int columnas = 49;


        static Vector centroHexagono (Coord centro);
        static Vector verticeHexagono (Coord centro, int minuto);

        void localizaCelda (Vector punto, Coord & localizada);

        // las posiciones de las celdas comienzan en la (1, 1) y terminan en
        void marcaCelda (Coord posicion, Color color);
        void marcaCelda (Coord posicion, Color color, bool grueso);
        void desmarcaCelda (Coord posicion);
        void desmarcaCeldas ();

    private:

        static constexpr int   puntosHexagono = 7;


        ActorTablero * actor_tablero;

        unir2d::Trazos * trazos_rejilla {};

        struct MarcajeCelda {
            Coord posicion;
            Color color;
            bool  grueso;
        };
        std::vector <MarcajeCelda> marcaje_celdas {};

        unir2d::Trazos * trazos_marcaje {};
        bool             cambio_trazos_marcaje {};


        explicit RejillaTablero (ActorTablero * actor_tablero);
        ~RejillaTablero ();

        void prepara ();
        void libera ();

        std::vector <MarcajeCelda>::iterator buscaMarcaCelda (Coord posicion);

        void refrescaMarcaje ();
        void trazaHexagono (const MarcajeCelda & marcaje);


        friend class ActorTablero;
        friend class PresenciaTablero;

    };


}

