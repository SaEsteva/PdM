/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "../inc/semaforo.h"


/*=====[Definition macros of private constants]==============================*/
	ModoOperacion_t ModoActual = NORMAL;
	ModoOperacion_t ModoAnterior;
	bool_t NuevoEstado = 0;

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/


void semaforo_normal(delay_t* tiempoDelay,gpioMap_t* ledEncendido,bool_t NuevoEstado){
	if (NuevoEstado){
		delayConfig( tiempoDelay, TIEMPO_EN_ROJO);
		*ledEncendido = ROJO;
	}
	if (delayRead( tiempoDelay ) ){// si se cumple el tiempo de encendido, invierte los leds
			   switch(*ledEncendido){
			   case AMARILLO:
				   apagarLeds();
				   encenderLed(VERDE);
				   *ledEncendido = VERDE;
				   delayConfig( tiempoDelay, TIEMPO_EN_VERDE);
				   break;
			   case ROJO:
				   apagarLeds();
				   encenderLed(AMARILLO);
				   *ledEncendido = AMARILLO;
				   delayConfig( tiempoDelay, TIEMPO_EN_AMARILLO);
				   break;
			   case VERDE:
				   apagarLeds();
				   encenderLed(ROJO);
				   *ledEncendido = ROJO;
				   delayConfig( tiempoDelay, TIEMPO_EN_ROJO);
				   break;
				   }
	}
}
void semaforo_alarma(delay_t* tiempoDelay,gpioMap_t* ledEncendido,bool_t NuevoEstado){
	if (NuevoEstado){
			delayConfig( tiempoDelay, TIEMPO_EN_ALARMA);
			*ledEncendido = ROJO;
	}
	if (delayRead( tiempoDelay ) ){// si se cumple el tiempo de encendido, invierte los leds
		switch(*ledEncendido){
					   case ROJO:
						   apagarLeds();
						   encenderLed(ROJO);
						   encenderLed(AMARILLO);
						   *ledEncendido = AMARILLO;
						   delayConfig( tiempoDelay, TIEMPO_EN_ALARMA);
						   break;
					   case AMARILLO:
						   apagarLeds();
						   *ledEncendido = ROJO;
						   delayConfig( tiempoDelay, TIEMPO_EN_ALARMA);
						   break;
		}
	}
}
void semaforo_desconectado(delay_t* tiempoDelay,gpioMap_t* ledEncendido,bool_t NuevoEstado){
	if (NuevoEstado){
				delayConfig( tiempoDelay, TIEMPO_EN_DESCONECTADO);
				*ledEncendido = ROJO;
		}
	if (delayRead( tiempoDelay ) ){// si se cumple el tiempo de encendido, invierte los leds
		switch(*ledEncendido){
					   case ROJO:
						   apagarLeds();
						   encenderLed(AMARILLO);
						   *ledEncendido = AMARILLO;
						   delayConfig( tiempoDelay, TIEMPO_EN_DESCONECTADO);
						   break;
					   case AMARILLO:
						   apagarLeds();
						   *ledEncendido = ROJO;
						   delayConfig( tiempoDelay, TIEMPO_EN_DESCONECTADO);
						   break;
		}
	}
}
bool_t semaforo( bool_t* Valor )
{
	static delay_t tiempoDelay;
	static gpioMap_t ledEncendido = ROJO;

	if(!*Valor){
		   ModoActual = NORMAL;
	   }else if (!*(Valor+1)){
		   ModoActual = DESCONECTADO;
	   }else if (!*(Valor+2)){
		   ModoActual = ALARMA;
	   }
	   if (ModoActual == ModoAnterior){
		   NuevoEstado = 0;
	   } else {
		   NuevoEstado = 1;
		   ModoAnterior = ModoActual;
	   }

	   switch(ModoActual){
	   case NORMAL:
		   semaforo_normal(&tiempoDelay,&ledEncendido,NuevoEstado);
		   break;
	   case DESCONECTADO:
		   semaforo_desconectado(&tiempoDelay,&ledEncendido,NuevoEstado);
		   break;
	   case ALARMA:
		   semaforo_alarma(&tiempoDelay,&ledEncendido,NuevoEstado);
		   break;
	   }
	   return NuevoEstado;
}
