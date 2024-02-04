/**
 * @author:	Sagar Ladla [sagarladla@gmail.com]
 * @file:	main.c
 * @brief:	main entry file after bootloader startup or system reset.
*/

#include <stdint.h>

uint32_t a = 0x08888;
const uint32_t const_v_1 = 10000;

int main()
{

	return a + const_v_1;
}