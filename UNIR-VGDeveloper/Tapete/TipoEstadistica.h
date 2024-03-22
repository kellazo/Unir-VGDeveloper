// proyecto: Grupal/Tapete
// archivo:  Habilidad.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {



    class TipoEstadistica {
    public:

        enum class Categoria {
            sistemaAtaque,
            defensa,
            dano,
            curacion
        };

        Categoria categoria () const;
        const wstring & nombre () const;

        int indice ();
        void ponIndice (int valor);

    protected:

        explicit TipoEstadistica (Categoria categoria, const wstring & nombre);

    private:

        Categoria categoria_;
        wstring nombre_;

        int indice_ {};

    };


    class TipoAtaqueDefensa : public TipoEstadistica {
    protected:

        explicit TipoAtaqueDefensa (Categoria categoria, const wstring & nombre);

    };


    class TipoAtaque : public TipoAtaqueDefensa {
    public:

        explicit TipoAtaque (const wstring & nombre);

    };


    class TipoDefensa : public TipoAtaqueDefensa {
    public:

        explicit TipoDefensa (const wstring & nombre);

    };


    class TipoDanoCuracion : public TipoEstadistica {
    protected:

        explicit TipoDanoCuracion (Categoria categoria, const wstring & nombre);

    };


    class TipoDano : public TipoDanoCuracion {
    public:

        explicit TipoDano (const wstring & nombre);

    };


    //class TipoCuracion : public TipoDanoCuracion {
    //public:

    //    explicit TipoCuracion (const wstring & nombre);

    //};


}
        

