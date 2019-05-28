#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>
int main() {
	while (1) {
		double a, b, c, D, x, x1, x2, sqrt_D, x0;
		printf("a=");
		scanf_s("%lf", &a);
		printf("b=");
		scanf_s("%lf", &b);
		printf("c=");
		scanf_s("%lf", &c);
		if (a == 0.0)
		{
			if (b == 0.0)
			{
				if (c == 0.0)
				{
					printf("All real numbers\n");
				}
				else
				{
					printf("No roots\n");
				}
			}
			else
			{
				x0 = -c / b;
				printf("1 root:x=%lf\n", x0);
			}
		}
		else
		{
			D = b * b - 4 * a*c;
			if (D < 0)
				printf("No roots\n");
			else
				if (D == 0)
				{
					x = (double)-b / (2 * a);
					printf("1 root:x=%lf\n", x);
				}
				else
				{
					sqrt_D = (double)sqrt(D);
					x1 = (double)(-b + sqrt_D) / (2 * a);
					x2 = (double)(-b - sqrt_D) / (2 * a);
					printf("2 roots: x1=%lf\tx2=%lf\n", x1, x2);
				}
		}
		printf("\nWould you like to repeat the calculation? \nEnter Y or N \n");
		char MyChar;
		do {
			MyChar = getch();
			if (MyChar > 96) MyChar = MyChar - 32;
			if (MyChar == 'N')
			{
				printf("End work"); return 0;
			}
			if (MyChar != 'Y');
			else break;
		} while (1);
	}
	return 0;
}