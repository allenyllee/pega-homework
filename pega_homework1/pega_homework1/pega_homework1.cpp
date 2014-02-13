#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE 505
//#define MAXINT 1000000000
#define HALFMAXINT 10000

struct BigInt {
	int intNum[ARRAYSIZE];
	
	void operator=(int b){
		int temp, i;
		i = 0;
		temp = b;

		for (int j = 0; j < ARRAYSIZE; j++){
			this->intNum[j] = 0;
		}

		while (temp != 0){
			if (i >= ARRAYSIZE){
				printf("error: HALFMAXINT is too small or ARRAYSIZE is too small.\n");
				return;
			}
			this->intNum[i] = temp % HALFMAXINT;
			temp = (int) temp/HALFMAXINT;
			i++;
		}
	}

	void operator=(BigInt b){
		for (int i = 0; i < ARRAYSIZE; i++){
			if (b.intNum[i] >= HALFMAXINT){
				printf("error: not a valid number.\n");
				return;
			}
			else
			{
				this->intNum[i] = b.intNum[i];
			}
		}
	}

	
	BigInt& operator+(BigInt b){
		BigInt c;
		int temp;

		temp = 0;
		for (int i = 0; i < ARRAYSIZE; i++){
			c.intNum[i] = 0;
		}

		for (int i = 0; i < ARRAYSIZE; i++){
			if (this->intNum[i] >= HALFMAXINT || b.intNum[i] >= HALFMAXINT){
				printf("error: not a valid number.\n");
				return c;
			}
		}

		for (int i = 0; i < ARRAYSIZE; i++){
			temp += this->intNum[i] + b.intNum[i];
			c.intNum[i] = temp % HALFMAXINT;
			temp = (int)temp / HALFMAXINT;
		}
		
		if (temp != 0)
			printf("sum is too big.\n");
		
		return c;
	}

	BigInt& operator*(BigInt b){
		BigInt temp[ARRAYSIZE], c;
		int d;
		
		d = 0;
		for (int i = 0; i < ARRAYSIZE; i++){
			c.intNum[i] = 0;
		}

		for (int i = 0; i < ARRAYSIZE; i++){
			if (this->intNum[i] >= HALFMAXINT || b.intNum[i] >= HALFMAXINT){
				printf("error: not a valid number.\n");
				return c;
			}
		}

		for (int i = 0; i < ARRAYSIZE; i++){
			for (int j = 0; j < ARRAYSIZE; j++){
				temp[i].intNum[j] = b.intNum[i] * this->intNum[j];
			}
		}

		for (int i = 0; i < ARRAYSIZE; i++){
			d = 0;
			
			for (int j = 0; j < ARRAYSIZE-i; j++){
				d += c.intNum[j+i] + temp[i].intNum[j];
				c.intNum[j+i] = d % HALFMAXINT;
				d = (int)d / HALFMAXINT;
			}

			if (d != 0){
				printf("error: number is too big.\n");
				return c;
			}
		}

		return c;
	}

	BigInt& operator+(int b){
		BigInt temp;
		temp = b;
		return *this + temp;
	}

	BigInt& operator*(int b){
		BigInt temp;
		temp = b;
		return *this * temp;
	}


	void operator+=(int b){
		*this = *this + b;
	}

	void operator+=(BigInt b){
		*this = *this + b;
	}

	void operator*=(int b){
		*this = *this * b;
	}

	void operator*=(BigInt b){
		*this = *this * b;
	}

	void bigIntPrint(void){
		for (int i = 0; i < ARRAYSIZE; i++){
			if (this->intNum[ARRAYSIZE - i - 1] != 0){
				printf("%04d", this->intNum[ARRAYSIZE - i - 1]);
			}
		}
		printf("\n");
	}

};




int main(void){
	BigInt factorial, sum, squrefactorial;
	squrefactorial = 0;
	factorial = 1;
	sum = 0;
	
	for (int i = 0; i < 814; i++){
		factorial *= (i + 1);
		sum += factorial;
		
		
		//sum.bigIntPrint();
		//printf("i = %d, ", i);
		
		//factorial.bigIntPrint();

		//printf("i = %d, factorial = %d\n", i, factorial);
		//printf("i = %d, sum = %d\n", i,sum);
	}
	//factorial.bigIntPrint();
	//squrefactorial = factorial* factorial;
	//squrefactorial.bigIntPrint();
	sum.bigIntPrint();

	system("PAUSE");
	return 0;
}