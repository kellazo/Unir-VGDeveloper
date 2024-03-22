// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoPares.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ModoJuegoPares;
    class JuegoMesa;


    class SucesosJuegoPares : public SucesosJuegoComun {
    public:

        explicit SucesosJuegoPares (JuegoMesaBase * juego,ModoJuegoPares * proceso);

    private:

        ModoJuegoPares * modo ();          


        void iniciado  () override;

        void personajeSeleccionado (ActorPersonaje * personaje) override;

        void pulsadoEspacio () override;
        void pulsadoEscape  () override;

    };


}
