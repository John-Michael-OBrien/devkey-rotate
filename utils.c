#include "string.h"

#include "utils.h"
#include "simulator.h"

// Allocate space for our DEVKEY
BTM_KEY devkey;

// Allocate space for the pending exchange. We'll assume only one is ever active at once.
BTM_EXCHANGE_PARAMETERS pending_exchange;

BTM_error BTM_load_from_NVRAM(const uint8_t* buffer, const int count) {
	SIM_log_action(read_byte_from_nvram, count, "Loaded value from NVRAM");

	// Code to read from the NVRAM goes here.

	return BTM_success;
}

BTM_error BTM_store_to_NVRAM(const uint8_t* buffer, const int count) {
	SIM_log_action(read_byte_from_nvram, count, "Stored value to NVRAM");

	// Code to write to the NVRAM goes here.

	return BTM_success;
}

BTM_error BTM_asym_decrypt(uint8_t* output, int *out_length_p, const uint8_t* message, const int length, BTM_ASYMKEY private_key) {
	SIM_log_action(asym_decryption, length, "Decrypted message using private key");

	*out_length_p = length;
	// Copy it over blind since we're just simulating and don't care about the actual data.
	memcpy(output, message, length);

	// Code to do Elliptic Curve or RSA decryption goes here.

	return BTM_success;
}

BTM_error BTM_verify_signature(const uint8_t* message, const int length, const BTM_SIGNATURE_p sig) {
	BTM_ASYMKEY ra_key;
	BTM_load_from_NVRAM(ra_key, BTM_ASYMKEY_BYTES);
	SIM_log_action(verify_signature, length, "Verified Signature");

	// Code to do the actual verification goes here.

	return BTM_success;
}

BTM_error BTM_get_crypto_rnd_bytes(const uint8_t* buffer, const int count) {
	// Add to the simulation log
	SIM_log_action(hw_generate_random, count, "Made Random Byte in HW");

	// Code to actually call the HW crypto core goes here.

	return BTM_success;
}

BTM_error BTM_compute_ecdh_exchange(const BTM_ECDH_EXHCANGE_p destination, const BTM_PUBKEY pubkey, const BTM_ECDHSECRET secret) {
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

BTM_error BTM_process_message(const uint8_t* message, const int length) {
	// Simulation state variable. Odd means start exchange, even means end it.
	static run = 0;

	// Code for deencapsulation and dispatch goes here.

	// We're going to just assume a completed deencapsulation and that we've been dispatched a DEVKEY app message.

	// Make sure our message is big enough to even have a signature. This is necessary for buffer underrun reasons.
	long offset = 0;
	if (length < 256) {
		return BTM_general_exception;
	}
	else {
		offset = length - 256;
	}

	// Assume the signature is at the end of the message, pass it in seperately. Check it's good.
	if (BTM_verify_signature(message, length - 256, message + offset) < BTM_success) {
		return BTM_general_exception;
	}

	// Code for dispatching DEVKEY messages would go here

	// We're going to assume it's an invitation for a DEVKEY cycle.

	// Code for limiting access to the private key goes here; this has to be a LONG timer (minutes) to be useful.

	long msg_length = length - 256;
	if (run == 0) {
		BTM_start_rotation(message, msg_length);
	}
	else {
		BTM_complete_rotation(message, msg_length);
	}
	// Do the other one next time
	run ^= 1;
}

BTM_error BTM_start_rotation(const uint8_t* message, const int length) {
	BTM_ASYMKEY priv_key;
	int exchange_length;
	BTM_load_from_NVRAM(priv_key, BTM_ASYMKEY_BYTES);

	// Check that we can decode the message
	if (BTM_asym_decrypt((uint8_t*) ((void *) &pending_exchange), &exchange_length, message, length, priv_key) < BTM_success) {
		return BTM_general_exception;
	}

	BTM_make_pubkey_from_devkey(pending_exchange.pubkey, devkey);
	BTM_get_crypto_rnd_bytes(pending_exchange.secret, BTM_SECRET_BYTES);
	BTM_compute_ecdh_exchange(pending_exchange.exchange, pending_exchange.pubkey, pending_exchange.secret);

	// Code to actually send the exchange message goes here.
	SIM_log_action(send_packet, 1, "Send Cycle Invitation Response");

	return BTM_success;
}

BTM_error BTM_complete_rotation(uint8_t *message, int length) {
	BTM_ASYMKEY priv_key;
	BTM_EXCHANGE_PARAMETERS remote_exchange;
	int exchange_length;
	BTM_load_from_NVRAM(priv_key, BTM_ASYMKEY_BYTES);

	// Check that we can decode the message
	if (BTM_asym_decrypt(&remote_exchange, &exchange_length, message, length, priv_key) < BTM_success) {
		return BTM_general_exception;
	}

	// Code to actually do the ECDH key calculation using the exchnage structure in the message goes here.
	SIM_log_action(ecdh_key_calculate, 1, "Computed ECDH Key");

	// And write it into NVRAM so we can load it on next boot.
	BTM_store_to_NVRAM(devkey, BTM_KEY_BYTES);

	return BTM_success;
}
