﻿// proyecto: Grupal/Tapete
// arhivo:   JuegoMesaBase.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"
#include "IntroJuegoImagen.h"


namespace tapete {


    string JuegoMesaBase::carpeta_activos_comun  {"../Assets/Art/Sprites/Environment/"};
    
    // intro.....
    Tiempo* cronoIntroLogo;
    Tiempo* cronoPulsaBoton;
    Tiempo* cronoIntroJuegoTexto;
    Tiempo* cronoIntroDialogoSophie;
    Tiempo* cronoIntroDialogoDana;
    unir2d::Sonido* ptr_audio;
    IntroJuegoImagen* ptr_introLogo;
    IntroJuegoImagen* ptr_imagenFondoIntro;
    IntroJuegoImagen* ptr_imagenTextoIntro;
    IntroJuegoImagen* ptr_introPulsaBotonBackground;
    IntroJuegoImagen* ptr_introPulsaBotonTexto;
    IntroJuegoImagen* ptr_introDialogosFondo;
    IntroJuegoImagen* ptr_introDialogosSophie;
    IntroJuegoImagen* ptr_introDialogosDana;
    bool reproduciendoIntroLogo = true;
    bool reproduciendoIntroJuego = false;
    bool reproducienodIntroPulsaBoton = false;
    bool reproduciendoIntroDialogosSophie = false;
    bool reproduciendoIntroDialgosDana = false;
    double duracionIntroLogo = 16;
    double duracionIntroJuegoTexto = 29;
    unir2d::Tecla teclaSaltoIntro = unir2d::Tecla::escape;
    //..........

    JuegoMesaBase::~JuegoMesaBase () {
        validaVacio ();
        delete modo_;
        modo_ = nullptr;
        delete sucesos_;
        sucesos_ = nullptr;
    }


    const string & JuegoMesaBase::carpetaActivos () {
        return carpeta_activos_comun;
    }


    void JuegoMesaBase::regionVentana (Vector & posicion, Vector & tamano) const {
        posicion = Vector {4, 4};
        tamano   = PresenciaTablero::tamanoTablero;
    }


    SucesosJuegoComun * JuegoMesaBase::sucesos () {
        return sucesos_;
    }


   ModoJuegoBase * JuegoMesaBase::modo () {
        return modo_;
    }


    SistemaAtaque & JuegoMesaBase::sistemaAtaque () {
        return ataque_;
    }


    void JuegoMesaBase::configura (SucesosJuegoComun * sucesos, ModoJuegoBase * modo) {
        this->sucesos_ = sucesos;
        this->modo_    = modo;
    }


    ActorTablero * JuegoMesaBase::tablero () {
        return tablero_;
    }


    void JuegoMesaBase::agregaTablero (ActorTablero * valor) {
        tablero_ = valor;
    }


    const std::vector <ActorPersonaje *> & JuegoMesaBase::personajes () const {
        return personajes_;
    }


    const std::vector <ActorPersonaje *> & JuegoMesaBase::personajes (LadoTablero lado) const {
        assert (lado != LadoTablero::nulo);
        if (lado == LadoTablero::Izquierda) {
            return personajes_izqrd;
        } else {
            return personajes_derch;
        }
    }


    void JuegoMesaBase::agregaPersonaje (ActorPersonaje * elemento) {
        if (elemento == nullptr) {
            // existe una validación específica para los personajes, no se hace aquí
            return;
        }
        elemento->ponIndice (static_cast <int> (personajes_.size ()));
        personajes_.push_back (elemento);
        if (elemento->ladoTablero () == LadoTablero::Izquierda) {
            personajes_izqrd.push_back (elemento);
        } else {
            personajes_derch.push_back (elemento);
        }
    }


    const std::vector <Habilidad *> & JuegoMesaBase::habilidades () const {
        return habilidades_;
    }


