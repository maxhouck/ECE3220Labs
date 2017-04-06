/*
 * Lab2.c
 *
 *  Created on: Jan 30, 2017
 *      Author: Max Houck
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	problem1();
	//problem2();
	return 1;
}

void problem1() {
	int exit = 0;
	char choice;
	while(exit == 0) {
		printf("1. Factorial\r\n2. Leap Year\r\n3. Maximum\r\n4. Division\r\n5. Exit\r\nEnter a number: ");
		fflush(stdout);
		choice = getchar();
		switch(choice) {
		case '1': factorial();
				break;
		case '2': leap_year();
				break;
		case '3': maximum();
				break;
		case '4': division();
				break;
		case '5': exit = 1;
				break;
		default: printf("\r\nInvalid input. Try again\r\n");
				break;
		}
		int c;
		while((c = getchar()) != '\n' && c != EOF);
	}

}

void factorial() { //calculates factorial of input
	unsigned short n;
	unsigned long m;
	printf("Input an unsigned short: ");
	fflush(stdout);
	scanf("%u",&n);
	if(n > 12) printf("Your number is too big\r\n");
	else {
		for(m=1;n>0;n--) //calculate factorial
			m*=n;
		printf("The factorial is %u\r\n",m);
	}
}

void leap_year() { //determines whether input year is a leap year
	unsigned int n;
	printf("Input a year: ");
	fflush(stdout);
	scanf("%u",&n);
	if(n % 4 == 0) printf("This year is a leap year\r\n"); //mod 4 to check for divisibility
	else printf("This year is not a leap year\r\n");
}

void maximum() { //prints maximum of two numbers
	float x,y,z;
	printf("Input the first number: ");
	fflush(stdout);
	scanf("%f",&x);
	printf("Input the second number: ");
	fflush(stdout);
	scanf("%f",&y);
	z = x > y ? x : y;
	printf("%f is the bigger number\r\n",z);
}

void division() { //divides two floats
	int x,y;
	float z;
	printf("Input the first number: ");
	fflush(stdout);
	scanf("%d",&x);
	printf("Input the second number: ");
	fflush(stdout);
	scanf("%d",&y);
	z = (float)x/(float)y;
	printf("The answer is %f\r\n",z);
}

void problem2() { //binary representation
	unsigned short n;
	printf("Input a decimal number: ");
	fflush(stdout);
	scanf("%d",&n);
	char choice;
	int c;
			while((c = getchar()) != '\n' && c != EOF);
	printf("Would you like to print using (a)rithmetic or (b)itwise operations? ");
	fflush(stdout);
	choice = getchar();
	if(choice == 'a') { //arithmetic method
		int bits = 1;
		while(pow(2,bits) < n) //how many bits do we need
			bits++;
		int buffer[bits];
		int i;
		for(i=0;i<bits;i++) { //pull out powers of 2
			buffer[bits-i-1] = n%2;
			n/=2;
		}
		printf("Your number in binary is: ");
		for(i=0;i<bits;i++) { //print the output
			printf("%d",buffer[i]);
		}
	}
	else if (choice == 'b') { //bitwise method
		int buffer[16]; //maximum 16 bits for unsigned short
		int i;
		for(i=0;i<16;i++)
			buffer[16-i-1] = (n & (1<<i)) >> i; //the formula you want to see
		printf("Your number in binary is: ");
		for(i=0;i<15;i++) //trim leading zeros
			if(buffer[i] == 1)
				break;
		for(;i<16;i++) { //print the trimmed output
			printf("%d",buffer[i]);
		}
	}
	else printf("Invalid choice\r\n");
}
