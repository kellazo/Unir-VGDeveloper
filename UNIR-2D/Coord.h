
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
// Archivo: Coord.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


namespace unir2d {


    /// @brief Implementación del un par de coordenadas enteras.
    /// @details Las coordenadas contienen dos componentes de tipo entero denominados 'fila' y 
    /// 'coln'.<p>
    /// Las coordenadas se usan para establecer la posición las entidades en el tablero de juego. 
    /// Por tanto, no miden pixels de la pantalla.<p>
    /// Las instancias de la clase Coord son inmutables, sus componentes no se pueden modificar. 
    /// Para obtener unas coordenadas modificada, se debe ejecutar una operación que crea y devuelve 
    /// una instancia nueva.
    class Coord {
    public: 
        
        /// @brief constructor de las coordenadas cero.
        constexpr Coord ();

        /// @brief Construye unas coordenadas con los componentes indicados.
        /// @param fila componente 'fila'.
        /// @param coln componente 'coln'.
        constexpr explicit Coord (int fila, int coln);
        
        /// @brief Obtiene el componente 'fila' de las coordenadas. 
        /// @return Componente 'fila'.
        constexpr int fila () const;        

        /// @brief Obtiene el componente 'coln' de las coordenadas. 
        /// @return Componente 'coln'.
        constexpr int coln () const;

        /// @brief Operador de asignación y suma.
        /// @details Suma las coordenadas de la instancia con las coordenadas indicadas y asigna el 
        /// resultado a la instancia.
        /// @param coord Coordenadas que se suman.
        /// @return Referencia a la intancia resultante.
        constexpr Coord & operator += (const Coord & coord);

        /// @brief Operador de asignación y resta.
        /// @details Resta a las coordenadas de la instancia las coordenadas indicadas y asigna el 
        /// resultado a la instancia.
        /// @param coord Coordenadas que se restan.
        /// @return Referencia a la intancia resultante.
        constexpr Coord & operator -= (const Coord & coord);
  
        /// @brief Operador de asignación y producto escalar.
        /// @details Multiplica las coordenadas de la instancia por el escalar indicadas y asigna el 
        /// resultado a la instancia.
        /// @param escalar Escalar por el que se multiplica.
        /// @return Referencia a la intancia resultante.
        constexpr Coord & operator *= (int escalar);
  
        /// @brief Indica si la instancia es las coordenadas cero.
        /// @return Si es las coordenadas cero.
        constexpr bool esCero () const;
      
    private:

        int m_fila;
        int m_coln;

        friend constexpr bool  operator == (const Coord & valor_1, const Coord & valor_2);
        friend constexpr bool  operator != (const Coord & valor_1, const Coord & valor_2);
        friend constexpr Coord operator +  (const Coord & valor_1, const Coord & valor_2);
        friend constexpr Coord operator +  (const Coord & valor);
        friend constexpr Coord operator -  (const Coord & valor_1, const Coord & valor_2);
        friend constexpr Coord operator -  (const Coord & valor);
        friend constexpr Coord operator *  (int escalar, const Coord & valor);
        friend           float norma       (const Coord & valor);
        // Orden lexicográfico. Para que funcionen las colecciones (p.ej. std::map).
        friend constexpr bool  operator <  (const Coord & valor_1, const Coord & valor_2);
        friend constexpr bool  operator >  (const Coord & valor_1, const Coord & valor_2);
        friend constexpr bool  operator <= (const Coord & valor_1, const Coord & valor_2);
        friend constexpr bool  operator >= (const Coord & valor_1, const Coord & valor_2);

    };


    inline constexpr Coord::Coord () {
        m_fila = 0;
        m_coln = 0;
    };

    inline constexpr Coord::Coord (int fila, int coln) { 
        this->m_fila = fila ; 
        this->m_coln = coln;
    }

    inline constexpr int Coord::fila () const {
        return m_fila;
    }

    inline constexpr int Coord::coln () const {
        return m_coln;
    }

    inline constexpr Coord & Coord::operator += (const Coord & valor) {
        m_fila += valor.m_fila;
        m_coln += valor.m_coln;      
        return * this;
    }

    inline constexpr Coord & Coord::operator -= (const Coord & valor) {
        m_fila -= valor.m_fila;
        m_coln -= valor.m_coln;      
        return * this;
    }

    inline constexpr Coord & Coord::operator *= (int escalar) {
        m_fila *= escalar;
        m_coln *= escalar;      
        return * this;
    }

    inline constexpr bool Coord::esCero () const {
        return m_fila == 0 && m_coln == 0;
    } 

    /// @brief Operador de igualdad de coordenadas.
    /// @param valor_1 Primeras coordenadas.
    /// @param valor_2 Segundas coordenadas.
    /// @return Si las coordenadas son iguales.
    inline constexpr bool operator == (const Coord & valor_1, const Coord & valor_2) {
        return valor_1.m_fila == valor_2.m_fila && 
               valor_1.m_coln == valor_2.m_coln;
    }

