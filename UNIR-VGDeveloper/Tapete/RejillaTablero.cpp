// proyecto: Grupal/Tapete
// arhivo:   RejillaTablero.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {
    

    Vector RejillaTablero::centroHexagono (Coord centro) {
        float x =   1.5f * centro.coln () - 0.5f;
        float y = seno60 * centro.fila ();
        x *= ladoHexagono;
        y *= ladoHexagono;
        return Vector {x, y};
    }


    Vector RejillaTablero::verticeHexagono (Coord centro, int posicion) {
        float x =    1.5f * centro.coln ();
        float y = seno60 * centro.fila ();
        if (posicion == 1 || posicion == 5) {
            x -= 1.0f;
        }
        if (posicion == 3) {
            x += 0.5f;
        }
        if (posicion == 6) {
            x -= 1.5f;
        }
        if (posicion == 1 || posicion == 2) {
            y -= seno60;
        }
        if (posicion == 4 || posicion == 5) {
            y += seno60;
        }
        x *= ladoHexagono;
        y *= ladoHexagono;
        return Vector {x, y};
    }


    RejillaTablero::RejillaTablero (ActorTablero * actor_tablero) {
        this->actor_tablero = actor_tablero;
    }


    RejillaTablero::~RejillaTablero () {
        this->actor_tablero = nullptr;
    }


    void RejillaTablero::localizaCelda (Vector punto, Coord & localizada) {
        // este es difícil de entender, ver 'centroHexagono'
        //
        float x = punto.x ();
        float y = punto.y ();
        if (x < 0.0f || y < 0.0f) {
            localizada = Coord {0, 0};
            return;
        }
        //
        x /= RejillaTablero::ladoHexagono;
        x -= 0.5f;
        //
        int coln_1;
        if (x < 0.0f) {
            coln_1 = 1;
        } else {
            coln_1 = static_cast <int> (x / 1.5f);
            coln_1 += 1;
        }
        if (coln_1 > RejillaTablero::columnas) {
            localizada = Coord {0, 0};
            return;
        }
        //
        int coln_2;
        if (x < 0.0f) {
            coln_2 = 0;
        } else {
            float m = std::fmodf (x, 1.5f);
            if (m <= 1.0f) {
                coln_2 = 0;
            } else {
                if (coln_1 + 1 > RejillaTablero::columnas) {
                    coln_2 = 0;
                } else {
                    coln_2 = coln_1 + 1;
                }
            }
        }
        //
        y /= RejillaTablero::ladoHexagono;
        y /= RejillaTablero::seno60;
        int fila_1;
        int fila_2;
        fila_1 = static_cast <int> (y);
        fila_2 = fila_1;
        if (fila_1 % 2 == 0) {
            fila_1 ++;
        } else {
            fila_2 ++;
        }
        if (fila_1 > RejillaTablero::filas) {
            localizada = Coord {0, 0};
            return;
        }
        if (fila_2 > RejillaTablero::filas - 1) {
            fila_2 = 0;
        }
        //
        // fila_1: es impar
        // fila_2: si no es 0, es par
        // coln_1: es par o impar 
        // coln_2: si no es 0, es coln_1 + 1
        //
        if (fila_2 == 0 && coln_2 == 0) {
            if (coln_1 % 2 == 0) {
                localizada = Coord {0, 0};
            } else {
                localizada = Coord {fila_1, coln_1};
            }
            return;
        }
        //
        if (fila_2 == 0) {
            if (coln_1 % 2 == 0) {
                localizada = Coord {fila_1, coln_2};
            } else {
                localizada = Coord {fila_1, coln_1};
            }
            return;
        }
        //
        if (coln_2 == 0) {
            if (coln_1 % 2 == 0) {
                localizada = Coord {fila_2, coln_1};
            } else {
                localizada = Coord {fila_1, coln_1};
            }
            return;
        }
        //
        Coord coord_1 {0, 0};
        Coord coord_2 {0, 0};
        if (coln_1 % 2 == 0) {
            coord_1 = Coord {fila_1, coln_2};
            coord_2 = Coord {fila_2, coln_1};
        } else {
            coord_1 = Coord {fila_1, coln_1};
            coord_2 = Coord {fila_2, coln_2};
        }
        Vector punto_1 = RejillaTablero::centroHexagono (coord_1);
        Vector punto_2 = RejillaTablero::centroHexagono (coord_2);
        float norma_1 = unir2d::norma (punto_1 - punto);
        float norma_2 = unir2d::norma (punto_2 - punto);
        if (norma_1 < norma_2) {
            localizada = coord_1;
        } else {
            localizada = coord_2;
        }
    }


    void RejillaTablero::prepara () {
        //------------------------------------------------------------
        trazos_rejilla = new unir2d::Trazos {};
        trazos_rejilla->ponPosicion (PresenciaTablero::regionRejilla.posicion ());
        Color color {0x80, 0xC0, 0x80};
        bool fila_par = true;
        for (int fila = 0; fila <= filas + 2; ++ fila) {
            bool coln_par = true;
            for (int coln = 0; coln <= columnas + 1; ++ coln) {
                if (fila_par == coln_par) {
                    Coord coord {fila, coln};
                    Vector punto1 = verticeHexagono (coord, 1);
                    Vector punto2 = verticeHexagono (coord, 2);
                    Vector punto3 = verticeHexagono (coord, 3);
                    Vector punto4 = verticeHexagono (coord, 4);
                    if (1 <= fila && fila <= filas + 2 &&
                        1 <= coln && coln <= columnas    ) {
                        trazos_rejilla->agrega (unir2d::TrazoLinea {punto1, punto2, color});
                    }
                    if (1 <= fila && fila <= filas + 1 && 
                        0 <= coln && coln <= columnas    ) {
                        trazos_rejilla->agrega (unir2d::TrazoLinea {punto2, punto3, color});
                    }
                    if (0 <= fila && fila <= filas && 
                        0 <= coln && coln <= columnas) {
                        trazos_rejilla->agrega (unir2d::TrazoLinea {punto3, punto4, color});
                    }
                }
                if (coln_par) {
                    coln_par = false;
                } else {
                    coln_par = true;
                }
            }
            if (fila_par) {
                fila_par = false;
            } else {
                fila_par = true;
            }
        }
        //------------------------------------------------------------
        trazos_marcaje = new unir2d::Trazos {};
        trazos_marcaje->ponPosicion (PresenciaTablero::regionRejilla.posicion ());
        cambio_trazos_marcaje = false;
        //trazaHexagono (Coord {4, 4});
        //------------------------------------------------------------
        //
        actor_tablero->agregaDibujo (trazos_rejilla);
        actor_tablero->agregaDibujo (trazos_marcaje);
    }


    void RejillaTablero::libera () {
        delete trazos_marcaje;
        delete trazos_rejilla;
        trazos_marcaje = nullptr;
        trazos_rejilla = nullptr;
    }


    void RejillaTablero::marcaCelda (Coord posicion, Color color) {
        marcaCelda (posicion, color, false);
    }


    void RejillaTablero::marcaCelda (Coord posicion, Color color, bool grueso) {
        std::vector <MarcajeCelda>::iterator iter = buscaMarcaCelda (posicion);
        if (iter != marcaje_celdas.end ()) {
            iter->color  = color;
            iter->grueso = grueso;
        } else {
            MarcajeCelda marcj {posicion, color, grueso};
            marcaje_celdas.push_back (marcj);
        }
        cambio_trazos_marcaje = true;
    }


    void RejillaTablero::desmarcaCelda (Coord posicion) {
        std::vector <MarcajeCelda>::iterator iter = buscaMarcaCelda (posicion);
        if (iter == marcaje_celdas.end ()) {
            return;
        }
        marcaje_celdas.erase (iter);
        cambio_trazos_marcaje = true;
    }


    void RejillaTablero::desmarcaCeldas () {
        marcaje_celdas.clear ();
        cambio_trazos_marcaje = true;
    }


    std::vector <RejillaTablero::MarcajeCelda>::iterator RejillaTablero::buscaMarcaCelda (Coord posicion) {
        for (std::vector <MarcajeCelda>::iterator iter = marcaje_celdas.begin (); iter < marcaje_celdas.end (); ++ iter) {
            if (iter->posicion == posicion) {
                return iter;
            }
        }
        return marcaje_celdas.end (); 
    }


    void RejillaTablero::refrescaMarcaje () {
        if (! cambio_trazos_marcaje) {
            return;
        }
        trazos_marcaje->borraLineas ();
        for (MarcajeCelda marcj : marcaje_celdas) {
            trazaHexagono (marcj);
        }
    }


    void RejillaTablero::trazaHexagono (const MarcajeCelda & marcaje) {
        Vector centro = centroHexagono (marcaje.posicion);
        Vector punto1 = verticeHexagono (marcaje.posicion, 1);
        Vector punto2 = verticeHexagono (marcaje.posicion, 2);
        Vector punto3 = verticeHexagono (marcaje.posicion, 3);
        Vector punto4 = verticeHexagono (marcaje.posicion, 4);
        Vector punto5 = verticeHexagono (marcaje.posicion, 5);
        Vector punto6 = verticeHexagono (marcaje.posicion, 6);
        punto1 += Vector { 1,  1};
        punto2 += Vector {-1,  1};
        punto3 += Vector {-1,  0};
        punto4 += Vector { 0, -1};
        punto5 += Vector { 0, -1};
        punto6 += Vector { 1,  0};
        trazos_marcaje->agrega (unir2d::TrazoLinea {punto1, punto2, marcaje.color});    
        trazos_marcaje->agrega (unir2d::TrazoLinea {punto2, punto3, marcaje.color});
        trazos_marcaje->agrega (unir2d::TrazoLinea {punto3, punto4, marcaje.color});
        trazos_marcaje->agrega (unir2d::TrazoLinea {punto4, punto5, marcaje.color});    
        trazos_marcaje->agrega (unir2d::TrazoLinea {punto5, punto6, marcaje.color});
        trazos_marcaje->agrega (unir2d::TrazoLinea {punto6, punto1, marcaje.color});
        if (marcaje.grueso) {
            punto1 += Vector { 0,  1};
            punto2 += Vector { 0,  1};
            punto3 += Vector {-1,  0};
            punto4 += Vector { 0, -1};
            punto5 += Vector { 0, -1};
            punto6 += Vector { 1,  0};
            trazos_marcaje->agrega (unir2d::TrazoLinea {punto1, punto2, marcaje.color});    
            trazos_marcaje->agrega (unir2d::TrazoLinea {punto2, punto3, marcaje.color});
            trazos_marcaje->agrega (unir2d::TrazoLinea {punto3, punto4, marcaje.color});
            trazos_marcaje->agrega (unir2d::TrazoLinea {punto4, punto5, marcaje.color});    
            trazos_marcaje->agrega (unir2d::TrazoLinea {punto5, punto6, marcaje.color});
            trazos_marcaje->agrega (unir2d::TrazoLinea {punto6, punto1, marcaje.color});
        }
    }


}


