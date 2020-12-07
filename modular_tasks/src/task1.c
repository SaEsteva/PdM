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
void task1_Update( bool_t* taskParam ){   
   	*taskParam = Antirebote( TEC1 );
      *(taskParam+1) = Antirebote( TEC2 );
      *(taskParam+2) = Antirebote( TEC3 );
}

/*==================[end of file]============================================*/
