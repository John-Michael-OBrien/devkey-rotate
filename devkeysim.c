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
	BTM_KEY devkey;
	BTM_EXCHANGE_PARAMETERS params;
	BTM_ECDH_EXHCANGE remote_exchange;


	debug_log("DEVKEY cycling test simulator");
	debug_log("John-Michael O'Brien; University of Colorado, Boulder");

	debug_log("Opening log...");

	RUN_AND_CHECK(SIM_open_log("activity_log.txt"));

	debug_log("Starting DEVKEY test simulations...");

	BTM_start_rotation(&params, devkey);
	BTM_complete_rotation(devkey, remote_exchange, &params);

	debug_log("Closing up...");
	RUN_AND_CHECK(SIM_close_log());

	debug_log("Finished!");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
