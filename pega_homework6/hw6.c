#include<conio.h>
#include<stdio.h>
#include<time.h>

#define IO_PCI_CONFIG_ADDR 0xCF8
#define IO_PCI_CONFIG_DATA 0xCFC

#define PCI_GPIOBASE 0x48

#define GPIO_USE_SEL 0x00
#define GP_IO_SEL 0x04
#define GP_LVL 0x0C



int main(void){
	unsigned int bus, dev, func;
	unsigned long pci_config_addr, pci_config_data, offset;
	unsigned long gpio_base, gpio_func, gpio_set;
	clock_t time;
	
	bus = 0;
	dev = 31;
	func = 0;
	offset = PCI_GPIOBASE;
	
	pci_config_addr = 0x80000000 | (bus << 16) | (dev << 11) | (func << 8) + offset;
	
	outpd(IO_PCI_CONFIG_ADDR, pci_config_addr);
	pci_config_data = inpd(IO_PCI_CONFIG_DATA);
	
	gpio_base = pci_config_data & 0xFFFFFFFE;
	
	gpio_func = gpio_base + GPIO_USE_SEL;
	gpio_set = 0x00400000;
	outpd(gpio_func, inpd(gpio_func) | gpio_set );
	
	gpio_func = gpio_base + GP_IO_SEL;
	gpio_set = 0xFFBFFFFF;
	outpd(gpio_func, inpd(gpio_func) & gpio_set );
	
	gpio_func = gpio_base + GP_LVL;
	gpio_set = 0x00400000;
	
	while(1){
		time = clock();
		
		if(gpio_set == 0x00400000){
			gpio_set = 0xFFBFFFFF;
			outpd(gpio_func, inpd(gpio_func) & gpio_set );
			printf("light off\n");
		}else if(gpio_set == 0xFFBFFFFF){
			gpio_set = 0x00400000;
			outpd(gpio_func, inpd(gpio_func) | gpio_set );
			printf("light on\n");
		}
		
		while(1){
			if( ((float)(clock()-time))/CLOCKS_PER_SEC > 0.5 ){
				break;
			}
		}
	}

	return 0;
}
