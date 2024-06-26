#include <xio.h>
#include <string.h>
#include <mb_interface.h>
#include "xparameters.h"

// TODO: Define the UART_BASE_ADDRESS.
#define UART_BASE_ADDRESS 

// TODO: Define the UART register offset. Hint: Look for the register map in the product guide

// TODO: Define the bit masks for the appropriate status flags. Hint: Look for the status registers in the product guide

// TODO: Define interrupt enable bit for the UART module

// More information in MicroBlaze product guide!
void ISR() __attribute__((interrupt_handler));
u32 count=0;

void set_bit_in_reg(u32 addr, u32 bit) {
	// RMW
	u32 val;
	val = XIo_In32((volatile u32 *) addr);
	val |= bit;
	XIo_Out32((volatile u32 *) addr, val);

}

void clear_bit_in_reg(u32 addr, u32 bit) {
	// RMW
	u32 val;
	val = XIo_In32((volatile u32 *) addr);
	val &= !bit;
	XIo_Out32((volatile u32 *) addr, val);

}

void ISR(void)
{
	// TODO: Service the interrupt.

	count++;
}

int main(void) {

	// TODO: Enable the UART to generate interrupts

	// TODO: Enable microblaze to respond to interrupts

	while(1) {

		; // Useful work goes here

	}

	// TODO: Disable Interrupts

	// Exit normally
	return 0;
}

