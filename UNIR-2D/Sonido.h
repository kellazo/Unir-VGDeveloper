
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
// Archivo: Sonido.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


namespace unir2d {


    class Rendidor;


    /// @brief Reproduce sonidos y musica mientras se ejecuta el proyecto.
    /// @details El sonido se toma de un archivo externo. Solo es posible usar un archivo en cada 
    /// instancia, sin embargo, se pueden usar varias instancias para reproducir varios sonidos 
    /// simultaneamente.
    class Sonido  {
    public: 

        /// @brief Constructor.
        explicit Sonido ();
        
        /// @brief Destructor.
        ~Sonido ();

        /// @brief Almacena un archivo de sonido en la memoria.
        /// @details No se pueden cargar archivos de tipo mp3. Este método se usa para sonidos de 
        /// corta duración. Para cargar archivos de sonido mas extensos se usa el método abre().
        /// @param archivo Archivo de sonido.
        void carga (path archivo);

        /// @brief Abre un archivo de sonido que no se almacena en la memoria.
        /// @details No se pueden cargar archivos de tipo mp3. Este método se usa para sonidos de 
        /// mayor duración. Para cargar archivos de sonido de corta duración se usa el método 
        /// carga().
        /// @param archivo Archivo de sonido.
        void abre (path archivo);

        /// @brief Obtiene el volumen del sonido entre 0 y 100.
        /// @return Volumen del sonido.
        int volumen ();

        /// @brief Establece el volumen del sonido entre 0 y 100.
        /// @param valor Volumen del sonido.
        void ponVolumen (int valor);

        /// @brief Indica si el sonido se esta reproduciendo.
        /// @return Si el sonido se está reproduciendo.
        bool sonando ();

        /// @brief Inicia la reproducción del sonido.
        /// @details El archivo debe estar establecido con el método carga() o el método graba().
        void suena ();

        /// @brief Detiene la reproducción del sonido.
        void para ();

        // @brief Reinicia la reproducción del sonido.
        void repite ();

    private: 

        bool            es_sonido {};
        bool            es_musica {};
        sf::SoundBuffer sound_buffer {};
        sf::Sound       sound {};
        sf::Music       music {};

        inline static int cuenta_instancias {};

        // loss sonidos no se pueden copiar ni mover
        Sonido (const Sonido & )              = delete;
        Sonido (Sonido && )                   = delete;
        Sonido & operator = (const Sonido & ) = delete;
        Sonido & operator = (Sonido && )      = delete;

        friend class JuegoBase;

    };


    inline Sonido::Sonido () {
        cuenta_instancias ++;
    }


    inline Sonido::~Sonido () {
        cuenta_instancias --;
    }


}


