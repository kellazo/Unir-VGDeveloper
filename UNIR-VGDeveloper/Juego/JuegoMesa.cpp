// proyecto: Grupal/Juego
// arhivo:   JuegoMesa.cpp
// versión:  1.1  (9-Ene-2023)


#include "juego.h"


namespace juego {


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Primera sección - Los recursos

    En esta sección se establecen las carpetas en las que aparecen los recursos usados por el 
    juego, incluyendo las imágenes que aparecen en pantalla y los sonidos que se escuchan. Hay 
    una carpeta separada para los retratos de los personajes y otra para las imágenes de las 
    habilidades.

    Las carpetas están situadas en la carpeta donde están los archivos de código fuente del 
    proyecto.

    En principio no es necesario hacer ningún cambio en esta sección, si los recursos que se 
    cambian se sitúan en las mismas carpetas.

    *******************************************************************************************/
    string JuegoMesa::carpeta_activos_juego  {"../Assets/Art/Sprites/Environment/"};
    string JuegoMesa::carpeta_retratos_juego {"../Assets/Art/Sprites/Characters/"};
    string JuegoMesa::carpeta_habilids_juego {"../Assets/Art/Sprites/VFXs/"};
    string JuegoMesa::carpeta_sonidos_juego  {"../Assets/Audio/"};
    /*******************************************************************************************
    /******************************************************************************************/


    const std::wstring JuegoMesa::tituloVentana () const {
        return L"UNIR-2D :: Juego de Mesa";
    }


    JuegoMesa::JuegoMesa () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Segunda sección - El modo del juego

        En esta sección se configura el modo general del juego, es decir como se suceden las 
        jugadas, los turnos y las rondas. Y como se establece el personaje que realiza cada jugada.  

        La configuración del modo del juego se realiza mediante la elección de alguno de los
        modos preestablecidos. Es la única forma de configurar el modo del juego.

        Hay tres modos de juego preestablecidos:

