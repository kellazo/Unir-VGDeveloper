// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoLibreDoble.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ModoJuegoLibreDoble;
    class JuegoMesa;


    class SucesosJuegoLibreDoble : public SucesosJuegoComun {
    public:

        explicit SucesosJuegoLibreDoble (JuegoMesaBase * juego, ModoJuegoLibreDoble * proceso);

    private:

        ModoJuegoLibreDoble * modo ();          


        void iniciado  () override;

        void personajeSeleccionado (ActorPersonaje * personaje) override;
        void actuanteSeleccionado  (LadoTablero lado) override;
        void habilidadSeleccionada (LadoTablero lado, int indice_habilidad) override;

        void pulsadoEspacio () override;
        void pulsadoEscape  () override;

    };


}

