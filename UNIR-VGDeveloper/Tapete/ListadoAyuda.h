// proyecto: Grupal/Tapete
// archivo:  ListadoAyuda.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ActorTablero;


    class ListadoAyuda {
    public:

        static constexpr int lineasTextoListado = 56;

        // Establece que las proximas escrituras sean en negrita o en claro.
        void enNegrita ();
        void enClaro ();
        // Escribe y salta de línea.
        void escribe (const wchar_t * texto);
        void escribe (const wstring & texto);
        void saltaLinea ();
        void borra ();
        int  linea ();

        void deslizaArriba ();
        void deslizaAbajo ();

        void muestra ();
        void oculta ();

    private:

        static constexpr Vector tamano {600, 800};
        static constexpr Vector posicion {PresenciaTablero::regionRejilla.posicion () + 
                                          0.5f * PresenciaTablero::tamanoRejilla - 
                                          0.5f * tamano                                };
        static constexpr Region region {posicion, tamano};
        static constexpr int cuentaBoquetes = 40;
        static constexpr int cuentaTrazos   = 80;


        ActorTablero * actor_tablero;

        bool visible {};  

        unir2d::Rectangulo *                           papel;
        std::array <unir2d::Circulo *, cuentaBoquetes> boquetes_izqrd;
        std::array <unir2d::Circulo *, cuentaBoquetes> boquetes_derch;
        unir2d::Trazos *                               trazos_izqrd;
        unir2d::Trazos *                               trazos_derch;
        unir2d::Rectangulo *                           sombra_derch;
        unir2d::Rectangulo *                           sombra_abajo;

        std::array <unir2d::Texto *, lineasTextoListado> texto_claro {};
        std::array <unir2d::Texto *, lineasTextoListado> texto_oscuro {};
        unir2d::Texto *                                  sigue_arriba {};
        unir2d::Texto *                                  sigue_abajo {};

        std::vector <bool>    negrita_linea {};
        std::vector <wstring> cadena_linea {}; 

        int  linea_actual {};
        bool negrita_actual {};
        int  bajante {};


        explicit ListadoAyuda (ActorTablero * actor_tablero);
        ~ListadoAyuda ();

        void prepara ();
        void libera ();

        void escribeLineas ();
        void escribeSigue ();


        friend class ActorTablero;

    };


}