/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Led2.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/
tick_t tiempoInicial   = 100;
tick_t tiempoTEC2   = 150;
tick_t tiempoTEC3   = 750;
bool_t Secuencia = 0;
bool_t ValorTec1 = ON;
bool_t ValorTec2 = OFF;
bool_t ValorTec3 = ON;
bool_t ValorTec4 = OFF;
/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
void  encenderLed(gpioMap_t led)
{
	gpioWrite( led, ON);
}
void apagarLeds()
{
	gpioWrite( LEDB, OFF);
	gpioWrite( LED1, OFF);
	gpioWrite( LED2, OFF);
	gpioWrite( LED3, OFF);
}
void leerTeclas()
{
	// leo los cuatro botones
	ValorTec1 = gpioRead( TEC1 );
	ValorTec2 = gpioRead( TEC2 );
	ValorTec3 = gpioRead( TEC3 );
	ValorTec4 = gpioRead( TEC4 );
}

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   int8_t ledEncendido    = 0;
   // Crear variable del tipo tick_t para contar tiempo
   delay_t tiempoDelay;

   //Definir el delay no bloqueante
   delayConfig( &tiempoDelay, tiempoInicial );

   // ----- Repeat for ever -------------------------
   while( TRUE ) {

	   leerTeclas();


	   //CAMBIAR ESTO POR INTERRUPCION

	   if (!ValorTec3){
		   delayWrite( &tiempoDelay, tiempoTEC3 );
	   } else if (!ValorTec2){
		   delayWrite( &tiempoDelay, tiempoTEC2 );
	   }

	   if (!ValorTec4){
	   		   Secuencia = 0;
	   	   } else if (!ValorTec1){
	   		   Secuencia = 1;
	   	   }

	   if (delayRead( &tiempoDelay ) ){// si se cumple el tiempo de encendido, invierte los leds
		   if (Secuencia == 1){//la secuencia debe ser invertida
			   switch(ledEncendido){
			   case 0:
				   apagarLeds();
				   encenderLed(LED3);
				   ledEncendido = 3;
				   break;
			   case 1:
				   apagarLeds();
				   encenderLed(LEDB);
				   ledEncendido = 0;
			   			   break;
			   case 2:
				   apagarLeds();
				   encenderLed(LED1);
				   ledEncendido = 1;
				   break;
			   case 3:
				   apagarLeds();
				   encenderLed(LED2);
				   ledEncendido = 2;
				   break;
			   }
		   }else {//la secuencia debe ser la original
			   switch(ledEncendido){
			   		   case 0:
						   apagarLeds();
						   encenderLed(LED1);
						   ledEncendido = 1;
			   			   break;
			   		   case 1:
						   apagarLeds();
						   encenderLed(LED2);
						   ledEncendido = 2;
			   		   			   break;
			   		   case 2:
						   apagarLeds();
						   encenderLed(LED3);
						   ledEncendido = 3;
			   			   break;
			   		   case 3:
						   apagarLeds();
						   encenderLed(LEDB);
						   ledEncendido = 0;
			   			   break;
			   		   }
		   }
	   }
   }
   return 0;
}
