// proyecto: Grupal/Tapete
// archivo:  tapete.h
// versión:  1.1  (9-Ene-2023)


#pragma once


#include <UNIR-2D.h>
using Vector = unir2d::Vector;
using Coord  = unir2d::Coord;
using Region = unir2d::Region;
using Color  = unir2d::Color;


#include <sstream>

#include "LadoTablero.h"
#include "TipoEstadistica.h"
#include "Habilidad.h"
#include "CuadroIndica.h"

#include "Excepciones.h"

#include "PresenciaPersonaje.h"
#include "CalculoCaminos.h"
#include "ActorPersonaje.h"

#include "PresenciaTablero.h"
#include "RejillaTablero.h"
#include "PresenciaHabilidades.h"
#include "PresenciaActuante.h"
#include "VistaCaminoCeldas.h"
#include "ListadoAyuda.h"
#include "ActorTablero.h"

#include "ActorMusica.h"

#include "GradoEfectividad.h"
#include "SistemaAtaque.h"
#include "EscritorAyuda.h"
#include "ModoJuegoBase.h"

#include "SucesosJuegoComun.h"
#include "EstadoJuegoComun.h"
#include "ModoJuegoComun.h"

#include "SucesosJuegoPares.h"
#include "EstadoJuegoPares.h"
#include "ModoJuegoPares.h"

#include "SucesosJuegoEquipo.h"
#include "EstadoJuegoEquipo.h"
#include "ModoJuegoEquipo.h"

#include "SucesosJuegoLibreDoble.h"
#include "EstadoJuegoLibreDoble.h"
#include "ModoJuegoLibreDoble.h"

#include "ValidacionJuego.h"
#include "JuegoMesaBase.h"
