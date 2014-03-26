#include "DES.h"

unsigned int PC2[] = {32, 29, 36, 50, 42, 46, 53, 34, 56, 39, 49, 44, 48, 33, 
					45, 51, 40, 30, 55, 47, 37, 31, 52, 41, 2, 13, 20, 27, 7, 
					16, 8, 26, 4, 12, 19, 23, 10, 21, 6, 15, 28, 3, 5, 1, 24, 
					11, 17, 14};

unsigned int PC1[] = {4, 12, 20, 28, 5, 13, 21, 29, 37, 45, 53, 61, 6, 14, 22, 
					30, 38, 46, 54, 62, 7, 15, 23, 31, 39, 47, 55, 63, 36, 44, 
					52, 60, 3, 11, 19, 27, 35, 43, 51, 59, 2, 10, 18, 26, 34, 
					42, 50, 58, 1, 9, 17, 25, 33, 41, 49, 57};

int IP[] = {7, 15, 23, 31, 39, 47, 55, 63, 5, 13, 21, 29, 37, 45, 53, 61, 3, 11, 19, 27, 35, 43, 51, 59, 1, 9, 17, 25, 33, 41, 49, 57, 8, 16, 24, 32, 40, 48, 56, 64, 6, 14, 22, 30, 38, 46, 54, 62, 4, 12, 20, 28, 36, 44, 52, 60, 2, 10, 18, 26, 34, 42, 50, 58};
			
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

KEY_LR shiftKey(KEY_LR key){
	KEY_LR lsbs = key & 0x7FFFFFF;
	lsbs <<= 1;
	KEY_LR MSB = key & 0x8000000;
	MSB >>= 27;
	return lsbs | MSB;
}

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = b[i] & (1<<j);
            byte >>= j;
            printf("%u", byte);
        }
    }
    puts("");
}

/*
	Run the key scheduling algorithm 
*/
void scheduleKeys(KEY key, KEY *keysP){
	int i, k =0;
	KEY keyPC1 = 0;
		
	KEY value = 1;
	
	for(i = 0; i<56; i++){
		value = (KEY)((KEY)1 << (KEY)(64-PC1[i]));
		if(key & value){
			KEY tmp = (KEY)1 << (KEY)i;
			keyPC1 |= tmp;
		}
		value = 0;
	}
	
	KEY_LR key_left = ((keyPC1 & 0xFFFFFFFFF0000000) >> 28);
	KEY_LR key_right = (keyPC1 & 0x000000000FFFFFFF);
	for(i = 0; i<16; i++){
		if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 9 || 
			i == 10 || i == 11 || i == 12 || i == 13 || i == 14) {
			key_left = shiftKey(key_left);
			key_right = shiftKey(key_right);
		}
		
		key_left = shiftKey(key_left);
		key_right = shiftKey(key_right);

		KEY newLeft = (KEY)((KEY)key_left << (KEY)28);
		KEY keyReformed = (KEY)(newLeft | (KEY)key_right); 
		KEY keyPC2 = 0;
		int j = 0; 
		value = 0;
		for(j = 0; j<56; j++){
			value = (KEY)((KEY)1 << (KEY)(56-PC2[j]));
			if(keyReformed & value){
				KEY tmp = (KEY)1 << (KEY)j;
				keyPC2 |= tmp;
			}
			value = 0;
		}
		keyPC2 &= 0xFFFFFFFFFFFF;
		keysP[i] = keyPC2;
	}
}

