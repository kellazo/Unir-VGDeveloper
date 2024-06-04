// proyecto: Grupal/Tapete
// arhivo:   EstadoJuegoKBM.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class EstadoJuegoKBM : public EstadoJuegoComun {
    public:

        static constexpr int inicioRonda = finalPartidaDerrota + 1;

        static constexpr int inicioTurno = finalPartidaDerrota + 2;
        

        EstadoJuegoKBM (int codigo);

        void transita (const EstadoJuegoKBM & destino);

    private:

        void valida (const EstadoJuegoComun & destino) override;

        const string nombre () const override;

    };


}
