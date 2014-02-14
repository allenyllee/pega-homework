#include<conio.h>
#include<stdio.h>

int main(void){
	unsigned long transmitted, VendorID, DeviceID;
	VendorID = 0;
	DeviceID = 0;
	
	outpd(0xCF8, 0x8000F800);
	
	transmitted = inpd(0xCFC);
	
	VendorID = transmitted & 0x0000FFFF;
	DeviceID = transmitted >> 16;
	
	printf("00h %X\n", transmitted);
	printf("Vendor ID: %X\n", VendorID);
	printf("Device ID: %X\n", DeviceID);
	
	return 0;
}