    void JuegoMesaBase::agregaHabilidad (Habilidad * elemento) {
        if (elemento == nullptr) {
            // existe una validación específica para las habilidades, no se hace aquí
            return;
        }
        elemento->ponIndice (static_cast <int> (habilidades_.size ()));
        habilidades_.push_back (elemento);
    }


    const std::vector <TipoAtaque *> & JuegoMesaBase::ataques () const {
        return ataques_;
    }


    void JuegoMesaBase::agregaAtaque (TipoAtaque * elemento) {
        if (elemento == nullptr) {
            // existe una validación específica para las estadísticas, no se hace aquí
            return;
        }
        elemento->ponIndice (static_cast <int> (ataques_.size ()));
        ataques_.push_back (elemento);
    }


    const std::vector <TipoDefensa *> & JuegoMesaBase::defensas () const {
        return defensas_;
    }


    void JuegoMesaBase::agregaDefensa (TipoDefensa * elemento) {
        if (elemento == nullptr) {
            // existe una validación específica para las estadísticas, no se hace aquí
            return;
        }
        elemento->ponIndice (static_cast <int> (defensas_.size ()));
        defensas_.push_back (elemento);
    }


    const std::vector <TipoDano *> & JuegoMesaBase::danos () const {
        return danos_;
    }


    void JuegoMesaBase::agregaDano (TipoDano * elemento) {
        if (elemento == nullptr) {
            // existe una validación específica para las estadísticas, no se hace aquí
            return;
        }
        elemento->ponIndice (static_cast <int> (danos_.size ()));
        danos_.push_back (elemento);
    }


    ActorMusica* JuegoMesaBase::musica () {
        return musica_;
    }


    void JuegoMesaBase::agregaMusica (ActorMusica * valor) {
        musica_ = valor;

    }
    // INICIO GUILLEM //
    /*
    ActorMusica* JuegoMesaBase::musicaLoop () {
        return musica_loop_;
    }

    
    void JuegoMesaBase::agregaMusicaLoop (ActorMusica * valor) {
        musica_loop_ = valor;
    }*/
    // FIN GUILLEM //

    //const std::vector <TipoCuracion *> & JuegoMesaBase::curaciones () const {
    //    return curaciones_;
    //}


    //void JuegoMesaBase::agregaCuracion  (TipoCuracion * elemento) {
    //    elemento->ponIndice (static_cast <int> (curaciones_.size ()));
    //    curaciones_.push_back (elemento);
    //}


    void JuegoMesaBase::agregaEfectividad (GradoEfectividad * elemento) {
        ataque_.agregaEfectividad (elemento);
    }


    unir2d::Tiempo & JuegoMesaBase::tiempoCalculo () {
        return tiempo_calculo;
    }


    const std::vector <wstring> & JuegoMesaBase::nombresAlumnos () const {
        return nombres_alumnos_;
    }


    void JuegoMesaBase::agregaNombreAlumno (const wstring & nombre_apellidos) {
        nombres_alumnos_.push_back (nombre_apellidos);
    }


    const wstring & JuegoMesaBase::cursoAcademico () const {
        return curso_academico_;
    }


    void JuegoMesaBase::indicaCursoAcademico (const wstring & curso_academico) {
        curso_academico_ = curso_academico;
    }


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    void JuegoMesaBase::inicia () {

        valida_.Construccion ();
        preparaTablero ();
        valida_.Tablero ();
        preparaPersonajes ();
        valida_.Personajes ();
        preparaHabilidades ();
        valida_.Habilidades ();
        preparaTiposEstadisticas ();
        valida_.TiposEstadisticas ();
        agregaHabilidadesPersonajes ();
        valida_.HabilidadesPersonajes ();
        agregaEstadisticasHabilidades ();
        valida_.EstadisticasHabilidades ();
        agregaEstadisticasPersonajes ();
        valida_.EstadisticasPersonajes ();
        preparaSistemaAtaque ();
        valida_.SistemaAtaque ();
        configuraJuego ();
        valida_.ConfiguraJuego ();
        //
        // 
        // 
        // intro 1ero logo, continua en posactualiza()
        //carga rápida **** ptr_introLogo = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/IntroGameBackground.png" };
        ptr_introLogo = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/logoIntro001a144.png", 0, -10, 0, 9, 16, false, "../Assets/Audio/Themes/audioIntroLogo.wav"};
        agregaActor(ptr_introLogo);
        cronoIntroLogo = new Tiempo{};
        cronoIntroLogo->inicia();
        
    }


