// proyecto: Grupal/Tapete
// archivo:  EscritorAyuda.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ModoJuegoBase;


    class EscritorAyuda {
    public:


        static void escribeGeneral   (JuegoMesaBase & juego);        
        
        static void escribePersonaje (JuegoMesaBase & juego, ActorPersonaje * personaje);
        
        static void escribeCalculo   (JuegoMesaBase & juego);
        
        static void borra            (JuegoMesaBase & juego);


        static void escribeHabilidad (
                ListadoAyuda & listado, 
                Habilidad *    habilidad);

        static void escribeAtaque    (
                ListadoAyuda                        & listado, 
                const SistemaAtaque                 & sistema, 
                const SistemaAtaque::AtaqueOponente & registro);


        static void escribeCuracion  (
                ListadoAyuda                          & listado, 
                const SistemaAtaque                   & sistema, 
                const SistemaAtaque::CuracionOponente & registro);

        static void escribeEfecto    (
                ListadoAyuda                      & listado, 
                const SistemaAtaque               & sistema, 
                const SistemaAtaque::CambioEfecto & registro);


        static std::vector <wstring> parrafea (int anchura, const wstring & parrafo); 


    };


}