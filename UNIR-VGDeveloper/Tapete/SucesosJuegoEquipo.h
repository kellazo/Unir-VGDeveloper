// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoEquipo.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ModoJuegoEquipo;
    class JuegoMesa;


    class SucesosJuegoEquipo : public SucesosJuegoComun {
    public:

        explicit SucesosJuegoEquipo (JuegoMesaBase * juego, ModoJuegoEquipo * proceso);

    private:

        ModoJuegoEquipo * modo ();          


        void iniciado  () override;

        void pulsadoEspacio () override;
        void pulsadoEscape  () override;

    };


}

