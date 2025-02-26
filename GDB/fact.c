#include <stdio.h>
int multiply(int a, int b) {
		printf("a=%d, b=%d\n", a, b);
		return a*b;
	}

int main()
{
	int i, num, j;
	printf ("Enter the number: ");
	scanf ("%d", &num );

	j=1;
	for (i=1; i<=num; i++)
		j=multiply(j,i);    

	printf("The factorial of %d is %d\n",num,j);
}


