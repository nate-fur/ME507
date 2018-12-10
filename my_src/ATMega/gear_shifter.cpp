//
// Created by nate on 11/18/18.
//

#include "gear_shifter.h"

#define FIRST_GEAR 1
#define SECOND_GEAR 2
#define THIRD_GEAR 3

#define FIRST_GEAR_LEVEL 1
#define SECOND_GEAR_LEVEL 2
#define THIRD_GEAR_LEVEL 3

gear_shifter::gear_shifter(const char *a_name, unsigned char a_priority, size_t a_stack_size, emstream *p_ser_dev,
                           semi_truck_data_t *semi_data_in)
		: TaskBase::TaskBase(a_name, a_priority, a_stack_size, p_ser_dev),
		Servo::Servo()
{
	semi_data = semi_data_in;
	shift_to_first();
	semi_data->desired_gear = FIRST_GEAR;
	state = FIRST_GEAR;
}

void gear_shifter::run()
{
	shift_to_first();

	for (;;) {

		if (state != semi_data->desired_gear) { // if the the same, don't need to actuate servo; should make loop faster

			if (state == FIRST_GEAR) {
				if (semi_data->desired_gear == SECOND_GEAR) {
					shift_to_second();
					state = SECOND_GEAR;
				} else if (semi_data->desired_gear == THIRD_GEAR) {
					shift_to_third();
					state = SECOND_GEAR;
				}

			} else if (state == SECOND_GEAR) {
				if (semi_data->desired_gear == FIRST_GEAR) {
					shift_to_first();
					state = FIRST_GEAR;
				} else if (semi_data->desired_gear == THIRD_GEAR) {
					shift_to_third();
					state = THIRD_GEAR;
				}

			} else if (state == THIRD_GEAR) {
				if (semi_data->desired_gear == FIRST_GEAR) {
					shift_to_first();
					state = FIRST_GEAR;
				} else if (semi_data->desired_gear == SECOND_GEAR) {
					shift_to_second();
					state = SECOND_GEAR;
				}

			} else { // in some incorrect state; print status and break
				print_status(*p_serial);
				break;
			}
		}
	}
}

void gear_shifter::shift_to_first()
{
	write(FIRST_GEAR_LEVEL);
	semi_data->actual_gear = FIRST_GEAR;
}

void gear_shifter::shift_to_second()
{
	write(SECOND_GEAR_LEVEL);
	semi_data->actual_gear = SECOND_GEAR;
}

void gear_shifter::shift_to_third()
{
	write(THIRD_GEAR_LEVEL);
	semi_data->actual_gear = THIRD_GEAR;
}

uint8_t gear_shifter::get_actual_level()
{
    return state; // actual level of the servo
}

void gear_shifter::set_desired_level(uint8_t in_level)
{
	semi_data->desired_gear = in_level;
}

