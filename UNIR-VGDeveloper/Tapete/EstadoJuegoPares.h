// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoPares.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class EstadoJuegoPares : public EstadoJuegoComun {
    public:

        static constexpr int inicioRonda             = finalPartida + 1;

        static constexpr int inicioTurnoNoElegidos   = finalPartida + 2;
        static constexpr int inicioTurnoElegidoUno   = finalPartida + 3;
        static constexpr int inicioTurnoConfirmacion = finalPartida + 4;

        static constexpr int agotadosPuntosAccion    = finalPartida + 5;
        static constexpr int finalTurno              = finalPartida + 6;
        

        EstadoJuegoPares (int codigo);

        void transita (const EstadoJuegoPares & destino);

    private:

        void valida (const EstadoJuegoComun & destino) override;

        const string nombre () const override;

    };


}


