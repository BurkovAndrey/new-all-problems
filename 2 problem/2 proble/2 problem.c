#include <stdio.h> 
#include <math.h> 
#include <stdlib.h>

int main() {
	while (1) {
		int number;
		printf("Vvedite chislo:\n");
		scanf_s("%d", &number);

		if (number < 2) {
			printf("Nekorretni vvod!");
		}
		else {
			printf("Vse prostie chisla do vvedennogo:\n");
			for (int knumber = 2; knumber <= number; knumber++) {
				int primal = 1;

				for (int delitel = 2; delitel*delitel <= knumber; delitel++) {
					if (knumber%delitel == 0) {
						primal = 0; break;
					}
				}
				if (primal == 1) {
					printf("%d\t", knumber);
				}
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