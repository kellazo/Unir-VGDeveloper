// proyecto: Grupal/Tapete
// archivo:  CalculoCaminos.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class JuegoMesaBase;


    // Es admisible que la celda central:
    //      esté fuera del tablero, 
    //      esté en los muros o 
    //      esté ocupada por una ficha
    // El resto de las celdas aparecen cuando:
    //      no estan fuera del tablero y 
    //      no están en los muros
    using AreaCentradaCeldas = std::vector <std::vector <Coord>>;


    class CalculoCaminos {
    public:

        static bool celdaEnTablero (Coord celda);
        static bool celdaEnMuro    (JuegoMesaBase * juego, Coord celda);
        static bool celdaOcupada   (JuegoMesaBase * juego, Coord celda);

        static bool etapaValidaCamino (JuegoMesaBase * juego, Coord celda_destino_etapa);
        static bool segmentoValido    (JuegoMesaBase * juego, Coord celda_origen, Coord celda_destino);

        static void areaCeldas (
                JuegoMesaBase *      juego, 
                Coord                celda_central, 
                int                  radio_area, 
                AreaCentradaCeldas & area_celdas    );

    private:

        struct EcuacionRecta {
            // a·x+b·y+c = 0
            float a;
            float b;
            float c;
            // d = √(a²+b²)    raiz cuadrada
            float d;
        };

        static void calculoDireccion (
                Coord celda_origen_etapa, Coord celda_destino_etapa,
                int & direccion_exacta, int & direccion_cuadrante   );

        static bool etapaValidaCaminoExacto (
                JuegoMesaBase * juego, 
                Coord celda_origen_etapa, Coord celda_destino_etapa, 
                int direccion_exacta                                );
        static void celdaProximaCaminoExacto (
                Coord celda_sale, int direccion_exacta,
                Coord & celda_llega                    );
        static bool etapaValidaCaminoCuadrante (
                JuegoMesaBase * juego, 
                Coord celda_origen_etapa, Coord celda_destino_etapa, 
                int direccion_cuadrante                             );
        static void celdaProximaCaminoCuadrante (
                Coord celda_sale, int direccion_cuadrante,
                const EcuacionRecta & recta_etapa, Coord & celda_llega);

        static void calculaRecta (
                Vector vector_director, Vector punto_recta,
                CalculoCaminos::EcuacionRecta & recta      );
        static float distancia (const EcuacionRecta & recta, Vector punto);

        static void agregaLadoArea (
                JuegoMesaBase * juego, 
                Coord celda_central, int radio_lado, 
                Coord origen_lado, Coord director_lado, 
                AreaCentradaCeldas & area_celdas       );

        static void aserta (bool expresion, const string & mensaje);

    };


}

