/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/24
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Led.h"
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
	  // leo los cuatro botones
	   ValorTec1 = gpioRead( TEC1 );
	   ValorTec2 = gpioRead( TEC2 );
	   ValorTec3 = gpioRead( TEC3 );
	   ValorTec4 = gpioRead( TEC4 );

	   //CAMBIAR ESTO POR INTERRUPCION

	   if (!gpioRead( TEC3 )){
		   delayWrite( &tiempoDelay, tiempoTEC3 );
	   } else if (!gpioRead( TEC2 )){
		   delayWrite( &tiempoDelay, tiempoTEC2 );
	   }

	   if (!gpioRead( TEC4 )){
	   		   Secuencia = 0;
	   	   } else if (!gpioRead( TEC1 )){
	   		   Secuencia = 1;
	   	   }

	   if (delayRead( &tiempoDelay ) ){// si se cumple el tiempo de encendido, invierte los leds
		   if (Secuencia == 1){//la secuencia debe ser invertida
			   switch(ledEncendido){
			   case 0:
				   gpioWrite( LEDB, OFF);
				   gpioWrite( LED1, OFF);
				   gpioWrite( LED2, OFF);
				   gpioWrite( LED3, ON);
				   ledEncendido = 3;
				   break;
			   case 1:
				   gpioWrite( LEDB, ON);
				   gpioWrite( LED1, OFF);
				   gpioWrite( LED2, OFF);
				   gpioWrite( LED3, OFF);
				   ledEncendido = 0;
			   			   break;
			   case 2:
				   gpioWrite( LEDB, OFF);
				   gpioWrite( LED1, ON);
				   gpioWrite( LED2, OFF);
				   gpioWrite( LED3, OFF);
				   ledEncendido = 1;
				   break;
			   case 3:
				   gpioWrite( LEDB, OFF);
				   gpioWrite( LED1, OFF);
				   gpioWrite( LED2, ON);
				   gpioWrite( LED3, OFF);
				   ledEncendido = 2;
				   break;
			   }
		   }else {//la secuencia debe ser la original
			   switch(ledEncendido){
			   		   case 0:
			   			   gpioWrite( LEDB, OFF);
			   			   gpioWrite( LED1, ON);
			   			   gpioWrite( LED2, OFF);
			   			   gpioWrite( LED3, OFF);
						   ledEncendido = 1;
			   			   break;
			   		   case 1:
			   			   gpioWrite( LEDB, OFF);
			   			   gpioWrite( LED1, OFF);
			   			   gpioWrite( LED2, ON);
			   			   gpioWrite( LED3, OFF);
						   ledEncendido = 2;
			   		   			   break;
			   		   case 2:
			   			   gpioWrite( LEDB, OFF);
			   			   gpioWrite( LED1, OFF);
			   			   gpioWrite( LED2, OFF);
			   			   gpioWrite( LED3, ON);
						   ledEncendido = 3;
			   			   break;
			   		   case 3:
			   			   gpioWrite( LEDB, ON);
			   			   gpioWrite( LED1, OFF);
			   			   gpioWrite( LED2, OFF);
			   			   gpioWrite( LED3, OFF);
						   ledEncendido = 0;
			   			   break;
			   		   }
		   }
	   }
   }
   return 0;
}
