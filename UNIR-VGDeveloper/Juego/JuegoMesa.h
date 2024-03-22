// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace juego {


    class JuegoMesa : public JuegoMesaBase {
    public:

        JuegoMesa ();

    private:

        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Segunda parte

        En esta sección se configuran los personajes del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen a los personajes. 

        El nombre de cada variable es similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de personajes diseñados para el juego.

        *******************************************************************************************/
        ActorPersonaje * Aristo {};
        ActorPersonaje * Harja {};
        ActorPersonaje * Hunter {};
        ActorPersonaje * Thief {};
        ActorPersonaje * Miner {};
        ActorPersonaje * Male {};
        ActorPersonaje * Patrek {};
        ActorPersonaje * Pirate {};
        /*******************************************************************************************
        /******************************************************************************************/
 

        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Primera parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen a las habilidades. 

        El nombre de cada variable es similar al de la habilidad correspondiente. Las variables son 
        de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de habilidades diseñadas para el juego.

        *******************************************************************************************/
        Habilidad * ataqueEspadaNormal {}; 
        Habilidad * ataqueArco {};
        Habilidad * ataqueEspadaPoderoso {};
        Habilidad * defensaFerrea {};
        Habilidad * curacionSimple {};
        Habilidad * curacionGrupo {};
        Habilidad * proyectilMagico {};
        Habilidad * bolaFuego {};
        /*******************************************************************************************
        /******************************************************************************************/


        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Primera parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego, que son usados
        por los personajes y las habilidades del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. 

        El nombre de cada variable identifica el tipo correspondiente. Las variables son de 
        tipo puntero. El nombre de la clase (por ejemplo 'TipoAtaque' para los ataques) 
        establece si es un tipo de ataque, de defensa o de daño.

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de tipos de ataque, defensa y daño diseñados para el juego.

        *******************************************************************************************/
        TipoAtaque *  ataqueCuerpoACuerpo {};
        TipoAtaque *  ataqueADistancia {};
        TipoAtaque *  ataqueMagico {};
        TipoDefensa * defensaCuerpoACuerpo {};
        TipoDefensa * defensaADistancia {};
        TipoDefensa * defensaMagica {};
        TipoDano *    danoFisico {};
        TipoDano *    danoMagico {};
        /*******************************************************************************************
        /******************************************************************************************/


        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Primera parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. 
        
        Consiste en declarar las variables que están destinadas a almacenar las instancias que 
        definen los grados de efectividad de los ataques. 

        Cada variable tiene un nombre similar al nombre del grados de efectividad correspondiente. 
        Las variables son de tipo puntero. 

        Programación
        ------------

        Se debe sustituir la lista de declaraciones de variables por una lista similar obtenida de
        la lista de grados de efectividad diseñados para el juego.

        *******************************************************************************************/
        GradoEfectividad * fallo {};
        GradoEfectividad * roce {};
        GradoEfectividad * impacto {};
        GradoEfectividad * critico {};
        /*******************************************************************************************
        /******************************************************************************************/

    private:

        static string carpeta_activos_juego;
        static string carpeta_retratos_juego;
        static string carpeta_habilids_juego;
        static string carpeta_sonidos_juego;


        const std::wstring tituloVentana () const override;

        void preparaTablero () override;
        void preparaPersonajes () override;
        void preparaHabilidades () override;
        void preparaTiposEstadisticas () override;
        void agregaHabilidadesPersonajes () override;
        void agregaEstadisticasHabilidades () override;
        void agregaEstadisticasPersonajes () override;
        void preparaSistemaAtaque () override;
        void configuraJuego () override;
        void termina () override;

    };


}


