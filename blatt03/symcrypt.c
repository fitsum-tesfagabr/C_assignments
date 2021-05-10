#include "./symcrypt_lib.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char encrypted[5000], decrypted[5000];
  char *key;
  if (argc > 1) {

    key = argv[1];
  }

  if (argc > 1 && strcmp(argv[1], "encrypt") == 0) {
    encrypt(argv[3], argv[2], encrypted);
    printf("'%s'\n", encrypted);
  } else if (argc > 1 && strcmp(key, "decrypt") == 0) {
    decrypt(argv[3], argv[2], decrypted);
    printf("'%s'\n", decrypted);
  } else {
    printf("USAGE\n");
    printf("  sysmcrpt [encrypt|decrypt] SECRET MESSAGE\n\n");
    printf("  Encrypts of decrypts a MESSAGE using a shared SECRET.\n\n");
  }
}
