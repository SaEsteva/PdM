
#ifndef _TASK1_H_
#define _TASK1_H_

/*==================[inclusions]=============================================*/
#include <stdint.h>
#include <stddef.h>
#include "sapi.h"   // <= sAPI header

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

// Funcion que inicializa la tarea
void Teclas_Init( void );

// Funcion que se ejecuta periodicamente
void Teclas_Update( void* taskParam );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _TASK1_H_ */
