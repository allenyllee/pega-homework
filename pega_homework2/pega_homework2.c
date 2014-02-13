#include<conio.h>
#include<time.h>


int main(void){
	clock_t start_time, end_time;
	int i;
	
	for(i=0;i<60;i++){
		start_time = clock();
		
		outp(0x80,0xF7+i);
		
		end_time = clock();
		while((end_time - start_time)/CLOCKS_PER_SEC <1){
			end_time = clock();
		}
	}
	
	//outp(0x80,0xF7);
	
	return 0;
}
