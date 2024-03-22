// proyecto: Grupal/Tapete
// arhivo:   ValidacionJuego.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class ValidacionJuego {
    public:

        explicit ValidacionJuego (JuegoMesaBase * juego);
        ~ValidacionJuego ();

        void Construccion            ();
        void Tablero                 ();
        void Personajes              ();
        void Habilidades             ();
        void TiposEstadisticas       ();
        void HabilidadesPersonajes   ();
        void EstadisticasHabilidades ();
        void EstadisticasPersonajes  ();
        void SistemaAtaque           ();
        void ConfiguraJuego          ();

    private:

        JuegoMesaBase * juego {}; 

        bool archivoAccesible (const string  & archivo, std::initializer_list <string> extensiones);
        bool cadenaValida     (const wstring & nombre);


        template <typename E>
        static bool pertenece (const E & elemento, const std::vector <E> & conjunto) {
            for (int indc_conjt = 0; indc_conjt < conjunto.size (); ++ indc_conjt) {
                if (elemento == conjunto [indc_conjt]) {
                    return true;
                }
            }
            return false;
        }        

        template <typename E>
        static int no_nulos (const std::vector <E> & lista) {
            for (int indc = 0; indc < lista.size (); ++ indc) {
                if (lista [indc] == nullptr) {
                    return indc;
                }
            }
            return -1;
        }

        template <typename E>
        static int no_nulos_pares (const std::vector <std::pair <E, int>> & lista) {
            for (int indc = 0; indc < lista.size (); ++ indc) {
                if (lista [indc].first == nullptr) {
                    return indc;
                }
            }
            return -1;
        }

        template <typename E>
        static int pertenecen (const std::vector <E> & elementos, const std::vector <E> & conjunto) {
            for (int indc_elemt = 0; indc_elemt < elementos.size (); ++ indc_elemt) {
                bool esta = false;
                for (int indc_conjt = 0; indc_conjt < conjunto.size (); ++ indc_conjt) {
                    if (elementos [indc_elemt] == conjunto [indc_conjt]) {
                        esta = true;
                        break;
                    }
                }
                if (! esta) {
                    return indc_elemt;
                }
            }
            return -1;
        }

        template <typename E>
        static int pertenecen_pares (const std::vector <std::pair <E, int>> & elementos, const std::vector <E> & conjunto) {
            for (int indc_elemt = 0; indc_elemt < elementos.size (); ++ indc_elemt) {
                bool esta = false;
                for (int indc_conjt = 0; indc_conjt < conjunto.size (); ++ indc_conjt) {
                    if (elementos [indc_elemt].first == conjunto [indc_conjt]) {
                        esta = true;
                        break;
                    }
                }
                if (! esta) {
                    return indc_elemt;
                }
            }
            return -1;
        }

        template <typename E>
        static int duplicados (const std::vector <E> & lista) {
            for (int indc_elemt = 0; indc_elemt < lista.size (); ++ indc_elemt) {
                for (int indc_prev = indc_elemt - 1; indc_prev >= 0; -- indc_prev) {
                    if (lista [indc_elemt] == lista [indc_prev]) {
                        return indc_elemt;
                    }
                }
            }
            return -1;
        }

        template <typename E>
        static int duplicados_pares (const std::vector <std::pair <E, int>> & lista) {
            for (int indc_elemt = 0; indc_elemt < lista.size (); ++ indc_elemt) {
                for (int indc_prev = indc_elemt - 1; indc_prev >= 0; -- indc_prev) {
                    if (lista [indc_elemt].first == lista [indc_prev].first) {
                        return indc_elemt;
                    }
                }
            }
            return -1;
        }

        template <typename E>
        static int tiene_valor_pares (const std::vector <std::pair <E, int>> & lista) {
            for (int indc_elemt = 0; indc_elemt < lista.size (); ++ indc_elemt) {
                for (int indc_prev = indc_elemt - 1; indc_prev >= 0; -- indc_prev) {
                    if (lista [indc_elemt].second <= 0) {
                        return indc_elemt;
                    }
                }
            }
            return -1;
        }

        template <typename E>
        static int valor_acotado_pares (const std::vector <std::pair <E, int>> & lista, int cota) {
            for (int indc_elemt = 0; indc_elemt < lista.size (); ++ indc_elemt) {
                for (int indc_prev = indc_elemt - 1; indc_prev >= 0; -- indc_prev) {
                    if (cota < lista [indc_elemt].second) {
                        return indc_elemt;
                    }
                }
            }
            return -1;
        }


        void aserta (bool condicion, wstring mensaje, const LocalizaConfigura localiza);

    };


}