//
// Created by nate on 11/8/18.
//

#include <iostream>
#include <ridgely_inc/rs232int.h>
#include "Adafruit_BNO055.h"
#include "communication_data.h"
#include "ATMega/imu_task.h"
#include "ATMega/fifth_wheel.h"
#include "ATMega/gear_shifter.h"
#include "ATMega/motor_driver.h"
#include "ATMega/steer_servo.h"
#include "ATMega/wheel_speed.h"
#include "ATMega/mega_comm_task.h"

using namespace std;

const uint8_t N_MULTI_TASKS = 8;

int main() {

    /// a bunch of initialization code

    static semi_truck_data_t semi_truck_data = {0};
    auto comm_data = new communication_data(&semi_truck_data);
    auto *p_ser_port = new rs232 (9600, 1);
    

    auto fifth = new fifth_wheel("fifth_wheel", 1, 200, nullptr, &semi_truck_data);
    auto shifter = new gear_shifter("gear_shifter", 1, 200, nullptr, &semi_truck_data);
    auto imu = new imu_task("imu", 5, 400, nullptr, 0, 0, nullptr);
    auto comm = new mega_comm_task("communicator", 5, 500, nullptr, 9600, 1, comm_data); // works with non-reference to comm data?
    auto motor = new motor_driver("motor", 6, 400, nullptr, &semi_truck_data);
    auto steering = new steer_servo("steering", 6, 400, nullptr, nullptr);
    auto speed = new wheel_speed("speed sensor", 9, 400, nullptr, nullptr);


    /// the actual freeRTOS function that runs the scheduler
}