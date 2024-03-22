
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
// Archivo: Rectangulo.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.
 

#pragma once


namespace unir2d {

	
	/// @brief Entidad que se presenta en pantalla como un rectángulo.
	/// @details Hereda de la clase Dibujable la capacidad de se presentado en pantalla formando
	/// parte de un actor del juego (de una clase derivada de ActorBase).
	class Rectangulo : public Dibujable {
	public:

		/// @brief Constructor de un rectángulo de base y altura 1.
		explicit Rectangulo ();

		/// @brief Constructor de un rectángulo con la base y altura indicadas.
		/// @param base base del rectángulo.
		/// @param altura altura del rectángulo.
		explicit Rectangulo (float base, float altura);

		/// @brief Obtiene la base del rectángulo.
		/// @return Base del rectángulo.
		float base () const;

		/// @brief Establece la base del rectángulo.
		/// @param valor base del rectángulo.
		void ponBase (float valor);

		/// @brief Obtiene la altura del rectángulo.
		/// @return Altura del rectángulo.
		float altura () const;

		/// @brief Establece la altura del rectángulo.
		/// @param valor altura del rectángulo.
		void ponAltura (float valor);

		/// @brief Obtiene el color del rectángulo.
		/// @return Color del rectángulo.
		Color color () const;

		/// @brief Establece el color del rectángulo.
		/// @param valor color del rectángulo.
		void ponColor (Color valor);

	private:

		float m_base   {1};
		float m_altura {1};
		Color m_color   {};

		sf::RectangleShape shape;

        // los rectangulos no se pueden copiar ni mover       
        Rectangulo (const Rectangulo & )              = delete;
        Rectangulo (Rectangulo && )                   = delete;
        Rectangulo & operator = (const Rectangulo & ) = delete;
        Rectangulo & operator = (Rectangulo && )      = delete;

		void dibuja (const Transforma & contenedor, Rendidor * rendidor) override;

	};


	inline Rectangulo::Rectangulo () :
		shape {sf::Vector2f {1, 1}} {
	}

	inline Rectangulo::Rectangulo (float base, float altura) :
		m_base {base}, m_altura {altura},
		shape {sf::Vector2f {base, altura}} {
	}

	inline float Rectangulo::base () const {
		return m_base;
	}

	inline void Rectangulo::ponBase (float valor) {
		m_base = valor;
		shape.setSize (sf::Vector2f {m_base, m_altura});
	}

	inline float Rectangulo::altura () const {
		return m_altura;
	}

	inline void Rectangulo::ponAltura (float valor) {
		m_altura = valor;
		shape.setSize (sf::Vector2f {m_base, m_altura});
	}

	inline Color Rectangulo::color () const {
		return m_color;
	}

	inline void Rectangulo::ponColor (Color valor) {
		m_color = valor;
		shape.setFillColor (sf::Color {m_color.entero ()});
	}


}
