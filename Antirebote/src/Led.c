/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "../../Antirebote/inc/Led.h"
#include "sapi.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
void  encenderLed(gpioMap_t led)
{
	gpioWrite( led, ON);
}
void apagarLeds()
{
	gpioWrite( LED1, OFF);
	gpioWrite( LED2, OFF);
	gpioWrite( LED3, OFF);
}
