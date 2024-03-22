
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
// Archivo: TrianguloMalla.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.

    
#pragma once


namespace unir2d {


	/// @brief Almacena los datos de un triángulo destinado a ser presentado en pantalla.
	/// @details Los triángulos se especifican mediante tres puntos y tres texels (texture pixel). 
    /// Los puntos establecen la posición en pantalla de los vértices del triángulo.<p> 
    /// El triángulo se rellena con los colores tomados de una instancia de Textura. Los texels 
    /// establecen la posición en dicha textura de los vértices de un triángulo, el cual se 
    /// transpone al triángulo que se dibuja.<p>
	/// Un conjunto de triángulos se agregan a una instancia de Malla para ser presentados 
    /// conjuntamente. En la instancia de Malla también se especifica la instancia de Textura que se 
    /// usa para dibujar los triángulos.
    class TrianguloMalla {
    public:

        /// @brief Constructor por defecto.
        explicit TrianguloMalla () = default;

        /// @brief Establece la posición de uno de los vértices del triángulo 
        /// @param indice Índice del vértice, de 0 a 2
        /// @param punto Posición en pantalla del vértice.
        void ponPunto (int indice, Vector punto);

        /// @brief Establece la posición de uno de los vértices del triángulo en una instancia de 
        /// Textura.
        /// @details La instancia de Textura está especificada en la instancia de Malla que contiene 
        /// a esta instanacia.
        /// @param indice Índice del vértice, de 0 a 2
        /// @param texel Posición en la instancia de Textura del vértice.
        void ponTexel (int indice, Vector texel);

    private:

        std::array <Vector, 3> puntos {};
        std::array <Vector, 3> texels {};

        friend class Malla;

    };


    inline void TrianguloMalla::ponPunto (int indice, Vector punto) {
        assert (0 <= indice && indice < 3);
        //
        this->puntos [indice] = punto;        
    }

    inline void TrianguloMalla::ponTexel (int indice, Vector texel) {
        assert (0 <= indice && indice < 3);
        //
        this->texels [indice] = texel;        
    }


}
