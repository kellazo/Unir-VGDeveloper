// proyecto: Grupal/Tapete
// arhivo:   PresenciaTablero.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    PresenciaTablero::PresenciaTablero (ActorTablero * actor_tablero) {
        this->actor_tablero = actor_tablero;
    }


    PresenciaTablero::~PresenciaTablero () {
        this->actor_tablero = nullptr;
    }


    void PresenciaTablero::prepara () {
        preparaBaldosas ();
        preparaMuros    (); 
        preparaPaneles  (); 
        preparaMonitor  ();
        preparaDisplay  ();
        preparaAyuda    ();
        preparaSonidos  ();
    }


    void PresenciaTablero::reprepara () {
        actor_tablero->agregaDibujo (malla_muros);
        //
        actor_tablero->agregaDibujo (imagen_panel_vertcl_izqrd);
        actor_tablero->agregaDibujo (imagen_panel_vertcl_derch);
        actor_tablero->agregaDibujo (imagen_panel_abajo_izqrd);
        actor_tablero->agregaDibujo (imagen_panel_abajo_derch);
        actor_tablero->agregaDibujo (imagen_bandera_izqrd);
        actor_tablero->agregaDibujo (imagen_escudo_izqrd);
        actor_tablero->agregaDibujo (imagen_bandera_derch);
        actor_tablero->agregaDibujo (imagen_escudo_derch);
        //
        actor_tablero->agregaDibujo (imagen_fondo_monitor);
        for (int indc = 0; indc < lineas_texto_monitor; ++ indc) {
            actor_tablero->agregaDibujo (texto_monitor [indc]);
        }
    }


    void PresenciaTablero::libera () {
        liberaPaneles  ();
        liberaMuros    ();
        liberaBaldosas ();
        liberaMonitor  ();
        liberaDisplay  ();
        liberaAyuda    ();
        liberaSonidos  ();
     }


    void PresenciaTablero::preparaBaldosas () {
        textura_fondo  = new unir2d::Textura {};
        baldosas_fondo = new unir2d::Baldosas {};
        constexpr int filas_estamp = 4;
        constexpr int colns_estamp = 4;
        textura_fondo->carga (actor_tablero->archivoBaldosas ());
        //textura_fondo->carga (JuegoMesaBase::carpetaActivos () + "estampas_fondo.png");
        baldosas_fondo->asigna (this->textura_fondo);
        baldosas_fondo->defineEstampas (filas_estamp, colns_estamp);
        baldosas_fondo->ponPosicion (Vector {0, 0});
        constexpr int filas_superf = 32;
        constexpr int colns_superf = 56;
        baldosas_fondo->defineSuperficie (filas_superf, colns_superf);
        std::vector <uint32_t> mapeo {};
        mapeo.resize (static_cast <int> (filas_superf * colns_superf));
	    std::random_device semilla {};
        std::mt19937 generador {semilla ()};
	    std::uniform_int_distribution <unsigned int> distrb_filas {0, filas_estamp - 1};
	    std::uniform_int_distribution <unsigned int> distrb_colns {0, colns_estamp - 1};
        for (int f_s = 0; f_s < filas_superf; ++ f_s) {
            for (int c_s = 0; c_s < colns_superf; ++ c_s) {
                int f_e = (int) distrb_filas (generador);
                int c_e = (int) distrb_colns (generador);
                mapeo [f_s * colns_superf + c_s] = f_e * colns_estamp + c_e;
            }
        }
        baldosas_fondo->mapea (mapeo);
        actor_tablero->agregaDibujo (baldosas_fondo);
    }


    void PresenciaTablero::liberaBaldosas () {
        delete baldosas_fondo;
        delete textura_fondo;
        //
        baldosas_fondo = nullptr;
        textura_fondo  = nullptr;
    }


    void PresenciaTablero::preparaMuros () {
        textura_muros  = new unir2d::Textura {};
        textura_muros->carga (JuegoMesaBase::carpetaActivos () + "muro_piedra.png");
        malla_muros = new unir2d::Malla {};
        malla_muros->asigna (textura_muros);
        malla_muros->ponPosicion (PresenciaTablero::regionRejilla.posicion ());
        //----------------------------------------
        IndicesEstampas indcs_estmp;
        calculaEstampasMuros (actor_tablero->sitios_muros, indcs_estmp);
        //
        PuntosHexagonos puntos_textr {};
        punteaTexturaMuros (puntos_textr);
        PuntosHexagonos puntos_rejll {};
        punteaRejillaMuros (actor_tablero->sitios_muros, puntos_rejll);
        estableceMallaMuros (puntos_rejll, indcs_estmp, puntos_textr);
    }


    void PresenciaTablero::liberaMuros () {
        delete malla_muros;
        delete textura_muros;
        //
        malla_muros   = nullptr;
        textura_muros = nullptr;
    }


    void PresenciaTablero::calculaEstampasMuros (
            const std::vector <Coord> & posiciones_rejilla,
            IndicesEstampas           & indices_estampas   ) {
        constexpr int colns_rejilla = RejillaTablero::columnas + 1;  // 50
        constexpr int filas_rejilla = RejillaTablero::filas    + 1;  // 52  
        // tabla_rejilla se indexa:
        //      entre 1 y RejillaTablero::filas y 
        //      entre 1 y RejillaTablero::columnas
        // los índices 0 se ignoran
        std::array <std::array <bool, colns_rejilla>, filas_rejilla> tabla_rejilla {false};
        for (const Coord & coord : posiciones_rejilla) {
            tabla_rejilla [coord.fila ()] [coord.coln ()] = true;
        }
        for (const Coord & coord : posiciones_rejilla) {
            bool las_12 = false;
            bool las__2 = false;
            bool las__4 = false;
            bool las__6 = false;
            bool las__8 = false;
            bool las_10 = false;
            if (coord.fila () - 2 >= 1) {
                las_12 = tabla_rejilla [coord.fila () - 2] [coord.coln ()];
            }
            if (coord.fila () - 1 >= 1                        && 
                coord.coln () + 1 <= RejillaTablero::columnas   ) {
                las__2 = tabla_rejilla [coord.fila () - 1] [coord.coln () + 1];
            }
            if (coord.fila () + 1 <= RejillaTablero::filas    && 
                coord.coln () + 1 <= RejillaTablero::columnas   ) {
                las__4 = tabla_rejilla [coord.fila () + 1] [coord.coln () + 1];
            }
            if (coord.fila () + 2 <= RejillaTablero::filas) {
                las__6 = tabla_rejilla [coord.fila () + 2] [coord.coln ()];
            }
            if (coord.fila () + 1 <= RejillaTablero::filas && 
                coord.coln () - 1 >= 1                       ) {
                las__8 = tabla_rejilla [coord.fila () + 1] [coord.coln () - 1];
            }
            if (coord.fila () - 1 >= 1 &&  
                coord.coln () - 1 >= 1   ) {
                las_10 = tabla_rejilla [coord.fila () - 1] [coord.coln () - 1];
            }
            std::array <int, 6> entrd {};
            entrd [0] = estampaMuros (las_10, las_12, las__2);
            entrd [1] = estampaMuros (las_12, las__2, las__4);
            entrd [2] = estampaMuros (las__2, las__4, las__6);
            entrd [3] = estampaMuros (las__4, las__6, las__8);
            entrd [4] = estampaMuros (las__6, las__8, las_10);
            entrd [5] = estampaMuros (las__8, las_10, las_12);
            indices_estampas.push_back (entrd);    
        }
    }


    int PresenciaTablero::estampaMuros (bool previo, bool adjunto, bool postrer) {
        if (adjunto) {
            return 4;
        }
        if (previo && postrer) {
            return 3;
        }
        if (! previo && postrer) {
            return 2;
        }
        if (previo && ! postrer) {
            return 1;
        }
        if (! previo && ! postrer) {
            return 0;
        }
        return -1;
    }


    void PresenciaTablero::punteaTexturaMuros (PuntosHexagonos & puntos_textura) {
        // índice 1: hay 'estampas_textura_muros' estampas para la textura, colocadas en línea y 
        //      separadas por 42 pixels
        // índice 2: cada estampa está formada por 6 triángulos colocados en un hexágono, empezando  
        //      por arriba y en el sentido de las agujas del reloj
        // índice 3: los triángulos se definen con 3 puntos, incluyendo en centro del hexágono y 2 
        //      vértices consecutivos
        puntos_textura.resize (estampasTexturaMuros);
        for (int indc_celda = 0; indc_celda < estampasTexturaMuros; ++ indc_celda) {
            puntos_textura [indc_celda] [0] = { 
                         Vector {20.0f, 17.0f},    
                         Vector {10.0f,  0.0f},    
                         Vector {30.0f,  0.0f} };
            puntos_textura [indc_celda] [1] = { 
                         Vector {20.0f, 17.0f},    
                         Vector {30.0f,  0.0f},    
                         Vector {40.0f, 17.0f} };
            puntos_textura [indc_celda] [2] = { 
                         Vector {20.0f, 17.0f},    
                         Vector {40.0f, 17.0f},    
                         Vector {30.0f, 34.0f} };
            puntos_textura [indc_celda] [3] = { 
                         Vector {20.0f, 17.0f},    
                         Vector {30.0f, 34.0f},    
                         Vector {10.0f, 34.0f} };
            puntos_textura [indc_celda] [4] = { 
                         Vector {20.0f, 17.0f},    
                         Vector {10.0f, 34.0f},    
                         Vector { 0.0f, 17.0f} };
            puntos_textura [indc_celda] [5] = { 
                         Vector {20.0f, 17.0f},    
                         Vector { 0.0f, 17.0f},    
                         Vector {10.0f,  0.0f} };
            for (int indc_trngl = 0; indc_trngl < 6; ++ indc_trngl) {
                for (int indc_vertc = 0; indc_vertc < 3; ++ indc_vertc) {
                    puntos_textura [indc_celda] [indc_trngl] [indc_vertc] += 
                            ((float) indc_celda) * Vector {42.0f, 0.0f};
                }
            }
        } 
    }


    void PresenciaTablero::punteaRejillaMuros (
            const std::vector <Coord> & posiciones_rejilla, 
            PuntosHexagonos           & puntos_rejilla      ) {
        // índice 1: hay el número de elementos de 'coordenadas_rejilla' de casillas de la rejilla
        // índice 2: cada elemento está formado por 6 triangulos colocados en un hexágono, empezando  
        //      por arriba y en el sentido de las agujas del reloj
        // índice 3: los triángulos se definen con 3 puntos, incluyendo en centro del hexágono y 2 
        //      vértices consecutivos
        puntos_rejilla.resize (posiciones_rejilla.size ());
        std::vector <Vector> punto_hexgn {RejillaTablero::puntosHexagono};
        for (int indc_celda = 0; indc_celda < posiciones_rejilla.size (); ++ indc_celda) {
            for (int indc_hexgn = 0; indc_hexgn < RejillaTablero::puntosHexagono; ++ indc_hexgn) {
                Vector punto;
                if (indc_hexgn == 0) {
                    punto = RejillaTablero::centroHexagono (posiciones_rejilla [indc_celda]);
                } else {
                    punto = RejillaTablero::verticeHexagono (posiciones_rejilla [indc_celda], indc_hexgn);
                }
                punto_hexgn [indc_hexgn] = Vector {punto.x (), punto.y ()};
            }
    //for (int indc_hexgn = 0; indc_hexgn < puntos_hexagono; ++ indc_hexgn) {
    //    std::cout << "(" << punto_hexgn [indc_hexgn].x << "," << punto_hexgn [indc_hexgn].y << ")" << std::endl;
    //}
            puntos_rejilla [indc_celda] [0] = {
                    punto_hexgn [0],
                    punto_hexgn [1],
                    punto_hexgn [2] };
            puntos_rejilla [indc_celda] [1] = {
                    punto_hexgn [0],
                    punto_hexgn [2],
                    punto_hexgn [3] };
            puntos_rejilla [indc_celda] [2] = {
                    punto_hexgn [0],
                    punto_hexgn [3],
                    punto_hexgn [4] };
            puntos_rejilla [indc_celda] [3] = {
                    punto_hexgn [0],
                    punto_hexgn [4],
                    punto_hexgn [5] };
            puntos_rejilla [indc_celda] [4] = {
                    punto_hexgn [0],
                    punto_hexgn [5],
                    punto_hexgn [6] };
            puntos_rejilla [indc_celda] [5] = {
                    punto_hexgn [0],
                    punto_hexgn [6],
                    punto_hexgn [1] };
        }
    }


    void PresenciaTablero::estableceMallaMuros (
                    const PuntosHexagonos & puntos_rejilla,
                    const IndicesEstampas & indices_estampas,
                    const PuntosHexagonos & puntos_textura   ) {
        this->malla_muros->define ((int) puntos_rejilla.size () * 6);
        for (int indc_celda = 0; indc_celda < puntos_rejilla.size (); ++ indc_celda) {
            for (int indc_trngl = 0; indc_trngl < 6; ++ indc_trngl) {
                unir2d::TrianguloMalla trngl_malla {};
                for (int indc_vertc = 0; indc_vertc < 3; ++ indc_vertc) {
                    trngl_malla.ponPunto (indc_vertc, puntos_rejilla [indc_celda] [indc_trngl] [indc_vertc]);
                    int indc_estmp = indices_estampas [indc_celda] [indc_trngl]; 
                    trngl_malla.ponTexel (indc_vertc, puntos_textura [indc_estmp] [indc_trngl] [indc_vertc]);
                }
                this->malla_muros->asigna (indc_celda * 6 + indc_trngl, trngl_malla);
            }
        }
    }


    void PresenciaTablero::preparaPaneles () {
        textura_panel_vertcl = new unir2d::Textura {};
        textura_panel_vertcl->carga (JuegoMesaBase::carpetaActivos () + "panel_lateral.png");
        //
        imagen_panel_vertcl_izqrd = new unir2d::Imagen {};
        imagen_panel_vertcl_izqrd->asigna (textura_panel_vertcl);
        imagen_panel_vertcl_izqrd->ponPosicion (regionPanelVertclIzqrd.posicion ());
        //
        imagen_panel_vertcl_derch = new unir2d::Imagen {};
        imagen_panel_vertcl_derch->asigna (textura_panel_vertcl);
        imagen_panel_vertcl_derch->ponPosicion (regionPanelVertclDerch.posicion ());
        //
        textura_panel_abajo = new unir2d::Textura {};
        textura_panel_abajo->carga (JuegoMesaBase::carpetaActivos () + "panel_abajo.png");
        //
        imagen_panel_abajo_izqrd = new unir2d::Imagen {};
        imagen_panel_abajo_izqrd->asigna (textura_panel_abajo);
        imagen_panel_abajo_izqrd->ponPosicion (regionPanelAbajoIzqrd.posicion ());
        //
        imagen_panel_abajo_derch = new unir2d::Imagen {};
        imagen_panel_abajo_derch->asigna (textura_panel_abajo);
        imagen_panel_abajo_derch->ponPosicion (regionPanelAbajoDerch.posicion ());
        //
        textura_bandera_izqrd = new unir2d::Textura ();
        textura_bandera_izqrd->carga (JuegoMesaBase::carpetaActivos () + "bandera_izquierda.png");
        imagen_bandera_izqrd = new unir2d::Imagen ();
        imagen_bandera_izqrd->asigna (textura_bandera_izqrd);
        imagen_bandera_izqrd->ponPosicion (regionPanelVertclIzqrd.posicion () + Vector {10, 10});
        //
        textura_escudo_izqrd = new unir2d::Textura ();
        textura_escudo_izqrd->carga (actor_tablero->archivo_escudo_izqrd);
        imagen_escudo_izqrd = new unir2d::Imagen ();
        imagen_escudo_izqrd->asigna (textura_escudo_izqrd);
        imagen_escudo_izqrd->ponPosicion (regionPanelVertclIzqrd.posicion () + Vector {10 + 25, 10 + 5});
        //
        textura_bandera_derch = new unir2d::Textura ();
        textura_bandera_derch->carga (JuegoMesaBase::carpetaActivos () + "bandera_derecha.png");
        imagen_bandera_derch = new unir2d::Imagen ();
        imagen_bandera_derch->asigna (textura_bandera_derch);
        imagen_bandera_derch->ponPosicion (regionPanelVertclDerch.posicion () + Vector {10, 10});
        //
        textura_escudo_derch = new unir2d::Textura ();
        textura_escudo_derch->carga (actor_tablero->archivo_escudo_derch);
        imagen_escudo_derch = new unir2d::Imagen ();
        imagen_escudo_derch->asigna (textura_escudo_derch);
        imagen_escudo_derch->ponPosicion (regionPanelVertclDerch.posicion () + Vector {10 + 25, 10 + 5});
    }


    void PresenciaTablero::liberaPaneles () {
        delete imagen_escudo_derch;         
        imagen_escudo_derch = nullptr;
        delete textura_escudo_derch;        
        textura_escudo_derch = nullptr;
        delete imagen_escudo_izqrd;         
        imagen_escudo_izqrd = nullptr;
        delete textura_escudo_izqrd;        
        textura_escudo_izqrd = nullptr;
        delete imagen_bandera_derch;        
        imagen_bandera_derch = nullptr;
        delete textura_bandera_derch;       
        textura_bandera_derch = nullptr;
        delete imagen_bandera_izqrd;        
        imagen_bandera_izqrd = nullptr;
        delete textura_bandera_izqrd;       
        textura_bandera_izqrd = nullptr;
        delete imagen_panel_abajo_izqrd;          
        imagen_panel_abajo_izqrd = nullptr;
        delete imagen_panel_abajo_derch;          
        imagen_panel_abajo_derch = nullptr;
        delete textura_panel_abajo;         
        textura_panel_abajo = nullptr;
        delete imagen_panel_vertcl_derch;          
        imagen_panel_vertcl_derch = nullptr;
        delete imagen_panel_vertcl_izqrd;          
        imagen_panel_vertcl_izqrd = nullptr;
        delete textura_panel_vertcl  ;      
        textura_panel_vertcl = nullptr;
    }


    void PresenciaTablero::preparaMonitor () {
        Vector poscn {regionMonitor.posicion () + Vector {4, 0}};
        //
        textura_fondo_monitor = new unir2d::Textura {};
        textura_fondo_monitor->carga (JuegoMesaBase::carpetaActivos () + "monitor_fondo.png");
        //
        imagen_fondo_monitor = new unir2d::Imagen {};
        imagen_fondo_monitor->asigna (textura_fondo_monitor);
        imagen_fondo_monitor->ponPosicion (poscn);
        //
        poscn += Vector {9, 9};
        for (int indc = 0; indc < lineas_texto_monitor; ++ indc) {
            texto_monitor [indc] = new unir2d::Texto ("DejaVuSansMono");
            texto_monitor [indc]->ponTamano (12);
            texto_monitor [indc]->ponColor (fosforo_verde);
            texto_monitor [indc]->ponCadena ("Hola gente.");
            texto_monitor [indc]->ponPosicion (poscn);
            poscn += Vector {0, 14};
        }
    }


    void PresenciaTablero::liberaMonitor () {
        for (int indc = 0; indc < lineas_texto_monitor; ++ indc) {
            delete texto_monitor [indc];
            texto_monitor [indc] = nullptr;
        }        
        delete imagen_fondo_monitor;
        imagen_fondo_monitor = nullptr;
        delete textura_fondo_monitor;
        textura_fondo_monitor = nullptr;
    }


    void PresenciaTablero::preparaDisplay () {
        textura_marco_display = new unir2d::Textura {};
        textura_marco_display->carga (JuegoMesaBase::carpetaActivos () + "marco_display.png");
        //
        imagen_marco_display = new unir2d::Imagen {};
        imagen_marco_display->asigna (textura_marco_display);
        imagen_marco_display->ponPosicion (PresenciaTablero::regionDisplay.posicion () + Vector {6, 34});
        imagen_marco_display->ponVisible (true);
        actor_tablero->agregaDibujo (imagen_marco_display);
        //
        textura_digitos_display = new unir2d::Textura {};
        textura_digitos_display->carga (JuegoMesaBase::carpetaActivos () + "digitos_display.png");
        //
        Vector poscn = imagen_marco_display->posicion () + Vector {6, 2};
        for (int indc = 0; indc < cuentaDigitosDisplay; ++ indc) {
            imagenes_digitos_display [indc] = new unir2d::Imagen {};
            imagenes_digitos_display [indc]->asigna (textura_digitos_display);
            imagenes_digitos_display [indc]->ponPosicion (poscn);
            imagenes_digitos_display [indc]->defineEstampas (1, 11);
            imagenes_digitos_display [indc]->seleccionaEstampa (1, 11);
            imagenes_digitos_display [indc]->ponVisible (true);
            actor_tablero->agregaDibujo (imagenes_digitos_display [indc]);
            poscn += Vector {34, 0};
        }
    }


    void PresenciaTablero::liberaDisplay () {
        for (int indc = 0; indc < cuentaDigitosDisplay; ++ indc) {
            delete imagenes_digitos_display [indc];
            imagenes_digitos_display [indc] = nullptr;
        }
        delete textura_digitos_display;
        textura_digitos_display = nullptr;
        delete imagen_marco_display;
        imagen_marco_display = nullptr;
        delete textura_marco_display;
        textura_marco_display = nullptr;
    }


    void PresenciaTablero::preparaAyuda () {
        textura_boton_ayuda = new unir2d::Textura {};
        textura_boton_ayuda->carga (JuegoMesaBase::carpetaActivos () + "boton_ayuda.png");
        //
        imagen_boton_ayuda  = new unir2d::Imagen  {};
        imagen_boton_ayuda->asigna (textura_boton_ayuda);
        imagen_boton_ayuda->ponPosicion (posicion_ayuda);
        imagen_boton_ayuda->ponVisible (true);
        actor_tablero->agregaDibujo (imagen_boton_ayuda);
        //
        textura_interroga = new unir2d::Textura {};
        textura_interroga->carga (JuegoMesaBase::carpetaActivos () + "interrogacion.png");
        //
        imagen_interroga = new unir2d::Imagen  {};
        imagen_interroga->asigna (textura_interroga);
        imagen_interroga->ponPosicion (posicion_ayuda);
        imagen_interroga->ponVisible (true);
        actor_tablero->agregaDibujo (imagen_interroga);
    }


    void PresenciaTablero::liberaAyuda () {
        delete imagen_interroga;
        imagen_interroga = nullptr;
        delete textura_interroga;
        textura_interroga = nullptr;
        delete imagen_boton_ayuda;
        imagen_boton_ayuda = nullptr;
        delete textura_boton_ayuda;
        textura_boton_ayuda = nullptr;
    }


    void PresenciaTablero::preparaSonidos () {
        sonido_establece = new unir2d::Sonido {};
        sonido_establece->carga      (actor_tablero->archivo_sonido_establece);
        sonido_establece->ponVolumen (actor_tablero->volumen_sonido_establece);
        sonido_desplaza = new unir2d::Sonido {};
        sonido_desplaza->carga      (actor_tablero->archivo_sonido_desplaza);
        sonido_desplaza->ponVolumen (actor_tablero->volumen_sonido_desplaza);
    }


    void PresenciaTablero::liberaSonidos () {
        delete sonido_establece;
        sonido_establece = nullptr;
        delete sonido_desplaza;
        sonido_desplaza = nullptr;
    }


}