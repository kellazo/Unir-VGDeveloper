// proyecto: Grupal/Tapete
// arhivo:   JuegoMesaBase.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    string JuegoMesaBase::carpeta_activos_comun  {"../Tapete/"};


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


    ActorMusica * JuegoMesaBase::musica () {
        return musica_;
    }


    void JuegoMesaBase::agregaMusica (ActorMusica * valor) {
        musica_ = valor;
    }


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
        // agregar los personajes debe ser lo último; de otra forma, no salen las habilidades
        agregaActor (tablero_);
        for (ActorPersonaje * persj : personajes_) {
            agregaActor (persj);
        }
        agregaActor (musica_);
        //
        sucesos_->iniciado ();
    }


    void JuegoMesaBase::termina () {
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
        controlTeclado ();
        controlTiempo  ();
    }


    void JuegoMesaBase::controlTeclado () {
        if (unir2d::Teclado::pulsando (unir2d::Tecla::espacio)) {
            sucesos_->pulsadoEspacio ();
        } else if (unir2d::Teclado::pulsando (unir2d::Tecla::escape)) {
            sucesos_->pulsadoEscape ();
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
