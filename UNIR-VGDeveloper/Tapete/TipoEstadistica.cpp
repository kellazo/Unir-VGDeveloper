// proyecto: Grupal/Tapete
// arhivo:   Habilidad.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    TipoEstadistica::TipoEstadistica (Categoria categoria, const wstring & nombre) {
        categoria_ = categoria;
        nombre_    = nombre;
    }


    TipoEstadistica::Categoria TipoEstadistica::categoria () const {
        return categoria_;
    }


    const wstring & TipoEstadistica::nombre () const {
        return nombre_;
    }


    int TipoEstadistica::indice () {
        return indice_;
    }


    void TipoEstadistica::ponIndice (int valor) {
        indice_ = valor;
    }


    TipoAtaqueDefensa::TipoAtaqueDefensa (Categoria categoria, const wstring & nombre) :
        TipoEstadistica {categoria, nombre} {
    }


    TipoAtaque::TipoAtaque (const wstring & nombre) :
        TipoAtaqueDefensa {Categoria::sistemaAtaque, nombre} {
    }


    TipoDefensa::TipoDefensa (const wstring & nombre) :
        TipoAtaqueDefensa {Categoria::defensa, nombre} {
    }


    TipoDanoCuracion::TipoDanoCuracion (Categoria categoria, const wstring & nombre) :
        TipoEstadistica {categoria, nombre} {
    }


    TipoDano::TipoDano (const wstring & nombre) :
        TipoDanoCuracion {Categoria::dano, nombre} {
    }


    //TipoCuracion::TipoCuracion (const wstring & nombre) :
    //    TipoDanoCuracion {Categoria::curacion, nombre} {
    //}


}