// proyecto: Grupal/Tapete
// archivo:  ModoJuegoBase.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ModoJuegoBase {
    public:

        virtual ~ModoJuegoBase ();  // si no es virtual, excepción

        JuegoMesaBase * juego ();

        float puntosAccionDeDesplaza () const;
        void configuraDesplaza (float puntos_accion_desplaza);

        int ronda  () const;
        int turno  () const;
        int jugada () const;

        LadoTablero ladoEquipoInicial () const;
        LadoTablero ladoEquipoActual  () const;
        
        const std::vector <ActorPersonaje * > & factoresEquipos () const;
        int indiceFactorEquipos () const;

        
        ActorPersonaje * personajeElegido (LadoTablero lado) const;
        ActorPersonaje * atacante () const;
        ModoAccionPersonaje  modoAccion () const;

        const std::vector <Coord> & etapasCamino () const;
        Habilidad * habilidadAccion () const;
        ActorPersonaje * oponente () const;
        const AreaCentradaCeldas & areaCeldas () const;

        // para depurar
        const string textoInforme () const;

    protected:

        ModoJuegoBase (JuegoMesaBase * juego);

        bool cuentaPersonajesIgual ();

        void iniciaRondas ();
        void avanzaJugada ();
        void avanzaTurno  ();
        void avanzaRonda  ();

        void atenuaMusica ();

        LadoTablero eligeEquipoIniciativa ();
        void asignaEquipoInicial (LadoTablero equipo);
        void asignaEquipoActual  (LadoTablero equipo);

        void estableceFactoresEquipos ();
        void indexaFactorEquipos (int valor);

        void establecePersonajeElegido (ActorPersonaje * personaje);
        void anulaEleccionPersonajes ();

        
        LadoTablero eligeAtacanteIniciativa ();
        void estableceAtacante (LadoTablero lado_tablero);
        void suprimeAtacante ();
        void reiniciaAtacante ();
        
        void estableceModoAccionDesplazam ();
        void estableceModoAccionHabilidad (int indice_habilidad);
        void anulaModoAccion ();

        void marcaCeldaInicio ();
        void desmarcaCeldaInicio ();
        void iniciaCamino ();
        void validaEtapaCamino   (Coord proxima_celda, bool & etapa_valida, int & puntos_en_juego);
        void marcaCeldaCamino    (Coord proxima_celda, bool etapa_valida);
        void desmarcaCeldaCamino (Coord proxima_celda);
        void agregaEtapaCamino   (Coord proxima_celda, int puntos_en_juego);
        void mueveFichaCamino ();
        void anulaCamino ();

        void alea100 ();
        void muestraAleatorio100 ();
        void ocultaAleatorio100 ();

        void muestraAyudaGeneral ();
        void muestraAyudaPersonaje (ActorPersonaje * personaje);
        void muestraAyudaCalculo ();
        void sigueAyudaArriba ();
        void sigueAyudaAbajo ();
        void ocultaAyuda ();

        void validaHabilidadSimple  (bool & uso_valido, int & puntos_en_juego);
        void muestraHabilidadSimple (bool uso_valido, int puntos_en_juego);
        void ocultaHabilidadSimple ();
        void aplicaHabilidadSimple ();

        void estableceOponente (ActorPersonaje * personaje);
        void suprimeOponente ();
        void validaAtaqueOponente  (bool & acceso_valido, int & puntos_en_juego);
        void muestraAtaqueOponente (bool acceso_valido, int puntos_en_juego);
        void ocultaAtaqueOponente ();
        void atacaOponente ();

        void estableceAreaHabilidad (Coord celda);
        void anulaAreaHabilidad ();
        void validaAtaqueArea  (bool & acceso_valido, int & puntos_en_juego);
        void muestraAtaqueArea (bool acceso_valido, int puntos_en_juego);
        void ocultaAtaqueArea ();
        void atacaArea ();

        void iniciaTiempoCalculo ();
        void terminaTiempoCalculo ();

        void muestraIndicaActuante  (LadoTablero lado);
        void muestraIndicaHabilidad (LadoTablero lado, int indice_habilidad);
        void muestraIndicaFicha     (ActorPersonaje * personaje);    
        void ocultaIndicaciones     ();

        bool rondasDisponibles ();
        bool turnosDisponiblesAmbos ();

        void anulaTotalmente ();

        // para depurar
        void almacenaInforme ( 
                const EstadoJuegoComun & estado,
                const string &           modulo, 
                const string &           metodo );

    private:


        class InformesProceso {
        public:

            void agregaInforme (
                    const EstadoJuegoComun & estado, 
                    const ModoJuegoBase * proceso, 
                    const string &           modulo, 
                    const string &           metodo  );

            const string textoInforme () const;

        private:

            struct Informe {

                std::chrono::system_clock::time_point tiempo;

                string estado;

                int ronda_;
                int turno_;
                int jugada_;

                string modulo;
                string metodo;

            };


            std::array <Informe *, 20> lista_informes {}; 


            void prepara  (Informe * & informe);
            void rota ();

        };


    private:

        inline static bool trazar_avance = true;

        JuegoMesaBase * juego_;

        float puntos_accion_de_desplaza {};

        int ronda_  {};
        int turno_  {};
        int jugada_ {};

        LadoTablero lado_equipo_inicial {};
        LadoTablero lado_equipo_actual {};

        std::vector <ActorPersonaje * > factores_equipos {};
        int                             indice_factor_equipos {};

        ActorPersonaje * personaje_elegido_izqrd {};
        ActorPersonaje * personaje_elegido_derch {};

        ActorPersonaje * atacante_ {};

        ModoAccionPersonaje  modo_accion {};
        std::vector <Coord>  etapas_camino {};
        Habilidad *          habilidad_accion {};        
        ActorPersonaje *     oponente_ {};
        AreaCentradaCeldas   area_celdas {};

        int valor_aleatorio_100 {};

        InformesProceso informes_proceso {};

        inline static Color color_elegido  = Color::Blanco;
        inline static Color color_atacante = Color::Amarillo;
        inline static Color color_objetivo = Color::Marron;


        static int azarosa (unsigned int contador);

        int   puntosEnJuegoCamino   (Coord proxima_celda) const;
        float distanciaCeldas (Coord celda_origen, Coord celda_destino) const;

        void marcaCeldasArea ();
        void desmarcaCeldasArea ();
        void personajesAreaCeldas (std::vector <ActorPersonaje *> & lista_oponentes) const;

        void iniciaPersonajes ();
        void restauraPersonajes ();

        void refrescaBarrasVida ();
        void refrescaPuntosAccion ();

        void asertaHabilidadSimple   (const string & metodo);
        void asertaHabilidadOponente (const string & metodo, ActorPersonaje * oponentable);
        void asertaHabilidadArea     (const string & metodo, bool con_area);
        void aserta (bool condicion, const string & metodo, const string & explicacion) const;


        friend class InformesProceso;

    };


}


