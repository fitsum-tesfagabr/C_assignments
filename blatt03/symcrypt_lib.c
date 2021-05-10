#include "./symcrypt_lib.h"
#include "stdio.h"
#include "string.h"

char encrypt_char(char m, char s) {

  int e = m + s - 64;
  if (e >= 95) {
    e -= 95;
  }
  e += 32;
  return e;
}

char decrypt_char(char m, char s) {
  int d;
  d = m - s;
  if (d < 0) {
    d += 95;
  }
  d += 32;
  return d;
}

void encrypt(char *message, char *secret, char *encrypted) {

  // considenring message is longer than secret
  /* given */
  int secret_counter = 0;
  for (int i = 0; i < strlen(message); i++) {
    *(encrypted++) = encrypt_char(message[i], secret[secret_counter]);
    secret_counter++;
    if (secret_counter == strlen(secret)) {
      secret_counter = 0;
    }
  }
  *(encrypted++) = 0;
}
void decrypt(char *message, char *secret, char *decrypted) {
  // considenring message is longer than secret
  /* given */
  int secret_counter = 0;
  for (int i = 0; i < strlen(message); i++) {
    *(decrypted++) = decrypt_char(message[i], secret[secret_counter]);
    secret_counter++;
    if (secret_counter == strlen(secret)) {
      secret_counter = 0;
    }
  }

  *(decrypted++) = 0;
}
