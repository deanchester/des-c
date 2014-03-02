#include "DES.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const *argv[]) {
	KEY key = 0;
	CIPHER_LR text = 0;
	
	CIPHER_LR returned = feistelFunction(text, key);
	
	printf("%x\n", returned);
	
}