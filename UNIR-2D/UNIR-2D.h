
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
// Archivo: UNIR-2D.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Por alguna razón que no entiendo, no se puede poner Windows aquí:
//#include <Windows.h>

#include <cassert>
#include <exception>
#include <system_error>
#include <memory>
#include <string>
using string  = std::string;
using wstring = std::wstring;
#include <array>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <random>
#include <filesystem>
#include <iostream>
#include <cmath>
#include <numbers>
#include <cstdint>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Coord.h"
#include "Vector.h"
#include "Region.h"
#include "Color.h"
#include "Tiempo.h"
#include "Tecla.h"
#include "Teclado.h"
#include "BotonRaton.h"
#include "Raton.h"
#include "Transforma.h"
#include "Dibujable.h"
#include "RellenoFigura.h"
#include "Circulo.h"
#include "Rectangulo.h"
#include "TrazoLinea.h"
#include "Trazos.h"
#include "Textura.h"
#include "Imagen.h"
#include "Baldosas.h"
#include "TrianguloMalla.h"
#include "Malla.h"
#include "Fuentes.h"
#include "Texto.h"
#include "Sonido.h"
#include "ActorBase.h"
#include "EjecucionJuego.h"
#include "JuegoBase.h"
#include "Motor.h"
#include "Rendidor.h"
