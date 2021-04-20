/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/


/*==================[inlcusiones]============================================*/

#include "../inc/BLE_protocol.h"
#include <string.h>

/*==================[definiciones y macros]==================================*/
buffer_t BLE_buffer;

/*==================[funciones]======================================*/
uint16_t Update_BLE_status(){
	return BLE_buffer.state;
}

void clear_buffer(){
	BLE_buffer.bleindex = 0;
	BLE_buffer.state = BEmpty;
}

// funcion de recepcion de dato
void data_ble_receive(){

	/* se lee el caracter recibido */
	char data = uartRxRead( UART_BLE );

    if( FRAME_MAX_SIZE-1==BLE_buffer.bleindex ){
    	BLE_buffer.bleindex = 0; // reinicio el paquete
    }

    switch ( data ){
    	case startByte:
    		BLE_buffer.bleindex = 0;
    		BLE_buffer.buffer[BLE_buffer.bleindex] = data;
    		BLE_buffer.bleindex++;
    		BLE_buffer.state = Receiving;
    		break;
    	case stopByte:
    		if (BLE_buffer.state == Receiving){
    			BLE_buffer.buffer[BLE_buffer.bleindex] = data;
    			BLE_buffer.bleindex++;
    			BLE_buffer.state = Newdata;
    			/* Deshabilito todas las interrupciones de UART_USB */
                uartCallbackClr( UART_BLE, UART_RECEIVE );
    		}
    		break;
    	default:
    		if (BLE_buffer.state == Receiving){
    			BLE_buffer.buffer[BLE_buffer.bleindex] = data;
    			BLE_buffer.bleindex++;
    		}
    		break;
    }
}

void BLEInit( ){
	/* Inicializar UART_232 para conectar al modulo bluetooth hc_05 */
	uartConfig( UART_BLE, UART_BR );

    /* Seteo un callback al evento de recepcion y habilito su interrupcion */
    uartCallbackSet( UART_BLE, UART_RECEIVE, data_ble_receive, NULL );

    /* Habilito las interrupciones de UART_BLE */
    uartInterrupt( UART_BLE, TRUE );

    /* Inicializa el indice del buffer */
    clear_buffer();
}

void restart_BLE()
{
    /* se inicia un paquete nuevo */
	clear_buffer();

    /* limpio interrupciones que hayan ocurrido */
    uartClearPendingInterrupt( UART_BLE );

    /* Habilito las interrupciones de UART_BLE */
    uartCallbackSet( UART_BLE, UART_RECEIVE, data_ble_receive, NULL );
}

void  ref_frame( char** data, uint16_t* size )
{
    *data = BLE_buffer.buffer;
    *size = BLE_buffer.bleindex;
}
uint16_t message_interpreter(){

    switch ( BLE_buffer.buffer[1] ){
    	case Average:
    		return Average;
    		break;
    	case Maxim:
    		return Maxim;
    		break;
    	case Minim:
    		return Minim;
			break;
    	case RMS:
    		return RMS;
			break;
    	default:
    		return SError;
    		break;
    }
}

void Send_Data_BLE(char *data){
	uartWriteString( UART_BLE, startByte );
	uartWriteString( UART_BLE, data );
	uartWriteString( UART_BLE, stopByte );
}

/*==================[funcion de prueba ]======================================*/
/*
void main( void )
{
   // ---------- CONFIGURACIONES ------------------------------
	boardInit();
	boardConfig();

	UartInit();
	// Inicializar UART_USB para incluir una opcion de debugger
	uartConfig( UART_USB, UART_BR );

	char *data;
	uint16_t size;

	ref_frame( &data, &size );

    uartWriteString( UART_PC,"Inicia la tarea de prueba\r\n");

	// ---------- REPETIR POR SIEMPRE --------------------------
	while( TRUE ) {

	  // Si leo un dato de una UART lo envio a al otra (bridge)
	  if( BLE_buffer.state == Newdata ) {
		  uartWriteString( UART_PC, data );
		  uartWriteString( UART_BLE, data );
		  restart_BLE();
	  }
	}
}
*/
