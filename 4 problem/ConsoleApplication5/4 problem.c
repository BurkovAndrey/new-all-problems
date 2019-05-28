#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double x0;
double func(double x)
{
	double my_func = 3*x - cos(x) - 1;
	return my_func;
}
double d_func(double x)
{
	double d_my_func = 3 + sin(x);
	return d_my_func;
}
double solve(double x, int accuracy)
{
	double delta;
	double tenth = pow(0.1,accuracy);
	double x1;
	do
	{
		double x1 = x - func(x) / d_func(x);
		delta = fabs(x1 - x);
		x = x1;
	} while (delta > tenth);
	x0 = x - func(x) / d_func(x);
	return x0;
}

int main() {
printf("Hi, this program solves this equation 0 = 3*x - cos(x) - 1 with a given accuarcy\n"); 
	while (1) {
		int accuracy; double xl; double xr;
		printf("Enter the initial accuracy\nAccuracy=");
		scanf_s("%d", &accuracy);
		double x0 = 0.5;
		x0 = solve(x0, accuracy);
		do
		{
			printf("Enter the left border xl:\n xl=");
			scanf_s("%lf", &xl);
			if (xl > x0)
				printf("The root of the equation lies to the left, the left border, repeat the input.\n");
		} while (xl > x0);
		printf("The left border is entered correctly.\n");
		do
		{
			printf("Enter the right border xr:\n xr=");
			scanf_s("%lf", &xr);
			if (xr < x0)
				printf("The root of the equation lies to the right, the right border, repeat the input.\n");
		} while (xr < x0);
		printf("The right border is entered correctly.\n The root of the equation in the range from %lf to %lf:\n x0=", xl, xr);
		printf("%.*lf", accuracy, x0);
		printf("\nWould you like to repeat the calculation? \nEnter Y or N.\n");
		char MyChar;
		do {
			MyChar = getch();
			if (MyChar > 96) MyChar = MyChar - 32;
			if (MyChar == 'N')
			{printf("End work"); return 0;}
			if (MyChar != 'Y');
			else break;
		} while (1);
			}
	return 0;
}