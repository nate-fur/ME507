/**
 * Created by nate furbeyre on 11/19/18.
 * The motor_driver task holds the code that runs the motor for the semi-truck.
 * The motor involved in this project is the Tekin RX8 ESC + 1550kv combo. Output
 * levels to the motor come from the control loop running on the Raspberry Pi that
 * is based on the data from the RC controller and the wheel speed sensors.
 */

#ifndef ME507_MOTOR_DRIVER_H
#define ME507_MOTOR_DRIVER_H


#include <ridgely_inc/taskbase.h>
#include "../semi_truck_data_t.h"

class motor_driver : public TaskBase {
private:
	semi_truck_data_t *semi_data;
	
public:
    /**
     * @brief The constructor for the motor driver to supply power to the motor.
     * @param a_name the name of the task
     * @param a_priority The priority given to this task
     * @param a_stack_size The amount of bytes given to the task
     * @param p_ser_dev A serial device that this tasks output is sent to
     * @param semi_data_in A pointer to the semi truck system data that is communicated between tasks
     */
	motor_driver(const char *a_name,
				 unsigned char a_priority = 0,
				 size_t a_stack_size = configMINIMAL_STACK_SIZE,
				 emstream *p_ser_dev = NULL,
				 semi_truck_data_t *semi_data_in = NULL);

	/**
	 * @brief Runs the task code for the motor driver.
	 * This task has a single state: reading output level that comes from the control
	 * loop running on the Raspberry pi, and actuating the motor to this level.
	 */
    void run();
};


#endif //ME507_MOTOR_DRIVER_H
