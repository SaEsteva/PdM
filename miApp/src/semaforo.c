/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "semaforo.h"


/*=====[Definition macros of private constants]==============================*/
static ModoOperacion_t ModoActual = NORMAL;
static ModoOperacion_t ModoAnterior;
static bool_t NuevoEstado = 0;

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
void MEF_selec(bool_t selector, gpioMap_t led1,gpioMap_t led2){

	if (!selector){
		encenderLed(led1);
	}else {
		encenderLed(led2);
	}
}

void semaforo_normal(delay_t* tiempoDelay,gpioMap_t* ledEncendido,bool_t NuevoEstado,bool_t* nMEF){
	if (NuevoEstado){
		delayConfig( tiempoDelay, TIEMPO_EN_ROJO);
		*ledEncendido = ROJO;
	}
	if (delayRead( tiempoDelay ) ){// si se cumple el tiempo de encendido, invierte los leds
		switch(*ledEncendido){
			case AMARILLO:
			   apagarLeds();
			   MEF_selec(*(nMEF+3),VERDE,GRGB);
			   *ledEncendido = VERDE;
			   delayConfig( tiempoDelay, TIEMPO_EN_VERDE);
			   break;
			case ROJO:
			   apagarLeds();
			   MEF_selec(*(nMEF+3),AMARILLO,BRGB);
			   *ledEncendido = AMARILLO;
			   delayConfig( tiempoDelay, TIEMPO_EN_AMARILLO);
			   break;
			case VERDE:
			   apagarLeds();
			   MEF_selec(*(nMEF+3),ROJO,RRGB);
			   *ledEncendido = ROJO;
			   delayConfig( tiempoDelay, TIEMPO_EN_ROJO);
			   break;
			default:
				apagarLeds();
				MEF_selec(*(nMEF+3),AMARILLO,BRGB);
				MEF_selec(*(nMEF+3),VERDE,GRGB);
				MEF_selec(*(nMEF+3),ROJO,RRGB);
				delayConfig( tiempoDelay, TIEMPO_DEFAULT);
				break;
			   }
	}
}
void semaforo_alarma(delay_t* tiempoDelay,gpioMap_t* ledEncendido,bool_t NuevoEstado,bool_t* nMEF){
	if (NuevoEstado){
			delayConfig( tiempoDelay, TIEMPO_EN_ALARMA);
			*ledEncendido = ROJO;
	}
	if (delayRead( tiempoDelay ) ){// si se cumple el tiempo de encendido, invierte los leds
		switch(*ledEncendido){
			case ROJO:
			   apagarLeds();
			   MEF_selec(*(nMEF+3),ROJO,RRGB);
			   MEF_selec(*(nMEF+3),AMARILLO,BRGB);
			   *ledEncendido = AMARILLO;
			   delayConfig( tiempoDelay, TIEMPO_EN_ALARMA);
			   break;
			case AMARILLO:
			   apagarLeds();
			   *ledEncendido = ROJO;
			   delayConfig( tiempoDelay, TIEMPO_EN_ALARMA);
			   break;
			default:
				apagarLeds();
				MEF_selec(*(nMEF+3),AMARILLO,BRGB);
				MEF_selec(*(nMEF+3),VERDE,GRGB);
				MEF_selec(*(nMEF+3),ROJO,RRGB);
				delayConfig( tiempoDelay, TIEMPO_DEFAULT);
				break;
		}
	}
}
void semaforo_desconectado(delay_t* tiempoDelay,gpioMap_t* ledEncendido,bool_t NuevoEstado,bool_t* nMEF){
	if (NuevoEstado){
				delayConfig( tiempoDelay, TIEMPO_EN_DESCONECTADO);
				*ledEncendido = ROJO;
		}
	if (delayRead( tiempoDelay ) ){// si se cumple el tiempo de encendido, invierte los leds
		switch(*ledEncendido){
			case ROJO:
			   apagarLeds();
			   MEF_selec(*(nMEF+3),AMARILLO,BRGB);
			   *ledEncendido = AMARILLO;
			   delayConfig( tiempoDelay, TIEMPO_EN_DESCONECTADO);
			   break;
			case AMARILLO:
			   apagarLeds();
			   *ledEncendido = ROJO;
			   delayConfig( tiempoDelay, TIEMPO_EN_DESCONECTADO);
			   break;
			default:
				apagarLeds();
				MEF_selec(*(nMEF+3),AMARILLO,BRGB);
				MEF_selec(*(nMEF+3),VERDE,GRGB);
				MEF_selec(*(nMEF+3),ROJO,RRGB);
				delayConfig( tiempoDelay, TIEMPO_DEFAULT);
				break;
		}
	}
}
void semaforo( bool_t* Valor )
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
	   //printf("Ingresa al modo NORMAL");
	   semaforo_normal(&tiempoDelay,&ledEncendido,NuevoEstado,Valor);
	   break;
	case DESCONECTADO:
	   //printf("Ingresa al modo DESCONECTADO");
	   semaforo_desconectado(&tiempoDelay,&ledEncendido,NuevoEstado,Valor);
	   break;
	case ALARMA:
	   //printf("Ingresa al modo ALARMA");
	   semaforo_alarma(&tiempoDelay,&ledEncendido,NuevoEstado,Valor);
	   break;
	default:
	   printf("Error en los estados de la maquina de estados.\r\n");
	   break;
	}
}
