// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoEquipo.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class EstadoJuegoEquipo : public EstadoJuegoComun {
    public:

        static constexpr int inicioRonda = finalPartida + 1;

        static constexpr int inicioTurno = finalPartida + 2;
        

        EstadoJuegoEquipo (int codigo);

        void transita (const EstadoJuegoEquipo & destino);

    private:

        void valida (const EstadoJuegoComun & destino) override;

        const string nombre () const override;

    };


}
