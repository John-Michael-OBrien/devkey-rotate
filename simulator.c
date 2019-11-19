#include <stdio.h>
#include <stdbool.h>

#include "simulator.h"

FILE* log_file;
char* SIM_last_error="";

SIM_error SIM_open_log(const char* location) {
	if (log_file != NULL) {
		SIM_last_error = "Log is already open.";
		return log_already_open;
	}
	if (fopen_s(&log_file, location, "w") != 0) {
		return unable_to_open_file;
	}

	return success;
}
SIM_error SIM_log_action(SIM_action action, uint32_t amount, const char* annotation) {
	if (log_file == NULL) {
		SIM_last_error = "Log has not been initialized.";
		return not_initialized;
	}

	// Write the log entry (tab delimited)
	fprintf(log_file, "%9d\t%9d\t%s\n", action, amount, annotation);

	return success;
}
SIM_error SIM_close_log() {
	if (log_file != log_file) {
		SIM_last_error = "Log was already closed.";
		return success_with_warning;
	}

	if (fclose(log_file) != 0) {
		SIM_last_error = "Error closing log file.";
		return unable_to_close;
	}
	
	return success;
}