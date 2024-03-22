
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
// Archivo: TrazoLinea.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.
 

#pragma once


namespace unir2d {

	
	/// @brief Almacena los datos del trazo de una línea destinada a ser presentada en pantalla.
	/// @details Los trazos se especifican mediante un punto inicial, un punto final y un color.<p>
	/// Un conjunto de trazos se agregan a una instancia de Trazos para ser presentados 
	/// conjuntamente.
	class TrazoLinea {
	public:

		/// @brief Constructor que almacena los datos del trazo.
		/// @param punto_1 Primer punto del trazo.
		/// @param punto_2 Segundo punto del trazo.
		/// @param color Color del trazo.
		explicit TrazoLinea (Vector punto_1, Vector punto_2, Color color);

	private:

		Vector m_punto_1;
		Vector m_punto_2;
		Color  m_color;

		friend class Trazos;

	};


	inline TrazoLinea::TrazoLinea (Vector punto_1, Vector punto_2, Color color) {
		m_punto_1 = punto_1;
		m_punto_2 = punto_2; 
		m_color   = color;
	}


}



