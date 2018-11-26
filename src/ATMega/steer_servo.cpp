//
// Created by nate on 11/18/18.
//

#include "steer_servo.h"
#include "../semi_truck_data_t.h"

#define FORWARDS 0

steer_servo::steer_servo(const char *a_name, unsigned char a_priority, size_t a_stack_size, emstream *p_ser_dev,
						 semi_truck_data_t *semi_data_in)
		:TaskBase::TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
    semi_data = semi_data_in;
    write(FORWARDS); // want the semi-truck to start facing forwards
}

void steer_servo::run()
{
	for (;;) {
	    write(semi_data->steer_output);
	}
}

void steer_servo::set_steering_level(int16_t level)
{
	semi_data->steer_output= level;
}

int16_t steer_servo::get_steering_level()
{
	return semi_data->steer_output;
}

