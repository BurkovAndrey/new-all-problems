#include <stdio.h>
#include <stdlib.h>
#include <process.h>

#define UNSORTED 100
#define SORTED 10


int compare_lr(int a, int b) {
	if (a > b) return 1;
	return 0;
}

int compare_rl(int a, int b) {
	if (a < b) return 1;
	return 0;
}

int compare_abs(int a, int b) {
	if (abs(a) > abs(b)) return 1;
	return 0;
}
void replace(int *mass, int one_numb, int two_numb) {
	int a = mass[one_numb];
	mass[one_numb] = mass[two_numb];
	mass[two_numb] = a;
}

void sort_array(int *mass, int array_size, int(*c)(int a, int b), void(*r)(int *mass, int one_numb, int two_numb)) {
	int mark = UNSORTED;
	while (mark == UNSORTED) {
		mark = SORTED;
		for (int i = 0; i < array_size - 1; i++) {
			if ((*c)(mass[i], mass[i + 1])) {
				(*r)(mass, i, i + 1);
				mark = UNSORTED;
			}
		}
	}
}
int main() {printf("Hi, I'm sorting a random array\n");
	while (1) {
		int array_size, bottom_line, upper_bound, direction;


		printf("Enter the length of the array: ");
		scanf_s("%d", &array_size);

		int *mass = (int *)(malloc(sizeof(int) * array_size));


		printf("Enter Sort Direction: \n");
		printf("1 - from left to right\n");
		printf("2 - from right to left\n");
		printf("3 - by absolute value\n");
		scanf_s("%d", &direction);


		printf("\nElement values: ");
		for (int i = 0; i < array_size; i++)
			scanf_s("%d", &*(mass + i));
		printf("Unsorted array: \n");
		for (int i = 0; i < array_size; i++)
			printf("%d ", *(mass + i));

		if (direction == 1) sort_array(mass, array_size, compare_lr, replace);
		if (direction == 2) sort_array(mass, array_size, compare_rl, replace);
		if (direction == 3) sort_array(mass, array_size, compare_abs, replace);

		printf("\nSorted array: \n");
		for (int i = 0; i < array_size; i++) printf("%d ", mass[i]);

		printf("\nWould you like to repeat the calculation? \nEnter Y or N \n");
		char MyChar;
		do {
			MyChar = getch();
			if (123 > MyChar & MyChar > 96) MyChar = MyChar - 32;
			if (MyChar == 'N')
			{
				printf("End work"); return 0;
			}
			if (MyChar != 'Y');
			else break;
		} while (1);
	}
}