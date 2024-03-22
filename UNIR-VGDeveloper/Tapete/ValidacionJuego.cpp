// proyecto: Grupal/Tapete
// arhivo:   ValidacionJuego.cpp
// versión:  1.1  (9-Ene-2023)


#include "tapete.h"


namespace tapete {


    ValidacionJuego::ValidacionJuego (JuegoMesaBase * juego) {
        this->juego = juego;
    }


    ValidacionJuego::~ValidacionJuego () {
        juego = nullptr;
    }


    void ValidacionJuego::Construccion () {
        aserta (juego->modo () != nullptr && juego->sucesos () != nullptr, 
                L"El modo de juego debe estar configurado.", 
                LocalizaConfigura::Seccion_2_Modo_juego);
        aserta (juego->modo ()->juego () == juego && juego->sucesos ()->juego () == juego,
                L"El modo de juego y los sucesos del juego están mal configurados.", 
                LocalizaConfigura::Seccion_2_Modo_juego);
        aserta (juego->sucesos ()->modo () == juego->modo (), 
                L"El modo de juego y los sucesos del juego no están emparejados.", 
                LocalizaConfigura::Seccion_2_Modo_juego);
    }


    void ValidacionJuego::Tablero () {
        aserta (archivoAccesible (juego->tablero ()->archivoBaldosas (), { ".png" }), 
                L"El archivo '.png' de las imagenes del fondo del tablero es inválido.",
                LocalizaConfigura::Seccion_3_Tablero_parte_2);
        aserta (cadenaValida (juego->tablero ()->nombreEquipo (LadoTablero::Izquierda)),
                L"El nombre del equipo izquierdo es inválido.",
                LocalizaConfigura::Seccion_4_Personajes_parte_1);
        aserta (cadenaValida (juego->tablero ()->nombreEquipo (LadoTablero::Derecha)),
                L"El nombre del equipo derecho es inválido.",
                LocalizaConfigura::Seccion_4_Personajes_parte_1);
        aserta (archivoAccesible (juego->tablero ()->ArchivoEscudo (LadoTablero::Izquierda), { ".png" }),
                L"El archivo '.png' de la imagen del escudo izquierdo es inválido.",
                LocalizaConfigura::Seccion_4_Personajes_parte_1);
        aserta (archivoAccesible (juego->tablero ()->ArchivoEscudo (LadoTablero::Derecha), { ".png" }),
                L"El archivo '.png' de la imagen del escudo derecho es inválido.",
                LocalizaConfigura::Seccion_4_Personajes_parte_1);
        try {
            juego->tablero ()->validaGraficoMuros ();
        } catch (const std::logic_error & error) {
            throw ExcepcionConfigura {
                L"El gráfico de los muros del tablero no es válido:", 
                error.what (), 
                LocalizaConfigura::Seccion_3_Tablero_parte_3};
        }
    }


