#ifndef SYMCRYPT_LIB_H_
#define SYMCRYPT_LIB_H_

/*Returns an encryption calculated from give message and a shared secret */
/* it calculates an encryption of only one character at a time */
char encrypt_char(char m, char s);

/*Returns a decryption of a given message from user and a shared secrete */
/*This also decryptes only one character at a time*/
char decrypt_char(char m, char s);

/*Encryptes  a given string of characters of a message and a shared secret
 * entered by user
 * */
void encrypt(char *message, char *secret, char *encrypted);

/*Encryptes  a given string of characters of a message and a shared secret
 * entered by user
 * */
void decrypt(char *message, char *secret, char *decrypted);

#endif /* SYMCRYPT_LIB_H_*/
