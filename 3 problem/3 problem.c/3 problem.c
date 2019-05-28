#include <stdio.h>
#include <math.h>

int main()
{
	while (1) {
		int signs; double pi; double tenth = 0.1;
		printf("the precision with which to write pi\n");
		scanf_s("%d", &signs);
		double exactness = pow(tenth, signs);
		double drob;
		int i = 1;
		pi = 0;
		do
		{
			drob = (double)4 / (2 * i - 1);
			pi -= pow(-1, i)*drob;
			i++;
		} while (drob >= exactness);
		printf("%.*lf", signs, pi);
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