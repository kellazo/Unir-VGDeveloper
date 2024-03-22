
// UNIR-2D :: Motor de juego mínimo para la programación de microjuegos en 2 dimensiones.
// 
// Copyright (C) 2022 UNIR-Universidad Internacional de La Rioja. 
// Todos los derechos reservados. 
// El sofware se entrega solo para uso educativo, sin ninguna garantía de adecuación para ningún 
// proposito particular.
// 
// Bibliotecas de código usadas: 
//   1) SFML - Simple and Fast Multimedia Library. Licencia: https://www.sfml-dev.org/license.php  
// 
// Archivo: Color.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once

namespace unir2d {


    /// @brief Establece un color en formato RGBA.
    /// @details Los colores contienen 4 componentes: 'rojo' (Red), 'verde' (Green), 'azul' (Blue) y 
    /// 'alfa'. El componente 'alfa' indica la transparencia del color.<p>
    /// Esta clase también permite realizar conversiones entre el modelo de color RGBA y los modelos 
    /// HSL y HSV.<p>
    /// Las instancias de la clase Color son inmutables, sus componentes no se pueden modificar. 
    class Color {
    public:

        /// @brief Construye el color negro.
        constexpr Color ();

        /// @brief Construye un color opaco con los componentes indicados.
        /// @param rojo componente 'rojo'.
        /// @param verde componente 'verde'.
        /// @param azul componente 'azul'.
        constexpr explicit Color (int rojo, int verde, int azul);

        /// @brief Construye un color tranparente con los componentes indicados.
        /// @param rojo componente 'rojo'.
        /// @param verde componente 'verde'.
        /// @param azul componente 'azul'.
        /// @param alfa componente 'alfa'.
        constexpr explicit Color (int rojo, int verde, int azul, int alfa);

        /// @brief Obtiene el componente 'rojo' del color. 
        /// @return Componente 'rojo'.
        int rojo () const;

        /// @brief Obtiene el componente 'verde' del color. 
        /// @return Componente 'verde'.
        int verde () const;

        /// @brief Obtiene el componente 'azul' del color. 
        /// @return Componente 'azul'.
        int azul () const;

        /// @brief Obtiene el componente 'alfa' del color (transparencia). 
        /// @return Componente 'alfa'.
        int alfa () const;

        /// @brief Obtiene el entero de 32 bits equivalente al color
        /// @return entero de 32 bits del color.
        uint32_t entero () const;

        /// @brief Instancia de color negro.
        static const Color Negro;
        /// @brief Instancia de color blanco.
        static const Color Blanco;
        /// @brief Instancia de color rojo.
        static const Color Rojo;
        /// @brief Instancia de color verde.
        static const Color Verde;    
        /// @brief Instancia de color azul.
        static const Color Azul;
        /// @brief Instancia de color amarillo.
        static const Color Amarillo;
        /// @brief Instancia de color gris oscuro.
        static const Color GrisOscuro;    
        /// @brief Instancia de color gris medio.
        static const Color Gris;    
        /// @brief Instancia de color gris claro.
        static const Color Plata;    
        /// @brief Instancia de color marrón (casi).
        static const Color Marron;
        /// @brief Instancia de color azul marino.
        static const Color Marino;    
        /// @brief Instancia de color naranja.
        static const Color Naranja;
        /// @brief Instancia de color verde claro.
        static const Color Lima;
        /// @brief Instancia de color azul celeste.
        static const Color Cian;    
        /// @brief Instancia de color fucsia.
        static const Color Fucsia;
        /// @brief Instancia de color verde oliva.
        static const Color Oliva;    
        /// @brief Instancia de color morado.
        static const Color Purpura;    
        /// @brief Instancia de color verde azulado.
        static const Color VerdeAzulado;    

        /// @brief Obtiene un Color (RGBA) a partir de los componentes del modelo de color HSL.
        /// @param matiz El componente H del modelo HSL, en el rango [0, 360].
        /// @param saturacion El componente S del modelo HSL, en el rango [0, 100].
        /// @param luminosidad El componente L del modelo HSL, en el rango [0, 100].
        /// @param alfa El componente A del modelo RGBA, en el rango [0, 255].
        /// @return El color obtenido.
        static Color rgbaDeHsl (int matiz, int saturacion, int luminosidad, int alfa);

        /// @brief Obtiene un Color (RGBA) a partir de los componentes del modelo de color HSV.
        /// @param matiz El componente H del modelo HSV, en el rango [0, 360]. 
        /// @param saturacion El componente S del modelo HSV, en el rango [0, 100]. 
        /// @param brillo El componente V del modelo HSV, en el rango [0, 100]. 
        /// @param alfa El componente A del modelo RGBA, en el rango [0, 255]. 
        /// @return El color obtenido.
        static Color rgbaDeHsv (int matiz, int saturacion, int brillo, int alfa);

