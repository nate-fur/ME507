/**
 * Created by nate furbeyre on 11/18/18.
 * The fifth wheel is responsible for locking and unlocking the connection between the
 * semi-truck tractor and trailer. It is implemented as a child class of both a Servo,
 * and as a TaskBase, allowing it to inherit properties and methods from each parent class.
 */

#ifndef ME507_FIFTH_WHEEL_H
#define ME507_FIFTH_WHEEL_H

#include "Servo.h"
#include "taskbase.h"
#include "../semi_truck_data_t.h"

class fifth_wheel : public Servo, public TaskBase {
public:
	/**
     * @brief The constructor for a fifth_wheel, which locks and unlocks the trailer hitch
     * @param a_name the name of the task
     * @param a_priority The priority given to this task
     * @param a_stack_size The amount of bytes given to the task
     * @param p_ser_dev A serial device that this tasks output is sent to
     * @param semi_data A pointer to the semi truck system data that is communicated between tasks
     */
    fifth_wheel(const char *a_name, unsigned char a_priority = 0, size_t a_stack_size = configMINIMAL_STACK_SIZE,
                emstream *p_ser_dev = NULL, semi_truck_data_t *semi_data_in = NULL);

	/**
	 * @brief Runs the task code for the fifth wheel.
	 * This method simulates finite state machine with 2 different states: locked (1) and unlocked (2).
	 * In its unlocked state, the servo is configured so that the trailer can be attached or detached
	 * from the tractor. In its unlocked state, the servo locks the fifth wheel.
	 */
    void run(); // contains a finite state machine: 2 states, open and closed

    /**
     * @brief sets the value of toggle for the fifth_wheel
     * This method is primarily called by the mastermind task that is responsible for retrieving
     * values from the RC controller and setting variables accordingly
     * @param value A boolean value signifying whether or not to toggle the locked / unlocked state
     * of the fifth wheel.
     */

private:
    semi_truck_data_t *semi_data;

    // overwriting parent state variable; we only have 2 states: true (locked) and false (unlocked)
    bool state;

    /**
     * @brief locks the servo
     * Provides a value (representing a PWM width) to the servo that puts the servo position
     * into a locked state for the fifth wheel
     */
    void lock_servo();
    /**
     * @brief unlocks the servo
     * Provides a value (representing a PWM width) to the servo that puts the servo position
     * into an unlocked state for the fifth wheel
     */
    void unlock_servo();

};


#endif //ME507_FIFTH_WHEEL_H
