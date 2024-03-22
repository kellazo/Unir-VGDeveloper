
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
// Archivo: Motor.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once
  

namespace unir2d {


    /// @brief Ejecuta el juego definido en una instancia de una clase derivada de JuegoBase.
    /// @details Al ejecutar el juego aparece una ventana donde se desarrolla el juego y aparece 
    /// también la consola de Window donde se muestran los mensajes de ejecución del juego.
    class Motor {
    public:

        /// @brief Constructor por defecto.
        explicit Motor () = default;

        /// @brief Ejecuta el juego indicado.
        /// @param juego: instancia del juego que se ejecuta.
        void ejecuta (JuegoBase * juego);

    private:

        // Juego que se está ejecutando.
        JuegoBase * juego {};

        // Instancia de Rendidor que muestra en pantalla la situación del juego.
        Rendidor * rendidor {};

        // Constante que especifica la duración del ciclo en microsegundos.
        // 33333 microsegundos se corresponden a 30 fps (frames per second). 
        static constexpr long micrseg_ciclo = 33333;
        // Contador de ciclos de ejecución del juego.
        int ciclos {};
        // Instancia de Tiempo que controla el tiempo durante la ejecución del juego.
        Tiempo tiempo {};

        // No se pueden copiar ni mover las instancias de esta clase. 
        Motor (const Motor & )              = delete;
        Motor (Motor && )                   = delete;
        Motor & operator = (const Motor & ) = delete;
        Motor & operator = (Motor && )      = delete;

        // Métodos privados.
        void inicia ();
        void actualiza ();
        void presenta ();
        void termina();

    };


}


/// @class unir2d::Motor
/// 
/// Ejemplo de uso:
/// @code {.cpp}
/// int main () {
///     try {
///         // Se crea el juego.    
///         JuegoAnimacion * juego = new JuegoAnimacion {};
///         // Se crea el motor de juego. 
///         unir2d::Motor * motor = new unir2d::Motor {};
///         // El motor ejecuta el juego.
///         motor->ejecuta (juego);
///         // Se eliminan las instancias.
///         delete juego;
///         delete motor;
///     } catch (std::exception excepcion) {
///         std::cerr << "UNIR-2D :: Prueba de animación\n";
///         std::cerr << "    " << excepcion.what () << "\n";
///         std::this_thread::sleep_for (std::chrono::milliseconds (5000));
///     }
///     return 0;    
/// }
/// @endcode
