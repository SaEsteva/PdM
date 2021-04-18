/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/

// The maximum number of tasks required at any one time during the execution
// of the program. MUST BE ADJUSTED FOR EACH NEW PROJECT
#define MEASSURETIME	10000
#define DELAYINIT		2000


#define UART_PC 		UART_USB

#include "display_info.h"
#include "BLE_protocol.h"
#include "sensor.h"

typedef struct{
	delay_t measure_timer;
	uint16_t action;
	uint16_t Procees_status;
	uint16_t acquisitionflag;
	char uartBuff[10];
	bool_t ChangeStatus;
}PSCE_t;

enum PSCE_state{ NoMeassure ,GetNewMeassure , NewMeassureProccessed};


int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardInit();
   boardConfig();
   
   BLEInit();
   displayInit();

   SensorInit();

   PSCE_t Process_Struct;

   delayConfig( &(Process_Struct.measure_timer), MEASSURETIME );

   Process_Struct.Procees_status = NoMeassure;

   current_data_t current_data;

   bool_t FirstMeassureflag ;

   welcome();
   delay(DELAYINIT);

   Process_Struct.acquisitionflag = Empty;

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
	   // Consulta si llega un mensaje válido por BLE para responder
	   if (Update_BLE_status() == Newdata){
		   Process_Struct.action = message_interpreter();
		   Process_Struct.acquisitionflag = Sending;
		   Process_Struct.ChangeStatus = 1;
		   if (Process_Struct.Procees_status == NoMeassure){
			   Send_Data_BLE("E: No hay medicion");
		   }else {
			   switch (Process_Struct.action){
			   	   case Average:
					   itoa( current_data.average, Process_Struct.uartBuff, 10 );
					   Send_Data_BLE(Process_Struct.uartBuff);
					   break;
				   case Maxim:
					   itoa( current_data.max_value, Process_Struct.uartBuff, 10 );
					   Send_Data_BLE(Process_Struct.uartBuff);
					   break;
				   case Minim:
					   itoa( current_data.min_value, Process_Struct.uartBuff, 10 );
					   Send_Data_BLE(Process_Struct.uartBuff);
					   break;
				   case RMS:
					   itoa( current_data.rms_value, Process_Struct.uartBuff, 10 );
					   Send_Data_BLE(Process_Struct.uartBuff);
					   break;
				   default:
					   Send_Data_BLE("E: ID incorrecto");
					   break;
			   }
		   }
		   restart_BLE();
	   }

	   // Delay no bloqueante de 2 segundos para indicar que se debe realizar una nueva medicion
	   if ( delayRead(&(Process_Struct.measure_timer)) ){
		   Process_Struct.Procees_status = GetNewMeassure;
		   measurementInit();
		   Process_Struct.ChangeStatus = 1;
	   }

	   // Adquisicion de una nueva medicion
	   if (Process_Struct.Procees_status == GetNewMeassure){
		   New_measurement(&current_data,&Process_Struct.acquisitionflag);
		   Process_Struct.ChangeStatus = 1;
	   }

	   // Actualizacion de estado al finalizar el procesamiento de la nueva medicion
	   if (Process_Struct.acquisitionflag == DataProcessed){
		   Process_Struct.Procees_status = NewMeassureProccessed;
		   Process_Struct.ChangeStatus = 1;
	   }

	   // Actualizacion de display si hubo cambio
	   if (Process_Struct.ChangeStatus){
		   Process_Struct.ChangeStatus = 0;
		   UpdateDisplay(Process_Struct.acquisitionflag);
	   }

   }
   return 0;
}
