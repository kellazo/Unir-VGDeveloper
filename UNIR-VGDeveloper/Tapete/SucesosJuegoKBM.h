// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoKBM.h
// versión:  1.1  (7-Ene-2024)


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

        void personajeSeleccionado (ActorPersonaje * personaje) override;
        void actuanteSeleccionado  (LadoTablero lado) override;
        void habilidadSeleccionada (LadoTablero lado, int indice_habilidad) override;

        void pulsadoEspacio () override;
        void pulsadoEscape  () override;

    };


}