    void ValidacionJuego::Personajes () {
        int cuenta_izqrd = 0;
        int cuenta_derch = 0;
        for (int i = 0; i < juego->personajes ().size (); ++ i) {
            ActorPersonaje * persj = juego->personajes ().at (i);
            aserta (persj->juego () == juego && persj->ladoTablero () != LadoTablero::nulo,
                    std::format (L"El personaje {} está mal configurado.", i + 1),
                    LocalizaConfigura::Seccion_4_Personajes_parte_3);
            if (persj->ladoTablero () == LadoTablero::Izquierda) {
                aserta (persj->indiceEnEquipo () == cuenta_izqrd,
                        L"Los índices de los personajes en los equipos deben ser consecutivos.",
                        LocalizaConfigura::Seccion_4_Personajes_parte_3);
                cuenta_izqrd ++;
            } else {
                aserta (persj->indiceEnEquipo () == cuenta_derch,
                        L"Los índices de los personajes en los equipos deben ser consecutivos.",
                        LocalizaConfigura::Seccion_4_Personajes_parte_3);
                cuenta_derch ++;
            }
            aserta (cadenaValida (persj->nombre ()),
                    std::format (L"El nombre de personaje {} es inválido.", i + 1),
                    LocalizaConfigura::Seccion_4_Personajes_parte_3);
            aserta (archivoAccesible (persj->archivoRetrato (), { ".png" }), 
                    std::format (L"El archivo '.png' del retrato del personaje '{}' es inválido.", persj->nombre ()),
                    LocalizaConfigura::Seccion_4_Personajes_parte_3);
            aserta (archivoAccesible (persj->archivoFicha (), { ".png" }), 
                    std::format (L"El archivo '.png' de la ficha del personaje '{}' es inválido.", persj->nombre ()),
                    LocalizaConfigura::Seccion_4_Personajes_parte_3);
            aserta (persj->iniciativa () > 0, 
                    std::format (L"La iniciativa del personaje '{}' es inválida.", persj->nombre ()),
                    LocalizaConfigura::Seccion_4_Personajes_parte_3);
        }
        aserta (0 < cuenta_izqrd,
                L"No hay personajes en el equipo izquierdo.",
                LocalizaConfigura::Seccion_4_Personajes_parte_3);
        aserta (cuenta_izqrd <= 6,
                L"Hay demasiados personajes en el equipo izquierdo.",
                LocalizaConfigura::Seccion_4_Personajes_parte_3);
        aserta (0 < cuenta_derch,
                L"No hay personajes en el equipo derecho.",
                LocalizaConfigura::Seccion_4_Personajes_parte_3);
        aserta (cuenta_derch <= 6,
                L"Hay demasiados personajes en el equipo derecho.",
                LocalizaConfigura::Seccion_4_Personajes_parte_3);
        aserta (cuenta_izqrd == cuenta_derch,
                L"Debe haber el mismo número de personajes en cada equipo.",
                LocalizaConfigura::Seccion_4_Personajes_parte_3);
    }


    void ValidacionJuego::Habilidades () {
        aserta (juego->habilidades ().size () > 0,
                L"Debe haber al menos una habilidad.",
                LocalizaConfigura::Seccion_5_Habilidades_parte_2);
        for (int i = 0; i < juego->habilidades ().size (); ++ i) {
            Habilidad * habil = juego->habilidades () [i];
            aserta (cadenaValida (habil->nombre ()),
                    std::format (L"El nombre de la habilidad {} es inválido", i + 1),
                    LocalizaConfigura::Seccion_5_Habilidades_parte_2);
            switch (habil->tipoEnfoque ()) {
            case EnfoqueHabilidad::personaje:
            case EnfoqueHabilidad::area:
                aserta (habil->tipoAcceso () == AccesoHabilidad::directo || 
                        habil->tipoAcceso () == AccesoHabilidad::indirecto,
                        std::format (L"El tipo de acceso de la habilidad '{}' es inválido", habil->nombre ()),
                        LocalizaConfigura::Seccion_5_Habilidades_parte_2);
                aserta (habil->antagonista () == Antagonista::oponente || 
                        habil->antagonista () == Antagonista::aliado,
                        std::format (L"El tipo de antagonista de la habilidad '{}' es inválido", habil->nombre ()),
                        LocalizaConfigura::Seccion_5_Habilidades_parte_2);
                break;
            case EnfoqueHabilidad::si_mismo:
                aserta (habil->tipoAcceso () == AccesoHabilidad::ninguno,
                        std::format (L"El tipo de acceso de la habilidad '{}' es inválido", habil->nombre ()),
                        LocalizaConfigura::Seccion_5_Habilidades_parte_2);
                aserta (habil->antagonista () == Antagonista::si_mismo,
                        std::format (L"El tipo de antagonista de la habilidad '{}' es inválido", habil->nombre ()),
                        LocalizaConfigura::Seccion_5_Habilidades_parte_2);
                break;
            }
            aserta (cadenaValida (habil->descripcion ()),
                    std::format (L"La descripción de la habilidad '{}' es inválida",  habil->nombre ()),
                    LocalizaConfigura::Seccion_5_Habilidades_parte_2);
            aserta (archivoAccesible (habil->archivoImagen (), { ".png" }), 
                    std::format (L"El archivo '.png' de la imagen de la habilidad '{}' es inválido.", habil->nombre ()),
                    LocalizaConfigura::Seccion_5_Habilidades_parte_2);
            aserta (archivoAccesible (habil->archivoFondoImagen (), { ".png" }), 
                    std::format (L"El archivo '.png' de la imagen de fondo de la habilidad '{}' es inválido.", habil->nombre ()),
                    LocalizaConfigura::Seccion_5_Habilidades_parte_2);
        }
    }


