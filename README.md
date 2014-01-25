# DES Implementation in C

This repo forms the second part of my dissertation objectives which looks at the DES algorith m in software. 

The choice to develop in C is that so it can be programmed on a NIOS II core on a Cyclone 2 FPGA. 


## Datatypes 
* KEY is a 64 bit unsigned data type used for holding the key. 
* KEY_LR is a 32 bit unsigned int designed for holding the left and right parts of the key used when shifting.
