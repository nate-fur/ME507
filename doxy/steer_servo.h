/**
 * Created by nate furbeyre on 11/18/18.
 * The steering servo is responsible for steering the semi-truck. It is implemented as a
 * child class of both a Servo, and as a TaskBase, allowing it to inherit properties
 * and methods from each parent class.
 */


#ifndef ME507_STEER_SERVO_H
#define ME507_STEER_SERVO_H

#include "Servo.h"
#include "taskbase.h"
#include "../semi_truck_data_t.h"

class steer_servo : public Servo, public TaskBase {
private:
	semi_truck_data_t *semi_data;

public:
    /**
     * @brief The constructor for a steer_servo that handles steering of the semi-truck.
     * @param a_name the name of the task
     * @param a_priority The priority given to this task
     * @param a_stack_size The amount of bytes given to the task
     * @param p_ser_dev A serial device that this tasks output is sent to
     * @param semi_data_in A pointer to the semi truck system data that is communicated between tasks
     */
	steer_servo(const char *a_name,
				unsigned char a_priority = 0,
				size_t a_stack_size = configMINIMAL_STACK_SIZE,
				emstream *p_ser_dev = NULL,
				semi_truck_data_t *semi_data_in = NULL);

	/**
	 * @brief Runs the task code for the steering servo.
	 * This method simulates finite state machine with a single state: on. In this state, the servo will
	 * actuate (based on PWM level) to hit the setpoint steering angle from the Raspberry Pi's
	 * control loop task.
	 */
    void run(); // contains a finite state machine: 2 states, open and closed


};


#endif //ME507_STEER_SERVO_H
