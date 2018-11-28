/**
 * Created by nate furbeyre on 11/19/18.
 * The wheel_speed class holds the software behind the QRE1113 Analog IR Sensor
 * that is used to track wheel speed of the semi-truck. On the inner rim of each
 * of the front wheels, there is a strip of alternating black and white tape. The
 * sensor can read which color tape is measured based on the analog signal, and
 * the data can be processed into a speed of the truck.
 *
 * Some code of this class is based off of http://bildr.org/2011/06/qre1113-arduino/
 */


#ifndef ME507_WHEEL_SPEED_H
#define ME507_WHEEL_SPEED_H


#include <ridgely_inc/taskbase.h>
#include "../semi_truck_data_t.h"

class wheel_speed : public TaskBase {
private:
	semi_truck_data_t *semi_data;
public:

	/**
     * @brief The constructor for the wheel speed sensor to track speed of the semi-truck.
     * @param a_name the name of the task
     * @param a_priority The priority given to this task
     * @param a_stack_size The amount of bytes given to the task
     * @param p_ser_dev A serial device that this tasks output is sent to
     * @param semi_data_in A pointer to the semi truck system data that is communicated between tasks
     */
	wheel_speed(const char *a_name,
				unsigned char a_priority = 0,
				size_t a_stack_size = configMINIMAL_STACK_SIZE,
				emstream *p_ser_dev = NULL,
				semi_truck_data_t *semi_data_in = NULL);

	/**
	 * @brief Runs the task code for the wheel speed sensor.
	 * This task has a single state: reading the wheel speed sensors to determine how fast
	 * the truck is going.
	 */
    void run();
};


#endif //ME507_WHEEL_SPEED_H
