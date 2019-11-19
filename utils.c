#include "inttypes.h"

typedef int BTM_error_t;
#define BTM_success 0

union BTM_KEY_t {
	uint8_t key_bytes[16];
	uint64_t key_qwords[2];
 };

typedef uint8_t* BTM_KEY_p;

typedef union BTM_KEY_t BTM_PUBKEY_t;
typedef BTM_PUBKEY_t* BTM_PUBKEY_p;

BTM_error_t BTM_get_crypto_rnd_bytes(uint8_t* buffer, int count) {
	return BTM_success;
}

BTM_error_t BTM_compute_key(BTM_KEY_p destination, BTM_PUBKEY_p pubkey, BTM_KEY_p secret) {
	return BTM_success;
}

