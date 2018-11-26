//
// Created by nate on 11/25/18.
//


#include "communication_data.h"

communication_data::communication_data(semi_truck_data_t *semi_data)
: TaskShare::TaskShare(semi_data)
{
    /// NEED TO FIX THIS CONSTRUCTOR
}

/**
 * Setters
 */

void communication_data::set_data_for_tasks(semi_truck_data_t in_data)
{
    data_for_tasks = in_data;
}

void communication_data::set_motor_output(int16_t in_data)
{
	data_for_tasks.motor_output = in_data;
}

void communication_data::set_speed_setpoint(int16_t in_data)
{
	data_for_tasks.motor_output = in_data;
}

void communication_data::set_steer_output(int16_t in_data)
{
	data_for_tasks.steer_output = in_data;
}

void communication_data::set_wheel_speed(int16_t in_data)
{
	data_for_tasks.steer_output = in_data;
}

void communication_data::set_imu_angle(int16_t in_data)
{
	data_for_tasks.imu_angle = in_data;
}

void communication_data::set_desired_gear(int8_t in_data)
{
	data_for_tasks.desired_gear = in_data;
}

void communication_data::set_actual_gear(int8_t in_data)
{
	data_for_tasks.actual_gear = in_data;
}

void communication_data::set_desired_5th(bool in_data)
{
	data_for_tasks.desired_5th = in_data;
}

void communication_data::set_actual_5th(bool in_data)
{
	data_for_tasks.desired_5th = in_data;
}


/**
 * Getters
 */

semi_truck_data_t communication_data::get_data_for_tasks()
{
	return data_for_tasks;
}

int16_t communication_data::get_motor_output()
{
	return data_for_tasks.motor_output;
}

int16_t communication_data::get_speed_setpoint()
{
	return data_for_tasks.speed_setpoint;
}

int16_t communication_data::get_steer_output()
{
	return data_for_tasks.steer_output;
}

int16_t communication_data::get_wheel_speed()
{
	return data_for_tasks.wheel_speed;
}

int16_t communication_data::get_imu_angle()
{
	return data_for_tasks.imu_angle;
}

int8_t communication_data::get_desired_gear()
{
	return data_for_tasks.desired_gear;
}

int8_t communication_data::get_actual_gear()
{
	return data_for_tasks.actual_gear;
}

bool communication_data::get_desired_5th()
{
	return data_for_tasks.desired_5th;
}

bool communication_data::get_actual_5th()
{
	return data_for_tasks.actual_5th;
}
