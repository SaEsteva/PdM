/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/


#ifndef __Antirebote_H__
#define __Antirebote_H__

#include <stdint.h>
#include <stddef.h>
#include <sapi.h>

#define TIEMPO_ESPERA	40// ms

typedef enum{
	UP,
	FALLING,
	DOWN,
   RISING
}EstadoBoton_t;

void InicializarBoton();
bool_t BotonLiberado();
bool_t BotonPresionado();
bool_t Antirebote( gpioMap_t );


#endif /* __Antirebote_H__ */
