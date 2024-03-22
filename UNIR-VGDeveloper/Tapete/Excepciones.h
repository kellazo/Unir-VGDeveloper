// proyecto: Grupal/Tapete
// archivo:  Excepciones.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class EstadoJuegoComun;
    class ModoJuegoComun;


    enum class LocalizaConfigura {
        Seccion_2_Modo_juego,
        Seccion_3_Tablero_parte_2,
        Seccion_3_Tablero_parte_3,
        Seccion_4_Personajes_parte_1,
        Seccion_4_Personajes_parte_3,
        Seccion_5_Habilidades_parte_2,
        Seccion_6_Estadisticas_parte_2,
        Seccion_7_Grados_efectividad_parte_2,
        Seccion_8_Habilidades_personajes,
        Seccion_9_Estadisticas_habilidades,
        Seccion_10_Estadisticas_personajes,
        Seccion_11_Miscelanea
    };


    class ExcepcionConfigura : public std::logic_error {
    public:

        explicit ExcepcionConfigura (
                const wstring & mensaje, 
                const LocalizaConfigura localiza);
        explicit ExcepcionConfigura (
                const wstring & mensaje, const string & lo_que,
                const LocalizaConfigura localiza);

        const char * what () const noexcept override;

    private:

        string mensaje {};

    };


    class ExcepcionEstado : public std::logic_error {
    public:

        explicit ExcepcionEstado (const EstadoJuegoComun & estado);

        const char * what () const noexcept override;

    private:

        const EstadoJuegoComun & estado;

        string mensaje {};

    };


    class ExcepcionValidacion : public std::logic_error {
    public:

        explicit ExcepcionValidacion (
                const string & modulo, const string & metodo, 
                const string & explicacion);
        explicit ExcepcionValidacion (
                const string & atributo, const string & condicion);

        const char * what () const noexcept override;

    private:

        string atributo {};
        string condicion {};

        string mensaje {};

    };


    class ExcepcionProcesoJuego : public std::logic_error {
    public:

        explicit ExcepcionProcesoJuego (
                const string & clase, const string & metodo,
                const std::exception & excepcion,
                ModoJuegoComun & modo);

        const char * what () const noexcept override;

    private:

        string clase {};
        string metodo {};
        string estado {};
        const std::exception & excepcion {};
        const ModoJuegoComun & modo;

        string mensaje {};


        void creaMensaje ();

    };


}
