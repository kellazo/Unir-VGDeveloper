// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoComun.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ModoJuegoComun : public ModoJuegoBase {
    public:

        ~ModoJuegoComun () override;

        EstadoJuegoComun & estado ();
        EstadoJuegoComun & estadoPrevio ();

        void saltaFinalJuego ();

        void anunciaActuante    (LadoTablero lado);
        void desanunciaActuante (LadoTablero lado);
        void anunciaHabilidad    (LadoTablero lado, int indice);
        void desanunciaHabilidad (LadoTablero lado, int indice);
        void anunciaFicha    (ActorPersonaje * personaje);
        void desanunciaFicha (ActorPersonaje * personaje);

        void entraAccionDesplazam ();
        void entraMarcacionCamino ();
        void marcaFichaCamino    (ActorPersonaje * personaje);
        void desmarcaFichaCamino (ActorPersonaje * personaje);
        void marcaCeldaCamino    (Coord celda);
        void desmarcaCeldaCamino (Coord celda);
        void fijaCeldaCamino     (Coord celda);
        void revierteAccionDesplazam ();
//        virtual void mueveFicha ();
        
        void entraAccionHabilidad   (int indice_habilidad);
        
        void evaluaHabilidadSimple   (int indice_habilidad);
        void efectuaHabilidadSimple  ();
//        void calculaHabilidadSimple  (unir2d::Tiempo & tiempo);
        void revierteHabilidadSimple ();

        void evaluaHabilidadOponente   (int indice_habilidad);
        void evaluaHabilidadOponente   (ActorPersonaje * personaje);
        void efectuaHabilidadOponente  ();
        void calculaHabilidadOponente  (unir2d::Tiempo & tiempo);
        void revierteHabilidadOponente ();
        
        void evaluaHabilidadArea   (int indice_habilidad);
        void evaluaHabilidadArea   (Coord celda);
        void efectuaHabilidadArea  ();
        void calculaHabilidadArea  (unir2d::Tiempo & tiempo);
        void revierteHabilidadArea ();
    
//        virtual void asumeHabilidad ();

        void muestraAyuda ();
        void muestraAyuda (ActorPersonaje * personaje);
        void muestraAyudaActuante ();
        void subeAyuda ();
        void bajaAyuda ();
        void ocultaAyuda ();

    protected:

        explicit ModoJuegoComun (JuegoMesaBase * juego, EstadoJuegoComun & estado, EstadoJuegoComun & estado_previo);

        virtual void escribeEstado ();


        // todo lo que sigue es exclusivamente para depurar

        enum SimboloValida {
            NO, SI,
            NINGUNO, UNO, AMBOS,
            NULO, ASIGNADO,
            CERO, VARIOS,
            DESPLAZAM, HABILIDAD,
            SIMPLE, OPONENTE, AREA,
            VACIO, NO_VACIO,
            ignora
        };

        virtual const string nombreModulo ();

        void validaEstado (const std::initializer_list <int> & estados);
        void validaEstado (bool coincide, const std::initializer_list <int> & estados);
        virtual void validaAtributos () = 0;
        virtual void valida (
                SimboloValida simbolo_equipo_inicial,
                SimboloValida simbolo_equipo_actual,
                SimboloValida simbolo_elegidos, 
                SimboloValida simbolo_atacante_, 
                SimboloValida simbolo_agotado, 
                SimboloValida simbolo_vivo,
                SimboloValida simbolo_modo_accion, 
                SimboloValida simbolo_etapas_camino, 
                SimboloValida simbolo_habilidad, 
                SimboloValida simbolo_tipo_accion, 
                SimboloValida simbolo_oponente_, 
                SimboloValida simbolo_area_celdas);
        void informaProceso (const string & metodo);

        static void aserta (bool condicion, const string & atributo, SimboloValida simbolo);
        void excepciona (const string & metodo, const std::exception & excepcion);

    private:

        EstadoJuegoComun & estado_;
        EstadoJuegoComun & estado_previo_;

        static constexpr double segundos_calculo = 1.0;

    };


}



