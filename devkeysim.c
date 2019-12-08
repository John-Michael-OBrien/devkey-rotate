// devkeysim.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdarg.h>
#include "simulator.h"
#include "utils.h"

#define RUN_AND_CHECK(x) { \
	SIM_error result; \
    result=x; \
    if(result<success){ \
        debug_log("Error on line %d: [%d] %s.", __LINE__, result, SIM_last_error); \
        return 1; \
    } \
    }
#define DEBUG_VERBOSE

void debug_log(const char* format, ...) {
#ifdef DEBUG_VERBOSE
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
	printf("\n");
#endif
}

int main()
{
	BTM_EXCHANGE_PARAMETERS params;
	BTM_ECDH_EXHCANGE remote_exchange;


	debug_log("DEVKEY cycling test simulator");
	debug_log("John-Michael O'Brien; University of Colorado, Boulder");

	debug_log("Opening log...");

	RUN_AND_CHECK(SIM_open_log("activity_log.txt"));

	debug_log("Starting DEVKEY test simulations...");

	// Make a dummy buffer
	uint8_t data[360];

	// Process the first "message" (an invitation)
	BTM_process_message(data, sizeof(data));
	// Process the second "message" (A parameters set)
	BTM_process_message(data, sizeof(data));


	debug_log("Closing up...");
	RUN_AND_CHECK(SIM_close_log());

	debug_log("Finished!");
}
