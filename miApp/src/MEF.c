
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
