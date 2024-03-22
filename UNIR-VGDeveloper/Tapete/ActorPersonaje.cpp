// proyecto: Grupal/Tapete
// arhivo:   ActorPersonaje.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    ActorPersonaje::ActorPersonaje (
                JuegoMesaBase * juego, 
                LadoTablero     lado_tablero, 
                int             indice_en_equipo,
                const wstring & nombre           ) {
        this->juego_           = juego;
        this->lado_tablero     = lado_tablero;
        this->indice_en_equipo = indice_en_equipo;
        this->nombre_          = nombre;
        this->archivo_retrato  = archivo_retrato;
    }


    ActorPersonaje::~ActorPersonaje () {
        juego_ = nullptr;
    }


    JuegoMesaBase * ActorPersonaje::juego () {
        return juego_;
    }


    LadoTablero ActorPersonaje::ladoTablero () const {
        return lado_tablero;
    }


    int ActorPersonaje::indiceEnEquipo () const {
        return indice_en_equipo;
    }


    const wstring & ActorPersonaje::nombre () const {
        return nombre_;
    }


    const string & ActorPersonaje::archivoRetrato () const {
        return archivo_retrato;
    }


    void ActorPersonaje::ponArchivoRetrato (const string & valor) {
        archivo_retrato = valor;
    }


    const string & ActorPersonaje::archivoFicha () const {
        return archivo_ficha;
    }


    void ActorPersonaje::ponArchivoFicha (const string & valor) {
        archivo_ficha = valor;
    }


    void ActorPersonaje::agregaAtaque (TipoAtaque * tipo_ataque, int valor) {
        valores_tipo_ataque [tipo_ataque] = Multivalor {valor, 0};
    }


    bool ActorPersonaje::apareceAtaque (TipoAtaque * tipo_ataque) const {
        return valores_tipo_ataque.contains (tipo_ataque);
    }


    int ActorPersonaje::valorAtaque (TipoAtaque * tipo_ataque) const {
        Multivalor multi = valores_tipo_ataque.at (tipo_ataque);
        return multi.inicial + multi.cambio;
    }


    void ActorPersonaje::cambiaAtaque (TipoAtaque * tipo_ataque, int valor_cambio) {
        valores_tipo_ataque.at (tipo_ataque).cambio = valor_cambio;
    }


    void ActorPersonaje::restauraAtaque (TipoAtaque * tipo_ataque) {
        valores_tipo_ataque.at (tipo_ataque).cambio = 0;
    }

        
    void ActorPersonaje::agregaDefensa (TipoDefensa * tipo_defensa, int valor) {
        valores_tipo_defensa [tipo_defensa] = Multivalor {valor, 0};
    }


    bool ActorPersonaje::apareceDefensa (TipoDefensa * tipo_defensa) const {
        return valores_tipo_defensa.contains (tipo_defensa);
    }


    int ActorPersonaje::valorDefensa (TipoDefensa * tipo_defensa) const {
        Multivalor multi = valores_tipo_defensa.at (tipo_defensa);
        return multi.inicial + multi.cambio;
    }


    void ActorPersonaje::cambiaDefensa (TipoDefensa * tipo_defensa, int valor_cambio) {
        valores_tipo_defensa.at (tipo_defensa).cambio = valor_cambio;
    }


    void ActorPersonaje::restauraDefensa (TipoDefensa * tipo_defensa) {
        valores_tipo_defensa.at (tipo_defensa).cambio = 0;
    }


    void ActorPersonaje::agregaReduceDano (TipoDano * tipo_dano, int valor) {
        valores_tipo_reduce_dano [tipo_dano] = valor;
    }


    bool ActorPersonaje::apareceReduceDano (TipoDano * tipo_dano) const {
        return valores_tipo_reduce_dano.contains (tipo_dano);
    }


    int ActorPersonaje::valorReduceDano (TipoDano * tipo_dano) const {
        return valores_tipo_reduce_dano.at (tipo_dano);
    }


    const std::vector <Habilidad *> & ActorPersonaje::habilidades () const {
        return lista_habilidades;
    }


    void ActorPersonaje::agregaHabilidad (Habilidad * elemento) {
        lista_habilidades.push_back (elemento);
    }


    int ActorPersonaje::indice () {
        return indice_;
    }


    void ActorPersonaje::ponIndice (int valor) {
        indice_ = valor;
    }


    PresenciaPersonaje & ActorPersonaje::presencia () {
        return presencia_personaje;
    }


    Coord ActorPersonaje::sitioFicha () const {
        return sitio_ficha;
    }


    void ActorPersonaje::ponSitioFicha (Coord valor) {
        sitio_ficha = valor;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////
    // métodos de las Estadísticas de los personajes
    ////////////////////////////////////////////////////////////////////////////////////////////////


    int ActorPersonaje::vitalidad () const { 
        return vitalidad_;
    }


    void ActorPersonaje::ponVitalidad (int valor) { 
        vitalidad_ = valor;
    }


    int ActorPersonaje::puntosAccion () const { 
        return puntos_accion;
    }


    void ActorPersonaje::ponPuntosAccion (int valor) { 
        if (valor < 0) {
            puntos_accion = 0;
            return;
        }
        if (ActorPersonaje::maximoPuntosAccion < valor) {
            puntos_accion = ActorPersonaje::maximoPuntosAccion;
            return;
        }
        puntos_accion = valor;
    }


    int ActorPersonaje::iniciativa () const { 
        return iniciativa_;
    }


    void ActorPersonaje::ponIniciativa (int valor) { 
        iniciativa_ = valor;
    }


    int ActorPersonaje::utilizable () const {
        return utilizable_;
    }


    void ActorPersonaje::ponUtilizable (int valor) {
        utilizable_ = valor;
    }


    //int ActorPersonaje::sistemaAtaque () const { 
    //    return ataque_;
    //}


    //void ActorPersonaje::ponAtaque (int valor) {
    //    ataque_ = valor;
    //}


    //int ActorPersonaje::defensa () const { 
    //    return defensa_;
    //}


    //void ActorPersonaje::ponDefensa (int valor) {
    //    defensa_ = valor;
    //}


    //int ActorPersonaje::reduccionDaño () const { 
    //    return reduccion_dano;
    //}


    //void ActorPersonaje::ponReduccionDano (int valor) {
    //    reduccion_dano = valor;
    //}


    int ActorPersonaje::puntosAccionEnJuego () const { 
        return puntos_accion_en_juego;
    }


    void ActorPersonaje::ponPuntosAccionEnJuego (int valor) { 
        puntos_accion_en_juego = valor;
    }




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    void ActorPersonaje::inicia () {
        ponPosicion (Vector {0, 0});
        //
        presencia_personaje.prepara ();
    }


    void ActorPersonaje::termina () {
        extraeDibujos ();
        lista_habilidades.clear ();
        presencia_personaje.libera ();
    }


    void ActorPersonaje::actualiza (double tiempo_seg) {
        refrescaFicha ();
        controlPersonajePulsacion ();
        controlSobreFicha ();
        controlFichaPulsacion ();
    }


    void ActorPersonaje::refrescaFicha () {
        Vector poscn = RejillaTablero::centroHexagono (sitio_ficha);
        poscn += PresenciaTablero::regionRejilla.posicion ();
        poscn -= PresenciaPersonaje::deslizaFicha;
        presencia_personaje.imagen_ficha->ponPosicion (poscn);
    }


    void ActorPersonaje::controlPersonajePulsacion () {
        bool sclic = unir2d::Raton::pulsando (unir2d::BotonRaton::izquierda);
        if (sclic) {
            if (presencia_personaje.panel_lateral.contiene (unir2d::Raton::posicion ())) {
                juego_->sucesos ()->personajeSeleccionado (this);
            }
        }
    }


    void ActorPersonaje::controlSobreFicha () {
        //
        bool esta_sobre_ahora = false;
        //
        Vector poscn = RejillaTablero::centroHexagono (sitio_ficha);
        poscn += PresenciaTablero::regionRejilla.posicion ();
        if (norma (unir2d::Raton::posicion () - poscn) <= PresenciaPersonaje::radioFicha) {
            esta_sobre_ahora = true;
        }
        if (esta_sobre_ficha) {
            if (esta_sobre_ahora) {
                // nada que hacer
            } else {
                juego_->sucesos ()->saliendoFicha (this); 
                esta_sobre_ficha = false;
            }
        } else {
            if (esta_sobre_ahora) {
                juego_->sucesos ()->entrandoFicha (this);
                esta_sobre_ficha = true;
            } else {
                // nada que hacer
            }
        }
    }


    void ActorPersonaje::controlFichaPulsacion () {
        bool dclic = unir2d::Raton::dobleClic ();
        bool sclic = unir2d::Raton::pulsando (unir2d::BotonRaton::izquierda);
        if (dclic || sclic) {
            Vector poscn = RejillaTablero::centroHexagono (sitio_ficha);
            poscn += PresenciaTablero::regionRejilla.posicion ();
            if (norma (unir2d::Raton::posicion () - poscn) <= PresenciaPersonaje::radioFicha) {
                if (dclic) {
                    juego_->sucesos ()->fichaSeleccionada (this);
                } 
                if (sclic) {
                    juego_->sucesos ()->fichaPulsada (this);
                }
            }
        }
    }


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    void ActorPersonaje::aserta (bool expresion, const string & mensaje) {
        if (expresion) {
            return;
        }
        throw std::logic_error (mensaje);
    }


}