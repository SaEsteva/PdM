/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "../../Antirebote/inc/Led.h"
#include "../../Antirebote/inc/Antirebote.h"
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
void BotonLiberado(){
   apagarLeds();
   encenderLed(VERDE);
}

void BotonPresionado(){
   apagarLeds();
   encenderLed(ROJO);
}

void Antirebote(gpioMap_t tecla)
{
	static delay_t tiempoDelay;

	switch(BotonActual){
	case UP:
		if (!gpioRead( tecla )){
			BotonActual = FALLING;
			delayConfig( &tiempoDelay, TIEMPO_ESPERA);
		}
		break;
	case FALLING:
		if (delayRead( &tiempoDelay )){
			if (!gpioRead( tecla )){
				BotonActual = DOWN;
				BotonPresionado();
			}
			else {
				BotonActual = UP;
			}
			delayConfig( &tiempoDelay, TIEMPO_ESPERA);
		}
		break;
	case DOWN:
		if (gpioRead( tecla )){
			BotonActual = RISING;
			delayConfig( &tiempoDelay, TIEMPO_ESPERA);
		}
		break;
	case RISING:
		if (delayRead( &tiempoDelay )){
			if (gpioRead( tecla )){
				BotonActual = UP;
				BotonLiberado();
			}
			else {
				BotonActual = DOWN;
			}
			delayConfig( &tiempoDelay, TIEMPO_ESPERA);
			}
		break;
	default:
		InicializarBoton();
		break;
	}
}

int main( void )
{
	// ----- Setup -----------------------------------
	boardInit();

	InicializarBoton();
	// ----- Repeat for ever -------------------------
	while( TRUE ) {
		// ----- Setup -----------------------------------
		Antirebote(TEC1);
	}
	return 0;
}
