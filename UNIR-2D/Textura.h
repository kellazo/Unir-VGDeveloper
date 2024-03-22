
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
// Archivo: Textura.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


namespace unir2d {


    using std::filesystem::path;


    class Imagen;
    class Texto;


    /// @brief Almacena una imagen en la memoria.
    /// @details Para presentar la imagen de una instancia de esta clase en la pantalla se usa una 
    /// instancia de la clase Imagen o se usa una instancia de la clase Baldosas para cubrir una 
    /// superficie.<p>
    /// Esta clase se puede usar para cargar las imágenes de un archivo o para crear una imagen 
    /// nueva en la memoria.
    class Textura {
    public: 

        /// @brief Constructor.
        explicit Textura ();

		/// @brief Destructor.
		~Textura ();

        /// @brief Lee la imagen del archivo y la almacena en la memoria.
        /// @details Solo se puede leer una imagen en cada instancia de Textura. Una imagen cargada
        /// no se puede usar como una imagen creada.
        /// @see crea()
        /// @param archivo Camino en el sistema de ficheros al archivo de la imagen.
        void carga (path archivo);

        /// @brief Suaviza la presentación de la imagen.
        void suaviza (); 

        /// @brief Crea una imagen nueva en la memoria.
        /// @details Solo se puede crear una imagen en cada instancia de Textura y solo cuando no 
        /// hay una imagen cargada.
        /// @see carga()
        /// @param tamano Anchura y altura de la imagen en píxeles.
        void crea (Vector tamano);

        /// @brief Dibuja sobre la imagen de esta instancia la imagen indicada. 
        /// @details La imagen de esta instancia debe ser una imagen creada, no cargada. Para 
        /// dibujar la imagen indicada se tienen en cuenta los valores establecidos en ella, por 
        /// ejemplo, la posicón, la rotación, etc.
        /// @param imagen Imagen que se dibuja.
        void dibuja (Imagen * imagen);

        /// @brief Escribe un texto en la imagen de esta instancia. 
        /// @details La imagen de esta instancia debe ser una imagen creada, no cargada. Para 
        /// escribir el texto indicado se tienen en cuenta los valores establecidos en el, por 
        /// ejemplo, la posición, la tipografía, etc.
        /// @param texto 
        void dibuja (Texto * texto);

        /// @brief Indica cuantas instancias de Dibujable tienen una asignación activa a esta 
        /// instancia.
        /// @details Si hay alguna asignación activa, esta instancia no se puede eliminar.
        /// @return Número de asignación activa a esta instancia.
        int cuentaUsos () const;

    private: 

        bool iniciada {false};
        bool para_rendir {false};
        sf::Vector2u rectg_textura {};

        sf::Texture texture {};

        bool rendida {false};
        sf::RenderTexture rendible {};

        int cuenta_usos {0};

        const sf::Texture & entidad ();

        inline static int cuenta_instancias {};

        // las texturas no se pueden copiar ni mover       
        Textura (const Textura & )              = delete;
        Textura (Textura && )                   = delete;
        Textura & operator = (const Textura & ) = delete;
        Textura & operator = (Textura && )      = delete;

        friend class Imagen;
        friend class Baldosas;
        friend class Malla;
        friend class Texto;
        friend class JuegoBase;

    };


    inline Textura::Textura () {
        cuenta_instancias ++;
    }

    inline Textura::~Textura () {
        cuenta_instancias --;
    }

    inline int Textura::cuentaUsos () const {
        return cuenta_usos;
    }


}
