//
// Created by nate on 11/26/18.
//

#ifndef ME507_SEMI_TRUCK_DATA_H
#define ME507_SEMI_TRUCK_DATA_H

#include <cstdint>

/**
 * @brief a data structure that holds all of the information of what state the semi-truck is in at any
 * given time.
 * @var motor_output the output sent to the motor driver
 * @var speed_setpoint the desired speed of the semi-truck as a setpoint to the controller
 * @var steer_output output sent to the steering servo
 * @var wheel_speed speed that the wheel speed sensor is recording
 * @var imu_angle euler angle read by the BNO055 IMU
 * @var actual_gear desired gear level (set by the remote control device)
 * @var desired_5th desired state of the 5th wheel (either locked or unlocked)
 * @var actual_5th actual state of the 5th wheel
 */
struct semi_truck_data_t {
	int16_t motor_output;    // output sent to the motor driver
	int16_t speed_setpoint;  // desired speed of the semi-truck as a setpoint to the controller
    int16_t steer_output;    // output sent to the steering servo
    int16_t wheel_speed;     // speed that the wheel speed sensor is recording
    int16_t imu_angle;       // euler angle read by the BNO055 IMU (degrees)
	int8_t  desired_gear;    // desired gear level (set by the remote control device)
	int8_t  actual_gear;     // actual gear that the transmission is in
    bool    desired_5th;     // desired state of the 5th wheel (locked or unlocked)
    bool    actual_5th;      // actual state of the 5th wheel
};

#endif //ME507_SEMI_TRUCK_DATA_H
