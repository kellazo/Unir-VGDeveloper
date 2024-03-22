
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
// Archivo: Rendidor.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.
    

#pragma once


namespace unir2d {
 

    class Rendidor {
    private:

        sf::RenderWindow * window {};

        explicit Rendidor() = default;
        ~Rendidor() = default;

        // No se pueden copiar ni mover las instancias de esta clase      
        Rendidor (const Rendidor & )              = delete;
        Rendidor (Rendidor && )                   = delete;
        Rendidor & operator = (const Rendidor & ) = delete;
        Rendidor & operator = (Rendidor && )      = delete;
                
        void abre (JuegoBase * juego);
        void cierra ();
        void limpia ();
        void muestra ();

        bool cerrado ();

        friend class Teclado;
        friend class Raton;
        friend class Motor;
        friend class ActorBase;
        friend class Textura;
        friend class Circulo;
        friend class Trazos;
        friend class Rectangulo;
        friend class Imagen;
        friend class Baldosas;
        friend class Malla;
        friend class Texto;

    };


}
