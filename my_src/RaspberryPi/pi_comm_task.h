/**
 * Created by nate furbeyre on 11/19/18.
 * The pi_comm_task task is responsible for receiving information from the ATMega
 * and relaying the necessary information to each of the tasks controlled by the
 * Rasp-Pi. In addition, it sends information back to the ATMega with output values
 * from the control loop
 */

#ifndef ME507_PI_COMM_TASK_H
#define ME507_PI_COMM_TASK_H


#include <ridgely_inc/taskbase.h>
#include <ridgely_inc/rs232int.h>

class pi_comm_task : public TaskBase, public rs232 {

	/**
     * @brief The constructor for a mega_comm_task object communicates with the Rasp-Pi.
     * @param a_name the name of the task
     * @param a_priority The priority given to this task
     * @param a_stack_size The amount of bytes given to the task
     * @param p_ser_dev A serial device that this tasks output is sent to
     * @param baud The baud rate for the UART port that the mega communicates with
     * @param port The UART port number
     */
    pi_comm_task(const char* a_name,
    			unsigned portBASE_TYPE a_priority = 0,
    			size_t a_stack_size = configMINIMAL_STACK_SIZE,
			    emstream* p_ser_dev = NULL,
			    uint16_t baud = 9600,
			    uint8_t port = 0);

    /**
	 * @brief Runs the code for the Raspberry Pi to transmit and receive data from the ATMega
     * This method runs on an infinite loop where data is read via an RS232 port from
     * the ATMega. The data received contains information about the status of different
     * tasks, and values input into the control loop. The output of the control loops are
     * sent back to the ATMega for actuation of different devices in the system.
	 */
    void run();

};


#endif //ME507_PI_COMM_TASK_H
