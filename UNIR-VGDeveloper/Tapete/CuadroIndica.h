// proyecto: Grupal/Tapete
// archivo:  CuadroIndica.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ActorTablero;


    class CuadroIndica {
    public:

        void prepara ();
        void libera ();

        void indica (Vector poscn, const wstring & cadena);
        void desindica ();

    private:

        static constexpr Color colorIndica {239, 228, 176, 255};


        ActorTablero * actor_tablero;

        unir2d::Rectangulo * rectangl_indica {};
        unir2d::Trazos *     trazos_indica {};
        unir2d::Texto *      texto_indica {};


        explicit CuadroIndica (ActorTablero * actor_tablero);
        ~CuadroIndica ();


        friend class ActorTablero;

    };


}


