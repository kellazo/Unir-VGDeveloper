// proyecto: Grupal/Tapete
// archivo:  Habilidad.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    enum class EnfoqueHabilidad {
        si_mismo,
        personaje,
        area,
    };

    enum class AccesoHabilidad {
        ninguno,
        directo,
        indirecto,
    };

    enum class Antagonista {
        oponente,
        aliado,
        si_mismo
    };


    class Habilidad {
    public:

        explicit Habilidad (
                const wstring  & nombre, 
                EnfoqueHabilidad tipo_accion, 
                AccesoHabilidad  tipo_acceso, 
                Antagonista      antagonista);
        ~Habilidad ();

        const wstring &  nombre () const;
        EnfoqueHabilidad tipoEnfoque () const;
        AccesoHabilidad  tipoAcceso () const;
        Antagonista      antagonista () const;

        const wstring & descripcion () const;
        void ponDescripcion (const wstring & valor);

        const string & archivoImagen () const;
        const string & archivoFondoImagen () const;
        void ponArchivosImagenes (const string & archivo_imagen, const string & archivo_fondo);

        const string & archivoSonido () const;
        void ponArchivoSonido (const string & archivo);

        int  coste () const;
        void ponCoste (int valor);
        int  alcance () const;
        void ponAlcance (int valor);
        int  radioAlcance () const;
        void ponRadioAlcance (int valor);

        TipoAtaque * tipoAtaque () const; 
        void asignaAtaque (TipoAtaque * tipo_ataque);

        TipoDefensa * tipoDefensa () const;
        void asignaDefensa (TipoDefensa * tipo_defensa);

        TipoDano * tipoDano () const;
        int        valorDano () const;
        void asignaDano (TipoDano * tipo_dano, int valor_dano);

        int  valorCuracion () const;
        void asignaCuracion (int valor);

        using EfectosAtaque = std::vector <std::pair <TipoAtaque *, int>>;
        const EfectosAtaque & efectosAtaque () const; 
        void agregaEfectoAtaque (TipoAtaque * tipo_ataque, int valor);

        using EfectosDefensa = std::vector <std::pair <TipoDefensa *, int>>;
        const EfectosDefensa & efectosDefensa () const; 
        void agregaEfectoDefensa (TipoDefensa * tipo_defensa, int valor);

        int indice () const;
        void ponIndice (int valor);

    private:

        wstring nombre_ {};
        EnfoqueHabilidad tipo_accion {};
        AccesoHabilidad  tipo_acceso {};
        Antagonista      antagonista_ {};

        int coste_ {};
        int alcance_ {};
        int radio_ {};

        wstring descripcion_ {};
        string archivo_imagen {};
        string archivo_fondo_imagen {};
        string archivo_sonido {};

        TipoAtaque *   tipo_ataque {}; 
        TipoDefensa *  tipo_defensa {};
        TipoDano *     tipo_dano {};
        int            valor_dano {};
        int            valor_curacion {};
        EfectosAtaque  efectos_ataque {}; 
        EfectosDefensa efectos_defensa {}; 

        //int fila_selecn_imagen {};
        //int coln_selecn_imagen {};

        int indice_ {};

    };


}