    void JuegoMesaBase::termina () {
        
        // clean crono intro
        delete cronoIntroLogo;

        //
        sucesos_->terminado ();
        sucesos_ = nullptr;
        //
        for (const TipoAtaque * tipo : ataques_) {
            delete tipo;
        }
        ataques_.clear ();
        //
        for (const TipoDefensa * tipo : defensas_) {
            delete tipo;
        }
        defensas_.clear ();
        //
        for (const TipoDano * tipo : danos_) {
            delete tipo;
        }
        danos_.clear ();
        //
        //for (const TipoCuracion * tipo : curaciones_) {
        //    delete tipo;
        //}
        //curaciones_.clear ();
        //
        extraeActores ();
        //
        for (const Habilidad * habil : habilidades_) {
            delete habil;
        }
        habilidades_.clear ();
        //
        delete musica_;
        musica_ = nullptr;
        // INICIO GUILLEM //
        delete musica_loop_;
        musica_loop_ = nullptr;
        // FIN GUILLEM //

        //
        for (const ActorPersonaje * persj : personajes_) {
            delete persj;
        }
        personajes_izqrd.clear ();
        personajes_derch.clear ();
        personajes_.clear ();
        //
        delete tablero_;
        tablero_ = nullptr;
    }


    void JuegoMesaBase::preactualiza (double tiempo_seg) {
    }


