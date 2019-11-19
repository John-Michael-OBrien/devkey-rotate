#include "utils.h"

#include "simulator.h"

BTM_error BTM_get_crypto_rnd_bytes(const uint8_t* buffer, const int count) {
	// Add to the simulation log
	SIM_log_action(hw_generate_random, count, "Made Random Byte in HW");

	return BTM_success;
}

BTM_error BTM_compute_ecdh_exchange(const BTM_ECDH_EXHCANGE destination, const BTM_PUBKEY pubkey, const BTM_ECDHSECRET secret) {
	// Log that we made a key.
	SIM_log_action(ecdh_exhange_calculate, 1, "Computed ECDH Exchange");

	// Code to actually compute the exchange goes here. (ACM128 I think.)

	return BTM_success;
}

BTM_error BTM_make_pubkey_from_devkey(const BTM_PUBKEY destination, const BTM_KEY devkey) {
	// Log that we convolved a DEVKEY into a public key
	SIM_log_action(pubkey_calculate, 1, "Computed Public key from DEVKEY");

	// Code to actually convolve the devkey to a pubkey goes here (Probably just writing 0s to the first 128 bits and the DEVKEY to the second.)

	return BTM_success;
}

BTM_error BTM_start_rotation(const BTM_EXCHANGE_PARAMETERS_p ecdh_exchange, const BTM_KEY old_devkey) {
	BTM_make_pubkey_from_devkey(ecdh_exchange->pubkey, old_devkey);
	BTM_get_crypto_rnd_bytes(ecdh_exchange->secret, BTM_SECRET_BYTES);
	BTM_compute_ecdh_exchange(ecdh_exchange->exchange, ecdh_exchange->pubkey, ecdh_exchange->secret);

	return BTM_success;
}

BTM_error BTM_complete_rotation(const BTM_KEY new_dev_key, const BTM_ECDH_EXHCANGE remote_ecdh_exchange, const BTM_EXCHANGE_PARAMETERS_p local_ecdh_exchange) {
	// Log that we made a key.
	SIM_log_action(ecdh_key_calculate, 1, "Computed ECDH Key");

	// Code to actually do the ECDH key calculation goes here.

	return BTM_success;
}
