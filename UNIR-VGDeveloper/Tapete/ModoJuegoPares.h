// proyecto: Grupal/Tapete
// arhivo:   ModoJuegoPares.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class JuegoMesa;


    class ModoJuegoPares : public ModoJuegoComun {
    public:

        explicit ModoJuegoPares (JuegoMesaBase * juego);

        // EstadoJuegoComun es polimórfica
        EstadoJuegoPares & estado ();

        void entraPartida ();

        void entraTurnoEleccion ();
        void eligePrimerPersonaje  (ActorPersonaje * personaje);
        void eligeSegundoPersonaje (ActorPersonaje * personaje);
        void revierteInicioTurno ();

        void entraInicioJugada ();

        void mueveFicha ();
        void asumeHabilidad ();

        void ignoraPersonajeAgotado ();
        void reiniciaTurno ();

    private:

        EstadoJuegoPares estado_;
        EstadoJuegoPares estado_previo_;


        void asume (
                bool & inicio_jugada, 
                bool & ataca_agotado, 
                bool & final_turno   );

        void escribeEstado () override;

        const string nombreModulo () override;
        void validaAtributos () override;
//        void excepciona (const string & metodo, const std::exception & excepcion);

    };


}





