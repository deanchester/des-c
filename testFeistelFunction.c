#include "DES.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char const *argv[]) {
	KEY key = 0x1B02EFFC7072;
	CIPHER_LR text = 0xF0AAF0AA;
	
	CIPHER_LR returned = feistelFunction(text, key);
	
	printBits(sizeof(returned), &returned);
	
}