//**************************************************************************************
/** @file task_user.cpp
 *    This file contains source code for a user interface task for a ME405/FreeRTOS
 *    test suite. 
 *
 *  Revisions:
 *    @li 09-30-2012 JRR Original file was a one-file demonstration with two tasks
 *    @li 10-05-2012 JRR Split into multiple files, one for each task
 *    @li 10-25-2012 JRR Changed to a more fully C++ version with class task_user
 *    @li 11-04-2012 JRR Modified from the data acquisition example to the test suite
 *    @li 01-04-2014 JRR Changed base class names to TaskBase, TaskShare, etc.
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
//**************************************************************************************

#include <avr/io.h>                         // Port I/O for SFR's
#include <avr/wdt.h>                        // Watchdog timer header

#include "task_user.h"                      // Header for this file


/** This constant sets how many RTOS ticks the task delays if the user's not talking.
 *  The duration is calculated to be about 5 ms.
 */
const TickType_t ticks_to_delay = ((configTICK_RATE_HZ / 1000) * 5);


//-------------------------------------------------------------------------------------
/** This constructor creates a new data acquisition task. Its main job is to call the
 *  parent class's constructor which does most of the work.
 *  @param a_name A character string which will be the name of this task
 *  @param a_priority The priority at which this task will initially run (default: 0)
 *  @param a_stack_size The size of this task's stack in bytes 
 *                      (default: configMINIMAL_STACK_SIZE)
 *  @param p_ser_dev Pointer to a serial device (port, radio, SD card, etc.) which can
 *                   be used by this task to communicate (default: NULL)
 */

task_user::task_user (const char* a_name, 
					  unsigned portBASE_TYPE a_priority, 
					  size_t a_stack_size,
					  emstream* p_ser_dev
					 )
	: TaskBase (a_name, a_priority, a_stack_size, p_ser_dev)
{
	// Nothing is done in the body of this constructor. All the work is done in the
	// call to the frt_task constructor on the line just above this one
}


//-------------------------------------------------------------------------------------
/** This task interacts with the user for force him/her to do what he/she is told. It
 *  is just following the modern government model of "This is the land of the free...
 *  free to do exactly what you're told." 
 */

