#include<conio.h>
#include<stdio.h>

int main(void){
	unsigned long transmitted, VendorID, DeviceID;
	unsigned long configAddr, bus, dev, func;
	
	printf("Vendor_ID\tDevice_ID\tBUS#\tDEV#\tFUNC#\n");
	for( bus = 0; bus < 256 ; bus++ ){
		for(dev = 0; dev < 32; dev++){
			for(func = 0; func < 8; func++){
				configAddr = 0x80000000 | (bus << 16) | (dev << 11) | (func << 8);
				//printf("Config_Address %X\n", configAddr);
				outpd(0xCF8, configAddr);
				transmitted = inpd(0xCFC);
				//printf("00h %X\n",transmitted);
				
				if(transmitted != 0xFFFFFFFF){
					VendorID = transmitted & 0x0000FFFF;
					DeviceID = transmitted >> 16;
					printf("     %04X\t     %04X\t  %02d\t  %02d\t   %02d\n",VendorID, DeviceID, bus, dev, func);
				}
			}
		}
	}
	
	/*
	VendorID = 0;
	DeviceID = 0;
	
	outpd(0xCF8, 0x8000F800);
	
	transmitted = inpd(0xCFC);
	
	VendorID = transmitted & 0x0000FFFF;
	DeviceID = transmitted >> 16;
	
	printf("00h %X\n", transmitted);
	printf("Vendor ID: %X\n", VendorID);
	printf("Device ID: %X\n", DeviceID);
	
	*/
	
	return 0;
}
