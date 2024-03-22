
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
// Archivo: Dibujable.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


/// @cond


void Dibujable::situa (sf::Transformable & objeto, const Transforma & contenedor, const Transforma & transforma) {
    Vector poscn = contenedor.aplicaAPosicion (transforma.posicion ());
    float  rotcn = contenedor.aplicaARotacion (transforma.rotacion ());
    objeto.setOrigin   (transforma.origen ().x (), transforma.origen ().y ());
    objeto.setPosition (poscn.x (), poscn.y ());
    objeto.setRotation (rotcn * Transforma::radianes_a_grados);
    objeto.setScale    (transforma.escala ().x (), transforma.escala ().y ());
}


/// @endcond



/*

	translate

        | a00  a01   0  a03 |   |   1    0   0   x |   | a00  a01   0  a00·x+a01·y+a03 |
        | a10  a11   0  a13 |   |   0    1   0   y |   | a10  a11   0  a10·x+a11·y+a13 |
        |   0    0   1    0 | · |   0    0   1   0 | = |   0    0   1                0 |  
        |   0    0   0    1 |   |   0    0   0   1 |   |   0    0   0                1 |


	rotate

        | a00  a01   0  a03 |   | cos -sen   0   0 |   | a00·cos+a01·sen  -a00·sen+a01·cos   0   a03 |
        | a10  a11   0  a13 |   | sen  cos   0   0 |   | a10·cos+a11·sen  -a10·sen+a11·cos   0   a13 |
        |   0    0   1    0 | · |   0    0   1   0 | = |               0                 0   1     0 |  
        |   0    0   0    1 |   |   0    0   0   1 |   |               0                 0   0     1 |


	escale

        | a00  a01   0  a03 |   |   x    0   0   0 |   | a00·x  a01·y   0   a03 |
        | a10  a11   0  a13 |   |   0    y   0   0 |   | a10·x  a11·y   0   a13 |
        |   0    0   1    0 | · |   0    0   1   0 | = |     0      0   1     0 |  
        |   0    0   0    1 |   |   0    0   0   1 |   |     0      0   0     1 |

 */
