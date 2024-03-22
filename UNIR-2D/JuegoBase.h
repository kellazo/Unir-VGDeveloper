
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
// Archivo: JuegoBase.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.
   

#pragma once


namespace unir2d {


    class Motor;


    /// @brief Clase base de los microjuegos que funcionana mediante el motor de juego 'UNIR-2D'.
    /// @details Para crear un juego debe implementarse un clase derivada de esta. El juego se 
    /// ejecuta en una llamada al método Motor::ejecuta que toma como parámetro una instancia de 
    /// dicha clase derivada.<p>
    /// También deben implementarse una o más clases derivadas de ActorBase. Las instancias de las 
    /// clase derivadas de ActorBase deben incluirse en la lista que es mantenida por esta clase.<p>
    /// En determinados momentos de la ejecución del juego, la clase Motor realiza llamadas a los 
    /// métodos JuegoBase#inicia, JuegoBase#termina, JuegoBase#preactualiza y JuegoBase#posactualiza. 
    /// También realiza llamadas a los métodos ActorBase#inicia, ActorBase#termina y 
    /// ActorBase#actualiza. La programación del juego se realizar en las sustituciones (override) 
    /// de estos métodos que aparecen en las clases derivadas de JuegoBase y ActorBase.<p>
    /// Las instancias derivadas de esta clase mantienen un valor de la enumeración EjecucionJuego 
    /// que indica cual es el estado de ejecución del juego. El método Motor#ejecuta establece el 
    /// estado inicial como EjecucionJuego#activo. A continuación, si el ususario cierra la ventana 
    /// de presentación del juego, el estado pasa a ser EjecucionJuego#cancelado y la ejecución del 
    /// juego termina. Mediante programación se puede establecer el estado de ejecución del juego. 
    /// Tipicamente se hace en los métodos JuegoBase#preactualiza, JuegoBase#posactualiza o 
    /// ActorBase#actualiza. Si el estado pasa a ser EjecucionJuego#cancelado o 
    /// EjecucionJuego#reinicio, la ejecución del juego termina.
    class JuegoBase {
    public:

        /// @brief Obtiene la lista de instancias de clases derivadas de ActorBase mantenida por 
        /// esta instancia.
        /// @return La lista de instancias de clases derivadas de ActorBase.
        const std::vector<ActorBase *> & actores () const;

        /// @brief Agrega una instancia de una clase derivada de ActorBase a lista mantenida por 
        /// esta instancia.
        /// @details Tras agregar la instancia a la lista se realiza una llamada al método 
        /// ActorBase#inicia.
        /// 
        /// @param actor Actor agregado a la lista. 
        void agregaActor (ActorBase * actor);

        /// @brief Estrae el elemento indicado de la lista mantenida por esta instancia.
        /// @details Antes de extraer la instancia a la lista se realiza una llamada al método 
        /// ActorBase#termina.
        /// @param actor elemento extraido de la lista. 
        void extraeActor (ActorBase * actor);

        /// @brief Estrae todos los elementos la lista de instancias de ActorBase mantenida por esta 
        /// instancia.
        /// @details Antes de extraer los elementos de la lista se realizan llamadas a los métodos 
        /// ActorBase#termina para cada uno de ellos.
        void extraeActores ();

        /// @brief Obtiene el estado de ejecución del juego.
        /// @return Estado de ejecución del juego.
        EjecucionJuego ejecucion ();

        /// @brief Establece el estado de ejecución del juego.
        /// @param valor Estado de ejecución del juego.
        void ponEjecucion (EjecucionJuego valor);

    protected:

        /// @brief Constructor por defecto.
        explicit JuegoBase () = default;

        /// @brief Obtiene el título de la ventana de presentación del juego.
        /// @details Es un metodo virtual puro que debe ser reescrito en las clases derivadas. El 
        /// valor devuelto se usa para establecer el título de la ventana de presentación del juego.
        /// @return Título de la ventana del juego.
        virtual const std::wstring tituloVentana () const = 0;

        /// @brief Obtiene la posición y el tamano de la ventana de presentación del juego.
        /// @details Es un metodo virtual puro que debe ser reescrito en las clases derivadas. Los
        /// dos valores devueltos se usas para establecer la posición y el tamano de la ventana de 
        /// presentación del juego.
        /// @param posicion posición de la ventana.
        /// @param tamano tamano de la ventana.
        virtual void regionVentana (Vector & posicion, Vector & tamano) const = 0;
    
        /// @brief Método llamado por Motor al inicio de la ejecución del juego.
        /// @details Durante la ejecución del método Motor#ejecuta de la clase Motor se realiza una 
        /// llamada a este método virtual.<p>
        /// Por defecto, este método no realiza ninguna acción. Las clases derivadas deben sustituir 
        /// este método (usando 'override') para realizar las acciones oportunas.
        virtual void inicia ();

