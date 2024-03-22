
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
// Archivo: Imagen.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.
  

#pragma once


namespace unir2d {


    class Rendidor;


    /// @brief Presenta en pantalla una imagen.
	/// @details Hereda de la clase Dibujable la capacidad de ser presentada en pantalla formando
	/// parte de un actor del juego (usando una clase derivada de ActorBase).<p>
    /// La imagen debe estar cargada en memoria mediante una instancia de la clase Textura.
    class Imagen : public Dibujable {
    public: 

        /// @brief Constructor por defecto.
        explicit Imagen () = default;

        /// @brief Destructor.
        ~Imagen ();

        /// @brief Establece que la imagen de la instancia se toma de la imagen almacenada en la 
        /// instancia de Textura indicada.
        /// @param textura textura de la que se toma la imagen.
        void asigna (Textura * textura);

        /// @brief Colorea la imagen.
        /// @param color color usado.
        void colorea (Color color);       
        
        /// @brief Establece que la imagen esta formada por subimagenes (o estampas).
        /// @details La imagen de la Textura se tratará como un conjunto de subimagenes organizadas 
        /// en una cuadricula con las filas y las columnas indicadas. Esta organización se denomina 
        /// "cuadricula de estampas".
        /// @param filas filas de la cuadricula
        /// @param columnas columnas de la cuadricula
        void defineEstampas (int filas, int columnas);

        /// @brief Establece la imagen de la cuadricula de estampas que será presentada.
        /// @see defineEstampas
        /// @param fila fila de la imagen en la cuadricula, a partir de 1.
        /// @param columna columna de la imagen en la cuadricula, a partir de 1.
        void seleccionaEstampa (int fila, int columna);

        /// @brief Fila de la imagen en la cuadricula de estampas.
        /// @see defineEstampas
        /// @return Fila de la imagen en la cuadricula, a partir de 1.
        int filaEstampa ();

        /// @brief Columna de la imagen en la cuadricula de estampas.
        /// @see defineEstampas
        /// @return Columna de la imagen en la cuadricula, a partir de 1.
        int columnaEstampa ();

    private: 

        Textura * textura {};
        sf::Sprite sprite {};

        int filas_estampas {1};
        int colns_estampas {1};    
        int fila_seleccion {1};
        int coln_seleccion {1};

        bool coloreado {false};
        Color color {};

        // las imágenes no se pueden copiar ni mover
        Imagen (const Imagen & )              = delete;
        Imagen (Imagen && )                   = delete;
        Imagen & operator = (const Imagen & ) = delete;
        Imagen & operator = (Imagen && )      = delete;
        
        void dibuja (const Transforma & contenedor, Rendidor * rendidor) override;
        void dibuja (Textura * textura);

        friend class Textura;

    };


    inline int Imagen::filaEstampa () {
        return fila_seleccion;
    }

    inline int Imagen::columnaEstampa () {
        return coln_seleccion;
    }


}
