// proyecto: Grupal/Tapete
// arhivo:   SistemaAtaque.h
// versión:  1.1  (9-Ene-2023)


#pragma once


namespace tapete {


    class SistemaAtaque {
    public:

        explicit SistemaAtaque (JuegoMesaBase * juego);
        ~SistemaAtaque ();

        const std::vector <GradoEfectividad *> & efectividades () const;
        void agregaEfectividad (GradoEfectividad * elemento);

        ActorPersonaje * atacante () const;
        Habilidad *      habilidad () const;


        // Hay habilidades de ataque, que un personaje (el personaje atacante) usa para disminuir el 
        // valor de la vitalidad del personaje sobre el que se aplica (el personaje atacado).
        // Si la habilidad se usa en un área puede haber mas de un personaje afectado por la 
        // habilidad. En esta caso, el personaje atacado puede ser del mismo equipo que el personaje 
        // atacante o puede ser del equipo contrario.
        // Si el personaje atacado tiene vitalidad cero (está muerto) el ataque no tiene efecto. 
        // Además, el ataque no puede hacer que la vitalidad sea inferior a cero ni superior a la 
        // vitalidad inicial de los personajes.
        // Esta estructura de datos se crea mediante el segundo método 'calcula'. 
        struct AtaqueOponente {
            // personaje atacado
            ActorPersonaje *   oponente;              
            // tipo de ataque de la habilidad 
            TipoAtaque *       tipo_ataque;           
            // valor del ataque en el personaje atacante (para el tipo de ataque)
            int                valor_ataque;          
            // tipo de defensa de la habilidad
            TipoDefensa *      tipo_defensa;          
            // valor de la defensa en el personaje atacado (para el tipo de defensa)
            int                valor_defensa;         
            // valor del ataque menos valor de la defensa
            int                ventaja;               
            // valor aleatorio entre 0 y 99 obtenido antes del ataque
            int                aleatorio_100;         
            // ventaja aumentada con el valor aleatorio
            int                valor_final_ataque;                                                                                        
            // instancia de los grados de efectividad seleccionada para el valor final del ataque    
            GradoEfectividad * efectividad;           
            // porcentaje de daño según el grados de efectividad para el valor final del ataque   
            int                porciento_dano;        
            // tipo de daño de la habilidad
            TipoDano *         tipo_dano;             
            // valor del daño de la habilidad
            int                valor_dano;            
            // valor del daño ajustado con el porcentaje de daño
            int                valor_ajustado_dano;   
            // valor de reducción del daño en el personaje atacado (para el tipo de daño)
            int                valor_reduce_dano;     
            // valor ajustado del daño menos valor de reducción del daño
            int                valor_final_dano;      
            // vitalidad original del oponente
            int                vitalidad_origen;      
            // vitalidad del oponente ajustada con el valor final del daño
            int                vitalidad_final;       
        };
        const std::vector <AtaqueOponente> & ataquesOponente () const;


        // Hay habilidades de curación, lo que significa que la habilidad cambia el valor de la 
        // vitalidad del personaje sobre el que se aplica (el personaje curado). El cambio se 
        // realiza usando un valor establecido en la habilidad llamado valor de curación.
        // Si la habilidad se usa en un área puede haber mas de un personaje afectado por la 
        // habilidad. En esta caso, el personaje curado puede ser del mismo equipo que el personaje 
        // que usa la habilidad o puede ser del equipo contrario.
        // Si el personaje curado tiene vitalidad cero (está muerto) la curación no tiene efecto. 
        // Además, la curación no puede hacer que la vitalidad sea sea inferior a cero (si fuera 
        // posible) ni superior a la vitalidad inicial de los personajes.
        // Esta estructura de datos se crea mediante el tercer método 'calcula'. 
        struct CuracionOponente {
            // personaje sobre el que se aplica la curación
            ActorPersonaje * oponente;   
            // valor de curación de la habilidad
            int              valor_curacion;        
            // vitalidad original del personaje 
            int              vitalidad_origen;      
            // vitalidad del personaje ajustada con el valor de curación
            int              vitalidad_final;       
        };
        const std::vector <CuracionOponente> & curacionesOponente ()  const;


