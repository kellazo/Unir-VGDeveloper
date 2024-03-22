// proyecto: Grupal/Tapete
// arhivo:   ActorTablero.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {
    

    ListadoAyuda::ListadoAyuda (ActorTablero * actor_tablero) {
        this->actor_tablero = actor_tablero;
    }


    ListadoAyuda::~ListadoAyuda () {
        actor_tablero = nullptr;
    }


    void ListadoAyuda::prepara () {
        papel = new unir2d::Rectangulo (region.ancho (), region.alto ());
        papel->ponIndiceZ (1);
        papel->ponPosicion (region.posicion ());
        //
        Vector poscn_izqrd = region.posicion () + Vector {3, 6};
        Vector poscn_derch = region.posicion () + Vector {region.tamano ().x () - 6 * 2, 6};
        for (int indc = 0; indc < cuentaBoquetes; ++ indc) {
            boquetes_izqrd [indc] = new unir2d::Circulo (4);
            boquetes_izqrd [indc]->ponIndiceZ (1);
            boquetes_izqrd [indc]->ponPosicion (poscn_izqrd);
            boquetes_izqrd [indc]->ponColor (Color::Gris);
            boquetes_derch [indc] = new unir2d::Circulo (4);
            boquetes_derch [indc]->ponIndiceZ (1);
            boquetes_derch [indc]->ponPosicion (poscn_derch);
            boquetes_derch [indc]->ponColor (Color::Gris);
            poscn_izqrd += Vector {0, 20};
            poscn_derch += Vector {0, 20};
        }
        //
        trazos_izqrd = new unir2d::Trazos ();
        trazos_izqrd->ponIndiceZ (1);
        trazos_derch = new unir2d::Trazos ();
        trazos_derch->ponIndiceZ (1);
        Vector punto_izqrd = region.posicion () + Vector {17, 4};
        Vector punto_derch = region.posicion () + Vector {region.tamano ().x (), 0} + Vector {-17, 4};
        for (int indc = 0; indc < cuentaTrazos; ++ indc) {
            unir2d::TrazoLinea linea_izqrd {punto_izqrd, punto_izqrd + Vector {0, 4}, Color::Gris};
            unir2d::TrazoLinea linea_derch {punto_derch, punto_derch + Vector {0, 4}, Color::Gris};
            trazos_izqrd->agrega (linea_izqrd);
            trazos_derch->agrega (linea_derch);
            punto_izqrd += Vector {0, 10};
            punto_derch += Vector {0, 10};
        }
        //
        constexpr int margen = 10;
        sombra_derch = new unir2d::Rectangulo (margen, region.alto ());
        sombra_derch->ponIndiceZ (1);
        sombra_derch->ponPosicion (Vector {region.posicion ().x () + region.ancho (), region.posicion ().y () + margen});
        sombra_derch->ponColor (Color {0, 0, 0, 80});
        sombra_abajo = new unir2d::Rectangulo (region.ancho () - margen, margen);
        sombra_abajo->ponIndiceZ (1);
        sombra_abajo->ponPosicion (Vector {region.posicion ().x () + margen, region.posicion ().y () + region.alto ()});
        sombra_abajo->ponColor (Color {0, 0, 0, 80});
        //
        actor_tablero->agregaDibujo (papel);
        for (int indc = 0; indc < cuentaBoquetes; ++ indc) {
            actor_tablero->agregaDibujo (boquetes_izqrd [indc]);
            actor_tablero->agregaDibujo (boquetes_derch [indc]);
        }
        actor_tablero->agregaDibujo (trazos_izqrd);
        actor_tablero->agregaDibujo (trazos_derch);
        actor_tablero->agregaDibujo (sombra_derch);
        actor_tablero->agregaDibujo (sombra_abajo);
        //
        Vector poscn = region.posicion () + Vector {25, 9};
        for (int indc = 0; indc < lineasTextoListado; ++ indc) {
            texto_claro  [indc] = new unir2d::Texto ("DejaVuSansMono");
            texto_claro  [indc]->ponIndiceZ (1);
            texto_claro  [indc]->ponTamano (12);
            texto_claro  [indc]->ponColor (Color::GrisOscuro);
            texto_oscuro [indc] = new unir2d::Texto ("DejaVuSansMono-Bold");
            texto_oscuro [indc]->ponIndiceZ (1);
            texto_oscuro [indc]->ponTamano (12);
            texto_oscuro [indc]->ponColor (Color::GrisOscuro);
            texto_claro  [indc]->ponPosicion (poscn);
            texto_oscuro [indc]->ponPosicion (poscn);
            actor_tablero->agregaDibujo (texto_claro  [indc]);
            actor_tablero->agregaDibujo (texto_oscuro [indc]);
            poscn += Vector {0, 14};
        }
        //
        sigue_arriba = new unir2d::Texto ("DejaVuSansMono-Bold");
        sigue_arriba->ponIndiceZ (1);
        sigue_arriba->ponTamano (12);
        sigue_arriba->ponColor (Color::GrisOscuro);
        sigue_arriba->ponCadena ("(sigue...)");
        poscn = region.posicion () + Vector {tamano.x () - 92, 9};
        sigue_arriba->ponPosicion (poscn);
        sigue_abajo  = new unir2d::Texto ("DejaVuSansMono-Bold");
        sigue_abajo ->ponIndiceZ (1);
        sigue_abajo ->ponTamano (12);
        sigue_abajo ->ponColor (Color::GrisOscuro);
        sigue_abajo ->ponCadena ("(sigue...)");
        poscn += (lineasTextoListado - 1) * Vector {0, 14};
        sigue_abajo ->ponPosicion (poscn);
        actor_tablero->agregaDibujo (sigue_arriba);
        actor_tablero->agregaDibujo (sigue_abajo);
        //
        oculta ();
    }


    void ListadoAyuda::libera () {
        delete sigue_arriba;
        delete sigue_abajo;
        sigue_arriba = nullptr;
        sigue_abajo  = nullptr;
        for (int indc = 0; indc < lineasTextoListado; ++ indc) {
            delete texto_claro  [indc];
            delete texto_oscuro [indc];
            texto_claro  [indc] = nullptr;
            texto_oscuro [indc] = nullptr;
        }
        delete sombra_abajo;
        delete sombra_derch;
        sombra_abajo = nullptr;
        sombra_derch = nullptr;
        delete trazos_derch;
        delete trazos_izqrd;
        trazos_derch = nullptr;
        trazos_izqrd = nullptr;
        for (int indc = 0; indc < cuentaBoquetes; ++ indc) {
            delete boquetes_izqrd [indc];
            delete boquetes_derch [indc];
            boquetes_izqrd [indc] = nullptr;
            boquetes_derch [indc] = nullptr;
        }
        delete papel;
        papel = nullptr;
    }


    void ListadoAyuda::enNegrita () {
        negrita_actual = true;
    }


    void ListadoAyuda::enClaro () {
        negrita_actual = false;
    }


    void ListadoAyuda::escribe (const wchar_t * texto) {
        negrita_linea.push_back (negrita_actual);
        cadena_linea .push_back (wstring {texto});
        linea_actual ++;
    }


    void ListadoAyuda::escribe (const wstring & texto) {
        negrita_linea.push_back (negrita_actual);
        cadena_linea .push_back (texto);
        linea_actual ++;
    }


    void ListadoAyuda::saltaLinea () {
        negrita_linea.push_back (negrita_actual);
        cadena_linea .push_back (wstring {});
        linea_actual ++;
    }


    void ListadoAyuda::borra () {
        negrita_linea.clear ();
        cadena_linea .clear ();
    }


    int ListadoAyuda::linea () {
        return linea_actual + 1;
    }


    void ListadoAyuda::deslizaArriba () {
        if (! visible) {
            return;
        }
        if (bajante <= 0) {
            return;
        }
        bajante --;
        escribeLineas ();
        escribeSigue ();
    }


    void ListadoAyuda::deslizaAbajo () {
        if (! visible) {
            return;
        }
        if (cadena_linea.size () - bajante <= lineasTextoListado) {
            return;
        }
        bajante ++;
        escribeLineas ();
        escribeSigue ();
    }


    void ListadoAyuda::muestra () {
        papel->ponVisible (true);
        for (int indc = 0; indc < cuentaBoquetes; ++ indc) {
            boquetes_izqrd [indc]->ponVisible (true);
            boquetes_derch [indc]->ponVisible (true);
        }
        trazos_izqrd->ponVisible (true);
        trazos_derch->ponVisible (true);
        sombra_derch->ponVisible (true);
        sombra_abajo->ponVisible (true);
        bajante = 0;
        escribeLineas ();
        escribeSigue ();
        //
        visible = true;
    }


    void ListadoAyuda::oculta () {
        papel->ponVisible (false);
        for (int indc = 0; indc < cuentaBoquetes; ++ indc) {
            boquetes_izqrd [indc]->ponVisible (false);
            boquetes_derch [indc]->ponVisible (false);
        }
        trazos_izqrd->ponVisible (false);
        trazos_derch->ponVisible (false);
        sombra_derch->ponVisible (false);
        sombra_abajo->ponVisible (false);
        for (int indc = 0; indc < lineasTextoListado; ++ indc) {
            texto_claro  [indc]->ponVisible (false);
            texto_oscuro [indc]->ponVisible (false);
        }
        sigue_arriba->ponVisible (false);
        sigue_abajo ->ponVisible (false);
        //
        visible = false;
    }


    void ListadoAyuda::escribeLineas () {
        for (int indc = 0; indc < lineasTextoListado; ++ indc) {
            texto_claro  [indc]->ponVisible (false);
            texto_oscuro [indc]->ponVisible (false);
            if (indc < static_cast <int> (cadena_linea.size ()) - bajante) {
                if (negrita_linea [indc]) {
                    texto_oscuro [indc]->ponCadena  (cadena_linea [indc + bajante]);
                    texto_oscuro [indc]->ponVisible (true);
                } else {
                    texto_claro  [indc]->ponCadena  (cadena_linea [indc + bajante]);
                    texto_claro  [indc]->ponVisible (true);
                }
            }
        }
    }


    void ListadoAyuda::escribeSigue () {
        sigue_arriba->ponVisible (bajante > 0);
        sigue_abajo ->ponVisible (cadena_linea.size () - bajante > lineasTextoListado);
    }

}