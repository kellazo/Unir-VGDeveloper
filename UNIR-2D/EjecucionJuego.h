
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
// Archivo: JuegoBase.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.

       
#pragma once


/// @file


namespace unir2d {


    /// @enum EjecucionJuego
    /// @brief Enumera los posibles estados de ejecución de un juego.
    /// @details La clase JuegoBase mantiene el estado de ejecución del juego.
    enum class EjecucionJuego {
        /// @brief El juego se está ejecutando. El método Motor::ejecuta continua en ejecución.
        activo,
        /// @brief El juego está en pausa. El método Motor::ejecuta continua en ejecución.
        pausado,
        /// @brief El juego ha sido cancelado. El método Motor::ejecuta termina su ejecución.
        cancelado,
        /// @brief El juego debe ser reiniciado. El método Motor::ejecuta termina su ejecución.
        reinicio
    };


}