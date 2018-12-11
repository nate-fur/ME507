//
// Created by nate on 11/18/18.
//

#include "mega_comm_task.h"


mega_comm_task::mega_comm_task(const char* a_name, unsigned portBASE_TYPE a_priority,
		size_t a_stack_size, emstream* p_ser_dev, uint16_t baud, uint8_t port,
		communication_data *comm_data_in)
		: TaskBase::TaskBase(a_name, a_priority, a_stack_size, p_ser_dev),
		rs232::rs232(baud, port)
{
	data_for_tasks = comm_data_in; // points to data that will be held in main (or be static)
}

void mega_comm_task::run()
{
	/// receive data from pi and relay to tasks
	read_from_pi();
	/// send data about tasks to the pi
	write_to_pi();
	delay_ms(10);

}

void mega_comm_task::read_from_pi()
{
	portENTER_CRITICAL ();
	if (check_for_char()) { /// if the other device writes all data atomically, then we can read all data (also atomically)
		data_for_tasks->set_motor_output(read_16bit_val()); // motor output is going to be a 16 bit value
		data_for_tasks->set_steer_output(read_16bit_val());
		data_for_tasks->set_desired_gear(getchar()); // desired gear is only an 8 bit value
		data_for_tasks->set_desired_5th(getchar());
	}
	portEXIT_CRITICAL ();
}

void mega_comm_task::write_to_pi()
{
	portENTER_CRITICAL ();
	write_16bit_val(data_for_tasks->get_wheel_speed());  /// an ugly way to do this is through bitshifting...
	write_16bit_val(data_for_tasks->get_imu_angle());
	putchar(data_for_tasks->get_actual_gear());
	putchar(data_for_tasks->get_actual_5th());
	portEXIT_CRITICAL ();
}

void mega_comm_task::write_16bit_val(int16_t write_val)
{
	char out_val;
	char num_bytes = 2;

	for (char i=0; i < num_bytes; i++) {
		out_val = ((char)(write_val >> 8*i)) & (char)0xFF; // shift right depending on which byte is sent
		putchar(out_val);
	}
}

int16_t mega_comm_task::read_16bit_val()
{
	int16_t ret_val = 0;
	char num_bytes = 2;
	char temp;

	for (int i=0; i < num_bytes; i++) {
		temp = getchar();
		ret_val = temp & (char) 0xFF; // get a byte of data
		if (i != num_bytes-1)
			ret_val = ret_val << 8; // shift byte to the left if it is not the last byte value
	}

	return ret_val;
}


