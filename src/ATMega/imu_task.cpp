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
	/// NEED TO DO SOME CALIBRATION AND SETUP FOR THE BNO055 DEVICE

}

void imu_task::run()
{
	/* Once the device is setup to correctly read data, we can just continually read
	 from the IMU and write to the mega task data */

}
