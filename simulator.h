#pragma once

#include <inttypes.h>

enum SIM_actions_enum {
	send_packet=1,
	save_to_eeprom=2,
	sym_encryption=3,
	sym_decryption=4,
	asym_encryption=5,
	asym_decruption=6,
	hw_generate_random=7,
	ecdh_exhange_calculate=8,
	ecdh_key_calculate=9,
	pubkey_calculate = 10
};
typedef enum SIM_actions_enum SIM_action;

enum SIM_errors_enum {
	general_exception=-1,
	log_already_open=-2,
	unable_to_open_file=-3,
	not_initialized=-4,
	unable_to_close=-5,
	success = 0,
	success_with_warning = 1
};
typedef enum SIM_errors_enum SIM_error;

extern char* SIM_last_error;
SIM_error SIM_open_log(const char* location);
SIM_error SIM_log_action(SIM_action action, uint32_t amount, const char* annotation);
SIM_error SIM_close_log();
