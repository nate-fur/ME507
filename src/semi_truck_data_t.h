//
// Created by nate on 11/26/18.
//

#ifndef ME507_SEMI_TRUCK_DATA_H
#define ME507_SEMI_TRUCK_DATA_H

#include <cstdint>

struct semi_truck_data_t {
	int16_t motor_output;    // output sent to the motor driver
	int16_t speed_setpoint;  // desired speed of the semi-truck as a setpoint to the controller
    int16_t steer_output;    // output sent to the steering servo
    int16_t wheel_speed;     // speed that the wheel speed sensor is recording
    uint16_t imu_angle;       // euler angle read by the BNO055 IMU (degrees)
	int8_t  desired_gear;    // desired gear level (set by the remote control device)
	int8_t  actual_gear;     // actual gear that the transmission is in
    bool    desired_5th;     // desired state of the 5th wheel (locked or unlocked)
    bool    actual_5th;      // actual state of the 5th wheel
};

#endif //ME507_SEMI_TRUCK_DATA_H
