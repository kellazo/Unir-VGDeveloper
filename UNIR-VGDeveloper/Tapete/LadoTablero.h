// proyecto: Grupal/Tapete
// archivo:  LadoTablero.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    enum class LadoTablero {
        Izquierda,
        Derecha,
        nulo
    };


    inline LadoTablero opuesto (LadoTablero lado) {
        assert (lado != LadoTablero::nulo);
        if (lado == LadoTablero::Izquierda) {
            return LadoTablero::Derecha;
        } else {
            return LadoTablero::Izquierda;
        }
    }

}


