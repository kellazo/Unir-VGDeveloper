
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
// Archivo: Dibujable.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.
	  

#pragma once


namespace unir2d {


	class Rendidor;


	/// @brief Clase base de los objetos que se presentan en la pantalla del juego.
	/// @details Las instancias de las clases que heredan de esta clase (los dibujables) aparecen en 
	/// una lista contenida en las instancia de la clase derivadas de ActorBase (los actores). Esto
	/// establece que se presenten automáticamente en la pantalla del juego.<p>
	/// Los dibujables se situan en la pantalla en una posición relativa a la posición del actor 
	/// contenedor. Lo mismo ocurre con la orientación del dibujable respecto a la orientación del 
	/// actor contenedor.<p>
	/// Si dos dibujables se situan el posiciones cercanas, uno de ellos puede ocultar al otro. Los
	/// dibujables se presentan en pantalla en el orden en el que aparecen los actores en el juego y, 
	/// dentro de cada actor, en el orden en el que aparecen los dibujables en el actor. En este orden,
	/// los posteriores ocultan a los anteriores. Para cambiar el orden de presentación se usa en 'índice 
	/// Z'. Si un dibujable tiene un 'índice Z' superior a otro, se presentará despues, aunque aparezca 
	/// antes en la lista de ActorBase o aparezca en un ActorBase previo.
	class Dibujable {
	public:

		/// @brief Destructor virtual.
		virtual ~Dibujable ();

		/// @brief Obtiene la posición considerada origen de la instancia.
		/// @details El origen es un punto que se toma como referencia para establecer la posición 
		/// de la instancia y para realizar las rotaciones de la instancia.
		/// @return Posición del punto origen de la instancia.
		Vector origen () const;

		/// @brief Establece la posición considerada origen de la instancia.
		/// @see Dibujable::origen.
		/// @param valor Posición del punto origen de la instancia.
		void ponOrigen (Vector valor);

		//Vector escala () const;
		//void ponEscala (Vector valor);

		/// @brief Establece la posición de la instancia.
		/// @details La posición es relativa a la posición y a la orientación del actor contenedor. La 
		/// posición indica la posicion del punto origen de la instancia.
		/// @return Posición de la instancia.
		Vector posicion () const;

		/// @brief Establece la posición de la instancia.
		/// @see Dibujable::posicion.
		/// @param valor Posición de la instancia.
		void ponPosicion (Vector valor);

		/// @brief Establece la rotación de la instancia.
		/// @details La rotación es relativa a la posición y a la orientación del actor contenedor. La 
		/// rotación se realiza sobre el punto origen de la instancia.
		/// @return Rotación de la instancia.
		float rotacion () const;

		/// @brief Establece la rotación de la instancia.
		/// @see Dibujable::rotacion.
		/// @param valor Rotación de la instancia.
		void ponRotacion (float valor);

		/// @brief Índice Z de este dibujable.
		/// @details El índice Z es un entero usado para establecer el orden de presentación de los 
		/// dibujables del juego. Un dibujable con índice Z superior a otro se presentará despues y
		/// no será ocultado por aquel. 
		/// @return Índice Z de la instancia.
		int indiceZ ();

		/// @brief Asigna el índice Z de este dibujable.
		/// @details Véase el método indiceZ();
		/// @param valor 
		void ponIndiceZ (int valor);

		/// @brief Indica si la instancia se presenta en pantalla o no.
		/// @details Si visible es falso la instancia no se presenta en pantalla automáticamente.
		/// @return Si la instancia se presenta en pantalla.
		bool visible () const;

		/// @brief Establece si la instancia se presenta en pantalla o no.
		/// @param valor Si la instancia se presenta en pantalla.
		void ponVisible (bool valor);

	protected:

		Transforma m_transforma {};
		int indice_z {};
		bool m_visible {true};

		explicit Dibujable ();

		static void situa (sf::Transformable & objeto, const Transforma & contenedor, const Transforma & transforma);

		virtual void dibuja (const Transforma & contenedor, Rendidor * rendidor) = 0;

	private:

		inline static int cuenta_instancias {};

		friend class ActorBase;
        friend class JuegoBase;

	};
	

    inline Dibujable::Dibujable () {
		cuenta_instancias ++;
	}

    inline Dibujable::~Dibujable () {
		cuenta_instancias --;
	}

	inline Vector Dibujable::origen () const {
		return m_transforma.origen ();
	}

	inline void Dibujable::ponOrigen (Vector valor) {
		m_transforma.ponOrigen (valor);
	}

	//inline Vector Dibujable::escala () const {
	//	return m_transforma.escala ();
	//}

	//inline void Dibujable::ponEscala (Vector valor) {
	//	m_transforma.ponEscala (valor);
	//}

	inline Vector Dibujable::posicion () const {
		return m_transforma.posicion ();
	}

	inline void Dibujable::ponPosicion (Vector valor) {
		m_transforma.ponPosicion (valor);
	}

	inline float Dibujable::rotacion () const {
		return m_transforma.rotacion ();
	}

	inline void Dibujable::ponRotacion (float valor) {
		m_transforma.ponRotacion (valor);
	}

	inline int Dibujable::indiceZ () {
		return indice_z;
	}

	inline void Dibujable::ponIndiceZ (int valor) {
		indice_z = valor;
	}

	inline bool Dibujable::visible () const {
		return m_visible;
	}

	inline void Dibujable::ponVisible (bool valor) {
		m_visible = valor;
	}


}