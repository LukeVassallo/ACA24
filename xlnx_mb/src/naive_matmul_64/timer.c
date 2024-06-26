#include <xparameters.h>
#include <xio.h>
#include "timer.h"

void configure_timer(){
	XIo_Out32((volatile u32 *) (XPAR_AXI_TIMER_0_BASEADDR),(1 << 11));

	// timer load registers set to 0
	XIo_Out32((volatile u32 *) (XPAR_AXI_TIMER_0_BASEADDR+0x4), 0);
	XIo_Out32((volatile u32 *) (XPAR_AXI_TIMER_0_BASEADDR+0x14), 0);

}

void clear_timer() {
	// load timer with contents from the associated load registers
	XIo_Out32((volatile u32 *) (XPAR_AXI_TIMER_0_BASEADDR),(1 << 5));

}

void start_timer() {
	clear_timer();
	XIo_Out32((volatile u32 *) (XPAR_AXI_TIMER_0_BASEADDR),(1 << 11) | (1 <<7));
}

double stop_timer() {
	double t;
	long long unsigned int upper;		// 64-bit unsigned - see UG984 Table 4.1
	long unsigned int lower;			// 32-bit unsigned
	XIo_Out32((volatile u32 *) (XPAR_AXI_TIMER_0_BASEADDR),(1 << 11));

	upper = ((long long unsigned int) XIo_In32((volatile u32 *) (XPAR_AXI_TIMER_0_BASEADDR+0x18))) << 32;
	lower = XIo_In32((volatile u32 *) (XPAR_AXI_TIMER_0_BASEADDR+0x8));
	t = (double) (upper+lower);
	t = t / XPAR_MICROBLAZE_CORE_CLOCK_FREQ_HZ;

	return t;
}