        /// @brief Método llamado por Motor al final de la ejecución del juego.
        /// @details Durante la ejecución del método Motor#ejecuta de la clase Motor se realiza una 
        /// llamada a este método virtual.<p>
        /// Por defecto, este método no realiza ninguna acción. Las clases derivadas deben sustituir 
        /// este método (usando 'override') para realizar las acciones oportunas.
	    virtual void termina ();
        
        /// @brief Método llamado por Motor al inicio de cada ciclo de la ejecución del juego.
        /// @details Durante la ejecución del método Motor#ejecuta se realizan llamada a este método 
        /// virtual en cada ciclo de ejecución del juego. La llamada se produce antes de realizar 
        /// las llamada a los métodos ActorBase#actualiza.<p>
        /// Por defecto, este método no realiza ninguna acción. Las clases derivadas deben sustituir 
        /// este método (usando 'override') para realizar las acciones oportunas. 
	    /// @param tiempo_seg: tiempo en segundos desde el inicio de la ejecución del juego. 
        virtual void preactualiza (double tiempo_seg);

        /// @brief Método llamado por Motor durante cada ciclo de la ejecución del juego.
        /// @details Durante la ejecución del método Motor#ejecuta se realizan llamada a este método 
        /// virtual en cada ciclo de ejecución del juego. La llamada se produce tras realizar las 
        /// llamada a los métodos ActorBase#actualiza.<p>
        /// Por defecto, este método no realiza ninguna acción. Las clases derivadas deben sustituir 
        /// este método (usando 'override') para realizar las acciones oportunas.
	    /// @param tiempo_seg: tiempo en segundos desde el inicio de la ejecución del juego. 
        virtual void posactualiza (double tiempo_seg);

        /// @brief Comprueba que todas las referencias mantenidas por esta instancia han quedado 
        /// anuladas. 
        /// @details Se usa para validar que, al final de la ejecución del juego, no quedan 
        /// instancias dependientes de él. Debe usarse solo para depurar el funcionamiento de esta 
        /// clase. 
        static void validaVacio ();

    private:

        std::vector<ActorBase *> m_actores {};  
        int indice_z_minimo {};

        EjecucionJuego m_ejecucion {EjecucionJuego::activo};

        bool permiso_actores {true};

        // los juegos no se pueden copiar ni mover       
        JuegoBase (const JuegoBase & )              = delete;
        JuegoBase (JuegoBase && )                   = delete;
        JuegoBase & operator = (const JuegoBase & ) = delete;
        JuegoBase & operator = (JuegoBase && )      = delete;

        void actualizaActores (double segundos_tiempo);
        void presentaActores (Rendidor * rendidor);

    private:

        friend class Motor;
        friend class Rendidor;

    };


    inline EjecucionJuego JuegoBase::ejecucion () {
        return m_ejecucion;
    }

    inline void JuegoBase::ponEjecucion (EjecucionJuego valor) {
        m_ejecucion = valor;
    }

    inline void JuegoBase::inicia () {
    }

    inline void JuegoBase::termina () {
    }

    inline void JuegoBase::preactualiza (double tiempo_seg) {
    }

    inline void JuegoBase::posactualiza (double tiempo_seg) {
    }

    inline const std::vector<ActorBase *> & JuegoBase::actores () const {
        return m_actores;
    }


}


/// @class unir2d::JuegoBase
/// 
/// Ejemplo de uso:
/// @code {.cpp}
/// // La clase JuegoAnimacion hereda de JuegoBase de UNIR-2D
/// class JuegoAnimacion : public JuegoBase {
/// private:
///     // El juego es el contenedor del actor.
///     ActorAnimacion * actor;

///     // Sustituye dos métodos de la clase base para configurar la ventana.
///     const std::wstring tituloVentana () const override;
///     void regionVentana (Vector & posicion, Vector & tamano) const override;
///     // El juego funciona sustituyendo dos métodos de la clase base.
///     void inicia () override;
///     void termina () override;
/// };
/// 
/// inline const std::wstring JuegoAnimacion::tituloVentana () const {
///     // Título de la ventana.
///     return L"UNIR2D :: Prueba de animación";
/// }
/// 
/// inline void JuegoAnimacion::regionVentana (Vector & posicion, Vector & tamano) const {
///     posicion = Vector {10, 10};
///     tamano   = Vector {800, 600};
/// }
/// 
/// // Sustituye al método de JuegoBase para preparar el juego.
/// inline void JuegoAnimacion::inicia () {
///     // Se crea el actor y se pone en la lista para que se renderize automáticamente.
///     actor = new ActorAnimacion {};
///     agregaActor (actor);
/// }
/// 
/// // Sustituye al método de JuegoBase para concluir el juego.
/// inline void JuegoAnimacion::termina () {
///     // Se quita el actor de la lista y se elimina.
///     extraeActor (actor);
///     delete actor;
/// }
/// @endcode
