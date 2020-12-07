/*=============================================================================
 * Copyright (c) 2020, Santiago Esteva <sesteva@fi.uba.ar>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/10/28
 * Version: 1.1
 *===========================================================================*/


#ifndef __semaforo_H__
#define __semaforo_H__


#define ROJO LED2
#define AMARILLO LED1
#define VERDE LED3

#define TIEMPO_EN_ROJO	3000// ms
#define TIEMPO_EN_AMARILLO	500// ms
#define TIEMPO_EN_VERDE	1000// ms
#define TIEMPO_EN_ALARMA	1000// ms
#define TIEMPO_EN_DESCONECTADO	500 // ms

typedef enum{
	NORMAL,
	DESCONECTADO,
	ALARMA
}ModoOperacion_t;

void semaforo(bool_t *);
void semaforo_normal(delay_t* ,gpioMap_t* ,bool_t );
void semaforo_alarma(delay_t* ,gpioMap_t* ,bool_t );
void semaforo_desconectado(delay_t* ,gpioMap_t* ,bool_t );

#endif /* __semaphore_H__ */
