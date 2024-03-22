
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
// Archivo: Texto.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.
  

#pragma once


namespace unir2d {


	class Rendidor;


	/// @brief Presenta un texto en pantalla.
	/// @details Hereda de la clase Dibujable la capacidad de ser presentado en pantalla formando
	/// parte de un actor del juego (de una clase derivada de ActorBase).<p>
	/// Las fuentes (tipografías) usada por los textos se cargan desde el subdirectorio 'fuentes' 
	/// del directorio de ejecución del juego. Solo se admiten fuentes de tipo "true type".
	class Texto : public Dibujable {
	public:

		/// @brief Constructor que establece la fuente usada por el texto.
		/// @details El nombre de la fuente es el nombre del archivo que se cargará; sin la 
		/// extensión 'ttf'. El archivo se carga desde el subdirectorio 'fuentes' del directorio de 
		/// ejecución del juego.
		/// @param fuente nombre de la fuente.
		explicit Texto (const string & fuente);

		/// @brief Destructor.
		~Texto ();

		/// @brief Establece la cadena de caracteres que aparecerá en la pantalla.
		/// @param valor cadena de caracteres.
		void ponCadena (const string & valor);

		/// @brief Establece la cadena de caracteres que aparecerá en la pantalla.
		/// @param valor cadena de caracteres.
		void ponCadena (const wstring & valor);

		/// @brief Establece el tamano de la fuente usada para presentar el texto.
		/// @param valor tamano de la fuente.
		void ponTamano (int valor);

		/// @brief Color de la fuente usada para presentar el texto.
		/// @param valor color de la fuente.
		void ponColor (Color valor);

		/// @brief Obtiene la anchura en píxeles del texto que se presenta en pantalla.
		/// @return Anchura en píxeles del texto.
		float anchura ();

	private:

		static Fuentes fuentes;

		sf::Text m_texto {};

        // los textos no se pueden copiar ni mover       
        Texto (const Texto & )              = delete;
        Texto (Texto && )                   = delete;
        Texto & operator = (const Texto & ) = delete;
        Texto & operator = (Texto && )      = delete;

        void dibuja (const Transforma & contenedor, Rendidor * rendidor) override;
        void dibuja (Textura * textura);

        friend class Textura;

	};


	inline Fuentes Texto::fuentes {};

	inline void Texto::ponCadena (const string & valor) {
		m_texto.setString (valor);
	}

	inline void Texto::ponCadena (const std::wstring & valor) {
		m_texto.setString (valor);
	}

	//inline void Texto::ponCaracterX (unsigned int valor) {
	//	m_texto.setString (sf::String (valor));
	//}

	inline void Texto::ponTamano (int valor) {
		m_texto.setCharacterSize (valor);
	}

	inline void Texto::ponColor (Color valor) {
		m_texto.setFillColor (sf::Color {valor.entero ()});
	}


}

