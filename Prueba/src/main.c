/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2021/04/14
 * Version: 1.1
 *===========================================================================*/


/*==================[inlcusiones]============================================*/

#include "sapi.h"        // <= Biblioteca sAPI

// Definir caracteres personalizados: https://omerk.github.io/lcdchargen/

#define MESSAGE_LCD_LEN		16


typedef struct{
	char *data_up;
	char *data_down;
}message_display_t;
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

enum{
	BODY_CHAR = 0,
	MOVE_CHAR = 1
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

void write_display(message_display_t data ){
	lcdGoToXY( 0, 0 ); // Poner cursor en 0, 0
	lcdSendStringRaw( data.data_up );

	lcdGoToXY( 0, 1 ); // Poner cursor en 0, 0
	lcdSendStringRaw( data.data_down );
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
