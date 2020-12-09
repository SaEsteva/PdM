#include "RX.h"  // <= own header

static bool_t *parametro = NULL;
static bool_t *estado_actual = NULL;

void onRx( void *noUsado )
{
	//LECTURA DEL ESTADO RECIBIDO
	char maquina = uartRxRead( UART_USB );

	// Se anulan todos los estados
	*parametro = 1;
	*(parametro+1) = 1;
	*(parametro+2) = 1;

	//define el estado dependiendo de lo que recibe por UART
	if(ESTADO1 == maquina){
		//printf( "Se recibe parametro correcto, estado de MEF seleccionado: NORMAL\r\n");
		uartWriteString( UART_USB,"Se recibe parametro correcto, estado de MEF seleccionado: NORMAL\r\n");
		*parametro = 0;
	}else if (ESTADO2 == maquina){
		//printf( "Se recibe parametro correcto, estado de MEF seleccionado: DESCONECTADO\r\n");
		uartWriteString( UART_USB, "Se recibe parametro correcto, estado de MEF seleccionado: DESCONECTADO\r\n");
		*(parametro+1) = 0;
	}else if (ESTADO3 == maquina){
		//printf( "Se recibe parametro correcto, estado de MEF seleccionado: ALARMA\r\n");
		uartWriteString( UART_USB,"Se recibe parametro correcto, estado de MEF seleccionado: ALARMA\r\n");
		*(parametro+2) = 0;
	}else {
		// se informa el dato erroneo por uart
		//printf( "Dato enviado incorrecto, los estados posibles son:\r\n");
		//printf( "1 -> NORMAL   2 -> DESCONECTADO   3 -> ALARMA  \r\n");
		uartWriteString( UART_USB,"Dato enviado incorrecto, los estados posibles son:\r\n");
		uartWriteString( UART_USB,"1 -> NORMAL   2 -> DESCONECTADO   3 -> ALARMA  \r\n");
	}

	//DEBUGG
	//printf( "Recibimos <<%c>> por UART\r\n", maquina );
	//printf( "PARAMETRO <<%o>> <<%o>> <<%o>> UART\r\n", *parametro,*(parametro+1),*(parametro+2) );
}

void enable_rx(bool_t * estado )
{
   parametro = estado;
	/* Inicializar la UART_USB junto con las interrupciones de Tx y Rx */
   uartConfig(UART_USB, UART_DW);
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
		//printf( "La MEF se encuentra en el estado NORMAL\r\n");
		uartWriteString( UART_USB,"La MEF se encuentra en el estado NORMAL\r\n");
	}else if (!*(estado_actual+1)){
		//printf( "La MEF se encuentra en el estado DESCONECTADO\r\n");
		uartWriteString( UART_USB,"La MEF se encuentra en el estado DESCONECTADO\r\n");
	}else if (!*(estado_actual+2)){
		//printf( "La MEF se encuentra en el estado ALARMA\r\n");
		uartWriteString( UART_USB,"La MEF se encuentra en el estado ALARMA\r\n");
	}else{
		//printf( "Estado erroneo, enviar un nuevo estado con la codificacion correcta\r\n");
		uartWriteString( UART_USB,"Estado erroneo, enviar un nuevo estado con la codificacion correcta\r\n");
	}

	if (!*(parametro+3)){
		//printf( "La MEF seleccionada es la LED\r\n");
		uartWriteString( UART_USB,"La MEF seleccionada es la LED\r\n");
	}else{
		//printf( "La MEF seleccionada es la RGB\r\n");
		uartWriteString( UART_USB,"La MEF seleccionada es la RGB\r\n");
	}
}