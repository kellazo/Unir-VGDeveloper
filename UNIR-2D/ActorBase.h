
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
// Archivo: ActorBase.h
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. Documentado.

 
#pragma once


namespace unir2d {


    class Rendidor;


    /// @brief Clase base de todas las entidades relevantes del juego, que se denominan actores.
    /// @details Todos las instancias de las clases derivadas de ActorBase deben aparecer en una 
    /// lista contenida en la instancia de la clase derivada de JuegoBase.<p>
    /// Esta clase mantiene una lista de instancias de clases derivadas de Dibujable. Son instancias 
    /// de las clases Baldosas, Circulo, Imagen, Malla, Rectangulo, Texto y Trazos. Las instancias 
    /// que aparecen en la lista se presentan en pantalla automáticamete.<p>
    /// En determinados momentos de la ejecución del juego, la clase Motor realiza llamadas a los 
    /// métodos ActorBase#inicia, ActorBase#termina y ActorBase#actualiza. También realiza llamadas 
    /// a los métodos JuegoBase#inicia, JuegoBase#termina, JuegoBase#preactualiza y 
    /// JuegoBase#posactualiza. La programación del juego se realizar en las sustituciones 
    /// (override) de estos métodos que aparecen en las clases derivadas de JuegoBase y ActorBase.<p>
    /// Los actores se situan en la pantalla del juego en una posición determinada, que se establece 
    /// mediante un Vector. El origen de la pantalla se situa en la esquina superior izquierda, el 
    /// sentido del eje vertical es hacia abajo. Los actores también pueden aparecer rotados en la 
    /// pantalla, con un ángulo de rotación indicado en radianes. El sentido de la rotación es el de 
    /// las agujas del reloj.
    class ActorBase {
    public:

        /// @brief Obtiene la posición del actor en la pantalla del juego.
        /// @return Posición del actor.
        Vector posicion () const;

        /// @brief Establece la posición del actor en la pantalla del juego.
        /// @param valor posición del actor.
        void ponPosicion (Vector valor);

        /// @brief Obtiene el ángulo de rotación del actor en la pantalla del juego.
        /// @return Rotación del actor en radianes.
        float rotacion ();

        /// @brief Establece la rotación del actor en la pantalla del juego.
        /// @param radianes angulo de rotación.
        void ponRotacion (float radianes);

        /// @brief Obtiene la lista de instancias de Dibujable contenidas en esta instancia.
        /// @details Las instancias de dibujable de la lista se presentan en pantalla 
        /// automáticamente durante la presentación del actor.
        /// @return Lista de instancias de Dibujable.
        const std::vector<Dibujable *> & dibujos () const;

        /// @brief Agrega un elemento derivado de la clase Dibujable a la lista contenida en esta 
        /// instancia.
        /// @param dibujo elemento dibujable.
        void agregaDibujo (Dibujable * dibujo);

        /// @brief Extrae el elemento indicado de la lista de contenida en esta instancia.
        /// @param dibujo elemento a extraer de la lista.
        void extraeDibujo (Dibujable * dibujo);

        /// @brief Extrae todos los elementos de la lista de instancias de la clase Dibujable 
        /// contenida en esta instancia.
        void extraeDibujos ();

    protected:

        /// @brief Constructor.
        explicit ActorBase ();

        /// @brief Destructor.
        ~ActorBase ();

	    /// @brief Método llamado por Motor cuando se agrega la instancia a la lista de actores del 
        /// juego.
        /// @details Durante la ejecución del método JuegoBase#agregaActor se realiza una llamada a 
        /// este método virtual.<p>
        /// Por defecto, este método no realiza ninguna acción. Las clases derivadas deben sustituir 
        /// este método (usando 'override') para realizar las acciones oportunas.
	    virtual void inicia ();

	    /// @brief Método llamado por Motor cuando el se extrae la instancia de la lista de actores 
        /// del juego.
        /// @details Durante la ejecución del método JuegoBase#extraeActor o JuegoBase#extraeActores 
        /// se realiza una llamada a este método virtual.<p>
        /// Por defecto, este método no realiza ninguna acción. Las clases derivadas deben sustituir 
        /// este método (usando 'override') para realizar las acciones oportunas.
	    virtual void termina ();