    /// @brief Operador de desigualdad de coordenadas.
    /// @param valor_1 Primeras coordenadas.
    /// @param valor_2 Segundas coordenadas.
    /// @return Si las coordenadas son desiguales.
    inline constexpr bool operator != (const Coord & valor_1, const Coord & valor_2) {
        return valor_1.m_fila != valor_2.m_fila || 
               valor_1.m_coln != valor_2.m_coln;
    }

    /// @brief Operador de suma de coordenadas.
    /// @param valor_1 Primeras coordenadas.
    /// @param valor_2 Segundas coordenadas.
    /// @return Suma de las coordenadas.
    inline constexpr Coord operator + (const Coord & valor_1, const Coord & valor_2) {
        return Coord {valor_1.m_fila + valor_2.m_fila, 
                      valor_1.m_coln + valor_2.m_coln };
    }

    /// @brief Operador unario de suma. No realiza ninguna operacion.
    /// @param valor Coordenadas.
    /// @return La misma instancia.
    inline constexpr Coord operator + (const Coord & valor) {
        return Coord {valor.m_fila, 
                      valor.m_coln };
    }

    /// @brief Operador de resta de coordenadas.
    /// @param valor_1 Primeras coordenadas.
    /// @param valor_2 Segundas coordenadas.
    /// @return Resta de las coordenadas.
    inline constexpr Coord operator - (const Coord & valor_1, const Coord & valor_2) {
        return Coord {valor_1.m_fila - valor_2.m_fila, 
                      valor_1.m_coln - valor_2.m_coln };
    }

    /// @brief Operador unario de cambio de signo.
    /// @param valor Coordenadas.
    /// @return Opuesto de la suma.
    inline constexpr Coord operator - (const Coord & valor) {
        return Coord {- valor.m_fila, 
                      - valor.m_coln };
    }

    /// @brief Operador de multiplicación por escalar.
    /// @param escalar Escalar multiplicado.
    /// @param valor Coordenadas multiplicadas.
    /// @return Coordenadas resultantes.
    inline constexpr Coord operator * (int escalar, const Coord & valor) {
        return Coord {escalar * valor.m_fila, 
                      escalar * valor.m_coln };
    }

    /// @brief Calcula la norma (o longitud) de las coordenadas.
    /// @param valor: Coordenadas.
    /// @return La norma del vector
    inline float norma (const Coord & valor) {
        return std::hypot ((float) valor.m_fila, (float) valor.m_coln);        
    }

    /// @brief Operador menor lexicográfico.
    /// @details Esta operación se usa unicamente para que las instancias se puedan usar en las 
    /// colecciones ordenadas (p.ej: std::map). 
    /// @param valor_1 Primer operando
    /// @param valor_2 Segundo operando
    /// @return Si es menor (lexicográficamente).
    inline constexpr bool operator < (const Coord & valor_1, const Coord & valor_2) {
        if (valor_1.m_fila < valor_2.m_fila) {
            return true;
        }
        if (valor_1.m_fila > valor_2.m_fila) {
            return false;
        }
        return valor_1.m_coln < valor_2.m_coln;
    }

    /// @brief Operador mayor lexicográfico.
    /// @details Esta operación se usa unicamente para que las instancias se puedan usar en las 
    /// colecciones ordenadas (p.ej: std::map). 
    /// @param valor_1 Primer operando
    /// @param valor_2 Segundo operando
    /// @return Si es mayor (lexicográficamente).
    inline constexpr bool operator > (const Coord & valor_1, const Coord & valor_2) {
        if (valor_1.m_fila > valor_2.m_fila) {
            return true;
        }
        if (valor_1.m_fila < valor_2.m_fila) {
            return false;
        }
        return valor_1.m_coln > valor_2.m_coln;
    }

    /// @brief Operador menor o igual lexicográfico.
    /// @details Esta operación se usa unicamente para que las instancias se puedan usar en las 
    /// colecciones ordenadas (p.ej: std::map). 
    /// @param valor_1 Primer operando
    /// @param valor_2 Segundo operando
    /// @return Si es menor o igual (lexicográficamente).
    inline constexpr bool operator <= (const Coord & valor_1, const Coord & valor_2) {
        if (valor_1.m_fila < valor_2.m_fila) {
            return true;
        }
        if (valor_1.m_fila > valor_2.m_fila) {
            return false;
        }
        return valor_1.m_coln <= valor_2.m_coln;
    }

    /// @brief Operador mayor o igual lexicográfico.
    /// @details Esta operación se usa unicamente para que las instancias se puedan usar en las 
    /// colecciones ordenadas (p.ej: std::map). 
    /// @param valor_1 Primer operando
    /// @param valor_2 Segundo operando
    /// @return Si es mayor o igual (lexicográficamente).
    inline constexpr bool operator >= (const Coord & valor_1, const Coord & valor_2) {
        if (valor_1.m_fila > valor_2.m_fila) {
            return true;
        }
        if (valor_1.m_fila < valor_2.m_fila) {
            return false;
        }
        return valor_1.m_coln >= valor_2.m_coln;
    }


}
