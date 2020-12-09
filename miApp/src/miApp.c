
// The maximum number of tasks required at any one time during the execution
// of the program. MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCHEDULER_MAX_TASKS   (10)
#define TAREA_MEF_TICK   100
#define TAREA_TEC_TICK   50
#define TAREA_RX_TICK   5000


#include "sapi.h"      // <= sAPI
#include "seos_pont.h" // <= Simple Embedded Operating Sistem (cooperative)
#include "Teclas.h"     // <= Task 1
#include "MEF.h"     // <= Task 2
#include "RX.h"     // <= rx interrupt
#include "Antirebote.h" // <= boton antirebote
#include "Led.h" // <= led de EDU-CIA
#include "semaforo.h" // <= MEF de leds

//Estados de la MEF y selecion de MEF (OFF leds normales, ON leds RGB)
bool_t ValorUART[5] = {OFF, ON, ON, OFF};


int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardInit();
   boardConfig();
   
   Teclas_Init();
   MEF_Init();
   enable_rx(&ValorUART[0]);


   // FUNCION que inicializa el planificador de tareas
   schedulerInit();

   // Se agrega la tarea tarea1 al planificador
   schedulerAddTask( Teclas_Update, // funcion de tarea a agregar
                     &ValorUART[0],            // parametro de la tarea
                     0,            // offset de ejecucion en ticks
					 TAREA_TEC_TICK           // periodicidad de ejecucion en ticks
                   );
   
   schedulerAddTask( MEF_Update, &ValorUART[0], 1, TAREA_MEF_TICK );

   schedulerAddTask( RX_Update, &ValorUART[0], 2, TAREA_RX_TICK );

   // FUNCION que inicializa la interrupcion que ejecuta el planificador de
   // tareas con tick cada 1ms.
   schedulerStart( 1 );

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {
      schedulerDispatchTasks();
   }
   return 0;
}
