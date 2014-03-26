#include "DES.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const *argv[])
{
	KEY key = (KEY)0x133457799BBCDFF1; 
	PLAIN_TEXT pt = (PLAIN_TEXT)0x0123456789ABCDEF; 
	
	CIPHER_TEXT ct = encrypt(pt, key);
	PLAIN_TEXT p = decrypt(ct, key);
	printf("Plain Value is: %llx\n", p);
	
	return 0;
}