// proyecto: Grupal/Tapete
// arhivo:   JuegoMesaBase.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class JuegoMesaBase : public unir2d::JuegoBase {
    public:

        static const string & carpetaActivos ();

        ActorTablero * tablero ();

        const std::vector <ActorPersonaje *> & personajes ()  const;
        const std::vector <ActorPersonaje *> & personajes (LadoTablero lado)  const;
        const std::vector <Habilidad *>      & habilidades () const;
        const std::vector <TipoAtaque *>     & ataques () const;
        const std::vector <TipoDefensa *>    & defensas () const;
        const std::vector <TipoDano *>       & danos () const;

        ActorMusica * musica ();

        const std::vector <wstring> & nombresAlumnos () const;
        const wstring & cursoAcademico () const; 

        SucesosJuegoComun * sucesos ();        
        ModoJuegoBase *     modo ();  
        SistemaAtaque     & sistemaAtaque ();

        unir2d::Tiempo & tiempoCalculo ();

    protected:

        static string carpeta_activos_comun;

        ~JuegoMesaBase ();

        void agregaTablero     (ActorTablero * valor);
        void agregaPersonaje   (ActorPersonaje * elemento);
        void agregaHabilidad   (Habilidad * elemento);
        void agregaAtaque      (TipoAtaque * elemento);
        void agregaDefensa     (TipoDefensa * elemento);
        void agregaDano        (TipoDano * elemento);
//        void agregaCuracion    (TipoCuracion * elemento);
        void agregaEfectividad (GradoEfectividad * elemento);
        void agregaMusica      (ActorMusica * valor);

        void configura (SucesosJuegoComun * sucesos, ModoJuegoBase * modo);

        void agregaNombreAlumno   (const wstring & nombre_apellidos);
        void indicaCursoAcademico (const wstring & curso_academico);

        virtual void preparaTablero                () = 0;
        virtual void preparaPersonajes             () = 0;
        virtual void preparaHabilidades            () = 0;
        virtual void preparaTiposEstadisticas      () = 0;
        virtual void agregaHabilidadesPersonajes   () = 0;
        virtual void agregaEstadisticasPersonajes  () = 0;
        virtual void agregaEstadisticasHabilidades () = 0;
        virtual void preparaSistemaAtaque          () = 0;
        virtual void configuraJuego                () = 0;

        void inicia  () override;
        void termina () override;

        void preactualiza (double tiempo_seg) override;
        void posactualiza (double tiempo_seg) override;

    private:

        ActorTablero *                 tablero_ {};
        std::vector <ActorPersonaje *> personajes_ {};
        std::vector <ActorPersonaje *> personajes_izqrd {};
        std::vector <ActorPersonaje *> personajes_derch {};
        std::vector <Habilidad *>      habilidades_ {};
        std::vector <TipoAtaque *>     ataques_ {};
        std::vector <TipoDefensa *>    defensas_ {};
        std::vector <TipoDano *>       danos_ {};
//        std::vector <TipoCuracion *>   curaciones_ {};
        ActorMusica *                  musica_ {};

        std::vector <wstring> nombres_alumnos_ {};
        wstring               curso_academico_ {};

        ValidacionJuego     valida_ {this};
        SucesosJuegoComun * sucesos_ {};
        ModoJuegoBase *     modo_ {};
        SistemaAtaque       ataque_  {this};

        unir2d::Tiempo tiempo_calculo {};


        void regionVentana (Vector & posicion, Vector & tamano) const override;

        void controlTeclado ();
        void controlTiempo ();

    };


}



