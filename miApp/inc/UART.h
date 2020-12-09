/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

#ifndef _RX_H_
#define _RX_H_

/*==================[inclusions]=============================================*/

#include "sapi.h"   // <= sAPI header

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
#define UART_DW   115200
#define ESTADO1 '1'
#define ESTADO2 '2'
#define ESTADO3 '3'
/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

// Funcion que inicializa la tarea
void enable_UART(bool_t* );

void onRx( void* );

void send_rx(bool_t*);
// Funcion que se ejecuta periodicamente
void UART_Update(void *);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _TASK3_H_ */
