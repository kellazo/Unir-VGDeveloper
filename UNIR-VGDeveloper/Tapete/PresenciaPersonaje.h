// proyecto: Grupal/Tapete
// archivo:  PresenciaPersonaje.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ActorPersonaje;


    class PresenciaPersonaje {
    public:

        unir2d::Imagen * imagenRetrato () const;
        unir2d::Imagen * imagenFicha   () const;

        void indicaFicha (const wstring & cadena);

        void oscureceRetrato ();
        void aclaraRetrato ();

        void refrescaBarraVida ();

    private:

        static constexpr int    radioFicha = 15;
        static constexpr Vector deslizaFicha {radioFicha, radioFicha};
        static constexpr int    cuentaBarrasVida = 21;


        ActorPersonaje * actor_personaje;

        Region panel_lateral {};

        unir2d::Textura * textura_retrato {};

        inline static unir2d::Textura * textura_titulos {};
        unir2d::Imagen *                imagen_titulo {};

        unir2d::Rectangulo *            fondo_retrato {};
        unir2d::Imagen *                imagen_retrato_lateral {};
        inline static unir2d::Textura * textura_marco_retrato {};
        unir2d::Imagen *                imagen_marco_retrato {};

        unir2d::Textura *               textura_ficha {};
        unir2d::Imagen *                imagen_ficha {};

        inline static unir2d::Textura * textura_barras_vida {};
        unir2d::Imagen *                imagen_barra_vida {};

        unir2d::Imagen *                imagen_retrato_actuante {};

        //inline static unir2d::Textura * texturas_habilidades {};
        //std::vector <unir2d::Imagen *>  imagenes_habilidades {};

//        inline static unir2d::Textura * textura_ficha_roja {};
//        inline static unir2d::Textura * textura_ficha_azul {};
//        unir2d::Imagen *                imagen_ficha {};


        explicit PresenciaPersonaje (ActorPersonaje * actor_personaje);
        ~PresenciaPersonaje ();

        void prepara ();
        void libera ();

        void preparaPanel (LadoTablero lado_tablero, int indice_grupo);
        void preparaTitulo (
                const std::vector <ActorPersonaje *> & lista_personajes, 
                ActorPersonaje *                       personaje_actual );
        void preparaRetratoLateral ();
        void preparaBarraVida ();
        int  indiceBarraVida ();

        void preparaRetratoActuante ();
        //void preparaHabilidadesActuante (ActorPersonaje * actor_personaje);

        void preparaFicha ();

        static void aserta (bool expresion, const string & mensaje);


        friend class ActorPersonaje;

    };


}

