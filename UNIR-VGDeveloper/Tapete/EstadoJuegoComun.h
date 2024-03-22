// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoComun.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class EstadoJuegoComun {
    public:

        static constexpr int inicial                        =  0;
        static constexpr int terminal                       =  1;
        
        static constexpr int inicioJugada                   =  2;
        
        static constexpr int preparacionDesplazamiento      =  3;
        static constexpr int marcacionCaminoFicha           =  4;
        
        static constexpr int habilidadSimpleInvalida        =  5;
        static constexpr int habilidadSimpleConfirmacion    =  6;
        static constexpr int habilidadSimpleResultado       =  7;
        
        static constexpr int preparacionHabilidadOponente   =  8;
        static constexpr int oponenteHabilidadInvalido      =  9;
        static constexpr int oponenteHabilidadConfirmacion  = 10;
        static constexpr int oponenteHabilidadCalculando    = 11;
        static constexpr int oponenteHabilidadResultado     = 12;
        
        static constexpr int preparacionHabilidadArea       = 13;
        static constexpr int areaHabilidadInvalida          = 14;
        static constexpr int areaHabilidadConfirmacion      = 15;
        static constexpr int areaHabilidadCalculando        = 16;
        static constexpr int areaHabilidadResultado         = 17;
        
        static constexpr int mostrandoAyuda                 = 18;

        static constexpr int finalPartida                   = 19;


        explicit EstadoJuegoComun ();
        EstadoJuegoComun (int codigo);

        operator int () const;

        void transita (const EstadoJuegoComun & destino);

        void conserva (const EstadoJuegoComun & estado);

        virtual const string nombre () const;

    protected:

        // exclusivamente para depurar
        inline static bool traza_transitos = true;


        void ponCodigo (int valor);

        virtual void valida (const EstadoJuegoComun & destino);
        void aserta (const EstadoJuegoComun & destino, bool condicion) const;

    private:

        int codigo;

        EstadoJuegoComun (const EstadoJuegoComun & ) = delete;
        EstadoJuegoComun (EstadoJuegoComun && )      = delete;
        EstadoJuegoComun & operator = (const EstadoJuegoComun & ) = delete;
        EstadoJuegoComun & operator = (EstadoJuegoComun && )      = delete;
        
    };


}