void task_user::run (void)
{
	char char_in;                           // Character read from serial device
	time_stamp a_time;                      // Holds the time so it can be displayed
	uint32_t number_entered = 0;            // Holds a number being entered by user

	// Tell the user how to get into command mode (state 1), where the user interface
	// task does interesting things such as diagnostic printouts
	*p_serial << PMS ("Press 'h' or '?' for help") << endl;

	// This is an infinite loop; it runs until the power is turned off. There is one 
	// such loop inside the code for each task
	for (;;)
	{
		// Run the finite state machine. The variable 'state' is kept by parent class
		switch (state)
		{
			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 0, we're in command mode, so when the user types characters, 
			// the characters are interpreted as commands to do something
			case (0):
				if (p_serial->check_for_char ())            // If the user typed a
				{                                           // character, read
					char_in = p_serial->getchar ();         // the character

					// In this switch statement, we respond to different characters as
					// commands typed in by the user
					switch (char_in)
					{
						// The 't' command asks what time it is right now
						case ('t'):
							*p_serial << (a_time.set_to_now ()) << endl;
							break;

						// The 's' command asks for version and status information
						case ('s'):
							show_status ();
							break;

						// The 'd' command has all the tasks dump their stacks
						case ('d'):
							print_task_stacks (p_serial);
							break;

						// The 'h' command is a plea for help; '?' works also
						case ('h'):
						case ('?'):
							print_help_message ();
							break;

						// The 'n' command runs a test of entering a number
						case ('n'):
							*p_serial << PMS ("Enter decimal numeric digits, "
							             "then RETURN or ESC") << endl;
							number_entered = 0;
							transition_to (1);
							break;

						// A control-C character causes the CPU to restart
						case (3):
							*p_serial << PMS ("Resetting AVR") << endl;
							wdt_enable (WDTO_120MS);
							for (;;);
							break;

						// If character isn't recognized, ask What's That Function?
						default:
							*p_serial << '"' << char_in << PMS ("\": WTF?") << endl;
							break;
					}; // End switch for characters
				} // End if a character was received

				break; // End of state 0

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// In state 1, wait for user to enter digits and build 'em into a number
			case (1):
				if (p_serial->check_for_char ())        // If the user typed a
				{                                       // character, read
					char_in = p_serial->getchar ();     // the character

					// Respond to numeric characters, Enter or Esc only. Numbers are
					// put into the numeric value we're building up
					if (char_in >= '0' && char_in <= '9')
					{
						*p_serial << char_in;
						number_entered *= 10;
						number_entered += char_in - '0';
					}
					// Carriage return is ignored; the newline character ends the entry
					else if (char_in == 10)
					{
						*p_serial << "\r";
					}
					// Carriage return or Escape ends numeric entry
					else if (char_in == 13 || char_in == 27)
					{
						*p_serial << endl << PMS ("Number entered: ") 
								  << number_entered << endl;
						transition_to (0);
					}
					else
					{
						*p_serial << PMS ("<invalid char \"") << char_in 
								  << PMS ("\">");
					}
				}

				// Check the print queue to see if another task has sent this task 
				// something to be printed
				else if (p_print_ser_queue->check_for_char ())
				{
					p_serial->putchar (p_print_ser_queue->getchar ());
				}

				break; // End of state 1

			// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
			// We should never get to the default state. If we do, complain and restart
			default:
				*p_serial << PMS ("Illegal state! Resetting AVR") << endl;
				wdt_enable (WDTO_120MS);
				for (;;);
				break;

		} // End switch state

		runs++;                             // Increment counter for debugging

		// No matter the state, wait for approximately a millisecond before we 
		// run the loop again. This gives lower priority tasks a chance to run
		delay_ms (1);
	}
}


//-------------------------------------------------------------------------------------
/** This method prints a simple help message.
 */

void task_user::print_help_message (void)
{
	*p_serial << PROGRAM_VERSION << PMS (" help") << endl;
	*p_serial << PMS ("  t:     Show the time right now") << endl;
	*p_serial << PMS ("  s:     Version and setup information") << endl;
	*p_serial << PMS ("  d:     Stack dump for tasks") << endl;
	*p_serial << PMS ("  n:     Enter a number (demo)") << endl;
	*p_serial << PMS ("  Ctl-C: Reset the AVR") << endl;
	*p_serial << PMS ("  h:     HALP!") << endl;
}


//-------------------------------------------------------------------------------------
/** This method displays information about the status of the system, including the
 *  following: 
 *    \li The name and version of the program
 *    \li The name, status, priority, and free stack space of each task
 *    \li Processor cycles used by each task
 *    \li Amount of heap space free and setting of RTOS tick timer
 */

void task_user::show_status (void)
{
	time_stamp the_time;					// Holds current time for printing

	// First print the program version, compile date, etc. 
	*p_serial << endl << PROGRAM_VERSION << PMS (__DATE__) << endl 
			  << PMS ("System time: ") << the_time.set_to_now ()
			  << PMS (", Heap: ") << heap_left() << "/" << configTOTAL_HEAP_SIZE
			  #ifdef OCR5A
				<< PMS (", OCR5A: ") << OCR5A << endl << endl;
			  #elif (defined OCR3A)
				<< PMS (", OCR3A: ") << OCR3A << endl << endl;
			  #else
				<< PMS (", OCR1A: ") << OCR1A << endl << endl;
			  #endif

	// Have the tasks print their status; then the same for the shared data items
	print_task_list (p_serial);
	*p_serial << endl;
	print_all_shares (p_serial);
}

