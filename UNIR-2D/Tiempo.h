
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
// Archivo: Tiempo.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.


#pragma once


namespace unir2d {


    /// @brief Realiza mediciones de tiempo.
    /// @details Esta clase mantiene un contador de tiempo global y un contador de tiempo parcial, 
    /// denominado cronómetro. También mantiene un contador para la media de las mediciones del
    /// cronómetro.<p>
    /// Esta clase es usada internamente por la clase Motor.
    class Tiempo {
    public:

        /// @brief Inicia la medición global del tiempo.
        void inicia ();

        /// @brief Termina la medición global del tiempo.
        void termina ();

        /// @brief Indica si la medición global del tiempo se ha iniciado.
        /// @return La medición global del tiempo se ha iniciado.
        bool iniciado () const;

        /// @brief Segundos transcurridos desde el inicio de la medición global del tiempo.
        /// @details Las llamadas al método Termina() no cambian la medición del tiempo.
        /// @return Segundos transcurridos.
        double segundos () const;

        /// @brief Inicia una medición con el cronómetro.
        void arrancaCrono (); 

        /// @brief Termina una medición con el cronómetro.
        void paraCrono ();

        /// @brief Indica si una medición del cronómetro se ha iniciado y no se ha terminado. 
        /// @return Una medición del cronometro se ha iniciado.
        bool cronometrando () const;

        /// @brief El tiempo transcurrido en la última medición del cronómetro.
        /// @details Solo se obtiene un resultado si la medición con el cronómetro se ha iniciado y 
        /// se ha terminado.
        /// @return Segundos transcurridos.
        long crono_segundos () const;

        /// @brief El tiempo transcurrido en la última medición del cronómetro.
        /// @details Solo se obtiene un resultado si la medición con el cronómetro se ha iniciado y 
        /// se ha terminado.
        /// @return Microsegundos transcurridos.
        long crono_micrseg () const;

        /// @brief Media de los tiempos medidos por el cronómetro.
        /// @details Las mediciones realizadas con el cronometro se acumulan para realizar la media. 
        /// @return La media de mediciones.
        long mediaCrono_micrseg () const;

        /// @brief Detiene la ejecución del juego durante el tiempo indicado (en milisegundos).
        /// @param milisegundos El tiempo de detención.
        static void duerme (int milisegundos);

    private:    

        using Momento = std::chrono::time_point<std::chrono::steady_clock>;
        using Duracion = std::chrono::nanoseconds;

        bool    iniciado_ {};
        Momento inicio_tiempo {};
        bool    cronometrando_ {};
        Momento inicio_crono {};

        std::chrono::microseconds tiempo_crono {}; 
        int periodos_crono {};
        std::chrono::microseconds acumulado_crono {};        

    };


    inline void Tiempo::inicia () {
        iniciado_ = true;
        inicio_tiempo = std::chrono::steady_clock::now ();
    }
    
    inline void Tiempo::termina () {
        iniciado_ = false;
    }

    inline bool Tiempo::iniciado () const {
        return iniciado_;
    }

    inline double Tiempo::segundos () const {
        Duracion duracion = std::chrono::steady_clock::now () - inicio_tiempo;        
        std::chrono::duration<double> segundos = 
                std::chrono::duration_cast <std::chrono::duration <double>> (duracion);
        return segundos.count ();
    }

    inline void Tiempo::arrancaCrono () {
        cronometrando_ = true;
        inicio_crono = std::chrono::steady_clock::now ();
    }
 
    inline void Tiempo::paraCrono () {
        Duracion duracion = std::chrono::steady_clock::now () - inicio_crono;        
        tiempo_crono = std::chrono::duration_cast <std::chrono::microseconds> (duracion);
        periodos_crono ++;
        acumulado_crono += tiempo_crono;
        cronometrando_ = false;
    }

    inline bool Tiempo::cronometrando () const {
        return cronometrando_;
    }

    inline long Tiempo::crono_segundos () const {
        return (long) (tiempo_crono.count () / 1000000) ;
    } 
        
    inline long Tiempo::crono_micrseg () const {
        return (long) tiempo_crono.count ();
    } 
        
    inline long Tiempo::mediaCrono_micrseg () const  {
        if (periodos_crono == 0) {
            return 0;
        }
        return (long) (acumulado_crono / periodos_crono).count ();
    }

    inline void Tiempo::duerme (int microsegundos) {
        std::this_thread::sleep_for (std::chrono::microseconds (microsegundos));
    }


}
