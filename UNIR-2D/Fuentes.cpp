
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
// Archivo: Fuentes.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


/// @cond


void Fuentes::carga (const std::string & nombre) {
    std::filesystem::path camino = std::filesystem::current_path ();
    camino = camino / "fuentes" / (nombre + ".ttf");
	sf::Font * fuente = new sf::Font {}; 
	bool bien = fuente->loadFromFile (camino.string ());
	if (! bien) {
		throw std::runtime_error ("archivo de fuente: " + camino.string () + " no encontrado");
	}
	this->tabla_fuentes.insert (std::pair {nombre, fuente});
	fuentes_cargadas ++;
}


void Fuentes::descarga () {
	fuentes_cargadas -= static_cast <int> (this->tabla_fuentes.size ());
	// no estoy seguro que esto sea necesario:
	for (const std::pair <string, sf::Font *> & pareja : this->tabla_fuentes) {
		delete pareja.second;
	}
	this->tabla_fuentes.clear ();
}


/// @endcond

