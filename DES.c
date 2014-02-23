#include "DES.h"

int PC2[] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,
			2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,
			50,36,29,32};

int PC1[] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,
			11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,
			61,53,45,37,29,21,13,5,28,20,12,4};

int IP[] = {58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,
			6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,
			11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
			
int EXPANDED[] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,
				16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,
				30,31,32,1};

unsigned int S1[] = {14,0,4,15,13,7,1,4,2,14, 15, 2, 11, 13, 8, 1, 3, 10, 10,
		 			6, 6, 12, 12, 11, 5, 9, 9, 5, 0, 3, 7, 8, 4, 15, 1, 12, 
					14, 8, 8, 2, 13, 4, 6, 9, 2, 1, 11, 7, 15, 5, 12, 11, 9, 
					3, 7, 14, 3, 10, 10, 0, 5, 6, 0, 13};

unsigned int S2[] = {15,3,1,13,8,4,14,7,6,15, 11, 2, 3, 8, 4, 14, 9, 12, 7, 0,
		 			2, 1, 13, 10, 12, 6, 0, 9, 5, 11, 10, 5, 0, 13, 14, 8, 7, 
					10, 11, 1, 10, 3, 4, 15, 13, 4, 1, 2, 5, 11, 8, 6, 12, 7, 
					6, 12, 9, 0, 3, 5, 2, 14, 15, 9};

unsigned int S3[] = {10, 13, 0, 7, 9, 0, 14, 9, 6, 3, 3, 4, 15, 6, 5, 10, 1, 2,
		 			13, 8, 12, 5, 7, 14, 11, 12, 4, 11, 2, 15, 8, 1, 13, 1, 6,
					10, 4, 13, 9, 0, 8, 6, 15, 9, 3, 8, 0, 7, 11, 4, 1, 15, 2, 
					14, 12, 3, 4, 11, 10, 5, 14, 2, 7, 12};

unsigned int S4[] = {7, 13, 13, 8, 14, 11, 3, 5, 0, 6, 6, 15, 9, 0, 10, 3, 1, 
					4, 2, 7, 8, 2, 5, 12, 11, 1, 12, 10, 4, 14, 15, 9, 10, 3,
					6, 15, 9, 0, 0, 6, 12, 10, 11, 1, 7, 13, 13, 8, 15, 9, 1, 
					4, 3, 5, 14, 11, 5, 12, 2, 7, 8, 2, 3, 14};

unsigned int S5[] = {2, 14, 12, 11, 4, 2, 1, 12, 7, 4, 10, 7, 11, 13, 6, 1, 8,
		 			5, 5, 0, 3, 15, 15, 10, 13, 3, 0, 9, 14, 8, 9, 6, 4, 11,
					2, 8, 1, 12, 11, 7, 10, 1, 13, 14, 7, 2, 8, 13, 15, 6, 9,
					15, 12, 0, 5, 9, 6, 10, 3, 4, 0, 5, 14, 3};

unsigned int S6[] = {12, 10, 1, 15, 10, 4, 15, 2, 9, 7, 2, 12, 6, 9, 8, 5, 0,
					6, 13, 1, 3, 13, 4, 14, 14, 0, 7, 11, 5, 3, 11, 8, 9, 4, 
					14, 3, 15, 2, 5, 12, 2, 9, 8, 5, 12, 15, 3, 10, 7, 11, 0,
					14, 4, 1, 10, 7, 1, 6, 13, 0, 11, 8, 6, 13};

unsigned int S7[] = {4, 13, 11, 0, 2, 11, 14, 7, 15, 4, 0, 9, 8, 1, 13, 10, 3,
					14, 12, 3, 9, 5, 7, 12, 5, 2, 10, 15, 6, 8, 1, 6, 1, 6, 4,
					11, 11, 13, 13, 8, 12, 1, 3, 4, 7, 10, 14, 7, 10, 9, 15,
					5, 6, 0, 8, 15, 0, 14, 5, 2, 9, 3, 2, 12};

unsigned int S8[] = {13, 1, 2, 15, 8, 13, 4, 8, 6, 10, 15, 3, 11, 7, 1, 4, 10,
					12, 9, 5, 3, 6, 14, 11, 5, 0, 0, 14, 12, 9, 7, 2, 7, 2, 11,
					1, 4, 14, 1, 7, 9, 4, 12, 10, 14, 8, 2, 13, 0, 15, 6, 12,
					10, 9, 13, 0, 15, 3, 3, 5, 5, 6, 8, 11};

int FEISTEL_PERMUTED[] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18,
						31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22,
						11, 4, 25};

int IIP[] = {40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,
			62,30,37,5,45,13,53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,
			19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};

inline KEY_LR shiftKey(KEY_LR key){
	return ((key << 1) | (((key >> sizeof(key) * 8) - 1)));
}

/*
	Run the key scheduling algorithm 
*/
void scheduleKeys(KEY key, KEY *keysP){
	int i;
	KEY keyPC1 = 0;
	
	for(i = 1; i<65; i++){
		KEY tmpKeyMasked = ((65 - i) & key);
		tmpKeyMasked << PC1[i];
		keyPC1 += tmpKeyMasked;
	}	
	
	KEY_LR key_left = ((keyPC1 & 0xFFFFFFFF00000000) >> 32);
	KEY_LR key_right = (keyPC1 & 0x00000000FFFFFFFF);

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
		
		keysP[i] = keyPC2;
	}
}

CIPHER_TEXT encrypt(PLAIN_TEXT plain, KEY key){
    KEY keys[16];
	KEY *keysP;
	keysP = &keys[0];
	scheduleKeys(key, keysP);
	
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
		CIPHER_LR returned = feistelFunction(cipher_right, 	keysP[i]);
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

CIPHER_TEXT decrypt(PLAIN_TEXT plain, KEY key){
    KEY keys[16];
	KEY *keysP;
	keysP = &keys[0];
	scheduleKeys(key, keysP);
	
	int i;
	CIPHER_TEXT permuted = 0; 
	
	for(i = 1; i<65; i++){
		CIPHER_TEXT tmpPermuted = ((65 - i) & plain);
		tmpPermuted << IP[i];
		permuted += tmpPermuted;
	}
	
	CIPHER_LR cipher_left = ((permuted & 0xFFFFFFFF00000000) >> 32);
	CIPHER_LR cipher_right = (permuted & 0x00000000FFFFFFFF);
	
	for(i = 15; i>=; i--){
		CIPHER_LR returned = feistelFunction(cipher_right, 	keysP[i]);
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

CIPHER_LR feistelFunction(CIPHER_LR right, KEY subkey){
	CIPHER_EXPANDED expanded = 0; 
	int i; 
	for(i = 1; i<33; i++){
		CIPHER_LR tmpExpanded = ((33 - i) & right);
		tmpExpanded << EXPANDED[i];
		expanded += tmpExpanded;
	}
	
	expanded ^= subkey;
	
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
	
	CIPHER_LR sBoxesRecombined = (s1<<28) + (s2 << 24) + (s3 << 20) + (s4 << 16) + (s5 << 12) + (s6 << 8) + (s7 << 4) + s8;
	CIPHER_LR returnVal = 0;
	for(i = 1; i<33; i++){
		CIPHER_LR tmpPermuted = ((33 - i) & sBoxesRecombined);
		tmpPermuted << FEISTEL_PERMUTED[i];
		returnVal += tmpPermuted;
	}
	
	return returnVal;
}