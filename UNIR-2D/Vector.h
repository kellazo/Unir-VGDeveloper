
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
// Archivo: Vector.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


namespace unir2d {


    /// @brief Implementación de los vectores de dos dimensiones.
    /// @details Los vectores contiene dos componentes de tipo flotante denominados 'x' e 'y'.<p>
    /// Los vectores se usan para establecer posiciones en la pantalla, por tanto, miden píxeles.<p>
    /// Las instancias de la clase Vector son inmutables, sus componentes no se pueden modificar. 
    /// Para obtener un vector modificado a partir de otro vector, se debe ejecutar una operación 
    /// que crea y devuelve una instancia nueva.
    class Vector {
    public: 
        
        /// @brief Constructor del vector cero. 
        constexpr Vector ();

        /// @brief Construye un vector con los componentes indicados
        /// @param x componente 'x'.
        /// @param y componente 'y'.
        constexpr explicit Vector (float x, float y);

        /// @brief Construye un vector tomando como componentes las coordenadas indicadas.
        /// @details El componente 'fila' de 'coord' pasa a ser el componente 'y' del vector y el 
        /// componente 'coln' de 'coord' pasa a ser el componente 'x' del vector.
        /// @param coord Instancia de Coord de la que se toman los componentes del vector.
        explicit Vector (const Coord & coord);
       
        /// @brief Obtiene el componente 'x' del vector. 
        /// @return Componente 'x'.
        constexpr float x () const;        

        /// @brief Obtiene el componente 'y' del vector. 
        /// @return Componente 'y'.
        constexpr float y () const;

        /// @brief Operador de asignación y suma.
        /// @details Suma el vector de la instancia con el vector indicado y asigna el resultado a 
        /// la instancia.
        /// @param vector vector que se suma.
        /// @return Referencia a la intancia resultante.
        constexpr Vector & operator += (const Vector & vector);

        /// @brief Operador de asignación y resta.
        /// @details Resta al vector de la instancia el vector indicado y asigna el resultado a 
        /// la instancia.
        /// @param vector vector que se resta.
        /// @return Referencia a la intancia resultante.
        constexpr Vector & operator -= (const Vector & vector);

        /// @brief Operador de asignación y producto por un escalar.
        /// @details Multiplica el vector de la instancia por el escalar indicado y asigna el resultado a 
        /// la instancia.
        /// @param escalar valor escalar de la multiplicación.
        /// @return Referencia a la intancia resultante.
        constexpr Vector & operator *= (float escalar);
  
        /// @brief Indica si la instancia es el vector cero.
        /// @return Si es el vector cero.
        constexpr bool esCero () const;
      
    private:

        float comp_x;
        float comp_y;

        friend constexpr bool   operator == (const Vector & vector_1, const Vector & vector_2);
        friend constexpr bool   operator != (const Vector & vector_1, const Vector & vector_2);
        friend constexpr Vector operator +  (const Vector & vector_1, const Vector & vector_2);
        friend constexpr Vector operator +  (const Vector & vector);
        friend constexpr Vector operator -  (const Vector & vector_1, const Vector & vector_2);
        friend constexpr Vector operator -  (const Vector & vector);
        friend constexpr Vector operator *  (float escalar, const Vector & vector);
        friend           float  norma       (const Vector & vector);
        friend constexpr Vector transp      (const Vector & vector);

    };


    inline constexpr Vector::Vector () {
        comp_x = 0;
        comp_y = 0;
    };


    inline constexpr Vector::Vector (float x , float y) { 
        this->comp_x = x ; 
        this->comp_y = y;
    }


    inline Vector::Vector (const Coord & coord) {
        comp_x = (float) coord.coln ();
        comp_y = (float) coord.fila ();
    }
       

    inline constexpr float Vector::x () const {
        return comp_x;
    }


    inline constexpr float Vector::y () const {
        return comp_y;
    }


    inline constexpr Vector & Vector::operator += (const Vector & vector) {
        comp_x += vector.comp_x;
        comp_y += vector.comp_y;      
        return * this;
    }


    inline constexpr Vector & Vector::operator -= (const Vector & vector) {
        comp_x -= vector.comp_x;
        comp_y -= vector.comp_y;      
        return * this;
    }


    inline constexpr Vector & Vector::operator *= (float escalar) {
        comp_x *= escalar;
        comp_y *= escalar;      
        return * this;
    }


    inline constexpr bool Vector::esCero () const {
        return comp_x == 0 && comp_y == 0;
    } 


    /// @brief Operador de igualdad de vectores.
    /// @param vector_1 Primer vector.
    /// @param vector_2 Segundo vector.
    /// @return Si los vectores son iguales.
    inline constexpr bool operator == (const Vector & vector_1, const Vector & vector_2) {
        return vector_1.comp_x == vector_2.comp_x && 
               vector_1.comp_y == vector_2.comp_y;
    }


    /// @brief Operador de desigualdad de vectores.
    /// @param vector_1 Primer vector.
    /// @param vector_2 Segundo vector.
    /// @return Si los vectores son desiguales.
    inline constexpr bool operator != (const Vector & vector_1, const Vector & vector_2) {
        return vector_1.comp_x != vector_2.comp_x || 
               vector_1.comp_y != vector_2.comp_y;
    }


    /// @brief Operador de suma de vectores.
    /// @param vector_1 Primer vector.
    /// @param vector_2 Segundo vector.
    /// @return Suma de los vectores.
    inline constexpr Vector operator + (const Vector & vector_1, const Vector & vector_2) {
        return Vector {vector_1.comp_x + vector_2.comp_x, 
                       vector_1.comp_y + vector_2.comp_y };
    }


    /// @brief Operador unario de suma. No realiza ninguna operacion.
    /// @param vector El vector.
    /// @return El mismo vector.
    inline constexpr Vector operator + (const Vector & vector) {
        return Vector {vector.comp_x, 
                       vector.comp_y };
    }


    /// @brief Operador de resta de vectores.
    /// @param vector_1 Primer vector.
    /// @param vector_2 Segundo vector.
    /// @return Suma de los vectores.
    inline constexpr Vector operator - (const Vector & vector_1, const Vector & vector_2) {
        return Vector {vector_1.comp_x - vector_2.comp_x, 
                       vector_1.comp_y - vector_2.comp_y };
    }


    /// @brief Operador unario de cambio de signo.
    /// @param vector El vector.
    /// @return Opuesto de la suma.
    inline constexpr Vector operator - (const Vector & vector) {
        return Vector {- vector.comp_x, 
                       - vector.comp_y };
    }


    /// @brief Operador de producto por un escalar.
    /// @param escalar El escalar multiplicado.
    /// @param vector El vector multiplicado.
    /// @return Producto de escalar por vector.
    inline constexpr Vector operator * (float escalar, const Vector & vector) {
        return Vector {escalar * vector.comp_x, 
                       escalar * vector.comp_y };
    }


    /// @brief Calcula la norma (o longitud) del vector.
    /// @param vector El vector.
    /// @return La norma del vector.
    inline float norma (const Vector & vector) {        
        return std::hypot (vector.comp_x, vector.comp_y);        
    }


    /// @brief Devuelve el vector transpuesto, intercambiando x por y.
    /// @param vector El vector.
    /// @return El vector transpuesto.
    inline constexpr Vector transp (const Vector & vector) {
        return Vector {vector.comp_y, vector.comp_x};
    }


}