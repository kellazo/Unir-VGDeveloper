
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
// Archivo: Transforma.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.

	
#include "UNIR-2D.h"	

using namespace unir2d;


/// @cond


float Transforma::aplicaARotacion (float rotacion) const {
	return rotacion + m_rotacion;
};


static Vector multiplica (const float mtrz [4][4], const Vector vect) {
	return Vector {
			mtrz [0][0] * vect.x () + mtrz [0][1] * vect.y () + mtrz [0][3],
	        mtrz [1][0] * vect.x () + mtrz [1][1] * vect.y () + mtrz [1][3] };
}


Vector Transforma::aplicaAPosicion (const Vector posicion) const {
	// este es el cálculo:
	float  sen  = std::sin (m_rotacion);
	float  cos  = std::cos (m_rotacion);
	Vector v_a {
			posicion.x () * cos - posicion.y () * sen + m_posicion.x () - m_origen.x (),
			posicion.y () * cos + posicion.x () * sen + m_posicion.y () - m_origen.y () };
	return v_a;
}


/// @endcond

