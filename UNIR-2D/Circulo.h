
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


namespace unir2d {

	
	/// @brief Entidad que se presenta en pantalla como un circulo.
	/// @details Hereda de la clase Dibujable la capacidad de se presentado en pantalla formando
	/// parte de un actor del juego (de una clase derivada de ActorBase).
	class Circulo : public Dibujable {
	public:

		/// @brief Constructor de un circulo de radio 1.
		explicit Circulo ();

		/// @brief Constructor de un circulo con el radio indicado.
		/// @param radio radio del circulo.
		explicit Circulo (float radio);

		/// @brief Obtiene el radio del circulo.
		/// @return Radio del circulo.
		float radio () const;

		/// @brief Establece el radio del circulo.
		/// @param valor radio del circulo.
		void ponRadio (float valor);

		/// @brief Obtiene el valor de RellenoFigura que indica como se dibuja la instancia.
		/// @return Como se dibuja la instancia.
		RellenoFigura relleno ();

		/// @brief Establece el valor de RellenoFigura que indica como se dibuja la instancia.
		/// @param valor Indica como se dibuja la instancia.
		void ponRelleno (RellenoFigura valor);

		/// @brief Obtiene el color del circulo.
		/// @return Color del circulo.
		Color color () const;

		/// @brief Establece el color del circulo.
		/// @param valor color del circulo.
		void ponColor (Color valor);

	private:

		float m_radio {1};
		Color m_color {Color::Blanco};
		RellenoFigura m_relleno {RellenoFigura::interior};
		sf::CircleShape shape;

        // los circulos no se pueden copiar ni mover       
        Circulo (const Circulo & )              = delete;
        Circulo (Circulo && )                   = delete;
        Circulo & operator = (const Circulo & ) = delete;
        Circulo & operator = (Circulo && )      = delete;

		void prepara ();

		void dibuja (const Transforma & contenedor, Rendidor * rendidor) override;

	};


	inline Circulo::Circulo () :
		shape {1} {
	}

	inline Circulo::Circulo (float radio) :
		m_radio {radio}, shape {radio} {
	}

	inline float Circulo::radio () const {
		return m_radio;
	}

	inline void Circulo::ponRadio (float valor) {
		m_radio = valor;
		shape.setRadius (m_radio);
	}

	inline RellenoFigura Circulo::relleno () {
		return m_relleno;
	}

	inline void Circulo::ponRelleno (RellenoFigura valor) {
		m_relleno = valor;
		prepara ();
	}

	inline Color Circulo::color () const {
		return m_color;
	}

	inline void Circulo::ponColor (Color valor) {
		m_color = valor;
		prepara ();
	}

	inline void Circulo::prepara () {
		switch (m_relleno) {
		case RellenoFigura::contorno:
			shape.setOutlineColor (sf::Color {m_color.entero ()});
			shape.setFillColor    (sf::Color {0, 0, 0, 0});
			shape.setOutlineThickness (1.0f);
			break;
		case RellenoFigura::interior:
			shape.setOutlineColor (sf::Color {0, 0, 0, 0});
			shape.setFillColor    (sf::Color {m_color.entero ()});
			break;
		}
	}

}