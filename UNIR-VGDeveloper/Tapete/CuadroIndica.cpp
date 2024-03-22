// proyecto: Grupal/Tapete
// arhivo:   CuadroIndica.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    CuadroIndica::CuadroIndica (ActorTablero * actor_tablero) {
        this->actor_tablero = actor_tablero;
    }

    CuadroIndica::~CuadroIndica () {
        actor_tablero = nullptr;
    }


    void CuadroIndica::prepara () {
        rectangl_indica = new unir2d::Rectangulo ();
        trazos_indica   = new unir2d::Trazos ();
        texto_indica    = new unir2d::Texto ("DejaVuSans");
        rectangl_indica->ponIndiceZ (1);
        rectangl_indica->ponVisible (false);
        trazos_indica  ->ponIndiceZ (1);
        trazos_indica  ->ponVisible (false);
        texto_indica   ->ponIndiceZ (1);
        texto_indica   ->ponVisible (false);
        //
        actor_tablero->agregaDibujo (rectangl_indica);
        actor_tablero->agregaDibujo (rectangl_indica);
        actor_tablero->agregaDibujo (trazos_indica);
        actor_tablero->agregaDibujo (trazos_indica);
        actor_tablero->agregaDibujo (texto_indica);
        actor_tablero->agregaDibujo (texto_indica);
    }


    void CuadroIndica::libera () {
        delete texto_indica;
        texto_indica = nullptr;
        delete trazos_indica;
        trazos_indica = nullptr;
        delete rectangl_indica;
        rectangl_indica = nullptr;
    }


    void CuadroIndica::indica (Vector poscn, const wstring & cadena) {
        //
        texto_indica->ponTamano (12);
        texto_indica->ponColor (Color::Negro);
        texto_indica->ponCadena (cadena);
        float anchr = texto_indica->anchura ();
        //
        rectangl_indica->ponPosicion (poscn);
        rectangl_indica->ponBase (anchr + 8);
        rectangl_indica->ponAltura (20);
        rectangl_indica->ponColor (colorIndica);
        //
        trazos_indica->ponPosicion (poscn);
        trazos_indica->borraLineas ();
        float sup =  0.0f;
        float inf = 20.0f;
        float der =  0.0f;
        float izq = anchr + 8;
        Vector sup_izq {izq, sup};
        Vector sup_der {der, sup};
        Vector inf_izq {izq, inf};
        Vector inf_der {der, inf};
        trazos_indica->agrega (unir2d::TrazoLinea {sup_izq, sup_der, Color::Negro});
        trazos_indica->agrega (unir2d::TrazoLinea {inf_izq, inf_der, Color::Negro});
        trazos_indica->agrega (unir2d::TrazoLinea {sup_izq, inf_izq, Color::Negro});
        trazos_indica->agrega (unir2d::TrazoLinea {sup_der, inf_der, Color::Negro});
        //
        texto_indica->ponPosicion (poscn + Vector {4, 3});
        //
        rectangl_indica->ponVisible (true);
        trazos_indica  ->ponVisible (true);
        texto_indica   ->ponVisible (true);
    }


    void CuadroIndica::desindica () {
        rectangl_indica->ponVisible (false);
        trazos_indica  ->ponVisible (false);
        texto_indica   ->ponVisible (false);
    }


}