    void ValidacionJuego::TiposEstadisticas () {
        aserta (juego->ataques ().size () > 0,
                L"Debe haber al menos un tipo de ataque.",
                LocalizaConfigura::Seccion_6_Estadisticas_parte_2);
        for (int i = 0; i < juego->ataques ().size (); i ++) {
            TipoAtaque * ataqu = juego->ataques () [i];
            aserta (cadenaValida (ataqu->nombre ()),
                    std::format (L"El nombre del ataque {} es inválida", i + 1),
                    LocalizaConfigura::Seccion_6_Estadisticas_parte_2);
        }
        aserta (juego->defensas ().size () > 0,
                L"Debe haber al menos un tipo de defensa.",
                LocalizaConfigura::Seccion_6_Estadisticas_parte_2);
        for (int i = 0; i < juego->defensas ().size (); i ++) {
            TipoDefensa * defns = juego->defensas () [i];
            aserta (cadenaValida (defns->nombre ()),
                    std::format (L"El nombre de la defensa {} es inválido", i + 1),
                    LocalizaConfigura::Seccion_6_Estadisticas_parte_2);
        }
        aserta (juego->danos ().size () > 0,
                L"Debe haber al menos un tipo de daño.",
                LocalizaConfigura::Seccion_6_Estadisticas_parte_2);
        for (int i = 0; i < juego->danos ().size (); i ++) {
            TipoDano * dano = juego->danos () [i];
            aserta (cadenaValida (dano->nombre ()),
                    std::format (L"El nombre del daño {} es inválido", i + 1),
                    LocalizaConfigura::Seccion_6_Estadisticas_parte_2);
        }

    }


    void ValidacionJuego::HabilidadesPersonajes () {
        for (int indc_persj = 0; indc_persj < juego->personajes ().size (); ++ indc_persj) {
            ActorPersonaje * persj = juego->personajes () [indc_persj];
            aserta (persj->habilidades ().size () > 0,
                    std::format (L"El personaje '{}' no tiene habilidades.", persj->nombre ()),
                    LocalizaConfigura::Seccion_8_Habilidades_personajes);
            aserta (persj->habilidades ().size () <= 10,
                    std::format (L"El personaje '{}' tiene demasiadas habilidades.", persj->nombre ()),
                    LocalizaConfigura::Seccion_8_Habilidades_personajes);
            int indc_habil = no_nulos (persj->habilidades ());
            aserta (indc_habil == -1,
                    std::format (L"La habilidad {} del personaje '{}' es inválida.", 
                                 indc_habil + 1, persj->nombre ()),
                    LocalizaConfigura::Seccion_8_Habilidades_personajes);
            indc_habil = pertenecen (persj->habilidades (), juego->habilidades ());
            aserta (indc_habil == -1,
                    std::format (L"La habilidad {} del personaje '{}' es desconocida.", 
                                 indc_habil + 1, persj->nombre ()),
                    LocalizaConfigura::Seccion_8_Habilidades_personajes);
            indc_habil = duplicados (persj->habilidades ());
            aserta (indc_habil == -1,
                    std::format (L"La habilidad {} del personaje '{}' está duplicada.", indc_habil + 1, persj->nombre ()),
                    LocalizaConfigura::Seccion_8_Habilidades_personajes);
        }
    }