        // Una habilidad puede producir efectos en los valores de ataque y defensa de un personaje. 
        // La habilidad debe ser "auto-aplicada", es decir, el personaje que usa la habilidad es el 
        // mismo al que se aplica la habilidad.
        // La habilidad puede tener efectos en uno o más tipos de ataque o en uno o más tipos de 
        // defensa. El efecto en cada tipo consiste en cambiar el valor establecido en el personaje 
        // para el tipo de ataque o de defensa.
        // A inicio de una ronda de juego nueva, el personaje recupera los valores iniciales de los 
        // ataques y defensas.
        // Esta estructura de datos se crea mediante el primer método 'calcula'. 
        struct CambioEfecto {                                                   
            // tipo de ataque del efecto de la habilidad (puede ser nulo, si es defensa)  
            TipoAtaque *  tipo_ataque;              
            // valor del cambio de ataque del efecto de la habilidad, para el tipo de ataque 
            int           valor_cambio_ataque;      
            // valor original del ataque del personaje para el tipo de ataque
            int           valor_origen_ataque;      
            // valor resultante del ataque del personaje para el tipo de defensa, tras aplicar el 
            // efecto
            int           valor_final_ataque;       
            // tipo de defensa del efecto de la habilidad (puede ser nulo, si es ataque)    
            TipoDefensa * tipo_defensa;             
            // valor del cambio de defensa del efecto de la habilidad, para el tipo de defensa
            int           valor_cambio_defensa;     
            // valor original de la defensa del personaje para el tipo de defensa
            int           valor_origen_defensa;     
            // valor resultante de la defensa del personaje para el tipo de defensa, tras aplicar el 
            // efecto
            int           valor_final_defensa;      
        };
        const std::vector <CambioEfecto> & cambiosEfecto () const; 


        // Cálculo para una habilidad "auto-aplicada":
        // Usado cuando la habilidad tiene: 
        //      tipoEnfoque = EnfoqueHabilidad::si_mismo
        //      tipoAcceso  = AccesoHabilidad::ninguno
        //      antagonista = Antagonista::si_mismo
        void calcula (
                ActorPersonaje * atacante, 
                Habilidad *      habilidad);

        // Cálculo para una habilidad "de ataque" o "de curación", que "afecta a personaje"
        // Usado cuando la habilidad tiene: 
        //      tipoEnfoque = EnfoqueHabilidad::personaje
        //      tipoAcceso  = { AccesoHabilidad::directo, AccesoHabilidad::indirecto }
        //      antagonista = { Antagonista::oponente, Antagonista::aliado }
        // Clasificación de la habilidad:
        //      antagonista = Antagonista::oponente ==> "de ataque"
        //      antagonista = Antagonista::aliado   ==> "de curación"
        void calcula (
                ActorPersonaje * atacante, 
                Habilidad *      habilidad,
                ActorPersonaje * oponente, 
                int              aleatorio_100);

        // Cálculo para una habilidad "de ataque" o "de curación", que "afecta a área"
        // Usado cuando la habilidad tiene: 
        //      tipoEnfoque = EnfoqueHabilidad::area
        //      tipoAcceso  = { AccesoHabilidad::directo, AccesoHabilidad::indirecto }
        //      antagonista = { Antagonista::oponente, Antagonista::aliado }
        // Clasificación de la habilidad:
        //      antagonista = Antagonista::oponente ==> "de ataque"
        //      antagonista = Antagonista::aliado   ==> "de curación"
        void calcula (
                ActorPersonaje *               atacante, 
                Habilidad *                    habilidad,
                std::vector <ActorPersonaje *> lista_oponentes, 
                int                            aleatorio_100);
        
    private:

        JuegoMesaBase * juego {}; 

        std::vector <GradoEfectividad *> grados_efectividad {};

        ActorPersonaje * atacante_;
        Habilidad *      habilidad_;

        std::vector <AtaqueOponente>   ataques_oponente {};
        std::vector <CuracionOponente> curaciones_oponente {};
        std::vector <CambioEfecto>     cambios_efecto {}; 


        void reinicia ();

        void calculaAtaque   (ActorPersonaje * oponente, int aleatorio_100);
        void calculaCuracion (ActorPersonaje * oponente);

    };


}




