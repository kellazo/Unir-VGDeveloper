// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoLibreDoble.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class EstadoJuegoLibreDoble : public EstadoJuegoComun {
    public:

        static constexpr int inicioRonda             = finalPartidaDerrota + 1;

        static constexpr int inicioTurnoNoElegido    = finalPartidaDerrota + 2;
        static constexpr int inicioTurnoConfirmacion = finalPartidaDerrota + 3;

        static constexpr int agotadosPuntosAccion    = finalPartidaDerrota + 4;
        

        EstadoJuegoLibreDoble (int codigo);

        void transita (const EstadoJuegoLibreDoble & destino);

    private:

        void valida (const EstadoJuegoComun & destino) override;

        const string nombre () const override;

    };


}
