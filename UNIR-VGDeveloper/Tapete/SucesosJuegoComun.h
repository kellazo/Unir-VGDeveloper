// proyecto: Grupal/Tapete
// arhivo:   SucesosJuegoComun.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ModoJuegoComun;
    //class JuegoMesa;


    class SucesosJuegoComun {
    public:

        explicit SucesosJuegoComun (JuegoMesaBase * juego, ModoJuegoComun * proceso);
        virtual ~SucesosJuegoComun ();  // es virtual por si acaso

        JuegoMesaBase *  juego ();
        ModoJuegoComun * modo ();          

        virtual void iniciado  () = 0;
        virtual void terminado ();

        virtual void entrandoActuante  (LadoTablero lado)            ;
        virtual void saliendoActuante  (LadoTablero lado)            ;
        virtual void entrandoHabilidad (LadoTablero lado, int indice);
        virtual void saliendoHabilidad (LadoTablero lado, int indice);
        virtual void entrandoFicha     (ActorPersonaje * personaje)  ;
        virtual void saliendoFicha     (ActorPersonaje * personaje)  ;
        virtual void entrandoCelda     (Coord celda)                 ;
        virtual void saliendoCelda     (Coord celda)                 ;

        virtual void personajeSeleccionado (ActorPersonaje * personaje)  ;
        virtual void actuanteSeleccionado  (LadoTablero lado)            ;
        virtual void habilidadSeleccionada (LadoTablero lado, int indice);
        virtual void fichaSeleccionada     (ActorPersonaje * personaje)  ;
        virtual void fichaPulsada          (ActorPersonaje * personaje)  ;
        virtual void celdaSeleccionada     (Coord celda)                 ;
        virtual void celdaPulsada          (Coord celda)                 ;

        virtual void ayudaSeleccionada ();

        virtual void pulsadoEspacio ();
        virtual void pulsadoEscape  ();
        virtual void pulsadoArriba  ();
        virtual void pulsadoAbajo   ();

        virtual void alarmaCalculo (unir2d::Tiempo & tiempo);

    private:

        JuegoMesaBase *  juego_ {};
        ModoJuegoComun * modo_ {};

    };


}


