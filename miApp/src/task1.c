/*============================================================================
 * License: BSD-3-Clause
 * Copyright 2018, Eric Pernia <ericpernia@gmail.com>
 * All rights reserved.
 * Date: 2018/10/04
 *===========================================================================*/

/*==================[inclusions]=============================================*/

#include "task1.h"  // <= own header
//#include "../../modular_tasks/inc/tarea.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

// Funcion que inicializa la tarea
void task1_Init( void ){
   boardInit();
   InicializarBoton();
}

// Funcion que se ejecuta periodicamente
void task1_Update( void* taskParam ){
	//printf("Se actualiza tarea 1");
	Antirebote( taskParam );
   	//printf(taskParam);
}

/*==================[end of file]============================================*/
