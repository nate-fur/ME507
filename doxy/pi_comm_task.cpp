#include "pi_comm_task.h"

#define PI_USART_PORT 0

pi_comm_task::pi_comm_task(const char* a_name, unsigned portBASE_TYPE a_priority,
		size_t a_stack_size, emstream* p_ser_dev, uint16_t baud, uint8_t port)
		: TaskBase::TaskBase(a_name, a_priority, a_stack_size, p_ser_dev),
		rs232::rs232(baud, port)
{

}

void pi_comm_task::run()
{

}

