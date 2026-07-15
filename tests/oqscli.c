/* OQS-CLI
 *
 * Command-line program to run cryptographic primitives
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "oqs.h"

#define OQSCLI_DEBUGGING 1

#define HELPTEXT_STR "Usage: %s [--version] [--verbose] <algname> <op> <args>\n"

enum OQSCLI_ErrorCodes {
    OQSCLI_OK = 0,
    /* General, non-specific error */
    OQSCLI_ERROR_E = -1,
};

enum OQSCLI_Encoding {
    OQSCLI_BIN,
    OQSCLI_HEX,
    OQSCLI_BASE64,
};

enum OQSCLI_AlgType {
    OQSCLI_Kem,
    OQSCLI_Sig,
};

// NOTE: CryptoOp needs to be in sync with SubcommandArgs
enum CryptoOp {
    /* No operation */
    NOPE = 0,
    KEM_KEYPAIR,
    KEM_ENC,
    KEM_DEC,
    SIG_KEYPAIR,
    SIG_SIGN,
    SIG_VERIFY,
};

struct KemKeypairArgs {
    const uint8_t *seed;
    size_t seedlen;
    FILE *pubkey_f;
    FILE *privkey_f;
};

struct KemEncArgs {
    const uint8_t *seed;
    size_t seedlen;
    FILE *pubkey_f;
    FILE *ciphertext_f;
    FILE *secret_f;
};

struct KemDecArgs {
    FILE *pubkey_f;
    FILE *ciphertext_f;
    FILE *secret_f;
};

struct SigKeypairArgs {
    const uint8_t *seed;
    size_t seedlen;
    FILE *pubkey_f;
    FILE *privkey_f;
};

struct SigSignArgs {};

struct SigVerifyArgs {};

union SubcommandArgs {
    struct KemKeypairArgs kemkeypairargs;
    struct KemEncArgs kemencargs;
    struct KemDecArgs kemdecargs;
    struct SigKeypairArgs sigkeypairargs;
    struct SigSignArgs sigsignargs;
    struct SigVerifyArgs sigverifyargs;
};

struct CliArgs {
    int version;
    int verbose;

    // Defaults to raw bytes. Use --base64 to encode bytes with base64, --hex
    // to encode with hexadecimal.
    enum OQSCLI_Encoding g_enc;

    // Name of the crypto algorithm
    const char *algname;
    enum OQSCLI_AlgType algtype;
    enum CryptoOp op;
    union SubcommandArgs subargs;
};

void cliargs_init(struct CliArgs *args) {
    if (!args) {
        return;
    }
    args->version = 0;
    args->verbose = 0;
    args->g_enc = OQSCLI_BIN;
    args->algname = NULL;
    args->op = NOPE;
    // TODO: how should I initialize args->args
}

int parse_alg_name_type(const char *name, enum OQSCLI_AlgType *algtype) {
    // NOTE: name came from argv, it is safe to assume proper name termination
    if (strcmp(name, OQS_KEM_alg_ml_kem_768) == 0) {
        *algtype = OQSCLI_Kem;
        return OQSCLI_OK;
    }
    // FIX: support other algorithms, too
    return OQSCLI_ERROR_E;
}

int cliargs_parse_subargs(struct CliArgs *args, int argc, const char *argv[]) {
    const char *arg = NULL;
    int rc;
#if OQSCLI_DEBUGGING
    printf("Remaining args: [");
    for (int argi = 0; argi < argc; argi++) {
        arg = argv[argi];
        printf("%s", arg);
        if (argi + 1 < argc) {
            printf(", ");
        }
    }
    printf("]\n");
#endif

    if ((rc = parse_alg_name_type(arg, &args->algtype)) < 0) {
        fprintf(stderr, "%s is not valid algorithm name\n", arg);
        return rc;
    }
    args->algname = arg;
    // FIX: need to parse op and op args

    return OQSCLI_OK;
}

int cliargs_parse_args(struct CliArgs *args, int argc, const char *argv[]) {
    const char *arg = NULL;
    int rc = OQSCLI_ERROR_E;
    enum OQSCLI_AlgType algtype;

    for (int argi = 1; argi < argc; argi++) {
        arg = argv[argi];

        if (strcmp(arg, "--version") == 0) {
            args->version = 1;
            return OQSCLI_OK;
        }
        if (strcmp(arg, "--verbose") == 0) {
            args->verbose = 1;
            continue;
        }
        if (strcmp(arg, "--hex") == 0) {
            args->g_enc = OQSCLI_HEX;
            continue;
        }
        if (strcmp(arg, "--base64") == 0) {
            args->g_enc = OQSCLI_BASE64;
            continue;
        }
        if (arg[0] == '-') {
            fprintf(stderr, "Invalid flag %s\n", arg);
            return OQSCLI_ERROR_E;
        }
        if ((rc = cliargs_parse_subargs(args, argc - argi, argv + argi)) < 0) {
            return rc;
        }
    }

    return OQSCLI_OK;
}

int main(int argc, const char *argv[]) {
    int rc = 0;
    struct CliArgs cliargs;
    cliargs_init(&cliargs);

    if ((rc = cliargs_parse_args(&cliargs, argc, argv)) < 0) {
        fprintf(stderr, HELPTEXT_STR, argv[0]);
        return 1;
    }

    return 0;
}
