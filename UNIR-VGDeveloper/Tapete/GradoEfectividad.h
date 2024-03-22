// proyecto: Grupal/Tapete
// arhivo:   GradoEfectividad.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class GradoEfectividad {
    public:

        GradoEfectividad (const wstring & nombre);

        void estableceRango (int valor_ataque_inf, int valor_ataque_sup, int porciento_dano);

        const wstring & nombre () const;

        int valorInferiorAtaque () const;
        int valorSuperioAtaque () const;
        int porcentajeDano () const;

    private:

        wstring nombre_ {};

        int valor_ataque_inf {};
        int valor_ataque_sup {};
        int porciento_dano {};

    };


}