    void ValidacionJuego::EstadisticasHabilidades () {
        for (int indc_habil = 0; indc_habil < juego->habilidades ().size (); ++ indc_habil) {
            Habilidad * habil = juego->habilidades () [indc_habil];
            //
            bool de_ataque        = false;
            bool de_curacion      = false;
            bool auto_aplicada    = false;
            bool afecta_personaje = false;
            bool afecta_area      = false;
            switch (habil->antagonista ()) {
            case Antagonista::oponente:
                de_ataque = true;
                break;
            case Antagonista::aliado:
                de_curacion = true;
                break;
            case Antagonista::si_mismo:
                auto_aplicada = true;
                break;
            }
            if (de_ataque || de_curacion) {
                switch (habil->tipoEnfoque ()) {
                case EnfoqueHabilidad::personaje:
                    afecta_personaje = true;
                    break;
                case EnfoqueHabilidad::area:
                    afecta_area = true;
                    break;
                }
            }
            // (a)
            aserta (0 < habil->coste (),
                    std::format (L"La habilidad '{}' no tiene coste.", habil->nombre ()),
                    LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            aserta (habil->coste () <= ActorPersonaje::maximoPuntosAccion,
                    std::format (L"La habilidad '{}' tiene un coste excesivo.", habil->nombre ()),
                    LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            // (b)
            if (de_ataque || de_curacion) {
                aserta (0 < habil->alcance (),
                        std::format (L"La habilidad '{}' no tiene alcance.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                aserta (habil->alcance () < RejillaTablero::filas + RejillaTablero::columnas,  // por poner algo
                        std::format (L"La habilidad '{}' tiene un alcance excesivo.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            } else {
                aserta (habil->alcance () == 0,
                        std::format (L"La habilidad '{}' no puede tener alcance.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (c)
            if (afecta_area) {
                aserta (0 < habil->radioAlcance (),
                        std::format (L"La habilidad '{}' no tiene un radio de área de alcance.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                aserta (habil->radioAlcance () < RejillaTablero::filas,  // por poner algo
                        std::format (L"La habilidad '{}' tiene un radio de área de alcance excesivo.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            } else {
                aserta (habil->radioAlcance () == 0,
                        std::format (L"La habilidad '{}' no puede tener radio de área de alcance.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (d)
            if (de_ataque) {
                aserta (habil->tipoAtaque () != nullptr,
                        std::format (L"La habilidad '{}' no tiene un tipo de ataque.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                aserta (pertenece (habil->tipoAtaque (), juego->ataques ()), 
                        std::format (L"La habilidad '{}' tiene un tipo de ataque desconocido.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            } else {
                aserta (habil->tipoAtaque () == nullptr,
                        std::format (L"La habilidad '{}' no puede tener un tipo de ataque.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (e)
            if (de_ataque) {
                aserta (habil->tipoDefensa () != nullptr,
                        std::format (L"La habilidad '{}' no tiene un tipo de defensa.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                aserta (pertenece (habil->tipoDefensa (), juego->defensas ()),
                        std::format (L"La habilidad '{}' tiene un tipo de defensa desconocido.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            } else {
                aserta (habil->tipoDefensa () == nullptr,
                        std::format (L"La habilidad '{}' no puede tener un tipo de defensa.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (f)
            if (de_ataque) {
                aserta (habil->tipoDano () != nullptr,
                        std::format (L"La habilidad '{}' no tiene un tipo de daño.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                aserta (pertenece (habil->tipoDano (), juego->danos ()),
                        std::format (L"La habilidad '{}' tiene un tipo de daño desconocido.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            } else {
                aserta (habil->tipoDano () == nullptr,
                        std::format (L"La habilidad '{}' no puede tener un tipo de daño.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (g)
            if (de_ataque) {
                aserta (0 < habil->valorDano (),
                        std::format (L"La habilidad '{}' no tiene un valor de daño.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                aserta (habil->valorDano () <= ActorPersonaje::maximaVitalidad,
                        std::format (L"La habilidad '{}' tiene un valor de daño excesivo.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            } else {
                aserta (habil->valorDano () == 0,
                        std::format (L"La habilidad '{}' no puede tener un valor de daño.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (h)
            if (de_curacion) {
                aserta (0 < habil->valorCuracion (),
                        std::format (L"La habilidad '{}' no tiene un valor de curación.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                aserta (habil->valorCuracion () <= ActorPersonaje::maximaVitalidad,
                        std::format (L"La habilidad '{}' tiene un valor de curación excesivo.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            } else {
                aserta (habil->valorCuracion () == 0,
                        std::format (L"La habilidad '{}' no puede tener un valor de curación.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (i) (k)
            if (auto_aplicada) {
                aserta (habil->efectosAtaque ().size () > 0 || habil->efectosDefensa ().size () > 0,
                        std::format (L"La habilidad '{}' debe tener al menos un efecto en ataque o en defensa.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                aserta ( (habil->efectosAtaque ().size () >  0 && habil->efectosDefensa ().size () == 0) ||
                        (habil->efectosAtaque ().size () == 0 && habil->efectosDefensa ().size () >  0), 
                        std::format (L"La habilidad '{}' no puede tener efectos en ataque y en defensa simultáneamente.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            } else {
                aserta (habil->efectosAtaque ().size () == 0 && habil->efectosDefensa ().size () == 0,
                        std::format (L"La habilidad '{}' no puede tener efectos en ataque o en defensa.", habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (i)
            if (auto_aplicada) {
                int indc_efect = no_nulos_pares (habil->efectosAtaque ());
                aserta (indc_efect == -1,
                        std::format (L"El efecto en ataque {} de la habilidad '{}' es inválido.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                indc_efect = pertenecen_pares (habil->efectosAtaque (), juego->ataques ());
                aserta (indc_efect == -1,
                        std::format (L"El efecto en ataque {} de la habilidad '{}' es desconocido.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                indc_efect = duplicados_pares (habil->efectosAtaque ());
                aserta (indc_efect == -1,
                        std::format (L"El efecto en ataque {} de la habilidad '{}' esta duplicado.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (j)
            if (auto_aplicada) {
                int indc_efect = tiene_valor_pares (habil->efectosAtaque ()); 
                aserta (indc_efect == -1,
                        std::format (L"El efecto en ataque {} de la habilidad '{}' no tiene valor.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                indc_efect = valor_acotado_pares (habil->efectosAtaque (), ActorPersonaje::maximaVitalidad); 
                aserta (indc_efect == -1,
                        std::format (L"El efecto en ataque {} de la habilidad '{}' no tiene un valor excesivo.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (k)
            if (auto_aplicada) {
                int indc_efect = no_nulos_pares (habil->efectosDefensa ());
                aserta (indc_efect == -1,
                        std::format (L"El efecto en defensa '{}' de la habilidad '{}' es inválido.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                indc_efect = pertenecen_pares (habil->efectosDefensa (), juego->defensas ());
                aserta (indc_efect == -1,
                        std::format (L"El efecto en defensa '{}' de la habilidad '{}' es desconocido.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                indc_efect = duplicados_pares (habil->efectosDefensa ());
                aserta (indc_efect == -1,
                        std::format (L"El efecto en defensa '{}' de la habilidad '{}' esta duplicado.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
            // (l)
            if (auto_aplicada) {
                int indc_efect = tiene_valor_pares (habil->efectosDefensa ()); 
                aserta (indc_efect == -1,
                        std::format (L"El efecto en defensa {} de la habilidad '{}' no tiene valor.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
                indc_efect = valor_acotado_pares (habil->efectosDefensa (), ActorPersonaje::maximaVitalidad); 
                aserta (indc_efect == -1,
                        std::format (L"El efecto en defensa {} de la habilidad '{}' no tiene un valor excesivo.", indc_efect + 1, habil->nombre ()),
                        LocalizaConfigura::Seccion_9_Estadisticas_habilidades);
            }
        }
    }


    void ValidacionJuego::EstadisticasPersonajes () {
        for (int indc_persj = 0; indc_persj < juego->personajes ().size (); ++ indc_persj) {
            ActorPersonaje * persj = juego->personajes () [indc_persj];
            //
            // (a)
            for (int indc_habil = 0; indc_habil < persj->habilidades ().size (); ++ indc_habil) {
                Habilidad * habil = persj->habilidades () [indc_habil];
                TipoAtaque * ataqu = habil->tipoAtaque (); 
                if (ataqu == nullptr) {
                    continue;
                }
                aserta (persj->apareceAtaque (ataqu),
                        std::format (L"El personaje '{}' debe tener el '{}'.", persj->nombre (), ataqu->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                aserta (persj->valorAtaque (ataqu) > 0,
                        std::format (L"El personaje '{}' debe tener un valor para el '{}'.", persj->nombre (), ataqu->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                aserta (persj->valorAtaque (ataqu) <= ActorPersonaje::maximaVitalidad,
                        std::format (L"El valor del '{}' del personaje '{}' es excesivo.", ataqu->nombre (), persj->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
            }
            //
            // (b)
            for (int indc_defns = 0; indc_defns < juego->defensas ().size (); ++ indc_defns) {
                TipoDefensa * defns = juego->defensas () [indc_defns];
                aserta (persj->apareceDefensa (defns),
                        std::format (L"El personaje '{}' debe tener la '{}'.", persj->nombre (), defns->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                aserta (persj->valorDefensa (defns) > 0,
                        std::format (L"El personaje '{}' debe tener un valor para la '{}'.", persj->nombre (), defns->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                aserta (persj->valorDefensa (defns) <= ActorPersonaje::maximaVitalidad,
                        std::format (L"El valor de la '{}' del personaje '{}' es excesivo.", defns->nombre (), persj->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
            }
            //
            // (c)
            for (int indc_dano = 0; indc_dano < juego->danos ().size (); ++ indc_dano) {
                TipoDano * dano = juego->danos () [indc_dano];
                aserta (persj->apareceReduceDano (dano),
                        std::format (L"El personaje '{}' debe tener la reducción de '{}'.", persj->nombre (), dano->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                aserta (persj->valorReduceDano (dano) >= 0,
                        std::format (L"El personaje '{}' debe tener un valor no negativo para la reducción de '{}'.", persj->nombre (), dano->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                aserta (persj->valorReduceDano (dano) <= ActorPersonaje::maximaVitalidad,
                        std::format (L"El valor de la reducción de '{}' del personaje '{}' es excesivo.", dano->nombre (), persj->nombre ()),
                        LocalizaConfigura::Seccion_10_Estadisticas_personajes);
            }
            // 
            // (d) 
            for (int indc_habil = 0; indc_habil < persj->habilidades ().size (); ++ indc_habil) {
                Habilidad * habil = persj->habilidades () [indc_habil];
                for (int indc_efect = 0; indc_efect < habil->efectosAtaque ().size (); ++ indc_efect) {
                    TipoAtaque * ataqu = habil->efectosAtaque () [indc_efect].first;
                    aserta (persj->apareceAtaque (ataqu),
                            std::format (L"El efecto en '{}' de la habilidad '{}' no aparece en el personaje '{}'.", 
                                         ataqu->nombre (), habil->nombre (), persj->nombre ()),
                            LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                    aserta (persj->valorAtaque (ataqu) > 0,
                            std::format (L"El personaje '{}' debe tener un valor para el '{}'.", persj->nombre (), ataqu->nombre ()),
                            LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                    aserta (persj->valorAtaque (ataqu) <= ActorPersonaje::maximaVitalidad,
                            std::format (L"El valor del '{}' del personaje '{}' es excesivo.", ataqu->nombre (), persj->nombre ()),
                            LocalizaConfigura::Seccion_10_Estadisticas_personajes);
                }
            }
            //
        }
    }


    void ValidacionJuego::SistemaAtaque () {        
        aserta (juego->sistemaAtaque ().efectividades ().size () > 0,
                L"Debe haber al menos un grado de efectividad en el ataque.",
                LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
        int valor = INT_MIN;
        for (int indc_efect = 0; indc_efect < juego->sistemaAtaque ().efectividades ().size (); ++ indc_efect) {
            GradoEfectividad * efect = juego->sistemaAtaque ().efectividades () [indc_efect];
            aserta (efect != nullptr,
                    std::format (L"El grado de efectividad {} es inválido.", indc_efect + 1),
                    LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
            aserta (cadenaValida (efect->nombre ()),
                    std::format (L"El nombre del grado de efectividad {} es inválido.", indc_efect + 1),
                    LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
            if (indc_efect == 0) {
                aserta (efect->valorInferiorAtaque () == INT_MIN,
                        std::format (L"El el valor inferior del grado de efectividad '{}' debe ser 'INT_MIN'.", efect->nombre ()),
                        LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
            } else {
                aserta (efect->valorInferiorAtaque () == valor,
                        std::format (L"El valor inferior del grado de efectividad '{}' debería ser {}.", efect->nombre (), valor),
                        LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
            }
            aserta (efect->valorInferiorAtaque () < efect->valorSuperioAtaque (),
                    std::format (L"Los valores del grado de efectividad '{}' no están en orden.", efect->nombre (), valor),
                    LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
            if (indc_efect == juego->sistemaAtaque ().efectividades ().size () - 1) {
                aserta (efect->valorSuperioAtaque () == INT_MAX,
                        std::format (L"El valor superior del grado de efectividad '{}' debe ser 'INT_MAX'.", efect->nombre ()),
                        LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
            } else {
                valor = efect->valorSuperioAtaque () + 1;
            }
            aserta (efect->porcentajeDano () >= 0,
                    std::format (L"El porcentaje de daño del grado de efectividad '{}' no puede ser negativo.", efect->nombre ()),
                    LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
            aserta (efect->porcentajeDano() <= 200,
                    std::format (L"El porcentaje de daño del grado de efectividad '{}' es excesivo.", efect->nombre ()),
                    LocalizaConfigura::Seccion_7_Grados_efectividad_parte_2);
        }
    }


    void ValidacionJuego::ConfiguraJuego () {
        aserta (0 < juego->modo ()->puntosAccionDeDesplaza (),
                L"El consumo de puntos de acción de los desplazamientos no se ha establecido.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        aserta (juego->modo ()->puntosAccionDeDesplaza () <= 1000,  // son 1000 píxeles
                L"El consumo de puntos de acción de los desplazamientos es excesivo.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        for (int indc_persj = 0; indc_persj < juego->personajes ().size (); indc_persj ++) {
            ActorPersonaje * persj = juego->personajes () [indc_persj];
            Coord sitio = persj->sitioFicha ();
            aserta (1 <= sitio.fila () && sitio.fila () <= RejillaTablero::filas, 
                    std::format (L"La posición inicial de la ficha del personaje '{}' no es válida.", persj->nombre ()),
                    LocalizaConfigura::Seccion_11_Miscelanea);
            aserta (1 <= sitio.coln () && sitio.coln () <= RejillaTablero::columnas, 
                    std::format (L"La posición inicial de la ficha del personaje '{}' no es válida.", persj->nombre ()),
                    LocalizaConfigura::Seccion_11_Miscelanea);
        }
        aserta (archivoAccesible (juego->tablero ()->archivoSonidoEstablece (), { ".wav", ".ogg", ".flac" }),
                L"El archivo del sonido de establecimiento es inválido.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        aserta (0 <= juego->tablero ()->volumenSonidoEstablece () && 
                juego->tablero ()->volumenSonidoEstablece () <= 100,
                L"El volumen del sonido de establecimiento es inválido.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        aserta (archivoAccesible (juego->tablero ()->archivoSonidoDesplaza (), { ".wav", ".ogg", ".flac" }),
                L"El archivo del sonido de desplazamiento es inválido.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        aserta (0 <= juego->tablero ()->volumenSonidoDesplaza () && 
                juego->tablero ()->volumenSonidoDesplaza () <= 100,
                L"El volumen del sonido de desplazamiento es inválido.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        aserta (archivoAccesible (juego->musica ()->archivoMusica (), { ".wav", ".ogg", ".flac" }),
                L"El archivo del sonido de la música es inválido.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        aserta (0 <= juego->musica ()->volumenMusica () && 
                juego->musica ()->volumenMusica () <= 100,
                L"El volumen del sonido de la música es inválido.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        aserta (juego->nombresAlumnos ().size () > 0,
                L"No se han indicado los nombres de los alumnos.",
                LocalizaConfigura::Seccion_11_Miscelanea);
        for (int i = 0; i < juego->nombresAlumnos ().size (); ++ i) {
            const wstring & alumn = juego->nombresAlumnos () [i];
            aserta (cadenaValida (alumn),
                    std::format (L"El nombre del alumno {} es inválido", i + 1),
                    LocalizaConfigura::Seccion_11_Miscelanea);
        }
        aserta (cadenaValida (juego->cursoAcademico ()),
                std::format (L"La indicación del curso academico es inválida"),
                LocalizaConfigura::Seccion_11_Miscelanea);
    }


    bool ValidacionJuego::archivoAccesible (
            const string & archivo, std::initializer_list <string> extensiones) {
        std::filesystem::path camino {archivo};
        if (! std::filesystem::is_regular_file (camino)) {
            return false;  
        } 
        bool esta = false;
        for (const string & extns : extensiones) {
            if (camino.extension () == extns) {
                esta = true;
                break;
            }
        }
        if (! esta) {
            return false;
        }
        std::filesystem::perms permisos = std::filesystem::status (camino).permissions ();
        if ( (permisos & std::filesystem::perms::owner_read) == std::filesystem::perms::none) {
            return false;
        }
        return true;
    }


    bool ValidacionJuego::cadenaValida (const wstring & nombre) {
        if (nombre.length () == 0) {
            return false;
        }
        if (nombre.at (0) == ' ' || nombre.at (nombre.length () - 1) == ' ') {
            return false;
        }
        return true;
    }


    void ValidacionJuego::aserta (
            bool condicion, wstring mensaje, const LocalizaConfigura localiza) {
        if (condicion) {
            return;
        }
        throw ExcepcionConfigura {mensaje, localiza};
    }


}