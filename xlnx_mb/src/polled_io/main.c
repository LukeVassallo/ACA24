#include <xio.h>
#include <string.h>
#include "xparameters.h"

// TODO: Define the UART_BASE_ADDRESS.
#define UART_BASE_ADDRESS XPAR_MDM_0_BASEADDR

// TODO: Define the UART register offset. Hint: Look for the register map in the product guide
#define UART_RX_REG 0x00
#define UART_TX_REG 0x04
#define UART_STAT_REG 0x08
#define UART_CTRL_REG 0x0C

// TODO: Define the bit masks for the appropriate status flags. Hint: Look for the status registers in the product guide
#define TX_FIFO_FULL_MASK (1 << 3)
#define RX_FIFO_VALID_DATA (1 << 0)

void print(char *s) {
	// TODO: Write C code to transmit the string using UART.
	u32 status = 0;
	u32 len;

	len = strlen(s);

	for (u32 i=0; i<len; i++) {

		do {
			status = XIo_In32((volatile u32 *) (UART_BASE_ADDRESS+UART_STAT_REG));
		} while(status & TX_FIFO_FULL_MASK);

		XIo_Out32((volatile u32 *) (UART_BASE_ADDRESS+UART_TX_REG), s[i]);
	}
}

int main(void) {
	u32 status = 0;

	char s[] = "Hello World, this is a demonstrator application for polled io!\r\n";

	print(s);

	while(1) {
		// TODO: Write C code to echo received characters.
		do {
			status = XIo_In32((volatile u32 *) (UART_BASE_ADDRESS+UART_STAT_REG));
		} while(! (status & RX_FIFO_VALID_DATA) ); 	// ! has higher precedence than &

		char data = XIo_In32((volatile u32 *) (UART_BASE_ADDRESS+UART_RX_REG)) & 0xFF;

		do {
			status = XIo_In32((volatile u32 *) (UART_BASE_ADDRESS+UART_STAT_REG));
		} while(status & TX_FIFO_FULL_MASK);

		XIo_Out32((volatile u32 *) (UART_BASE_ADDRESS+UART_TX_REG), data);
	}

	// Exit normally
	return 0;
}
