#include<conio.h>

#define SLP_EN 0x2000
#define SLP_TYP_S3 0x1400
#define SLP_TYP_S4 0x1800
#define SLP_TYP_S5 0x1C00
#define IO_PCI_CONFIG_ADDR 0xCF8
#define IO_PCI_CONFIG_DATA 0xCFC

int main(void){
	
	unsigned long io_space_Addr, pci_config_Addr, pci_config_Data, PMBASE;
	
	pci_config_Addr = 0x8000F840;
	
	outpd(IO_PCI_CONFIG_ADDR, pci_config_Addr);
	pci_config_Data = inpd(IO_PCI_CONFIG_DATA);
	
	PMBASE = pci_config_Data & 0x0000FF80;
	
	io_space_Addr = (PMBASE + 0x04);
	
	outpd(io_space_Addr, ( inpd(io_space_Addr) & 0xFFFFC3FF ) | SLP_EN | SLP_TYP_S5 ); 
	
	return 0;
}
