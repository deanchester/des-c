#include "DES.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char const *argv[])
{
	KEY key = 0x01;
	
	KEY_LR left = 0x01;
	KEY *keys = malloc(16*sizeof(KEY));
	scheduleKeys(key, keys);
	int i;
	for(i = 0; i<16; i++){
		printf("Key %d: %llx\n", i, keys[i]);
	}
	
	return 0;
}