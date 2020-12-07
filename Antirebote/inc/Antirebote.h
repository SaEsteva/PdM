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

#define ROJO LED2
#define AMARILLO LED1
#define VERDE LED3

#define TIEMPO_ESPERA	2000// ms

typedef enum{
	UP,
	FALLING,
	DOWN,
   RISING
}EstadoBoton_t;

//void InicializarBoton();
//void Antirebote(bool_t *,delay_t *);
//void buttonReleased();
//void buttonPressed();


#endif /* __Antirebote_H__ */
