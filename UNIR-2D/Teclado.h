
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
// Archivo: Teclado.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


namespace unir2d {


	class Rendidor;


	/// @brief Clase que implementa el acceso al teclado del sistema.
	/// @details La clase Motor comprueba el estado de pulsación de las teclas una sola vez en cada 
	/// ciclo del bucle del juego. De esta forma, el resultado obtenido con los métodos de esta 
	/// clase es coherente durante todo el ciclo.<p>
	/// La pulsación de una tecla es lenta en comparación con la ejecución de los ciclos del bucle 
	/// del juego. Si, durante un ciclo, el juego responde a una pulsación con una acción, en el 
	/// siguiente ciclo la tecla puede seguir estando pulsada y, en consecuencia, la accion se puede 
	/// repetir. Para evitar este efecto, esta clase puede marcar una pulsación como 'consumida',
	/// lo que es equivalente a anular la pulsación. La pulsacion se vuelve a detectar cuando el 
	/// jugador levanta la tecla y la vuelve a pulsar.
	class Teclado {
	public:

		/// @brief Comprueba si la tecla indicada está pulsada en el momento de la llamada.
		/// @param tecla Tecla que se comprueba.
		/// @return Si la tecla está pulsada.
		static bool pulsando (Tecla tecla);

		/// @brief Anula la pulsación actual de la tecla indicada.
		/// @details Si la tecla indicada está pulsada, la marca como no pulsada hasta que el 
		/// jugador la vuelva a pulsar.
		/// @param tecla Tecla que se marca. 
		static void consume (Tecla tecla);

		static bool cualquierTecla();

	private:

		inline static sf::WindowHandle winHandle;

		inline static sf::RenderWindow* window; //raimon

		static const int totalTeclas = static_cast <int> (Tecla::escape) + 1;
		inline static std::array <bool, totalTeclas> s_pulsada   { false };
		inline static std::array <bool, totalTeclas> s_consumida { false };

		static void sondea ();

		static void configura (Rendidor * rendidor);

		static void sondea (Tecla tecla, int virtual_key);

		friend class Motor;

	};


}
