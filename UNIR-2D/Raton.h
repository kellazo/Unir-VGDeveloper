
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
// Archivo: Raton.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


namespace unir2d {


	class Rendidor;


	/// @brief Clase que implementa el acceso al ratón del sistema.
	/// @details Esta clase detecta si se ha realizado una pulsación reciente doble del botón 
	/// izquierdo del ratón. Es lo que se denomina doble-clic.<p>
	/// La clase Motor comprueba el estado de pulsación de los botones del ratón una sola vez en 
	/// cada ciclo del bucle del juego. De esta forma, el resultado obtenido con los métodos de esta 
	/// clase es coherente durante todo el ciclo.<p>
	/// La pulsación de un botón del ratón es lenta en comparación con la ejecución de los ciclos 
	/// del bucle del juego. Si, durante un ciclo, el juego responde a una pulsación con una acción, en 
	/// el siguiente ciclo el botón puede seguir estando pulsado y, en consecuencia, la accion se puede 
	/// repetir. Para evitar este efecto, esta clase puede marcar una pulsación como 'consumida',
	/// lo que es equivalente a anular la pulsación. La pulsacion se vuelve a detectar cuando el 
	/// jugador levanta el botón y lo vuelve a pulsar.
	class Raton {
	public:

		/// @brief Comprueba si el botón del ratón indicado está pulsado en el momento de la llamada.
		/// @details La pulsación doble (doble-clic) y la pulsación simple no son excluyentes.
		/// @param boton Botón del ratón que se comprueba.
		/// @return Si el botón está pulsado.
		static bool pulsando (BotonRaton boton);

		/// @brief Anula la pulsación actual del botón del ratón indicado.
		/// @details Si el botón indicado está pulsado, lo marca como no pulsado hasta que el 
		/// jugador lo vuelva a pulsar.
		/// @param boton Botón que se marca. 
		static void consumePulsado (BotonRaton boton);

		/// @brief Comprueba si se ha realizado un doble-clic reciente con el ratón.
		/// @details El doble-clic y la pulsación simple no son excluyentes.
		/// @return Si se ha reaizado un doble-clic reciente.
		static bool dobleClic ();

		/// @brief Anula el doble-clic reciente del ratón.
		/// @details Si se ha realizado un doble-clic reciente, lo marca como no realizado hasta que 
		/// el jugador lo vuelva a realizar.
		static void consumeDobleClic ();

		/// @brief Obtiene la posición del ratón en el momento de la llamada.
		/// @details La posición del ratón es relativa a la posición del la pantalla del juego. El 
		/// origen de la pantalla está en la esquina superior izquierda del area de cliente de la 
		/// ventana.
		/// @return Posición del ratón.
		static Vector posicion ();

	private:

		using Momento = std::chrono::time_point<std::chrono::steady_clock>;

		inline static sf::WindowHandle winHandle;

		inline static Momento momento_clic;

		static const int totalBotones = static_cast <int> (BotonRaton::centro) + 1;
		inline static std::array <bool, totalBotones> s_pulsado   { false };
		inline static std::array <bool, totalBotones> s_consumido { false };

		inline static bool   s_doble_clic;
		inline static Vector s_posicion;

		static void sondea ();

		static void configura (Rendidor * rendidor);

		static void sondeaPulsado (BotonRaton boton);
		static void sondeaDobleClic ();
		static void sondeaPosicion ();

		friend class Motor;

	};


}