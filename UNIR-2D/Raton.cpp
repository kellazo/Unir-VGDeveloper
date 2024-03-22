
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
// Archivo: Raton.cpp
// Autor:   Miguel Angel Zurita Cortés
// Versión: 1.2 (10-Oct-2022)
// Estado:  Terminado. Revisado. No documentado.


#include "UNIR-2D.h"
#include <Windows.h>

using namespace unir2d;


void Raton::configura (Rendidor * rendidor) {
    winHandle = rendidor->window->getSystemHandle ();
    momento_clic = std::chrono::steady_clock::time_point::min ();
}


void Raton::sondea () {
    if (GetFocus () != winHandle) {
        for (int indc = 0; indc < s_pulsado.size (); ++ indc) {
            s_pulsado [indc] = false;
        }
        s_doble_clic = false;
        return;
    }
    //s_pulsado = false;
    sondeaPulsado (BotonRaton::izquierda);
    sondeaPulsado (BotonRaton::derecha);
    sondeaPulsado (BotonRaton::centro);
    sondeaDobleClic ();
    sondeaPosicion ();
}


void Raton::sondeaPulsado (BotonRaton boton) {
    int vkey = 0;
    switch (boton) {
        case BotonRaton::izquierda:  
            if (GetSystemMetrics (SM_SWAPBUTTON) == 0) {
                vkey = VK_LBUTTON; 
            } else {
                vkey = VK_RBUTTON; 
            }
            break;
        case BotonRaton::derecha:    
            if (GetSystemMetrics (SM_SWAPBUTTON) == 0) {
                vkey = VK_RBUTTON; 
            } else {
                vkey = VK_LBUTTON; 
            }
            break;
        case BotonRaton::centro:   
            vkey = VK_MBUTTON;  
            break;
        default:
            return;
    }
    int indice = static_cast <int> (boton);
    if ((GetAsyncKeyState(vkey) & 0x8000) != 0) {
        s_pulsado [indice] = true;
    } else {
        s_pulsado   [indice] = false;
        s_consumido [indice] = false;
    }
}


void Raton::sondeaDobleClic () {
    int vkey = 0;
    if (GetSystemMetrics (SM_SWAPBUTTON) == 0) {
        vkey = VK_LBUTTON; 
    } else {
        vkey = VK_RBUTTON; 
    }
    bool clic = (GetAsyncKeyState(vkey) & 0x8000) != 0;
    if (! clic) {
        s_doble_clic = false;
        return;
    }
    //
	Momento ahora = std::chrono::steady_clock::now ();
    std::chrono::nanoseconds lapso = ahora - momento_clic;        
    momento_clic = ahora;
    //
    constexpr std::chrono::nanoseconds ms__50 { 50 * 1000 * 1000};  // 50 millisegundos
    constexpr std::chrono::nanoseconds ms_200 {200 * 1000 * 1000}; // 200 millisegundos
    //
    if (lapso > ms_200) {
        s_doble_clic = false;
        return;
    }
    if (lapso < ms__50) {
        s_doble_clic = false;
        return;
    }
    s_doble_clic = true;
}


void Raton::sondeaPosicion () {
    POINT raton;
    GetCursorPos (& raton);
    WINDOWINFO win_info;
    BOOL bien =  GetWindowInfo (winHandle, & win_info);
    s_posicion = Vector {
            (float) (raton.x - win_info.rcClient.left), 
            (float) (raton.y - win_info.rcClient.top ) };
}


bool Raton::pulsando (BotonRaton boton) {
    int indice = static_cast <int> (boton);
    if (s_consumido [indice]) {
        return false;
    }
    return s_pulsado [indice];
//    return s_pulsado && s_boton == boton;
}


void Raton::consumePulsado (BotonRaton boton) {
    int indice = static_cast <int> (boton);
    s_consumido [indice] = true;
    //if (s_pulsado && s_boton == boton) {
    //    s_pulsado = false;
    //}
}


bool Raton::dobleClic () {
    return s_doble_clic;
}


void Raton::consumeDobleClic () {
    s_doble_clic = false;
}


Vector Raton::posicion () {
    return s_posicion;
}

