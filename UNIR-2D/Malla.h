
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
// Archivo: Malla.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


namespace unir2d {


    /// @brief Conjunto de triángulos que se presentan en pantalla. 
    /// @details Hereda de la clase Dibujable la capacidad de ser presentada en pantalla formando
	/// parte de un actor del juego (usando una clase derivada de ActorBase).<p>
	/// Para establecer los triángulos que se presentan en pantalla se usan instancias de la clase 
    /// TrianguloMalla.
    class Malla : public Dibujable {
    public:

        /// @brief Constructor por defecto.
        Malla () = default;

		/// @brief Destructor.
        ~Malla ();

        /// @brief Establece la instancia de Textura de la cual se toman los colores usados para 
        /// dibujar los triángulos contenidos en esta instancia.
        /// @see TrianguloMalla.
        /// @param textura Instancia de Textura que se usa para dibujar los triangulos.
        void asigna (Textura * textura);

        /// @brief Establece el número total de triangulos contenidos en esta instancia.
        /// @details Antes de estableder los triangulos (instancias de la clase TrianguloMalla) 
        /// contenidos en esta instancia, es necesario establecer cuantos habrá. 
        /// @param triangulos Número total de triangulos contenidos en esta instancia.
        void define (int triangulos);

        /// @brief Establece uno de los triangulos contenido en esta instancia. 
        /// @param indice Índice en la lista de esta instancia en el cual estará el triangulo.
        /// @param triangulo Instancia de la clase TrianguloMalla asignada a la lista de esta 
        /// instancia.
        void asigna (int indice, TrianguloMalla triangulo);

    private:

        Textura * textura {};

        int total_vertices {0};
        sf::VertexArray vertices {};

        // las mallas no se pueden copiar ni mover       
        Malla (const Malla & )              = delete;
        Malla (Malla && )                   = delete;
        Malla & operator = (const Malla & ) = delete;
        Malla & operator = (Malla && )      = delete;
        
        void dibuja (const Transforma & contenedor, Rendidor * rendidor) override;

    };


}