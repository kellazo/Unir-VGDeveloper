// proyecto: Grupal/Tapete
// archivo:  PresenciaTablero.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ActorTablero;


    class PresenciaTablero {
    public:

        static constexpr Vector tamanoTablero           {1710, 1010};

        static constexpr Vector tamanoPanelVertcl       { 110, 880};
        static constexpr Vector tamanoRejilla           {1480, 885};
        static constexpr Vector tamanoPanelAbajo        { 619, 120};

        static constexpr float  margenPanelVertcl       {5};
        static constexpr Region regionPanelVertclIzqrd  {Vector {margenPanelVertcl, margenPanelVertcl}, tamanoPanelVertcl};
        static constexpr float  columnaRejilla          {regionPanelVertclIzqrd.x () + regionPanelVertclIzqrd.ancho ()};
        static constexpr Region regionRejilla           {Vector {columnaRejilla, 0}, tamanoRejilla};
        static constexpr float  columnaPanelVertclDerch {regionRejilla.x () + regionRejilla.ancho ()};
        static constexpr Region regionPanelVertclDerch  {Vector {columnaPanelVertclDerch, margenPanelVertcl}, tamanoPanelVertcl};

        static constexpr float  margenBandaAbajo        {1};
        static constexpr float  filaBandaAbajo          {regionRejilla.y () + regionRejilla.alto () + margenBandaAbajo};
        static constexpr Vector tamanoBandaAbajo        {tamanoPanelVertcl.x () * 2 + tamanoRejilla.x (), tamanoPanelAbajo.y ()}; 

        static constexpr Vector tamanoDisplay           { 90, tamanoBandaAbajo.y ()};
        static constexpr Vector tamanoMonitor           {282, tamanoBandaAbajo.y ()};
        static constexpr Vector tamanoAyuda             { 90, tamanoBandaAbajo.y ()};

        static constexpr Region regionBandaAbajo        {Vector {regionPanelVertclIzqrd.x (), filaBandaAbajo}, tamanoBandaAbajo};
        static constexpr Region regionDisplay           {regionBandaAbajo.posicion (), tamanoDisplay};
        static constexpr float  columnaPanelAbajoIzqrd  {regionDisplay.x () + regionDisplay.ancho ()};
        static constexpr Region regionPanelAbajoIzqrd   {Vector {columnaPanelAbajoIzqrd, regionBandaAbajo.y ()}, tamanoPanelAbajo};
        static constexpr float  columnaMonitor          {regionPanelAbajoIzqrd.x () + regionPanelAbajoIzqrd.ancho ()};
        static constexpr Region regionMonitor           {Vector {columnaMonitor, regionBandaAbajo.y ()}, tamanoMonitor};
        static constexpr float  columnaPanelAbajoDerch  {regionMonitor.x () + regionMonitor.ancho ()};
        static constexpr Region regionPanelAbajoDerch   {Vector {columnaPanelAbajoDerch, regionBandaAbajo.y ()}, tamanoPanelAbajo};
        static constexpr float  columnaAyuda            {regionPanelAbajoDerch.x () + regionPanelAbajoDerch.ancho ()};
        static constexpr Region regionAyuda             {Vector {columnaAyuda, regionBandaAbajo.y ()}, tamanoAyuda};


    private:

        static constexpr int estampasTexturaMuros = 5;


        ActorTablero * actor_tablero;

        unir2d::Textura  * textura_fondo {};
        unir2d::Baldosas * baldosas_fondo {};
        unir2d::Textura  * textura_muros {};
        unir2d::Malla    * malla_muros {};

        unir2d::Textura * textura_panel_vertcl {};
        unir2d::Imagen  * imagen_panel_vertcl_izqrd {};
        unir2d::Imagen  * imagen_panel_vertcl_derch {};
        unir2d::Textura * textura_panel_abajo {};
        unir2d::Imagen  * imagen_panel_abajo_izqrd {};
        unir2d::Imagen  * imagen_panel_abajo_derch {};

        unir2d::Textura * textura_bandera_izqrd {};
        unir2d::Imagen  * imagen_bandera_izqrd {};
        unir2d::Textura * textura_bandera_derch {};
        unir2d::Imagen  * imagen_bandera_derch {};
        unir2d::Textura * textura_escudo_izqrd {};
        unir2d::Imagen  * imagen_escudo_izqrd {};
        unir2d::Textura * textura_escudo_derch {};
        unir2d::Imagen  * imagen_escudo_derch {};

        static constexpr Color fosforo_verde {60, 252, 117};
        unir2d::Textura * textura_fondo_monitor {};
        unir2d::Imagen  * imagen_fondo_monitor {};
        static constexpr int lineas_texto_monitor = 7;
        std::array <unir2d::Texto *, lineas_texto_monitor> texto_monitor {};

        unir2d::Textura * textura_marco_display {};
        unir2d::Imagen *  imagen_marco_display {};
        unir2d::Textura * textura_digitos_display {};
        static constexpr int cuentaDigitosDisplay = 2;
        std::array <unir2d::Imagen *, cuentaDigitosDisplay> imagenes_digitos_display {};

        static constexpr Vector posicion_ayuda {PresenciaTablero::regionAyuda.posicion () + Vector {10, 26}};
        static constexpr float  radio_ayuda {33};
        static constexpr Vector centro_ayuda {posicion_ayuda + Vector {radio_ayuda, radio_ayuda}};
        unir2d::Textura * textura_boton_ayuda {};
        unir2d::Imagen *  imagen_boton_ayuda {};
        unir2d::Textura * textura_interroga {};
        unir2d::Imagen *  imagen_interroga {};

        unir2d::Sonido * sonido_establece {};
        unir2d::Sonido * sonido_desplaza {};


        using IndicesEstampas = std::vector <std::array <int, 6>>;
        using PuntosHexagonos = std::vector <std::array <std::array <Vector, 3>, 6>>;


        explicit PresenciaTablero (ActorTablero * actor_tablero);
        ~PresenciaTablero ();

        void prepara ();
        void reprepara ();
        void libera ();

        void preparaBaldosas ();
        void preparaMuros    ();
        void preparaPaneles  ();
        void preparaMonitor  ();
        void preparaDisplay  ();
        void preparaAyuda    ();
        void preparaSonidos  ();

        void liberaBaldosas ();
        void liberaMuros    ();
        void liberaPaneles  ();
        void liberaMonitor  ();
        void liberaDisplay  ();
        void liberaAyuda    ();
        void liberaSonidos  ();

        void calculaEstampasMuros (
                const std::vector <Coord> & posiciones_rejilla,
                IndicesEstampas           & indices_estampas   );
        int  estampaMuros (bool previo, bool adjunto, bool postrer);
        void punteaTexturaMuros (PuntosHexagonos & puntos_textura);
        void punteaRejillaMuros (
                const std::vector <Coord> & posiciones_rejilla, 
                PuntosHexagonos           & puntos_rejilla     );
        void estableceMallaMuros (
                const PuntosHexagonos & puntos_rejilla,
                const IndicesEstampas & indices_estampas,
                const PuntosHexagonos & puntos_textura   );


        friend class ActorTablero;

    };


}


