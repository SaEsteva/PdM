/*============================================================================
 * License: BSD-3-Clause
 * Copyright 2018, Eric Pernia <ericpernia@gmail.com>
 * All rights reserved.
 * Date: 2018/10/04
 *===========================================================================*/

// The maximum number of tasks required at any one time during the execution
// of the program. MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCHEDULER_MAX_TASKS   (10)

#include "sapi.h"      // <= sAPI
#include "seos_pont.h" // <= Simple Embedded Operating Sistem (cooperative)
#include "task1.h"     // <= Task 1
#include "task2.h"     // <= Task 2
//#include "task3.h"     // <= Task 3
#include "../../modular_tasks/inc/Antirebote.h"
#include "../../modular_tasks/inc/Led.h"
#include "../../modular_tasks/inc/semaforo.h"

//bool_t* pValor = NULL;
bool_t ValorTec[3] = {OFF, ON, ON};
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardInit();
   
   //pValor = &ValorTec[0];
   task1_Init();
   task2_Init();


   // FUNCION que inicializa el planificador de tareas
   schedulerInit();

   // Se agrega la tarea tarea1 al planificador
   schedulerAddTask( task1_Update, // funcion de tarea a agregar
                     &ValorTec[0],            // parametro de la tarea
                     0,            // offset de ejecucion en ticks
                     50           // periodicidad de ejecucion en ticks
                   );
   
   schedulerAddTask( task2_Update, &ValorTec[0], 1, 100 );
   //schedulerAddTask( task3_Update, 0, 2, 300 );

   // FUNCION que inicializa la interrupcion que ejecuta el planificador de
   // tareas con tick cada 1ms.
   schedulerStart( 1 );

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
      // Se despachan (ejecutan) las tareas marcadas para su ejecucion.
      // Luego se pone el sistema en bajo consumo hasta que ocurra la
      // proxima interrupcion, en este caso la de Tick.
      // Al ocurrir la interrupcion de Tick se ejecutara el planificador
      // que revisa cuales son las tareas a marcar para su ejecucion.
      schedulerDispatchTasks();
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