        /// @brief Obtiene el componente H, el matiz, del modelo de color HSL, HSV y HSI.
        /// @return Componente H, en el rango [0, 360].
        int matiz ();

        /// @brief Obtiene el componente L, la luminosidad, del modelo de color HSL.
        /// @return Componente L, en el rango [0, 100].
        int luminosidad ();

        /// @brief Obtiene el componente I, la intensidad, del modelo de color HSI.
        /// @return Componente I, en el rango [0, 100].
        int intensidad ();

        /// @brief Obtiene el componente V, el brillo, del modelo de color HSV.
        /// @return Componente V, en el rango [0, 100].
        int brillo ();

        /// @brief Obtiene el componente S, la saturación, del modelo de color HSL.
        /// @return Componente S, en el rango [0, 100].
        int saturacionL ();

        /// @brief Obtiene el componente S, la saturación, del modelo de color HSV.
        /// @return Componente S, en el rango [0, 100].
        int saturacionV ();

        /// @brief Obtiene el componente S, la saturación, del modelo de color HSI.
        /// @return Componente S, en el rango [0, 100].
        int saturacionI ();

    private:

        uint8_t m_rojo;
        uint8_t m_verde;
        uint8_t m_azul;
        uint8_t m_alfa;
    
        friend constexpr bool operator == (const Color & color_1, const Color & color_2);
        friend constexpr bool operator != (const Color & color_1, const Color & color_2);

    };   


    inline constexpr Color::Color () {
        this->m_rojo  = 0;
        this->m_verde = 0;
        this->m_azul  = 0;
        this->m_alfa  = 255;
    }

    inline constexpr Color::Color (int rojo, int verde, int azul) {
        this->m_rojo  = rojo;
        this->m_verde = verde;
        this->m_azul  = azul;
        this->m_alfa  = 255;
    }

    inline constexpr Color::Color (int rojo, int verde, int azul, int alfa) {
        this->m_rojo  = rojo;
        this->m_verde = verde;
        this->m_azul  = azul;
        this->m_alfa  = alfa;
    }

    inline int Color::rojo () const {    
        return m_rojo;
    }

    inline int Color::verde () const {
        return m_verde;
    }

    inline int Color::azul () const {
        return m_azul;
    }

    inline int Color::alfa () const {
        return m_alfa;
    }

    inline uint32_t Color::entero () const {
        return (m_rojo << 24) | (m_verde << 16) | (m_azul << 8) | m_alfa;
    }

    inline const Color Color::Negro        {0x00, 0x00, 0x00};
    inline const Color Color::Blanco       {0xFF, 0xFF, 0xFF};
    inline const Color Color::Rojo         {0xFF, 0x00, 0x00};
    inline const Color Color::Verde        {0x00, 0x80, 0x00};    
    inline const Color Color::Azul         {0x00, 0x00, 0xFF};
    inline const Color Color::Amarillo     {0xFF, 0xFF, 0x00};
    inline const Color Color::GrisOscuro   {0x40, 0x40, 0x40};    
    inline const Color Color::Gris         {0x80, 0x80, 0x80};    
    inline const Color Color::Plata        {0xC0, 0xC0, 0xC0};    
    inline const Color Color::Marron       {0x80, 0x00, 0x00};
    inline const Color Color::Marino       {0x00, 0x00, 0x80};    
    inline const Color Color::Naranja      {0xFF, 0x80, 0x00};
    inline const Color Color::Lima         {0x00, 0xFF, 0x00};
    inline const Color Color::Cian         {0x00, 0xFF, 0xFF};    
    inline const Color Color::Fucsia       {0xFF, 0x00, 0xFF};
    inline const Color Color::Oliva        {0x80, 0x80, 0x00};    
    inline const Color Color::Purpura      {0x80, 0x00, 0x80};    
    inline const Color Color::VerdeAzulado {0x00, 0x80, 0x80};    

    inline constexpr bool operator == (const Color & color_1, const Color & color_2) {
        return  color_1.m_rojo  == color_2.m_rojo  &&
                color_1.m_verde == color_2.m_verde &&
                color_1.m_azul  == color_2.m_azul    ;
    }

    inline constexpr bool operator != (const Color & color_1, const Color & color_2) {
        return  color_1.m_rojo  != color_2.m_rojo  ||
                color_1.m_verde != color_2.m_verde ||
                color_1.m_azul  != color_2.m_azul    ;
    }


}