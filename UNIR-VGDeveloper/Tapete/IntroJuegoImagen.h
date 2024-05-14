// archivo IntroJuegoImagen.h Raimon

#pragma once

#include <UNIR-2D.h>

using namespace unir2d;


class IntroJuegoImagen : public ActorBase {
private:

    Textura* textura;
    Imagen* imagen;

    // posición en la que aparece la imagen en el eje_x y eje_y
    float posicion_x = 0;
    float posicion_y = 0;
    float posicionInicialX;
    float posicionInicialY;
    float velocidadDesplazamientoArriba;
    int numeroDeFotogramasColumnas;
    int numeroDeFotogramasFilas;
    int numeroDeFotogramas;
    int ultimoFotogramaReproducido = 0;
    bool bucle;
    bool conSonido;
    string pathSonido;
    Sonido* ptr_sonido;


    // controla si el caballo anda o está parado
    //bool animando;

    void inicia() override;
    void termina() override;
    void actualiza(double tiempo_seg) override;

public:
    // constructor
    IntroJuegoImagen(const string pathArchivo, float posicionInicialX = 0,
        float posicionInicialY = 0, float velocidadDesplazamientoArriba = 0, int numeroDeFotogramasColumnas = 0, int numeroDeFotogramasFilas = 0, bool bucle = false, string pathSonido = "");

};


inline IntroJuegoImagen::IntroJuegoImagen(const string pathArchivo, float posicionInicialX, 
    float posicionInicialY, float velocidadDesplazamientoArriba, int numeroDeFotogramasColumnas, int numeroDeFotogramasFilas, bool bucle, string pathSonido) {
    
    this->posicionInicialX = posicionInicialX;
    this->posicionInicialY = posicionInicialY;
    this->velocidadDesplazamientoArriba = velocidadDesplazamientoArriba;
    this->numeroDeFotogramasColumnas = numeroDeFotogramasColumnas;
    this->numeroDeFotogramasFilas = numeroDeFotogramasFilas;
    this->numeroDeFotogramas = numeroDeFotogramasColumnas * numeroDeFotogramasFilas;
    this->bucle = bucle;
    this->pathSonido = pathSonido;

    textura = new Textura{};
    imagen = new Imagen{};
    //std::filesystem::path archivo = std::filesystem::current_path();
    //archivo = archivo / "imagenes" / nombreArchivo;
    textura->carga(pathArchivo);
    imagen->asigna(textura);
    agregaDibujo(imagen);
}

inline void IntroJuegoImagen::inicia() {
    // posicion inicial de la imagen de la pala
    //tenemos en cuenta tamaño pala y tamaño pantalla para que empieze centrada
    posicion_x = posicionInicialX;
    posicion_y = posicionInicialY;
    if(numeroDeFotogramasColumnas > 0 || numeroDeFotogramasFilas > 0)
        imagen->defineEstampas(numeroDeFotogramasFilas, numeroDeFotogramasColumnas);
    ponPosicion(Vector{ posicion_x, posicion_y });

    // comprueba si la imagen ha de ir sincronizada con alguna pista de audio
    if (pathSonido != "") {
        conSonido = true;
        ptr_sonido = new unir2d::Sonido{};
        ptr_sonido->abre(pathSonido);
    }
    else {
        conSonido = false;
    }
}

inline void IntroJuegoImagen::termina() {
    extraeDibujos();
    delete imagen;
    delete textura;
    if (conSonido) {
        delete ptr_sonido;
    }
}

inline void IntroJuegoImagen::actualiza(double tiempo_seg) {
    
    // si se trata de imagen con fotogramas tilesheet, congela el último fotograma hasta que finalize el tiempo
    if (numeroDeFotogramas > 0 && (bucle || (ultimoFotogramaReproducido != numeroDeFotogramas))) {
        int indice = ((int)(tiempo_seg * 10)) % numeroDeFotogramas + 1;
        // dispara pista de sonido a cada inicio de bucle
        if (indice == 1 && conSonido) {
            ptr_sonido->suena();
        }
        ultimoFotogramaReproducido = indice;
        int puntero = indice;
        int fila = 1;
        int columna = indice % numeroDeFotogramasColumnas;
        if (columna == 0)
            columna = numeroDeFotogramasColumnas;
        while (puntero > numeroDeFotogramasColumnas) {
            fila++;
            puntero -= numeroDeFotogramasColumnas;
        }
        //std::cout << "c=" << columna << " f=" << fila << std::endl;
        imagen->seleccionaEstampa(fila, columna);
        // deja en pausa 1 segundo el último fotograma
        //if(indice == numeroDeFotogramas)

    }

    // si es imagen con scroll vertical
    if (velocidadDesplazamientoArriba > 0)
    {
        posicion_y -= velocidadDesplazamientoArriba;
        ponPosicion(Vector{ posicion_x, posicion_y });
    }
}


#pragma once
