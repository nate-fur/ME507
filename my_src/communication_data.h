//
//@fileCreated by nate on 11/25/18.
//
/**
 * @file this is a comment for the doxygen
 */

#include <ridgely_inc/taskshare.h>
#include "semi_truck_data_t.h"

#ifndef ME507_COMMUNICATION_DATA_H
#define ME507_COMMUNICATION_DATA_H


class communication_data : public TaskShare<semi_truck_data_t> {
private:
	semi_truck_data_t data_for_tasks;


public:
	""""this is a doc""""
	communication_data(semi_truck_data_t *semi_data);

     /**
     * Sets the data_for_task variable of the mega_comm_task class object.
     * @param in_data Data being used to set the object's variable
     */
	void set_data_for_tasks(semi_truck_data_t in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_motor_output(int16_t in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_speed_setpoint(int16_t in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_steer_output(int16_t in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_wheel_speed(int16_t in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_imu_angle(int16_t in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_desired_gear(int8_t in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_actual_gear(int8_t in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_desired_5th(bool in_data);

	/**
	 * Sets the specific data_for_task variable of the mega_comm_task class object
     * @param in_data Data being used to set the object's variable
	 */
	void set_actual_5th(bool in_data);


//////////////////////////////////////////////////////////////////////////////////////

	/**
     * gets the data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	semi_truck_data_t get_data_for_tasks();

	/**
     * gets the specific data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	int16_t get_motor_output();

	/**
     * gets the data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	int16_t get_speed_setpoint();

	/**
     * gets the specific data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */

	int16_t get_steer_output();
	/**
     * gets the data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	int16_t get_wheel_speed();

	/**
     * gets the data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	int16_t get_imu_angle();

	/**
     * gets the specific data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	int8_t get_desired_gear();

	/**
     * gets the specific data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	int8_t get_actual_gear();

	/**
     * gets the data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	bool get_desired_5th();

	/**
     * gets the data_for_task variable of the mega_comm_task class object.
	 * @return the data_for_task variable
	 */
	bool get_actual_5th();

};

#endif //ME507_COMMUNICATION_DATA_H
