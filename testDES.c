#include "DES.h"
#include <stdio.h>

int main (int argc, char const *argv[])
{
	KEY key = 0; 
	PLAIN_TEXT pt = 0; 
	
	CIPHER_TEXT ct = encrypt(pt, key);
	
	printf("Ciphered Value is: %llu\n", ct);
	
	return 0;
}