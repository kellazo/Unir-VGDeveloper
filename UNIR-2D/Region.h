
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
// Estado:  Terminado. Revisado. No documentado.


#pragma once


namespace unir2d {


    /// @brief Especifica una región formada por una posición y unas dimensiones. 
    /// @details Las regiones contienen 4 componentes de tipo flotante denominados 'x', 'y' (para la 
    /// posición), 'alto' y 'ancho' (para las dimensiones). Las regiones se usan para establecer 
    /// posiciones en la pantalla, por tanto miden píxeles.<p> 
    /// Las instancias de la clase Region son inmutables, sus componentes no se pueden modificar. 
    /// Para obtener una región modificada a partir de otra región, se debe ejecutar una operación 
    /// que crea y devuelve una instancia nueva.
    /// <p>
    class Region {
    public: 
        
        /// @brief Constructor de una región con valores cero en sus componentes. 
        constexpr Region ();

        /// @brief Construye un una región con los componentes indicados.
        /// @param x Componente 'x'.
        /// @param y Componente 'y'.
        /// @param ancho Componente 'ancho'.
        /// @param alto Componente 'alto'. 
        constexpr explicit Region (float x, float y, float ancho, float alto);

        /// @brief Constructor de una región que toma sus componentes de los parámetros.
        /// @details Los componentes 'x' e 'y' se toman de 'posicion'. Y los componentes 'ancho' y 
        /// 'alto' se toman de 'tamano'.
        /// @param posicion Vector para los componente 'x' e 'y'.
        /// @param tamano Vector para los componentes 'ancho' y 'alto'.
        explicit constexpr Region (const Vector & posicion, const Vector & tamano);
       
        /// @brief Obtiene el componente 'x' de la región. 
        /// @return Componente 'x'.
        constexpr float x () const;        

        /// @brief Obtiene el componente 'y' de la región. 
        /// @return Componente 'y'.
        constexpr float y () const;

        /// @brief Obtiene el componente 'ancho' de la región. 
        /// @return Componente 'ancho'.
        constexpr float ancho () const;

        /// @brief Obtiene el componente 'alto' de la región. 
        /// @return Componente 'alto'.
        constexpr float alto () const;

        /// @brief Obtiene un valor de Vector para la posición de la región. 
        /// @details La posición se obtiene a partir de los componente 'x' e 'y' de la región. 
        /// @return Vector con la posición de la regíon.
        constexpr Vector posicion () const;

        /// @brief Obtiene un valor de Vector para las dimesiones de la región. 
        /// @details Las dimensiones se obtienen a partir de los componente 'ancho' y 'alto' de la 
        /// región. 
        /// @return Vector con las dimensiones de la regíon.
        constexpr Vector tamano () const;

        /// @brief Indica si una posición está dentro de esta región.
        /// @param posicion Posición que se verifica.
        /// @return Indica si la posición está dentro de esta región.
        constexpr bool contiene (const Vector & posicion);

    private:

        Vector m_posicion;
        Vector m_tamano;

        friend constexpr bool operator == (const Region & region_1, const Region & region_2);
        friend constexpr bool operator != (const Region & region_1, const Region & region_2);

    };


    inline constexpr Region::Region () :
        m_posicion {}, m_tamano {} {
    }

    inline constexpr Region::Region (float x, float y, float ancho, float alto) :
        m_posicion {x, y}, m_tamano {ancho, alto} {
    }

    inline constexpr Region::Region (const Vector & posicion, const Vector & tamano) :
        m_posicion {posicion}, m_tamano {tamano} {
    }
       
    inline constexpr float Region::x () const {
        return m_posicion.x ();
    }        

    inline constexpr float Region::y () const {
        return m_posicion.y ();
    }

    inline constexpr float Region::ancho () const {
        return m_tamano.x ();
    }

    inline constexpr float Region::alto () const {
        return m_tamano.y ();
    }

    inline constexpr Vector Region::posicion () const {
        return m_posicion;
    }

    inline constexpr Vector Region::tamano () const {
        return m_tamano;
    }

    inline constexpr bool operator == (const Region & region_1, const Region & region_2) {
        return region_1.m_posicion == region_2.m_posicion && 
               region_1.m_tamano   == region_2.m_tamano;
    }

    inline constexpr bool operator != (const Region & region_1, const Region & region_2) {
        return region_1.m_posicion != region_2.m_posicion || 
               region_1.m_tamano   != region_2.m_tamano;
    }

    inline constexpr bool Region::contiene (const Vector & posicion) {
        return 
            m_posicion.x () <= posicion.x () && 
                    posicion.x () <= m_posicion.x () + m_tamano.x () &&
            m_posicion.y () <= posicion.y () && 
                    posicion.y () <= m_posicion.y () + m_tamano.y ()   ;
    }

}
