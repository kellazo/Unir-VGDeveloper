
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
// Archivo: Motor.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


void Motor::ejecuta (JuegoBase * juego) {
    //
    // Ejecuta el juego de principio a fin.        
    // La ejecución esta acotada entre dos llamadas a 'inicia' y 'termina'. Hay otras dos llamadas 
    // en cada iteración del bucle, 'actualiza' y 'presenta'.
    // 
    // Almacena el juego que se va a ejecutar.
    this->juego = juego;
    // El estado del juego debe ser activo.
    this->juego->ponEjecucion (EjecucionJuego::activo);
    //
    // Una instancia de 'Rendidor' se usa para presentar el juego en pantalla.
    this->rendidor = new Rendidor {};
    //
    // 'inicia' muestra la ventana del juego. También realiza la llamada al método 'inicia' del 
    // juego. 
    this->inicia ();
    //
    // 'ciclos' lleva la cuenta del número de iteraciones del bucle de juego.
    this->ciclos = 0;
    // 'tiempo' mide el tiempo desde el inicio de la ejecución.
    this->tiempo.inicia ();
    //
    // El bucle de juego.
    while (true) {
        //
        // Los ciclos comienzan por 1.
        this->ciclos++;
        //
        // El rendidor ha detectado el cierre de la ventana del juego. Se termina el juego.  
        if (rendidor->cerrado ()) {
            juego->ponEjecucion (EjecucionJuego::cancelado);
            break;
        }
        //
        // Comprueba la situación del teclado y del ratón en este momento y la almacena para ser 
        // consultada a continuación por los métodos 'actualiza' del juego y de los actores del 
        // juego. Hacerlo así evita problemas de tiempo con el doble-clic.
        Teclado::sondea ();
        Raton  ::sondea ();
        //
        // Inicia la medición parcial del tiempo de cada iteración del bucle.
        this->tiempo.arrancaCrono ();
        //
        // Indica en la consola que el motor está funcionando.
        std::cout << '.';
        //
        // 'actualiza' llama a los métodos 'actualiza' del juego y de los actores del juego.
        this->actualiza ();
        //
        // 'presenta' usa el rendidor para mostrar en pantalla el juego. Además, realiza una llamada 
        // al método 'presenta' de cada actor del juego.
        this->presenta ();
        //
        // Termina la medición parcial del tiempo. Es el tiempo usado para actualizar el estado del
        // juego y para presentalo en pantalla.
        this->tiempo.paraCrono ();
        //
        // Se comprueba si en 'actualiza' se ha cambiado el estado de ejecución.
        if (juego->ejecucion () == EjecucionJuego::cancelado ||
            juego->ejecucion () == EjecucionJuego::reinicio    ) {
            break;
        }
        //
        // Este bucle de juego realiza iteraciones en un tiempo predeterminado, con ello se consigue
        // un número constante de fps (frames per second). Además se evita que este sucesos alcance 
        // el 100% de uso de la CPU.
        // 
        // 'micrseg_ciclo' es el tiempo asignado a cada iteración de bucle, se resta el tiempo de la 
        // medición parcial y se obtiene el tiempo que hay que estar parado, en 'duracion'. 
        long duracion = micrseg_ciclo - this->tiempo.crono_micrseg ();
        if (duracion > 0) {
            //
            // Se detiene la ejecución durante el tiempo indicado por 'duracion'. Otros procesos del 
            // sistema tinene oportunidad de ejecutarse.
            Tiempo::duerme (duracion);
        }
    }
    //
    // La llamada a 'termina' cierra la ventana del juego tras llamar al método ‘termina' del juego.
    this->termina ();
    //
    delete this->rendidor;
}


void Motor::inicia () {
    std::cout << "Motor UNIR-2D arrancado.\n";        
    rendidor->abre (juego);
    juego->inicia ();
    Teclado::configura (rendidor);
    Raton::configura (rendidor);
}


void Motor::actualiza () {
    double segundos_tiempo = this->tiempo.segundos ();
    juego->preactualiza (segundos_tiempo);
    juego->actualizaActores (segundos_tiempo);
    juego->posactualiza (segundos_tiempo);
}


void Motor::presenta () {
    rendidor->limpia ();
    juego->presentaActores (rendidor);
    rendidor->muestra ();
}


void Motor::termina () {
    juego->termina ();
    rendidor->cierra ();
    std::cout << "\n";        
    std::cout << "Motor UNIR-2D parado.\n";        
    std::cout << "  tiempo " << this->tiempo.segundos () <<"s\n";
    std::cout << "  " << this->ciclos << " ciclos\n";
    std::cout << "  ciclo medio " << this->tiempo.mediaCrono_micrseg () << " microseg.\n";  //  μ  \u03BC
}

