
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
// Archivo: Rendidor.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"

using namespace unir2d;


/// @cond


Color Color::rgbaDeHsl (int matiz, int saturacion, int luminosidad, int alfa) {
    float h =  (float) matiz;
    float s = ((float) saturacion ) / 100.0f;
    float l = ((float) luminosidad) / 100.0f;
    //
    float C = (1.0f - std::abs (2 * l - 1.0f)) * s;
    float H = h / 60.0f;
    float X = C * ( 1.0f - std::abs (std::fmodf (H, 2) - 1.0f)); 
    //
    float R;
    float G;
    float B;
    if (H < 1) {
        R = C;  G = X;  B = 0;
    } else if (H < 2) {
        R = X;  G = C;  B = 0;
    } else if (H < 3) {
        R = 0;  G = C;  B = X;
    } else if (H < 4) {
        R = 0;  G = X;  B = C;
    } else if (H < 5) {
        R = X;  G = 0;  B = C;
    } else {  // (H < 6) 
        R = C;  G = 0;  B = X;
    }
    //
    float m = l - (C / 2.0f);
    R = (R + m) * 255;
    G = (G + m) * 255;
    B = (B + m) * 255;
    //
    return Color {(int) R, (int) G, (int) B, alfa}; 
}


Color Color::rgbaDeHsv (int matiz, int saturacion, int brillo, int alfa) {
    float h =  (float) matiz;                                           // es H
    float s = ((float) saturacion ) / 100.0f;                           // es Sv
    float v = ((float) brillo     ) / 100.0f;                           // es V
    //
    float C = v * s;                                                    // es C
    float H = h / 60.0f;                                                // es H' 
    float X = C * ( 1.0f - std::abs (std::fmodf (H, 2) - 1.0f));        // es X
    //
    float R;                                                            // es R1
    float G;                                                            // es G1
    float B;                                                            // es B1
    if (H < 1) {
        R = C;  G = X;  B = 0;
    } else if (H < 2) {
        R = X;  G = C;  B = 0;
    } else if (H < 3) {
        R = 0;  G = C;  B = X;
    } else if (H < 4) {
        R = 0;  G = X;  B = C;
    } else if (H < 5) {
        R = X;  G = 0;  B = C;
    } else {  // (H < 6) 
        R = C;  G = 0;  B = X;
    }
    //
    float m = v - C;
    R = (R + m) * 255;
    G = (G + m) * 255;
    B = (B + m) * 255;
    //
    return Color {(int) R, (int) G, (int) B, alfa}; 
}


int Color::matiz () {
    float R = ((float) this->m_rojo ) / 255.0f;
    float G = ((float) this->m_verde) / 255.0f;
    float B = ((float) this->m_azul ) / 255.0f;
    //
    float M = std::max ({R, G, B});     // Xmax         V
    float m = std::min ({R, G, B});     // Xmin         V - C
    float C = M - m;
    //
    //float H;
    //if (C == 0) {
    //    H = 0.0f;
    //} else {
    //    if (M == R) {
    //        H = (G - B) / C; 
    //        H = std::fmodf (H, 6);        
    //    } else if (M == G) {
    //        H = ((B - R) / C) + 2.0f;
    //    } else {  // (M == B)
    //        H = ((R - G) / C) + 4.0f;
    //    }
    //    H = H * 60.0f;
    //}
    float H;
    if (C == 0) {
        H = 0;
    } else if (M == R) {
        H = (float) (360.0f + 60.0f * (G - B) / C);
        H = std::fmodf (H, 360);        
    } else if (M == G) {
        H = (float) (120.0f + 60.0f * (B - R) / C);
    } else {  // (M == B)
        H = (float) (240.0f + 60.0f * (R - G) / C);
    }
    //
    return (int) H;    
}


// L del modelo HSL
int Color::luminosidad () {
    float R = ((float) this->m_rojo ) / 255.0f;
    float G = ((float) this->m_verde) / 255.0f;
    float B = ((float) this->m_azul ) / 255.0f;
    //
    float M = std::max ({R, G, B});
    float m = std::min ({R, G, B});
    //
    float L = (M + m) / 2.0f;
    //
    return (int) (L * 100.0f);   
}


// I del modelo HSI
int Color::intensidad () {
    float R = ((float) this->m_rojo ) / 255.0f;
    float G = ((float) this->m_verde) / 255.0f;
    float B = ((float) this->m_azul ) / 255.0f;
    //
    float I = (R + G + B) / 3.0f;
    //
    return (int) (I * 100.0f);    
}


// V del modelo HSV
int Color::brillo () {
    float R = ((float) this->m_rojo ) / 255.0f;
    float G = ((float) this->m_verde) / 255.0f;
    float B = ((float) this->m_azul ) / 255.0f;
    //
    float V = std::max ({R, G, B});
    //
    return (int) (V * 100.0f);    
}


// S del modelo HSL
int Color::saturacionL () {
    float R = ((float) this->m_rojo ) / 255.0f;
    float G = ((float) this->m_verde) / 255.0f;
    float B = ((float) this->m_azul ) / 255.0f;
    //
    float M = std::max ({R, G, B});
    float m = std::min ({R, G, B});
    float C = M - m;
    //
    float S;
    float L = (M + m) / 2.0f;
    if (C == 0.0f) {
        S = 0.0f;
    } else {
        S = 1.0f - std::abs (M + m - 1.0f);
        S = C / S;
    }
    // 
    return (int) (S * 100.0f);    
}


// S del modelo HSV
int Color::saturacionV () {
    float R = ((float) this->m_rojo ) / 255.0f;
    float G = ((float) this->m_verde) / 255.0f;
    float B = ((float) this->m_azul ) / 255.0f;
    //
    float M = std::max ({R, G, B});
    float m = std::min ({R, G, B});
    float C = M - m;
    //
    float S;
    if (M == 0) {
        S = 0.0f;
    } else {
        S = 1.0f - (m / M);
    }
    //
    return (int) (S * 100.0f);    
}


// S del modelo HSI
int Color::saturacionI () {
    float R = ((float) this->m_rojo ) / 255.0f;
    float G = ((float) this->m_verde) / 255.0f;
    float B = ((float) this->m_azul ) / 255.0f;
    //
    float M = std::max ({R, G, B});
    float m = std::min ({R, G, B});
    float C = M - m;
    //
    float I = (R + G + B) / 3.0f;
    //
    float S;
    if (I == 0.0f) {
        S = 0.0f;
    } else {  // (M + m > 0.5f) 
        S = 1.0f - (m / I);
    }
    //
    return (int) (S * 100.0f);    
}


/// @endcond

