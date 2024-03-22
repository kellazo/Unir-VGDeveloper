// proyecto: Grupal/Tapete
// archivo:  PresenciaActuante.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class PresenciaActuante {
    public:

        void muestra (ActorPersonaje * personaje);
        void oculta ();
        bool visible ();
        ActorPersonaje * personaje ();

        void marcaRetrato ();
        void marcaHabilidad (int indice);
        void desmarcaRetratoHabilidad ();

        void iluminaPuntosAccion (int actuales, int en_juego);
        void refrescaBarraVida ();
        
    private:

        static constexpr int cuentaPuntosAccion = ActorPersonaje::maximoPuntosAccion;
        static constexpr int cuentaHabilidades  = ActorPersonaje::maximoHabilidades;
        static constexpr int cuentaBarrasVida   = 21;


        ActorTablero * actor_tablero;
        LadoTablero        lado_tablero;

        Region                                 panel_abajo {};
        Region                                 panel_retrato {};
        std::array <Region, cuentaHabilidades> paneles_habilidad {};

        inline static unir2d::Textura * textura_marco_personaje {};
        unir2d::Imagen *                imagen_marco_personaje {};

        inline static unir2d::Textura *                  textura_marco_habilidad {};
        std::array <unir2d::Imagen *, cuentaHabilidades> imagen_marco_habilidad {};
        //
        inline static unir2d::Textura *                   textura_luces_punto_accion {};
        std::array <unir2d::Imagen *, cuentaPuntosAccion> imagen_luces_punto_accion {};

        inline static unir2d::Textura * textura_barras_vida {};
        unir2d::Imagen *                imagen_barra_vida {};

        inline static unir2d::Textura *                  textura_marca {};
        unir2d::Imagen *                                 imagen_marca_retrato {};
        std::array <unir2d::Imagen *, cuentaHabilidades> imagen_marca_habilidad {};

        bool                 visible_ {};
        ActorPersonaje * personaje_mostrado {};


        explicit PresenciaActuante (ActorTablero * actor_tablero, LadoTablero lado_tablero);
        ~PresenciaActuante ();

        void prepara ();
        void libera ();

        void preparaPaneles ();
        void preparaPersonaje ();
        void preparaHabilidades ();
        void preparaPuntosAccion ();
        void preparaBarraVida ();
        void preparaMarcas ();

        int  indiceBarraVida ();

        static void aserta (bool expresion, const string & mensaje);


        friend class ActorTablero;

    };


}


