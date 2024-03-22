// proyecto: Grupal/Tapete
// archivo:  PresenciaHabilidades.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class PresenciaHabilidades {
    public:

        std::vector <unir2d::Imagen *> imagenesHabilidades     (ActorPersonaje * personaje);
        std::vector <unir2d::Imagen *> imagenesFondosHabilidad (ActorPersonaje * personaje);

    private:

        ActorTablero * actor_tablero;

        std::vector <unir2d::Textura *>              texturas_habilidades {}; 
        std::vector <unir2d::Textura *>              texturas_fondos {}; 
        std::vector <std::vector <unir2d::Imagen *>> imagenes_habilidades {};
        std::vector <std::vector <unir2d::Imagen *>> imagenes_fondos {};
//        std::vector <unir2d::BuzonSonido *>          buzones_sonidos_habilds {};
        std::vector <unir2d::Sonido *>               sonidos_habilidades {};


        explicit PresenciaHabilidades (ActorTablero * actor_personaje);
        ~PresenciaHabilidades ();

        void prepara ();
        void libera ();

        static void aserta (bool expresion, const string & mensaje);


        friend class ActorTablero;

    };


}
