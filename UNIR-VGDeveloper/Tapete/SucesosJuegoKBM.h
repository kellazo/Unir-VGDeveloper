// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoKBM.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ModoJuegoKBM;
    class JuegoMesa;


    class SucesosJuegoKBM : public SucesosJuegoComun {
    public:

        explicit SucesosJuegoKBM (JuegoMesaBase * juego, ModoJuegoKBM * proceso);

    private:

        ModoJuegoKBM * modo ();          


        void iniciado  () override;

        void pulsadoEspacio () override;
        void pulsadoEscape  () override;

    };


}

