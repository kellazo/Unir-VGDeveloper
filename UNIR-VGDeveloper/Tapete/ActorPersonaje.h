// proyecto: Grupal/Tapete
// archivo:  ActorPersonaje.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class JuegoMesaBase;


    enum class ModoAccionPersonaje {
        Nulo,
        Desplazamiento,
        Habilidad
    };


    class ActorPersonaje : public unir2d::ActorBase {
    public:

        explicit ActorPersonaje (
                JuegoMesaBase * juego, 
                LadoTablero     lado_tablero, 
                int             indice_en_equipo,
                const wstring & nombre           );
        ~ActorPersonaje ();

        JuegoMesaBase * juego (); 
        LadoTablero ladoTablero () const;
        int indiceEnEquipo () const;
        const wstring & nombre () const;

        const string & archivoRetrato () const;
        void ponArchivoRetrato (const string & valor);
        const string & archivoFicha () const;
        void ponArchivoFicha (const string & valor);

        // 
        // Los valores de los tipos defensa y de sistemaAtaque de los personajes son dobles, es decir, hay 
        // un valor base y un valor de cambio, siendo el valor que se usa la suma de los dos. 
        // Inicialmete (al principio de la partida) se asigna el valor base y el valor de cambio es 
        // cero. El valor de cambio es asignado al usar determinadas habilidades.
        // Cuando se inicia un nuevo ronda, los valores de cambio deben pasar automáticamente a ser 
        // cero. 
        // 

        bool apareceAtaque  (TipoAtaque * tipo_ataque) const; 
        int  valorAtaque    (TipoAtaque * tipo_ataque) const; 
        void agregaAtaque   (TipoAtaque * tipo_ataque, int valor_base);
        void cambiaAtaque   (TipoAtaque * tipo_ataque, int valor_cambio);
        void restauraAtaque (TipoAtaque * tipo_ataque);

        bool apareceDefensa  (TipoDefensa * tipo_ataque) const; 
        int  valorDefensa    (TipoDefensa * tipo_ataque) const; 
        void agregaDefensa   (TipoDefensa * tipo_defensa, int valor_base);
        void cambiaDefensa   (TipoDefensa * tipo_defensa, int valor_cambio);
        void restauraDefensa (TipoDefensa * tipo_defensa);

        bool apareceReduceDano (TipoDano * tipo_dano) const; 
        int  valorReduceDano   (TipoDano * tipo_dano) const; 
        void agregaReduceDano  (TipoDano * tipo_dano, int valor);

        static constexpr int maximoHabilidades  = 10;
        const std::vector <Habilidad *> & habilidades () const;
        void agregaHabilidad (Habilidad * elemento);

        int indice ();
        void ponIndice (int valor);

        PresenciaPersonaje & presencia ();

        Coord sitioFicha () const;
        void ponSitioFicha (Coord valor);

        //------------------------------------------------------------------------------------------
        // Estadísticas de los personajes
        //------------------------------------------------------------------------------------------

        static constexpr int maximaVitalidad = 100;
        int vitalidad () const;
        void ponVitalidad (int valor);

        static constexpr int maximoPuntosAccion = 20;
        int puntosAccion () const;
        void ponPuntosAccion (int valor);

        int iniciativa () const;
        void ponIniciativa (int valor);

        // Utilizable. No se usa, se deja para más adelante
        int utilizable () const;
        void ponUtilizable (int valor);

        int puntosAccionEnJuego () const;
        void ponPuntosAccionEnJuego (int valor);

    protected:

        void inicia () override;
        void termina () override;

        void actualiza (double tiempo_seg) override;

    private:

        JuegoMesaBase * juego_ {}; 

        LadoTablero lado_tablero {};
        int         indice_en_equipo {};
        wstring     nombre_;

        string archivo_retrato {};
        string archivo_ficha {};

        struct Multivalor {
            int inicial;
            int cambio;
        };
        std::map <TipoAtaque *,  Multivalor> valores_tipo_ataque {};
        std::map <TipoDefensa *, Multivalor> valores_tipo_defensa {};
        std::map <TipoDano *,    int>        valores_tipo_reduce_dano {};

        std::vector <Habilidad *> lista_habilidades {};

        int indice_;

        Coord sitio_ficha {};
       
        int puntos_accion {};
        int vitalidad_ {};
        int iniciativa_ {};
        int utilizable_ {};
        int ataque_ {};
        int defensa_ {};
        int reduccion_dano {};

        int puntos_accion_en_juego {};

        PresenciaPersonaje presencia_personaje {this};

        bool esta_sobre_ficha {false};


        void refrescaFicha ();
        void controlPersonajePulsacion ();
        void controlSobreFicha ();
        void controlFichaPulsacion ();

        static void aserta (bool expresion, const string & mensaje);


        friend class CalculoCaminos;
        friend class PresenciaPersonaje;

    };


}
