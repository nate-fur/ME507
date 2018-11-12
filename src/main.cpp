//
// Created by nate on 11/8/18.
//

#include <iostream>
#include "Adafruit_BNO055.h"
using namespace std;


int main() {
    auto *imu = new Adafruit_BNO055(123, 456);

    printf("in main sensorID is %i\n", imu->_sensorID);

    printf("in main: address ID is %i\n", imu->_address);

    cout << "Hello world" << endl;

}