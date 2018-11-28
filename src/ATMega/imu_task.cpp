//
// Created by nate on 11/19/18.
//

#include "imu_task.h"
#include "../semi_truck_data_t.h"

imu_task::imu_task(const char *a_name, unsigned char a_priority, size_t a_stack_size, emstream *p_ser_dev, uint32_t sensorID,
                   uint8_t address, semi_truck_data_t *semi_data_in)
		: TaskBase(a_name, a_priority, a_stack_size, p_ser_dev),
		Adafruit_BNO055(sensorID, address)
{
    semi_data = semi_data_in;
    state = 0;
	/// NEED TO DO SOME CALIBRATION AND SETUP FOR THE BNO055 DEVICE

}

void imu_task::run()
{
	/* Once the device is setup to correctly read data, we can just continually read
	 from the IMU and write to the mega task data */
	char temp_buffer[2];

	for (;;) {
		if (state == 1) { // checked first for simple optimization as this is the primary state that the imu is in
		    readLen(BNO055_EULER_H_MSB_ADDR, temp_buffer, 2);
		    semi_data->imu_angle = *((int16_t *)temp_buffer); // interesting but necessary casting to get value into semi_data
		}

		else if (state == 0) {
			// todo: initialize the imu either here or in the constructor

			state = 1;
		}
		else {
            print_status(*p_serial);
            break;
		}

	}

}
