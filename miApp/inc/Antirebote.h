/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/


#ifndef __Antirebote_H__
#define __Antirebote_H__

#include <stdint.h>
#include <stddef.h>
#include <sapi.h>

#define BUTTON_LOGIC BUTTON_ONE_IS_UP
#define TIEMPO_ESPERA	40// ms
#define BUTTON0 TEC1
#define BUTTON1 TEC2
#define BUTTON2 TEC3

// Temporization
delay_t refreshButton;
delay_t refreshButtonEvents;
// Button objects
button_t myButton0;
button_t myButton1;
button_t myButton2;

void InicializarBoton();
void Antirebote( bool_t* );
//void myButton1PressedCallback(void* );
//void myButton1ReleasedCallback(void* );
//void myButton1HoldPressedCallback(void* );


#endif /* __Antirebote_H__ */
