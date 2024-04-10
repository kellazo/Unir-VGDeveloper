// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoKBM.h
// versión:  1.1  (7-Abr-2024)


#pragma once


namespace tapete {


    class EstadoJuegoKBM : public EstadoJuegoComun {
    public:

        static constexpr int inicioRonda             = finalPartida + 1;

        static constexpr int inicioTurnoNoElegido    = finalPartida + 2;
        static constexpr int inicioTurnoConfirmacion = finalPartida + 3;

        static constexpr int agotadosPuntosAccion    = finalPartida + 4;
        

        EstadoJuegoKBM (int codigo);

        void transita (const EstadoJuegoKBM & destino);

    private:

        void valida (const EstadoJuegoComun & destino) override;

        const string nombre () const override;

    };


}
