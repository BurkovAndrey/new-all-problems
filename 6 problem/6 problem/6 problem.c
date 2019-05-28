#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MNOI 1000
int mass[MNOI];


int minimal_search(int amount_of_elements) {
	int min_value = *mass;
	for (int i = 1; i < amount_of_elements; i++) {
		if (*(mass + i) < min_value) min_value = *(mass + 1);
	}
	return min_value;

}

int maximum_search(int amount_of_elements) {
	int max_value = *mass;
	for (int i = 1; i < amount_of_elements; i++) {
		if (*(mass + i) > max_value) max_value = *(mass + i);
	}
	return max_value;
}

double average(int amount_of_elements) {
	int average_value = 0;
	for (int i = 0; i < amount_of_elements; i++) {
		average_value += mass[i];
	}
	average_value = average_value / amount_of_elements;
	return average_value;
}
double standard_deviation(int amount_of_elements, double average) {
	double st_dev = 0;
	for (int i = 0; i < amount_of_elements; i++) {
		st_dev += pow(mass[i] - average, 2);
	}
	st_dev = st_dev * (1.0 / amount_of_elements);
	st_dev = sqrt(st_dev);
	return st_dev;
}

int main(){
	int amount_of_elements;
	printf("Hi, I calculate the maximum and minimum values, as well as the standard deviation\n");
	while (1) {
		printf("Maximum number of items: 1000");
		printf("\nAmount of elements: ");
		scanf_s("%d", &amount_of_elements);

		printf("\nElement values: ");
		for (int i = 0; i < amount_of_elements; i++)
			scanf_s("%d", &mass[i]);

		int min_value = minimal_search(amount_of_elements);
		int max_value = maximum_search(amount_of_elements);
		double ar = average(amount_of_elements);
		double st_dev = standard_deviation(amount_of_elements, ar);

		printf("\nMinimum values: %d\n", min_value);
		printf("Maximum values: %d\n", max_value);
		printf("average: %lf\n", ar);
		printf("Standard deviation: %lf\n", st_dev);

		printf("\nWould you like to repeat the calculation? \nEnter Y or N \n");
		char MyChar;
		do {
			MyChar = getch();
			if (123 > MyChar & MyChar > 96) MyChar = MyChar - 32;
			if (MyChar == 'N'){
				printf("End work"); return 0;
			}
			if (MyChar != 'Y');
			else break;
		} while (1);
	}
	return 0;
}