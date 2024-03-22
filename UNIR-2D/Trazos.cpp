
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
// Archivo: Trazos.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


void Trazos::dibuja (const Transforma & contenedor, Rendidor * rendidor) {
/*******************************************************************************/
	int total_vertices = static_cast <int> (m_lineas.size ()) * 2;
	if (! this->preparado) {
		if (this->vertices != nullptr) {
			delete this->vertices;
		}
		vertices = new sf::Vertex [total_vertices];
		int indice = 0;
		for (const TrazoLinea & linea : m_lineas) {
			sf::Vector2f punto_1 = sf::Vector2f {linea.m_punto_1.x (), linea.m_punto_1.y ()};
			sf::Vector2f punto_2 = sf::Vector2f {linea.m_punto_2.x (), linea.m_punto_2.y ()};
			sf::Color    color {linea.m_color.entero ()};
			this->vertices [indice    ] = sf::Vertex {punto_1, color};
			this->vertices [indice + 1] = sf::Vertex {punto_2, color};
			indice += 2;
		}
		this->preparado = true;
	}
	//
	sf::Transformable objeto {};
	Dibujable::situa (objeto, contenedor, this->m_transforma);
	sf::RenderStates states {};
    states.transform = objeto.getTransform ();
    rendidor->window->draw (vertices, total_vertices, sf::Lines, states);
/*******************************************************************************/
/*******************************************************************************
	if (this->lineas_cambiado) {
		this->vertices.resize (this->m_lineas.size () * 2);
		int indice = 0;
		for (const TrazoLinea & linea : this->m_lineas) {
			//
			sf::Vector2f punto_1 = sf::Vector2f {linea.m_punto_1.x (), linea.m_punto_1.y ()};
			sf::Vector2f punto_2 = sf::Vector2f {linea.m_punto_2.x (), linea.m_punto_2.y ()};
			sf::Color color {linea.m_color.entero ()};
			//
			vertices [indice    ] = sf::Vertex {punto_1, color};
			vertices [indice + 1] = sf::Vertex {punto_2, color};
			//
			indice += 2;
		}
	}
	//
    sf::Transformable objeto {};
	Dibujable::situa (objeto, contenedor, this->m_transforma);
	//
    sf::RenderStates states {};
    states.transform = objeto.getTransform ();
    //
	rendidor->window->draw (this->vertices, states);
*******************************************************************************/
}