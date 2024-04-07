// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoKBM.h
// versión:  1.1  (7-Abr-2024)


#pragma once


namespace tapete {


    class JuegoMesa;


    class ModoJuegoKBM : public ModoJuegoComun {
    public:

        explicit ModoJuegoKBM (JuegoMesaBase * juego);

        // EstadoJuegoComun es polimórfica
        EstadoJuegoKBM & estado ();

        void entraPartida ();

        void entraTurnoEleccion ();
        void eligePersonaje (ActorPersonaje * personaje);
        void revierteInicioTurno ();

        void entraInicioJugada ();

        void mueveFicha ();
        void asumeHabilidad ();

        void ignoraPersonajeAgotado ();

    private:

        EstadoJuegoKBM estado_;
        EstadoJuegoKBM estado_previo_;


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
