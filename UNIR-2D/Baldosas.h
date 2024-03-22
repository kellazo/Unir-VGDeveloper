
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
// Archivo: Baldosas.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once

namespace unir2d {


    /// @brief Presenta en pantalla un conjunto de imágenes usadas para cubrir una superficie.
    /// @details Hereda de la clase Dibujable la capacidad de ser presentada en pantalla formando
	/// parte de un actor del juego (usando una clase derivada de ActorBase).<p>
    /// El conjunto de imágenes debe estar cargado en memoria mediante una instancia de la clase 
    /// Textura. Esta clase establece un mapeo entre las posiciones de la superficie a cubrir y las 
    /// subimágenes (o estampas) de la textura.
    class Baldosas : public Dibujable {
    public:

        /// @brief Constructor por defecto.
        explicit Baldosas () = default;

		/// @brief Destructor.
        ~Baldosas ();

        /// @brief Establece que el conjunto de imágenes de esta instancia se toma de la instancia 
        /// de Textura indicada.
        /// @param textura Textura de la que se toma el conjunto de imágenes.
        void asigna (Textura * textura);

        /// @brief Establece las subimágenes (o estampas) contenidas en la instancia de Textura.
        /// @details La imagen de la Textura se tratará como un conjunto de subimágenes organizadas 
        /// en una cuadricula con las filas y las columnas indicadas. Esta organización se denomina 
        /// "cuadricula de estampas".
        /// @param filas Filas de la cuadricula.
        /// @param columnas Columnas de la cuadricula.
        void defineEstampas (int filas, int columnas);

        /// @brief Establece la cuadricula de la pantalla que se cubre con las estampas.
        /// @details La superficie de la pantalla cubierta por las estampas se trata como una 
        /// cuadricula con las filas y las columnas indicadas. Cada elemento de la cuadricula de la
        /// pantalla coincide en sus dimensiones con un elemento de la cuadricula de estampas.
        /// @param filas Filas de la cuadricula.
        /// @param columnas Columnas de la cuadricula.
        void defineSuperficie (int filas, int columnas);

        /// @brief Establece la colocación de las estampas en la superficie cubierta de la pantalla.
        /// @details Las imágenes de la cuadricula de estampas de la instancia de Textura se sitúan 
        /// en la cuadricula de la superficie cubierta de la pantalla. El vector 'tabla_indices' 
        /// establece la posición de origen de la imagen (en la cuadricula de estampas) para cada 
        /// posición de destino (en la cuadricula de la pantalla).<p>
        /// Aparece un elemento en 'tabla_indices' para cada elemento de la cuadricula de la 
        /// pantalla. Por ello, el número de elementos de 'tabla_indices' es el producto del número 
        /// de filas por el número de columnas de la cuadricula de la pantalla. Los elementos 
        /// aparecen organizados, primero en filas y luego en columnas.<p>
        /// El valor de cada elemento de 'tabla_indices' establece una posición en la cuadricula de
        /// estampas. Si la posición en la cuadricula de estampas es 'fila' y 'coln' (índices a 
        /// partir de 0) el valor del elemento se obtiene con la fórmula: 'fila' * 
        /// 'columnas_estampas' + 'coln', donde 'columnas_estampas' es el número de columnas en la 
        /// cuadricula de estampas.
        /// @param tabla_indices Vector que establece la posición de origen de la imagen para cada 
        /// posición de destino.
        void mapea (const std::vector <uint32_t> & tabla_indices);

    private:

        Textura * textura {};

        int filas_estampas {1};
        int colns_estampas {1};    

        int filas_baldosas {1};
        int colns_baldosas {1};    

        bool preparado {};
        sf::VertexArray vertices {};

        // las baldosas no se pueden copiar ni mover       
        Baldosas (const Baldosas & )              = delete;
        Baldosas (Baldosas && )                   = delete;
        Baldosas & operator = (const Baldosas & ) = delete;
        Baldosas & operator = (Baldosas && )      = delete;
        
        void dibuja (const Transforma & contenedor, Rendidor * rendidor) override;

    };


}