            1) Modo de juego por pares
            2) Modo de juego por equipos
            3) Modo de juego libre de doble jugada

        Las siguientes definiciones se aplican a todos los modos de juego:

        Jugada:   
            Es una acción realizada con uno de los personajes. Puede ser un desplazamiento o la
            aplicación de una habilidad.

        Turno:
            Es una secuencia de jugadas realizadas por un grupo de personajes, normalmente 
            alternando a los dos equipos. los turnos se inician con la elección de los personajes 
            que van a participar en el turno, aunque en algunos modos de juego estos están 
            preestablecidos.

        Ronda:
            Es una secuencia de turnos en las que intervienen todos los personajes y que se 
            prolongan hasta que los personajes no pueden continuar, por haber perdido sus puntos de 
            acción o por haber perdido su vitalidad. Al inicio de la ronda, se recuperan los puntos 
            de acción de todos los personajes.

        Partida:
            Está formada por una secuencia de rondas. La partida termina cuando todos los personajes 
            de un equipo pierden su vitalidad. El otro equipo es el ganador.


        Modo de juego por pares
        --------------------------
        
        En este modo debe haber el mismo número de personajes en cada equipo.

        los turnos comienzan con los jugadores eligiendo un personaje de cada equipo. El primer 
        personaje en jugar es el que tiene más iniciativa, y en caso de tener la misma, se elige al 
        azar. A continuación se suceden las jugadas, alternando los dos personajes. 

        Cuando un personaje pierde sus puntos de acción o su vitalidad, el turno continua solo con 
        el otro. Y cuando lo pierden los dos, el turno termina.

        En el nuevo turno los jugador elige de nuevo a los dos personajes, evitando a los que han
        perdido sus puntos de acción o vitalidad.

        Cuando todos los personajes han perdido sus puntos de acción o su vitalidad, termina la 
        ronda.


        Modo de juego por equipos
        ----------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un orden de juego para los personajes. Se toman los 
        personajes según aparecen en el tablero, de arriba a abajo, alternando los dos equipos. El 
        primero de los personajes será el que tenga más iniciativa de los dos primeros, eligiéndolos 
        al azar si coinciden. 
        
        Un turno consiste en una jugada de cada personaje, tomándolos en el orden de la lista y se 
        prolonga hasta que juega el último de los personajes de la lista. Si un personaje ha perdido 
        sus puntos de acción o su vitalidad, la jugada es nula y se pasa al siguiente personaje de 
        la lista. 
        
        Los turnos se suceden hasta que todos los personajes han perdido sus puntos de acción o su 
        vitalidad, momento en que se inicia el siguiente ronda.


        Modo de juego libre de doble jugada
        --------------------------------------

        En este modo debe haber el mismo número de personajes en cada equipo.

        Al principio de la partida se establece un equipo inicial, tomando el que tiene el personaje 
        con más iniciativa o eligiéndolo al azar si coinciden. A continuación se alternan turnos de 
        uno y otro equipo. 
        
        Al principio de cada turno, el jugador elije un personaje del equipo correspondiente. El 
        turno consiste en dos jugadas seguidas del mismo personaje, tras las cuales se pasa a el 
        siguiente turno, en la que el jugador elige un personaje del otro equipo. Si un personaje 
        ha perdido sus puntos de acción o su vitalidad, no puede ser elegido.

        Cuando todos los personajes de un equipo han perdido sus puntos de acción o vitalidad, 
        termina el turno (a pesar de que el otro equipo si pueda continuar).


        Programación
        ------------

        Para cambiar el modo del juego es suficiente con cambiar los identificadores usados en 
        las dos líneas de código siguientes. Debe aparecer una de estas tres parejas:

            · ModoJuegoPares       SucesosJuegoPares       
            · ModoJuegoEquipo      SucesosJuegoEquipo    
            · ModoJuegoLibreDoble  SucesosJuegoLibreDoble
            · ModoJuegoKBM         SucesosJuegoKBM         NEW! (Personalizado para Kid, Bikes and Monsters)

        *******************************************************************************************/
        ModoJuegoKBM    * modo    = new ModoJuegoKBM {this};
        SucesosJuegoKBM * sucesos = new SucesosJuegoKBM {this, modo};
        /*******************************************************************************************
        /******************************************************************************************/
        //
        JuegoMesaBase::configura (sucesos, modo);
    }


    /*******************************************************************************************
    /*******************************************************************************************
        
    CONFIGURACIÓN DEL JUEGO
    Tercera sección - El tablero - Primera parte

    En esta sección se preparan los muros que aparecen en el tablero de juego.

    En el juego aparecen imágenes que muestran muros que ocupan algunas casillas hexagonales
    del tablero. Los jugadores no pueden situar a los personajes sobre los muros, ni 
    atravesarlos. Tampoco pueden realizar ataque a través de los muros (excepto si están 
    marcados como ataques indirectos).  

    Existen muchas posibilidades de diseño para los muros. Es posible que los muros se usen solo
    para delimitar un área del tablero, como ocurre con el ejemplo que aparece a continuación,
    llamado 'grafico_muros_area_central'. Otra posibilidad es diseñar una especie de laberinto
    con pasillos y cámaras, como en el ejemplo: 'grafico_muros_pasillos'. Aunque, lo más 
    aconsejable es crear unos muros que sean simplemente obstáculos para los ataques entre los 
    personajes.

    Especificación de los muros
    ---------------------------

    Para especificar los muros del tablero se debe crear un array similar al que aparece en los 
    ejemplos. Es preferible crear uno nuevo y mantener los ejemplos, en ese caso , la variable 
    debe tener un nombre diferente.

    El array está formado por 51 cadenas de caracteres, cada una de ellas de 145 caracteres de 
    longitud (mas el carácter \0 final, que no es visible). La mayor parte de los caracteres de 
    la cadena son espacios en blanco. En determinadas posiciones, y solo en ellas, puede haber: 
    o bien un guion, o bien la letra O mayúscula. 
        
    Esta disposición está pensada para indicar las posiciones de las celdas de la rejilla del 
    tablero. Al ser celdas hexagonales, no es posible usar una tabla formada por filas y 
    columnas, que, además, no daría una representación visual clara del tablero.

    Si se quiere que en una celda del tablero no aparezca un fragmento del muro, se debe 
    escribir un guion en la posición correspondiente del array. Si, por el contrario, se quiere 
    que si aparezca, se debe escribir la letra o mayúscula.

    El programa es muy sensible a la colocación de los caracteres en el array. Si uno de ellos
    está desplazado (por poco que sea), se producirá una excepción y el programa no se podrá 
    ejecutar.

    Programación
    ------------

    Véase la tercera parte de esta sección.
        
    *******************************************************************************************/
    static ActorTablero::GraficoMuros grafico_muros_vacio { 
//                                      1  1  1  1  1  1  1  1  1  1  2  2  2  2  2  2  2  2  2  2  3  3  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
//           1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
//                                                                                                                11111111111111111111111111111111111111111111
//                     111111111122222222223333333333444444444455555555556666666666777777777788888888889999999999000000000011111111112222222222333333333344444  
//           0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",  
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -",
            "   -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -   ",
            "-     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -     -"};

    /*******************************************************************************************
    /******************************************************************************************/


    void JuegoMesa::preparaTablero () {
        agregaTablero (new ActorTablero (this));
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Segunda parte

        En esta sección se configura el fondo del tablero. Para rellenar el fondo del tablero se usa
        un conjunto de imágenes colocadas en una rejilla (en filas y columnas), que ocupan toda la 
        superficie de la ventana.
        
        La imagen usada para rellenar el fondo del tablero no se usa directamente, se divide en 16
        partes, con 4 filas y 4 columnas, y continuación se colocan en el fondo del tablero, 
        seleccionado las partes de manera aleatoria. La razón de este funcionamiento es que se 
        consiguen evitar los patrones visuales que pueden aparecer si se colocan de forma uniforme.

        El tamaño de la imagen usada es de 128x128 px (y cada parte es de 32x32 px). 
        
        Programación
        ------------

        Para cambiar la imagen del fondo es suficiente con situar la imagen nueva en la carpeta de 
        activos del juego y cambiar el nombre en la línea de código siguiente. 
        
        Es conveniente usar un archivo de tipo PNG. Además se deben respetar las medidas indicadas
        previamente.

        *******************************************************************************************/
        tablero ()->ponArchivoBaldosas (carpeta_activos_juego + "estampas_fondo.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Primera parte

        En esta sección se configuran los equipos del juego. 

        Cada equipo tiene un nombre y un escudo que aparece sobre la bandera en la parte superior de
        los paneles laterales del juego. En escudo se superpone a la bandera, sin taparla. El tamaño
        de las dos imágenes es de 40x40 px.
        
        Programación
        ------------

        Para cambiar los nombres de los equipos, se deben cambiar las dos líneas de código 
        siguientes. 
        
        Para cambiar las imágenes de los escudos es suficiente con situar las imágenes nuevas en la 
        carpeta de activos del juego y cambiar los nombres en las líneas de código siguiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        // tablero ()->equipa (LadoTablero::Izquierda, L"Devils", carpeta_activos_juego + "escudo_devils.png");
        // tablero ()->equipa (LadoTablero::Derecha,   L"Tusk",   carpeta_activos_juego + "escudo_tusk.png");
        /*******************************************************************************************
        /******************************************************************************************/
        //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Tercera sección - El tablero - Tercera parte

        En esta sección se preparan los muros que aparecen en el tablero de juego. En la primera
        parte de la sección se preparan los muros que aparecen en el tablero, en esta tercera parte 
        se establecen los muros que usará el juego.

        Programación
        ------------

        Para cambiar los muros que aparecen en el tablero de juego es suficiente con cambiar el 
        nombre de la variable que contiene el array que los especifica en la línea de código que 
        aparece a continuación.
        
        *******************************************************************************************/
        tablero ()->situaMuros (grafico_muros_vacio);
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaPersonajes () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Cuarta sección - Los personajes - Tercera parte

        En esta sección se configuran los personajes del juego. En la segunda parte se establecen
        las variables destinadas a almacenar las instancias que definen los personajes. En esta 
        parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre del personaje correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los personajes:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. Deben 
                ser evitados los nombres compuestos y los nombres largos.

             b) Equipo: Se establece indicando si el personaje aparece en el panel de la izquierda o 
                en el panel de la derecha en el tablero de juego.

             c) Orden en equipo: Debe ser un índice a partir de 0 y consecutivo.

             d) Iniciativa: Establece que personaje actúa en primer lugar en algunas de las 
                circunstancias del juego. Debe ser positivo.

        Imágenes
        --------

        Cada personaje tiene un retrato con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 75x75 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre un fondo gris oscuro. El retrato se especifica en la creación de la instancia.

        De la misma forma, cada personaje tiene una imagen para la ficha con la que aparece en el 
        tablero. El tamaño de la imagen usada es de 31x31 px.

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de personajes diseñados para el 
        juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        personaje en el diseño del juego.

        Para cambiar las imágenes de los retratos de los personajes es suficiente con situar las 
        imágenes nuevas en la carpeta de retratos del juego y cambiar los nombres de los archivos en 
        las llamadas al método correspondientes. Lo mismo ocurre con las imágenes de las fichas.
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
        Jason    = new ActorPersonaje {this, LadoTablero::Izquierda, 0, L"Jason"};
        Sophie   = new ActorPersonaje {this, LadoTablero::Izquierda, 1, L"Sophie"};
        Pete     = new ActorPersonaje {this, LadoTablero::Izquierda, 2, L"Pete"};
        Cadaver  = new ActorPersonaje {this, LadoTablero::Derecha,   0, L"Cadáver"};
        Espectro = new ActorPersonaje {this, LadoTablero::Derecha,   1, L"Espectro"};
        Dana     = new ActorPersonaje {this, LadoTablero::Derecha,   2, L"Dana"};
        //
        Jason    -> ponArchivoRetrato (carpeta_retratos_juego + "Jason/JasonPortrait_75.png");
        Sophie   -> ponArchivoRetrato (carpeta_retratos_juego + "Sophie/SophiePortrait_75.png");
        Pete     -> ponArchivoRetrato (carpeta_retratos_juego + "Pete/PetePortrait_75.png");
        Dana     -> ponArchivoRetrato (carpeta_retratos_juego + "Dana/DanaPortrait_75.png");
        Espectro -> ponArchivoRetrato (carpeta_retratos_juego + "Espectro/GhostPortrait_75.png");
        Cadaver  -> ponArchivoRetrato (carpeta_retratos_juego + "Cadaver/ZombiePortrait_75.png");
        //
        Jason    -> ponArchivoFicha (carpeta_retratos_juego + "Jason/FichaJason.png");
        Sophie   -> ponArchivoFicha (carpeta_retratos_juego + "Sophie/FichaSophie.png");
        Pete     -> ponArchivoFicha (carpeta_retratos_juego + "Pete/FichaPete.png");
        Dana     -> ponArchivoFicha (carpeta_retratos_juego + "Dana/FichaDana.png");
        Espectro -> ponArchivoFicha (carpeta_retratos_juego + "Espectro/FichaFantasma.png");
        Cadaver  -> ponArchivoFicha (carpeta_retratos_juego + "Cadaver/FichaCadaver.png");
        //
        Jason    -> ponIniciativa (25);
        Sophie   -> ponIniciativa (24);
        Pete     -> ponIniciativa (23);
        Dana     -> ponIniciativa (18);
        Espectro -> ponIniciativa (19);
        Cadaver  -> ponIniciativa (20);

        // INICIO GUILLEM //
        // Listado de SFX que se le asigna individualmente a cada personaje
    
        //Sophie->ponArchivoSFX(carpeta_sonidos_juego + "Cadaver.wav"); // Prueba
        //Sophie->asignaPersonajeSFX(carpeta_sonidos_juego + "SFX/Cadaver.wav", 100); //Prueba

        // Retratos SFX
        Jason    -> asignaPersonajeSFX  (carpeta_sonidos_juego + "SFX/Jason.wav", 100);
        Sophie   -> asignaPersonajeSFX  (carpeta_sonidos_juego + "SFX/Sophie.wav", 100);
        Pete     -> asignaPersonajeSFX  (carpeta_sonidos_juego + "SFX/Pete.wav", 100);
        Dana     -> asignaPersonajeSFX  (carpeta_sonidos_juego + "SFX/Dana.wav", 100);
        Espectro -> asignaPersonajeSFX  (carpeta_sonidos_juego + "SFX/Espectro.wav", 100);
        Cadaver  -> asignaPersonajeSFX  (carpeta_sonidos_juego + "SFX/Cadaver.wav", 100);

        // Seleccion SFX
        Jason    -> asignaSeleccionSFX  (carpeta_sonidos_juego + "SFX/Jason_Seleccion.wav", 100);
        Sophie   -> asignaSeleccionSFX  (carpeta_sonidos_juego + "SFX/Sophie_Seleccion.wav", 100);
        Pete     -> asignaSeleccionSFX  (carpeta_sonidos_juego + "SFX/Pete_Seleccion.wav", 100);
        Dana     -> asignaSeleccionSFX  (carpeta_sonidos_juego + "SFX/Dana_Seleccion.wav", 100);
        Espectro -> asignaSeleccionSFX  (carpeta_sonidos_juego + "SFX/Espectro_Seleccion.wav", 100);
        Cadaver  -> asignaSeleccionSFX  (carpeta_sonidos_juego + "SFX/Cadaver_Seleccion.wav", 100);

        // Desplazamiento SFX
        Jason    -> asignaDesplazamientoSFX (carpeta_sonidos_juego + "SFX/Jason_Desplazamiento.wav", 100);
        Sophie   -> asignaDesplazamientoSFX (carpeta_sonidos_juego + "SFX/Sophie_Desplazamiento.wav", 100);
        Pete     -> asignaDesplazamientoSFX (carpeta_sonidos_juego + "SFX/Pete_Desplazamiento.wav", 100);
        Dana     -> asignaDesplazamientoSFX (carpeta_sonidos_juego + "SFX/Dana_Desplazamiento.wav", 100);
        Espectro -> asignaDesplazamientoSFX (carpeta_sonidos_juego + "SFX/Espectro_Desplazamiento.wav", 100);
        Cadaver  -> asignaDesplazamientoSFX (carpeta_sonidos_juego + "SFX/Cadaver_Desplazamiento.wav", 100);

        // FIN GUILLEM //
        
        //
        agregaPersonaje (Jason);
        agregaPersonaje (Sophie);
        agregaPersonaje (Pete);
        agregaPersonaje (Cadaver);
        agregaPersonaje (Espectro);
        agregaPersonaje (Dana);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaHabilidades () {
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Quinta sección - Las habilidades - Segunda parte

        En esta sección se configuran las habilidades compartidas por los personajes del juego. En 
        la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen las habilidades. En esta segunda parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de la habilidad correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a las habilidades:

             a) Nombre: Asignado en la creación de la instancia en una cadena de caracteres. 

             b) Enfoque: Indica a que esta enfocada la habilidad. Puede ser a un personaje, a un 
                área formada por varias celdas del tablero o hacia el mismo personaje que usa la 
                habilidad. 

             c) Acceso: Indica si el efecto de la habilidad puede atravesar muros. Puede ser directo,
                indirecto o ninguno.

             d) Antagonista: Indica a que grupo de personajes se dirige la habilidad. Puede ser a un
                oponente, a un aliado o a sí mismo.

             e) Descripción: Es un texto largo que describe la habilidad.

        Imágenes
        --------

        Cada habilidad tiene una imagen con el que aparece en la pantalla del juego. El tamaño de la
        imagen usada es de 50x50 px. La imagen puede tener zonas transparentes, en cuyo caso aparece 
        sobre una imagen de fondo, que puede ser distinta para cada habilidad o la misma para todas. 
        Las dos imágenes de cada habilidad se especifican la misma llamada a un método.

        Sonidos
        -------

        Cada habilidad tiene un sonido que suena cuando el personaje la usa. El sonido se carga de 
        un archivo de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de emisión del sonido
        debe ser corto (escasos segundos).

        Programación
        ------------

        Se deben modificar las lineas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias y las listas de llamadas a los 
        métodos por listas similares, obtenidas a partir de la lista de habilidades diseñadas para 
        el juego.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        habilidad en el diseño del juego.

        Para cambiar las imágenes de las habilidad es suficiente con situar las imágenes nuevas en 
        la carpeta de habilidades del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Para cambiar los sonidos de las habilidad es suficiente con situar los sonidos nuevos en 
        la carpeta de sonidos del juego y cambiar los nombres en las llamadas al método 
        correspondiente. 
        
        Es conveniente usar archivos de tipo PNG que permiten la transparencia. Además se deben 
        respetar las medidas indicadas previamente.

        *******************************************************************************************/
        //
        
       /* ataqueEspadaNormal = new Habilidad{
                L"Ataque cuerpo a cuerpo normal", 
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        ataqueArco           = new Habilidad {
                L"Ataque a distancia normal",     
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        ataqueEspadaPoderoso = new Habilidad {
                L"Ataque poderoso",               
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        defensaFerrea        = new Habilidad {
                L"Defensa férrea",                
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        curacionSimple       = new Habilidad {
                L"Curación",                      
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::aliado};
        curacionGrupo        = new Habilidad {
                L"Curación en grupo",             
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::aliado};
        proyectilMagico      = new Habilidad {
                L"Proyectil mágico",              
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto, Antagonista::oponente};
        bolaFuego            = new Habilidad {
                L"Bola de fuego",                 
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};
        revientaHuesos   = new Habilidad {
                L"Revienta huesos", 
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};*/
        fogonazo   = new Habilidad {
                L"Fogonazo", 
                EnfoqueHabilidad::area,      AccesoHabilidad::indirecto,   Antagonista::oponente};
        homeRun           = new Habilidad {
                L"Home Run",     
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        minaRepelente = new Habilidad {
                L"Mina Repelente",               
                EnfoqueHabilidad::area, AccesoHabilidad::directo,   Antagonista::oponente};
        roboVida        = new Habilidad {
                L"Robo de Vida",                
                EnfoqueHabilidad::si_mismo,  AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        espinasSombras       = new Habilidad {
                L"Espinas de Sombras",                      
                EnfoqueHabilidad::area, AccesoHabilidad::directo,   Antagonista::oponente};
        vomitoPutrefacto        = new Habilidad {
                L"Vómito Putrefacto",             
                EnfoqueHabilidad::personaje,      AccesoHabilidad::directo,   Antagonista::oponente};
        hazLuz      = new Habilidad {
                L"Haz de Luz",              
                EnfoqueHabilidad::area, AccesoHabilidad::directo, Antagonista::oponente};
        /*bolaFuego = new Habilidad{
                L"Bola de fuego",                 
                EnfoqueHabilidad::area,      AccesoHabilidad::directo,   Antagonista::oponente};*/
        sprint   = new Habilidad {
                L"Sprint", 
                EnfoqueHabilidad::si_mismo, AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        proteccionCampana   = new Habilidad {
                L"Protección de Campaña", 
                EnfoqueHabilidad::area, AccesoHabilidad::directo,   Antagonista::aliado};
        fuerzaTumba           = new Habilidad {
                L"Fuerza de la Tumba",     
                EnfoqueHabilidad::personaje, AccesoHabilidad::directo,   Antagonista::oponente};
        pasoSombras = new Habilidad {
                L"Paso de Sombras",               
                EnfoqueHabilidad::si_mismo, AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        mortaja        = new Habilidad {
                L"Mortaja",                
                EnfoqueHabilidad::personaje,  AccesoHabilidad::directo,   Antagonista::oponente};
        bengalaLuminosa       = new Habilidad {
                L"Bengala Luminosa",                      
                EnfoqueHabilidad::si_mismo, AccesoHabilidad::ninguno,   Antagonista::si_mismo};
        botiquin        = new Habilidad {
                L"Botiquín",             
                EnfoqueHabilidad::personaje,      AccesoHabilidad::directo,   Antagonista::aliado};
        somnolencia      = new Habilidad {
                L"Somnolencia",              
                EnfoqueHabilidad::si_mismo, AccesoHabilidad::ninguno, Antagonista::si_mismo};
        toqueHelado            = new Habilidad {
                L"Toque Helado",                 
                EnfoqueHabilidad::personaje,      AccesoHabilidad::directo,   Antagonista::oponente};
        dentellada   = new Habilidad {
                L"Dentallada", 
                EnfoqueHabilidad::area, AccesoHabilidad::directo,   Antagonista::oponente};
        bolaRapida   = new Habilidad {
                L"Bola Rápida", 
                EnfoqueHabilidad::personaje, AccesoHabilidad::indirecto,   Antagonista::oponente};

        //
        /*ataqueEspadaNormal->ponDescripcion(
                L"El personaje usa su espada para atacar a un enemigo que se encuentra en una casilla próxima.");
        ataqueArco          ->ponDescripcion (
                L"El personaje usa su arco para atacar a un enemigo que se encuentra en una casilla próxima.");
        ataqueEspadaPoderoso->ponDescripcion (
                L"El personaje blande su espada con fuerza para atacar a un enemigo que se encuentra en una casilla próxima.");
        defensaFerrea       ->ponDescripcion (
                L"El personaje aumenta su defensa hasta su próximo ronda.");
        curacionSimple      ->ponDescripcion (
                L"El personaje canaliza poder divino para sanar a un aliado.");
        curacionGrupo      ->ponDescripcion (
                L"El personaje canaliza poder divino para sanar a todos los personajes en un área.");
        proyectilMagico     ->ponDescripcion (
                L"El personaje acumula energía mágica y la lanza contra un enemigo.");
        bolaFuego           ->ponDescripcion (
                L"El personaje acumula energía mágica y la lanza contra un grupo de enemigos.");
        revientaHuesos  ->ponDescripcion (
                L"El personaje abraza con todas sus fuerzas hasta que los huesos del oponente se resquebran.");*/
        fogonazo          ->ponDescripcion (
                L"El personaje acumula energia térmica para lanzar un proyectil ardiente contra un enemigo.");
        homeRun             ->ponDescripcion (
                L"El personaje usa la fuerza bruta para canalizar toda la energía cinética en su palo de béisbol y usarlo contra un enemigo.");
        minaRepelente       ->ponDescripcion (
                L"El personaje pone una mina cerca de un grupo de enemigos y explota con todas las fuerzas para causar el mayor daño posible.");
        roboVida      ->ponDescripcion (
                L"***PRUEBAS:El personaje usa magia oscura para absorver energía vital de un enemigo que se encuentra en una casilla próxima.****");
        espinasSombras      ->ponDescripcion (
                L"El personaje usa magia oscura para lanzar una batería de proyectiles contra un grupo de enemigos.");
        vomitoPutrefacto     ->ponDescripcion (
                L"El personaje usa su vómito asqueroso para envenenar y podrir a su enemigo cercano.");
        hazLuz           ->ponDescripcion (
                L"El personaje quema los ojos a un grupo de enemigos cerca para que se debiliten y fallen más de lo esperado.");
        sprint          ->ponDescripcion (
                L"El personaje usa su cuerpo para canalizar su energía física y aumentar su velocidad de ataque.");
        proteccionCampana   ->ponDescripcion (
                L"El personaje hace uso de medicina avanzada para curar a todos los personajes en un área.");
        fuerzaTumba       ->ponDescripcion (
                L"El personaje usa un ataque muy poderoso, jugando con magia oscura pero sacrificando un gran consumo de energía.");
        pasoSombras      ->ponDescripcion (
                L"El personaje hace un llamamiento al poder de la sombra para aumentar su ataque durante un turno.");
        mortaja      ->ponDescripcion (
                L"El personaje roba de un sepúlcro cercano la mortaja y lo usa para asfixiar a su enemigo.");
        bengalaLuminosa     ->ponDescripcion (
                L"El personaje puede ver con claridad y al estar seguro de si mísmo aumenta sus ataques.");
        botiquin           ->ponDescripcion (
                L"El personaje hace uso de las herramientas curativas para sanar a un miembro de su equipo.");
        somnolencia      ->ponDescripcion (
                L"El personaje usa un somnífero a si mismo para aumentar sus defensas brutas.");
        toqueHelado     ->ponDescripcion (
                L"El personaje usa un ataque poderoso que congela y golpea con fuerza a su enemigo.");
        dentellada           ->ponDescripcion (
                L"El personaje se arranca varios dientes afilados de su mandíbula y los lanza a un grupo de enemigos cercano.");
        bolaRapida           ->ponDescripcion (
                L"El personaje lanza con todas sus fuerzas una bola de béisbol desde la distancia hasta impactar contra un enemigo.");
        //

        /*ataqueEspadaNormal->ponArchivosImagenes(
                carpeta_habilids_juego + "espada.png",          carpeta_habilids_juego + "fondo_5.png");
        ataqueArco          ->ponArchivosImagenes (
                carpeta_habilids_juego + "arco_flecha.png",     carpeta_habilids_juego + "fondo_5.png");
        ataqueEspadaPoderoso->ponArchivosImagenes (
                carpeta_habilids_juego + "espada_poderosa.png", carpeta_habilids_juego + "fondo_5.png");
        defensaFerrea       ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        curacionSimple      ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela.png",            carpeta_habilids_juego + "fondo_5.png");
        curacionGrupo       ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela_triple.png",     carpeta_habilids_juego + "fondo_5.png");
        proyectilMagico     ->ponArchivosImagenes (
                carpeta_habilids_juego + "cristales.png",       carpeta_habilids_juego + "fondo_5.png");
        bolaFuego           ->ponArchivosImagenes (
                carpeta_habilids_juego + "bola_fuego.png",      carpeta_habilids_juego + "fondo_5.png");*/
        fogonazo            ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada_poderosa.png", carpeta_habilids_juego + "fondo_5.png");
        homeRun             ->ponArchivosImagenes(
                carpeta_habilids_juego + "espada_poderosa.png", carpeta_habilids_juego + "fondo_5.png");
        minaRepelente       ->ponArchivosImagenes (
                carpeta_habilids_juego + "bola_fuego.png",      carpeta_habilids_juego + "fondo_5.png");
        roboVida            ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela.png",            carpeta_habilids_juego + "fondo_5.png");
        espinasSombras      ->ponArchivosImagenes (
                carpeta_habilids_juego + "cristales.png",       carpeta_habilids_juego + "fondo_5.png");
        vomitoPutrefacto    ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada.png",          carpeta_habilids_juego + "fondo_5.png");
        hazLuz              ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        sprint              ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        proteccionCampana   ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela_triple.png",     carpeta_habilids_juego + "fondo_5.png");
        fuerzaTumba         ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada_poderosa.png", carpeta_habilids_juego + "fondo_5.png");
        pasoSombras         ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        mortaja             ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada.png",          carpeta_habilids_juego + "fondo_5.png");
        bengalaLuminosa     ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        botiquin            ->ponArchivosImagenes (
                carpeta_habilids_juego + "vela.png",            carpeta_habilids_juego + "fondo_5.png");
        somnolencia         ->ponArchivosImagenes (
                carpeta_habilids_juego + "escudo.png",          carpeta_habilids_juego + "fondo_5.png");
        toqueHelado         ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada_poderosa.png", carpeta_habilids_juego + "fondo_5.png");
        dentellada          ->ponArchivosImagenes (
                carpeta_habilids_juego + "espada.png",          carpeta_habilids_juego + "fondo_5.png");
        bolaRapida          ->ponArchivosImagenes (
                carpeta_habilids_juego + "arco_flecha.png",          carpeta_habilids_juego + "fondo_5.png");
        //
        /*ataqueEspadaNormal->ponArchivoSonido(carpeta_sonidos_juego + "SFX/SFXHomeRun.wav");
        ataqueArco          ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXHomeRun.wav");
        ataqueEspadaPoderoso->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXVomitoPutrefacto.wav");
        defensaFerrea       ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXHomeRun.wav");
        curacionSimple      ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXHomeRun.wav");
        curacionGrupo       ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXHomeRun.wav");
        proyectilMagico     ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXHomeRun.wav");
        bolaFuego           ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/Magic Missiles.wav");*/
        homeRun             ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXHomeRun.wav");
        fogonazo            ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXFogonazo.wav");
        minaRepelente       ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXMinaRepelente.wav");
        roboVida            ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXRoboVida.wav");
        espinasSombras      ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXEspinasSombras.wav");
        vomitoPutrefacto    ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXVomitoPutrefacto.wav");
        hazLuz              ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXHazLuz.wav");
        sprint              ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXSprint.wav");
        proteccionCampana   ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXProteccionCampana.wav");
        fuerzaTumba         ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXFuerzaTumba.wav");
        pasoSombras         ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXPasoSombras.wav");
        mortaja             ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXMortaja.wav");
        bengalaLuminosa     ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXBengalaLuminosa.wav");
        botiquin            ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXBotiquin.wav");
        somnolencia         ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXSomnolencia.wav");
        toqueHelado         ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXToqueHelado.wav");
        dentellada          ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXDentellada.wav");
        bolaRapida          ->ponArchivoSonido (carpeta_sonidos_juego + "SFX/SFXBolaRapida.wav");
        //
       /* agregaHabilidad(ataqueEspadaNormal);
        agregaHabilidad (ataqueArco);
        agregaHabilidad (ataqueEspadaPoderoso);
        agregaHabilidad (defensaFerrea);
        agregaHabilidad (curacionSimple);
        agregaHabilidad (curacionGrupo);
        agregaHabilidad (proyectilMagico);
        agregaHabilidad (bolaFuego);*/
        agregaHabilidad (homeRun);
        agregaHabilidad (fogonazo);
        agregaHabilidad (minaRepelente);
        agregaHabilidad (roboVida);
        agregaHabilidad (espinasSombras);
        agregaHabilidad (vomitoPutrefacto);
        agregaHabilidad (hazLuz);
        agregaHabilidad (sprint);
        agregaHabilidad (proteccionCampana);
        agregaHabilidad (fuerzaTumba);
        agregaHabilidad (pasoSombras);
        agregaHabilidad (mortaja);
        agregaHabilidad (bengalaLuminosa);
        agregaHabilidad (botiquin);
        agregaHabilidad (somnolencia);
        agregaHabilidad (toqueHelado);
        agregaHabilidad (dentellada);
        agregaHabilidad (bolaRapida);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaTiposEstadisticas () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Sexta sección - Los tipos de ataque, defensa y daño (estadísticas) - Segunda parte

        En esta sección se configuran los tipos de ataque, defensa y daño del juego. Estos tipos  
        son usados para establecer las estadisticas del juego en los personajes y en las habilidades. 
        En la primera parte se establecen las variables destinadas a almacenar las instancias que 
        definen los tipos de ataque, defensa y daño. En esta parte se crean las instancias y se 
        configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos y deben comenzar con la palabra 'Ataque', 'Defensa' o 'Daño'.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de tipos diseñados para el juego. El nombre de la clase (por ejemplo 
        'TipoAtaque' para los ataques) establece si es un tipo de ataque, de defensa o de daño.

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        tipo en el diseño del juego.

        *******************************************************************************************/
        //
        /*ataqueCuerpoACuerpo = new TipoAtaque{L"Ataque cuerpo a cuerpo"};
        ataqueADistancia      = new TipoAtaque  {L"Ataque a distancia"};
        ataqueMagico          = new TipoAtaque  {L"Ataque mágico"};*/
        energiaTermica        = new TipoAtaque  {L"Ataque de tipo fuego"};
        ataqueExplosivo       = new TipoAtaque  {L"Ataque explosivo"};
        magiaOscura           = new TipoAtaque  {L"Ataque con magia oscura"};
        ataqueAsqueroso       = new TipoAtaque  {L"Ataque asqueroso"};
        ataqueHielo           = new TipoAtaque  {L"Ataque Hielo"};
        fuerzaBruta           = new TipoAtaque  {L"Ataque bruto"};

       /* defensaCuerpoACuerpo = new TipoDefensa{L"Defensa cuerpo a cuerpo"};
        defensaADistancia     = new TipoDefensa {L"Defensa a distancia"};
        defensaMagica         = new TipoDefensa {L"Defensa mágica"};*/
        defensaEnergiaTermica = new TipoDefensa {L"Defensa energía térmica"};
        defensaExplosivo      = new TipoDefensa {L"Defensa explosiva"};
        defensaOscura         = new TipoDefensa {L"Defensa magia oscura"};
        defensaAsquerosa      = new TipoDefensa {L"Defensa asquerosa"};
        defensaHielo          = new TipoDefensa {L"Defensa hielo"};
        defensaBruta          = new TipoDefensa {L"Defensa bruta"};
        
        /*danoFisico = new TipoDano{L"Daño físico"};
        danoMagico           = new TipoDano     {L"Daño mágico"};*/
        danoTermico          = new TipoDano     {L"Daño térmico"};
        danoExplosivo        = new TipoDano     {L"Daño explosivo"};
        danoOscuro           = new TipoDano     {L"Daño Oscuro"};
        danoAsqueroso        = new TipoDano     {L"Daño asqueroso"};
        danoHielo            = new TipoDano     {L"Daño hielo"};
        danoBruto            = new TipoDano     {L"Daño bruto"};

        //
       /* agregaAtaque(ataqueCuerpoACuerpo);
        agregaAtaque  (ataqueADistancia);
        agregaAtaque  (ataqueMagico);*/
        agregaAtaque  (energiaTermica);
        agregaAtaque  (ataqueExplosivo);
        agregaAtaque  (magiaOscura);
        agregaAtaque  (ataqueAsqueroso);
        agregaAtaque  (ataqueHielo);
        agregaAtaque  (fuerzaBruta);

        /*agregaDefensa(defensaCuerpoACuerpo);
        agregaDefensa (defensaADistancia );
        agregaDefensa (defensaMagica );*/
        agregaDefensa (defensaEnergiaTermica);
        agregaDefensa (defensaExplosivo);
        agregaDefensa (defensaOscura);
        agregaDefensa (defensaAsquerosa);
        agregaDefensa (defensaHielo);
        agregaDefensa (defensaBruta);

        /*agregaDano(danoFisico);
        agregaDano    (danoMagico);*/
        agregaDano    (danoTermico);
        agregaDano    (danoExplosivo);
        agregaDano    (danoOscuro);
        agregaDano    (danoAsqueroso);
        agregaDano    (danoHielo);
        agregaDano    (danoBruto);

        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaHabilidadesPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Octava sección - Las habilidades de los personajes

        En esta sección se establecen que habilidades que tiene cada personajes del juego.

        Cada personaje debe tener entre 1 y 10 habilidades.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de habilidades de cada personaje por listas similares, 
        obtenidas a partir del diseño del juego.

        *******************************************************************************************/
        //
        Jason    -> agregaHabilidad (homeRun);
        Jason    -> agregaHabilidad (sprint);
        Jason    -> agregaHabilidad (bolaRapida);
        //
        //Sophie   -> agregaHabilidad (ataqueEspadaNormal);
        Sophie   -> agregaHabilidad (fogonazo);
        Sophie   -> agregaHabilidad (bengalaLuminosa);
        Sophie   -> agregaHabilidad (minaRepelente);
        //
        Pete     -> agregaHabilidad (hazLuz);
        Pete     -> agregaHabilidad (proteccionCampana);
        Pete     -> agregaHabilidad (botiquin);
        //
        Dana     -> agregaHabilidad (roboVida);
        Dana     -> agregaHabilidad (fuerzaTumba);
        Dana     -> agregaHabilidad (somnolencia);
        //
        Espectro -> agregaHabilidad (espinasSombras);
        Espectro -> agregaHabilidad (pasoSombras);
        Espectro -> agregaHabilidad (toqueHelado);
        //
        Cadaver  -> agregaHabilidad (vomitoPutrefacto);
        Cadaver  -> agregaHabilidad (mortaja);
        Cadaver  -> agregaHabilidad (dentellada);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasHabilidades () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Novena sección - Las estadísticas de las habilidades

        En esta sección se establecen diversos atributos y valores para las habilidades del juego,
        incluyendo las estadisticas del juego.

        Estadísticas
        ------------

        Las habilidades se clasifican en habilidades de ataque, de curación y auto-aplicada. Esta 
        clasificación se establece mediante el atributo 'Antagonista' de la habilidad. 

            - Si 'Antagonista' es 'oponente' la habilidad es de ataque. El ataque puede afectar a un 
              personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'aliado' la habilidad es de curación. La curación puede afectar a 
              un personaje o a los personajes de un área del tablero.
            - Si 'Antagonista' es 'si_mismo' la habilidad es auto-aplicada.

        Los valores que se establecen para las habilidades son:

             a) Coste: Es el número de puntos de acción que se gastan al usar la habilidad.

             b) Alcance: En las habilidades de ataque y curación debe estar establecido el alcance 
                de la habilidad. La habilidad solo se puede usar si el alcance lo permite. Es un 
                valor que indica un número de casillas del tablero y debe ser positivo.

             c) Radio de ara de alcance: En las habilidades de ataque y curación que afectan a un 
                área del tablero, debe estar establecido el radio del área. Es un valor que indica 
                un número de casillas del tablero y debe ser positivo. 

             d) Tipo de ataque: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                ataque. El tipo de ataque se usa en el personaje atacante.

             e) Tipo de defensa: Cuando una habilidad es de ataque, debe tener establecido un tipo 
                de defensa. El tipo de defensa se usa en el personaje atacado.

             f) Tipo de daño: Cuando una habilidad es de ataque, debe tener establecido un tipo de 
                daño. El tipo de daño se usa en el personaje atacado.

             g) Valor del daño: Cuando una habilidad es de ataque, debe tener establecido un valor 
                para el daño en puntos de vitalidad. El valor del daño se usa con el personaje 
                atacado.

             h) Curación: Cuando una habilidad es de curación, debe tener establecido un valor de 
                curación en puntos.

             i) Efecto en ataque: Cuando una habilidad es auto-aplicada, puede tener establecido uno 
                o más tipos de ataque, asignado como tipo de efecto en ataque. Alternativamente 
                (y excluyentemente) puede tener establecido un efecto en defensa (véase k).

             j) Valor del efecto en ataque: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en ataque establecido (véase i), debe tener establecido un valor del efecto
                en ataque en puntos de vitalidad.

             k) Efecto en defensa: Cuando una habilidad es auto-aplicada, puede tener establecido 
                uno o más tipos de defensa, asignado como tipo de efecto en defensa. Alternativamente 
                (excluyentemente) puede tener establecido un efecto en ataque (véase i).

             l) Valor del efecto en defensa: Cuando una habilidad es auto-aplicada, para cada tipo de 
                efecto en defensa establecido (véase k), debe tener establecido un valor del efecto
                en defensa en puntos de vitalidad.


        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las asignaciones de valores por asignaciones similares, obtenidas a 
        partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si se debe usar un tipo de 
        ataque, de defensa o de daño. Por ejemplo, el método 'asignaAtaque' debe ser llamado con un 
        parámetro del tipo (puntero) 'TipoAtaque'.  

        *******************************************************************************************/
        //
        /*ataqueEspadaNormal->ponCoste(3);
        ataqueEspadaNormal->ponAlcance (1);
        ataqueEspadaNormal->asignaAtaque  (ataqueCuerpoACuerpo); 
        ataqueEspadaNormal->asignaDefensa (defensaCuerpoACuerpo); 
        ataqueEspadaNormal->asignaDano    (danoFisico, 20); 
        //
        ataqueArco->ponCoste (5);
        ataqueArco->ponAlcance (15);
        ataqueArco->asignaAtaque  (ataqueADistancia);
        ataqueArco->asignaDefensa (defensaADistancia);
        ataqueArco->asignaDano    (danoFisico, 20);
        //
        ataqueEspadaPoderoso->ponCoste (5);
        ataqueEspadaPoderoso->ponAlcance (1);
        ataqueEspadaPoderoso->asignaAtaque  (ataqueCuerpoACuerpo);
        ataqueEspadaPoderoso->asignaDefensa (defensaCuerpoACuerpo);
        ataqueEspadaPoderoso->asignaDano    (danoFisico, 50);
        //
        defensaFerrea->ponCoste (3);
        defensaFerrea->agregaEfectoDefensa (defensaCuerpoACuerpo, 30);
        defensaFerrea->agregaEfectoDefensa (defensaADistancia,    30);
        //
        curacionSimple->ponCoste (5);
        curacionSimple->ponAlcance (3);  
        curacionSimple->asignaCuracion (40);
        //
        curacionGrupo->ponCoste (10);
        curacionGrupo->ponAlcance (3);  
        curacionGrupo->ponRadioAlcance (3);
        curacionGrupo->asignaCuracion (40);
        //
        proyectilMagico->ponCoste (7);
        proyectilMagico->ponAlcance (15);                                            
        proyectilMagico->asignaAtaque  (ataqueMagico);
        proyectilMagico->asignaDefensa (defensaMagica);
        proyectilMagico->asignaDano    (danoMagico, 30);
        //
        bolaFuego->ponCoste (10);
        bolaFuego->ponAlcance (8);
        bolaFuego->ponRadioAlcance (3);
        bolaFuego->asignaAtaque  (ataqueMagico);
        bolaFuego->asignaDefensa (defensaMagica);
        bolaFuego->asignaDano    (danoMagico, 50);
        //
        revientaHuesos->ponCoste (4);
        revientaHuesos->ponAlcance (1);
        revientaHuesos->asignaAtaque  (ataqueCuerpoACuerpo);
        revientaHuesos->asignaDefensa (defensaCuerpoACuerpo);
        revientaHuesos->asignaDano    (danoFisico, 60);*/
        //
        fogonazo->ponCoste (4);
        fogonazo->ponAlcance (10);
        fogonazo->ponRadioAlcance (2);
        fogonazo->asignaAtaque  (energiaTermica);
        fogonazo->asignaDefensa (defensaEnergiaTermica);
        fogonazo->asignaDano    (danoTermico, 13);
        //
        homeRun->ponCoste (5);
        homeRun->ponAlcance (15);
        homeRun->asignaAtaque  (fuerzaBruta);
        homeRun->asignaDefensa (defensaBruta);
        homeRun->asignaDano    (danoBruto, 19);
        //
        minaRepelente->ponCoste (6);
        minaRepelente->ponAlcance (3);
        minaRepelente->ponRadioAlcance (3);
        minaRepelente->asignaAtaque  (ataqueExplosivo);
        minaRepelente->asignaDefensa (defensaExplosivo);
        minaRepelente->asignaDano    (danoExplosivo, 25);
        //
        roboVida->ponCoste (3);
        roboVida->agregaEfectoDefensa(defensaEnergiaTermica, 8);
        roboVida->agregaEfectoDefensa(defensaExplosivo, 8);
        //roboVida->asignaCuracion (40);
        // roboVida->asignaAtaque  (magiaOscura);
        // roboVida->asignaDefensa (defensaOscura);
        // roboVida->asignaDano    (danoOscuro, 60);
        //
        espinasSombras->ponCoste (7);
        espinasSombras->ponAlcance (15);
        espinasSombras->ponRadioAlcance (2);
        espinasSombras->asignaAtaque  (magiaOscura);
        espinasSombras->asignaDefensa (defensaOscura);
        espinasSombras->asignaDano    (danoOscuro, 24);
        //
        vomitoPutrefacto->ponCoste (7);
        vomitoPutrefacto->ponAlcance (1);
        vomitoPutrefacto->asignaAtaque  (ataqueAsqueroso);
        vomitoPutrefacto->asignaDefensa (defensaAsquerosa);
        vomitoPutrefacto->asignaDano    (danoAsqueroso, 15);
        //
        hazLuz->ponCoste (3);
        hazLuz->ponAlcance (1);
        hazLuz->ponRadioAlcance (3);
        hazLuz->asignaAtaque  (energiaTermica);
        hazLuz->asignaDefensa (defensaEnergiaTermica);
        hazLuz->asignaDano    (danoTermico, 15);
        //
        sprint->ponCoste (3);
        sprint->agregaEfectoAtaque (fuerzaBruta, 8);
        //sprint->agregaEfectoAtaque (ataqueExplosivo, 8);
        //
        proteccionCampana->ponCoste (5);
        proteccionCampana->ponAlcance (1);
        proteccionCampana->ponRadioAlcance (4);
        proteccionCampana->asignaCuracion(25);
        //
        fuerzaTumba->ponCoste (12);
        fuerzaTumba->ponAlcance (1);
        fuerzaTumba->asignaAtaque  (magiaOscura);
        fuerzaTumba->asignaDefensa (defensaOscura);
        fuerzaTumba->asignaDano    (danoOscuro, 28);
        //
        pasoSombras->ponCoste (3);
        pasoSombras->agregaEfectoAtaque(magiaOscura, 9);
        //
        mortaja->ponCoste (6);
        mortaja->ponAlcance (1);
        mortaja->asignaAtaque  (ataqueAsqueroso);
        mortaja->asignaDefensa (defensaAsquerosa);
        mortaja->asignaDano    (danoAsqueroso, 15);
        //
        bengalaLuminosa->ponCoste (3);
        bengalaLuminosa->agregaEfectoAtaque(energiaTermica, 11);
        //
        botiquin->ponCoste (5);
        botiquin->ponAlcance (1);
        botiquin->asignaCuracion(23);
        //
        somnolencia->ponCoste (3);
        somnolencia->agregaEfectoDefensa(defensaBruta, 4);
        somnolencia->agregaEfectoDefensa(defensaExplosivo, 10);
        //
        toqueHelado->ponCoste (7);
        toqueHelado->ponAlcance (1);
        toqueHelado->asignaAtaque  (ataqueHielo);
        toqueHelado->asignaDefensa (defensaHielo);
        toqueHelado->asignaDano    (danoHielo, 23);
        //
        dentellada->ponCoste (6);
        dentellada->ponAlcance (4);
        dentellada->ponRadioAlcance (3);
        dentellada->asignaAtaque  (ataqueAsqueroso);
        dentellada->asignaDefensa (defensaAsquerosa);
        dentellada->asignaDano    (danoAsqueroso, 20);
        //
        bolaRapida->ponCoste (5);
        bolaRapida->ponAlcance (8);
        bolaRapida->asignaAtaque  (fuerzaBruta);
        bolaRapida->asignaDefensa (defensaBruta);
        bolaRapida->asignaDano    (danoBruto, 15);

        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::agregaEstadisticasPersonajes () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Décima sección - Los tipos de ataque, defensa y reducción de daño de los personajes

        En esta sección se establecen que tipos de ataque, defensa y reducción de daño tiene cada 
        personajes del juego, junto con la correspondiente puntuación.

        Configuración
        -------------

        La configuración de los tipos se debe realizar de la siguiente forma:

             a) Si un personaje tiene una habilidad y esta habilidad tiene un tipo de ataque, el 
                personaje debe tener ese tipo de ataque.

             b) Cada personaje debe tener todos los tipos de defensa.

             c) Cada personaje debe tener todos los tipos de daño, en forma de reducción de daño.

             d) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en ataque,
                que está definido usando un tipo de ataque, el personaje debe tener dicho tipo de 
                ataque.

             e) Si un personaje tiene una habilidad y esta habilidad tiene un efecto en defensa,
                que está definido usando un tipo de defensa, el personaje debe tener dicho tipo de 
                defensa. Esta propiedad está establecida previamente mediante el punto (b)

             f) Cada tipo de ataque, defensa y reducción de daño del personaje debe tener una 
                puntuación. La puntuación no puede ser negativa.        

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de tipos de ataque, defensa y reducción de daño de cada 
        personaje por listas similares, obtenidas a partir del diseño del juego.

        Los métodos usados en las líneas de código siguientes establecen si el tipo es ataque, 
        defensa o daño. Por ejemplo, el método 'agregaReduceDano' debe ser llamado con un parámetro 
        del tipo (puntero) 'TipoDano'.  

        *******************************************************************************************/
        //
        /*Jason->agregaAtaque(ataqueCuerpoACuerpo, 70);
        Jason    -> agregaAtaque     (ataqueADistancia,     50);
        Jason    -> agregaDefensa    (defensaCuerpoACuerpo, 70);
        Jason    -> agregaDefensa    (defensaADistancia,    70);
        Jason    -> agregaDefensa    (defensaMagica,        20);*/
        Jason    -> agregaAtaque     (fuerzaBruta,          70);
        Jason    -> agregaDefensa    (defensaOscura,        60);
        Jason    -> agregaDefensa    (defensaEnergiaTermica,70);
        Jason    -> agregaDefensa    (defensaExplosivo,     20);
        Jason    -> agregaDefensa    (defensaAsquerosa,     20);
        Jason    -> agregaDefensa    (defensaHielo,         20);
        Jason    -> agregaDefensa    (defensaBruta,         20);
        //Jason    -> agregaReduceDano (danoFisico,           10);
        //Jason    -> agregaReduceDano (danoMagico,           5);
        Jason    -> agregaReduceDano (danoOscuro,           5);
        Jason    -> agregaReduceDano (danoTermico,          5);
        Jason    -> agregaReduceDano (danoExplosivo,        5);
        Jason    -> agregaReduceDano (danoAsqueroso,        4);
        Jason    -> agregaReduceDano (danoHielo,            5);
        Jason    -> agregaReduceDano (danoBruto,            5);
        //
        //Sophie   -> agregaAtaque     (ataqueCuerpoACuerpo,  50);
        //Sophie   -> agregaAtaque     (ataqueADistancia,     50);
        //Sophie   -> agregaAtaque     (ataqueMagico,         50);
        //Sophie   -> agregaDefensa    (defensaCuerpoACuerpo, 50);
        //Sophie   -> agregaDefensa    (defensaADistancia,    50);
        //Sophie   -> agregaDefensa    (defensaMagica,        50);
        Sophie   -> agregaAtaque     (energiaTermica,       50);
        Sophie  ->  agregaAtaque     (ataqueExplosivo,       58);
        Sophie   -> agregaDefensa    (defensaOscura,        50);
        Sophie   -> agregaDefensa    (defensaEnergiaTermica,50);
        Sophie   -> agregaDefensa    (defensaExplosivo,     50);
        Sophie   -> agregaDefensa    (defensaAsquerosa,     50);
        Sophie   -> agregaDefensa    (defensaHielo,         50);
        Sophie   -> agregaDefensa    (defensaBruta,         20);
        //Sophie   -> agregaReduceDano (danoFisico,            5);
        //Sophie   -> agregaReduceDano (danoMagico,           10);
        Sophie   -> agregaReduceDano (danoOscuro,           10);
        Sophie   -> agregaReduceDano (danoTermico,           5);
        Sophie   -> agregaReduceDano (danoExplosivo,        10);
        Sophie   -> agregaReduceDano (danoAsqueroso,         5);
        Sophie   -> agregaReduceDano (danoHielo,             5);
        Sophie   -> agregaReduceDano (danoBruto,             5);
        //                       
        //Pete     -> agregaAtaque     (ataqueCuerpoACuerpo,  50);
        //Pete     -> agregaAtaque     (ataqueADistancia,     70);
        Pete     -> agregaAtaque     (energiaTermica,       50);
        //Pete     -> agregaAtaque     (ataqueMagico,         70);        
        //Pete     -> agregaDefensa    (defensaCuerpoACuerpo, 40);
        //Pete     -> agregaDefensa    (defensaADistancia,    40);
        //Pete     -> agregaDefensa    (defensaMagica,        30);
        Pete     -> agregaDefensa    (defensaOscura,        40);
        Pete     -> agregaDefensa    (defensaEnergiaTermica,40);
        Pete     -> agregaDefensa    (defensaExplosivo,     30);
        Pete     -> agregaDefensa    (defensaAsquerosa,     70);
        Pete     -> agregaDefensa    (defensaHielo,         30);
        Pete     -> agregaDefensa    (defensaBruta,         30);
        //Pete     -> agregaReduceDano (danoFisico,            0);
        //Pete     -> agregaReduceDano (danoMagico,           15);
        Pete     -> agregaReduceDano (danoOscuro,            0);
        Pete     -> agregaReduceDano (danoTermico,           0);
        Pete     -> agregaReduceDano (danoExplosivo,         15);
        Pete     -> agregaReduceDano (danoAsqueroso,         15);
        Pete     -> agregaReduceDano (danoHielo,             0);
        Pete     -> agregaReduceDano (danoBruto,             0);
        //                       
        //Dana     -> agregaAtaque     (ataqueCuerpoACuerpo,  70);
        //Dana     -> agregaAtaque     (ataqueADistancia,     50);        
        Dana     -> agregaAtaque     (magiaOscura,          65);
        //Dana     -> agregaDefensa    (defensaCuerpoACuerpo, 70);
        //Dana     -> agregaDefensa    (defensaADistancia,    70);
        //Dana     -> agregaDefensa    (defensaMagica,        20);
        Dana     -> agregaDefensa    (defensaOscura,        70);
        Dana     -> agregaDefensa    (defensaEnergiaTermica,45);
        Dana     -> agregaDefensa    (defensaExplosivo,     20);
        Dana     -> agregaDefensa    (defensaAsquerosa,     60);
        Dana     -> agregaDefensa    (defensaHielo,         60);
        Dana     -> agregaDefensa    (defensaBruta,         40);
        //Dana     -> agregaReduceDano (danoFisico,           10);
        //Dana     -> agregaReduceDano (danoMagico,            5);
        Dana     -> agregaReduceDano (danoOscuro,            5);
        Dana     -> agregaReduceDano (danoTermico,           5);
        Dana     -> agregaReduceDano (danoExplosivo,         5);
        Dana     -> agregaReduceDano (danoAsqueroso,         15);
        Dana     -> agregaReduceDano (danoHielo,             5);
        Dana     -> agregaReduceDano (danoBruto,             2);
        //                       
        //Espectro -> agregaAtaque     (ataqueCuerpoACuerpo,  50);
        //Espectro -> agregaAtaque     (ataqueMagico,         50);        
        Espectro -> agregaAtaque     (magiaOscura,          50);        
        Espectro -> agregaAtaque     (ataqueHielo,          50);        
        //Espectro -> agregaDefensa    (defensaCuerpoACuerpo, 50);
        //Espectro -> agregaDefensa    (defensaADistancia,    50);
        //Espectro -> agregaDefensa    (defensaMagica,        50);
        Espectro -> agregaDefensa    (defensaOscura,        50);
        Espectro -> agregaDefensa    (defensaEnergiaTermica,50);
        Espectro -> agregaDefensa    (defensaExplosivo,     50);
        Espectro -> agregaDefensa    (defensaAsquerosa,     30);
        Espectro -> agregaDefensa    (defensaHielo,         30);
        Espectro -> agregaDefensa    (defensaBruta,         35);
        //Espectro -> agregaReduceDano (danoFisico,            5);
        //Espectro -> agregaReduceDano (danoMagico,           10);
        Espectro -> agregaReduceDano (danoOscuro,            5);
        Espectro -> agregaReduceDano (danoTermico,           5);
        Espectro -> agregaReduceDano (danoExplosivo,         10);
        Espectro -> agregaReduceDano (danoAsqueroso,         5);
        Espectro -> agregaReduceDano (danoHielo,             5);
        Espectro -> agregaReduceDano (danoBruto,             2);

        //                       
        //Cadaver  -> agregaAtaque     (ataqueCuerpoACuerpo,  50);
        //Cadaver  -> agregaAtaque     (ataqueADistancia,     50);
        //Cadaver  -> agregaAtaque     (ataqueMagico,         50);       
        Cadaver  -> agregaAtaque     (ataqueAsqueroso,      59);     
        //Cadaver  -> agregaDefensa    (defensaCuerpoACuerpo, 50);
        //Cadaver  -> agregaDefensa    (defensaADistancia,    50);
        //Cadaver  -> agregaDefensa    (defensaMagica,        50);
        Cadaver  -> agregaDefensa    (defensaOscura,        60);
        Cadaver  -> agregaDefensa    (defensaEnergiaTermica,50);
        Cadaver  -> agregaDefensa    (defensaExplosivo,     50);
        Cadaver  -> agregaDefensa    (defensaAsquerosa,     50);
        Cadaver  -> agregaDefensa    (defensaHielo,         50);
        Cadaver  -> agregaDefensa    (defensaBruta,         40);
        //Cadaver  -> agregaReduceDano (danoFisico,            5);
        //Cadaver  -> agregaReduceDano (danoMagico,           10);
        Cadaver  -> agregaReduceDano (danoOscuro,            0);
        Cadaver  -> agregaReduceDano (danoTermico,           0);
        Cadaver  -> agregaReduceDano (danoExplosivo,         10);
        Cadaver  -> agregaReduceDano (danoAsqueroso,         5);
        Cadaver  -> agregaReduceDano (danoHielo,             0);
        Cadaver  -> agregaReduceDano (danoBruto,             2);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::preparaSistemaAtaque () {
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Séptima sección - Los grados de efectividad - Segunda parte

        En esta sección se configuran los grados de efectividad de los ataques del juego. En la 
        primera parte se establecen las variables destinadas a almacenar las instancias que definen 
        los grados de efectividad. En esta parte se crean las instancias y se configuran.

        Las variable usan un nombre similar al nombre de los tipos correspondiente. Las variables 
        son de tipo puntero, la creación de las instancias utiliza la palabra reservada 'new'. 

        Atributos
        ---------

        Se asignan los siguientes atributos a los tipos:

             a) Descripción: Asignado en la creación de la instancia en una cadena de caracteres. 
                Deben ser cortos.

             b) Intervalo de puntos: Es el intervalo de puntos al que se aplica la efectividad. 
                Se establece con un valor mínimo y uno máximo. En el primer intervalo el valor 
                mínimo es el número entero mínimo y en el último intervalo, el valor máximo es 
                el número entero máximo.

             c) Efectividad: Es un porcentaje que se aplica a una puntuación para modificar su 
                valor cuando dicha puntuación esta en el intervalo definido por el intervalo
                correspondiente. 
            
        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se debe sustituir las listas de creaciones de instancias por listas similares, obtenidas a 
        partir de la lista de grados de efectividad diseñados para el juego. 

        Se deben cambiar los valores de los parámetros según los valores establecidos para cada 
        grados de efectividad en el diseño del juego.

        *******************************************************************************************/
        //
        GradoEfectividad * fallo   = new GradoEfectividad {L"Fallo"};
        GradoEfectividad * roce    = new GradoEfectividad {L"Roce"};
        GradoEfectividad * impacto = new GradoEfectividad {L"Impacto"};
        GradoEfectividad * critico = new GradoEfectividad {L"Impacto crítico"};
        //
        fallo  ->estableceRango (INT_MIN,       9,    0);
        roce   ->estableceRango (     10,      49,   50);
        impacto->estableceRango (     50,      89,  100);
        critico->estableceRango (     90, INT_MAX,  150);
        //
        agregaEfectividad (fallo);
        agregaEfectividad (roce);
        agregaEfectividad (impacto);
        agregaEfectividad (critico);
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::configuraJuego () {
        
        // INICIO GUILLEM //
        agregaMusica (new ActorMusica {this}); //original
        //ActorMusica * musicote = new ActorMusica{ this };
       // ActorMusica* musicota = new ActorMusica{ this };
        //agregaMusica(musicote);
        //agregaMusicaLoop(musicote);
        // FIN GUILLEM //
        //
        /*******************************************************************************************
        /*******************************************************************************************
        
        CONFIGURACIÓN DEL JUEGO
        Undécima sección - Configuración miscelánea del juego.

        En esta sección se establecen varios valores de configuración que no tienen sitio en otras 
        secciones.

        Configuración
        -------------

        La configuración tiene los siguientes aspectos:

                 a) Se establece el consumo de puntos de acción de los desplazamientos de los 
                    personajes. Para ello se indica el número píxeles de desplazamiento que 
                    originan el consumo de un punto de acción.

                 b) Se establece la posición inicial de las fichas de los personajes en el tablero 
                    de juego.
         
                 c) Se establecen los archivos de sonido, que se escuchan en momentos concretos del
                    juego. Se deben especificar los sonidos:

                      - Sonido de una pulsación con el ratón (clic)
                      - Sonido de desplazamiento de una ficha.

                 d) Se establece la música que se escucha con el juego. En un fragmento musical que 
                    se repite en bucle.

                 e) Se almacenan los nombres de los alumnos diseñadores del juego. Estos nombres
                    aparecen en la ayuda del juego.

                 f) Se almacena el curso académico durante el que los alumnos han elaborado el 
                    diseño del juego.

        Sonidos y música
        ----------------

        Los sonidos se cargan de archivos de tipo 'wav', 'ogg' o 'flac', pero no 'mp3'. El tiempo de
        emisión del sonido debe ser corto (escasos segundos).
        
        Los sonidos y la música se han tomado de:
                https://opengameart.org/content/metal-click
                https://opengameart.org/content/walking-on-snow-sound
        La licencia aparece en esas mismas páginas.

        La música que suena en momentos determinados del juego también se carga de un archivo. Sin 
        embargo, no es necesario que sea corta, por que se atenúa a los pocos segundos.

        La música se han tomado de:
                https://opengameart.org/content/unused-music
        La licencia aparece en esa misma página.

        Programación
        ------------

        Se deben modificar las líneas de código que aparecen a continuación.

        Se deben sustituir las listas de personajes por listas similares, obtenidas a partir del 
        diseño del juego.

        *******************************************************************************************/
        //
        modo ()->configuraDesplaza (RejillaTablero::distanciaCeldas);
        //
        Jason    -> ponSitioFicha (Coord {10, 14});
        Sophie   -> ponSitioFicha (Coord {18, 14});
        Pete     -> ponSitioFicha (Coord {26, 14});
        Dana     -> ponSitioFicha (Coord {26, 34});
        Espectro -> ponSitioFicha (Coord {18, 34});
        Cadaver  -> ponSitioFicha (Coord {10, 34});
        //
        tablero ()->asignaSonidoEstablece (carpeta_sonidos_juego + "SFX/Metal Click.wav", 100);
        tablero ()->asignaSonidoDesplaza  (carpeta_sonidos_juego + "SFX/SnowWalk.ogg",    100);
        // INICIO GUILLEM //
        //musica     ()->asignaMusica      (carpeta_sonidos_juego + "Themes/Track_1.ogg",   100);
        musica       ()->asignaMusica      (carpeta_sonidos_juego + "Themes/tomb_of_the_lost_voices_intro.wav", 100);
        musica       ()->asignaMusicaLoop  (carpeta_sonidos_juego + "Themes/tomb_of_the_lost_voices_bucle.wav", 100);
        //musicaLoop ()->asignaMusica      (carpeta_sonidos_juego + "Themes/tomb_of_the_lost_voices_bucle.wav", 100);
        //musicaLoop ()->asignaMusicaLoop  (carpeta_sonidos_juego + "Themes/tomb_of_the_lost_voices_bucle.wav", 100);
        
        // FIN GUILLEM //
        //
        agregaNombreAlumno (L"Andrei Danescu");
        agregaNombreAlumno (L"Luis Ivan Cabrera Rodriguez");
        agregaNombreAlumno (L"Guillem Muñoz Pueyo");
        agregaNombreAlumno (L"Juan Luis Casas Nebrera");
        agregaNombreAlumno (L"Raimon Rodriguez Alles");
        agregaNombreAlumno (L"Raul Vivar Cano");
        indicaCursoAcademico (L"2023 - 2024");
        //
        /*******************************************************************************************
        /******************************************************************************************/
    }


    void JuegoMesa::termina () {
        //
        JuegoMesaBase::termina ();
        //
        Jason    = nullptr;
        Sophie   = nullptr;
        Pete     = nullptr;
        Dana     = nullptr;
        Espectro = nullptr;
        Cadaver  = nullptr;
        //
        ataqueEspadaNormal   = nullptr;
        ataqueArco           = nullptr;
        ataqueEspadaPoderoso = nullptr;
        defensaFerrea        = nullptr;
        curacionSimple       = nullptr;
        curacionGrupo        = nullptr;
        proyectilMagico      = nullptr;
        bolaFuego            = nullptr;
        //
        ataqueCuerpoACuerpo  = nullptr;
        ataqueADistancia     = nullptr;
        ataqueMagico         = nullptr;
        defensaCuerpoACuerpo = nullptr;
        defensaADistancia    = nullptr;
        defensaMagica        = nullptr;
        danoFisico           = nullptr;
        danoMagico           = nullptr;
        // INICIO GUILLEM //
        //musicote = nullptr;
        // FIN GUILLEM //
    }


}