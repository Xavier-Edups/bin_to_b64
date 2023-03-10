#include "stdio.h"
#include "string.h"

#define PAD_MARKER '\0'

void pad_b64 (char * byte);
char *nasm_encode (char *bytes);

int main (int argc, char** argv) {
    /* Verifica se número de argumentos está correto */
    if (argc < 2 || argc > 3) {
        printf("Invalid number of arguments.\nUsage: bin_to_b64 <file> [--decode]\n");
        return 1;
    }

    if (argc == 3) {
        if (strcmp("--decode", argv[2])) {
            printf("Flag \"%s\" doesn't exist.\nUsage: bin_to_b64 <file> [--decode]\n", argv[2]);
            return 2;
        }
    }

    /* Abre arquivo */
    FILE *fp;
    fp = fopen(argv[1], "r");

    if (!fp) {
        printf("Error: Cannot open file \"%s\".\n", argv[1]);
        return 3;
    }

    /* REMOVE debbug only */
    char* foo = nasm_encode("asddd");
    pad_b64(foo);
    printf("%s\n", foo);

    if (argc == 2) { /* Encode no arquivo binário */
        /* Le arquivo de 3 em 3 bytes */
        char bytes[3];
        while (!feof(fp)) {
            /* TODO */

        }
    } else { /* Decode de arquivo em base64 */
        /* TODO */
    }

    /* Fecha arquivo */
    fclose(fp);

    return 0;
}

/* Adiciona '=' para completar byte */
void pad_b64 (char *encoded) {
    int i;
    for (i=0; i<4; i++) {
        if (encoded[i] == PAD_MARKER) {
            encoded[i] = '=';
        }
    }

    return;
}

/* Executa encode em uma rotina de NASM */
char *nasm_encode (char *bytes) {
    static char encoded_bytes[4];

    /* TODO */

    /* REMOVE debugg only */
    printf("%s\n", bytes);
    encoded_bytes[0] = 'A';
    encoded_bytes[1] = 'B';
    encoded_bytes[2] = PAD_MARKER;
    encoded_bytes[3] = PAD_MARKER;

    return encoded_bytes;
}
