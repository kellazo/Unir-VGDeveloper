
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
// Archivo: Circulo.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


/// @file


namespace unir2d {


    /// @enum RellenoFigura
    /// @brief Enumera las posibles formas de dibujar una figura.
    /// @details Algunas clases derivadas de Dibujable son figuras, por ejemplo Circulo. Esta 
    /// enumeración establece que partes de la figura se dibujan en pantalla. 
    enum class RellenoFigura {
        /// @brief Solo se dibuja el contorno de la figura.
        contorno,
        /// @brief Se dibuja el área completa de la figura.
        interior
    };


}
