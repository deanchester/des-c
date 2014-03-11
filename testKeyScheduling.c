#include "DES.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char const *argv[])
{
	KEY key = 0x133457799BBCDFF1;
	
	KEY *keys = malloc(16*sizeof(KEY));
	scheduleKeys(key, keys);
	int i;
	
	KEY keysCheck[16] = {
		(KEY)29699430183026,
		(KEY)133791886330341, 
		(KEY)94543139753881, 
		(KEY)126090959598877, 
		(KEY)137353186988968, 
		(KEY)109561366215471, 
		(KEY)260054766196924, 
		(KEY)272173063289851, 
		(KEY)247235160696705,  
		(KEY)195658438559311,  
		(KEY)36695460205446,  
		(KEY)129132311898089,  
		(KEY)166875887221313, 
		(KEY)104744453596986,  
		(KEY)210631860764426,  
		(KEY)223465186400245
	};
	
	for(i =0; i<16; i++){
		if(keys[i] == keysCheck[i]){
			printf("Key at %d is the correct.\n", i);
		} else {
			printf("Key at %d is the incorrect.\n", i);
		}
	}
	
	return 0;
}
