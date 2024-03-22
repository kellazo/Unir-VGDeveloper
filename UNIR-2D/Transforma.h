
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
// Archivo: Transforma.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#pragma once


namespace unir2d {


	/// @brief Almacena las geometría de las entidades del juego.
	/// @details Esta clase es usada internamente por los actores del juego (derivados de ActorBase)
	/// y por los dibujables del juego (derivados de Dibujable).
	class Transforma {
	public:

		/// @brief Constante π.
		static constexpr float pi = 3.141592654f;

		/// @brief Constante de conversion de radianes a grados.
		static constexpr float radianes_a_grados = 180 / pi;

		Vector origen () const;
		void ponOrigen (Vector valor);
		Vector posicion () const;
		void ponPosicion (Vector valor);
		float rotacion () const;
		void ponRotacion (float valor);
		Vector escala () const;
		void ponEscala (Vector valor);

		float aplicaARotacion (float rotacion) const;
		Vector aplicaAPosicion (Vector posicion) const;

	private:

		Vector m_origen   {0.0, 0.0};
		Vector m_posicion {0.0, 0.0};
		float  m_rotacion {0.0};
		Vector m_escala   {1.0, 1.0};

	};


	inline Vector Transforma::origen () const {
		return m_origen;
	}

	inline Vector Transforma::posicion () const {
		return m_posicion;
	}

	inline float Transforma::rotacion () const {
		return m_rotacion;
	}

	inline Vector Transforma::escala () const {
		return m_escala;
	}

	inline void Transforma::ponOrigen (Vector valor) {
		m_origen = valor;
	}

	inline void Transforma::ponPosicion (Vector valor) {
		m_posicion = valor;
	}

	inline void Transforma::ponRotacion (float valor) {
		m_rotacion = valor;
	}

	inline void Transforma::ponEscala (Vector valor) {
		m_escala = valor;
	}


}

