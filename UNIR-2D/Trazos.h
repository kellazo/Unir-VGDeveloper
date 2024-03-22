
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
// Archivo: Trazos.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.

  
#pragma once


namespace unir2d {

	
	/// @brief Conjunto de trazos que se presentan en pantalla.
	/// @details Hereda de la clase Dibujable la capacidad de se presentado en pantalla formando
	/// parte de un actor del juego (de una clase derivada de ActorBase).<p>
	/// Para establecer los trazos se usan instancias de la clase TrazoLinea.
	class Trazos : public Dibujable {
	public:

        /// @brief Constructor por defecto.
        explicit Trazos () = default;

		/// @brief Lista de instancias de TrazoLinea que se presentan en pantalla.
		/// @return Lista de TrazoLinea.
		const std::vector <TrazoLinea> & lineas () const;

		/// @brief Agrega una instancia de TrazoLinea a la lista de la instancia.
		/// @param linea instancia de TrazoLinea agregada.
		void agrega (TrazoLinea linea);

		/// @brief Extrae todas las instancias de TrazoLinea contenidas en esta instancia.
		void borraLineas ();

		/// @brief Cambia una de las instancia de TrazoLinea contenida en esta instancia.
		/// @details Cambia el primer o el segundo punto del trazo establecido por la instancia de 
		/// TrazoLinea.
		/// @param indice_linea Índice de la instancia de TrazoLinea que se cambia en la lista de 
		/// esta instancia.
		/// @param numero_punto Indica que punto de la instancia de TrazoLinea se cambia. Su valor 
		/// es 1 para el primer punto, 2 para el segundo punto.
		/// @param punto Nuevo valor para el punto de la instancia de TrazoLinea.
		void ponPuntoLinea (int indice_linea, int numero_punto, Vector punto);

		/// @brief Cambia una de las instancia de TrazoLinea contenida en esta instancia.
		/// @details Cambia el color del trazo establecido por la instancia de TrazoLinea.
		/// @param indice Índice de la instancia de TrazoLinea que se cambia en la lista de esta 
		/// instancia.
		/// @param color Nuevo color.
		void ponColorLinea (int indice, Color color);

		/// @brief Extrae la última instancia de TrazoLinea contenidas en esta instancia.
		/// @details La instancia extraida es la última agregada.
		void extreUltimaLinea ();

	private:

		std::vector <TrazoLinea> m_lineas {};

		bool preparado {false};
		sf::Vertex * vertices {};

        // los trazos no se pueden copiar ni mover       
        Trazos (const Trazos & )              = delete;
        Trazos (Trazos && )                   = delete;
        Trazos & operator = (const Trazos & ) = delete;
        Trazos & operator = (Trazos && )      = delete;

		void dibuja (const Transforma & contenedor, Rendidor * rendidor) override;

	};


	inline const std::vector<TrazoLinea> & Trazos::lineas () const {
		return this->m_lineas;
	}

	inline void Trazos::agrega (TrazoLinea linea) {
		this->m_lineas.push_back (linea);
		this->preparado = false;
	}

	inline void Trazos::borraLineas () {
		this->m_lineas.clear ();
		this->preparado = false;
	}

	inline void Trazos::ponPuntoLinea (int indice_linea, int numero_punto, Vector punto) {
		if (numero_punto == 1) {
			this->m_lineas [indice_linea].m_punto_1 = punto;
		}
		if (numero_punto == 2) {
			this->m_lineas [indice_linea].m_punto_2 = punto;
		}
		this->preparado = false;
	}

	inline void Trazos::ponColorLinea (int indice, Color color) {
		this->m_lineas [indice].m_color = color;
		this->preparado = false;
	}

	inline void Trazos::extreUltimaLinea () {
		this->m_lineas.pop_back ();
		this->preparado = false;
	}


}