    void JuegoMesaBase::posactualiza (double tiempo_seg) {

        if (reproduciendoIntroLogo && ((cronoIntroLogo->segundos() >= duracionIntroLogo
            || unir2d::Teclado::pulsando(teclaSaltoIntro)))) {
            reproduciendoIntroLogo = false;
            reproducienodIntroPulsaBoton = true;
            // limpia logo
            extraeActor(ptr_introLogo);
            delete ptr_introLogo;
            cronoIntroLogo->termina();
            // crea pantalla pulsa botón
            ptr_introPulsaBotonBackground = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/MenuPulsaBoton_Background.png" };
            ptr_introPulsaBotonTexto = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/MenuPulsaBoton_Text.png", 400, 500, 0, 1, 8, true };
            agregaActor(ptr_introPulsaBotonBackground);
            agregaActor(ptr_introPulsaBotonTexto);
            cronoPulsaBoton = new Tiempo{};
            cronoPulsaBoton->inicia();
        }
        
        // intro voz en off
        if (reproducienodIntroPulsaBoton && cronoPulsaBoton->segundos() > 0.5 && unir2d::Teclado::pulsando(Tecla::entrar)) {
            reproducienodIntroPulsaBoton = false;
            reproduciendoIntroJuego = true;

            // limpia
            extraeActor(ptr_introPulsaBotonBackground);
            extraeActor(ptr_introPulsaBotonTexto);
            delete ptr_introPulsaBotonBackground;
            delete ptr_introPulsaBotonTexto;
            cronoPulsaBoton->termina();

            // carga intro juego
            ptr_imagenFondoIntro = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/IntroGameBackground.png" };
            ptr_imagenTextoIntro = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/TextoIntro.png", 0, 480, 1 };
            agregaActor(ptr_imagenFondoIntro);
            agregaActor(ptr_imagenTextoIntro);
            cronoIntroJuegoTexto = new Tiempo{};
            cronoIntroJuegoTexto->inicia();

            // reproduce sonido
            ptr_audio = new unir2d::Sonido{};
            ptr_audio->abre("..\\Assets\\Audio\\Themes\\IntroKidsBikesAndMonsters.wav");
            ptr_audio->suena();
        }


        // inicia diálogos (Sophie)
        if (reproduciendoIntroJuego && (cronoIntroJuegoTexto->segundos() >= duracionIntroJuegoTexto
            || (unir2d::Teclado::pulsando(teclaSaltoIntro) && cronoIntroJuegoTexto->segundos() > 0.5))) {
            reproduciendoIntroJuego = false;
            reproduciendoIntroDialogosSophie = true;

            // limpia intro
            cronoIntroJuegoTexto->termina();
            ptr_audio->para();
            extraeActor(ptr_imagenFondoIntro);
            extraeActor(ptr_imagenTextoIntro);
            delete ptr_imagenFondoIntro;
            delete ptr_imagenTextoIntro;
            delete ptr_audio;

            // carga diálogos
            ptr_introDialogosFondo = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/IntroDialogosFondo.png" };
            ptr_introDialogosSophie = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/IntroDialogSophie.png", 110, 150 };
            agregaActor(ptr_introDialogosFondo);
            agregaActor(ptr_introDialogosSophie);
            agregaActor(musica_);
            cronoIntroDialogoSophie = new Tiempo{};
            cronoIntroDialogoSophie->inicia();
        }

        // Intro diálogo Dana
        if (reproduciendoIntroDialogosSophie && unir2d::Teclado::pulsando(unir2d::Tecla::espacio) 
            && cronoIntroDialogoSophie->segundos() > 0.5) {
            reproduciendoIntroDialogosSophie = false;
            reproduciendoIntroDialgosDana = true;

            // limpia diálogo Sophie
            cronoIntroDialogoSophie->termina();
            extraeActor(ptr_introDialogosSophie);
            delete ptr_introDialogosSophie;

            // carga diálogo Dana
            cronoIntroDialogoDana = new Tiempo{};
            cronoIntroDialogoDana->inicia();
            ptr_introDialogosDana = new IntroJuegoImagen{ "../Assets/Art/Sprites/Environment/IntroDialogDana.png", 1120, 150 };
            agregaActor(ptr_introDialogosDana);
        }

        // inicia juego
        if(reproduciendoIntroDialgosDana && unir2d::Teclado::pulsando(unir2d::Tecla::espacio) 
            && cronoIntroDialogoDana->segundos() > 0.5){
            reproduciendoIntroDialgosDana = false;

            // limpia dialogos
            cronoIntroDialogoDana->termina();
            extraeActor(ptr_introDialogosDana);
            extraeActor(ptr_introDialogosFondo);
            delete ptr_introDialogosDana;
            delete ptr_introDialogosFondo;

            //...continua con juego tras intro
            // agregar los personajes debe ser lo último; de otra forma, no salen las habilidades
            agregaActor(tablero_);
            for (ActorPersonaje* persj : personajes_) {
                agregaActor(persj);
            }
            //agregaActor(musica_);
            // INICIO GUILLEM //
            //agregaActor(musica_loop_);
            // FIN GUILLEM //
            //
            sucesos_->iniciado();
        }

        controlTeclado ();
        controlTiempo  ();
    }


    void JuegoMesaBase::controlTeclado () {
        if (unir2d::Teclado::pulsando (unir2d::Tecla::espacio)) {
            sucesos_->pulsadoEspacio ();
        } else if (unir2d::Teclado::pulsando (unir2d::Tecla::escape)) {
            sucesos_->pulsadoEscape ();
        } else if (unir2d::Teclado::pulsando (unir2d::Tecla::entrar)) {
            sucesos_->pulsadoEnter();
        } else if (unir2d::Teclado::pulsando (unir2d::Tecla::arriba)) {
            sucesos_->pulsadoArriba ();
        } else if (unir2d::Teclado::pulsando (unir2d::Tecla::abajo)) {
            sucesos_->pulsadoAbajo ();
        }
    }


    void JuegoMesaBase::controlTiempo () {
        if (tiempo_calculo.iniciado ()) {
            sucesos_->alarmaCalculo (tiempo_calculo);
        }
    }


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


}
