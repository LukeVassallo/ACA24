#include <xio.h>
#include <string.h>
#include "xparameters.h"

// TODO: Define the UART_BASE_ADDRESS.
#define UART_BASE_ADDRESS 

// TODO: Define the UART register offset. Hint: Look for the register map in the product guide

// TODO: Define the bit masks for the appropriate status flags. Hint: Look for the status registers in the product guide

void print(char *s) {
	// TODO: Write C code to transmit the string using UART.

}

int main(void) {
	u32 status = 0;

	char s[] = "Hello World, this is a demonstrator application for polled io!\r\n";

	print(s);

	while(1) {
		// TODO: Write C code to echo received characters.
		;
	}

	// Exit normally
	return 0;
}
