// proyecto: Grupal/Tapete
// archivo:  VistaCaminoCeldas.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class VistaCaminoCeldas {
    public:

        void marcaCeldaInicio (Coord celda);
        void desmarcaCeldaInicio ();
        bool celdaInicioMarcada ();
        void arrancaCamino ();

        void marcaCeldaEtapa (Coord celda, bool etapa_valida, Coord origen_trazo);
        void desmarcaCeldaEtapa ();
        void fijaCeldaEtapa   ();

        void vaciaCamino ();

        // estos métodos son para depurar, no borrar
        //int dianasVisibles ();
        //int dianasFijadas ();

    private:

        static constexpr int grosorTrazado = 5;

        ActorTablero * actor_tablero {};

        inline static unir2d::Textura * textura_mdiana {};
        std::vector <unir2d::Imagen *>  imagenes_mdiana {};
        int                             imagenes_mdiana_fijadas {}; 
        unir2d::Imagen *                imagen_mdiana_cache {};   
        unir2d::Trazos *                trazos {};

        // estas son para control y para depurar
        bool celda_inicio_marcada {}; // se ha marcado la celda de inicio del camino, aún no se ha fijado 
        bool camino_arrancado {};     // se ha fijado la celda de inicio en el camino
        bool celda_etapa_marcada {};  // se ha marcado una celda en el camino, distinta a la de inicio, aún no se ha fijado 
        bool celda_etapa_fijada {};   // se ha fijado una celda en el camino, además de la celda de inicio, no es muy útil


        explicit VistaCaminoCeldas (ActorTablero * actor_tablero);
        ~VistaCaminoCeldas ();

        void prepara ();
        void libera ();

        void agregaMicrodiana    (Coord celda, bool provisional, bool valida);
        void extraeMicrodiana    ();
        void agregaTrazado       (Coord celda, bool provisional, bool valida, Coord origen);
        void cacheaMicrodiana    ();
        void descacheaMicrodiana (Coord celda, bool provisional, bool valida);

        Vector posicionMicrodiana (Coord coord);


        friend class ActorTablero;

    };


}