	    /// @brief Método llamado por Motor durante cada ciclo de la ejecución del juego.
        /// @details Durante la ejecución del método Motor#ejecuta se realizan llamada a este método 
        /// virtual en cada ciclo de ejecución del juego. La llamada se produce entre las llamadas a
        /// los métodos JuegoBase#preactualiza y JuegoBase#posactualiza.<p>
        /// Por defecto, este método no realiza ninguna acción. Las clases derivadas deben sustituir 
        /// este método (usando 'override') para realizar las acciones oportunas.
	    /// @param tiempo_seg: tiempo en segundos desde el inicio de la ejecución del juego. 
	    virtual void actualiza (double tiempo_seg);

        /// @brief Muestra unas marcas en pantalla durante la presentación del actor.
        /// @details Debe usarse solo para depurar errores de programación.
        void ponDiana ();

    private: 

        Transforma m_transforma {};
        std::vector <Dibujable *> m_dibujos {};   
        int presentados {};
        bool diana {false};

        inline static int cuenta_instancias {};

        // los actores no se pueden copiar ni mover       
        ActorBase (const ActorBase & )              = delete;
        ActorBase (ActorBase && )                   = delete;
        ActorBase & operator = (const ActorBase & ) = delete;
        ActorBase & operator = (ActorBase && )      = delete;

        virtual void presenta (Rendidor * rendidor, int z_indice);
       
        void dibujaDiana (Rendidor * rendidor);


        friend class JuegoBase;

    };


    inline ActorBase::ActorBase () {
        cuenta_instancias ++;
    }

    inline ActorBase::~ActorBase () {
        cuenta_instancias --;
    }

    inline Vector ActorBase::posicion () const {
        return m_transforma.posicion ();
    }

    inline void ActorBase::ponPosicion (Vector valor) {
        this->m_transforma.ponPosicion (valor);
    }

    inline float ActorBase::rotacion () {
        return m_transforma.rotacion ();
    }

    inline void ActorBase::ponRotacion (float grados) {
        m_transforma.ponRotacion (grados);
    }

    inline const std::vector<Dibujable *> & ActorBase::dibujos () const {
        return m_dibujos;
    }

    inline void ActorBase::ponDiana () {
        diana = true;
    }


}


/// @class unir2d::ActorBase
/// 
/// Ejemplo de uso:
/// @code {.cpp}
/// // La clase ActorAnimacion hereda de ActorBase de UNIR-2D
/// class ActorAnimacion : public ActorBase {
/// private:
///     // Usa una instancia de Textura para almacenar la imagen.
///     Textura * textura;
///     // Usa una instancia de Imagen para presentar la imagen en pantalla.
///     Imagen * imagen;
/// 
///     // El actor funciona sustituyendo tres métodos de la clase base.
///     void inicia () override;
///     void termina () override;
///     void actualiza (double tiempo_seg) override;
/// };
/// 
/// // Sustituye al método de ActorBase para preparar el actor.
/// void ActorAnimacion::inicia () {
///     // Crea la textura para alamacenar la imagen.
///     textura = new Textura {};
///     // Camino del archivo en el SO.
///     std::filesystem::path archivo = std::filesystem::current_path();
///     archivo = archivo / "imagenes" / "Horse_Walk.png";
///     // Carga la textura del archivo.
///     textura->carga (archivo);
///     // Crea la imagen con la que el actor aparecerá en pantalla.
///     imagen = new Imagen {};
///     // La imagen usará la textura.
///     imagen->asigna (textura);
///     // Al poner la textura en la lista del actor se renderizará automáticamente.
///     agregaDibujo (imagen);
///     // En la imagen hay 8 estampas en una fila.
///     imagen->defineEstampas (1, 8);
///     // Situa al actor en la ventana.
///     this->ponPosicion (Vector {100, 100});
/// }
/// 
/// // Sustituye al método de ActorBase para eliminar el actor.
/// void ActorAnimacion::termina () {
///     // Vacía la lista de dibujables.
///     extraeDibujos ();
///     // Elimina el dibujo.
///     delete imagen;
///     // Elimina la textura.
///     delete textura;
/// }
/// 
/// // Sustituye al método de ActorBase para establecer el estado del actor en cada 
/// // ciclo del juego.
/// void ActorAnimacion::actualiza (double tiempo_seg) {
///     // No se puede cambiar la estampa de la textura en cada ciclo, iría muy rapido.
///     // Se hace en funcion del tiempo de juego.
///     int indice = ((int) (tiempo_seg * 10)) % 8 + 1;
///     // Sellecciona la estampa.
///     imagen->seleccionaEstampa (1, indice);
/// }
/// @endcode

