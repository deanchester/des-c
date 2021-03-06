#include <stdlib.h>
#include <stdio.h>
typedef unsigned long long int KEY;
typedef unsigned int KEY_LR;
typedef unsigned long long int PLAIN_TEXT;
typedef unsigned long long int CIPHER_TEXT;
typedef unsigned int CIPHER_LR;
typedef unsigned long long int CIPHER_EXPANDED;

KEY_LR shiftKey(KEY_LR key);

void scheduleKeys(KEY key, KEY *keysP);

CIPHER_TEXT encrypt(PLAIN_TEXT plain, KEY key);

PLAIN_TEXT decrypt(CIPHER_TEXT plain, KEY key);

CIPHER_LR feistelFunction(CIPHER_LR right, KEY subkey);

void printBits(size_t const size, void const * const ptr);