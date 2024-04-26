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


    // controla si el caballo anda o está parado
    //bool animando;

    void inicia() override;
    void termina() override;
    void actualiza(double tiempo_seg) override;

public:
    // constructor
    IntroJuegoImagen(const string nombreArchvio);

};


inline IntroJuegoImagen::IntroJuegoImagen(const string nombreArchivo) {
    textura = new Textura{};
    imagen = new Imagen{};
    //std::filesystem::path archivo = std::filesystem::current_path();
    //archivo = archivo / "imagenes" / nombreArchivo;
    textura->carga("../Assets/Art/Sprites/Environment/" + nombreArchivo);
    imagen->asigna(textura);
    agregaDibujo(imagen);
}

inline void IntroJuegoImagen::inicia() {
    // posicion inicial de la imagen de la pala
    //tenemos en cuenta tamaño pala y tamaño pantalla para que empieze centrada
    posicion_x = 0;
    posicion_y = 0;
    //imagen->defineEstampas(1, 8);
    ponPosicion(Vector{ posicion_x, posicion_y });
}

inline void IntroJuegoImagen::termina() {
    extraeDibujos();
    delete imagen;
    delete textura;
}

inline void IntroJuegoImagen::actualiza(double tiempo_seg) {

}


#pragma once
