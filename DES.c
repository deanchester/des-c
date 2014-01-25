#include "DES.h"

KEY keys[] = KEY[16];

inline KEY_LR shiftKey(KEY_LR key){
	return (key << 1) | (key >> sizeof(key) * 8 - 1);
}

/*
	Run the key scheduling algorithm 
*/
void scheduleKeys(KEY key){
	int i;
	KEY keyPC1 = 0;
	
	for(i = 1; i<65; i++){
		KEY tmpKeyMasked = ((65 - i) & key);
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
			KEY tmpKeyMasked = ((65 - i) & keyReformed);
			tmpKeyMasked << PC2[i];
			keyPC2 += tmpKeyMasked;
		}
		
		keys[i] = keyPC2;
	}
}

CIPHER_TEXT encrypt(PLAIN_TEXT plain, KEY key){
	scheduleKeys(key);
	
	int i;
	CIPHER_TEXT permuted = 0; 
	
	for(i = 1; i<65; i++){
		CIPHER_TEXT tmpPermuted = ((65 - i) & plain);
		tmpPermuted << IP[i];
		permuted += tmpPermuted;
	}
	
	CIPHER_LR cipher_left = ((permuted & 0xFFFFFFFF00000000) >> 32);
	CIPHER_LR cipher_right = (permuted & 0x00000000FFFFFFFF);
	
	for(i = 0; i<16; i++){
		CIPHER_LR returned = feistelFunction(cipher_right, i);
		CIPHER_LR cipher_tmp = cipher_right;
		cipher_right = cipher_left ^ returned;
		cipher_left = cipher_tmp;
	}
	
	permuted = (cipher_left << 32) + cipher_right; 
	CIPHER_TEXT ciphered = 0; 
	for(i = 1; i<65; i++){
		CIPHER_TEXT tmpPermuted = ((65 - i) & permuted);
		tmpPermuted << IIP[i];
		ciphered += tmpPermuted;
	}
	
	return ciphered;
}

CIPHER_LR feistelFunction(CIPHER_LR right, int round){
	CIPHER_EXPANDED expanded = 0; 
	
	for(i = 1; i<33; i++){
		CIPHER_LR tmpExpanded = ((33 - i) & plain);
		tmpExpanded << EXPANDED[i];
		expanded += tmpExpanded;
	}
	
	expanded ^= keys[round];
	
	unsigned char e8 = ((expanded & 0x3F));
	unsigned char e7 = ((expanded & 0x3F60) >> 6);
	unsigned char e6 = ((expanded & 0x3F6000) >> 12);
	unsigned char e5 = ((expanded & 0x3F600000) >> 18);
	unsigned char e4 = ((expanded & 0x3F60000000) >> 24);
	unsigned char e3 = ((expanded & 0x3F6000000000) >> 30);
	unsigned char e2 = ((expanded & 0x3F600000000000)  >> 36);
	unsigned char e1 = ((expanded & 0x3F60000000000000) >> 42);
	
	unsigned int s1 = S1[e1];
	unsigned int s2 = S2[e2];
	unsigned int s3 = S3[e3];
	unsigned int s4 = S4[e4];
	unsigned int s5 = S5[e5];
	unsigned int s6 = S6[e6];
	unsigned int s7 = S7[e7];
	unsigned int s8 = S8[e8];
	
	CIPHER_LR sBoxesRecombined = (s1<<28) + (s2 << 24) + (s3 << 20) + (s4 << 16) + (s5 << 12) + (s6 << 8) + (s7 << 4) + s2;
	CIPHER_LR returnVal = 0;
	for(i = 1; i<33; i++){
		CIPHER_LR tmpPermuted = ((33 - i) & sBoxesRecombined);
		tmpPermuted << FEISTEL_PERMUTED[i];
		returnVal += tmpPermuted;
	}
	
	return returnVal;
}