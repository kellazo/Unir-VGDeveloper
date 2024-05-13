// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoPares.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class EstadoJuegoPares : public EstadoJuegoComun {
    public:

        static constexpr int inicioRonda             = finalPartidaDerrota + 1;

        static constexpr int inicioTurnoNoElegidos   = finalPartidaDerrota + 2;
        static constexpr int inicioTurnoElegidoUno   = finalPartidaDerrota + 3;
        static constexpr int inicioTurnoConfirmacion = finalPartidaDerrota + 4;

        static constexpr int agotadosPuntosAccion    = finalPartidaDerrota + 5;
        static constexpr int finalTurno              = finalPartidaDerrota + 6;
        

        EstadoJuegoPares (int codigo);

        void transita (const EstadoJuegoPares & destino);

    private:

        void valida (const EstadoJuegoComun & destino) override;

        const string nombre () const override;

    };


}


