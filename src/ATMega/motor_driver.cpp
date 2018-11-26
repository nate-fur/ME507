//
// Created by nate on 11/19/18.
//

#include "motor_driver.h"
#include "../semi_truck_data_t.h"

motor_driver::motor_driver(const char *a_name, unsigned char a_priority, size_t a_stack_size, emstream *p_ser_dev,
                           semi_truck_data_t *semi_data_in)
        : TaskBase(a_name, a_priority, a_stack_size, p_ser_dev)
{
    semi_data = semi_data_in;
}

void motor_driver::run()
{

}