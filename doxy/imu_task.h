/**
 * Created by nate furbeyre on 11/19/18.
 * The imu_task is responsible for reading data from Adafruit's BNO055 IMU device.
 * This class descends both the Adafruit_BNO055 class written by Adafruit, and TaskBase,
 * written by JRR as a wrapper to the FreeRTOS task class.
 */

#ifndef ME507_IMU_H
#define ME507_IMU_H

#define BNO055_ADDRESS_A (0x28)

#include <Adafruit_BNO055/Adafruit_BNO055.h>
#include <ridgely_inc/taskbase.h>
#include "../semi_truck_data_t.h"

class imu_task : public TaskBase, public Adafruit_BNO055  {
private:
    semi_truck_data_t *semi_data;

public:
    /**
     * @brief The constructor for a mega_comm_task object communicates with the Rasp-Pi.
     * @param a_name the name of the task
     * @param a_priority The priority given to this task
     * @param a_stack_size The amount of bytes given to the task
     * @param p_ser_dev A serial device that this tasks output is sent to
     * @param sensorID The ID number for the IMU sensor
     * @param address The actual address for the BNO055 device itself
     * @param semi_data_in A pointer to the semi truck system data that is communicated between tasks
     */
    imu_task(const char *a_name,
             unsigned char a_priority = 0,
             size_t a_stack_size = configMINIMAL_STACK_SIZE,
             emstream *p_ser_dev = NULL,
             uint32_t sensorID = -1,
             uint8_t address = BNO055_ADDRESS_A,
             semi_truck_data_t *semi_data_in = NULL);

    /**
     * Runs the infinite loop task code for reading IMU data. This task has only one effective state; reading
     * angle data of the semi truck to be input into the control loop for a steering servo output.
     */
    void run();
};


#endif //ME507_IMU_H
