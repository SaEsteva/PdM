/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/


/*==================[inlcusiones]============================================*/

#include "display_info.h"        // <= Biblioteca sAPI

enum{
	BODY_CHAR = 0,
	MOVE_CHAR = 1
};

uint16_t last_state = Error;

// Definir caracteres personalizados: https://omerk.github.io/lcdchargen/
// Simbolo persona
const char body[8] = {
	0b00100,
	0b01010,
	0b00100,
	0b01110,
	0b10101,
	0b00100,
	0b01010,
	0b10001
};

//Simbolo persona corriendo
const char move[8] = {
	0b00100,
	0b01010,
	0b00101,
	0b11111,
	0b10100,
	0b00111,
	0b01101,
	0b10001
};

void displayInit(){


	   i2cInit( I2C0, 100000 );

	   delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)

	   // Inicializar LCD de 16x2 (caracteres x lineas) con cada caracter de 5x8 pixeles
	   lcdInit( 16, 2, 5, 8 );

	   lcdCreateChar( BODY_CHAR, body );
	   lcdCreateChar( MOVE_CHAR, move );
	   lcdCursorSet( LCD_CURSOR_OFF ); // Apaga el cursor
	   lcdClear();                     // Borrar la pantalla
}


void welcome(){
	lcdClear();
	lcdGoToXY( 4, 0 ); // Poner cursor en 0, 0
	lcdSendStringRaw( "Welcome" );

	lcdGoToXY( 1, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 3, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 5, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 7, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 9, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 11, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 13, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 15, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
}

void write_display_error(){
	lcdClear();
	lcdGoToXY( 4, 0 ); // Poner cursor en 0, 0
	lcdSendStringRaw( "ERROR" );

	lcdGoToXY( 1, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 3, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 5, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 7, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 9, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 11, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 13, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 15, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
}
void write_display_Empty(){
	lcdClear();
	lcdGoToXY( 4, 0 ); // Poner cursor en 0, 0
	lcdSendStringRaw( "SIN DATOS" );

	lcdGoToXY( 1, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 3, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 5, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 7, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 9, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 11, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
	lcdGoToXY( 13, 1 ); // Poner cursor en 0, 0
	lcdData(BODY_CHAR);
	lcdGoToXY( 15, 1 ); // Poner cursor en 0, 0
	lcdData(MOVE_CHAR);
}
void write_display(message_display_t data ){
	lcdGoToXY( 0, 0 ); // Poner cursor en 0, 0
	lcdSendStringRaw( data.data_up );

	lcdGoToXY( 0, 1 ); // Poner cursor en 0, 0
	lcdSendStringRaw( data.data_down );
}

void write_display_reading(){
	message_display_t data;

	lcdClear();
	char data1[]="Estado Sensor:";
	char data2[]="Leyendo datos";
	data.data_up = &data1;
	data.data_down = &data2;

	write_display(data);
}

void write_display_processing(){
	message_display_t data;

	lcdClear();
	char data1[]="Estado Sensor:";
	char data2[]="Precesando datos";
	data.data_up = &data1;
	data.data_down = &data2;

	write_display(data);
}

void write_display_process(){
	message_display_t data;

	lcdClear();
	char data1[]="Estado Sensor:";
	char data2[]="Dato procesado";
	data.data_up = &data1;
	data.data_down = &data2;

	write_display(data);
}

void write_display_Sending(){
	message_display_t data;

	lcdClear();
	char data1[]="Estado Sensor:";
	char data2[]="Enviado Dato BLE";
	data.data_up = &data1;
	data.data_down = &data2;

	write_display(data);
}

void UpdateDisplay(uint16_t proces_status){

	switch (proces_status){
		case Reading:
			if (last_state != Reading){
				write_display_reading();
				last_state = Reading;
			}
			break;
		case Processing:
			if (last_state != Processing){
				write_display_processing();
				last_state = Processing;
			}
			break;
		case DataProcessed:
			if (last_state != DataProcessed){
				write_display_process();
				last_state = DataProcessed;
			}
			break;
		case Sending:
			if (last_state != Sending){
				write_display_Sending();
				last_state = Sending;
			}
			break;
		case Empty:
			if (last_state != Empty){
				write_display_Empty();
				last_state = Empty;
			}
			break;
		default:
			write_display_error();
			break;
	}
}

/* funcion de debbug
int main( void )
{

	// ---------- CONFIGURACIONES ------------------------------
	//boardInit();
	boardConfig();

	displayInit();
	message_display_t message;

	char aux0[]="buenas noches";
	char aux1[]="que tal les fue";
	char aux2[]="esto es la fiest";
	char aux3[]="  DAMAS GRATIS";
	char aux4[]=" MANDALE CUMBIA";
	char aux5[]="   VIEJAAA  ";

	while( TRUE ) {
		lcdClear();
		welcome();
		delay(2000);

		lcdClear(); // Borrar la pantalla
		message.data_up = &aux0;
		message.data_down = &aux1;
		write_display(message);
		delay(2000);

		lcdClear(); // Borrar la pantalla
		message.data_up = &aux2;
		message.data_down = &aux3;
		write_display(message);
		delay(2000);

		lcdClear(); // Borrar la pantalla
		message.data_up = &aux4;
		message.data_down = &aux5;
		write_display(message);
		delay(2000);
   }
   return 0;
}*/
