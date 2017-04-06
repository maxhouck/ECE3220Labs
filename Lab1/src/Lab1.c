#define PI 3.1415962

#include <stdio.h>

int main() {
	//Problem 1
	printf("Problem 1\r\n");
	printf("Input the radius of the circle: ");
	fflush(stdout);
	float radius;
	scanf("%f",&radius);
	float area = PI * radius * radius;
	printf("The area of the circle is %f\r\n",area);

	//Problem 2
	printf("Problem 2\r\n");
	printf("Input the cost price: ");
	fflush(stdout);
	float cost,sale;
	scanf("%f",&cost);
	printf("Input the sale price: ");
	fflush(stdout);
	scanf("%f",&sale);
	fflush(stdout);
	if(cost>sale) {
		printf("The item was sold at a loss of $%f\r\n",cost-sale);
		fflush(stdout);
	}
	else if (cost<sale) {
		printf("The item was sold for a profit of $%f\r\n",sale-cost);
		fflush(stdout);
	}
	else if (cost == sale) {
		printf("The item was bought and sold for the same price\r\n");
		fflush(stdout);
	}

	//Problem 3
	int operand1,operand2;
	char operator;
	printf("Problem 3\r\nEnter your first operand (integers only!): ");
	fflush(stdout);
	scanf("%d",&operand1);
	printf("Enter your second operand: ");
	fflush(stdout);
	scanf("%d",&operand2);
	fflush(stdout);
	printf("Enter your operator: ");
	fflush(stdout);
	scanf(" %c",&operator);
	switch(operator) {
		case '+': printf("%d + %d = %d",operand1,operand2,operand1+operand2);
			fflush(stdout);
			break;
		case '-': printf("%d - %d = %d",operand1,operand2,operand1-operand2);
		fflush(stdout);
			break;
		case '*': printf("%d * %d = %d",operand1,operand2,operand1*operand2);
		fflush(stdout);
			break;
		case '/': printf("%d / %d = %d",operand1,operand2,operand1/operand2);
			fflush(stdout);
			break;
		default: printf("Invalid input");
			fflush(stdout);
			break;
	}
}
