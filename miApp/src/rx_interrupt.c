#include "RX.h"  // <= own header

bool_t *parametro = NULL;
bool_t *estado_actual = NULL;

void onRx( void *noUsado )
{
	//LECTURA DEL ESTADO RECIBIDO
	char maquina = uartRxRead( UART_USB );

	*parametro = 1;
	*(parametro+1) = 1;
	*(parametro+2) = 1;

	//define el estado dependiendo de lo que recibe por UART
	if(maquina == '1'){
		printf( "La MEF se encuentra en el estado NORMAL\r\n");
		*parametro = 0;
	}else if (maquina == '2'){
		printf( "La MEF se encuentra en el estado DESCONECTADO\r\n");
		*(parametro+1) = 0;
	}else if (maquina == '3'){
		printf( "La MEF se encuentra en el estado ALARMA\r\n");
		*(parametro+2) = 0;
	}

	//DEBUGG
	//printf( "Recibimos <<%c>> por UART\r\n", maquina );
	//printf( "PARAMETRO <<%o>> <<%o>> <<%o>> UART\r\n", *parametro,*(parametro+1),*(parametro+2) );
}

void enable_rx(bool_t * estado )
{
   parametro = estado;
	/* Inicializar la UART_USB junto con las interrupciones de Tx y Rx */
   uartConfig(UART_USB, 115200);     
   // Seteo un callback al evento de recepcion y habilito su interrupcion
   uartCallbackSet(UART_USB, UART_RECEIVE, onRx, NULL);
   // Habilito todas las interrupciones de UART_USB
   uartInterrupt(UART_USB, true);
}

void RX_Update(void *estado)
{
	estado_actual = estado;

	//DEBUGG
	//printf( "ESTADO normal=%o  ESTADO desconectado=%o  ESTADO alarma=%o\r\n",*estado_actual,*(estado_actual+1),*(estado_actual+2));


	//Define el mensaje dependiendo el estado
	if(!*estado_actual){
		printf( "La MEF se encuentra en el estado NORMAL\r\n");
	}else if (!*(estado_actual+1)){
		printf( "La MEF se encuentra en el estado DESCONECTADO\r\n");
	}else if (!*(estado_actual+2)){
		printf( "La MEF se encuentra en el estado ALARMA\r\n");
	}

	if (!*(parametro+3)){
		printf( "La MEF seleccionada es la LED\r\n");
	}else{
		printf( "La MEF seleccionada es la RGB\r\n");
	}
}
