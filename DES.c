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
			
int EXPANDED[] = {1, 32, 31, 30, 29, 28, 29, 28, 27, 26, 25, 24, 25, 24, 23, 22, 21, 20, 21, 20, 19, 18, 17, 16, 17, 16, 15, 14, 13, 12, 13, 12, 11, 10, 9, 8, 9, 8, 7, 6, 5, 4, 5, 4, 3, 2, 1, 32};

int S1[] = {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
			 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
			 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
			15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

int S2[] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
			 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
			 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
			13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

int S3[] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
			13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
			13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
			 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

int S4[] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
			13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
			10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
			 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

int S5[] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
			14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
			 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
			11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

int S6[] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
			10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
			 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
			 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

int S7[] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
			13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
			 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
			 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

int S8[] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
			 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
			 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
			 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

int FEISTEL_PERMUTED[] = {25, 4, 11, 22, 6, 30, 13, 19, 9, 3, 27, 32, 14, 24, 8, 2, 10, 31, 18, 5, 26, 23, 15, 1, 17, 28, 12, 29, 21, 20, 7, 16};

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

	for(i = 0; i<48; i++){
		CIPHER_EXPANDED value = (CIPHER_EXPANDED)((CIPHER_EXPANDED)1 << (CIPHER_EXPANDED)(32-EXPANDED[i]));
		if(value & right){
			expanded |= (CIPHER_EXPANDED)1 << (CIPHER_EXPANDED)i;
		}
	}
	
	expanded ^= subkey;
	
	unsigned char e8 = ((expanded & 0x3F)) & 0x3F;
	unsigned char e7 = ((expanded & 0xFC0) >> 6) & 0x3F;
	unsigned char e6 = ((expanded & 0x3F000) >> 12) & 0x3F;
	unsigned char e5 = ((expanded & 0xFC0000) >> 18) & 0x3F;
	unsigned char e4 = ((expanded & 0x3F000000) >> 24) & 0x3F;
	unsigned char e3 = ((expanded & 0xFC0000000) >> 30) & 0x3F;
	unsigned char e2 = ((expanded & 0x3F000000000)  >> 36) & 0x3F;
	unsigned char e1 = ((expanded & 0xFC0000000000) >> 42) & 0x3F;	

	unsigned char s1Col = (e1 & (unsigned char)0x1E)>> (unsigned char)1;
	unsigned char s1Row = (e1 & (unsigned char)0x20) >> (unsigned char)4| (e1 & (unsigned char)0x01);
	s1Row *= 16;
	
	unsigned char s2Col = (e2 & (unsigned char)0x1E)>> (unsigned char)1;
	unsigned char s2Row = ((e2 & (unsigned char)0x20) >> (unsigned char)5 | (e2 & (unsigned char)0x01));
	s2Row *= 16;
	printBits(sizeof(s2Col), &s2Col);
	printBits(sizeof(s2Row), &s2Row);
	unsigned char s3Col = (e3 & (unsigned char)0x1E)>> (unsigned char)1;
	unsigned char s3Row = ((e3 & (unsigned char)0x20) >> (unsigned char)4 | (e3 & (unsigned char)0x01));
	s3Row *= 16;
	
	unsigned char s4Col = (e4 & (unsigned char)0x1E)>> (unsigned char)1;
	unsigned char s4Row = ((e4 & (unsigned char)0x20) >> (unsigned char)4 | (e4 & (unsigned char)0x01));
	s4Row *= 16;
	                                                          
	unsigned char s5Col = (e5 & (unsigned char)0x1E)>> (unsigned char)1;                          
	unsigned char s5Row = ((e5 & (unsigned char)0x20) >> (unsigned char)4 | (e5 & (unsigned char)0x01));
	s5Row *= 16;
	                                                          
	unsigned char s6Col = (e6 & (unsigned char)0x1E)>> (unsigned char)1;                          
	unsigned char s6Row = ((e6 & (unsigned char)0x20) >> (unsigned char)4 | (e6 & 0x01));
	s6Row *= 16;
	                                                          
	unsigned char s7Col = (e7 & (unsigned char)0x1E)>> (unsigned char)1;                          
	unsigned char s7Row = ((e7 & (unsigned char)0x20) >> (unsigned char)4 | (e7 & 0x01));
	s7Row *= 16;
	                                                           
	unsigned char s8Col = (e8 & (unsigned char)0x1E)>> (unsigned char)1;                           
	unsigned char s8Row = ((e8 & (unsigned char)0x20) >>(unsigned char)4 | (e8 & 0x01));
	s8Row *= 16;
	
	printf("1: %d\n", (s1Col + s1Row));
	printf("2: %d\n", (s2Col + s2Row));	
	printf("3: %d\n", (s3Col + s3Row));
	printf("4: %d\n", (s4Col + s4Row));
	printf("5: %d\n", (s5Col + s5Row));
	printf("6: %d\n", (s6Col + s6Row));	
	printf("7: %d\n", (s7Col + s7Row));
	printf("8: %d\n", (s8Col + s8Row));
	
	unsigned int s1 = S1[(s1Col + s1Row)];
	unsigned int s2 = S2[(s2Col + s2Row)];
	unsigned int s3 = S3[(s3Col + s3Row)];
	unsigned int s4 = S4[(s4Col + s4Row)];
	unsigned int s5 = S5[(s5Col + s5Row)];
	unsigned int s6 = S6[(s6Col + s6Row)];
	unsigned int s7 = S7[(s7Col + s7Row)];
	unsigned int s8 = S8[(s8Col + s8Row)];
	
	CIPHER_LR sBoxesRecombined = (CIPHER_LR)((CIPHER_LR)s1<<28) | (CIPHER_LR)((CIPHER_LR)s2 << 24) | 
		(CIPHER_LR)((CIPHER_LR)s3 << 20) | (CIPHER_LR)(s4 << 16) | (CIPHER_LR)((CIPHER_LR)s5 << 12) | 
		(CIPHER_LR)((CIPHER_LR)s6 << 8) | (CIPHER_LR) ((CIPHER_LR)s7 << 4) | (CIPHER_LR) (s8);
	
	printBits(sizeof(sBoxesRecombined), &sBoxesRecombined);
	CIPHER_LR returnVal = 0;
	KEY_LR value = 1;
	for(i = 0; i<32; i++){
		CIPHER_LR tmpPermuted = (CIPHER_LR)((CIPHER_LR)1 << (CIPHER_LR)(32-FEISTEL_PERMUTED[i]));;
		if(tmpPermuted & sBoxesRecombined){
			returnVal |= ((CIPHER_LR)1<< (CIPHER_LR)(i));
		}
	}
	
	return returnVal;
}