/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "../../semaforo/inc/Antirebote.h"
#include "sapi.h"


/*=====[Definition macros of private constants]==============================*/
	EstadoBoton_t BotonActual;
/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

void InicializarBoton(){
   BotonActual = UP;
}
bool_t BotonLiberado(){
   return 0;
}

bool_t BotonPresionado(){
   return 1;
}

bool_t Antirebote( gpioMap_t tecla)
{
	static delay_t DelayTecla;
	static bool_t Boton;

	switch(BotonActual){
	case UP:
		if (!gpioRead( tecla )){
			BotonActual = FALLING;
			delayConfig( &DelayTecla, TIEMPO_ESPERA);
		}
		break;
	case FALLING:
		if (delayRead( &DelayTecla )){
			if (!gpioRead( tecla )){
				BotonActual = DOWN;
				Boton = BotonPresionado();
			}
			else {
				BotonActual = UP;
			}
			delayConfig( &DelayTecla, TIEMPO_ESPERA);
		}
		break;
	case DOWN:
		if (gpioRead( tecla )){
			BotonActual = RISING;
			delayConfig( &DelayTecla, TIEMPO_ESPERA);
		}
		break;
	case RISING:
		if (delayRead( &DelayTecla )){
			if (gpioRead( tecla )){
				BotonActual = UP;
				Boton = BotonLiberado();
			}
			else {
				BotonActual = DOWN;
			}
			delayConfig( &DelayTecla, TIEMPO_ESPERA);
			}
		break;
	default:
		InicializarBoton();
		break;
	}
	return Boton;
}

