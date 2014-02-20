#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

#define SLP_EN 0x2000
#define SLP_TYP_S3 0x1400
#define SLP_TYP_S4 0x1800
#define SLP_TYP_S5 0x1C00
#define IO_PCI_CONFIG_ADDR 0xCF8
#define IO_PCI_CONFIG_DATA 0xCFC

#define IO_RTC_INDEX 0x70
#define IO_RTC_TARGET 0x71

#define RTC_EN 0x0400
#define RTC_SEC 0x00
#define RTC_SEC_ALARM 0x01
#define RTC_MIN 0x02
#define RTC_MIN_ALARM 0x03
#define RTC_HR 0x04
#define RTC_HR_ALARM 0x05

#define RTC_REGA 0x0A
#define RTC_REGB 0x0B
#define RTC_REGB_AIE 0x20



unsigned int BCDtoDEC(unsigned int num_bcd){
	unsigned int num_dec;
	num_dec = 0;
	num_dec = (num_bcd & 0x0000000F) + ((num_bcd >> 4) & 0x0000000F) * 10;
	return num_dec;
}

unsigned int DECtoBCD(unsigned int num_dec){
	unsigned int num_bcd;
	num_bcd = 0;
	num_bcd = (num_dec%10) + (num_dec/10)*16;
	return num_bcd;
}


unsigned int get_RTC(unsigned int rtc_index){
	unsigned int num_dec, rtc_regA_uip;
	rtc_regA_uip = 1;
	num_dec = 0;
	
	outp(IO_RTC_INDEX, RTC_REGA);
	while(rtc_regA_uip){
		rtc_regA_uip = inp(IO_RTC_TARGET) >> 7;
	}
	
	outp(IO_RTC_INDEX, rtc_index);
	num_dec = BCDtoDEC(inp(IO_RTC_TARGET));
	//printf("uip: %d, get secs: %d\n", uip, sec_dec);
	
	return num_dec;
}

void set_RTC(unsigned int rtc_index, unsigned int num_dec){
	unsigned int rtc_regA_uip;
	rtc_regA_uip = 1;
	
	outp(IO_RTC_INDEX, RTC_REGA);
	while(rtc_regA_uip){
		rtc_regA_uip = inp(IO_RTC_TARGET) >> 7;
	}
	
	outp(IO_RTC_INDEX, rtc_index);
	outp(IO_RTC_TARGET, DECtoBCD(num_dec));
	//printf("uip: %d, set times: %d\n", uip, num_dec);
	
}

void get_RTC_time(void){
	printf("now time is %02d:%02d:%02d\n", get_RTC(RTC_HR), get_RTC(RTC_MIN), get_RTC(RTC_SEC));
}

void set_RTC_time(){

}

void get_RTC_alarm(void){
	printf("alarm time is %02d:%02d:%02d\n", get_RTC(RTC_HR_ALARM), get_RTC(RTC_MIN_ALARM), get_RTC(RTC_SEC_ALARM));
}

void set_RTC_alarm_after(int hrs, int mins, int secs){
	int sec, min, hr;
	
	sec = get_RTC(RTC_SEC) + secs;
	min = get_RTC(RTC_MIN) + mins + (sec/60);
	hr = get_RTC(RTC_HR) + hrs + (min/60);
	
	hr = hr%24;
	min = min%60;
	sec = sec%60;
	
	set_RTC(RTC_HR_ALARM, hr);
	set_RTC(RTC_MIN_ALARM, min);
	set_RTC(RTC_SEC_ALARM, sec);
	
	//printf("alarm time is %02d:%02d:%02d\n", get_RTC(RTC_HR_ALARM), get_RTC(RTC_MIN_ALARM), get_RTC(RTC_SEC_ALARM));
}

int main(int argc, char* argv[]){
	unsigned long io_space_Addr, pci_config_Addr, pci_config_Data, PMBASE;
	int command;
	command = 0;
	
	pci_config_Addr = 0x8000F840;
	
	outpd(IO_PCI_CONFIG_ADDR, pci_config_Addr);
	pci_config_Data = inpd(IO_PCI_CONFIG_DATA);
	
	PMBASE = pci_config_Data & 0x0000FF80;
	
	get_RTC_time();
	//get_RTC_alarm();
	
	if(argc>1){
		set_RTC_alarm_after(0,0,atoi(argv[1]));
		get_RTC_alarm();
	}
	
	outp(IO_RTC_INDEX, RTC_REGB);
	outp(IO_RTC_TARGET, inp(IO_RTC_TARGET) | RTC_REGB_AIE);
	
	io_space_Addr = (PMBASE + 0x02);
	outpw(io_space_Addr, inpw(io_space_Addr) | RTC_EN);
	
	printf("Shutdown? y/n: ");
	
	while(1){
		command = getchar();
		if(command == 'n') break;
	
		if(command == 'y'){
			io_space_Addr = (PMBASE + 0x04);
			outpd(io_space_Addr, ( inpd(io_space_Addr) & 0xFFFFC3FF ) | SLP_EN | SLP_TYP_S5 ); 
			break;
		}
	}
	
	/*
	set_RTC_sec(0);
	sec_dec = get_RTC_sec();
	
	for(i=0;i<10;i++){
		while(1){
			if(sec_dec < get_RTC_sec()){
				printf("sec_dec: %d, get_RTC_sec: %d\n", sec_dec, get_RTC_sec());
				break;	
			}
			//sec_dec = get_RTC_sec();
			//printf("count: %d\n", i);
		}
		sec_dec = get_RTC_sec();
		printf("secs: %d\n", sec_dec);
		//set_RTC_sec(i);
		//get_RTC_sec();
	}
	*/

	
	return 0;
}
