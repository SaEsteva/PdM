/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "Antirebote.h"
#include "sapi.h"


/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/
/*
void myButton1PressedCallback(void* param)
{
   printf("Boton 0 presionado\r\n");
}
void myButton1ReleasedCallback(void* param)
{
   printf("Boton 0 liberado\r\n");
}
void myButton1HoldPressedCallback(void* param)
{
   printf("Boton 0 presionado durante mas de 3 segundos\r\n");
}
*/
void InicializarBoton(){
	   // Temporization
	   //delay_t refreshButton;
	   //delay_t refreshButtonEvents;
	   delayInit( &refreshButton, TIEMPO_ESPERA );
	   delayInit( &refreshButtonEvents, 10 );

	   // Button objects
	   //button_t myButton0;
	   //button_t myButton1;
	   //button_t myButton2;
	   // Button 0 is handled with callbacks
	   buttonInit( &myButton0,                  // Button structure (object)
	               BUTTON0, BUTTON_LOGIC,       // Pin and electrical connection
				   TIEMPO_ESPERA,                          // Button scan time [ms]
	               TRUE,                        // checkPressedEvent
				   FALSE,                        // checkReleasedEvent
				   TRUE,                        // checkHoldPressedEvent
	               2000,                        // holdPressedTime [ms]
	               0,    // pressedCallback
	               0,   // releasedCallback
	               0 // holdPressedCallback
	             );

	   // Rest of buttons handled by pooling

	   // Buttton 1 not check released event
	   buttonInit( &myButton1, BUTTON1, BUTTON_LOGIC,TIEMPO_ESPERA,TRUE,FALSE,TRUE,2000,0,0,0);
	   buttonInit( &myButton2,BUTTON2, BUTTON_LOGIC,TIEMPO_ESPERA,TRUE,FALSE,TRUE,2000,0,0,0);
}

void Antirebote( bool_t * estadoBotenes)
{
	static delay_t DelayTecla;
	static bool_t Boton;

    // Refrehs button FSMs every 50 ms
    if( delayRead(&refreshButton) ) {
       buttonFsmUpdate( &myButton0 );
       buttonFsmUpdate( &myButton1 );
       buttonFsmUpdate( &myButton2 );
    }

    // Poll buttons events every 10 ms
    if( delayRead(&refreshButtonEvents) ) {
       // button 1 will print 5 times beacause difference of temporization not mark evend as handled
       if( (buttonEventGet( &myButton0 ) == BUTTON_PRESSED) ) {
          //printf("Se presiono boton 1\r\n");
          *estadoBotenes = 0;
          *(estadoBotenes+1) = 1;
          *(estadoBotenes+2) = 1;
       }
       // Never execute because not check released event
       if( (buttonEventGet( &myButton0 ) == BUTTON_RELEASED) ) {
          printf("Se libero boton 1\r\n");
          //*estadoBotenes = 0;
       }
       // Rest of buttons will print only 1 time because mark events as handled
       if( (buttonEventGet( &myButton1 ) == BUTTON_PRESSED) ) {
          //printf("Se presiono boton 2\r\n");
          buttonEventHandled( &myButton1 );
          *estadoBotenes = 1;
          *(estadoBotenes+1) = 0;
          *(estadoBotenes+2) = 1;
       }
       // Never execute because not check released event
       if( (buttonEventGet( &myButton1 ) == BUTTON_RELEASED) ) {
          printf("Se libero boton 2\r\n");
          buttonEventHandled( &myButton1 );
          //*(estadoBotenes+1) = 0;
       }
       if( (buttonEventGet( &myButton2 ) == BUTTON_PRESSED) ) {
          printf("Se presiono boton 3\r\n");
          buttonEventHandled( &myButton2 );
          *estadoBotenes = 1;
          *(estadoBotenes+1) = 1;
          *(estadoBotenes+2) = 0;
       }
       // Never execute because not check released event
       if( (buttonEventGet( &myButton2 ) == BUTTON_RELEASED) ) {
          printf("Se libero boton 3\r\n");
          buttonEventHandled( &myButton2 );
          //*(estadoBotenes+2) = 0;
       }
    }
}

