
/*==================[inclusions]=============================================*/

#include "Teclas.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

// Funcion que inicializa la tarea
void Teclas_Init( void ){
   InicializarBoton();
}

// Funcion que se ejecuta periodicamente
void Teclas_Update( void* taskParam ){
	Antirebote( taskParam );
}

/*==================[end of file]============================================*/
