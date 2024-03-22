
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
// Archivo: Tecla.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


/// @file


namespace unir2d {


    /// @brief Enumera las teclas reconocidas por la clase Teclado.
	/// @remarks Tecla::escape debe ser siempre el último valor de esta enumeración (véase: Teclado::totalTeclas).
	enum class Tecla : int {
		/// @brief Tecla 'flecha arriba'.
        arriba,
		/// @brief Tecla 'flecha abajo'.
		abajo,
		/// @brief Tecla 'flecha izquierda'.
		izquierda,
		/// @brief Tecla 'flecha derecha'.
		derecha,
		/// @brief Tecla 'A'.
		A,
		/// @brief Tecla 'S'.
		S,
		/// @brief Tecla 'D'.
		D,
		/// @brief Tecla 'W'.
		W,
		/// @brief Tecla 'Entrar'.
		entrar,
		/// @brief Tecla 'espacio'.
		espacio,
		/// @brief Tecla 'Esc'.
		escape,
	};
	// 

		
}
