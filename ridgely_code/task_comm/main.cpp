//*************************************************************************************
/** \file main.cpp
 *    This file contains the main() code for a program which tests various features of
 *    the ME405/ME507/FreeRTOS software package. Tests include sending data from tasks
 *    to other tasks by several means and checking for errors in transmission; creating
 *    large numbers of tasks and getting them to all run at the same time; and testing
 *    time stamps by measuring the frequency of signals sent by a signal generator. 
 *
 *  Revisions:
 *    \li 09-30-2012 JRR Original file was a one-file demonstration with two tasks
 *    \li 10-05-2012 JRR Split into multiple files, one for each task plus a main one
 *    \li 10-30-2012 JRR A hopefully somewhat stable version with global queue 
 *                       pointers and the new operator used for most memory allocation
 *    \li 11-04-2012 JRR FreeRTOS Swoop demo program changed to a sweet test suite
 *
 *  License:
 *    This file is copyright 2012 by JR Ridgely and released under the Lesser GNU 
 *    Public License, version 2. It intended for educational use only, but its use
 *    is not limited thereto. */
/*    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUEN-
 *    TIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 *    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 *    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 *    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
//*************************************************************************************


#include <stdlib.h>                         // Prototype declarations for I/O functions
#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header
#include <string.h>                         // Functions for C string handling

#include "FreeRTOS.h"                       // Primary header for FreeRTOS
#include "task.h"                           // Header for FreeRTOS task functions
#include "queue.h"                          // FreeRTOS inter-task communication queues
#include "croutine.h"                       // Header for co-routines and such

#include "rs232int.h"                       // ME405/507 library for serial comm.
#include "time_stamp.h"                     // Class to implement a microsecond timer
#include "taskbase.h"                       // Header of wrapper for FreeRTOS tasks
#include "textqueue.h"                      // Wrapper for FreeRTOS character queues
#include "taskqueue.h"                      // Header of wrapper for FreeRTOS queues
#include "taskshare.h"                      // Header for thread-safe shared data
#include "shares.h"                         // Global ('extern') queue declarations
#include "task_multi.h"                     // Header for the data acquisition task
#include "task_source.h"                    // Header for data sending task
#include "task_sink.h"                      // Header for data receiving task
#include "task_user.h"                      // Header for user interface task


/** This is the number of tasks which will be instantiated from the task_multi class.
 *  These tasks don't to a whole lot except use up processor time and memory space in
 *  order to test how well the program works with lots of tasks.
 */
const uint8_t N_MULTI_TASKS = 4;


// Declare pointers to the shared data items which are used by tasks to communicate 
// with each other here. Each pointer must also be declared 'extern' in a header file
// (traditionally called shares.h) which will be read by every task that needs to use
// inter-task data. 

// This queue allows tasks to send characters to the user interface task for display.
TextQueue* p_print_ser_queue;

/** This queue sends data from the source task to the sink task.
 */
TaskQueue<uint32_t>* p_queue_1;

/** This shared data item allows a value to be posted by the source task and read by
 *  the sink task.
 */
TaskShare<uint32_t>* p_share_1;

/** This global variable will be written by the source task and read by the sink task.
 *  We expect the process to be corrupted by context switches now and then.
 */
uint32_t glob_of_probs;

/** This shared data item is used to test the increment and decrement operators for
 *  shared data items. 
 */
TaskShare<int8_t>* p_share_counter;


//=====================================================================================
/** The main function sets up the RTOS.  Some test tasks are created. Then the 
 *  scheduler is started up; the scheduler runs until power is turned off or there's a 
 *  reset.
 *  @return This is a real-time microcontroller program which doesn't return. Ever.
 */

int main (void)
{
	char multi_task_name[12];				// Stores name for multiple tasks

	// Disable the watchdog timer unless it's needed later. This is important because
	// sometimes the watchdog timer may have been left on...and it tends to stay on
	MCUSR = 0;
	wdt_disable ();

	// Configure a serial port which can be used by a task to print debugging infor-
	// mation, or to allow user interaction, or for whatever use is appropriate.  The
	// serial port will be used by the user interface task after setup is complete and
	// the task scheduler has been started by the function vTaskStartScheduler()
	rs232* p_ser_port = new rs232 (9600, 1);
	*p_ser_port << clrscr << PMS ("ME405/FreeRTOS Task Communication Demo Program") 
				<< endl;

	// This queue allows tasks to send characters to the user interface task for display.
	p_print_ser_queue = new TextQueue (32, "Print", NULL, 10);

	// This queue sends data from the source task to the sink task.
	p_queue_1 = new TaskQueue<uint32_t> (20, "Test Queue");

	// This shared data item allows a value to be posted by the source task and read by
	// the sink task.
	p_share_1 = new TaskShare<uint32_t> ("Test Share");

	// This shared data item is used to test the increment and decrement operators for
	// shared data items. 
	p_share_counter = new TaskShare<int8_t> ("Count");

	// Create the data source and sink tasks
	new task_source ("Source", task_priority (2), 120, p_ser_port);
	new task_sink ("Sink", task_priority (2), 140, p_ser_port);

	// The user interface is at low priority; it could have been run in the idle task
	// but it is desired to exercise the RTOS more thoroughly in this test program.
	new task_user ("UserInt", task_priority (1), 260, p_ser_port);

	// Create a set of tasks from the task_multi class. This is to test how things work
	// when there are a whole bunch of tasks operating
	for (uint8_t index = 0; index < N_MULTI_TASKS; index++)
	{
		strcpy (multi_task_name, "Multi");
		itoa (index, (multi_task_name + 5), 10);

		new task_multi (multi_task_name, task_priority (1), 110, p_ser_port);
	}

	// Print an empty line so that there's space between task hellos and a help 
	// message which will be printed by the user interface task
	*p_ser_port << endl;

	// Here's where the RTOS scheduler is started up. It should never exit as long as
	// power is on and the microcontroller isn't rebooted
	vTaskStartScheduler ();
}

