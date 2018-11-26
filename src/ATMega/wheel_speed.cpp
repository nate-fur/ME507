//
// Created by nate on 11/19/18.
//

#include "wheel_speed.h"
#include "../semi_truck_data_t.h"

wheel_speed::wheel_speed(const char *a_name, unsigned char a_priority, size_t a_stack_size, emstream *p_ser_dev,
						 semi_truck_data_t *semi_data_in)
		: TaskBase::TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
	semi_data = semi_data_in;
}

void wheel_speed::run()
{

}
