/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/24
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "../../semaforo/inc/main.h"
#include "../../semaforo/inc/Antirebote.h"
#include "../../semaforo/inc/Led.h"
#include "../../semaforo/inc/semaforo.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/


/*=====[Definitions of public global variables]==============================*/
bool_t ValorTec[3] = {ON, ON, OFF};
bool_t* pValor = NULL;

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
void leerTeclas(bool_t* Valor)
{
	// leo los cuatro botones
	*Valor = Antirebote( TEC1 );
	*(Valor+1) = Antirebote( TEC2 );
	*(Valor+2) = Antirebote( TEC3 );
}
int main( void )
{
	// ----- Setup -----------------------------------
	boardInit();

	bool_t estado = 0;
	pValor = &ValorTec[0];
	InicializarBoton();
   // ----- Repeat for ever -------------------------
   while( TRUE ) {
	   // ----- Setup -----------------------------------
		leerTeclas(pValor);
		estado = semaforo(pValor);

   }
   return 0;
}
