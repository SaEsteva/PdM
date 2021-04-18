/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/


/*==================[inclusions]=============================================*/

#include "sapi.h"        // <= sAPI header
#include "sensor.h"

sensor_data_t muestra;

void SensorInit(){
	// sapi permite dos configuraciones: ADC_ENABLE,  ADC_DISABLE,
	adcConfig( ADC_ENABLE ); /* ADC */
}

void measurementInit(){
	muestra.nmeasure=0;
	muestra.state=Empty;
	delayConfig( &(muestra.extractdelay), SAMPLETIME );
}

void get_data (sensor_data_t* lectura){
	lectura->data[lectura->nmeasure] = adcRead( SENSOR_ID );
}

void extract_measurement(sensor_data_t* data){

	if (data->nmeasure == 0)
		data->state = Reading;

	if ( delayRead( &(data->extractdelay) ) ){ //consulta si ya paso el tiempo para tomar la siguiente muestra
		get_data (data);
		data->nmeasure++;
	}
	if (data->nmeasure >= NDATA){// actualiza el estado del buffer cuando tiene las N muestras
		data->state = Full;
	}
}

void convert_measurement(sensor_data_t* measurements, current_data_t * current){
	uint32_t i;

	measurements->state = Processing;

	for (i = 0; i < NDATA; i++){
		current->current_value[i] = measurements->data[i] * CURRENTSCALE;
	}
}


void process_measurement(current_data_t * current){
	uint32_t i;
	double aux_avg = 0;
	double aux_max = 0;
	double aux_min = 0;

	aux_min = current->current_value[0];
	for (i = 0; i < NDATA; i++){
		aux_avg += current->current_value[i];
		if (aux_max < current->current_value[i])// busca el máximo
			aux_max = current->current_value[i];
		if (aux_min > current->current_value[i])// busca el minimo
			aux_min = current->current_value[i];
	}
	aux_avg = aux_avg/NDATA;
	current->average = aux_avg;
	current->max_value = aux_max;
	current->min_value = aux_min;

	aux_min = 0;
	for (i = 0; i < NDATA; i++){
		aux_max = current->current_value[i] - aux_avg;
		if (aux_max < 0)
			aux_max = aux_max*(-1);
		aux_min += pow(aux_max,aux_max);
	}
	current->rms_value = sqrt(aux_min/NDATA);
}


char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}

void New_measurement(current_data_t* corriente, uint16_t* flag){

	if (muestra.state == Full){
		convert_measurement(&muestra, corriente);
		*flag = Processing;
	}else if (muestra.state == Processing){
		process_measurement(corriente);
		muestra.state = DataProcessed;
		*flag = DataProcessed;
	}else {
		extract_measurement(&muestra);
		*flag = Reading;
	}
}

/*
// Funcion de debbug
void main(void){

	// ---------- CONFIGURACIONES ------------------------------
	boardInit();
	boardConfig();

	sensor_data_t muestra;
	current_data_t corriente;

	SensorInit(&muestra);

	// Inicializar UART_USB para incluir una opcion de debugger
	uartConfig( UART_USB, 9600 );


	static char uartBuff[10];

	uint16_t i;
	uint16_t flag = 0;

	while(1) {

		if (muestra.state == Full){
			uartWriteString( UART_USB, "\r\n Se finaliza la toma de 20 muestras: \r\n" );
			muestra.state = Processing;
			i=0;
		}else if (muestra.state == Processing){
			convert_measurement(&muestra, &corriente);
			process_measurement(&corriente);
			flag = 1;

		}else {
			extract_measurement(&muestra);
		}

		if (flag){

			uartWriteString( UART_USB, "\r\n Los valores en corriente: \r\n" );
			for (i = 0; i < NDATA; i++){
				itoa( corriente.current_value[i], uartBuff, 10 );
				uartWriteString( UART_USB, uartBuff );
				uartWriteString(UART_USB, ";   ");
				delay(100);
			}
			uartWriteString( UART_USB, "\r\n El promedio da: \r\n" );
			itoa( corriente.average, uartBuff, 10 );
			uartWriteString( UART_USB, uartBuff );
			delay(10);

			uartWriteString( UART_USB, "\r\n El maximo da: \r\n" );
			itoa( corriente.max_value, uartBuff, 10 );
			uartWriteString( UART_USB, uartBuff );
			delay(10);

			uartWriteString( UART_USB, "\r\n El minimo da: \r\n" );
			itoa( corriente.min_value, uartBuff, 10 );
			uartWriteString( UART_USB, uartBuff );
			delay(10);

			uartWriteString( UART_USB, "\r\n El valor rms da: \r\n" );
			itoa( corriente.rms_value, uartBuff, 10 );
			uartWriteString( UART_USB, uartBuff );
			delay(10);

			muestra.state = Empty;
			muestra.nmeasure = 0;
			flag=0;
		}
	}
}
*/

