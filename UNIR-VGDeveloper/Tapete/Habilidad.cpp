// proyecto: Grupal/Tapete
// arhivo:   Habilidad.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    Habilidad::Habilidad (
            const wstring & nombre, 
            EnfoqueHabilidad  tipo_accion, 
            AccesoHabilidad  tipo_acceso, 
            Antagonista antagonista) {
        this->nombre_      = nombre;
        this->tipo_accion  = tipo_accion;
        this->tipo_acceso  = tipo_acceso;
        this->antagonista_ = antagonista;
    }


    Habilidad::~Habilidad () {
        tipo_ataque  = nullptr; 
        tipo_defensa = nullptr;
        tipo_dano    = nullptr;
    }


    const wstring & Habilidad::nombre () const {
        return nombre_;
    }


    EnfoqueHabilidad Habilidad::tipoEnfoque () const {
        return tipo_accion;
    }


    AccesoHabilidad Habilidad::tipoAcceso () const {
        return tipo_acceso;
    }


    Antagonista Habilidad::antagonista () const {
        return antagonista_;
    }


    const wstring & Habilidad::descripcion () const {
        return descripcion_;
    }


    void Habilidad::ponDescripcion (const wstring & valor) {
        descripcion_ = valor;
    }


    const string & Habilidad::archivoImagen () const {
        return archivo_imagen;
    }


    const string & Habilidad::archivoFondoImagen () const {
        return archivo_fondo_imagen;
    }


    void Habilidad::ponArchivosImagenes (const string & archivo_imagen, const string & archivo_fondo) {
        this->archivo_imagen       = archivo_imagen;
        this->archivo_fondo_imagen = archivo_fondo;
    }


    const string & Habilidad::archivoSonido () const {
        return archivo_sonido;
    }


    void Habilidad::ponArchivoSonido (const string & archivo) {
        this->archivo_sonido = archivo;
    }


    int Habilidad::coste () const {
        return coste_;
    }


    void Habilidad::ponCoste (int valor) {
        coste_ = valor;
    }


    int Habilidad::alcance () const {
        return alcance_;
    }


    void Habilidad::ponAlcance (int valor) {
        alcance_ = valor;
    }


    int Habilidad::radioAlcance () const {
        return radio_;
    }


    void Habilidad::ponRadioAlcance (int valor) {
        radio_ = valor;
    }


    TipoAtaque * Habilidad::tipoAtaque () const {
        return tipo_ataque;
    } 


    void Habilidad::asignaAtaque (TipoAtaque * tipo_ataque) {
        this->tipo_ataque = tipo_ataque;
    }


    TipoDefensa * Habilidad::tipoDefensa () const {
        return tipo_defensa;
    }


    void Habilidad::asignaDefensa (TipoDefensa * tipo_defensa) {
        this->tipo_defensa = tipo_defensa;
    }


    TipoDano * Habilidad::tipoDano () const {
        return tipo_dano;
    }


    int Habilidad::valorDano () const {
        return valor_dano;
    }


    void Habilidad::asignaDano (TipoDano * tipo_dano, int valor_dano) {
        this->valor_dano = valor_dano;
        this->tipo_dano  = tipo_dano;
    }


    int Habilidad::valorCuracion () const {
        return valor_curacion;
    }


    void Habilidad::asignaCuracion (int valor) {
        valor_curacion = valor;
    }


    const Habilidad::EfectosAtaque & Habilidad::efectosAtaque () const {
        return efectos_ataque;
    } 

 
    void Habilidad::agregaEfectoAtaque (TipoAtaque * tipo_ataque, int valor) {
        efectos_ataque.push_back (std::pair (tipo_ataque, valor));
    }


    const Habilidad::EfectosDefensa & Habilidad::efectosDefensa () const {
        return efectos_defensa;
    } 


    void Habilidad::agregaEfectoDefensa  (TipoDefensa * tipo_defensa, int valor) {
        efectos_defensa.push_back (std::pair (tipo_defensa, valor));
    }


    int Habilidad::indice () const {
        return indice_;
    }


    void Habilidad::ponIndice (int valor) {
        indice_ = valor;
    }


}

