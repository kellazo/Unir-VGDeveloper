// proyecto: Grupal/Tapete
// arhivo:   Excepciones.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    static std::string multibyte (const std::wstring & wstr) {
        std::string cadena {};
        std::mbstate_t state {};
        constexpr int max_mb = 5;
        char mb [max_mb];
        for (wchar_t wc : wstr) {
            size_t retval;
            size_t ret = wcrtomb_s (& retval, mb, max_mb, wc, & state);
            if (ret != 0) {
                return cadena;
            }
            for (int i = 0; i < retval; ++ i) {
                cadena.push_back (mb [i]);
            }
        }
        return cadena;
    }
 

    ExcepcionConfigura::ExcepcionConfigura (
                const wstring & mensaje, const LocalizaConfigura localiza) :
        ExcepcionConfigura {mensaje, "", localiza} {
    }


    ExcepcionConfigura:: ExcepcionConfigura (
            const wstring & mensaje, const string & lo_que,
            const LocalizaConfigura localiza) :
        std::logic_error {"ExcepcionConfigura"} {
        this->mensaje.append ("EXCEPCIÓN producida en la configuración el juego:");
        this->mensaje.append ("\n");
        this->mensaje.append ("\n");
        this->mensaje.append ("    ");
        this->mensaje.append (multibyte (mensaje));
        if (lo_que.length () != 0) {
            this->mensaje.append ("\n");
            this->mensaje.append ("        ");
            this->mensaje.append (lo_que);
        }
        this->mensaje.append ("\n");
        this->mensaje.append ("\n");
        this->mensaje.append ("    Ver: ");
        switch (localiza) {
        case LocalizaConfigura::Seccion_2_Modo_juego:
            this->mensaje.append (multibyte (L"Segunda sección - El modo del juego."));
            break;
        case LocalizaConfigura::Seccion_3_Tablero_parte_2:
            this->mensaje.append (multibyte (L"Tercera sección - El tablero - Segunda parte."));
            break;
        case LocalizaConfigura::Seccion_3_Tablero_parte_3:
            this->mensaje.append (multibyte (L"Tercera sección - El tablero - Tercera parte."));
            break;
        case LocalizaConfigura::Seccion_4_Personajes_parte_1:
            this->mensaje.append (multibyte (L"Cuarta sección - Los personajes - Primera parte."));
            break;
        case LocalizaConfigura::Seccion_4_Personajes_parte_3:
            this->mensaje.append (multibyte (L"Cuarta sección - Los personajes - Tercera parte."));
            break;
        case LocalizaConfigura::Seccion_5_Habilidades_parte_2:
            this->mensaje.append (multibyte (L"Quinta sección - Las habilidades - Segunda parte."));
            break;
        case LocalizaConfigura::Seccion_6_Estadisticas_parte_2:
            this->mensaje.append (multibyte (L"Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Segunda parte."));
            break;
        case LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2:
            this->mensaje.append (multibyte (L"Séptima sección - Los grados de efectividad - Segunda parte."));
            break;
        case LocalizaConfigura::Seccion_8_Habilidades_personajes:
            this->mensaje.append (multibyte (L"Octava sección - Las habilidades de los personajes."));
            break;
        case LocalizaConfigura::Seccion_9_Estadisticas_habilidades:
            this->mensaje.append (multibyte (L"Novena sección - Las estadísticas de las habilidades."));
            break;
        case LocalizaConfigura::Seccion_10_Estadisticas_personajes:
            this->mensaje.append (multibyte (L"Décima sección - Los tipos de ataque, defensa y reducción de daño de los personajes."));
            break;
        case LocalizaConfigura::Seccion_11_Miscelanea:
            this->mensaje.append (multibyte (L"Undécima sección - Configuración miscelánea del juego."));
            break;
        }
        this->mensaje.append ("\n");
    }


    const char * ExcepcionConfigura::what () const noexcept {
        return mensaje.c_str ();
    }


    ExcepcionEstado::ExcepcionEstado (const EstadoJuegoComun & estado) :
        std::logic_error {"ExcepcionEstado"},
        estado {estado} {
        mensaje.append ("La operación no se puede realizar en el estado '");
        mensaje.append (estado.nombre ());
        mensaje.append ("'.");
    }


    const char * ExcepcionEstado::what () const noexcept {
        return mensaje.c_str ();
    }


    ExcepcionValidacion::ExcepcionValidacion (
            const string & modulo, const string & metodo, const string & explicacion) :
        std::logic_error {"ExcepcionValidacion"} {
        mensaje.append ("Validación: '");
        mensaje.append (modulo);
        mensaje.append ("::");
        mensaje.append (metodo);
        mensaje.append ("': ");
        mensaje.append (explicacion);
        mensaje.append (".");
    }


    ExcepcionValidacion::ExcepcionValidacion (const string & atributo, const string & condicion) :
        std::logic_error {"ExcepcionValidacion"},
        atributo  {atributo}, 
        condicion {condicion} {
        mensaje.append ("Validación: El atributo '");
        mensaje.append (atributo);
        mensaje.append ("' no cumple la condición '");
        mensaje.append (condicion);
        mensaje.append ("'.");
    }


    const char * ExcepcionValidacion::what () const noexcept {
        return mensaje.c_str ();
    }


    ExcepcionProcesoJuego::ExcepcionProcesoJuego (
            const string & clase, const string & metodo, 
            const std::exception & excepcion,
            ModoJuegoComun & modo) :
        std::logic_error {"ExcepcionProcesoJuego"},
        clase     {clase},
        metodo    {metodo},
        estado    {modo.estado ().nombre ()},
        excepcion {excepcion},
        modo      {modo}    {
        creaMensaje ();
    }


    const char * ExcepcionProcesoJuego::what () const noexcept {
        return mensaje.c_str ();
    }


    void ExcepcionProcesoJuego::creaMensaje () {
        mensaje.append ("EXCEPCIÓN producida durante el juego:\n\n");
        mensaje.append ("Módulo:    ");
        mensaje.append (this->clase);
        mensaje.append ("\n");
        mensaje.append ("Operación: ");
        mensaje.append (this->metodo);
        mensaje.append ("\n");
        mensaje.append ("Estado:    ");
        mensaje.append (this->estado);
        mensaje.append ("\n");
        mensaje.append ("\n    ");
        mensaje.append (excepcion.what ());
        mensaje.append ("\n");
        mensaje.append ("\n");
        //
        if (this->modo.atacante () != nullptr) {
            mensaje.append ("Atacante:      ");
            mensaje.append (multibyte (this->modo.atacante ()->nombre ()));
            mensaje.append ("\n");
        }
        mensaje.append ("Modo acción:   ");
        switch (this->modo.modoAccion ()) {
        case ModoAccionPersonaje::Nulo:
            mensaje.append("nulo");
        case ModoAccionPersonaje::Desplazamiento:
            mensaje.append("desplazamiento");
        case ModoAccionPersonaje::Habilidad:
            mensaje.append("habilidad");
        }
        mensaje.append ("\n");
        //
        mensaje.append ("Etapas camino: ");
        mensaje.append (std::format ("{}", this->modo.etapasCamino ().size ()));
        mensaje.append ("\n");
        if (this->modo.habilidadAccion () != nullptr) {
            mensaje.append ("Habilidad:     ");
            mensaje.append (multibyte (this->modo.habilidadAccion ()->nombre ()));
            mensaje.append ("\n");
        }
        if (this->modo.oponente () != nullptr) {
            mensaje.append ("Oponente:      ");
            mensaje.append (multibyte (this->modo.oponente ()->nombre ()));
            mensaje.append ("\n");
        }
        if (this->modo.areaCeldas ().size () > 0) {
            mensaje.append ("Celdas área:   ");
            mensaje.append (std::format ("{}", this->modo.areaCeldas ().size ()));
            mensaje.append ("\n");
        }
        mensaje.append ("\n");
        //
        mensaje.append ("Últimas operaciones realizadas\n");
        mensaje.append ("--------------------------------------------------");
        mensaje.append ("--------------------------------------------------\n");
        mensaje.append (modo.textoInforme ());
        mensaje.append ("\n");
    }


}