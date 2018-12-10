/**
 * Created by nate furbeyre on 11/18/18.
 * The mega_comm_task task is responsible for receiving information from the raspberry
 * pi and relaying the necessary information to each of the tasks controlled by the
 * ATMega64. In addition, it sends information back to the Raspberry Pi about different
 * states of tasks on the ATMega. It uses the rs232 communication protocol and the UART/
 * USART ports on the ATMega.
 */

#ifndef ME507_mega_comm_task_H
#define ME507_mega_comm_task_H

#include <ridgely_inc/rs232int.h>
#include <ridgely_inc/taskshare.h>
#include "taskbase.h"
#include "../communication_data.h"


class mega_comm_task : public TaskBase, public rs232 {
private:
    /**
     * data_for_tasks is the data that will be communicated between the raspberry pi and the atmega.
     * fundamentally, the data is of the type semi_truck_data, which itself is inside a class
     * communcation data which extends the taskshare class used for RTOS communication.
     */
	communication_data *data_for_tasks;

public:
	/**
     * @brief The constructor for a mega_comm_task object communicates with the Rasp-Pi.
     * @param a_name the name of the task
     * @param a_priority The priority given to this task
     * @param a_stack_size The amount of bytes given to the task
     * @param p_ser_dev A serial device that this tasks output is sent to
     * @param baud The baud rate for the UART port that the mega communicates with
     * @param port The UART port number
     * @param semi_data_in A pointer to the semi truck system data communicated between tasks
     */
    mega_comm_task(const char* a_name,
    			unsigned portBASE_TYPE a_priority = 0,
    			size_t a_stack_size = configMINIMAL_STACK_SIZE,
			    emstream* p_ser_dev = NULL,
			    uint16_t baud = 9600,
			    uint8_t port = 0,
			    communication_data *comm_data_in = NULL);

    /**
	 * @brief Runs the code for the ATMega64 to transmit and receive data from the Raspberry Pi
     * This method runs on an infinite loop where data is read via an RS232 port from
     * the raspberry pi. The data, which contains information regarding
     * different desired values from the user and control loop, is then
     * relayed to each of the different tasks within the ATMega, so that each task
     * can act accordingly. In addition, this method sends information back to the Raspberry
     * Pi about the actual state of each of the tasks in the ATMega.
	 */
    void run();

    /**
     * @brief Reads data from the raspberry pi through one of the USART ports of the ATMega.
     * Since this class descents the rs232int class, it is able to use its communication based
     * methods for talking with the Raspberry Pi.
     *
     */
	void read_from_pi();

	/**
     * @brief Writes data to the raspberry pi through one of the USART ports of the ATMega.
     * Since this class descents the rs232int class, it is able to use its communication based
     * methods for talking with the Raspberry Pi.
     */
	void write_to_pi();

	/**
	 * @brief writes a 16 bit value to the rs232 port.
	 * This function is implemented using calls to the rs232 class getchar, along with some
	 * bitshifting to get a final value
	 */
	void write_16bit_val(int16_t write_val);

	/**
	 * @brief reads a 16 bit balue from the rs232 port.
	 * This function is implemented using calls to the rs232 class getchar, along with some
	 * bitshifting to get a final value
	 */
	int16_t read_16bit_val();
};


#endif //ME507_mega_comm_task_H
