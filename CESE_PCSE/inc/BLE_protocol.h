/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/

#ifndef _BLE_H_
#define _BLE_H_

/*==================[inclusions]=============================================*/

#include "sapi.h"   // <= sAPI header

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/
#define UART_BLE		UART_232
#define UART_BR			9600
#define FRAME_MAX_SIZE  200
#define startByte		60 //ASCII de <
#define stopByte		62 //ASCII de >

enum buffer_state{BEmpty, Receiving, Newdata};

enum message_accion{Average = 65 ,Maxim = 77 ,Minim = 78 ,RMS = 82 ,SError = 0 };//Average = A ,Maxim = M ,Minim = N ,RMS = R

/*==================[typedef]================================================*/
typedef struct{
	char 		buffer[FRAME_MAX_SIZE];
	uint32_t 	bleindex;
	uint32_t 		state;
}buffer_t;
/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
uint16_t Update_BLE_status();
void clear_buffer();
void data_ble_receive();
void BLEInit( );
void restart_BLE();
void  ref_frame( char** , uint16_t*  );
uint16_t message_interpreter();
void Send_Data_BLE(char *);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _BLE_H_ */
