#include "DES.h"

KEY keys[] = KEY[16];

inline KEY_LR shiftKey(KEY_LR key){
	return (key << 1) | (key >> sizeof(key) * 8 - 1);
}

void scheduleKeys(KEY key){
	/*
		Run 
	*/
	int i;
	KEY keyPC1 = 0;
	
	for(i = 1; i<65; i++){
		KEY tmpKeyMasked = ((64 - i) & key);
		tmpKeyMasked << PC1[i];
		keyPC1 += tmpKeyMasked;
	}
	
	KEY_LR key_left = ((newKeyPC1 & 0xFFFFFFFF00000000) >> 32);
	KEY_LR key_right = (newKeyPC1 & 0x00000000FFFFFFFF);

	for(i = 0; i<16; i++){
		if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 9 || 
			i == 10 || i == 11 || i == 12 || i == 13 || i == 14) {
			key_left = shiftKey(key_left);
			key_right = shiftKey(key_right);
		}
		
		key_left = shiftKey(key_left);
		key_right = shiftKey(key_right);
		
		KEY keyReformed = key_left << 32 & key_right; 
		KEY keyPC2 = 0;
		
		for(i = 1; i<65; i++){
			KEY tmpKeyMasked = ((64 - i) & keyReformed);
			tmpKeyMasked << PC2[i];
			keyPC2 += tmpKeyMasked;
		}
		
		keys[i] = keyPC2;
	}
}