CIPHER_TEXT encrypt(PLAIN_TEXT plain, KEY key){
	KEY *keys = malloc(16*sizeof(KEY));
	scheduleKeys(key, keys);
	int i;
	CIPHER_TEXT permuted = 0; 
	CIPHER_TEXT value = 1;
	for(i = 0; i<64; i++){
		CIPHER_TEXT tmpPermuted = (CIPHER_TEXT)((CIPHER_TEXT)1 << (CIPHER_TEXT)(64-IP[i]));
		if(tmpPermuted & plain){
			CIPHER_TEXT cTMP = (CIPHER_TEXT)1<<(CIPHER_TEXT)i;
			permuted |= cTMP;
		}
	}
	CIPHER_LR cipher_left = ((permuted & (KEY)0xFFFFFFFF00000000) >> 32);
	CIPHER_LR cipher_right = (permuted & (KEY)0x00000000FFFFFFFF);
	printBits(sizeof(cipher_right), &cipher_left);
	printBits(sizeof(cipher_right), &cipher_right);
	for(i = 0; i<16; i++){
		CIPHER_LR returned = feistelFunction(cipher_right, keys[i]);
		CIPHER_LR cipher_tmp = cipher_right;
		cipher_right = cipher_left ^ returned;
		cipher_left = cipher_tmp;
	}
	
	permuted = (cipher_left << 32) + cipher_right; 
	CIPHER_TEXT ciphered = 0; 
	value = 1;
	for(i = 0; i<64; i++){
		CIPHER_TEXT tmpPermuted = (value & permuted);
		tmpPermuted <<= IIP[i];
		value *= 2;
		ciphered += tmpPermuted;
	}
	
	free(keys);
	
	return ciphered;
}

PLAIN_TEXT decrypt(CIPHER_TEXT plain, KEY key){
	KEY *keys = malloc(16*sizeof(KEY));
	scheduleKeys(key, keys);
	
	int i;
	CIPHER_TEXT permuted = 0; 
	
	KEY value = 1;
	for(i = 0; i<64; i++){
		CIPHER_TEXT tmpPermuted = (value & plain);
		tmpPermuted <<= IP[i];
		value *= 2;
		permuted += tmpPermuted;
	}
	
	CIPHER_LR cipher_left = ((permuted & 0xFFFFFFFF00000000) >> 32);
	CIPHER_LR cipher_right = (permuted & 0x00000000FFFFFFFF);
	
	for(i = 15; i>=0; i--){
		CIPHER_LR returned = feistelFunction(cipher_right, keys[i]);
		CIPHER_LR cipher_tmp = cipher_right;
		cipher_right = cipher_left ^ returned;
		cipher_left = cipher_tmp;
	}
	
	permuted = (cipher_left << 32) + cipher_right; 
	CIPHER_TEXT ciphered = 0; 
	value = 1;
	for(i = 0; i<64; i++){
		CIPHER_TEXT tmpPermuted = (value & permuted);
		tmpPermuted <<= IIP[i];
		value *= 2;
		ciphered += tmpPermuted;
	}
	
	free(keys);
	
	return ciphered;
}

CIPHER_LR feistelFunction(CIPHER_LR right, KEY subkey){
	CIPHER_EXPANDED expanded = 0; 
	int i; 
	CIPHER_LR value1 = 1;
	for(i = 1; i<33; i++){
		CIPHER_LR tmpExpanded = (value1 & right);
		tmpExpanded <<= EXPANDED[i];
		expanded += tmpExpanded;
		value1 *= 2;
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
	
	unsigned int s1 = S1[e8];
	unsigned int s2 = S2[e7];
	unsigned int s3 = S3[e6];
	unsigned int s4 = S4[e5];
	unsigned int s5 = S5[e4];
	unsigned int s6 = S6[e3];
	unsigned int s7 = S7[e2];
	unsigned int s8 = S8[e1];
	
	CIPHER_LR sBoxesRecombined = (CIPHER_LR)(s1<<28) | (CIPHER_LR)(s2 << 24) | 
		(CIPHER_LR)(s3 << 20) | (CIPHER_LR)(s4 << 16) | (CIPHER_LR)(s5 << 12) | 
		(CIPHER_LR)(s6 << 8) | (CIPHER_LR) (s7 << 4) | (CIPHER_LR) (s8);
	
	CIPHER_LR returnVal = 0;
	KEY_LR value = 1;
	for(i = 0; i<32; i++){
		CIPHER_LR tmpPermuted = (value & sBoxesRecombined);
		if(tmpPermuted == value){
			returnVal += (1<<(FEISTEL_PERMUTED[i]-1));
		}
		value *= 2;
	}
	
	return returnVal;
}