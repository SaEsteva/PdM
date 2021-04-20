/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/*==================[inclusions]=============================================*/

#include "sapi.h"   // <= sAPI header
#include "sensor.h"
/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
#define MESSAGE_LCD_LEN		16

/*==================[typedef]================================================*/
typedef struct{
	char *data_up;
	char *data_down;
}message_display_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void displayInit();
void welcome();
void write_display_error();
void write_display(message_display_t  );
void write_display_reading();
void write_display_processing();
void write_display_process();
void write_display_Sending();
void write_display_Empty();
void UpdateDisplay(uint16_t );


/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _DISPLAY_H_ */
