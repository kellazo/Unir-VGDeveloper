// proyecto: Grupal/Tapete
// archivo:  ActorTablero.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class JuegoMesaBase;


    class ActorTablero : public unir2d::ActorBase {
    public:

        static constexpr int columnasGraficoMuros = RejillaTablero::columnas * 3 - 2;
        using GraficoMuros = std::array <const char [columnasGraficoMuros + 1], RejillaTablero::filas>;


        ActorTablero (JuegoMesaBase * juego);
        ~ActorTablero ();

        const string & archivoBaldosas ();
        void ponArchivoBaldosas (const string & archivo);

        const wstring & nombreEquipo  (LadoTablero lado_tablero);
        const string  & ArchivoEscudo (LadoTablero lado_tablero);
        void equipa (LadoTablero lado_tablero, const wstring & nombre, const string & archivo_escudo);

        const std::vector <Coord> & sitiosMuros () const;
        void situaMuros (const GraficoMuros & grafico_muros);
        void validaGraficoMuros ();

        RejillaTablero    & rejilla ();
        PresenciaActuante & presencia (LadoTablero lado);
        CuadroIndica      & indicador ();
        VistaCaminoCeldas & vistaCamino ();
        ListadoAyuda      & listadoAyuda ();

        void indicaPersonaje (LadoTablero lado, const wstring & cadena);
        void indicaHabilidad (LadoTablero lado, int indice_habilidad, const wstring & cadena);
        void desindica ();

        const string & archivoSonidoEstablece ();
        int volumenSonidoEstablece ();
        void asignaSonidoEstablece (const string & archivo_establece, int volumen);
        const string & archivoSonidoDesplaza ();
        int volumenSonidoDesplaza ();
        void asignaSonidoDesplaza  (const string & archivo_desplaza,  int volumen);

        void emiteSonidoEstablece ();
        void emiteSonidoDesplaza ();
        void emiteSonidoHabilidad (Habilidad * habilidad);
        //void emiteMusica ();
        //void bajaMusica (int & volumen);

        template <typename S>
        void escribeMonitor (
                const std::vector <S> & mensaje, 
                const std::vector <S> & indica  );

        void muestraDisplay (int digito_1, int digito_2);
        void borraDisplay ();

    protected:

        void inicia () override;
        void termina () override;

        void actualiza (double tiempo_seg) override;

    private:

        JuegoMesaBase * juego {}; 

        string archivo_baldosas;

        wstring nombre_equipo_izqrd {}; 
        string  archivo_escudo_izqrd {};
        wstring nombre_equipo_derch {}; 
        string  archivo_escudo_derch {};

        const GraficoMuros * grafico_muros;
        std::vector <Coord>  sitios_muros {};

        PresenciaTablero     presencia_tablero        {this};
        RejillaTablero       rejilla_tablero          {this};
        PresenciaHabilidades presencia_habilidades    {this};
        PresenciaActuante    presencia_actuante_izqrd {this, LadoTablero::Izquierda};
        PresenciaActuante    presencia_actuante_derch {this, LadoTablero::Derecha};
        CuadroIndica         cuadro_indica            {this};
        VistaCaminoCeldas    vista_camino_celdas      {this};
        ListadoAyuda         listado_ayuda            {this};

        string archivo_sonido_establece {};
        int    volumen_sonido_establece {};
        string archivo_sonido_desplaza {};
        int    volumen_sonido_desplaza {};

        struct SobreRetrato {
            bool        esta {false};  
            LadoTablero lado {};
        };
        SobreRetrato sobre_retrato {};
        struct SobreHabilidad {
            bool        esta {false};  
            LadoTablero lado {};
            int         indice {};
        };
        SobreHabilidad sobre_habilidad {};
        struct SobreCelda {
            bool  esta {false};
            Coord celda {};
        };
        SobreCelda sobre_celda {};

        void calculaSitiosMuros ();

        void controlSobreRetrato ();
        void controlSobreHabilidad ();
        void controlRetratoPulsacion ();
        void controlHabilidadPulsacion ();
        void controlSobreCelda ();
        void controlCeldaPulsacion ();
        void controlAyudaPulsacion ();

        static void aserta (bool expresion, const string & mensaje);


        friend class PresenciaTablero;
        friend class RejillaTablero;
        friend class PresenciaHabilidades;
        friend class PresenciaActuante;
        friend class ListadoAyuda;

    };


    template <typename S>
    void ActorTablero::escribeMonitor (
            const std::vector <S> & mensaje, 
            const std::vector <S> & indica  ) {
        aserta (mensaje.size () + indica.size () <= PresenciaTablero::lineas_texto_monitor,
                "excesivo número de línea a escribir");
        //
        for (int indc = 0; indc < PresenciaTablero::lineas_texto_monitor; ++ indc) {
            presencia_tablero.texto_monitor [indc]->ponCadena ("");
        }
        for (int indc = 0; indc < mensaje.size (); ++ indc) {
            presencia_tablero.texto_monitor [indc]->ponCadena (mensaje [indc]);
            presencia_tablero.texto_monitor [indc]->ponColor  (PresenciaTablero::fosforo_verde);
        }
        int indc_text = PresenciaTablero::lineas_texto_monitor - static_cast <int> (indica.size ());            
        for (int indc = 0; indc < indica.size (); ++ indc) {
            presencia_tablero.texto_monitor [indc_text]->ponCadena (indica [indc]);
            presencia_tablero.texto_monitor [indc_text]->ponColor  (Color::Amarillo);
            indc_text ++;
        }
    }


}
