// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoLibreDoble.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class JuegoMesa;


    class ModoJuegoLibreDoble : public ModoJuegoComun {
    public:

        explicit ModoJuegoLibreDoble (JuegoMesaBase * juego);

        // EstadoJuegoComun es polimórfica
        EstadoJuegoLibreDoble & estado ();

        void entraPartida ();

        void entraTurnoEleccion ();
        void eligePersonaje (ActorPersonaje * personaje);
        void revierteInicioTurno ();

        void entraInicioJugada ();

        void mueveFicha ();
        void asumeHabilidad ();

        void ignoraPersonajeAgotado ();

    private:

        EstadoJuegoLibreDoble estado_;
        EstadoJuegoLibreDoble estado_previo_;


        void asume (
                bool & inicio_jugada, 
                bool & ataca_agotado, 
                bool & inicio_turno, 
                bool & inicio_ronda, 
                bool & final_partida);

        void escribeEstado () override;

        const string nombreModulo () override;
        void validaAtributos () override;
//        void excepciona (const string & metodo, const std::exception & excepcion);

    };


}
