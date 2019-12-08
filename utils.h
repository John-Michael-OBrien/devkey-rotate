#pragma once
#include "inttypes.h"

enum BTM_errors_enum {
	BTM_general_exception=-1,
	BTM_success=0
};
typedef enum BTM_errors_enum BTM_error;

#define BTM_KEY_BYTES 16
#define BTM_PUBKEY_BYTES 64
#define BTM_SECRET_BYTES 32
#define BTM_EXCHANGE_BYTES 32
#define BTM_ASYMKEY_BYTES 256
#define BTM_SIG_BYTES 256

typedef uint8_t* BTM_KEY[BTM_KEY_BYTES];
typedef BTM_KEY* BTM_KEY_p;

// This is preliminary.
typedef uint8_t BTM_PUBKEY[BTM_PUBKEY_BYTES];
typedef BTM_PUBKEY* BTM_PUBKEY_p;

typedef uint8_t BTM_ECDHSECRET[BTM_SECRET_BYTES];
typedef BTM_ECDHSECRET* BTM_ECDHSECRET_p;

typedef uint8_t BTM_ECDH_EXHCANGE[BTM_EXCHANGE_BYTES];
typedef BTM_ECDH_EXHCANGE* BTM_ECDH_EXHCANGE_p;

struct BTM_EXCHANGE_PARAMETERS_STRUCT {
	BTM_ECDHSECRET secret;
	BTM_PUBKEY pubkey;
	BTM_ECDH_EXHCANGE exchange;
};
typedef struct BTM_EXCHANGE_PARAMETERS_STRUCT BTM_EXCHANGE_PARAMETERS;
typedef BTM_EXCHANGE_PARAMETERS* BTM_EXCHANGE_PARAMETERS_p;


typedef uint8_t BTM_ASYMKEY[BTM_ASYMKEY_BYTES];
typedef BTM_ASYMKEY* BTM_ASYMKEY_p;

typedef uint8_t BTM_SIGNATURE[BTM_SIG_BYTES];
typedef BTM_SIGNATURE* BTM_SIGNATURE_p;


BTM_error BTM_get_crypto_rnd_bytes(const uint8_t* buffer, const int count);
BTM_error BTM_compute_ecdh_exchange(const BTM_ECDH_EXHCANGE_p destination, const BTM_PUBKEY pubkey, const BTM_ECDHSECRET secret);
BTM_error BTM_make_pubkey_from_devkey(const BTM_PUBKEY destination, const BTM_KEY devkey);
BTM_error BTM_start_rotation(uint8_t* message, int length);
BTM_error BTM_complete_rotation(uint8_t* message, int length);
BTM_error BTM_process_message(const uint8_t* message, const int length);