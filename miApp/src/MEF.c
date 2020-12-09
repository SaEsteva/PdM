/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

/*==================[inclusions]=============================================*/

#include "MEF.h"  // <= own header

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

// Funcion que inicializa la tarea
void MEF_Init( void ){
	apagarLeds();
}

// Funcion que se ejecuta periodicamente
void MEF_Update( void* taskParam ){
   	semaforo(taskParam);
}

/*==================[end of file]============================================*/
